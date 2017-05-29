//==================================================================================================================================//
//!< @file		StageDataManager.cpp
//!< @brief		ar::StageDataManagerクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "StageDataManager.h"
#include "../../../GameDataManager/GameDataManager.h"

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

	std::string path = "../Resource/GameScene/" + stageName + ".mpd";
	m_BackGoundTexFileName = "../Resource/GameScene/" + stageName + ".png";

	FILE* fp;
	fopen_s(&fp, path.c_str(), "rb");
	if(fp == nullptr)
	{
		return false;
	}

	short	stageWidthChipNum;		//!< ステージチップの横の数
	short	stageHeightChipNum;		//!< ステージチップの縦の数

	// 横と縦のインデックスを読み込む
	std::fread(&stageWidthChipNum, sizeof(short), 1, fp);  
	std::fread(&stageHeightChipNum, sizeof(short), 1, fp);  

	// 横と縦の長さをもとめる
	m_StageWidth = (StageChipSize * stageWidthChipNum) + StageChipSize;
	m_StageHeight = (StageChipSize * stageHeightChipNum) + StageChipSize;

	m_LoadStageData.resize(stageHeightChipNum);

	for (auto& stageY : m_LoadStageData)
	{
		stageY.resize(stageWidthChipNum);
		std::fseek(fp, 0, SEEK_CUR);
		std::fread(&stageY[0], sizeof(short), stageY.size(), fp);
	}

	std::fclose(fp);

	return true;
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
