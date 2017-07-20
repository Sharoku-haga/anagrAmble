﻿//==================================================================================================================================//
//!< @file		ControllerEnum.h
//!< @brief		Controllerに関係するenumのヘッダファイル
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_CONTROLLER_ENUM_H
#define AR_CONTROLLER_ENUM_H

namespace ar
{

/** 
* anagrAmbleにおけるコントローラーのボタン判定によるアクションイベントの種類
* @attention ライブラリのカスタマイズでボタン設定しておくこと
*/
enum CONTROLLER_ACTION_EVENT
{
	UP,					//!< 上
	DOWN,				//!< 下
	RIGHT,				//!< 右
	LEFT,				//!< 左
	ENTER,				//!< 決定
	MODE_CHANGE,		//!< モード切替
	MODE_RELEASE,		//!< モード解除
	SPACE_CHANGE,		//!< スぺース入れ替え
	ANCHOR_SET,			//!< アンカー設置アクション
	ANCHOR_RETRIEVE,	//!< アンカー回収アクション	
	DASH,				//!< ダッシュ
	JUMP,				//!< ジャンプ
	SQUAT,				//!< しゃがむ
	SPECIAL_ACTION,		//!< 特殊アクション
	TIME_RETURN_L,		//!< とき戻しボタン左。※ 下記の右と同時押しで、初めて時が戻せる点に注意
	TIME_RETURN_R,		//!< とき戻しボタン右。※ 上記の左と同時押しで、初めて時が戻せる点に注意
	PAUSE,				//!< ポーズ
};

}	// namespace ar

#endif	// AR_CONTROLLER_ENUM_H


//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
