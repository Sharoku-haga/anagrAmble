//==================================================================================================================================//
//!< @file		BrightnessFunction.cpp
//!< @brief		ar::BrightnessFunctionクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "BrightnessFunction.h"
#include "../SharokuLibrary/sl/sl.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

BrightnessFunction::BrightnessFunction(Button* pButton, float redVal, float greenVal, 
						float blueVal, float alphaVal)
	: ButtonFunction(pButton)
	, m_BrightnessVal(redVal, greenVal, blueVal, alphaVal)
	, m_BrightnessValMax(1.0f, 1.0f, 1.0f, 1.0f)
	, m_CurrentBrightnessVal(redVal, greenVal, blueVal, alphaVal)
{
	m_ID.m_VtxID = m_pButton->GetVtxID();
}

BrightnessFunction::~BrightnessFunction(void)
{}

/* Private Functions ------------------------------------------------------------------------------------------ */

void BrightnessFunction::Run(void)
{
	m_pButton->Control();
	m_CurrentBrightnessVal = m_BrightnessValMax;		// 明暗処理値の更新.明度を挙げる
}

void BrightnessFunction::Render(void)
{
	m_pLibrary->SetVtxColor(m_ID.m_VtxID, m_CurrentBrightnessVal.m_RedVal, m_CurrentBrightnessVal.m_GreenVal
							, m_CurrentBrightnessVal.m_BlueVal, m_CurrentBrightnessVal.m_AlphaVal);
	m_pButton->Draw();

	// 明度を元に戻す
	m_CurrentBrightnessVal = m_BrightnessVal;
	m_pLibrary->SetVtxColor(m_ID.m_VtxID, m_CurrentBrightnessVal.m_RedVal, m_CurrentBrightnessVal.m_GreenVal
							, m_CurrentBrightnessVal.m_BlueVal, m_CurrentBrightnessVal.m_AlphaVal);
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
