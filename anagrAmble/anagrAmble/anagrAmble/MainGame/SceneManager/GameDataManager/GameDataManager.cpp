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
	: m_ThisScoreTime(0)
	, m_HighScoreTime(0)
{
	m_SelectStageName = "Stage";
}

void GameDataManager::Initialize(void)
{
	LoadHighScoreData();
}

void GameDataManager::ProcessGameClear(void)
{
	if(m_ThisScoreTime < m_HighScoreTime
		|| m_HighScoreTime == 0)
	{
		m_HighScoreTime = m_ThisScoreTime;
	}
	
	SaveHighScoreData();
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void GameDataManager::LoadHighScoreData(void)
{
	//ファイルポインタ
	FILE *file;
	fopen_s(&file, "../Resource/ScoreData/score.dat", "rb");
	fread(&m_HighScoreTime, sizeof(m_HighScoreTime), 1, file);
	fclose(file);
}

void GameDataManager::SaveHighScoreData(void)
{
	//ファイルポインタ
	FILE *file;
	fopen_s(&file,"../Resource/ScoreData/score.dat", "wb");
	fwrite(&m_HighScoreTime, sizeof(m_HighScoreTime), 1, file);
	fclose(file);
}


}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
