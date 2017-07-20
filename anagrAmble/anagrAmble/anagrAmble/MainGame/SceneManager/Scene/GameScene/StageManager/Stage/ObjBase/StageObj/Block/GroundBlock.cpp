//==================================================================================================================================//
//!< @file		GroundBlock.cpp
//!< @brief		ar::GroundBlockクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "GroundBlock.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

GroundBlock::GroundBlock(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
						, const Stage::INDEX_DATA& rStageIndexData, const sl::DrawingID& rID)
	: StageObj(pStageDataManager, pCollisionManager, rStageIndexData)
{
	m_DrawingID = rID;
	m_TypeID = GROUND_B;
}

GroundBlock::~GroundBlock(void)
{}

void GroundBlock::Initialize(void)
{
	m_Pos.x = m_StageIndexData.m_XIndexNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YIndexNum * m_StageChipSize + (m_StageChipSize / 2);
	m_RectSize = m_pLibrary->GetSizeRect(m_DrawingID.m_VtxID);
}

void GroundBlock::ChangeStagePos(short yIndexNum, short xIndexNum)
{
	// 変更はないので、処理なし
}

void GroundBlock::ProcessCollision(const CollisionManager::CollisionData& rData)
{
	// 処理なし
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void GroundBlock::Run(void)
{
	// 処理なし
}

void GroundBlock::Render(void)
{
	m_pLibrary->Draw2D( m_DrawingID, (m_Pos - m_BasePointPos));
}

void GroundBlock::HandleEvent(void)
{
	// 処理なし
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
