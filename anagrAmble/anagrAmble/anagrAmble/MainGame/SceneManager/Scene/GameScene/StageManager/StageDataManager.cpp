//==================================================================================================================================//
//!< @file		StageDataManager.cpp
//!< @brief		ar::StageDataManagerクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

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

/* Public Functions ------------------------------------------------------------------------------------------- */


StageDataManager::StageDataManager(GameDataManager* pGameDataManager)
	: m_pGameDataManager(pGameDataManager)
	, m_StageChipSize(StageChipSize)
{}

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

	m_LoadStageData.resize(m_StageHeightChipNum);

	for (auto& stageY : m_LoadStageData)
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

const ObjBase* StageDataManager::GetObjBasePointer(int indexY, int indexX)
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

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
