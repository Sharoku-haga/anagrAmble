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

const sl::fRect		LeverLeftUV		= { 0.55f, 0.0f, 0.6f, 0.088f};				// レバーが左に傾いているときのUV値
const sl::fRect		LeverRightUV	= { 0.6f, 0.0f, 0.65f, 0.088f};				// レバーが右に傾いているときのUV値

}

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

Lever::Lever(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
								, const Stage::INDEX_DATA& rStageIndexData, int texID)
	: StageObj(pStageDataManager, pCollisionManager, rStageIndexData)
{
	CalculatePos();
	m_TypeID = LEVER;

	m_DrawingID.m_TexID = texID;

	// ブロックサイズのRect構造体を作成
	float chipSize = m_pStageDataManager->GetStageChipSize();
	m_RectSize.m_Left		= -(chipSize / 2);
	m_RectSize.m_Top		= -(chipSize / 2);
	m_RectSize.m_Right		= (chipSize / 2);
	m_RectSize.m_Bottom		= (chipSize / 2);

	m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, LeverLeftUV);

	m_CurrentRectData.m_Left	= m_Pos.x + m_RectSize.m_Left;
	m_CurrentRectData.m_Top		= m_Pos.y + m_RectSize.m_Top;
	m_CurrentRectData.m_Right	= m_Pos.x + m_RectSize.m_Right;
	m_CurrentRectData.m_Bottom	= m_Pos.y + m_RectSize.m_Bottom;
}

Lever::~Lever(void)
{
	m_pLibrary->ReleaseVertex2D(m_DrawingID.m_VtxID);
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

void Lever::CalculatePos(void)
{
	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize + (m_StageChipSize / 2);
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
