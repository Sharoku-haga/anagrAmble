//==================================================================================================================================//
//!< @file		TitleScene.cpp
//!< @brief		TitleSceneクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "TitleScene.h"
#include "TitleBackground.h"
#include "TitleText.h"
#include "TitleMenu.h"
#include "../SharokuLibrary/sl/sl.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

TitleScene::TitleScene(void)
	: m_pBackground(nullptr)
	, m_pText(nullptr)
	, m_pMenu(nullptr)
{
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
}

TitleScene::~TitleScene(void)
{
	sl::DeleteSafely(m_pMenu);
	sl::DeleteSafely(m_pText);
	sl::DeleteSafely(m_pBackground);
	m_pLibrary->ReleaseVertexALL();
	m_pLibrary->ReleaseTexALL();
}

/* Private Functions ------------------------------------------------------------------------------------------ */

Scene::ID TitleScene::Control(void)
{
	Scene::ID nextSceneID = m_pMenu->Control();
	return nextSceneID;
}

void TitleScene::Draw(void)
{
	m_pMenu->Draw();
	m_pText->Draw();
	m_pBackground->Draw();
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
