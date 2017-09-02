//==================================================================================================================================//
//!< @file		Lever.cpp
//!< @brief		ar::Leverクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "Lever.h"
#include "../../../../StageDataManager.h"
#include "../../SwitchOperatingArea/SwitchOperatingArea.h"
#include "../../../../../GameEventManager/GameEventManager.h"
#include "../../../../../GameEventManager/EventListener.h"
#include "../../../../../GameSceneSoundID.h"
#include "../../../StageEffect/SandwichEffect.h"
#include "../../../../../../../SoundManager/SceneSoundManager.h"

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const sl::fRect		LeverOffUV		= { 0.3f, 0.0f, 0.35f, 0.088f};				// レバーが左に傾いているときのUV値
const sl::fRect		LeverOnUV		= { 0.4f, 0.0f, 0.45f, 0.088f};				// レバーが右に傾いているときのUV値

}

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

Lever::Lever(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
	, const Stage::INDEX_DATA& rStageIndexData, int texID)
	: StageObj(pStageDataManager, pCollisionManager, rStageIndexData)
	, m_pSwitchOperatingArea(nullptr)
	, m_HasCollidedWithPlayer(false)
	, m_IsOnState(false)
{
	m_TypeID = LEVER;
	m_DrawingID.m_TexID = texID;
}

Lever::~Lever(void)
{
	sl::DeleteSafely(&m_pSandwichEffect);
	sl::DeleteSafely(&m_pSwitchOperatingArea);
	m_pLibrary->ReleaseVertex2D(m_DrawingID.m_VtxID);
}

void Lever::Initialize(void)
{
	m_Pos.x = m_StageIndexData.m_XIndexNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YIndexNum * m_StageChipSize + (m_StageChipSize / 2);

	// 矩形サイズを設定
	m_RectSize.m_Left		= -(m_StageChipSize / 2);
	m_RectSize.m_Top		= -(m_StageChipSize / 2);
	m_RectSize.m_Right		= (m_StageChipSize / 2);
	m_RectSize.m_Bottom		= (m_StageChipSize / 2);

	m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, LeverOffUV);

	m_pSwitchOperatingArea = new SwitchOperatingArea(m_pStageDataManager, m_pCollisionManager, m_StageIndexData, this);
	m_pSwitchOperatingArea->Initialize();

	m_pSandwichEffect = new SandwichEffect(m_Pos, m_RectSize, m_DrawingID, m_StageChipSize);
	m_pSandwichEffect->Initialize();

	// イベント登録
	// 特殊アクションボタンが押されるイベント
	GameEventManager::Instance().RegisterEventType("special_action", m_pEventListener);
}

void Lever::ChangeStagePos(short yIndexNum, short xIndexNum)
{
	m_StageIndexData.m_YIndexNum = yIndexNum;
	m_StageIndexData.m_XIndexNum = xIndexNum;

	m_Pos.x = m_StageIndexData.m_XIndexNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YIndexNum * m_StageChipSize + (m_StageChipSize / 2);

	m_pSwitchOperatingArea->SwitchOffState();

	m_pSwitchOperatingArea->ChangeStagePos(yIndexNum, xIndexNum);

	if(m_IsOnState)
	{
		m_pSwitchOperatingArea->SwitchOnState();
	}
	else
	{
		m_pSwitchOperatingArea->SwitchOffState();
	}

	m_pSandwichEffect->ChangeStagePos(m_Pos);
}

void Lever::ProcessCollision(const CollisionManager::CollisionData& rData)
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

void Lever::Run(void)
{
	m_HasCollidedWithPlayer = false;
	m_pSwitchOperatingArea->Control();

	if(m_HasBeenSandwiched)
	{	
		m_pSandwichEffect->Control();
	}
}

void Lever::Render(void)
{
	m_pLibrary->Draw2D( m_DrawingID, (m_Pos - m_BasePointPos));

	if(m_HasBeenSandwiched)
	{
		m_pSandwichEffect->Draw();
	}
}

void Lever::HandleEvent(void)
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
			if(gameEvent == "special_action" && m_HasCollidedWithPlayer)
			{
				if(m_IsOnState)
				{
					m_pSwitchOperatingArea->SwitchOffState();
					m_pLibrary->SetVtxUV(m_DrawingID.m_VtxID, LeverOffUV);
					m_pSandwichEffect->ChangeUV();
					m_IsOnState = false;
					SceneSoundManager::Instance().PlayBackSound(static_cast<int>(GAME_SCENE_SOUND_ID::LEVER), sl::RESET_PLAY);
				}
				else
				{
					m_pSwitchOperatingArea->SwitchOnState();
					m_pLibrary->SetVtxUV(m_DrawingID.m_VtxID, LeverOnUV);
					m_pSandwichEffect->ChangeUV();
					m_IsOnState = true;
					SceneSoundManager::Instance().PlayBackSound(static_cast<int>(GAME_SCENE_SOUND_ID::LEVER), sl::RESET_PLAY);
				}
			}
		}

		m_pEventListener->DelEvent();
	}
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
