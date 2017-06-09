//==================================================================================================================================//
//!< @file		GameClearScene.cpp
//!< @brief		ar::GameClearSceneクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "GameClearScene.h"
#include "GameClearBackground.h"
#include "../../../ControllerEnum.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

GameClearScene::GameClearScene(void)
	: m_pBackground(nullptr)
{
	m_NextSceneID = Scene::GAME_CLEAR;

	// 背景作成
	{
		int texID = m_pLibrary->LoadTexture("../Resource/GameClearScene/GameClearBG.png");
		m_pBackground = new GameClearBackground(texID);
	}
}

GameClearScene::~GameClearScene(void)
{
	sl::DeleteSafely(m_pBackground);
	m_pLibrary->ReleaseVertexALL();
	m_pLibrary->ReleaseTexALL();
}

/* Private Functions ------------------------------------------------------------------------------------------ */

Scene::ID GameClearScene::Control(void)
{
	if(m_pBackground->Control())
	{ // 処理が終了したらTitleSceneへ移行
		m_NextSceneID = Scene::TITLE;
	}

	if(m_pLibrary->CheckCustomizeState(ENTER, sl::ON))
	{	// 決定ボタンが押されたらTitleSceneへ移行
		m_NextSceneID = Scene::TITLE;
	}

	return m_NextSceneID;
}

void GameClearScene::Draw(void)
{
	m_pBackground->Draw();
}


}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
