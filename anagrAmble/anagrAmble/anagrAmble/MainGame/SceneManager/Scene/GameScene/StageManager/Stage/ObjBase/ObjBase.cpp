//==================================================================================================================================//
//!< @file		ObjBase.cpp
//!< @brief		ar::ObjBaseクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "ObjBase.h"
#include "../../../GameEventManager/EventListener.h"
#include "../../StageDataManager.h"
#include "../CollisionManager.h"
#include"../StageEffect/SandwichEffect.h"

namespace ar
{

/* Static Variable -------------------------------------------------------------------------------------------- */

sl::SLVECTOR2	ObjBase::m_BasePointPos		= {0.0f, 0.0f};
sl::fRect		ObjBase::m_DisplayArea		= {0.0f, 0.0f, 0.0f, 0.0f};
float			ObjBase::m_StageChipSize	= 0.0f;

namespace
{

const float		Speed = 1.0f;

}

/* Public Functions ------------------------------------------------------------------------------------------- */

ObjBase::ObjBase(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
				, const Stage::INDEX_DATA& rStageIndexData)
	: m_pLibrary(sl::ISharokuLibrary::Instance())
	, m_StageIndexData(rStageIndexData)
	, m_pEventListener(new EventListener())
	, m_pStageDataManager(pStageDataManager)
	, m_pCollisionManager(pCollisionManager)
	, m_pSandwichEffect(nullptr)
	, m_HasBeenSandwiched(false)
{}

ObjBase::~ObjBase(void)
{
	sl::DeleteSafely(&m_pEventListener);
}

const sl::fRect& ObjBase::GetCurrentRectData(void) 
{ 
	m_CurrentRectData.m_Left	= m_Pos.x + m_RectSize.m_Left; 
	m_CurrentRectData.m_Top		= m_Pos.y + m_RectSize.m_Top;
	m_CurrentRectData.m_Right	= m_Pos.x + m_RectSize.m_Right;
	m_CurrentRectData.m_Bottom	= m_Pos.y + m_RectSize.m_Bottom;
	return m_CurrentRectData; 
}

void ObjBase::ApplySandwichEffect(const sl::SLVECTOR2& rSandwichedSpaceCenterPos)
{
	if(m_pSandwichEffect == nullptr)
	{
		return;
	}

	m_HasBeenSandwiched = true;
	m_pSandwichEffect->ProcessBeforeEffectStart(rSandwichedSpaceCenterPos);
	// 不透明にする
	m_pLibrary->SetVtxColor(m_DrawingID.m_VtxID, 1.0f, 1.0f, 1.0f, 0.6f);
}

void ObjBase::DetachSandwichEffect(void)
{
	m_HasBeenSandwiched = false;
	m_pLibrary->SetVtxColor(m_DrawingID.m_VtxID, 1.0f, 1.0f, 1.0f, 1.0f);
}

bool ObjBase::EndSandwichEffect(void)
{
	if(m_pSandwichEffect != nullptr)
	{
		return m_pSandwichEffect->EndEffect();
	}

	return false;
}


}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
