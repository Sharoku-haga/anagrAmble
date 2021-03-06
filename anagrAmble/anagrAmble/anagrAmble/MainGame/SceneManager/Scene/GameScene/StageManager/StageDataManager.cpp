﻿//==================================================================================================================================//
//!< @file		StageDataManager.cpp
//!< @brief		ar::StageDataManagerクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include <algorithm>    
#include <iterator>     
#include "StageDataManager.h"
#include "../../../GameDataManager/GameDataManager.h"
#include "Stage/ObjBase/ObjBase.h"

namespace ar
{

/* Unnmaed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const	float StageChipSize = 96.f;			//!< ステージのチップのサイズ

}

/* Static Variable -------------------------------------------------------------------------------------------- */

const int StageDataManager::m_StockStageDataOrderCount = 3;

/* Public Functions ------------------------------------------------------------------------------------------- */

StageDataManager::StageDataManager(GameDataManager* pGameDataManager)
	: m_pGameDataManager(pGameDataManager)
	, m_StageChipSize(StageChipSize)
{
	m_StockStageData.resize(m_StockStageDataOrderCount);
	m_StockStageDataOrder.resize(m_StockStageDataOrderCount);

	// 順番に0を代入
	for(auto& order : m_StockStageDataOrder)
	{
		order = -1;
	}
}

StageDataManager::~StageDataManager(void)
{}

bool StageDataManager::LoadDataFile(void)
{
	std::string stageName = m_pGameDataManager->GetSelectStageName();

	std::string path = "../Resource/GameScene/" + stageName + "ChipData.mpd";
	m_BackGoundTexFileName = "../Resource/GameScene/" + stageName + ".png";

	FILE* fp;
	fopen_s(&fp, path.c_str(), "rb");
	if(fp == nullptr)
	{
		return false;
	}

	// 横と縦のインデックスを読み込む
	std::fread(&m_StageWidthChipCount, sizeof(short), 1, fp);  
	std::fread(&m_StageHeightChipCount, sizeof(short), 1, fp);  

	// 横と縦の長さをもとめる
	m_StageWidth = (StageChipSize * m_StageWidthChipCount) + StageChipSize;
	m_StageHeight = (StageChipSize * m_StageHeightChipCount) + StageChipSize;

	m_LoadStageIndexData.resize(m_StageHeightChipCount);

	for (auto& stageY : m_LoadStageIndexData)
	{
		stageY.resize(m_StageWidthChipCount);
		std::fseek(fp, 0, SEEK_CUR);
		std::fread(&stageY[0], sizeof(short), stageY.size(), fp);
	}

	std::fclose(fp);

	// 現在データのvectorのresizeを行う
	m_CurrentStageData.resize(m_StageHeightChipCount);

	for (auto& stageY : m_CurrentStageData)
	{
		stageY.resize(m_StageWidthChipCount);
	}

	return true;
}

void StageDataManager::SaveStageOriginalData(void)
{
	m_StageOriginalData = m_CurrentStageData;
}

void StageDataManager::SaveRespawnStageData(void)
{
	m_RespawnStageData = m_CurrentStageData;
}

void StageDataManager::AddStockStageData(void)
{
	int newStockDataNum = 0;	// 新しく更新するストックデータの番号を格納する変数

	// データが1番古い(順番が0)を現在のデータで更新する
	for(unsigned int i = 0; i < m_StockStageDataOrder.size(); ++i)
	{
		if(m_StockStageDataOrder[i] <= 0)
		{
			m_StockStageData[i] = m_CurrentStageData;
			m_StockStageDataOrder[i] = (m_StockStageDataOrderCount - 1);
			newStockDataNum = i;
			break;
		}
	}

	// 順番データを更新する
	for(unsigned int i = 0; i < m_StockStageDataOrder.size(); ++i)
	{
		if(i != newStockDataNum
			&& m_StockStageDataOrder[i] > 0)
		{
			m_StockStageDataOrder[i] -= 1;
		}
	}
}

void StageDataManager::ReturnmRespawnStageData(void)
{
	m_CurrentStageData = m_RespawnStageData;

	// オブジェクトを再配置する
	for(short i = 0; i < m_StageHeightChipCount ; ++i)
	{
		for(short j = 0; j < m_StageWidthChipCount ; ++j)
		{
			if(m_CurrentStageData[i][j] == nullptr)
			{
				continue;
			}
			m_CurrentStageData[i][j]->ChangeStagePos(i, j);
		}
	}
}

void StageDataManager::ReturnStageDataChangeBefore(void)
{
	int useStockDataNum = 0;	// 使用するストックデータの番号を格納する変数

	for(unsigned int i = 0; i < m_StockStageDataOrder.size(); ++i)
	{
		// ストックデータの中の1番最新のもので現在のステージデータを更新する
		if(m_StockStageDataOrder[i] == (m_StockStageDataOrderCount - 1))
		{
			m_CurrentStageData = m_StockStageData[i];
			m_StockStageDataOrder[i] = 0;
			useStockDataNum = i;
			break;
		}

		if(i == m_StockStageDataOrder.size() - 1)
		{	// 戻せるデータがなかったらオリジナルデータをいれる
			m_CurrentStageData = m_StageOriginalData;
		}
	}

	// 順番データを更新する
	// 1つずつ後ろにずらしておく
	for(unsigned int i = 0; i < m_StockStageDataOrder.size(); ++i)
	{
		if(i != useStockDataNum
			&& m_StockStageDataOrder[i] >= 0)
		{
			m_StockStageDataOrder[i] += 1;
		}
	}

	// オブジェクトを再配置する
	for(short i = 0; i < m_StageHeightChipCount ; ++i)
	{
		for(short j = 0; j < m_StageWidthChipCount ; ++j)
		{
			if(m_CurrentStageData[i][j] == nullptr)
			{
				continue;
			}
			m_CurrentStageData[i][j]->ChangeStagePos(i, j);
		}
	}
}

bool StageDataManager::ExistStockStageData(void)
{
	for(unsigned int i = 0; i < m_StockStageDataOrder.size(); ++i)
	{
		// ストックデータの中の1番最新のものがあるならtrueをかえす
		if(m_StockStageDataOrder[i] == (m_StockStageDataOrderCount - 1))
		{
			return true;;
		}

	}
	return false;
}

int StageDataManager::GetTypeID(int yIndexNum, int xIndexNum)
{
	// 引数のインデックス番号が存在しているかチェックし、存在してなければ即-1を返す
	if(RESULT_FAILED(ExistsIndexNum(yIndexNum, xIndexNum)))
	{
		return -1;
	}

	// データがnullptrなら空白のIDをかえす
	if(m_CurrentStageData[yIndexNum][xIndexNum] == nullptr)
	{
		return ObjBase::BLANK;
	}

	return static_cast<int>(m_CurrentStageData[yIndexNum][xIndexNum]->GetTypeID());
}

 ObjBase* const StageDataManager::GetObjBasePointer(int yIndexNum, int xIndexNum)
{
	// 引数のインデックス番号が存在しているかチェックし、存在してなければnullptrをかえす
	if(RESULT_FAILED(ExistsIndexNum(yIndexNum, xIndexNum)))
	{
		return nullptr;
	}

	return m_CurrentStageData[yIndexNum][xIndexNum];
}

void StageDataManager::SetCurrentStageChipData(int yIndexNum, int xIndexNum, ObjBase* pObj)
{
	// 引数のインデックス番号が存在しているかチェックし、存在してなければ即return
	if(RESULT_FAILED(ExistsIndexNum(yIndexNum, xIndexNum)))
	{
		return;
	}

	m_CurrentStageData[yIndexNum][xIndexNum] = pObj;
}

void StageDataManager::SetNewStockStageChipData(int yIndexNum, int xIndexNum, ObjBase* pObj)
{
	// 引数のインデックス番号が存在しているかチェックし、存在してなければ即return
	if(RESULT_FAILED(ExistsIndexNum(yIndexNum, xIndexNum)))
	{
		return;
	}

	for(unsigned int i = 0; i < m_StockStageDataOrder.size(); ++i)
	{
		// ストックデータの中の1番最新のもので現在のステージデータを更新する
		if(m_StockStageDataOrder[i] == (m_StockStageDataOrderCount - 1))
		{
			m_StockStageData[i][yIndexNum][xIndexNum] = pObj;
			break;
		}
	}
}

/* Private Functions ------------------------------------------------------------------------------------------ */

bool StageDataManager::ExistsIndexNum(int yIndexNum, int xIndexNum)
{
	if(yIndexNum < 0 || yIndexNum > static_cast<int>(m_StageHeightChipCount - 1)
		|| xIndexNum < 0 ||  xIndexNum > static_cast<int>(m_StageWidthChipCount - 1))
	{
		return false;
	}

	return true;
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
