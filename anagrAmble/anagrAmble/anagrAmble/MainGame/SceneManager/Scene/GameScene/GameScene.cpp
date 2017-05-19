﻿//==================================================================================================================================//
//!< @file		GameScene.cpp
//!< @brief		ar::GameSceneクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "GameScene.h"
#include "../../GameDataManager/GameDataManager.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

GameScene::GameScene(GameDataManager* pGameDataManager)
	: m_pGameDataManager(pGameDataManager)
{}

GameScene::~GameScene(void)
{}


/* Private Functions ------------------------------------------------------------------------------------------ */

Scene::ID GameScene::Control(void)
{

	return Scene::GAME;
}

void GameScene::Draw(void)
{

}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
