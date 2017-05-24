﻿//==================================================================================================================================//
//!< @file		TilteMenu.cpp
//!< @brief		ar::TilteMenuクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "TitleMenu.h"
#include "../Button/Button.h"
#include "../Button/BasicButton.h"
#include "../../../ControllerEnum.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

TitleMenu::TitleMenu(int btnTexID)
	: m_pLibrary(sl::ISharokuLibrary::Instance())
	, m_CurrentSelectBtn(GAME_START)
{
	
	// ボタンの生成
	{
		sl::fRect		size		= { 0.0f, 0.0f, 340.f, 180.f };		// サイズ

		sl::fRect		startUv		= { 0.0f, 0.0f, 1.0f, 0.5f };		// 初期UV値
		float			scrollTu	= 0.5f;								// Tu値のスクロール値

		sl::SLVECTOR2	startPos		= { 790.f, 590.f };				// 開始座標
		float			scrollPosYVal	= 200.f;						// Y座標のスクロール値

		for(int createBtnCount = 0; createBtnCount < BTN_MAX; ++createBtnCount)
		{
			sl::SLVECTOR2 pos = { startPos.x, (startPos.y + (scrollPosYVal * createBtnCount)) };
			sl::fRect	  uv = { startUv.m_Left, (startUv.m_Top + (scrollTu *  createBtnCount))
								, startUv.m_Right, (startUv.m_Bottom + (scrollTu *  createBtnCount)) };

			Button* pBtn = nullptr;
			pBtn = new BasicButton(btnTexID, size, uv, pos);
			m_pButtons.push_back(pBtn);
		}
	}

}

TitleMenu::~TitleMenu(void)
{
	for(auto& pBtn : m_pButtons)
	{
		sl::DeleteSafely(pBtn);
	}
}

Scene::ID TitleMenu::Control(void)
{
	SelectButton();

	m_pButtons[m_CurrentSelectBtn]->Control();

	// Aボタンを押したとき現在選んでいるボタンの種類から
	// 次のSceneIDを判断してかえす
	if(m_pLibrary->CheckCustomizeState( ENTER, sl::PUSH))
	{
		switch(m_CurrentSelectBtn)
		{
		case GAME_START:
			return Scene::GAME;
			break;

		case GAME_END:
			return Scene::END;
			break;

		default:
			// return Scene::TITLE;
			break;
		}
	}

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
			m_CurrentSelectBtn = GAME_END;
		}
		break;

	case GAME_END:
		if(m_pLibrary->CheckCustomizeState(UP, sl::PUSH))
		{
			m_CurrentSelectBtn = GAME_START;
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
