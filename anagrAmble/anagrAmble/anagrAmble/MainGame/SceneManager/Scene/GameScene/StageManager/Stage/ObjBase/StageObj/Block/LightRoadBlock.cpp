﻿//==================================================================================================================================//
//!< @file		LightRoadBlock.cpp
//!< @brief		ar::LightRoadBlockクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "LightRoadBlock.h"
#include "LightBlock.h"
#include "../../../../StageDataManager.h"
#include "../../../../../GameEventManager/GameEventManager.h"
#include "../../../../../GameEventManager/EventListener.h"
#include "../../../StageEffect/SandwichEffect.h"

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
	sl::DeleteSafely(&m_pSandwichEffect);
	m_pLibrary->ReleaseVertex2D(m_DrawingID.m_VtxID);
}

void LightRoadBlock::Initialize(void)
{
	m_Pos.x = m_StageIndexData.m_XIndexNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YIndexNum * m_StageChipSize + (m_StageChipSize / 2);

	// 矩形サイズを設定
	m_RectSize.m_Left		= -(m_StageChipSize / 2);
	m_RectSize.m_Top		= -(m_StageChipSize / 2);
	m_RectSize.m_Right		= (m_StageChipSize / 2);
	m_RectSize.m_Bottom		= (m_StageChipSize / 2);

	const sl::fRect		uv = {0.45f, 0.0f, 0.5f, 0.088f};

	m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, uv);

	m_pSandwichEffect = new SandwichEffect(m_Pos, m_RectSize, m_DrawingID, m_StageChipSize);
	m_pSandwichEffect->Initialize();

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

	// 空間入れ替え処理終了イベント
	GameEventManager::Instance().RegisterEventType("space_change_end", m_pEventListener);
	m_pEventListener->RegisterSynEventFunc("space_change_end", std::bind(&ar::LightRoadBlock::DischargeLightBlock, this));

	// 時戻し終了イベント
	GameEventManager::Instance().RegisterEventType("space_change_return_end", m_pEventListener);
	m_pEventListener->RegisterSynEventFunc("space_change_return_end", std::bind(&ar::LightRoadBlock::DischargeLightBlock, this));

	// プレイヤーリスポーン終了イベント
	GameEventManager::Instance().RegisterEventType("player_respawn_end", m_pEventListener);
	m_pEventListener->RegisterSynEventFunc("player_respawn_end", std::bind(&ar::LightRoadBlock::DischargeLightBlock, this));
}

void LightRoadBlock::ChangeStagePos(short yIndexNum, short xIndexNum)
{
	m_StageIndexData.m_YIndexNum = yIndexNum;
	m_StageIndexData.m_XIndexNum = xIndexNum;

	m_Pos.x = m_StageIndexData.m_XIndexNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YIndexNum * m_StageChipSize + (m_StageChipSize / 2);

	for(auto pBlock : m_pLightBlocks)
	{
		pBlock->ChangeStagePos(m_StageIndexData.m_YIndexNum, m_StageIndexData.m_XIndexNum);;
	}

	m_pSandwichEffect->ChangeStagePos(m_Pos);

	DischargeLightBlock();
}

void LightRoadBlock::ProcessCollision(const CollisionManager::CollisionData& rData)
{}

/* Private Functions ------------------------------------------------------------------------------------------ */

void LightRoadBlock::Run(void)
{
	if(m_HasBeenSandwiched)
	{	
		m_pSandwichEffect->Control();
	}

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

	if(m_HasBeenSandwiched)
	{
		m_pSandwichEffect->Draw();
	}
}

void LightRoadBlock::HandleEvent(void)
{}

void LightRoadBlock::DischargeLightBlock(void)
{
	// ブロックの位置に戻す
	for(auto pBlock : m_pLightBlocks)
	{
		pBlock->ChangeStagePos(m_StageIndexData.m_YIndexNum, m_StageIndexData.m_XIndexNum);;
	}

	// チェックしたいY方向のインデックス. 
	// 横のチェックだけなのでここで変数を作成
	int checkYIndexNum = m_StageIndexData.m_YIndexNum;

	// 足場排出ブロックの後方チェック。後方のためインデックスを引きながらチェックしている
	// 2からチェックを開始しているのは、1からだと光ブロックを作成する必要がないため
	for(int xIndexCount = 2 ; xIndexCount <= SearchArea ; ++xIndexCount)
	{
		int checkXIndexNum = m_StageIndexData.m_XIndexNum - xIndexCount;

		if(m_pStageDataManager->GetTypeID(checkYIndexNum, checkXIndexNum) == LIGHT_ROAD_B)
		{
			// 発見したブロックまでの距離に到達するようにブロックを生成する
			// -1しているのはその手前までに光ブロックを作成するため
			int lightBlockCount = xIndexCount -1;		// 光ブロック生成数

			for(int count = 1; count <= lightBlockCount; ++count)
			{
				Stage::INDEX_DATA stageIndexData;
				stageIndexData.m_YIndexNum = m_StageIndexData.m_YIndexNum;
				stageIndexData.m_XIndexNum = m_StageIndexData.m_XIndexNum - count;
				m_pLightBlocks[count - 1]->ChangeStagePos(stageIndexData.m_YIndexNum, stageIndexData.m_XIndexNum);
			}
			break;
		}
	}
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
