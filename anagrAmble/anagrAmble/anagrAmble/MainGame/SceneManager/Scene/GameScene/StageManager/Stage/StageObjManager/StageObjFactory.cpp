﻿//==================================================================================================================================//
//!< @file		StageObjFactory.h
//!< @brief		ar::StageObjFactoryクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "StageObjFactory.h"
#include "../../StageDataManager.h"
#include "../CollisionManager.h"
#include "../ObjBase/StageObj/Block/NormalBlock.h"
#include "../ObjBase/StageObj/Block/GroundBlock.h"
#include "../ObjBase/StageObj/Block/ElectricalBlock.h"
#include "../ObjBase/StageObj/Block/PressureSensitiveBlock.h"
#include "../ObjBase/StageObj/Block/LightRoadBlock.h"
#include "../ObjBase/StageObj/Gimmik/Lever.h"
#include "../ObjBase/StageObj/Goal/Goal.h"
#include "../ObjBase/StageObj/Goal/GoalKey.h"
#include "../ObjBase/StageObj/Block/PairOfEmblemBlock.h"
#include "../ObjBase/StageObj/Block/SetOfThreeEmblemBlock.h"
#include "../ObjBase/StageObj/Gimmik/RevolvingLightDoor.h"
#include "../ObjBase/StageObj/Gimmik/LightDoor.h"
#include "../ObjBase//StageObj/Block/BeltConverBlock.h"
#include "../ObjBase/StageObj/Block/SpearBlock/SpearBlock.h"
#include "../ObjBase/StageObj/Block/LightBlock.h"
#include "../ObjBase/StageObj/Entrance/Entrance.h"

namespace ar
{

StageObjFactory::StageObjFactory(StageDataManager* pStageDataManager, CollisionManager*	pCollisionManager, int texID)
	: m_pLibrary(sl::ISharokuLibrary::Instance())
	, m_pStageDataManager(pStageDataManager)
	, m_pCollisionManager(pCollisionManager)
	, m_TexID(texID)
{
	// ブロックサイズのRect構造体を作成
	float chipSize = m_pStageDataManager->GetStageChipSize();
	m_BlockSize.m_Left		= -(chipSize / 2);
	m_BlockSize.m_Top		= -(chipSize / 2);
	m_BlockSize.m_Right		= (chipSize / 2);
	m_BlockSize.m_Bottom	= (chipSize / 2);

	InitializeVertex();
}

/* Public Functions ------------------------------------------------------------------------------------------- */

StageObjFactory::~StageObjFactory(void)
{
	m_pLibrary->ReleaseVertex2D(m_GroundBlockVtxID);
}

StageObj* StageObjFactory::CreateStageObj(int typeID, const Stage::INDEX_DATA rIndex)
{
	StageObj* pStageObj = nullptr;

	switch(typeID)
	{

	case ObjBase::NORMAL_B:	
		pStageObj = new NormalBlock(m_pStageDataManager, m_pCollisionManager, rIndex, m_TexID);	
		break;

	case ObjBase::GROUND_B:
	{
		sl::DrawingID id;
		id.m_VtxID = m_GroundBlockVtxID;
		id.m_TexID = m_TexID;
		pStageObj = new GroundBlock(m_pStageDataManager, m_pCollisionManager, rIndex, id);
	}
		break;

	case ObjBase::ELECTICAL_B:
		pStageObj = new ElectricalBlock(m_pStageDataManager, m_pCollisionManager, rIndex, m_TexID);
		break;

	case ObjBase::PRESSURE_SENSITIVE_B:
		pStageObj = new PressureSensitiveBlock(m_pStageDataManager, m_pCollisionManager, rIndex, m_TexID);
		break;

	case ObjBase::LIGHT_ROAD_B:
		pStageObj = new LightRoadBlock(m_pStageDataManager, m_pCollisionManager, rIndex, m_TexID);
		break;

	case ObjBase::LEVER:
		pStageObj = new Lever(m_pStageDataManager, m_pCollisionManager, rIndex, m_TexID);
		break;

	case ObjBase::GOAL:
		pStageObj = new Goal(m_pStageDataManager, m_pCollisionManager, rIndex, m_TexID, ObjBase::GOAL);
		break;

	case ObjBase::LOCKED_GOAL:
		pStageObj = new Goal(m_pStageDataManager, m_pCollisionManager, rIndex, m_TexID, ObjBase::LOCKED_GOAL);
		break;

	case ObjBase::GOAL_KEY:
		pStageObj = new GoalKey(m_pStageDataManager, m_pCollisionManager, rIndex, m_TexID);
		break;

	case ObjBase::PAIR_OF_EMBLME_B_R:
		pStageObj = new PairOfEmblemBlock(m_pStageDataManager, m_pCollisionManager, rIndex, m_TexID, ObjBase::PAIR_OF_EMBLME_B_R);
		break;

	case ObjBase::PAIR_OF_EMBLME_B_L:
		pStageObj = new PairOfEmblemBlock(m_pStageDataManager, m_pCollisionManager, rIndex, m_TexID, ObjBase::PAIR_OF_EMBLME_B_L);
		break;

	case ObjBase::SET_OF_THREE_EMBLME_B_R:
		pStageObj = new SetOfThreeEmblemBlock(m_pStageDataManager, m_pCollisionManager, rIndex, m_TexID, ObjBase::SET_OF_THREE_EMBLME_B_R);
		break;

	case ObjBase::SET_OF_THREE_EMBLME_B_F:
		pStageObj = new SetOfThreeEmblemBlock(m_pStageDataManager, m_pCollisionManager, rIndex, m_TexID, ObjBase::SET_OF_THREE_EMBLME_B_F);
		break;

	case ObjBase::SET_OF_THREE_EMBLME_B_L:
		pStageObj = new SetOfThreeEmblemBlock(m_pStageDataManager, m_pCollisionManager, rIndex, m_TexID, ObjBase::SET_OF_THREE_EMBLME_B_L);
		break;

	case ObjBase::REVOLVING_LIGHT_DOOR_HORIZONTAL:
		pStageObj = new RevolvingLightDoor(m_pStageDataManager, m_pCollisionManager, rIndex, m_TexID, ObjBase::REVOLVING_LIGHT_DOOR_HORIZONTAL);
		break;

	case ObjBase::REVOLVING_LIGHT_DOOR_VERTICAL:
		pStageObj = new RevolvingLightDoor(m_pStageDataManager, m_pCollisionManager, rIndex, m_TexID, ObjBase::REVOLVING_LIGHT_DOOR_VERTICAL);
		break;

	case ObjBase::LIGHT_DOOR_UP:
		pStageObj = new LightDoor(m_pStageDataManager, m_pCollisionManager, rIndex, m_TexID, ObjBase::LIGHT_DOOR_UP);
		break;

	case ObjBase::LIGHT_DOOR_DOWN:
		pStageObj = new LightDoor(m_pStageDataManager, m_pCollisionManager, rIndex, m_TexID, ObjBase::LIGHT_DOOR_DOWN);
		break;

	case ObjBase::LIGHT_DOOR_RIGHT:
		pStageObj = new LightDoor(m_pStageDataManager, m_pCollisionManager, rIndex, m_TexID, ObjBase::LIGHT_DOOR_RIGHT);
		break;

	case ObjBase::LIGHT_DOOR_LEFT:
		pStageObj = new LightDoor(m_pStageDataManager, m_pCollisionManager, rIndex, m_TexID, ObjBase::LIGHT_DOOR_LEFT);
		break;

	case ObjBase::LIGHT_B:
		pStageObj = new LightBlock(m_pStageDataManager, m_pCollisionManager, rIndex, m_TexID);
		break;

	case ObjBase::BELT_CONVER_B_L:
		pStageObj = new BeltConverBlock(m_pStageDataManager, m_pCollisionManager, rIndex, m_TexID, ObjBase::BELT_CONVER_B_L);
		break;

	case ObjBase::BELT_CONVER_B_R:
		pStageObj = new BeltConverBlock(m_pStageDataManager, m_pCollisionManager, rIndex, m_TexID, ObjBase::BELT_CONVER_B_R);
		break;

	case ObjBase::SPEAR_B:
		pStageObj = new SpearBlock(m_pStageDataManager, m_pCollisionManager, rIndex, m_TexID);
		break;

	case ObjBase::ENTRANCE:
		pStageObj = new Entrance(m_pStageDataManager, m_pCollisionManager, rIndex, m_TexID);
		break;

	default:
		// do nothing
		break;
	}

	return pStageObj;
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void StageObjFactory::InitializeVertex(void)
{
	// 地面ブロックのVertexを作成
	{
		sl::fRect	uv = { 0.05f, 0.0f, 0.1f, 0.088f};
		m_GroundBlockVtxID = m_pLibrary->CreateVertex2D(m_BlockSize, uv);
	}
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
