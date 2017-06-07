//==================================================================================================================================//
//!< @file		SpearBlock.cpp
//!< @brief		ar::SpearBlockクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "SpearBlock.h"
#include "Spear.h"
#include "../../../../../StageDataManager.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

SpearBlock::SpearBlock(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
				, const Stage::INDEX_DATA& rStageIndexData, int texID)
	: StageObj(pStageDataManager, pCollisionManager, rStageIndexData)
{
	CalculatePos();
	m_TypeID = SPEAR_B;
	m_DrawingID.m_TexID = texID;

	// ブロックサイズのRect構造体を作成
	float chipSize = m_pStageDataManager->GetStageChipSize();
	m_RectSize.m_Left		= -(chipSize / 2);
	m_RectSize.m_Top		= -(chipSize / 2);
	m_RectSize.m_Right		= (chipSize / 2);
	m_RectSize.m_Bottom		= (chipSize / 2);

	const sl::fRect		uv = {0.35f, 0.1777f, 0.4f, 0.264f};

	m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, uv);
	
	m_pSpear = new Spear(m_pStageDataManager, m_pCollisionManager, m_StageIndexData, m_DrawingID.m_TexID);

	m_CurrentRectData.m_Left	= m_Pos.x + m_RectSize.m_Left;
	m_CurrentRectData.m_Top		= m_Pos.y + m_RectSize.m_Top;
	m_CurrentRectData.m_Right	= m_Pos.x + m_RectSize.m_Right;
	m_CurrentRectData.m_Bottom	= m_Pos.y + m_RectSize.m_Bottom;

}

SpearBlock::~SpearBlock(void)
{
	sl::DeleteSafely(m_pSpear);
	m_pLibrary->ReleaseVertex2D(m_DrawingID.m_VtxID);
}

void SpearBlock::ProcessCollision(const CollisionManager::CollisionData& rData)
{}

/* Private Functions ------------------------------------------------------------------------------------------ */

void SpearBlock::Run(void)
{
	m_pSpear->Control();
}

void SpearBlock::Render(void)
{
	m_pSpear->Draw();
	m_pLibrary->Draw2D( m_DrawingID, (m_Pos - m_BasePointPos));	
}

void SpearBlock::HandleEvent(void)
{}

void SpearBlock::CalculatePos(void)
{
	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize + (m_StageChipSize / 2);
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
