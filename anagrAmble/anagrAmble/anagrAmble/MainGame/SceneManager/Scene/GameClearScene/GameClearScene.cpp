//==================================================================================================================================//
//!< @file		GameClearScene.cpp
//!< @brief		ar::GameClearSceneクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "GameClearScene.h"
#include "GameClearBackground.h"
#include "GameClearSceneSoundID.h"
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

	// 音楽の読み込み
	//m_pLibrary->LoadSound(static_cast<int>(GAME_CLEAR_SCENE_SOUND_ID::BACK_GROUND)
	//		, "../Sounds/BGM/GameClear.wav");
	m_pLibrary->LoadSound(static_cast<int>(GAME_CLEAR_SCENE_SOUND_ID::BACK_GROUND)
			, "../Sounds/BGM/Stage.wav");
}

GameClearScene::~GameClearScene(void)
{
	m_pLibrary->ReleaseSound(static_cast<int>(GAME_CLEAR_SCENE_SOUND_ID::BACK_GROUND));
	sl::DeleteSafely(&m_pBackground);
	m_pLibrary->ReleaseVertexALL();
	m_pLibrary->ReleaseTexALL();
}

/* Private Functions ------------------------------------------------------------------------------------------ */

Scene::ID GameClearScene::Control(void)
{
	m_pLibrary->PlayBackSound(static_cast<int>(GAME_CLEAR_SCENE_SOUND_ID::BACK_GROUND), sl::PLAY_LOOP);
	if(m_pBackground->Control())
	{ // 処理が終了したらTitleSceneへ移行
		m_NextSceneID = Scene::TITLE;
	}

	if(m_pLibrary->CheckCustomizeState(ENTER, sl::ON))
	{	// 決定ボタンが押されたらTitleSceneへ移行
		m_NextSceneID = Scene::TITLE;
		m_pLibrary->PlayBackSound(static_cast<int>(GAME_CLEAR_SCENE_SOUND_ID::ENTER), sl::RESET_PLAY);	
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
