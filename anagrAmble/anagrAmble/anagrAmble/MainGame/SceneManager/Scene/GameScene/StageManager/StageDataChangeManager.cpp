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

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const int WhiteOutTime = 40;			// ホワイトアウト処理の時間

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
	if(m_pPlayer->GetStageIndex().m_XIndexNum > m_SandwichedSpaceStartIndex.m_XIndexNum
		&& m_pPlayer->GetStageIndex().m_XIndexNum < m_SandwichedSpaceEndIndex.m_XIndexNum)
	{
		return false;
	}

	// 現在のデータをストックデータにセットする
	m_pStageDataManager->AddStockStageData();
	
	std::vector<std::vector<ChangeData>> changingStageData;		// 交換するステージデータ

	// それぞれの幅を求める。ｙのIndexは引くと1少なくなるため +1しておく
	short changeSpaceXCount = (m_SandwichedSpaceEndIndex.m_XIndexNum - m_SandwichedSpaceStartIndex.m_XIndexNum);
	short changeSpaceYCount = (m_SandwichedSpaceEndIndex.m_YIndexNum - m_SandwichedSpaceStartIndex.m_YIndexNum) + 1;

	changingStageData.resize(changeSpaceYCount);
	for(auto& changingStageDataY : changingStageData)
	{
		changingStageDataY.resize(changeSpaceXCount);
	}

	// 入れ替えたい部分(プレイヤーの向いている方面の空間)の開始インデックスを計算する
	Stage::INDEX_DATA		changeStartIndexData = CalculateChangeStartIndex();	

	if(m_pPlayer->IsFacingRight())
	{
		if((changeStartIndexData.m_XIndexNum + changeSpaceXCount) > (m_pStageDataManager->GetStageWidthChipCount() - 1))
		{	// インデックスがステージに範囲(1番端の壁の向こう)を超えるなら入れ替えできない
			return false;
		}

		// 入れ替え用の入れ物に入れ替えたい空間のインデックスデータをつめる
		for(short yIndexNum = changeStartIndexData.m_YIndexNum; yIndexNum <= m_SandwichedSpaceEndIndex.m_YIndexNum; ++yIndexNum)
		{
			for(short xIndexNum = changeStartIndexData.m_XIndexNum; xIndexNum < (changeStartIndexData.m_XIndexNum + changeSpaceXCount); ++xIndexNum)
			{
				short currentYIndexNum = yIndexNum - changeStartIndexData.m_YIndexNum;
				short currentXIndexNum = xIndexNum - changeStartIndexData.m_XIndexNum;

				changingStageData[currentYIndexNum][currentXIndexNum].m_XIndexNum = xIndexNum;
				changingStageData[currentYIndexNum][currentXIndexNum].m_YIndexNum = yIndexNum;
				changingStageData[currentYIndexNum][currentXIndexNum].m_pObj = m_pStageDataManager->GetObjBasePointer(yIndexNum, xIndexNum);
				m_pStageDataManager->SetCurrentStageChipData(yIndexNum, xIndexNum);
			}
		}

		ChangeStageData(changeSpaceYCount, changeSpaceXCount, changeStartIndexData, changingStageData);
	}
	else
	{
		if((changeStartIndexData.m_XIndexNum - changeSpaceXCount) < 1 )
		{	// インデックスがステージに範囲を超えるなら入れ替えできない
			return false;
		}

		// 入れ替え用の入れ物に入れ替えたい空間のデータをつめる.左を向いているため逆からつめる
		for(short yIndexNum = changeStartIndexData.m_YIndexNum; yIndexNum <= m_SandwichedSpaceEndIndex.m_YIndexNum; ++yIndexNum)
		{
			for(short xIndexNum = (changeStartIndexData.m_XIndexNum - changeSpaceXCount); xIndexNum < changeStartIndexData.m_XIndexNum; ++xIndexNum)
			{
				short currentYIndexNum = yIndexNum - changeStartIndexData.m_YIndexNum;
				short currentXIndexNum = xIndexNum - (changeStartIndexData.m_XIndexNum - changeSpaceXCount);

				changingStageData[currentYIndexNum][currentXIndexNum].m_XIndexNum = xIndexNum;
				changingStageData[currentYIndexNum][currentXIndexNum].m_YIndexNum = yIndexNum;
				changingStageData[currentYIndexNum][currentXIndexNum].m_pObj = m_pStageDataManager->GetObjBasePointer(yIndexNum, xIndexNum);
				m_pStageDataManager->SetCurrentStageChipData(yIndexNum, xIndexNum);
			}
		}

		changeStartIndexData.m_XIndexNum = (changeStartIndexData.m_XIndexNum - changeSpaceXCount);
		ChangeStageData(changeSpaceYCount, changeSpaceXCount, changeStartIndexData, changingStageData);
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
		m_pStageDataManager->ReturnmRespawnStageData();
		m_WhiteOutTimeCount = 0;
		return true;
	}

	++m_WhiteOutTimeCount;
	return false;
}

/* Private Functions ------------------------------------------------------------------------------------------ */

Stage::INDEX_DATA StageDataChangeManager::CalculateChangeStartIndex(void)
{
	Stage::INDEX_DATA changeIndexData;
	if(m_pPlayer->IsFacingRight())
	{
		// プレイヤーの左端がプレイヤーがいるステージチップの左端より大きい場合は、
		// 2マス右にオブジェクトを移動させ、それ以外は1マス右に移動させる
		if(m_pPlayer->GetCurrentRectData().m_Left >(m_pPlayer->GetStageIndex().m_XIndexNum * m_StageMapChipSize))
		{
			changeIndexData.m_XIndexNum = m_pPlayer->GetStageIndex().m_XIndexNum + 2;
		}
		else
		{
			changeIndexData.m_XIndexNum = m_pPlayer->GetStageIndex().m_XIndexNum + 1;
		}
		changeIndexData.m_YIndexNum = m_SandwichedSpaceStartIndex.m_YIndexNum;
	}
	else
	{
		// プレイヤーの右端がプレイヤーがいるステージチップの右端より小さい場合は、
		// 2マス左にオブジェクトを移動させ、それ以外は1マス左に移動させる
		if(m_pPlayer->GetCurrentRectData().m_Right < (m_pPlayer->GetStageIndex().m_XIndexNum * m_StageMapChipSize))
		{
			changeIndexData.m_XIndexNum = m_pPlayer->GetStageIndex().m_XIndexNum - 2;
		}
		else
		{
			changeIndexData.m_XIndexNum = m_pPlayer->GetStageIndex().m_XIndexNum - 1;
		}
		changeIndexData.m_YIndexNum = m_SandwichedSpaceStartIndex.m_YIndexNum;
	}

	return changeIndexData;
}

void StageDataChangeManager::ChangeStageData(short changeSpaceYCount
											, short changeSpaceXCount
											, Stage::INDEX_DATA& rChangeStartIndexData
											, std::vector<std::vector<ChangeData>>& rChangingStageData)
{
	// 入れ替えたい空間に挟んだ空間のデータをいれる
	for(short yIndexNum = m_SandwichedSpaceStartIndex.m_YIndexNum; yIndexNum <= m_SandwichedSpaceEndIndex.m_YIndexNum; ++yIndexNum)
	{
		for(short xIndexNum = 0; xIndexNum < changeSpaceXCount; ++xIndexNum)
		{
			ObjBase* pObj = m_pStageDataManager->GetObjBasePointer(yIndexNum, (m_SandwichedSpaceStartIndex.m_XIndexNum + xIndexNum));

			if(pObj == nullptr)
			{
				continue;
			}

			if(pObj->GetTypeID() == ObjBase::LIGHT_B)
			{	// 光ブロックの場合は入れ替えないので、データを消しおく
				pObj->DetachSandwichEffect();
				m_pStageDataManager->SetCurrentStageChipData(yIndexNum, xIndexNum);
				continue;
			}

			pObj->DetachSandwichEffect();		// オブジェクトの挟む効果をきる

			m_pStageDataManager->SetCurrentStageChipData(yIndexNum, (m_SandwichedSpaceStartIndex.m_XIndexNum + xIndexNum));
			pObj->ChangeStagePos(yIndexNum, (rChangeStartIndexData.m_XIndexNum + xIndexNum));
			m_pStageDataManager->SetCurrentStageChipData(yIndexNum, (rChangeStartIndexData.m_XIndexNum + xIndexNum), pObj);
		}
	}

	// 1番上の列のデータ(状態)を変更する
	ChangeTopRowData(changeSpaceXCount, rChangeStartIndexData.m_XIndexNum);
	
	// 1番下の列のデータ(状態)を変更する
	ChangeBottomRowData(changeSpaceXCount, rChangeStartIndexData.m_XIndexNum);

	// 挟んだ空間内に入れ替え用に入れておいたデータを適用する
	for(short yIndexNum = 0; yIndexNum < changeSpaceYCount; ++yIndexNum)
	{
		for(short xIndexNum = 0; xIndexNum < changeSpaceXCount; ++xIndexNum)
		{
			ObjBase* pObj = rChangingStageData[yIndexNum][xIndexNum].m_pObj;
			if(pObj == nullptr)
			{
				continue;
			}

			if(pObj->GetTypeID() == ObjBase::LIGHT_B)
			{	// 光ブロックの場合は入れ替えないので、データを消しおく
				pObj->DetachSandwichEffect();
				m_pStageDataManager->SetCurrentStageChipData(yIndexNum, xIndexNum);
				continue;
			}

			pObj->ChangeStagePos(rChangingStageData[yIndexNum][xIndexNum].m_YIndexNum, (m_SandwichedSpaceStartIndex.m_XIndexNum + xIndexNum));
			m_pStageDataManager->SetCurrentStageChipData(rChangingStageData[yIndexNum][xIndexNum].m_YIndexNum, (m_SandwichedSpaceStartIndex.m_XIndexNum + xIndexNum), pObj);
		}
	}

	// 1番上の列のデータ(状態)を変更する
	ChangeTopRowData(changeSpaceXCount, m_SandwichedSpaceStartIndex.m_XIndexNum);
	
	// 1番下の列のデータ(状態)を変更する
	ChangeBottomRowData(changeSpaceXCount, m_SandwichedSpaceStartIndex.m_XIndexNum);
}

void StageDataChangeManager::ChangeTopRowData(short changeSpaceXCount, short startIndexXNum)
{
	for(short xIndexNum = 0; xIndexNum < changeSpaceXCount; ++xIndexNum)
	{
		ObjBase* pObj = m_pStageDataManager->GetObjBasePointer(0, (startIndexXNum + xIndexNum));

		if(pObj == nullptr)
		{
			continue;
		}

		pObj->ChangeStagePos(0, (startIndexXNum + xIndexNum));
	}
}

void StageDataChangeManager::ChangeBottomRowData(short changeSpaceXCount, short startIndexXNum)
{
	for(short xIndexNum = 0; xIndexNum < changeSpaceXCount; ++xIndexNum)
	{
		ObjBase* pObj = m_pStageDataManager->GetObjBasePointer((m_pStageDataManager->GetStageHeightChipCount() - 1)
															, (startIndexXNum + xIndexNum));

		if(pObj == nullptr)
		{
			continue;
		}

		pObj->ChangeStagePos((m_pStageDataManager->GetStageHeightChipCount() - 1)
							, (startIndexXNum + xIndexNum));
	}
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
