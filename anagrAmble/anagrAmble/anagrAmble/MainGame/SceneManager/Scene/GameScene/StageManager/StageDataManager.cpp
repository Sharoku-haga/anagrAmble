//==================================================================================================================================//
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
	std::fread(&m_StageWidthChipNum, sizeof(short), 1, fp);  
	std::fread(&m_StageHeightChipNum, sizeof(short), 1, fp);  

	// 横と縦の長さをもとめる
	m_StageWidth = (StageChipSize * m_StageWidthChipNum) + StageChipSize;
	m_StageHeight = (StageChipSize * m_StageHeightChipNum) + StageChipSize;

	m_LoadStageIndexData.resize(m_StageHeightChipNum);

	for (auto& stageY : m_LoadStageIndexData)
	{
		stageY.resize(m_StageWidthChipNum);
		std::fseek(fp, 0, SEEK_CUR);
		std::fread(&stageY[0], sizeof(short), stageY.size(), fp);
	}

	std::fclose(fp);

	// 現在データのvectorのresizeを行う
	m_CurrentStageData.resize(m_StageHeightChipNum);

	for (auto& stageY : m_CurrentStageData)
	{
		stageY.resize(m_StageWidthChipNum);
	}

	return true;
}

void StageDataManager::SaveStageOriginData(void)
{
	m_StageOriginData = m_CurrentStageData;
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


bool StageDataManager::ReturnBeforeCurrentStageData(void)
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

		if( i ==  m_StockStageDataOrder.size() - 1)
		{	// 戻せるデータがなかったら即return
			return false;
		}
	}

	// 順番データを更新する
	// 1つずつ後ろにずらしておく
	for(unsigned int i = 0; i < m_StockStageDataOrder.size(); ++i)
	{
		
		if(i != useStockDataNum
			&& m_StockStageDataOrder[i] > 0)
		{
			m_StockStageDataOrder[i] += 1;
		}
	}

	// オブジェクトを再配置する
	for(short i = 0; i < (m_StageHeightChipNum - 1); ++i)
	{
		for(short j = 0; j < (m_StageWidthChipNum - 1); ++j)
		{
			if(m_CurrentStageData[i][j] == nullptr)
			{
				continue;
			}
			m_CurrentStageData[i][j]->RelocatePos(i, j);
		}
	}

	return true;
}

int StageDataManager::GetTypeID(int indexY, int indexX)
{
	// インデックスが0未満、もしくはサイズ以上なら-1をかえす
	if(indexY < 0 || indexY > static_cast<int>(m_StageHeightChipNum - 1)
		|| indexX < 0 ||  indexX > static_cast<int>(m_StageWidthChipNum - 1))
	{
		return -1;
	}

	// データがnullptrなら空白のIDをかえす
	if(m_CurrentStageData[indexY][indexX] == nullptr)
	{
		return ObjBase::BLANK;
	}

	return static_cast<int>(m_CurrentStageData[indexY][indexX]->GetTypeID());
}

 ObjBase* const StageDataManager::GetObjBasePointer(int indexY, int indexX)
{
	// インデックスが0未満、もしくはサイズ以上ならnullptrをかえす
	if(indexY < 0 || indexY > static_cast<int>(m_StageHeightChipNum - 1)
		|| indexX < 0 ||  indexX > static_cast<int>(m_StageWidthChipNum - 1))
	{
		return nullptr;
	}

	return m_CurrentStageData[indexY][indexX];
}

void StageDataManager::SetCurrentStageChipData(int indexY, int indexX, ObjBase* pObj)
{
	// インデックスが0未満、もしくはサイズ以上なら即return
	if(indexY < 0 || indexY > static_cast<int>(m_StageHeightChipNum - 1)
		|| indexX < 0 ||  indexX > static_cast<int>(m_StageWidthChipNum - 1))
	{
		return;
	}

	m_CurrentStageData[indexY][indexX] = pObj;
}

void StageDataManager::SetNewStockStageChipData(int indexY, int indexX, ObjBase* pObj)
{
	// インデックスが0未満、もしくはサイズ以上なら即return
	// 念の為チェック
	if(indexY < 0 || indexY > static_cast<int>(m_StageHeightChipNum - 1)
		|| indexX < 0 ||  indexX > static_cast<int>(m_StageWidthChipNum - 1))
	{
		return;
	}

	for(unsigned int i = 0; i < m_StockStageDataOrder.size(); ++i)
	{
		// ストックデータの中の1番最新のもので現在のステージデータを更新する
		if(m_StockStageDataOrder[i] == (m_StockStageDataOrderCount - 1))
		{
			m_StockStageData[i][indexY][indexX] = pObj;
			break;
		}
	}
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
