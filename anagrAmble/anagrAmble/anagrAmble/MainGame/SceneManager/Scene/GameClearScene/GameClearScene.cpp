//==================================================================================================================================//
//!< @file		GameClearScene.cpp
//!< @brief		ar::GameClearSceneクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "GameClearScene.h"
#include "../../GameDataManager/GameDataManager.h"
#include "../../NumberDrawer/NumberDrawer.h"
#include "../../NumberDrawer/LargeNumberDrawer.h"
#include "../../ScoreCharacterDrawer/ScoreCharacterDrawer.h"
#include "../../ScoreCharacterDrawer/LargeScoreCharacterDrawer.h"
#include "../../ScoreTimeText/ScoreTimeText.h"
#include "../../ScoreTimeText/HighScoreText.h"
#include "../../ScoreTimeText/ThisScoreTimeText.h"
#include "GameClearBackground.h"
#include "GameClearSceneSoundID.h"
#include "../../../ControllerEnum.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

GameClearScene::GameClearScene(GameDataManager*	pGameDataManager)
	: m_pGameDataManager(pGameDataManager)
	, m_pNumberDrawer(nullptr)
	, m_pScoreCharacterDrawer(nullptr)
	, m_pBackground(nullptr)
	, m_CurrentState(FADE_IN_SCREEN)
{
	m_NextSceneID = Scene::GAME_CLEAR;

	// スコア関連作成
	{
		int texID = m_pLibrary->LoadTexture("../Resource/GameScene/UiNumber.png");
		m_pNumberDrawer = new LargeNumberDrawer(texID);
		m_pNumberDrawer->Initialize();
		m_pScoreCharacterDrawer = new LargeScoreCharacterDrawer(texID);
		m_pScoreCharacterDrawer->Initialize();

		m_pHighScoreText = new HighScoreText(m_pNumberDrawer, m_pScoreCharacterDrawer);
		// ハイスコアの位置座標 
		sl::SLVECTOR2 highScorePos = {690.0f, 700.f};
		m_pHighScoreText->Initialize(m_pGameDataManager->GetHighScoreTime(), highScorePos);

		m_pThisScoreTimeText = new ThisScoreTimeText(m_pNumberDrawer, m_pScoreCharacterDrawer);
			// タイムの位置座標 
		sl::SLVECTOR2 thisScoreTimePos = {690.0f, 800.f};
		m_pThisScoreTimeText->Initialize(m_pGameDataManager->GetThisScoreTime(), thisScoreTimePos);
	}

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
	m_pGameDataManager->ProcessGameClear();
	m_pLibrary->ReleaseSound(static_cast<int>(GAME_CLEAR_SCENE_SOUND_ID::BACK_GROUND));
	sl::DeleteSafely(&m_pBackground);
	sl::DeleteSafely(&m_pThisScoreTimeText);
	sl::DeleteSafely(&m_pHighScoreText);
	sl::DeleteSafely(&m_pScoreCharacterDrawer);
	sl::DeleteSafely(&m_pNumberDrawer);
	m_pLibrary->ReleaseVertexALL();
	m_pLibrary->ReleaseTexALL();
}

/* Private Functions ------------------------------------------------------------------------------------------ */

Scene::ID GameClearScene::Control(void)
{
	switch(m_CurrentState)
	{
	case FADE_IN_SCREEN:
		if(m_pBackground->FadeIn())
		{ 
			m_CurrentState = DISPLAY_SCREEN;
		}
		break;

	case DISPLAY_SCREEN:
		if(m_pBackground->ControlDisplayTime())
		{ 
			m_CurrentState = FADE_OUT_SCREEN;
		}
		break;

	case FADE_OUT_SCREEN:
		if(m_pBackground->FadeOut())
		{ // 処理が終了したらTitleSceneへ移行
			m_NextSceneID = Scene::TITLE;
		}
		if(m_pLibrary->CheckCustomizeState(ENTER, sl::ON))
		{	// 決定ボタンが押されたらTitleSceneへ移行
			m_NextSceneID = Scene::TITLE;
			m_pLibrary->PlayBackSound(static_cast<int>(GAME_CLEAR_SCENE_SOUND_ID::ENTER), sl::RESET_PLAY);
		}
		break;

	default:
		// do nothing
		break;
	}
	m_pLibrary->PlayBackSound(static_cast<int>(GAME_CLEAR_SCENE_SOUND_ID::BACK_GROUND), sl::PLAY_LOOP);
	return m_NextSceneID;
}

void GameClearScene::Draw(void)
{
	m_pBackground->Draw();
	switch(m_CurrentState)
	{
	case FADE_IN_SCREEN:
		break;

	case DISPLAY_SCREEN:
			m_pHighScoreText->Draw();
			m_pThisScoreTimeText->Draw();
		break;

	case FADE_OUT_SCREEN:
		break;

	default:
		break;
	}
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
