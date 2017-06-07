//==================================================================================================================================//
//!< @file		LightBlock.cpp
//!< @brief		ar::LightBlockクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "LightBlock.h"
#include "../../../../StageDataManager.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

LightBlock::LightBlock(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
								, const Stage::INDEX_DATA& rStageIndexData, int texID)
	: StageObj(pStageDataManager, pCollisionManager, rStageIndexData)
{
	CalculatePos();
	m_TypeID = LIGHT_B;

	m_DrawingID.m_TexID = texID;

	// ブロックサイズのRect構造体を作成
	float chipSize = m_pStageDataManager->GetStageChipSize();
	m_RectSize.m_Left		= -(chipSize / 2);
	m_RectSize.m_Top		= -(chipSize / 2);
	m_RectSize.m_Right		= (chipSize / 2);
	m_RectSize.m_Bottom		= (chipSize / 2);

	const sl::fRect		uv = {0.2f, 0.1777f, 0.25f, 0.264f};

	m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, uv);

	m_CurrentRectData.m_Left	= m_Pos.x + m_RectSize.m_Left;
	m_CurrentRectData.m_Top		= m_Pos.y + m_RectSize.m_Top;
	m_CurrentRectData.m_Right	= m_Pos.x + m_RectSize.m_Right;
	m_CurrentRectData.m_Bottom	= m_Pos.y + m_RectSize.m_Bottom;
}

LightBlock::~LightBlock(void)
{
	m_pLibrary->ReleaseVertex2D(m_DrawingID.m_VtxID);
}

void LightBlock::ProcessCollision(const CollisionManager::CollisionData& rData)
{}

/* Private Functions ------------------------------------------------------------------------------------------ */

void LightBlock::Run(void)
{}

void LightBlock::Render(void)
{
	m_pLibrary->Draw2D( m_DrawingID, (m_Pos - m_BasePointPos));
}

void LightBlock::HandleEvent(void)
{}

void LightBlock::CalculatePos(void)
{
	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize + (m_StageChipSize / 2);
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
