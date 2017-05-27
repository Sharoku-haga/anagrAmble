﻿//==================================================================================================================================//
//!< @file		Player.cpp
//!< @brief		ar::Playerクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "Player.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

Player::Player(const Stage::INDEX_DATA& rStageIndexData)
	: ObjBase(rStageIndexData)
{}

Player::~Player()
{}

void Player::ProcessCollision(int typeID, bool isDeath)
{}

/* Private Functions ------------------------------------------------------------------------------------------ */

void Player::Run(void)
{}

void Player::Render(void)
{}

void Player::HandleEvent(void)
{}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//

