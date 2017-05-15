//==================================================================================================================================//
//!< @file		Main.cpp
//!< @brief		ゲーム「anagrAmble」のMain.cpp
//!< @author	T.Haga
//==================================================================================================================================//

#include <windows.h>
#include <crtdbg.h>
#include "MainGame/MainGame.h"

/* Entry Point ---------------------------------------------------------------------------------------- */

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
	// メモリリーク検出
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	ar::MainGame* pMainGame = nullptr;

	pMainGame = new ar::MainGame();

	pMainGame->Loop();

	delete pMainGame;

	return 0;
}

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
