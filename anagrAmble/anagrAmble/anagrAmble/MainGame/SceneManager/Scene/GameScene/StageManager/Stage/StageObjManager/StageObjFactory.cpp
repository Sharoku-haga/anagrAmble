//==================================================================================================================================//
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

StageObjFactory::~StageObjFactory()
{}

StageObj* StageObjFactory::CreateStageObj(int typeID, const Stage::INDEX_DATA rIndex)
{
	StageObj* pStageObj = nullptr;
	sl::DrawingID id;

	switch(typeID)
	{

	case ObjBase::NORMAL_B:	
		id.m_VtxID = m_VtxID[ObjBase::NORMAL_B];
		id.m_TexID = m_TexID;
		pStageObj = new NormalBlock(m_pStageDataManager, m_pCollisionManager, rIndex, id);
		break;

	case ObjBase::GROUND_B:
		id.m_VtxID = m_VtxID[ObjBase::GROUND_B];
		id.m_TexID = m_TexID;
		pStageObj = new GroundBlock(m_pStageDataManager, m_pCollisionManager, rIndex, id);
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
	m_VtxID.resize(ObjBase::STAGE_OBJ_ID_MAX);

	// 通常ブロック
	{
		sl::fRect	uv = { 0.0f, 0.0f, 0.05f, 0.088f};
		m_VtxID[ObjBase::NORMAL_B] = m_pLibrary->CreateVertex2D(m_BlockSize, uv);
	}

	// 地面ブロック
	{
		sl::fRect	uv = { 0.05f, 0.0f, 0.1f, 0.088f};
		m_VtxID[ObjBase::GROUND_B] = m_pLibrary->CreateVertex2D(m_BlockSize, uv);
	}
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
