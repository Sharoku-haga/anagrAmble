//==================================================================================================================================//
//!< @file		GamePauseMenu.cpp
//!< @brief		ar::GamePauseMenuクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "GamePauseMenu.h"
#include "../../TitleScene/Button/Button.h"
#include "../../TitleScene/Button/BasicButton.h"
#include "../../../../ControllerEnum.h"
#include "../GameEventManager/GameEventManager.h"
#include "GamePauseMenuBackground.h"
#include "../SharokuLibrary/sl/sl.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

GamePauseMenu::GamePauseMenu(int bgTexID, int btnTexID)
	: m_pLibrary(sl::ISharokuLibrary::Instance())
	, m_pBackground(nullptr)
	, m_pButton(nullptr)
{
	// 背景作成
	m_pBackground = new GamePauseMenuBackground(bgTexID);

	// ボタン生成
	{
		sl::fRect		size		= { 0.0f, 0.0f, 340.f, 180.f };		// サイズ
		sl::fRect		uv			= { 0.0f, 0.0f, 1.0f, 1.0f };		// UV値
		sl::SLVECTOR2	pos			= { 790.f, 590.f };					// 開始座標
		m_pButton = new BasicButton(btnTexID, size, uv, pos);
	}
}

GamePauseMenu::~GamePauseMenu(void)
{
	sl::DeleteSafely(m_pBackground);
	sl::DeleteSafely(m_pButton);
}

void GamePauseMenu::Control(void)
{
	m_pButton->Control();
	
	if(m_pLibrary->CheckCustomizeState(ENTER, sl::PUSH))
	{
		GameEventManager::Instance().ReceiveEvent("title_return");
	}
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
