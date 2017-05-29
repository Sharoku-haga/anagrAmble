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

}

/* Public Functions ------------------------------------------------------------------------------------------- */

StageObjFactory::~StageObjFactory()
{}

StageObj* StageObjFactory::CreateStageObj(int typeID, const Stage::INDEX_DATA rIndex)
{
	StageObj* pStageObj = nullptr;

	switch(typeID)
	{

	case ObjBase::NORMAL_BLOCK:
	{
		sl::DrawingID id;
		sl::fRect	uv = { 0.0f, 0.0f, 0.05f, 0.088f};
		id.m_VtxID = m_pLibrary->CreateVertex2D(m_BlockSize, uv);
		id.m_TexID = m_TexID;
		pStageObj = new NormalBlock(rIndex, id);
	}
		break;

	default:
		// do nothing
		break;
	}

	return pStageObj;
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
