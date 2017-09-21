//==================================================================================================================================//
//!< @file		TitleScene.cpp
//!< @brief		ar::TitleSceneクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "TitleScene.h"
#include "TitleBackground.h"
#include "TitleText.h"
#include "TitleMenu.h"
#include "TitleSceneSoundID.h"
#include "../../SoundManager/SceneSoundManager.h"
#include "../SharokuLibrary/sl/sl.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

TitleScene::TitleScene(void)
	: m_pBackground(nullptr)
	, m_pText(nullptr)
	, m_pMenu(nullptr)
{
	m_NextSceneID = Scene::TITLE;

	// 背景クラス生成
	{
		int texID = m_pLibrary->LoadTexture("../Resource/TitleScene/TitleBG.png");
		m_pBackground = new TitleBackground(texID);
	}

	// タイトル文字クラス生成
	{
		int texID = m_pLibrary->LoadTexture("../Resource/TitleScene/TitleText.png");
		m_pText = new TitleText(texID);
	}

	// メニュークラス生成
	{
		int btnTexID = m_pLibrary->LoadTexture("../Resource/TitleScene/TitleBtn.png");
		m_pMenu = new TitleMenu(btnTexID);
	}

	// 音楽ファイル読み込み
	{
		//SceneSoundManager::Instance().LoadSound(static_cast<int>(TITLE_SCENE_SOUND_ID::BACK_GROUND)
		//	, "../Sounds/BGM/Title.wav");
		SceneSoundManager::Instance().LoadSound(static_cast<int>(TITLE_SCENE_SOUND_ID::BACK_GROUND)
			, "../Sounds/BGM/Stage.wav");

	}
}

TitleScene::~TitleScene(void)
{
	SceneSoundManager::Instance().ReleaseSoundALL();
	sl::DeleteSafely(&m_pMenu);
	sl::DeleteSafely(&m_pText);
	sl::DeleteSafely(&m_pBackground);
	m_pLibrary->ReleaseVertexALL();
	m_pLibrary->ReleaseTexALL();
}

/* Private Functions ------------------------------------------------------------------------------------------ */

Scene::ID TitleScene::Control(void)
{
	SceneSoundManager::Instance().PlayBackSound(static_cast<int>(TITLE_SCENE_SOUND_ID::BACK_GROUND), sl::PLAY_LOOP);
	m_NextSceneID = m_pMenu->Control();
	return m_NextSceneID;
}

void TitleScene::Draw(void)
{
	m_pBackground->Draw();
	m_pText->Draw();
	m_pMenu->Draw();
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
