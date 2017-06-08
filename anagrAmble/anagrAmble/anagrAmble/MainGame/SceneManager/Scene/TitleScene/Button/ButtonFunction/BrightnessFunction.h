//==================================================================================================================================//
//!< @file		BrightnessFunction.h
//!< @brief		ar::BrightnessFunctionクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_BRIGHTNESS_FUNCTION_H
#define AR_BRIGHTNESS_FUNCTION_H

#include "ButtonFunction.h"

namespace ar
{

//======================================================================//
//!< anagrAmbleにおけるボタンの色の明度を切り替える機能のクラス
//!< 渡す引数の値は明度をどれくらい下げるかの値になる
//!< @attention BasicButtonクラスと一緒に必ず使用すること
//======================================================================//
class BrightnessFunction : public ButtonFunction
{

public:
	/** 
	* Constructor 
	* @param[in] pButton		機能を追加したいButtonクラスのインスタンスへのポインタ 
	* @param[in] redVal			設定したいr値.デフォルト値は0.5f
	* @param[in] greenVal		設定したいg値.デフォルト値は0.5f
	* @param[in] blueVal		設定したいb値.デフォルト値は0.5f
	* @param[in] alphaVal		設定したいアルファ値.デフォルト値は1.0f
	*/
	BrightnessFunction(Button* pButton, float redVal = 0.5f, float greenVal = 0.5f, 
						float blueVal = 0.5f, float alphaVal = 1.0f);

	/** Destructor */
	~BrightnessFunction(void);

private:
	/** 色の値を格納する構造体*/
	struct ColorVal
	{
		float		m_RedVal;		//!< r値
		float		m_GreenVal;		//!< g値
		float		m_BlueVal;		//!< b値
		float		m_AlphaVal;		//!< alpha値

		ColorVal(float redVal, float greenVal, float blueVal, float alphaVal)
			: m_RedVal(redVal)
			, m_GreenVal(greenVal)
			, m_BlueVal(blueVal)
			, m_AlphaVal(alphaVal)
		{}
	};

	const ColorVal		m_BrightnessVal;				//!< 明度処理のデフォルト値
	const ColorVal		m_BrightnessValMax;				//!< 明度最大値. Constructor内にて初期化.全て値が1.0ｆ
	ColorVal			m_CurrentBrightnessVal;			//!< 現在の明度処理を行う値
	

	/** 制御処理関数 */
	virtual void Run(void)override;

	/** 描画処理関数 */
	virtual void Render(void)override;

};	// class BrightnessFunction

}	// namespace ar

#endif	// AR_BRIGHTNESS_FUNCTION_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
