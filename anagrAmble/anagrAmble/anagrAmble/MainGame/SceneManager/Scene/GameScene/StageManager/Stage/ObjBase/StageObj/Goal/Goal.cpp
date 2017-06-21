//==================================================================================================================================//
//!< @file		Goal.cpp
//!< @brief		ar::Goalクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "Goal.h"
#include "../../../../StageDataManager.h"
#include "../../../../../GameEventManager/GameEventManager.h"
#include "../../../../../GameEventManager/EventListener.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

Goal::Goal(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
			, const Stage::INDEX_DATA& rStageIndexData,  int texID,  ObjBase::TYPE_ID typeID)
	: StageObj(pStageDataManager, pCollisionManager, rStageIndexData)
	, m_HasCollidedWithPlayer(false)
{
	m_TypeID = typeID;
	m_DrawingID.m_TexID = texID;
}

Goal::~Goal(void)
{
	m_pLibrary->ReleaseVertex2D(m_DrawingID.m_VtxID);
}

void  Goal::Initialize(void)
{
	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2) + m_StageChipSize;
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize - (m_StageChipSize / 2);

	// ブロックサイズのRect構造体を作成
	m_RectSize.m_Left	=  -((m_StageChipSize * 3) / 2);
	m_RectSize.m_Top	=  -((m_StageChipSize * 3) / 2);
	m_RectSize.m_Right	= ((m_StageChipSize * 3) / 2);
	m_RectSize.m_Bottom = ((m_StageChipSize * 3) / 2);

	const sl::fRect		uv = { 0.6f, 0.444f, 0.75f, 0.8f};			/** @todo 2017/06/17 とりあえず開いている画像にしておく*/

	m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, uv);

	// イベント登録
	// 特殊アクションボタンが押されるイベント
	GameEventManager::Instance().RegisterEventType("special_action", m_pEventListener);

	// ゴールキーを取得するイベント
	GameEventManager::Instance().RegisterEventType("goal_key_get", m_pEventListener);
}

void Goal::ChangeStagePos(short yIndexNum, short xIndexNum)
{
	m_StageIndexData.m_YNum = yIndexNum;
	m_StageIndexData.m_XNum = xIndexNum;

	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2) + m_StageChipSize;
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize - (m_StageChipSize / 2);

}

void Goal::ProcessCollision(const CollisionManager::CollisionData& rData)
{
	switch(rData.m_ObjType)
	{

	case ObjBase::PLAYER:
		m_HasCollidedWithPlayer = true;
		break;

	default:
		// do nothing
		break;

	}
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void Goal::Run(void)
{
	m_HasCollidedWithPlayer = false;
}

void Goal::Render(void)
{
	m_pLibrary->Draw2D( m_DrawingID, (m_Pos - m_BasePointPos));
}

void Goal::HandleEvent(void)
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
			if(gameEvent == "special_action" && m_HasCollidedWithPlayer && m_TypeID == GOAL)
			{
				// ゴールに到達したイベントを通知する
				GameEventManager::Instance().ReceiveEvent("goal_touch");
				break;
			}
			else if(gameEvent == "goal_key_get"  && m_TypeID == LOCKED_GOAL)
			{
				m_TypeID = GOAL;
				break;
			}
		}

		m_pEventListener->DelEvent();
	}
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
