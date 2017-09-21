//==================================================================================================================================//
//!< @file		SceneManager.cpp
//!< @brief		ar::SceneManagerクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "../SharokuLibrary/sl/sl.h"
#include "SceneManager.h"
#include "SceneFactory.h"
#include "GameDataManager/GameDataManager.h"
#include "SoundManager/CommonSoundManager.h"
#include "SoundManager/SceneSoundManager.h"
#include "Scene/TitleScene/TitleSceneSoundID.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

SceneManager::SceneManager(void)
	: m_CurrentState(CREATE_SCENE)
	, m_pScene(nullptr)
	, m_CurrentSceneID(Scene::LOGO)
	, m_NextSceneID(Scene::LOGO)
	, m_IsGameEnd(false)
	, m_pGameDataManager(nullptr)
{	
#ifdef _DEBUG
	m_NextSceneID = Scene::TITLE;
	//m_NextSceneID = Scene::GAME;
	//m_NextSceneID = Scene::GAME_CLEAR;
	//m_NextSceneID = Scene::GAME_OVER;
#endif	// _DEBUG

	m_pGameDataManager = new GameDataManager();

	m_pGameDataManager->Initialize();

	SceneFactory::Initialize(m_pGameDataManager);

	CommonSoundManager::Instance().Initialize();	
	CommonSoundManager::Instance().LoadSound(CommonSoundManager::SELECT, "../Sounds/SE/Select.wav");
	CommonSoundManager::Instance().LoadSound(CommonSoundManager::ENTER, "../Sounds/SE/Decision.wav");
	
	SceneSoundManager::Instance().Initialize();
}

SceneManager::~SceneManager(void)
{
	CommonSoundManager::Instance().ReleaseSoundALL();
	sl::ISharokuLibrary::Instance()->ReleaseSoundALL();
	sl::DeleteSafely(&m_pScene);
	sl::DeleteSafely(&m_pGameDataManager);
}

bool SceneManager::Updtae(void)
{
	switch(m_CurrentState)
	{

	case CREATE_SCENE:
		if(m_NextSceneID == Scene::END)
		{
			m_IsGameEnd = true;
		}
		else 
		{
			// シーン作成処理
			m_pScene = SceneFactory::CreateScene(m_NextSceneID);
			m_CurrentSceneID = m_NextSceneID;
			m_CurrentState = UPADATE_SCENE;
		}

		break;

	case UPADATE_SCENE:
		if(m_pScene == nullptr)
		{
			m_IsGameEnd = true;
		}
		else
		{
			if(m_CurrentSceneID != (m_NextSceneID = m_pScene->Update()))
			{
				m_CurrentState = DELETE_SCENE;
			}
		}
		break;

	case DELETE_SCENE:
		delete m_pScene;
		m_pScene = nullptr;
		m_CurrentState = CREATE_SCENE;
		break;

	default:
		// do nothing
		break;
	}

	return m_IsGameEnd;
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
