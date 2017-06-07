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
#include "../SharokuLibrary/sl/sl.h"

namespace ar
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const	int		ButtonMoveTimeInterval = 30;	// ボタンが動く間隔

}

/* Public Functions ------------------------------------------------------------------------------------------- */

GamePauseMenu::GamePauseMenu(int bgTexID, int btnTexID)
	: m_pLibrary(sl::ISharokuLibrary::Instance())
	, m_pBackground(nullptr)
	, m_pButton(nullptr)
	, m_ButtonMoveTimeCount(0)
	, m_MovesButton(false)
{
	// 背景作成
	m_pBackground = new GamePauseMenuBackground(bgTexID);

	// ボタン生成
	{
		sl::fRect		size		= { -170.f, -90.f, 170.f, 90.f };		// サイズ
		sl::fRect		uv			= { 0.0f, 0.0f, 1.0f, 1.0f };		// UV値
		sl::SLVECTOR2	pos			= { 960.f, 680.f };					// 開始座標
		m_pButton = ButtonFactory::AddScaleFunction(new BasicButton(btnTexID, size, uv, pos));
	}
}

GamePauseMenu::~GamePauseMenu(void)
{
	sl::DeleteSafely(m_pBackground);
	sl::DeleteSafely(m_pButton);
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
		m_pButton->Control();
	}
	
	if(m_pLibrary->CheckCustomizeState(ENTER, sl::PUSH))
	{
		GameEventManager::Instance().ReceiveEvent("title_return");
	}

	++m_ButtonMoveTimeCount;
}

void GamePauseMenu::Draw(void)
{
	m_pBackground->Draw();
	m_pButton->Draw();
}

}	// namespace ar	

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
