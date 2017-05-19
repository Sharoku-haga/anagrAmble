//==================================================================================================================================//
//!< @file		BasicButton.h
//!< @brief		ar::BasicButtonクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_BASIC_BUTTON_H
#define AR_BASIC_BUTTON_H

#include "Button.h"
#include "../SharokuLibrary/sl/Common/slStruct.h"
#include "../SharokuLibrary/sl/Common/slVECTOR/slVECTOR2.h"

namespace ar
{

//======================================================================//
//!< anagrAmbleにおけるボタンの描画だけを行うクラス
//======================================================================//
class BasicButton : public Button
{

public:
	/** 
	* Constructor
	* @param[in] texID	テクスチャーID
	* @param[in] rSize	ボタンのサイズ
	* @param[in] rUv	UV値
	* @param[in] rPos	位置座標
	*/
	BasicButton(int texID, const sl::fRect& rSize, const sl::fRect& rUv, const sl::SLVECTOR2& rPos);

	/** Destructor */
	virtual ~BasicButton(void);

private:
	sl::SLVECTOR2			m_Pos;			//!< 位置座標

	/** 
	* 処理実行関数 
	* Control()におけるメイン処理
	*/
	virtual void Run(void)override;

	/** 
	* 描画処理関数
	* Draw()におけるメイン処理
	*/
	virtual void Render(void)override;

};	// class BasicButton

}	// namespace ar

#endif	// AR_BASIC_BUTTON_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
