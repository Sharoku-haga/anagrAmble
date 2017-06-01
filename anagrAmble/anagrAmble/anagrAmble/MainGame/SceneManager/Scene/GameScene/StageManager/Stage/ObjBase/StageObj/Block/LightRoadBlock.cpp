//==================================================================================================================================//
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
	CalculatePos();
	m_TypeID = LIGHT_ROAD_B;

	m_DrawingID.m_TexID = texID;

	// ブロックサイズのRect構造体を作成
	float chipSize = m_pStageDataManager->GetStageChipSize();
	m_RectSize.m_Left		= -(chipSize / 2);
	m_RectSize.m_Top		= -(chipSize / 2);
	m_RectSize.m_Right		= (chipSize / 2);
	m_RectSize.m_Bottom		= (chipSize / 2);

	const sl::fRect		uv = {0.15f, 0.1777f, 0.2f, 0.264f};

	m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, uv);

	m_CurrentRectData.m_Left	= m_Pos.x + m_RectSize.m_Left;
	m_CurrentRectData.m_Top		= m_Pos.y + m_RectSize.m_Top;
	m_CurrentRectData.m_Right	= m_Pos.x + m_RectSize.m_Right;
	m_CurrentRectData.m_Bottom	= m_Pos.y + m_RectSize.m_Bottom;

	// 光ブロック生成
	CreateLightBlock();
}

LightRoadBlock::~LightRoadBlock(void)
{
	for(auto pblock : m_pLightBlock)
	{
		sl::DeleteSafely(pblock);
	}
	m_pLibrary->ReleaseVertex2D(m_DrawingID.m_VtxID);
}

void LightRoadBlock::ProcessCollision(int typeID, bool isDeath)
{}

/* Private Functions ------------------------------------------------------------------------------------------ */

void LightRoadBlock::Run(void)
{}

void LightRoadBlock::Render(void)
{
	m_pLibrary->Draw2D( m_DrawingID, (m_Pos - m_BasePointPos));
	for(auto pblock : m_pLightBlock)
	{
		pblock->Draw();
	}
}

void LightRoadBlock::HandleEvent(void)
{}

void LightRoadBlock::CalculatePos(void)
{
	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize + (m_StageChipSize / 2);
}

void LightRoadBlock::CreateLightBlock(void)
{
	// チェックしたいY方向のインデックス. 
	// 横のチェックだけなのでここで変数を作成
	int checkIndexY = m_StageIndexData.m_YNum;

	// 足場排出ブロックの後方チェック。後方のためインデックスを引きながらチェックしている
	// 2からチェックを開始しているのは、1からだと光ブロックを作成する必要がないため
	for(int indexX = 2 ; indexX < SearchArea ; ++indexX)
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

				m_pLightBlock.push_back(new LightBlock(m_pStageDataManager, m_pCollisionManager
										, stageIndexData, m_DrawingID.m_TexID));
			}
			break;
		}
	}
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
