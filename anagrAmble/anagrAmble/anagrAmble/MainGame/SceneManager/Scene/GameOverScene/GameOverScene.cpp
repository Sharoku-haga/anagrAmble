//==================================================================================================================================//
//!< @file		GameOverScene.cpp
//!< @brief		ar::GameOverSceneクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "GameOverScene.h"
#include "GameOverBackground.h"
#include "../../../ControllerEnum.h"
#include "GameOverSceneSoundID.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

GameOverScene::GameOverScene(void)
	: m_pBackground(nullptr)
{
	m_NextSceneID = Scene::GAME_OVER;

	// 背景作成
	{
		int texID = m_pLibrary->LoadTexture("../Resource/GameOverScene/GameOverBG.png");
		m_pBackground = new GameOverBackground(texID);
	}

	// 音楽の読み込み
	m_pLibrary->LoadSound(static_cast<int>(GAME_OVER_SCENE_SOUND_ID::BACK_GROUND)
			, "../Sounds/BGM/GameOver.wav");
}

GameOverScene::~GameOverScene(void)
{
	m_pLibrary->ReleaseSound(static_cast<int>(GAME_OVER_SCENE_SOUND_ID::BACK_GROUND));
	sl::DeleteSafely(&m_pBackground);
	m_pLibrary->ReleaseVertexALL();
	m_pLibrary->ReleaseTexALL();
}

/* Private Functions ------------------------------------------------------------------------------------------ */

Scene::ID GameOverScene::Control(void)
{
	m_pLibrary->PlayBackSound(static_cast<int>(GAME_OVER_SCENE_SOUND_ID::BACK_GROUND), sl::PLAY_LOOP);
	if(m_pBackground->Control())
	{ // 処理が終了したらTitleSceneへ移行
		m_NextSceneID = Scene::TITLE;
	}

	if(m_pLibrary->CheckCustomizeState(ENTER, sl::ON))
	{	// 決定ボタンが押されたらTitleSceneへ移行
		m_pLibrary->PlayBackSound(static_cast<int>(GAME_OVER_SCENE_SOUND_ID::ENTER), sl::RESET_PLAY);	
		m_NextSceneID = Scene::TITLE;
	}

	return m_NextSceneID;
}

void GameOverScene::Draw(void)
{
	m_pBackground->Draw();
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
