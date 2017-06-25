//==================================================================================================================================//
//!< @file		SwitchOperatingArea.cpp		
//!< @brief		ar::SwitchOperatingAreaクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "SwitchOperatingArea.h"
#include "../../CollisionManager.h"
#include "../../../../GameEventManager/GameEventManager.h"
#include "../../../../GameEventManager/EventListener.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

SwitchOperatingArea::SwitchOperatingArea(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
										, const Stage::INDEX_DATA& rStageIndexData, ObjBase* pOwner)
	: ObjBase(pStageDataManager, pCollisionManager, rStageIndexData)
	, m_pOwner(pOwner)
{
	m_Pos		= m_pOwner->GetPos();
	m_TypeID	= ObjBase::SWITCH_OPERATING_AREA_OFF;
}

SwitchOperatingArea::~SwitchOperatingArea(void)
{}

void SwitchOperatingArea::Control(void)
{
	// 衝突判定用データへ追加
	m_pCollisionManager->SetSwitchOperatingAreaData(this);
}

void SwitchOperatingArea::SwitchOnState(void)
{
	m_TypeID = ObjBase::SWITCH_OPERATING_AREA_ON;
}

void SwitchOperatingArea::SwitchOffState(void)
{
	m_TypeID = ObjBase::SWITCH_OPERATING_AREA_OFF;
}

void SwitchOperatingArea::Initialize(void)
{
	// 空間入れ替え終了イベント
	GameEventManager::Instance().RegisterEventType("space_change_end", m_pEventListener);
	m_pEventListener->RegisterSynEventFunc("space_change_end", std::bind(&ar::SwitchOperatingArea::ResisterCollision, this));

	// 時戻し終了イベント
	GameEventManager::Instance().RegisterEventType("space_change_return_end", m_pEventListener);
	m_pEventListener->RegisterSynEventFunc("space_change_return_end", std::bind(&ar::SwitchOperatingArea::ResisterCollision, this));

	// プレイヤーリスポーン終了イベント
	GameEventManager::Instance().RegisterEventType("player_respawn_end", m_pEventListener);
	m_pEventListener->RegisterSynEventFunc("player_respawn_end", std::bind(&ar::SwitchOperatingArea::ResisterCollision, this));
}

void SwitchOperatingArea::ChangeStagePos(short yIndexNum, short xIndexNum)
{
	m_StageIndexData.m_YNum = yIndexNum;
	m_StageIndexData.m_XNum = xIndexNum;
	m_Pos					= m_pOwner->GetPos();
}

void SwitchOperatingArea::ProcessCollision(const CollisionManager::CollisionData& rData)
{}

/* Private Functions ------------------------------------------------------------------------------------------ */

void SwitchOperatingArea::HandleEvent(void)
{}

void SwitchOperatingArea::ResisterCollision(void)
{
	m_pCollisionManager->SetSwitchOperatingAreaData(this);
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
