﻿//==================================================================================================================================//
//!< @file		slBuild.h
//!< @brief		ビルド時の設定を行うヘッダファイル
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef SL_BUILD_H
#define SL_BUILD_H


//======================================================================//
//!< Setting
//!< ライブラリの初期設定を行う
//======================================================================//

/*  GraphicsAPI ----------------------------------------------------------------------------------------------- */

#define DIRECT_X_11							// DirectX11を使用する

/* Screen ----------------------------------------------------------------------------------------------------- */

 #define ADJUST_CLIENT_SIZE					// クライアント領域を調整する(クライアント領域を指定したサイズに変換する場合)
 //#define FULL_SCREEN						// フルスクリーン. コメントアウトを行うと実行開始時はウィンドウモードになる(変更は可能)

/* Stencil Test ----------------------------------------------------------------------------------------------- */

//#define STRAT_STECIL_TEST_ON				//  ステンシルテストをONにした状態でプログラムを実行する

/* Shader Version --------------------------------------------------------------------------------------------- */

//#define SHADER_VERSION_4_0				// シェーダーバージョン4.0
#define SHADER_VERSION_5_0					// シェーダーバージョン5.0

/* Input Device ----------------------------------------------------------------------------------------------- */

#define USING_KEY_DEVICE					// キーボードデバイスを使用する		
//#define USING_DI_GAMEPAD					// DirectInputのゲームパッドを使用する	
#define USING_XI_GAMEPAD					// XInputのゲームパッドを使用する

#endif	// SL_BUILD_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
