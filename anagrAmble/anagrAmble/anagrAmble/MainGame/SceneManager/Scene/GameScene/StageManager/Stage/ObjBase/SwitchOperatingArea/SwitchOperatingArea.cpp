//==================================================================================================================================//
//!< @file		SwitchOperatingArea.cpp		
//!< @brief		ar::SwitchOperatingAreaクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "SwitchOperatingArea.h"
#include "../../CollisionManager.h"

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

void SwitchOperatingArea::Draw(void)
{}

void SwitchOperatingArea::SwitchOnState(void)
{
	m_TypeID = ObjBase::SWITCH_OPERATING_AREA_ON;
	// 衝突判定用データへ追加
	m_pCollisionManager->SetSwitchOperatingAreaData(this);
}

void SwitchOperatingArea::SwitchOffState(void)
{
	m_TypeID = ObjBase::SWITCH_OPERATING_AREA_OFF;
	// 衝突判定用データへ追加
	m_pCollisionManager->SetSwitchOperatingAreaData(this);
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

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
