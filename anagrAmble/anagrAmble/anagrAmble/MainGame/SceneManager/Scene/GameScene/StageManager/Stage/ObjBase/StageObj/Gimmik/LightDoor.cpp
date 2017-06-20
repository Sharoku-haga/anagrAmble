﻿//==================================================================================================================================//
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

const int LightBlockCount = 3;			//!< 光ブロックの数(ドアの長さ分)

}

/* Public Functions ------------------------------------------------------------------------------------------- */

LightDoor::LightDoor(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
	, const Stage::INDEX_DATA& rStageIndexData, int texID, ObjBase::TYPE_ID typeID)
	: StageObj(pStageDataManager, pCollisionManager, rStageIndexData)
	, m_HasOpened(false)
{
	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize + (m_StageChipSize / 2);

	m_TypeID = typeID;

	m_DrawingID.m_TexID = texID;

	// ブロックサイズのRect構造体を作成
	m_RectSize.m_Left = -(m_StageChipSize / 2);
	m_RectSize.m_Top = -(m_StageChipSize / 2);
	m_RectSize.m_Right = (m_StageChipSize / 2);
	m_RectSize.m_Bottom = (m_StageChipSize / 2);

	const sl::fRect		uv = { 0.55f, 0.0f, 0.6f, 0.088f };

	m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, uv);

	// 光ブロックを生成する
	for(int count = 0; count < LightBlockCount; ++count)
	{
		m_pLightBlocks.push_back(new LightBlock(m_pStageDataManager, m_pCollisionManager
			, m_StageIndexData, m_DrawingID.m_TexID));
	}

	// 扉を閉じる
	Close();
}

LightDoor::~LightDoor(void)
{
	for(auto& pblock : m_pLightBlocks)
	{
		sl::DeleteSafely(pblock);
	}
	m_pLibrary->ReleaseVertex2D(m_DrawingID.m_VtxID);
}

void  LightDoor::ChangeStagePos(short yIndexNum, short xIndexNum)
{
	m_StageIndexData.m_YNum = yIndexNum;
	m_StageIndexData.m_XNum = xIndexNum;

	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize + (m_StageChipSize / 2);

	Close();
}

void LightDoor::ProcessCollision(const CollisionManager::CollisionData& rData)
{
	// スイッチONなら扉を開け、OFFなら閉める
	switch(rData.m_ObjType)
	{

	case SWITCH_OPERATING_AREA_ON:
		Open();
		break;

	case SWITCH_OPERATING_AREA_OFF:
		Close();
		break;

	default:
		// do nothing
		break;
	}
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void LightDoor::Run(void)
{
	// 開いているなら光ブロックの処理を飛ばす
	if(m_HasOpened)
	{
		return;
	}

	for(auto& pblock : m_pLightBlocks)
	{
		pblock->Control();
	}
}

void LightDoor::Render(void)
{
	// 開いているなら光ブロックの処理を飛ばす
	if(RESULT_FAILED(m_HasOpened))
	{
		for(auto& pblock : m_pLightBlocks)
		{
			pblock->Draw();
		}
	}

	m_pLibrary->Draw2D(m_DrawingID, (m_Pos - m_BasePointPos));
}

void LightDoor::HandleEvent(void)
{}

void LightDoor::Open(void)
{
	m_HasOpened = true;
	for(auto& pblock : m_pLightBlocks)
	{
		pblock->ChangeStagePos(m_StageIndexData.m_YNum, m_StageIndexData.m_XNum);
	}
}

void LightDoor::Close(void)
{
	m_HasOpened = false;
	Stage::INDEX_DATA checkIndexData;

	// 扉の種類にあわせて光ブロックを展開していく
	switch(m_TypeID)
	{
	case LIGHT_DOOR_UP:
		for(int count = 1; count <= LightBlockCount; ++count)
		{
			checkIndexData.m_YNum = m_StageIndexData.m_YNum - count;
			checkIndexData.m_XNum = m_StageIndexData.m_XNum;

			if(m_pStageDataManager->GetTypeID(checkIndexData.m_YNum, checkIndexData.m_XNum) == BLANK)
			{
				m_pLightBlocks[(count - 1)]->ChangeStagePos(checkIndexData.m_YNum, checkIndexData.m_XNum);
			}
			else
			{	// 空白じゃないなら再配置をやめる
				return;
			}
		}
		break;

	case LIGHT_DOOR_DOWN:
		for(int count = 1; count <= LightBlockCount; ++count)
		{
			checkIndexData.m_YNum = m_StageIndexData.m_YNum + count;
			checkIndexData.m_XNum = m_StageIndexData.m_XNum;

			if(m_pStageDataManager->GetTypeID(checkIndexData.m_YNum, checkIndexData.m_XNum) == BLANK)
			{
				m_pLightBlocks[(count - 1)]->ChangeStagePos(checkIndexData.m_YNum, checkIndexData.m_XNum);
			}
			else
			{	// 空白じゃないなら再配置をやめる
				return;
			}
		}
		break;

	case LIGHT_DOOR_RIGHT:
		for(int count = 1; count <= LightBlockCount; ++count)
		{
			checkIndexData.m_YNum = m_StageIndexData.m_YNum;
			checkIndexData.m_XNum = m_StageIndexData.m_XNum + count;

			if(m_pStageDataManager->GetTypeID(checkIndexData.m_YNum, checkIndexData.m_XNum) == BLANK)
			{
				m_pLightBlocks[(count - 1)]->ChangeStagePos(checkIndexData.m_YNum, checkIndexData.m_XNum);
			}
			else
			{	// 空白じゃないなら再配置をやめる
				return;
			}
		}
		break;

	case LIGHT_DOOR_LEFT:
		for(int count = 1; count <= LightBlockCount; ++count)
		{
			checkIndexData.m_YNum = m_StageIndexData.m_YNum;
			checkIndexData.m_XNum = m_StageIndexData.m_XNum - count;
			if(m_pStageDataManager->GetTypeID(checkIndexData.m_YNum, checkIndexData.m_XNum) == BLANK)
			{
				m_pLightBlocks[(count - 1)]->ChangeStagePos(checkIndexData.m_YNum, checkIndexData.m_XNum);
			}
			else
			{	// 空白じゃないなら再配置をやめる
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
