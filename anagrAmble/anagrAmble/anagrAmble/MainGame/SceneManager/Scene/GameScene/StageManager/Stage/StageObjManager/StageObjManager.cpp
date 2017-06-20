//==================================================================================================================================//
//!< @file		StageObjManager.cpp
//!< @brief		ar::StageObjManagerクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "StageObjManager.h"
#include "../../StageDataManager.h"
#include "../CollisionManager.h"
#include "StageObjFactory.h"
#include "../SharokuLibrary/sl/sl.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

StageObjManager::StageObjManager(StageDataManager* pStageDataManager, CollisionManager*	pCollisionManager, int texID)
	: m_pStageDataManager(pStageDataManager)
	, m_pCollisionManager(pCollisionManager)
	, m_pStageObjFactory(nullptr)
{
	m_pStageObjFactory = new StageObjFactory(pStageDataManager, pCollisionManager, texID);
}

StageObjManager::~StageObjManager(void)
{
	for(auto& pObj : m_pStageObj)
	{
		sl::DeleteSafely(pObj);
	}

	sl::DeleteSafely(m_pStageObjFactory);
}

void StageObjManager::CreateStageObj(int typeID, const Stage::INDEX_DATA rIndex)
{
	StageObj* pObj = m_pStageObjFactory->CreateStageObj(typeID, rIndex);
	m_pStageObj.push_back(pObj);
	m_pStageDataManager->SetCurrentStageChipData(rIndex.m_YNum, rIndex.m_XNum, pObj);
}

void StageObjManager::InitializeStageObj(void)
{
	for(auto& pObj : m_pStageObj)
	{
		pObj->Initialize();
	}
}

void StageObjManager::Control(void)
{
	for(auto& pObj : m_pStageObj)
	{
		pObj->Control();
	}
}

void StageObjManager::Draw(void)
{
	for(auto& pObj : m_pStageObj)
	{
		pObj->Draw();
	}
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
