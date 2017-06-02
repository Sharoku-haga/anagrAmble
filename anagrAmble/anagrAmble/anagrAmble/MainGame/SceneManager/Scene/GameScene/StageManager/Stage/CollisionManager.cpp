//==================================================================================================================================//
//!< @file		CollisionManager.cpp
//!< @brief		ar::CollisionManagerクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include <cmath> 
#include "CollisionManager.h"
#include "../StageDataManager.h"
#include "ObjBase/ObjBase.h"


namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

CollisionManager::CollisionManager(StageDataManager*	pStageDataManager)
	: m_pStageDataManager(pStageDataManager)
{}

CollisionManager::~CollisionManager(void)
{}

void CollisionManager::UpDate(void)
{
	unsigned int checkObjCount = m_pStageObj.size();

	if(checkObjCount == 0)
	{
		return;
	}

	// プレイヤーの衝突判定処理
	for(unsigned int i = 0; i < checkObjCount; ++i)
	{
		CheckCollisionPlayer(m_pStageObj[i]);
	}

	// データをクリアする
	m_pStageObj.clear();
	std::vector<ObjBase*>().swap(m_pStageObj);
}

void CollisionManager::SetObjBasePointer(ObjBase* pObj)
{
	m_pStageObj.push_back(pObj);
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void CollisionManager::CheckCollisionPlayer(ObjBase* pObj)
{
	if(CheckCollisionRect(m_pPlayer, pObj))
	{	
		CollisionData playerCollisionData;
		playerCollisionData.m_ObjType	= pObj->GetTypeID();
		playerCollisionData.m_ObjPos	= pObj->GetPos();
		playerCollisionData.m_ObjRect	= pObj->GetCurrentRectData();
		m_pPlayer->ProcessCollision(playerCollisionData);

		CollisionData objCollisionData;
		objCollisionData.m_ObjType	= m_pPlayer->GetTypeID();
		objCollisionData.m_ObjPos	= m_pPlayer->GetPos();
		objCollisionData.m_ObjRect	= m_pPlayer->GetCurrentRectData();
		pObj->ProcessCollision(objCollisionData);
	}
}

bool CollisionManager::CheckCollisionCircle(ObjBase* pObjA, ObjBase* pObjB)
{

	sl::fRect objARect = pObjA->GetRectSize();
	sl::fRect objBRect = pObjB->GetRectSize();

	float lengthX = (objARect.m_Right - objARect.m_Left) /2 + (objBRect.m_Right - objBRect.m_Left) /2;
	float lengthY = (objARect.m_Right - objARect.m_Left) /2 + (objBRect.m_Right - objBRect.m_Left) /2;

	if(std::abs((pObjA->GetPos().x - pObjB->GetPos().x)) < lengthX
		|| std::abs((pObjA->GetPos().y - pObjB->GetPos().y)) < lengthY)
	{
		return true;
	}

	return false;
}

bool CollisionManager::CheckCollisionRect(ObjBase* pObjA, ObjBase* pObjB)
{
	sl::fRect objARect = pObjA->GetCurrentRectData();
	sl::fRect objBRect = pObjB->GetCurrentRectData();

	if(objARect.m_Right > objBRect.m_Left
		&& objARect.m_Top < objBRect.m_Bottom
		&& objARect.m_Left < objBRect.m_Right
		&& objARect.m_Bottom > objBRect.m_Top)
	{
		return true;
	}

	return false;
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
