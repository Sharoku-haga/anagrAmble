//==================================================================================================================================//
//!< @file		GoalKey.cpp
//!< @brief		ar::GoalKeyクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "GoalKey.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

GoalKey::GoalKey(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager, const Stage::INDEX_DATA& rStageIndexData)
	: StageObj(pStageDataManager, pCollisionManager, rStageIndexData)
{}

GoalKey::~GoalKey()
{}

void GoalKey::ProcessCollision(int typeID, bool isDeath)
{}

/* Private Functions ------------------------------------------------------------------------------------------ */

void GoalKey::Run(void)
{}

void GoalKey::Render(void)
{}

void GoalKey::HandleEvent(void)
{}

void GoalKey::CalculatePos(void)
{}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
