﻿//==================================================================================================================================//
//!< @file		LogoScene.cpp
//!< @brief		LogoSceneクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "LogoScene.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

LogoScene::LogoScene(void)
{}

LogoScene::~LogoScene(void)
{}

/* Private Functions ------------------------------------------------------------------------------------------ */

Scene::ID LogoScene::Control(void)
{

	return Scene::LOGO;
}

void LogoScene::Draw(void)
{

}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
