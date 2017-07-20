﻿//==================================================================================================================================//
//!< @file		GameSceneSoundID.h
//!< @brief		GameSceneで使用するサウンドIDのヘッダファイル
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_GAME_SCENE_SOUND_ID_H 
#define AR_GAME_SCENE_SOUND_ID_H

/** GameSceneで使用するSoundのID */
enum class GAME_SCENE_SOUND_ID : int
{
	BACK_GROUND,				//!< バック音
	CHANGE_SPACE,				//!< 空間入れ替え音
	RETURN_CHAGED_SPACE,		//!< とき戻し音
	ANCHOR,						//!< アンカーセット音
	RUN,						//!< 走る音
	JUMP,						//!< シャンプ音
	WALK,						//!< 歩く音
	DEATH,						//!< 死亡音
	REVIVE,						//!< 蘇り音
	HIT,						//!< ヒット音
	LEVER,						//!< レバー音
	EMBLME_ON,					//!< 紋章ON音
	ELECTICAL,					//!< 電気音
	GET_KEY,					//!< 鍵を手に入れた音
	PRESSURE_SENSITIVE_ON,		//!< 感圧音
	SELECT,						//!< 選択音
	DOOR,						//!< ドアの音

	ENTER = 99,					//!< 決定音

};

#endif	// AR_GAME_SCENE_SOUND_ID_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//