﻿//==================================================================================================================================//
//!< @file		LightRoadBlock.cpp
//!< @brief		ar::LightRoadBlockクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "LightRoadBlock.h"
#include "LightBlock.h"
#include "../../../../StageDataManager.h"

namespace ar
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const int SearchArea = 7;			//!< 足場排出ブロック探査範囲

}

/* Public Functions ------------------------------------------------------------------------------------------- */

LightRoadBlock::LightRoadBlock(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
								, const Stage::INDEX_DATA& rStageIndexData, int texID)
	: StageObj(pStageDataManager, pCollisionManager, rStageIndexData)
{	
	m_TypeID = LIGHT_ROAD_B;
	m_DrawingID.m_TexID = texID;
}

LightRoadBlock::~LightRoadBlock(void)
{
	for(auto pblock : m_pLightBlocks)
	{
		sl::DeleteSafely(&pblock);
	}
	m_pLibrary->ReleaseVertex2D(m_DrawingID.m_VtxID);
}

void LightRoadBlock::Initialize(void)
{
	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize + (m_StageChipSize / 2);

	// ブロックサイズのRect構造体を作成
	m_RectSize.m_Left		= -(m_StageChipSize / 2);
	m_RectSize.m_Top		= -(m_StageChipSize / 2);
	m_RectSize.m_Right		= (m_StageChipSize / 2);
	m_RectSize.m_Bottom		= (m_StageChipSize / 2);

	const sl::fRect		uv = {0.45f, 0.0f, 0.5f, 0.088f};

	m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, uv);

	// 光ブロック生成 探査範囲部分をカバーできる分だけ作成する
	for(int count = 0; count < SearchArea; ++count)
	{
		m_pLightBlocks.push_back(new LightBlock(m_pStageDataManager, m_pCollisionManager
												, m_StageIndexData, m_DrawingID.m_TexID));
	}

	for(auto pBlock : m_pLightBlocks)
	{
		pBlock->Initialize();
	}

	DischargeLightBlock();
}

void LightRoadBlock::ChangeStagePos(short yIndexNum, short xIndexNum)
{
	m_StageIndexData.m_YNum = yIndexNum;
	m_StageIndexData.m_XNum = xIndexNum;

	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize + (m_StageChipSize / 2);

	for(auto pBlock : m_pLightBlocks)
	{
		pBlock->ChangeStagePos(m_StageIndexData.m_YNum, m_StageIndexData.m_XNum);;
	}

	DischargeLightBlock();
}

void LightRoadBlock::ProcessCollision(const CollisionManager::CollisionData& rData)
{}

/* Private Functions ------------------------------------------------------------------------------------------ */

void LightRoadBlock::Run(void)
{
	for(auto pblock : m_pLightBlocks)
	{
		pblock->Control();
	}
}

void LightRoadBlock::Render(void)
{
	for(auto pblock : m_pLightBlocks)
	{
		pblock->Draw();
	}
	m_pLibrary->Draw2D( m_DrawingID, (m_Pos - m_BasePointPos));
}

void LightRoadBlock::HandleEvent(void)
{}

void LightRoadBlock::DischargeLightBlock(void)
{
	// チェックしたいY方向のインデックス. 
	// 横のチェックだけなのでここで変数を作成
	int checkIndexY = m_StageIndexData.m_YNum;

	// 足場排出ブロックの後方チェック。後方のためインデックスを引きながらチェックしている
	// 2からチェックを開始しているのは、1からだと光ブロックを作成する必要がないため
	for(int indexX = 2 ; indexX <= SearchArea ; ++indexX)
	{
		int checkIndexX = m_StageIndexData.m_XNum - indexX;

		if(m_pStageDataManager->GetTypeID(checkIndexY, checkIndexX) == LIGHT_ROAD_B)
		{
			// 発見したブロックまでの距離に到達するようにブロックを生成する
			// -1しているのはその手前までに光ブロックを作成するため
			int lightBlockCount = indexX -1;		// 光ブロック生成数

			for(int count = 1; count <= lightBlockCount; ++count)
			{
				Stage::INDEX_DATA stageIndexData;
				stageIndexData.m_YNum = m_StageIndexData.m_YNum;
				stageIndexData.m_XNum = m_StageIndexData.m_XNum - count;
				m_pLightBlocks[count - 1]->ChangeStagePos(stageIndexData.m_YNum, stageIndexData.m_XNum);
			}
			break;
		}
	}
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
