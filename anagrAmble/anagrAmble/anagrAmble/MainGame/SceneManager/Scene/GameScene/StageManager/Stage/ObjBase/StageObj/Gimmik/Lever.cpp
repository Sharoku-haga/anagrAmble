//==================================================================================================================================//
//!< @file		Lever.cpp
//!< @brief		ar::Leverクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "Lever.h"
#include "../../../../StageDataManager.h"

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const sl::fRect		LeverLeftUV		= { 0.3f, 0.0f, 0.35f, 0.088f};				// レバーが左に傾いているときのUV値
const sl::fRect		LeverRightUV	= { 0.4f, 0.0f, 0.45f, 0.088f};				// レバーが右に傾いているときのUV値

}

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

Lever::Lever(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
								, const Stage::INDEX_DATA& rStageIndexData, int texID)
	: StageObj(pStageDataManager, pCollisionManager, rStageIndexData)
{
	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize + (m_StageChipSize / 2);

	m_TypeID = LEVER;

	m_DrawingID.m_TexID = texID;

	// ブロックサイズのRect構造体を作成
	m_RectSize.m_Left		= -(m_StageChipSize / 2);
	m_RectSize.m_Top		= -(m_StageChipSize / 2);
	m_RectSize.m_Right		= (m_StageChipSize / 2);
	m_RectSize.m_Bottom		= (m_StageChipSize / 2);

	m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, LeverLeftUV);
}

Lever::~Lever(void)
{
	m_pLibrary->ReleaseVertex2D(m_DrawingID.m_VtxID);
}

void Lever::ChangeStagePos(short yIndexNum, short xIndexNum)
{
	m_StageIndexData.m_YNum = yIndexNum;
	m_StageIndexData.m_XNum = xIndexNum;

	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize + (m_StageChipSize / 2);
}

void Lever::ProcessCollision(const CollisionManager::CollisionData& rData)
{}

/* Private Functions ------------------------------------------------------------------------------------------ */

void Lever::Run(void)
{}

void Lever::Render(void)
{
	m_pLibrary->Draw2D( m_DrawingID, (m_Pos - m_BasePointPos));
}

void Lever::HandleEvent(void)
{}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
