//==================================================================================================================================//
//!< @file		StageManager.cpp
//!< @brief		ar::StageManagerクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "StageManager.h"
#include "../../../GameDataManager/GameDataManager.h"
#include "StageDataManager.h"
#include "Stage/Stage.h"
#include "../SharokuLibrary/sl/sl.h"
#include "StageDataChangeManager.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

StageManager::StageManager(GameDataManager*	pGameDataManager)
	: m_pGameDataManager(pGameDataManager)
	, m_pStageDataManager(nullptr)
	, m_pStage(nullptr)
	, m_CurrentState(STAGE_INIT)
{
	m_pStageDataManager = new StageDataManager(m_pGameDataManager);
	StageDataChangeManager::Instance().InitialIze(m_pStageDataManager);
	m_pStage = new Stage(m_pStageDataManager);
}

StageManager::~StageManager(void)
{
	sl::DeleteSafely(m_pStageDataManager);
	sl::DeleteSafely(m_pStage);
}

void StageManager::Contorl(void)
{
	switch(m_CurrentState)
	{
	case STAGE_INIT:
		m_pStageDataManager->LoadDataFile();
		m_pStage->Initialize();
		m_pStageDataManager->SaveStageOriginData();
		m_CurrentState = STAGE_RUN;
		break;

	case STAGE_RUN:
		m_pStage->Control();
		break;

	default:
		// do nothing
		break;
	}
}

void StageManager::Draw(void)
{
	switch(m_CurrentState)
	{
	case STAGE_INIT:
		// do nothing
		break;

	case STAGE_RUN:
		m_pStage->Draw();
		break;

	default:
		// do nothing
		break;
	}

}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
