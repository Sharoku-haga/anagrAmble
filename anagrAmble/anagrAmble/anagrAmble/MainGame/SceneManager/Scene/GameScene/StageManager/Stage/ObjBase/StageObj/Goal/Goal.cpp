//==================================================================================================================================//
//!< @file		Goal.cpp
//!< @brief		ar::Goalクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "Goal.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

Goal::Goal(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager, const Stage::INDEX_DATA& rStageIndexData)
	: StageObj(pStageDataManager, pCollisionManager, rStageIndexData)
{}

Goal::~Goal()
{}

void Goal::ProcessCollision(int typeID, bool isDeath)
{}

/* Private Functions ------------------------------------------------------------------------------------------ */

void Goal::Run(void)
{}

void Goal::Render(void)
{}

void Goal::HandleEvent(void)
{}

void Goal::CalculatePos(void)
{}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
