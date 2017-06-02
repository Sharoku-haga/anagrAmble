//==================================================================================================================================//
//!< @file		Player.cpp
//!< @brief		ar::Playerクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "Player.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

Player::Player(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager, const Stage::INDEX_DATA& rStageIndexData)
	: ObjBase(pStageDataManager, pCollisionManager, rStageIndexData)
{}

Player::~Player()
{}

void Player::ProcessCollision(int typeID, bool isDeath)
{}

/* Private Functions ------------------------------------------------------------------------------------------ */

void Player::HandleEvent(void)
{}

void Player::CalculatePos(void)
{}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//

