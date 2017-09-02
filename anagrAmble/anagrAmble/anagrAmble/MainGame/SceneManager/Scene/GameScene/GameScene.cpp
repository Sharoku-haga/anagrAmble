//==================================================================================================================================//
//!< @file		GameScene.cpp
//!< @brief		ar::GameSceneクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "GameScene.h"
#include "../../GameDataManager/GameDataManager.h"
#include "../../../ControllerEnum.h"
#include "GameSceneSoundID.h"
#include "GamePauseMenu/GamePauseMenu.h"
#include "GameEventManager/GameEventManager.h"
#include "GameEventManager/EventListener.h"
#include "StageManager/StageManager.h"
#include "../SharokuLibrary/sl/sl.h"
#include "../../SoundManager/CommonSoundManager.h"
#include "../../SoundManager/SceneSoundManager.h"
#include <iostream>

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

GameScene::GameScene(GameDataManager* pGameDataManager)
	: m_pGameDataManager(pGameDataManager)
	, m_rGameEventManager(GameEventManager::Instance())
	, m_pEventListener(new EventListener())
	, m_pPauseMenu(nullptr)
	, m_pStageManager(nullptr)
	, m_CurrentState(GAME_PLAY)
{
	m_NextSceneID = Scene::GAME;
	m_rGameEventManager.InitEventType();
	RegisterEvent();

	// ポーズメニューの作成
	{
		int menuBGTexID = m_pLibrary->LoadTexture("../Resource/GameScene/PauseMenuBG.png");
		int pauseBtnTexID = m_pLibrary->LoadTexture("../Resource/GameScene/PauseMenuPauseBtn.png");
		int titleReturnBtnID= m_pLibrary->LoadTexture("../Resource/GameScene/PauseMenuTitleBtn.png");
		m_pPauseMenu = new GamePauseMenu(menuBGTexID, pauseBtnTexID, titleReturnBtnID);
	}

	m_pStageManager = new StageManager(m_pGameDataManager);
}

GameScene::~GameScene(void)
{
	SceneSoundManager::Instance().ReleaseSoundALL();
	m_pLibrary->ReleaseUVAnimeDataALL();
	sl::DeleteSafely(&m_pStageManager);
	sl::DeleteSafely(&m_pPauseMenu);
	sl::DeleteSafely(&m_pEventListener);
	m_pLibrary->ReleaseVertexALL();
	m_pLibrary->ReleaseTexALL();
}


/* Private Functions ------------------------------------------------------------------------------------------ */

Scene::ID GameScene::Control(void)
{
	m_rGameEventManager.Update();		// ゲームイベントを更新

	HandleEvent();						// GameSceneのイベント処理を行う

	switch(m_CurrentState)
	{
	case GAME_PLAY:
		if(m_pLibrary->CheckCustomizeState(PAUSE, sl::PUSH))
		{
			CommonSoundManager::Instance().PlayBackSound(CommonSoundManager::SELECT, sl::RESET_PLAY);
			m_CurrentState = PAUSE_MENU;
		}
		m_pStageManager->Contorl();
		break;

	case PAUSE_MENU:
		m_pPauseMenu->Control();
		if(m_pLibrary->CheckCustomizeState(PAUSE, sl::PUSH))
		{
			CommonSoundManager::Instance().PlayBackSound(CommonSoundManager::SELECT, sl::RESET_PLAY);
			m_CurrentState = GAME_PLAY;
		}
		break;

	case CHANGE_SCENE:
		// do nothing
		break;

	default:
		// do nothing
		break;
	}

	return m_NextSceneID;
}

void GameScene::Draw(void)
{
	m_pStageManager->Draw();

	switch(m_CurrentState)
	{
	case GAME_PLAY:
		break;

	case PAUSE_MENU:
		m_pPauseMenu->Draw();
		break;

	case CHANGE_SCENE:
		// do nothing
		break;

	default:
		// do nothing
		break;
	}
}

void GameScene::HandleEvent(void)
{
	if(m_pEventListener->EmptyCurrentEvent())
	{
		return;
	}
	else
	{
		const std::deque<std::string>& currentEvents = m_pEventListener->GetEvent();

		m_CurrentState = CHANGE_SCENE;			// ゲームシーンの状態をシーン遷移状態にかえる

		std::string eventType;			
		for(auto& gameEvent : currentEvents)
		{
			if(gameEvent == "game_over")
			{
				m_NextSceneID = Scene::GAME_OVER;
				return;								// ゲームオーバーの場合はチェック終了して、即return
			}
			else if(gameEvent == "game_clear")
			{
				m_NextSceneID = Scene::GAME_CLEAR;
			}
			else if(gameEvent == "title_return")
			{
				m_NextSceneID = Scene::TITLE;
			}
		}

		m_pEventListener->DelEvent();
	}
}

void GameScene::RegisterEvent(void)
{
	// ゲームオーバー
	m_rGameEventManager.RegisterEventType("game_over", m_pEventListener);

	// ゲームクリア
	m_rGameEventManager.RegisterEventType("game_clear", m_pEventListener);

	// タイトルへ戻る
	m_rGameEventManager.RegisterEventType("title_return", m_pEventListener);
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
