﻿//==================================================================================================================================//
//!< @file		Enemy.cpp
//!< @brief		ar::Enemyクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "Enemy.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

Enemy::Enemy(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager, const Stage::INDEX_DATA& rStageIndexData)
	: ObjBase(pStageDataManager, pCollisionManager, rStageIndexData)
{}

Enemy::~Enemy()
{}

void Enemy::ProcessCollision(const CollisionManager::CollisionData& rData)
{}

/* Private Functions ------------------------------------------------------------------------------------------ */

void Enemy::HandleEvent(void)
{}

void Enemy::CalculatePos(void)
{}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
