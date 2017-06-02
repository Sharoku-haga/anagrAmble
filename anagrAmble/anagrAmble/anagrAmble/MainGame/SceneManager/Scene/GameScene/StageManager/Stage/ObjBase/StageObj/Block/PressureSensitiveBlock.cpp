//==================================================================================================================================//
//!< @file		PressureSensitiveBlock.cpp
//!< @brief		ar::PressureSensitiveBlockクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "PressureSensitiveBlock.h"
#include "../../../../StageDataManager.h"

namespace ar
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const sl::fRect		BlockOnUV = { 0.15f, 0.0f, 0.2f, 0.088f};				// 感圧ONのときのUV値
const sl::fRect		BlockOffUV = {0.1f, 0.0f, 0.15f,  0.088f};				// 感圧OFFのときのUV値

}

/* Public Functions ------------------------------------------------------------------------------------------- */

PressureSensitiveBlock::PressureSensitiveBlock(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
	, const Stage::INDEX_DATA& rStageIndexData, int texID)
	: StageObj(pStageDataManager, pCollisionManager, rStageIndexData)
{
	CalculatePos();
	m_TypeID = PRESSURE_SENSITIVE_B;

	m_DrawingID.m_TexID = texID;

	// ブロックサイズのRect構造体を作成
	float chipSize = m_pStageDataManager->GetStageChipSize();
	m_RectSize.m_Left = -(chipSize / 2);
	m_RectSize.m_Top = -(chipSize / 2);
	m_RectSize.m_Right = (chipSize / 2);
	m_RectSize.m_Bottom = (chipSize / 2);

	m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, BlockOffUV);

	m_CurrentRectData.m_Left = m_Pos.x + m_RectSize.m_Left;
	m_CurrentRectData.m_Top = m_Pos.y + m_RectSize.m_Top;
	m_CurrentRectData.m_Right = m_Pos.x + m_RectSize.m_Right;
	m_CurrentRectData.m_Bottom = m_Pos.y + m_RectSize.m_Bottom;

}

PressureSensitiveBlock::~PressureSensitiveBlock(void)
{
	m_pLibrary->ReleaseVertex2D(m_DrawingID.m_VtxID);
}

void PressureSensitiveBlock::ProcessCollision(const CollisionManager::CollisionData& rData)
{}

/* Private Functions ------------------------------------------------------------------------------------------ */

void PressureSensitiveBlock::Run(void)
{}

void PressureSensitiveBlock::Render(void)
{
	m_pLibrary->Draw2D( m_DrawingID, (m_Pos - m_BasePointPos));
}

void PressureSensitiveBlock::HandleEvent(void)
{}

void PressureSensitiveBlock::CalculatePos(void)
{
	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize + (m_StageChipSize / 2);
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
