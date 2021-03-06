﻿//==================================================================================================================================//
//!< @file		TilteMenu.cpp
//!< @brief		ar::TilteMenuクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "TitleMenu.h"
#include "Button/Button.h"
#include "Button/BasicButton.h"
#include "Button\ButtonFactory.h"
#include "TitleSceneSoundID.h"
#include "../../../ControllerEnum.h"
#include "../../SoundManager/CommonSoundManager.h"
#include "../../SoundManager//SceneSoundManager.h"

namespace ar
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const	int		ButtonMoveTimeInterval = 20;	// ボタンが動く間隔

}

/* Public Functions ------------------------------------------------------------------------------------------- */

TitleMenu::TitleMenu(int btnTexID)
	: m_pLibrary(sl::ISharokuLibrary::Instance())
	, m_CurrentSelectBtn(GAME_START)
	, m_ButtonMoveTimeCount(0)
	, m_MovesButton(false)
{
	
	// ボタンの生成
	{
		sl::fRect		size		= { -128.0f, -64.0f, 128.f, 64.f };		// サイズ

		sl::fRect		startUv		= { 0.0f, 0.0f, 1.0f, 0.5f };		// 初期UV値
		float			scrollTu	= 0.5f;								// Tu値のスクロール値

		sl::SLVECTOR2	startPos		= { 960.f, 760.f };				// 開始座標
		float			scrollPosYVal	= 100.f;						// Y座標のスクロール値

		for(int createBtnCount = 0; createBtnCount < BTN_MAX; ++createBtnCount)
		{
			sl::SLVECTOR2 pos = { startPos.x, (startPos.y + (scrollPosYVal * createBtnCount)) };
			sl::fRect	  uv = { startUv.m_Left, (startUv.m_Top + (scrollTu *  createBtnCount))
								, startUv.m_Right, (startUv.m_Bottom + (scrollTu *  createBtnCount)) };

			Button* pBtn = nullptr;
			pBtn = ButtonFactory::AddScaleFunction(ButtonFactory::AddBrightnessFunction(new BasicButton(btnTexID, size, uv, pos)));
			m_pButtons.push_back(pBtn);
		}
	}

}

TitleMenu::~TitleMenu(void)
{
	for(auto& pBtn : m_pButtons)
	{
		sl::DeleteSafely(&pBtn);
	}
}

Scene::ID TitleMenu::Control(void)
{
	if(m_ButtonMoveTimeCount == ButtonMoveTimeInterval)
	{
		m_MovesButton = m_MovesButton ? false : true;		// trueならfalseへ falseならtrueへと逆転させる
		m_ButtonMoveTimeCount = 0;
	}

	SelectButton();

	if(m_MovesButton)
	{
		m_pButtons[m_CurrentSelectBtn]->Control();
	}

	// Aボタンを押したとき現在選んでいるボタンの種類から
	// 次のSceneIDを判断してかえす
	if(m_pLibrary->CheckCustomizeState( ENTER, sl::PUSH))
	{
		switch(m_CurrentSelectBtn)
		{
		case GAME_START:
			CommonSoundManager::Instance().PlayBackSound(CommonSoundManager::ENTER,  sl::RESET_PLAY);
			return Scene::GAME;
			break;

		case GAME_END:
			CommonSoundManager::Instance().PlayBackSound(CommonSoundManager::ENTER,  sl::RESET_PLAY);
			return Scene::END;
			break;

		default:
			// return Scene::TITLE;
			break;
		}
	}

	++m_ButtonMoveTimeCount;

	return Scene::TITLE;
}

void TitleMenu::Draw(void)
{
	for(auto& pBtn : m_pButtons)
	{
		pBtn->Draw();
	}
}


void TitleMenu::SelectButton(void)
{
	switch(m_CurrentSelectBtn)
	{
	case GAME_START:
		if(m_pLibrary->CheckCustomizeState(DOWN, sl::PUSH))
		{
			CommonSoundManager::Instance().PlayBackSound(CommonSoundManager::SELECT, sl::RESET_PLAY);
			m_CurrentSelectBtn = GAME_END;
			m_MovesButton = true;
			m_ButtonMoveTimeCount = 0;
		}
		break;

	case GAME_END:
		if(m_pLibrary->CheckCustomizeState(UP, sl::PUSH))
		{
			CommonSoundManager::Instance().PlayBackSound(CommonSoundManager::SELECT, sl::RESET_PLAY);
			m_CurrentSelectBtn = GAME_START;
			m_MovesButton = true;
			m_ButtonMoveTimeCount = 0;
		}
		break;

	default:
		// do nothing
		break;
	}
}


}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
