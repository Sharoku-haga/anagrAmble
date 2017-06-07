//==================================================================================================================================//
//!< @file		ButtonFactory.h
//!< @brief		ar::ButtonFactoryクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_BUTTON_FACTORY_H
#define AR_BUTTON_FACTORY_H

#include "../SharokuLibrary/sl/sl.h"

namespace ar
{

class Button;

//======================================================================//
//!< anagrAmbleにおけるボタンを生成するファクトリークラス
//!< モノステイトパターン
//======================================================================//
class ButtonFactory
{

public:
	/**
	* ボタンのサイズ変更を行う機能を追加する関数
	* 引数に渡す値は倍率になる。
	* @param[in] pButton	機能を追加したいButtonクラスのインスタンスへのポインタ
	* @param[in] scaleVal	スケール処理の変化量(デフォルト引数 = 1.1f)
	*/
	static	Button*	AddScaleFunction(Button* pButton, float scaleVal = 1.1f);

	/**
	* ボタンの明度を調節する機能を追加する関数
	* 渡す引数の値は明度をどれくらい下げるかの値になる
	* @param[in] pButton		Buttonクラスのインスタンスへのポインタ
	* @param[in] redVal			設定したいr値.デフォルト値は0.5f
	* @param[in] greenVal		設定したいg値.デフォルト値は0.5f
	* @param[in] blueVal		設定したいb値.デフォルト値は0.5f
	* @param[in] alphaVal		設定したいアルファ値.デフォルト値は1.0f
	*/
	static	Button*	AddBrightnessFunction(Button* pButton, float redVal = 0.5f, float greenVal = 0.5f, 
											float blueVal = 0.5f, float alphaVal = 1.0f);


private:
	/** Constructor */
	ButtonFactory(void) = default;

	/** Destructor */
	~ButtonFactory(void) = default;

	SL_DISALLOW_COPY_AND_ASSIGN(ButtonFactory);

};	// class ButtonFactory

}	// namespace ar

#endif	// AR_BUTTON_FACTORY_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
