//==================================================================================================================================//
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

Enemy::~Enemy(void)
{}

void Enemy::Initialize(void)
{}

void Enemy::ChangeStagePos(short yIndexNum, short xIndexNum)
{

}

void Enemy::ProcessCollision(const CollisionManager::CollisionData& rData)
{}

/* Private Functions ------------------------------------------------------------------------------------------ */

void Enemy::HandleEvent(void)
{}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
