//==================================================================================================================================//
//!< @file		ScaleFunction.h
//!< @brief		ar::ScaleFunctionクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef SCALE_FUNCTION_H
#define SCALE_FUNCTION_H

#include "ButtonFunction.h"

namespace ar
{

//======================================================================//
//!< anagrAmbleにおけるボタンのサイズを調節する機能のクラス
//!< @attention BasicButtonクラスと一緒に必ず使用すること
//======================================================================//
class ScaleFunction : public ButtonFunction
{

public:
	/**
	* Constructor
	* @param[in] pButton	Buttonクラスのインスタンスへのポインタ
	* @param[in] scaleVal	スケール処理の変化量(デフォルト引数 = 1.1f)
	*/
	ScaleFunction(Button* pButton, float scaleVal = 1.1f);

	/** Destructor */
	~ScaleFunction(void);

private:
	const float		m_ScaleVal;				//!< スケール処理に使用する変化量. 数値が変動しないためconst
	float			m_CurrentScaleVal;		//!< 現在のスケール処理の変化量. 毎フレーム変化する値. 制御関数がよばれなければ値は0

	/** 制御処理関数 */
	virtual void Run(void)override;

	/** 描画処理関数 */
	virtual void Render(void)override;

};	// class ScaleFunction

}	// namespace ar

#endif	// SCALE_FUNCTION_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
