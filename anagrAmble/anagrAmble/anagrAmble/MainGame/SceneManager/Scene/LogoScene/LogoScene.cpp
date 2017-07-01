//==================================================================================================================================//
//!< @file		LogoScene.cpp
//!< @brief		ar::LogoSceneクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "LogoScene.h"
#include "LogoBackground.h"
#include "../SharokuLibrary/sl/sl.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

LogoScene::LogoScene(void)
	: m_pBackground(nullptr)
{
	m_NextSceneID = Scene::LOGO;
	 // 背景
	{
		int texID = m_pLibrary->LoadTexture("../Resource/LogoScene/LogoSceneBG.png");
		m_pBackground = new LogoBackground(texID);
	}
}

LogoScene::~LogoScene(void)
{
	sl::DeleteSafely(&m_pBackground);
	m_pLibrary->ReleaseVertexALL();
	m_pLibrary->ReleaseTexALL();
}

/* Private Functions ------------------------------------------------------------------------------------------ */

Scene::ID LogoScene::Control(void)
{
	if(m_pBackground->Control())
	{
		// 背景の表示時間が終わったらタイトルシーンへ移行
		m_NextSceneID = Scene::TITLE;
	}

	return m_NextSceneID;
}

void LogoScene::Draw(void)
{
	m_pBackground->Draw();
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
