﻿//==================================================================================================================================//
//!< @file		GroundBlockBlock.cpp
//!< @brief		ar::GroundBlockBlockBlockクラスヘッダ
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
	CalculatePos();
	m_DrawingID = rID;
	m_TypeID = GROUND_B;
	m_RectSize = m_pLibrary->GetSizeRect(m_DrawingID.m_VtxID);
	m_CurrentRectData.m_Left	= m_Pos.x + m_RectSize.m_Left; 
	m_CurrentRectData.m_Right	= m_Pos.x + m_RectSize.m_Right;
	m_CurrentRectData.m_Top		= m_Pos.y + m_RectSize.m_Top;
	m_CurrentRectData.m_Bottom	= m_Pos.y + m_RectSize.m_Bottom;
}

GroundBlock::~GroundBlock(void)
{}

void GroundBlock::ProcessCollision(int typeID, bool isDeath)
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

void GroundBlock::CalculatePos(void)
{
	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize + (m_StageChipSize / 2);
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//