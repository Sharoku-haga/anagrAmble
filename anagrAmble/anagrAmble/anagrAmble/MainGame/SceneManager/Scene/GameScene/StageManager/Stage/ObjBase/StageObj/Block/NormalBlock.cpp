﻿//==================================================================================================================================//
//!< @file		NormalBlock.cpp
//!< @brief		ar::NormalBlockクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "NormalBlock.h"
#include "../../../StageEffect/SandwichEffect.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

NormalBlock::NormalBlock(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
						, const Stage::INDEX_DATA& rStageIndexData, int texID)
	: StageObj(pStageDataManager, pCollisionManager, rStageIndexData)
{
	m_DrawingID.m_TexID = texID;
	m_TypeID = NORMAL_B;
}

NormalBlock::~NormalBlock(void)
{
	sl::DeleteSafely(&m_pSandwicheffect);
}

void NormalBlock::Initialize(void)
{
	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize + (m_StageChipSize / 2);
	
	// ブロックサイズのRect構造体を作成
	m_RectSize.m_Left		= -(m_StageChipSize / 2);
	m_RectSize.m_Top		= -(m_StageChipSize / 2);
	m_RectSize.m_Right		= (m_StageChipSize / 2);
	m_RectSize.m_Bottom		= (m_StageChipSize / 2);

	sl::fRect	uv = { 0.0f, 0.0f, 0.05f, 0.088f};
	m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, uv);
	m_pSandwicheffect = new SandwichEffect(m_Pos, m_RectSize, m_DrawingID, m_StageChipSize);
	m_pSandwicheffect->Initialize();
}

void NormalBlock::ChangeStagePos(short yIndexNum, short xIndexNum)
{
	m_StageIndexData.m_YNum = yIndexNum;
	m_StageIndexData.m_XNum = xIndexNum;

	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize + (m_StageChipSize / 2);

	m_pSandwicheffect->ChangeStagePos(m_Pos);
}

void NormalBlock::ProcessCollision(const CollisionManager::CollisionData& rData)
{
	// 処理なし
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void NormalBlock::Run(void)
{
	HandleEvent();

	if(m_HasBeenSandwiched)
	{	
		m_pSandwicheffect->Control();
	}
}

void NormalBlock::Render(void)
{
	m_pLibrary->Draw2D( m_DrawingID, (m_Pos - m_BasePointPos));

	if(m_HasBeenSandwiched)
	{
		m_pSandwicheffect->Draw();
	}
}

void NormalBlock::HandleEvent(void)
{}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
