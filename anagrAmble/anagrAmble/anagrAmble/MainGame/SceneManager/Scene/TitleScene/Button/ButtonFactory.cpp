//==================================================================================================================================//
//!< @file		ButtonFactory.cpp
//!< @brief		ar::ButtonFactoryクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "ButtonFactory.h"
#include "ButtonFunction/ScaleFunction.h"
#include "ButtonFunction/BrightnessFunction.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

Button*	ButtonFactory::AddScaleFunction(Button* pButton, float scaleVal)
{
	Button* pNewButton = nullptr;
	pNewButton = new ScaleFunction(pButton, scaleVal);
	return pNewButton;
}

Button*	ButtonFactory::AddBrightnessFunction(Button* pButton, float redVal, float greenVal, 
											float blueVal, float alphaVal)
{
	Button* pNewButton = nullptr;
	pNewButton = new BrightnessFunction(pButton, redVal, greenVal, blueVal, alphaVal);
	return pNewButton;
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
