//==================================================================================================================================//
//!< @file		ObjBase.cpp
//!< @brief		ar::ObjBaseクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "ObjBase.h"
#include "../../../GameEventManager/EventLisner.h"
#include "../../StageDataManager.h"
#include "../CollisionManager.h"

namespace ar
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const float AreaCorrectionVal	= 96.f;		//!< 表示画面エリアの補正値. この値を使用して少し画面外まで描画するようにする。

}

/* Static Variable -------------------------------------------------------------------------------------------- */

sl::SLVECTOR2	ObjBase::m_BasePointPos		= {0.0f, 0.0f};
sl::fRect		ObjBase::m_DisplayArea		= {0.0f, 0.0f, 1920.0f, 0.0f};
const float		ObjBase::m_StageChipSize	= 96.f;

/* Public Functions ------------------------------------------------------------------------------------------- */

ObjBase::ObjBase(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager, const Stage::INDEX_DATA& rStageIndexData)
	: m_pLibrary(sl::ISharokuLibrary::Instance())
	, m_StageIndexData(rStageIndexData)
	, m_pEventLisner(new EventLisner())
	, m_pStageDataManager(pStageDataManager)
	, m_pCollisionManager(pCollisionManager)
{}

ObjBase::~ObjBase(void)
{
	sl::DeleteSafely(m_pEventLisner);
}

void ObjBase::Control(void)
{
	Run();
}

void ObjBase::Draw(void)
{
	// プレイヤーじゃない画面外にあるオブジェクトは描画しない
	if(m_TypeID != PLAYER
		&& m_Pos.x < (m_BasePointPos.x - AreaCorrectionVal)
		|| m_Pos.x > (m_BasePointPos.x + AreaCorrectionVal + m_DisplayArea.m_Right))
	{
		return;
	}
	else
	{
		Render();
	}
}


}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
