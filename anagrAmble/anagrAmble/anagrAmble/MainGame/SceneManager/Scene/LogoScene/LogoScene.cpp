//==================================================================================================================================//
//!< @file		LogoScene.cpp
//!< @brief		LogoSceneクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "LogoScene.h"
#include "LogoBackground.h"
#include "LogoText.h"
#include "../SharokuLibrary/sl/sl.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

LogoScene::LogoScene(void)
	: m_pBackground(nullptr)
	, m_pText(nullptr)
{

	// 背景
	{
		int texID = m_pLibrary->LoadTexture("../Resource/LogoScene/LogoBG.png");
		m_pBackground = new LogoBackground(texID);
	}

	// テキスト
	{
		int texID = m_pLibrary->LoadTexture("../Resource/LogoScene/LogoText.png");
		m_pText = new LogoText(texID);
	}
}

LogoScene::~LogoScene(void)
{
	sl::DeleteSafely(m_pText);
	sl::DeleteSafely(m_pBackground);
	m_pLibrary->ReleaseVertexALL();
	m_pLibrary->ReleaseTexALL();
}

/* Private Functions ------------------------------------------------------------------------------------------ */

Scene::ID LogoScene::Control(void)
{
	
	if(m_pText->Control())
	{
		// ロゴの表示時間が終わったらタイトルシーンへ移行
		return Scene::TITLE;
	}

	return Scene::LOGO;
}

void LogoScene::Draw(void)
{
	m_pText->Draw();
	m_pBackground->Draw();
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
