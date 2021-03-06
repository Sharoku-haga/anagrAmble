﻿//==================================================================================================================================//
//!< @file		slSoundModeEnum.h
//!< @brief		サウンドで使用する再生方式のenumのヘッダファイル
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef SL_SOUND_MODE_ENUM_H
#define SL_SOUND_MODE_ENUM_H

namespace sl
{

/**音楽の再生方式*/
enum SOUND_MODE
{
	PLAY,			//!< 再生
	PLAYLOOP,		//!< ループ再生
	STOP,			//!< 停止
	RESET,			//!< 初期位置に戻す
	STOP_RESET,		//!< 停めて初期位置戻す
	RESET_PLAY		//!< 初期位置から再生し直す
};

}	// namespace sl

#endif	// SL_SOUND_MODE_ENUM_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
