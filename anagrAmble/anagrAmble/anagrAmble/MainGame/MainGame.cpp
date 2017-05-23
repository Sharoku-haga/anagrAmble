//==================================================================================================================================//
//!< @file		MainGame.cpp
//!< @brief		ar::MainGameクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "MainGame.h"
#include "../SharokuLibrary/sl/sl.h"
#include "SceneManager/SceneManager.h"
#include "ControllerEnum.h"

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

	// デバイスインプットのカスタマイズ
	CustomizeInput();
#ifdef _DEBUG
	CutomizeInputDebug();
#endif // _DEBUG

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

/* Private Functions------------------------------------------------------------------------------------------- */

void MainGame::CustomizeInput(void)
{
	// 上ボタン: UP
	{

	}

	// 下のボタン : DOWN
	{

	}

	// 右ボタン	: RIGHT
	{

	}

	// 左ボタン : LEFT
	{

	}

	// 決定 : ENTER
	{

	}

	// プレイヤーのモード切替 : MODE_CHANGE
	{

	}

	// プレイヤーのモード解除 : MODE_RELEASE
	{

	}

	// 空間入れ替え : SPACE_CHANGE
	{

	}

	// 空間反転 : SPACE_INVERTED
	{

	}

	// アンカ-セット : ANCHOR_SET
	{

	}

	// ジャンプ : JUMP
	{

	}

	// しゃがむ : SQUAT
	{

	}

	// 特殊アクション : SPECIAL_ACTION
	{

	}

	//  時もどしの左ボタン : TIME_RETURN_L
	{

	}

	//  時もどしの右ボタン : TIME_RETURN_R
	{

	}

	// ポーズボタン : PAUSE
	{

	}
}

#ifdef _DEBUG

/** @todo 2017/05/19現在 仮実装 */
void MainGame::CutomizeInputDebug(void)
{
	// 上ボタン: UP
	{
		m_pLibrary->RegisterCustomizeType(UP, sl::KEYBOARD, sl::K_UP);
	}

	// 下のボタン : DOWN
	{
		m_pLibrary->RegisterCustomizeType(DOWN, sl::KEYBOARD, sl::K_DOWN);
	}

	// 右ボタン	: RIGHT
	{
		m_pLibrary->RegisterCustomizeType(RIGHT, sl::KEYBOARD, sl::K_RIGHT);
	}

	// 左ボタン : LEFT
	{
		m_pLibrary->RegisterCustomizeType(LEFT, sl::KEYBOARD, sl::K_LEFT);
	}

	// 決定 : ENTER
	{
		m_pLibrary->RegisterCustomizeType(ENTER, sl::KEYBOARD, sl::K_A);
	}

	// プレイヤーのモード切替 : MODE_CHANGE
	{

	}

	// プレイヤーのモード解除 : MODE_RELEASE
	{

	}

	// 空間入れ替え : SPACE_CHANGE
	{

	}

	// 空間反転 : SPACE_INVERTED
	{

	}

	// アンカ-セット : ANCHOR_SET
	{

	}

	// ジャンプ : JUMP
	{

	}

	// しゃがむ : SQUAT
	{

	}

	// 特殊アクション : SPECIAL_ACTION
	{

	}

	//  時もどしの左ボタン : TIME_RETURN_L
	{

	}

	//  時もどしの右ボタン : TIME_RETURN_R
	{

	}

	// ポーズボタン : PAUSE
	{
		m_pLibrary->RegisterCustomizeType(PAUSE, sl::KEYBOARD, sl::K_P);
	}
}

#endif // _DEBUG


} // namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
