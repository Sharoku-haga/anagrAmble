//==================================================================================================================================//
//!< @file		MainGame.cpp
//!< @brief		MainGameクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "MainGame.h"
#include "../SharokuLibrary/sl/sl.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

MainGame::MainGame(void)
	: m_pLibrary(nullptr)
{
	sl::ISharokuLibrary::Create();
	m_pLibrary = sl::ISharokuLibrary::Instance();

	// ライブラリの初期化
	sl::t_char*	windowTitle		= "anagrAmble";			// ウィンドウのタイトル
	int			windowWidth		= 1920;					// ウィンドウの横幅
	int			windowHeight	= 1080;					// ウィンドウの縦幅
	m_pLibrary->Initialize(windowTitle, windowWidth, windowHeight);
}

MainGame::~MainGame(void)
{
	sl::ISharokuLibrary::Delete();
}

void MainGame::Roop(void)
{
	while(true)
	{
		if(m_pLibrary->UpdateWindow())
		{
			break;
		}
		else
		{

		}
	}
}

} // namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//

