﻿//==================================================================================================================================//
//!< @file		CollisionManager.cpp
//!< @brief		ar::CollisionManagerクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include <cmath> 
#include "CollisionManager.h"
#include "../StageDataManager.h"
#include "ObjBase/ObjBase.h"

namespace ar
{

/* Unnamed namespace ------------------------------------------------------------------------------------------- */

namespace
{

const short		SwitchOperatingAreaCount = 4;		// スイッチ作動範囲のエリア数

}

/* Public Functions ------------------------------------------------------------------------------------------- */

CollisionManager::CollisionManager(StageDataManager*	pStageDataManager)
	: m_pStageDataManager(pStageDataManager)
{}

CollisionManager::~CollisionManager(void)
{}

void CollisionManager::UpDate(void)
{
	// スイッチ作動範囲が登録されているなら専用の衝突判定を行う
	if(RESULT_FAILED(m_pSwitchOperatingArea.empty()))
	{
		for(auto& pArea : m_pSwitchOperatingArea)
		{
			CheckCollisionSwitchOperatingArea(pArea);
		}
	
		// データをクリアする
		m_pSwitchOperatingArea.clear();
		std::vector<ObjBase*>().swap(m_pSwitchOperatingArea);
	}

	if(m_pStageObj.empty() || m_pPlayer == nullptr)
	{
		return;
	}

	// プレイヤーの衝突判定処理
	for(auto& pStageObj : m_pStageObj)
	{
		CheckCollisionPlayer(pStageObj);
	}

	// データをクリアする
	m_pStageObj.clear();
	std::vector<ObjBase*>().swap(m_pStageObj);
}

void CollisionManager::SetObjBasePointer(ObjBase* pObj)
{
	m_pStageObj.push_back(pObj);
}

void CollisionManager::SetSwitchOperatingAreaPointer(ObjBase* pArea)
{
	m_pSwitchOperatingArea.push_back(pArea);
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void CollisionManager::CheckCollisionPlayer(ObjBase* pObj)
{
	if(CheckCollisionRect(m_pPlayer, pObj))
	{	
		CollisionData playerCollisionData;
		playerCollisionData.m_ObjType	= pObj->GetTypeID();
		playerCollisionData.m_ObjPos	= pObj->GetPos();
		playerCollisionData.m_ObjRect	= pObj->GetCurrentRectData();
		m_pPlayer->ProcessCollision(playerCollisionData);

		CollisionData objCollisionData;
		objCollisionData.m_ObjType	= m_pPlayer->GetTypeID();
		objCollisionData.m_ObjPos	= m_pPlayer->GetPos();
		objCollisionData.m_ObjRect	= m_pPlayer->GetCurrentRectData();
		pObj->ProcessCollision(objCollisionData);
	}
}

void CollisionManager::CheckCollisionSwitchOperatingArea(ObjBase* pArea)
{
	Stage::INDEX_DATA areaIndex = pArea->GetStageIndex();
	short stageHeightChipNum = m_pStageDataManager->GetStageHeightChipNum();
	short stageWidthChipNum = m_pStageDataManager->GetStageWidthChipNum();

	// エリアの衝突判定を行う範囲(インデックスを求める)
	// それぞれ1で補正しているのは、配列内側だけチェックしたい為
	Stage::INDEX_DATA chechStartIndex;			// チェック開始インデックス
	chechStartIndex.m_YNum = ((areaIndex.m_YNum - SwitchOperatingAreaCount) > 0) ? (areaIndex.m_YNum - SwitchOperatingAreaCount) : 1;
	chechStartIndex.m_XNum = ((areaIndex.m_XNum - SwitchOperatingAreaCount) > 0) ? (areaIndex.m_XNum - SwitchOperatingAreaCount) : 1;

	Stage::INDEX_DATA chechEndIndex;			// チェック終了インデックス
	chechEndIndex.m_YNum = ((areaIndex.m_YNum + SwitchOperatingAreaCount) < stageHeightChipNum) ? (areaIndex.m_YNum + SwitchOperatingAreaCount) : (stageHeightChipNum - 1);
	chechEndIndex.m_XNum = ((areaIndex.m_XNum + SwitchOperatingAreaCount) < stageWidthChipNum) ? (areaIndex.m_XNum + SwitchOperatingAreaCount) : (stageWidthChipNum - 1);

	// エリア内のObjBaseとの衝突をチェックする
	for(int yNum = chechStartIndex.m_YNum ; yNum <= chechEndIndex.m_YNum; ++yNum)
	{
		for(int xNum = chechStartIndex.m_XNum; xNum <= chechEndIndex.m_XNum; ++xNum)
		{
			ObjBase* pObj = m_pStageDataManager->GetObjBasePointer(yNum, xNum);
			if(pObj == nullptr)
			{
				continue;
			}

			// 衝突データを渡す。ただしタイプIDだけ渡せばOK
			CollisionData objCollisionData;
			objCollisionData.m_ObjType	= pArea->GetTypeID();
			pObj->ProcessCollision(objCollisionData);
		}
	}
}

bool CollisionManager::CheckCollisionRect(ObjBase* pObjA, ObjBase* pObjB)
{
	sl::fRect objARect = pObjA->GetCurrentRectData();
	sl::fRect objBRect = pObjB->GetCurrentRectData();

	if(objARect.m_Right > objBRect.m_Left
		&& objARect.m_Top < objBRect.m_Bottom
		&& objARect.m_Left < objBRect.m_Right
		&& objARect.m_Bottom > objBRect.m_Top)
	{
		return true;
	}

	return false;
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
