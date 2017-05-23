//==================================================================================================================================//
//!< @file		GameScene.cpp
//!< @brief		ar::GameSceneクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "GameScene.h"
#include "../../GameDataManager/GameDataManager.h"
#include "../../../ControllerEnum.h"
#include "GamePauseMenu/GamePauseMenu.h"
#include "GameEventManager/GameEventManager.h"
#include "GameEventManager/EventLisner.h"
#include <functional>
#include <iostream>
#include "../SharokuLibrary/sl/sl.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

GameScene::GameScene(GameDataManager* pGameDataManager)
	: m_pGameDataManager(pGameDataManager)
	, m_rGameEventManager(GameEventManager::Instance())
	, m_pEventLisner(new EventLisner())
	, m_pPauseMenu(nullptr)
	, m_CurrentState(GAME_PLAY)
{
	m_NextSceneID = Scene::GAME;
	m_rGameEventManager.InitEventType();
	RegisterEvent();

	// ポーズメニューの作成
	{
		int menuBGTexID = m_pLibrary->LoadTexture("../Resource/GameScene/PauseMenuBG.png");
		int btnTexID = m_pLibrary->LoadTexture("../Resource/GameScene/PauseMeneBtn.png");
		m_pPauseMenu = new GamePauseMenu( menuBGTexID, btnTexID);
	}
}

GameScene::~GameScene(void)
{
	sl::DeleteSafely(m_pPauseMenu);
	sl::DeleteSafely(m_pEventLisner);
	m_pLibrary->ReleaseVertexALL();
	m_pLibrary->ReleaseTexALL();
}


/* Private Functions ------------------------------------------------------------------------------------------ */

Scene::ID GameScene::Control(void)
{
	m_rGameEventManager.Update();

	HandleEvent();

	switch(m_CurrentState)
	{
	case GAME_PLAY:
		if(m_pLibrary->CheckCustomizeState(PAUSE, sl::PUSH))
		{
			m_CurrentState = PAUSE_MENU;
		}
		break;

	case PAUSE_MENU:
		m_pPauseMenu->Control();
		if(m_pLibrary->CheckCustomizeState(PAUSE, sl::PUSH))
		{
			m_CurrentState = GAME_PLAY;
		}
		break;

	case CHANGE_SCENE:
		break;

	default:
		// do nothing
		break;
	}

	return m_NextSceneID;
}

void GameScene::Draw(void)
{
	
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
	const std::deque<std::string>& currentEvents = m_pEventLisner->GetEvent();

	if(currentEvents.empty())
	{
		return;
	}
	else
	{
		m_CurrentState = CHANGE_SCENE;
		std::string eventType;
		for(auto& gameEvent : currentEvents)
		{
			if(gameEvent == "game_over")
			{
				m_NextSceneID = Scene::GAME_OVER;
				return;
			}
			else if(gameEvent == "game_clear")
			{
				m_NextSceneID = Scene::GAME_CLEAR;
			}
			else if(gameEvent == "return_title")
			{
				m_NextSceneID = Scene::TITLE;
			}
		}

		m_pEventLisner->DelEvent();
	}

}

void GameScene::RegisterEvent(void)
{
	// ゲームオーバー
	m_rGameEventManager.RegisterEventType("game_over", m_pEventLisner);

	// ゲームクリア
	m_rGameEventManager.RegisterEventType("game_clear", m_pEventLisner);

	// タイトルへ戻る
	m_rGameEventManager.RegisterEventType("return_title", m_pEventLisner);
	
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
