//==================================================================================================================================//
//!< @file		LightDoor.cpp
//!< @brief		ar::LightDoorクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "LightDoor.h"
#include "../Block/LightBlock.h"
#include "../../../../StageDataManager.h"

namespace ar
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const int SearchArea = 4;			//!< 探査範囲

}

/* Public Functions ------------------------------------------------------------------------------------------- */

LightDoor::LightDoor(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
			, const Stage::INDEX_DATA& rStageIndexData,  int texID,  ObjBase::TYPE_ID typeID)
	: StageObj(pStageDataManager, pCollisionManager, rStageIndexData)
{
	CalculatePos();
	m_TypeID = typeID;

	m_DrawingID.m_TexID = texID;

	// ブロックサイズのRect構造体を作成
	float chipSize = m_pStageDataManager->GetStageChipSize();
	m_RectSize.m_Left		= -(chipSize / 2);
	m_RectSize.m_Top		= -(chipSize / 2);
	m_RectSize.m_Right		= (chipSize / 2);
	m_RectSize.m_Bottom		= (chipSize / 2);

	const sl::fRect		uv = {0.3f, 0.088f, 0.35f, 0.1777f};

	m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, uv);

	m_CurrentRectData.m_Left	= m_Pos.x + m_RectSize.m_Left;
	m_CurrentRectData.m_Top		= m_Pos.y + m_RectSize.m_Top;
	m_CurrentRectData.m_Right	= m_Pos.x + m_RectSize.m_Right;
	m_CurrentRectData.m_Bottom	= m_Pos.y + m_RectSize.m_Bottom;

	CreateLightBlock();

}

LightDoor::~LightDoor(void)
{
	for(auto pblock : m_pLightBlocks)
	{
		sl::DeleteSafely(pblock);
	}
	m_pLibrary->ReleaseVertex2D(m_DrawingID.m_VtxID);
}

void LightDoor::ProcessCollision(const CollisionManager::CollisionData& rData)
{}

/* Private Functions ------------------------------------------------------------------------------------------ */

void LightDoor::Run(void)
{
	for(auto pblock : m_pLightBlocks)
	{
		pblock->Control();
	}
}

void LightDoor::Render(void)
{
	m_pLibrary->Draw2D( m_DrawingID, (m_Pos - m_BasePointPos));
	for(auto pblock : m_pLightBlocks)
	{
		pblock->Draw();
	}
}

void LightDoor::HandleEvent(void)
{}

void LightDoor::CalculatePos(void)
{
	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize + (m_StageChipSize / 2);
}

void LightDoor::CreateLightBlock(void)
{
	Stage::INDEX_DATA checkIndexData;
	switch(m_TypeID)
	{
	case LIGHT_DOOR_UP:
		for(int count = 1; count < SearchArea ; ++count)
		{
			checkIndexData.m_YNum = m_StageIndexData.m_YNum - count;
			checkIndexData.m_XNum = m_StageIndexData.m_XNum;

			if(m_pStageDataManager->GetTypeID(checkIndexData.m_YNum, checkIndexData.m_XNum) == BLANK)
			{	// 何もないならそのスペースに光ブロックを生成する
				m_pLightBlocks.push_back(new LightBlock(m_pStageDataManager, m_pCollisionManager
										, checkIndexData, m_DrawingID.m_TexID));
			}
			else
			{	// 空白じゃないなら生成をやめる
				return;
			}
		}
		break;

	case LIGHT_DOOR_DOWN:
		for(int count = 1; count < SearchArea ; ++count)
		{
			checkIndexData.m_YNum = m_StageIndexData.m_YNum + count;
			checkIndexData.m_XNum = m_StageIndexData.m_XNum;

			if(m_pStageDataManager->GetTypeID(checkIndexData.m_YNum, checkIndexData.m_XNum) == BLANK)
			{	// 空白ならそのスペースに光ブロックを生成する
				m_pLightBlocks.push_back(new LightBlock(m_pStageDataManager, m_pCollisionManager
										, checkIndexData, m_DrawingID.m_TexID));
			}
			else
			{	// 空白じゃないなら生成をやめる
				return;
			}
		}
		break;

	case LIGHT_DOOR_RIGHT:
		for(int count = 1; count < SearchArea ; ++count)
		{
			checkIndexData.m_YNum = m_StageIndexData.m_YNum;
			checkIndexData.m_XNum = m_StageIndexData.m_XNum + count;

			if(m_pStageDataManager->GetTypeID(checkIndexData.m_YNum, checkIndexData.m_XNum) == BLANK)
			{	// 空白ならそのスペースに光ブロックを生成する
				m_pLightBlocks.push_back(new LightBlock(m_pStageDataManager, m_pCollisionManager
										, checkIndexData, m_DrawingID.m_TexID));
			}
			else
			{	// 空白じゃないなら生成をやめる
				return;
			}
		}
		break;

	case LIGHT_DOOR_LEFT:
		for(int count = 1; count < SearchArea ; ++count)
		{
			checkIndexData.m_YNum = m_StageIndexData.m_YNum;
			checkIndexData.m_XNum = m_StageIndexData.m_XNum - count;

			if(m_pStageDataManager->GetTypeID(checkIndexData.m_YNum, checkIndexData.m_XNum) == BLANK)
			{	// 空白ならそのスペースに光ブロックを生成する
				m_pLightBlocks.push_back(new LightBlock(m_pStageDataManager, m_pCollisionManager
										, checkIndexData, m_DrawingID.m_TexID));
			}
			else
			{	// 空白じゃないなら生成をやめる
				return;
			}
		}
		break;

	default:
		// do nothing
		break;
	}
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
