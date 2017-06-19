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
	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize + (m_StageChipSize / 2);
	
	m_TypeID = PRESSURE_SENSITIVE_B;

	m_DrawingID.m_TexID = texID;

	// ブロックサイズのRect構造体を作成
	m_RectSize.m_Left		= -(m_StageChipSize / 2);
	m_RectSize.m_Top		= -(m_StageChipSize / 2);
	m_RectSize.m_Right		= (m_StageChipSize / 2);
	m_RectSize.m_Bottom		= (m_StageChipSize / 2);

	m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, BlockOffUV);
}

PressureSensitiveBlock::~PressureSensitiveBlock(void)
{
	m_pLibrary->ReleaseVertex2D(m_DrawingID.m_VtxID);
}

void PressureSensitiveBlock::ChangeStagePos(short yIndexNum, short xIndexNum)
{
	m_StageIndexData.m_YNum = yIndexNum;
	m_StageIndexData.m_XNum = xIndexNum;

	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize + (m_StageChipSize / 2);
}

void PressureSensitiveBlock::ProcessCollision(const CollisionManager::CollisionData& rData)
{
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void PressureSensitiveBlock::Run(void)
{}

void PressureSensitiveBlock::Render(void)
{
	m_pLibrary->Draw2D( m_DrawingID, (m_Pos - m_BasePointPos));
}

void PressureSensitiveBlock::HandleEvent(void)
{}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
