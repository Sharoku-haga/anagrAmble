//==================================================================================================================================//
//!< @file		ScaleFunction.cpp
//!< @brief		ar::ScaleFunctionクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "ScaleFunction.h"
#include "../SharokuLibrary/sl/sl.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

ScaleFunction::ScaleFunction(Button* pButton, float scaleVal)
	: ButtonFunction(pButton)
	, m_ScaleVal(scaleVal)
	, m_CurrentScaleVal(m_CurrentScaleVal)
{	
	m_ID.m_VtxID = m_pButton->GetVtxID();
}

ScaleFunction::~ScaleFunction(void)
{}

/* Private Functions ------------------------------------------------------------------------------------------ */

void ScaleFunction::Run(void)
{
	m_pButton->Control();

	m_CurrentScaleVal = m_ScaleVal;		// スケール処理の値を更新
}

void ScaleFunction::Render(void)
{
	// スケール処理
	sl::fRect drawVtxRect;		// 描画で使用するRect構造体
	sl::fRect vtxRect = m_pLibrary->GetSizeRect(m_ID.m_VtxID);
	drawVtxRect.m_Left		= vtxRect.m_Left	* m_CurrentScaleVal;
	drawVtxRect.m_Top		= vtxRect.m_Top		* m_CurrentScaleVal;
	drawVtxRect.m_Right		= vtxRect.m_Right	* m_CurrentScaleVal;
	drawVtxRect.m_Bottom	= vtxRect.m_Bottom	* m_CurrentScaleVal;
	m_pLibrary->SetVtxSize(m_ID.m_VtxID, drawVtxRect);

	m_pButton->Draw();

	m_pLibrary->SetVtxSize(m_ID.m_VtxID, vtxRect);
	m_CurrentScaleVal = 1.0f;
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
