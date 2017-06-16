//==================================================================================================================================//
//!< @file		NormalBlock.cpp
//!< @brief		ar::NormalBlockクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "NormalBlock.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

NormalBlock::NormalBlock(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
						, const Stage::INDEX_DATA& rStageIndexData, const sl::DrawingID& rID)
	: StageObj(pStageDataManager, pCollisionManager, rStageIndexData)
{
	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize + (m_StageChipSize / 2);

	m_DrawingID = rID;
	m_TypeID = NORMAL_B;
	m_RectSize = m_pLibrary->GetSizeRect(m_DrawingID.m_VtxID);
}

NormalBlock::~NormalBlock(void)
{}

void NormalBlock::ChangeStagePos(short yIndexNum, short xIndexNum)
{
	m_StageIndexData.m_YNum = yIndexNum;
	m_StageIndexData.m_XNum = xIndexNum;

	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize + (m_StageChipSize / 2);
}

void NormalBlock::ProcessCollision(const CollisionManager::CollisionData& rData)
{
	// 処理なし
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void NormalBlock::Run(void)
{
	HandleEvent();
}

void NormalBlock::Render(void)
{
	m_pLibrary->Draw2D( m_DrawingID, (m_Pos - m_BasePointPos));
}

void NormalBlock::HandleEvent(void)
{}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
