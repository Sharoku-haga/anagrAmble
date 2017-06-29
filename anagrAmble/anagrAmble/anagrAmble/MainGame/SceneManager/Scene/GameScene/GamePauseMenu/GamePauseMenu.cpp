//==================================================================================================================================//
//!< @file		GamePauseMenu.cpp
//!< @brief		ar::GamePauseMenuクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "GamePauseMenu.h"
#include "../../TitleScene/Button/Button.h"
#include "../../TitleScene/Button/BasicButton.h"
#include "../../TitleScene/Button/ButtonFactory.h"
#include "../../../../ControllerEnum.h"
#include "../GameEventManager/GameEventManager.h"
#include "GamePauseMenuBackground.h"
#include "../GameSceneSoundID.h"
#include "../SharokuLibrary/sl/sl.h"

namespace ar
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const	int		ButtonMoveTimeInterval = 30;	// ボタンが動く間隔

}

/* Public Functions ------------------------------------------------------------------------------------------- */

GamePauseMenu::GamePauseMenu(int bgTexID, int pauseBtnTexID, int titleReturnBtnID)
	: m_pLibrary(sl::ISharokuLibrary::Instance())
	, m_pBackground(nullptr)
	, m_ButtonMoveTimeCount(0)
	, m_MovesButton(false)
{
	// 背景作成
	m_pBackground = new GamePauseMenuBackground(bgTexID);


	// ボタン作成
	m_pButtons.resize(BTN_MAX);

	// ポーズボタン(表示のみ)
	{
		sl::fRect		size		= { -170.f, -90.f, 170.f, 90.f };	// サイズ
		sl::fRect		uv			= { 0.0f, 0.0f, 1.0f, 1.0f };		// UV値
		sl::SLVECTOR2	pos			= { 960.f, 340.f };					// 開始座標
		m_pButtons[PAUSE] = new BasicButton(pauseBtnTexID, size, uv, pos);
	}

	// タイトルへ戻るボタン生成
	{
		sl::fRect		size		= { -170.f, -90.f, 170.f, 90.f };	// サイズ
		sl::fRect		uv			= { 0.0f, 0.0f, 1.0f, 1.0f };		// UV値
		sl::SLVECTOR2	pos			= { 960.f, 680.f };					// 開始座標
		m_pButtons[TITLE_RETUN] = ButtonFactory::AddScaleFunction(new BasicButton(titleReturnBtnID, size, uv, pos));
	}
}

GamePauseMenu::~GamePauseMenu(void)
{
	for(auto& pBtn : m_pButtons)
	{
		sl::DeleteSafely(&pBtn);
	}
	sl::DeleteSafely(&m_pBackground);
}

void GamePauseMenu::Control(void)
{
	if(m_ButtonMoveTimeCount == ButtonMoveTimeInterval)
	{
		m_MovesButton = m_MovesButton ? false : true;		// trueならfalseへ falseならtrueへと逆転させる
		m_ButtonMoveTimeCount = 0;
	}
	
	if(m_MovesButton)
	{
		m_pButtons[TITLE_RETUN]->Control();
	}
	
	if(m_pLibrary->CheckCustomizeState(ENTER, sl::PUSH))
	{
		GameEventManager::Instance().ReceiveEvent("title_return");
		m_pLibrary->PlayBackSound(static_cast<int>(GAME_SCENE_SOUND_ID::ENTER), sl::RESET_PLAY);
	}

	++m_ButtonMoveTimeCount;
}

void GamePauseMenu::Draw(void)
{
	m_pBackground->Draw();
	for(auto& pBtn : m_pButtons)
	{
		pBtn->Draw();
	}
}

}	// namespace ar	

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
