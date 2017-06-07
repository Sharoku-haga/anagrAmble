﻿//==================================================================================================================================//
//!< @file		ButtonFunction.cpp
//!< @brief		ar::ButtonFunctionクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "ButtonFunction.h"
#include "../SharokuLibrary/sl/sl.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

ButtonFunction::ButtonFunction(Button* pButton)
	: m_pButton(pButton)
{}

ButtonFunction::~ButtonFunction(void)
{
	sl::DeleteSafely(m_pButton);
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
