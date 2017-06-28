﻿//==================================================================================================================================//
//!< @file		LightBlock.cpp
//!< @brief		ar::LightBlockクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "LightBlock.h"
#include "../../../../StageDataManager.h"
#include "../../../StageEffect/SandwichEffect.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

LightBlock::LightBlock(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
								, const Stage::INDEX_DATA& rStageIndexData, int texID)
	: StageObj(pStageDataManager, pCollisionManager, rStageIndexData)
{
	m_TypeID = LIGHT_B;
	m_DrawingID.m_TexID = texID;
}

LightBlock::~LightBlock(void)
{
	sl::DeleteSafely(&m_pSandwicheffect);
	m_pLibrary->ReleaseVertex2D(m_DrawingID.m_VtxID);
}

void LightBlock::Initialize(void)
{
	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize + (m_StageChipSize / 2);
	
	// ブロックサイズのRect構造体を作成
	m_RectSize.m_Left		= -(m_StageChipSize / 2);
	m_RectSize.m_Top		= -(m_StageChipSize / 2);
	m_RectSize.m_Right		= (m_StageChipSize / 2);
	m_RectSize.m_Bottom		= (m_StageChipSize / 2);

	const sl::fRect		uv = {0.0f, 0.8f, 0.05f, 0.889f};

	m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, uv);

	m_pLibrary->SetVtxColor(m_DrawingID.m_VtxID, 1.0f, 1.0f, 1.0f, 0.8f);

	m_UVAnimeID = m_pLibrary->RegisterUVAnimeID(m_DrawingID.m_VtxID, 11, true);
	m_pLibrary->CreateUVAnimeData(m_DrawingID.m_VtxID, m_UVAnimeID, 11, 0, uv, 5);

	m_pSandwicheffect = new SandwichEffect(m_Pos, m_RectSize, m_DrawingID, m_StageChipSize);
	m_pSandwicheffect->Initialize();
}

void LightBlock::ChangeStagePos(short yIndexNum, short xIndexNum)
{
	DetachSandwichEffect();
	if(m_pStageDataManager->GetObjBasePointer(m_StageIndexData.m_YNum, m_StageIndexData.m_XNum) == this)
	{
		m_pStageDataManager->SetCurrentStageChipData(m_StageIndexData.m_YNum, m_StageIndexData.m_XNum);
	}

	m_StageIndexData.m_YNum = yIndexNum;
	m_StageIndexData.m_XNum = xIndexNum;

	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize + (m_StageChipSize / 2);

	m_pSandwicheffect->ChangeStagePos(m_Pos);

	if(m_pStageDataManager->GetObjBasePointer(m_StageIndexData.m_YNum, m_StageIndexData.m_XNum) == nullptr)
	{
		m_pStageDataManager->SetCurrentStageChipData(m_StageIndexData.m_YNum, m_StageIndexData.m_XNum, this);
	}

	m_pLibrary->SetVtxColor(m_DrawingID.m_VtxID, 1.0f, 1.0f, 1.0f, 0.8f);
}

void LightBlock::ProcessCollision(const CollisionManager::CollisionData& rData)
{}

/* Private Functions ------------------------------------------------------------------------------------------ */

void LightBlock::Run(void)
{
	// アニメーションを更新する
	m_pLibrary->UpdateUVAnime(m_DrawingID.m_VtxID, m_UVAnimeID);
	
	if(m_HasBeenSandwiched)
	{	
		m_pSandwicheffect->Control();
	}
}

void LightBlock::Render(void)
{
	m_pLibrary->Draw2D( m_DrawingID, (m_Pos - m_BasePointPos));

	if(m_HasBeenSandwiched)
	{
		m_pSandwicheffect->Draw();
	}
}

void LightBlock::HandleEvent(void)
{}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
