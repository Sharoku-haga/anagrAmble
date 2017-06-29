//==================================================================================================================================//
//!< @file		GameDataManager.cpp
//!< @brief		ar::GameDataManagerクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "GameDataManager.h"
#include <stdio.h>

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

GameDataManager::GameDataManager(void)
	: m_PlayedGameTime(0)
	, m_HighScoreGameTime(0)
{
	m_SelectStageName = "Stage";
}

GameDataManager::~GameDataManager(void)
{}

void GameDataManager::Initialize(void)
{
	LoadHighScoreData();
}

void GameDataManager::ProcessGameClear(void)
{
	if(m_PlayedGameTime < m_HighScoreGameTime
		|| m_HighScoreGameTime == 0)
	{
		m_HighScoreGameTime = m_PlayedGameTime;
	}
	
	SaveHighScoreData();
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void GameDataManager::LoadHighScoreData(void)
{
	//ファイルポインタ
	FILE *file;
	fopen_s(&file, "../Resource/ScoreData/score.dat", "rb");
	fread(&m_HighScoreGameTime, sizeof(m_HighScoreGameTime), 1, file);
	fclose(file);
}

void GameDataManager::SaveHighScoreData(void)
{
	//ファイルポインタ
	FILE *file;
	fopen_s(&file,"../Resource/ScoreData/score.dat", "wb");
	fwrite(&m_HighScoreGameTime, sizeof(m_HighScoreGameTime), 1, file);
	fclose(file);
}


}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
