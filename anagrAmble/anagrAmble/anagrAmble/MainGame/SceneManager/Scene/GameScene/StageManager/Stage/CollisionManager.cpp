//==================================================================================================================================//
//!< @file		CollisionManager.cpp
//!< @brief		ar::CollisionManagerクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include <cmath> 
#include "CollisionManager.h"
#include "../StageDataManager.h"
#include "ObjBase/ObjBase.h"
#include "ObjBase/Player/Player.h"

namespace ar
{

/* Unnamed namespace ------------------------------------------------------------------------------------------- */

namespace
{

const short		SwitchOperatingAreaCount	= 4;		// スイッチ作動範囲のエリア数

}

/* Public Functions ------------------------------------------------------------------------------------------- */

CollisionManager::CollisionManager(StageDataManager*	pStageDataManager)
	: m_pStageDataManager(pStageDataManager)
{}

void CollisionManager::Update(void)
{
	// スイッチ作動範囲が登録されているなら専用の衝突判定を行う
	// まずOFF状態からチェックし、その後にON状態をチェックする
	if(RESULT_FAILED(m_SwitchOperatingAreaOffData.empty())
		|| RESULT_FAILED(m_SwitchOperatingAreaOnData.empty()))
	{
		for(auto& AreaData : m_SwitchOperatingAreaOffData)
		{
			CheckCollisionSwitchOperatingArea(AreaData);
		}

		m_SwitchOperatingAreaOffData.clear();
		std::vector<SwitchOperatingAreaData>().swap(m_SwitchOperatingAreaOffData);

		for(auto& AreaData : m_SwitchOperatingAreaOnData)
		{
			CheckCollisionSwitchOperatingArea(AreaData);
		}
	
		m_SwitchOperatingAreaOnData.clear();
		std::vector<SwitchOperatingAreaData>().swap(m_SwitchOperatingAreaOnData);

	}

	if(m_pStageObj.empty() || m_pPlayer == nullptr)
	{
		return;
	}

	// プレイヤーの衝突判定処理
	if(m_pPlayer->IsFacingRight())
	{
		for(unsigned int i = 0; i < m_pStageObj.size() ; ++i)
		{
			CheckCollisionPlayer(m_pStageObj[i]);
		}
	}
	else
	{
		unsigned int count = 0;
		count = (m_pStageObj.size() - 1);
		for(int i = count; i >= 0  ; --i)
		{
			CheckCollisionPlayer(m_pStageObj[i]);
		}
	}

	// データをクリアする
	m_pStageObj.clear();
	std::vector<ObjBase*>().swap(m_pStageObj);
}

void CollisionManager::SetObjBasePointer(ObjBase* pObj)
{
	m_pStageObj.push_back(pObj);
}

void CollisionManager::SetSwitchOperatingAreaOffData(ObjBase* pArea)
{
	m_SwitchOperatingAreaOffData.emplace_back(pArea->GetStageIndex().m_YIndexNum
											, pArea->GetStageIndex().m_XIndexNum
											, pArea->GetTypeID());
}

void CollisionManager::SetSwitchOperatingAreaOnData(ObjBase* pArea)
{
	m_SwitchOperatingAreaOffData.emplace_back(pArea->GetStageIndex().m_YIndexNum
											, pArea->GetStageIndex().m_XIndexNum
											, pArea->GetTypeID());
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void CollisionManager::CheckCollisionPlayer(ObjBase* pObj)
{

	if(CheckRectCollision(m_pPlayer, pObj))
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

void CollisionManager::CheckCollisionSwitchOperatingArea(const SwitchOperatingAreaData& rArea)
{
	short stageHeightChipNum = m_pStageDataManager->GetStageHeightChipCount();
	short stageWidthChipNum = m_pStageDataManager->GetStageWidthChipCount();

	// エリアの衝突判定を行う範囲(インデックスを求める)
	// それぞれ1で補正しているのは、配列内側だけチェックしたい為
	Stage::INDEX_DATA chechStartIndex;			// チェック開始インデックス
	chechStartIndex.m_YIndexNum = ((rArea.m_YIndexNum - SwitchOperatingAreaCount) > 0) ? (rArea.m_YIndexNum - SwitchOperatingAreaCount) : 1;
	chechStartIndex.m_XIndexNum = ((rArea.m_XIndexNum - SwitchOperatingAreaCount) > 0) ? (rArea.m_XIndexNum - SwitchOperatingAreaCount) : 1;

	Stage::INDEX_DATA chechEndIndex;			// チェック終了インデックス
	chechEndIndex.m_YIndexNum = ((rArea.m_YIndexNum + SwitchOperatingAreaCount) < stageHeightChipNum) ? (rArea.m_YIndexNum + SwitchOperatingAreaCount) : (stageHeightChipNum - 1);
	chechEndIndex.m_XIndexNum = ((rArea.m_XIndexNum + SwitchOperatingAreaCount) < stageWidthChipNum) ? (rArea.m_XIndexNum + SwitchOperatingAreaCount) : (stageWidthChipNum - 1);

	// エリア内のObjBaseとの衝突をチェックする
	for(int yIndexNum = chechStartIndex.m_YIndexNum ; yIndexNum <= chechEndIndex.m_YIndexNum; ++yIndexNum)
	{
		for(int xIndexNum = chechStartIndex.m_XIndexNum; xIndexNum <= chechEndIndex.m_XIndexNum; ++xIndexNum)
		{
			ObjBase* pObj = m_pStageDataManager->GetObjBasePointer(yIndexNum, xIndexNum);
			if(pObj == nullptr)
			{
				continue;
			}

			// 衝突データを渡す。ただしタイプIDだけ渡せばOK
			CollisionData objCollisionData;
			objCollisionData.m_ObjType	= rArea.m_TypeID;
			pObj->ProcessCollision(objCollisionData);
		}
	}
}

bool CollisionManager::CheckRectCollision(ObjBase* pObjA, ObjBase* pObjB)
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
