//==================================================================================================================================//
//!< @file		StageDataChangeManager.cpp
//!< @brief		ar::StageDataChangeManagerクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "StageDataChangeManager.h"
#include "Stage/ObjBase/ObjBase.h"
#include "Stage/ObjBase/Player/Player.h"
#include "StageDataManager.h"

namespace ar
{
/* Unnamed namespace ------------------------------------------------------------------------------------------ */

namespace
{

const int WhiteOutTime = 25;			// ホワイトアウト処理の時間

}

/* Public Functions ------------------------------------------------------------------------------------------- */

void StageDataChangeManager::InitialIze(StageDataManager* pStageDataManager)
{
	m_pStageDataManager = pStageDataManager;
	m_StageMapChipSize = m_pStageDataManager->GetStageChipSize();
	m_WhiteOutTimeCount = 0;
}

bool StageDataChangeManager::ChangeSpace(void)
{
	// 挟んだ空間内にプレイヤーがいるなら入れ替えはしない
	if(m_pPlayer->GetStageIndex().m_XNum > m_SandwichedSpaceStartIndex.m_XNum
		&& m_pPlayer->GetStageIndex().m_XNum < m_SandwichedSpaceEndIndex.m_XNum)
	{
		return false;
	}

	// 現在のデータをストックデータにセットする
	m_pStageDataManager->AddStockStageData();
	
	// 変数宣言
	std::vector<std::vector<ChangeData>> tmp;		// 交換用の入れ物
	short changeSpaceXNum = (m_SandwichedSpaceEndIndex.m_XNum - m_SandwichedSpaceStartIndex.m_XNum);
	short changeSpaceYNum = (m_SandwichedSpaceEndIndex.m_YNum - m_SandwichedSpaceStartIndex.m_YNum) + 1;

	// 入れ物のresizeを行う
	tmp.resize(changeSpaceYNum);
	for(auto& tmpY : tmp)
	{
		tmpY.resize(changeSpaceXNum);
	}

	// 入れ替えたい部分(プレイヤーの向いている方面の空間)の開始インデックスを取得する
	Stage::INDEX_DATA		changeStartIndexData = CalculateChangeStartIndex();	

	if(m_pPlayer->IsFacingRight())
	{
		if((changeStartIndexData.m_XNum + changeSpaceXNum) > (m_pStageDataManager->GetStageWidthChipNum() - 2))
		{	// インデックスがステージに範囲(1番端の壁の向こう)を超えるなら入れ替えできない
			return false;
		}

		// 入れ替え用の入れ物に入れ替えたい空間のインデックスデータをつめる
		for(short yNum = changeStartIndexData.m_YNum; yNum <= m_SandwichedSpaceEndIndex.m_YNum; ++yNum)
		{
			for(short xNum = changeStartIndexData.m_XNum; xNum < (changeStartIndexData.m_XNum + changeSpaceXNum); ++xNum)
			{
				tmp[(yNum - changeStartIndexData.m_YNum)][(xNum - changeStartIndexData.m_XNum)].m_XNum = xNum;
				tmp[(yNum - changeStartIndexData.m_YNum)][(xNum - changeStartIndexData.m_XNum)].m_YNum = yNum;
				tmp[(yNum - changeStartIndexData.m_YNum)][(xNum - changeStartIndexData.m_XNum)].m_pObj = m_pStageDataManager->GetObjBasePointer(yNum, xNum);
				m_pStageDataManager->SetCurrentStageChipData(yNum, xNum);
			}
		}

		// 入れ替えたい空間に挟んだ空間のデータをいれる
		for(short yNum = m_SandwichedSpaceStartIndex.m_YNum; yNum <= m_SandwichedSpaceEndIndex.m_YNum; ++yNum)
		{
			for(short xNum = 0; xNum < changeSpaceXNum; ++xNum)
			{
				ObjBase* pObj = m_pStageDataManager->GetObjBasePointer(yNum, (m_SandwichedSpaceStartIndex.m_XNum + xNum));
				if(pObj == nullptr)
				{
					continue;
				}
				m_pStageDataManager->SetCurrentStageChipData(yNum, (m_SandwichedSpaceStartIndex.m_XNum + xNum));
				pObj->ChangeStagePos(yNum, (changeStartIndexData.m_XNum + xNum));
				m_pStageDataManager->SetCurrentStageChipData(yNum, (changeStartIndexData.m_XNum + xNum), pObj);
			}
		}

		// 挟んだ空間内に入れ替え用に入れておいたデータを適用する
		for(short yNum = 0; yNum < changeSpaceYNum; ++yNum)
		{
			for(short xNum = 0; xNum < changeSpaceXNum; ++xNum)
			{
				ObjBase* pObj = tmp[yNum][xNum].m_pObj;
				if(pObj == nullptr)
				{
					continue;
				}
				pObj->ChangeStagePos(tmp[yNum][xNum].m_YNum, (m_SandwichedSpaceStartIndex.m_XNum + xNum));
				m_pStageDataManager->SetCurrentStageChipData(tmp[yNum][xNum].m_YNum, (m_SandwichedSpaceStartIndex.m_XNum + xNum), pObj);
			}
		}

	}
	else
	{
		if((changeStartIndexData.m_XNum - changeSpaceXNum) < 1 )
		{	// インデックスがステージに範囲を超えるなら入れ替えできない
			return false;
		}

		// 入れ替え用の入れ物に入れ替えたい空間のデータをつめる.左を向いているため逆からつめる
		for(short yNum = changeStartIndexData.m_YNum; yNum <= m_SandwichedSpaceEndIndex.m_YNum; ++yNum)
		{
			for(short xNum = (changeStartIndexData.m_XNum - changeSpaceXNum); xNum < changeStartIndexData.m_XNum; ++xNum)
			{
				tmp[(yNum - changeStartIndexData.m_YNum)][(xNum - (changeStartIndexData.m_XNum - changeSpaceXNum))].m_XNum = xNum;
				tmp[(yNum - changeStartIndexData.m_YNum)][(xNum - (changeStartIndexData.m_XNum - changeSpaceXNum))].m_YNum = yNum;
				tmp[(yNum - changeStartIndexData.m_YNum)][(xNum - (changeStartIndexData.m_XNum - changeSpaceXNum))].m_pObj = m_pStageDataManager->GetObjBasePointer(yNum, xNum);
				m_pStageDataManager->SetCurrentStageChipData(yNum, xNum);
			}
		}

		// 入れ替えたい空間に挟んだ空間のインデックスデータをいれる
		for(short yNum = m_SandwichedSpaceStartIndex.m_YNum; yNum <= m_SandwichedSpaceEndIndex.m_YNum; ++yNum)
		{
			for(short xNum = changeSpaceXNum; xNum > 0; --xNum)
			{
				ObjBase* pObj = m_pStageDataManager->GetObjBasePointer(yNum, (m_SandwichedSpaceEndIndex.m_XNum - xNum));
				if(pObj == nullptr)
				{
					continue;
				}
				m_pStageDataManager->SetCurrentStageChipData(yNum, (m_SandwichedSpaceEndIndex.m_XNum - xNum));
				pObj->ChangeStagePos(yNum, (changeStartIndexData.m_XNum - xNum));
				m_pStageDataManager->SetCurrentStageChipData(yNum, (changeStartIndexData.m_XNum - xNum), pObj);
			}
		}

		// 挟んだ空間内のデータに入れ替え用に入れておいたデータをつめる
		for(short yNum = 0; yNum < changeSpaceYNum; ++yNum)
		{
			for(short xNum = 0; xNum < changeSpaceXNum; ++xNum)
			{
				ObjBase* pObj = tmp[yNum][xNum].m_pObj;
				if(pObj == nullptr)
				{
					continue;
				}
				pObj->ChangeStagePos(tmp[yNum][xNum].m_YNum, (m_SandwichedSpaceStartIndex.m_XNum + xNum));
				m_pStageDataManager->SetCurrentStageChipData(tmp[yNum][xNum].m_YNum, (m_SandwichedSpaceStartIndex.m_XNum + xNum), pObj);
			}
		}
	}

	return true;
}

bool StageDataChangeManager::ReturnChangedSpace(void)
{
	// 少し間をあけてから処理をする(ホワイトアウトさせるため)
	if(m_WhiteOutTimeCount == WhiteOutTime)
	{
		m_pStageDataManager->ReturnStageDataChangeBefore();
		m_WhiteOutTimeCount = 0;
		return true;
	}

	++m_WhiteOutTimeCount;
	return false;
}

bool StageDataChangeManager::ReturnBeforeStageData(void)
{
	// 少し間をあけてから処理をする(ホワイトアウトさせるため)
	if(m_WhiteOutTimeCount == WhiteOutTime)
	{
		m_pStageDataManager->ReturnBeforeStageData();
		m_WhiteOutTimeCount = 0;
		return true;
	}

	++m_WhiteOutTimeCount;
	return false;
}

StageDataChangeManager::~StageDataChangeManager(void)
{}

/* Private Functions ------------------------------------------------------------------------------------------ */

Stage::INDEX_DATA StageDataChangeManager::CalculateChangeStartIndex(void)
{
	Stage::INDEX_DATA changeIndexData;
	if(m_pPlayer->IsFacingRight())
	{
		// プレイヤーの左端がプレイヤーがいるステージチップの左端より大きい場合は、
		// 2マス右にオブジェクトを移動させ、それ以外は1マス右に移動させる
		if(m_pPlayer->GetCurrentRectData().m_Left >(m_pPlayer->GetStageIndex().m_XNum * m_StageMapChipSize))
		{
			changeIndexData.m_XNum = m_pPlayer->GetStageIndex().m_XNum + 2;
		}
		else
		{
			changeIndexData.m_XNum = m_pPlayer->GetStageIndex().m_XNum + 1;
		}
		changeIndexData.m_YNum = m_SandwichedSpaceStartIndex.m_YNum;
	}
	else
	{
		// プレイヤーの右端がプレイヤーがいるステージチップの右端より小さい場合は、
		// 2マス左にオブジェクトを移動させ、それ以外は1マス左に移動させる
		if(m_pPlayer->GetCurrentRectData().m_Right < (m_pPlayer->GetStageIndex().m_XNum * m_StageMapChipSize))
		{
			changeIndexData.m_XNum = m_pPlayer->GetStageIndex().m_XNum - 2;
		}
		else
		{
			changeIndexData.m_XNum = m_pPlayer->GetStageIndex().m_XNum - 1;
		}
		changeIndexData.m_YNum = m_SandwichedSpaceStartIndex.m_YNum;

	}

	return changeIndexData;
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
