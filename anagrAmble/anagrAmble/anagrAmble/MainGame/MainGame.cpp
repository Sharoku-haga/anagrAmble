//==================================================================================================================================//
//!< @file		MainGame.cpp
//!< @brief		MainGameクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "MainGame.h"
#include "../SharokuLibrary/sl/sl.h"
#include "SceneManager/SceneManager.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

MainGame::MainGame(void)
	: m_pLibrary(nullptr)
	, m_pSceneManager(nullptr)
{
	sl::ISharokuLibrary::Create();
	m_pLibrary = sl::ISharokuLibrary::Instance();

	// ライブラリの初期化
	sl::t_char*	windowTitle		= "anagrAmble";			// ウィンドウのタイトル
	int			windowWidth		= 1920;					// ウィンドウの横幅
	int			windowHeight	= 1080;					// ウィンドウの縦幅
	m_pLibrary->Initialize(windowTitle, windowWidth, windowHeight);

	m_pSceneManager = new SceneManager();
}

MainGame::~MainGame(void)
{
	sl::DeleteSafely(m_pSceneManager);
	sl::ISharokuLibrary::Delete();
}

void MainGame::Loop(void)
{
	while(true)
	{
		if(m_pLibrary->UpdateWindow())
		{
			break;
		}
		else
		{
			if(m_pSceneManager->Updtae())
			{
				break;
			}
		}
	}
}

} // namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//

