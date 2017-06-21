//==================================================================================================================================//
//!< @file		GoalKey.cpp
//!< @brief		ar::GoalKeyクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "GoalKey.h"
#include "../../../../StageDataManager.h"
#include "../../../../../GameEventManager/GameEventManager.h"
#include "../../../../../GameEventManager/EventListener.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

GoalKey::GoalKey(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
				, const Stage::INDEX_DATA& rStageIndexData, int texID)
	: StageObj(pStageDataManager, pCollisionManager, rStageIndexData)
	, m_HasCollidedWithPlayer(false)
	, m_HasBeenGotPlayer(false)
{
	m_TypeID = GOAL_KEY;
	m_DrawingID.m_TexID = texID;
}

GoalKey::~GoalKey(void)
{
	m_pLibrary->ReleaseVertex2D(m_DrawingID.m_VtxID);
}

void GoalKey::Initialize(void)
{
	// 位置座標を求める
	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize + (m_StageChipSize / 2);

	// ブロックサイズのRect構造体を作成
	m_RectSize.m_Left		= -(m_StageChipSize / 2);
	m_RectSize.m_Top		= -(m_StageChipSize / 2);
	m_RectSize.m_Right		= (m_StageChipSize / 2);
	m_RectSize.m_Bottom		= (m_StageChipSize / 2);

	const sl::fRect		uv = { 0.0f, 0.0f, 0.1f, 0.176f };		/** @todo 2017/06/17 UV値がわからないので適当あたいにしておく*/ 

	m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, uv);

	// イベント登録
	// 特殊アクションボタンが押されるイベント
	GameEventManager::Instance().RegisterEventType("special_action", m_pEventListener);
}

void GoalKey::ChangeStagePos(short yIndexNum, short xIndexNum)
{
	// すでに取得されているなら即return
	if(m_HasBeenGotPlayer)
	{
		return;
	}

	m_StageIndexData.m_YNum = yIndexNum;
	m_StageIndexData.m_XNum = xIndexNum;

	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize + (m_StageChipSize / 2);
}

void GoalKey::ProcessCollision(const CollisionManager::CollisionData& rData)
{
	switch(rData.m_ObjType)
	{
	case PLAYER:
		m_HasCollidedWithPlayer = true;
		break;

	default:
		// do nothing
		break;
	}
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void GoalKey::Run(void)
{
	m_HasCollidedWithPlayer = false;
}

void GoalKey::Render(void)
{
	// すでに取得されているなら即return
	if(m_HasBeenGotPlayer)
	{
		return;
	}
	m_pLibrary->Draw2D( m_DrawingID, (m_Pos - m_BasePointPos));
}

void GoalKey::HandleEvent(void)
{
	if(m_pEventListener->EmptyCurrentEvent())
	{
		return;
	}
	else
	{
		const std::deque<std::string>& currentEvents = m_pEventListener->GetEvent();

		std::string eventType;			
		for(auto& gameEvent : currentEvents)
		{
			if(gameEvent == "special_action" && m_HasCollidedWithPlayer 
				&& RESULT_FAILED(m_HasBeenGotPlayer))
			{
				GameEventManager::Instance().ReceiveEvent("goal_key_get");
				
				// 取得されたフラグにして、さらに衝突しないステージの端へ移動させる
				m_HasBeenGotPlayer = true;
				m_StageIndexData.m_YNum = 0;
				m_StageIndexData.m_XNum = 0;
			}
		}

		m_pEventListener->DelEvent();
	}
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
