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
		//m_pLibrary->RegisterCustomizeType(UP, sl::GAMEPAD, sl::XIGAMEPAD_DPAD_UP );
	}

	// 下のボタン : DOWN
	{
		m_pLibrary->RegisterCustomizeType(DOWN, sl::GAMEPAD, sl::XIGAMEPAD_LSTICK_DOWN);
		m_pLibrary->RegisterCustomizeType(DOWN, sl::GAMEPAD, sl::XIGAMEPAD_DPAD_DOWN );

	}

	// 右ボタン	: RIGHT
	{
		m_pLibrary->RegisterCustomizeType(RIGHT, sl::GAMEPAD, sl::XIGAMEPAD_LSTICK_RIGHT);
		m_pLibrary->RegisterCustomizeType(RIGHT, sl::GAMEPAD, sl::XIGAMEPAD_DPAD_RIGHT );
	}

	// 左ボタン : LEFT
	{
		m_pLibrary->RegisterCustomizeType(LEFT, sl::GAMEPAD, sl::XIGAMEPAD_LSTICK_LEFT);
		m_pLibrary->RegisterCustomizeType(LEFT, sl::GAMEPAD, sl::XIGAMEPAD_DPAD_LEFT );

	}

	// 決定 : ENTER
	{
		m_pLibrary->RegisterCustomizeType(ENTER, sl::GAMEPAD, sl::XIGAMEPAD_A  );
	}

	// プレイヤーのモード切替 : MODE_CHANGE
	{
		m_pLibrary->RegisterCustomizeType(MODE_CHANGE, sl::GAMEPAD, sl::XIGAMEPAD_B  );
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

	// アンカー回収 : ANCHOR_RETRIEVE
	{

	}


	// ダッシュ : DASH
	{
		m_pLibrary->RegisterCustomizeType(DASH, sl::GAMEPAD, sl::XIGAMEPAD_B  );
	}

	// ジャンプ : JUMP
	{
		m_pLibrary->RegisterCustomizeType(JUMP, sl::GAMEPAD, sl::XIGAMEPAD_DPAD_UP);
		m_pLibrary->RegisterCustomizeType(JUMP, sl::GAMEPAD, sl::XIGAMEPAD_LSTICK_UP);
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
		m_pLibrary->RegisterCustomizeType(PAUSE, sl::GAMEPAD, sl::XIGAMEPAD_START);
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
		m_pLibrary->RegisterCustomizeType(ENTER, sl::KEYBOARD, sl::K_RETURN);
	}

	// プレイヤーのモード切替 : MODE_CHANGE
	{
		m_pLibrary->RegisterCustomizeType(MODE_CHANGE, sl::KEYBOARD, sl::K_X);
	}

	// プレイヤーのモード解除 : MODE_RELEASE
	{
		m_pLibrary->RegisterCustomizeType(MODE_RELEASE, sl::KEYBOARD, sl::K_C);
	}

	// 空間入れ替え : SPACE_CHANGE
	{

	}

	// 空間反転 : SPACE_INVERTED
	{

	}

	// アンカ-セット : ANCHOR_SET
	{
		m_pLibrary->RegisterCustomizeType(ANCHOR_SET, sl::KEYBOARD, sl::K_Z);
	}

	// アンカー回収 : ANCHOR_RETRIEVE
	{
		m_pLibrary->RegisterCustomizeType(ANCHOR_RETRIEVE, sl::KEYBOARD, sl::K_M);
	}

	// ダッシュ : DASH
	{
		m_pLibrary->RegisterCustomizeType(DASH, sl::KEYBOARD, sl::K_D);
	}

	// ジャンプ : JUMP
	{
		m_pLibrary->RegisterCustomizeType(JUMP, sl::KEYBOARD, sl::K_A);
	}

	// しゃがむ : SQUAT
	{

	}

	// 特殊アクション : SPECIAL_ACTION
	{
		m_pLibrary->RegisterCustomizeType(SPECIAL_ACTION, sl::KEYBOARD, sl::K_K);
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
		m_pLibrary->RegisterCustomizeType(PAUSE, sl::KEYBOARD, sl::K_T);
	}
}

#endif // _DEBUG


} // namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
