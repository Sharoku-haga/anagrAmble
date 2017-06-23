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
	sl::DeleteSafely(&m_pSceneManager);
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
		m_pLibrary->RegisterCustomizeType(UP, sl::KEYBOARD, sl::K_UP);
		m_pLibrary->RegisterCustomizeType(UP, sl::GAMEPAD, sl::XIGAMEPAD_LSTICK_UP);
		m_pLibrary->RegisterCustomizeType(UP, sl::GAMEPAD, sl::XIGAMEPAD_DPAD_UP );
	}

	// 下のボタン : DOWN
	{
		m_pLibrary->RegisterCustomizeType(DOWN, sl::GAMEPAD, sl::XIGAMEPAD_LSTICK_DOWN);
		m_pLibrary->RegisterCustomizeType(DOWN, sl::GAMEPAD, sl::XIGAMEPAD_DPAD_DOWN );
		m_pLibrary->RegisterCustomizeType(DOWN, sl::KEYBOARD, sl::K_DOWN);

	}

	// 右ボタン	: RIGHT
	{
		m_pLibrary->RegisterCustomizeType(RIGHT, sl::GAMEPAD, sl::XIGAMEPAD_LSTICK_RIGHT);
		m_pLibrary->RegisterCustomizeType(RIGHT, sl::GAMEPAD, sl::XIGAMEPAD_DPAD_RIGHT );
		m_pLibrary->RegisterCustomizeType(RIGHT, sl::KEYBOARD, sl::K_RIGHT);

	}

	// 左ボタン : LEFT
	{
		m_pLibrary->RegisterCustomizeType(LEFT, sl::GAMEPAD, sl::XIGAMEPAD_LSTICK_LEFT);
		m_pLibrary->RegisterCustomizeType(LEFT, sl::GAMEPAD, sl::XIGAMEPAD_DPAD_LEFT );
		m_pLibrary->RegisterCustomizeType(LEFT, sl::KEYBOARD, sl::K_LEFT);
	}

	// 決定 : ENTER
	{
		m_pLibrary->RegisterCustomizeType(ENTER, sl::GAMEPAD, sl::XIGAMEPAD_A  );
		m_pLibrary->RegisterCustomizeType(ENTER, sl::KEYBOARD, sl::K_RETURN);
	}

	// プレイヤーのモード切替 : MODE_CHANGE
	{
		m_pLibrary->RegisterCustomizeType(MODE_CHANGE, sl::GAMEPAD, sl::XIGAMEPAD_X  );
		m_pLibrary->RegisterCustomizeType(MODE_CHANGE, sl::KEYBOARD, sl::K_Z);

	}

	// プレイヤーのモード解除 : MODE_RELEASE
	{
		m_pLibrary->RegisterCustomizeType(MODE_RELEASE, sl::KEYBOARD, sl::K_Z);
		m_pLibrary->RegisterCustomizeType(MODE_RELEASE, sl::GAMEPAD, sl::XIGAMEPAD_X  );

	}

	// 空間入れ替え : SPACE_CHANGE
	{
		m_pLibrary->RegisterCustomizeType(SPACE_CHANGE, sl::KEYBOARD, sl::K_RETURN);
		m_pLibrary->RegisterCustomizeType(SPACE_CHANGE, sl::GAMEPAD, sl::XIGAMEPAD_B  );

	}

	// 空間反転 : SPACE_INVERTED
	{

	}

	// アンカ-セット : ANCHOR_SET
	{
		m_pLibrary->RegisterCustomizeType(ANCHOR_SET, sl::KEYBOARD, sl::K_SPACE);
		m_pLibrary->RegisterCustomizeType(ANCHOR_SET, sl::GAMEPAD, sl::XIGAMEPAD_B  );
	}

	// アンカー回収 : ANCHOR_RETRIEVE
	{
		m_pLibrary->RegisterCustomizeType(ANCHOR_RETRIEVE, sl::KEYBOARD, sl::K_C);
		m_pLibrary->RegisterCustomizeType(ANCHOR_RETRIEVE, sl::GAMEPAD, sl::XIGAMEPAD_Y  );

	}


	// ダッシュ : DASH
	{
		m_pLibrary->RegisterCustomizeType(DASH, sl::GAMEPAD, sl::XIGAMEPAD_A  );
		m_pLibrary->RegisterCustomizeType(DASH, sl::KEYBOARD, sl::K_LSHIFT);
		m_pLibrary->RegisterCustomizeType(DASH, sl::KEYBOARD, sl::K_RSHIFT);
	}

	// ジャンプ : JUMP
	{
		m_pLibrary->RegisterCustomizeType(JUMP, sl::GAMEPAD, sl::XIGAMEPAD_DPAD_UP);
		m_pLibrary->RegisterCustomizeType(JUMP, sl::GAMEPAD, sl::XIGAMEPAD_LSTICK_UP);
		m_pLibrary->RegisterCustomizeType(JUMP, sl::KEYBOARD, sl::K_UP);
	}

	// しゃがむ : SQUAT
	{

	}

	// 特殊アクション : SPECIAL_ACTION
	{
		m_pLibrary->RegisterCustomizeType(SPECIAL_ACTION, sl::KEYBOARD, sl::K_X);
		m_pLibrary->RegisterCustomizeType(SPECIAL_ACTION, sl::GAMEPAD, sl::XIGAMEPAD_B);
	}

	//  時もどしの左ボタン : TIME_RETURN_L
	{
		m_pLibrary->RegisterCustomizeType(TIME_RETURN_L, sl::KEYBOARD, sl::K_B);
		m_pLibrary->RegisterCustomizeType(TIME_RETURN_L, sl::GAMEPAD, sl::XIGAMEPAD_LTRIGGER);

	}

	//  時もどしの右ボタン : TIME_RETURN_R
	{
		m_pLibrary->RegisterCustomizeType(TIME_RETURN_R, sl::KEYBOARD, sl::K_N);
		m_pLibrary->RegisterCustomizeType(TIME_RETURN_R, sl::GAMEPAD, sl::XIGAMEPAD_RTRIGGER);

	}

	// ポーズボタン : PAUSE
	{
		m_pLibrary->RegisterCustomizeType(PAUSE, sl::GAMEPAD, sl::XIGAMEPAD_START);
		m_pLibrary->RegisterCustomizeType(PAUSE, sl::KEYBOARD, sl::K_TAB);
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
		m_pLibrary->RegisterCustomizeType(MODE_CHANGE, sl::KEYBOARD, sl::K_X);
	}

	// 空間入れ替え : SPACE_CHANGE
	{
		m_pLibrary->RegisterCustomizeType(SPACE_CHANGE, sl::KEYBOARD, sl::K_H);
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
		m_pLibrary->RegisterCustomizeType(TIME_RETURN_L, sl::KEYBOARD, sl::K_B);
	}

	//  時もどしの右ボタン : TIME_RETURN_R
	{
		m_pLibrary->RegisterCustomizeType(TIME_RETURN_R, sl::KEYBOARD, sl::K_N);
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
