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

namespace ar
{

/* Static Variable -------------------------------------------------------------------------------------------- */

sl::SLVECTOR2	ObjBase::m_BasePointPos		= {0.0f, 0.0f};
sl::fRect		ObjBase::m_DisplayArea		= {0.0f, 0.0f, 1920.0f, 0.0f};
float			ObjBase::m_StageChipSize	= 0.0f;

/* Public Functions ------------------------------------------------------------------------------------------- */

ObjBase::ObjBase(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
				, const Stage::INDEX_DATA& rStageIndexData)
	: m_pLibrary(sl::ISharokuLibrary::Instance())
	, m_StageIndexData(rStageIndexData)
	, m_pEventListener(new EventListener())
	, m_pStageDataManager(pStageDataManager)
	, m_pCollisionManager(pCollisionManager)
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


}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
