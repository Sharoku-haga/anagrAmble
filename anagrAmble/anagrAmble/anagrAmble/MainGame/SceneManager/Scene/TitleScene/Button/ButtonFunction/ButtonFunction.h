//==================================================================================================================================//
//!< @file		ButtonFunction.h
//!< @brief		ar::ButtonFunctionクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_BUTTON_FUNCTION_H
#define AR_BUTTON_FUNCTION_H

#include "../Button.h"

namespace ar
{

//======================================================================//
//!< anagrAmbleにおけるボタンの機能の基底クラス
//======================================================================//
class ButtonFunction : public Button
{

public:
	/** 
	* Constructor 
	* @param[in] pButton 機能を追加したいButtonクラスのインスタンスへのポインタ 
	*/
	explicit ButtonFunction(Button* pButton);

	/** Destructor */
	~ButtonFunction(void);

protected:
	Button*			m_pButton;			//!< 機能を追加したいButtonクラスのインスタンスへのポインタ

	/** 制御処理関数*/
	virtual void Run(void) = 0;

	/** 描画処理関数 */
	virtual void Render(void) = 0;

};	// class ButtonFunction 

}	// namespace ar

#endif	// AR_BUTTON_FUNCTION_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
