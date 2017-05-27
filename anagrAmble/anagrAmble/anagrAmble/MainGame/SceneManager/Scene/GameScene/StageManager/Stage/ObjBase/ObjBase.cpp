//==================================================================================================================================//
//!< @file		ObjBase.cpp
//!< @brief		ar::ObjBaseクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "ObjBase.h"

namespace ar
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const float AreaCorrectionVal = 96.f;		//!< 表示画面エリアの補正値. この値を使用して少し画面外まで描画するようにする。

}

/* Static Variable -------------------------------------------------------------------------------------------- */

sl::SLVECTOR2	ObjBase::m_BasePointPos = {0.0f, 0.0f};
sl::fRect		ObjBase::m_DisplayArea  = {0.0f, 0.0f, 0.0f, 0.0f};


/* Public Functions ------------------------------------------------------------------------------------------- */

ObjBase::ObjBase(const Stage::INDEX_DATA& rStageIndexData)
	: m_StageIndexData(rStageIndexData)
{}

ObjBase::~ObjBase(void)
{}

void ObjBase::Control(void)
{
	Run();
}

void ObjBase::Draw(void)
{
	// プレイヤーじゃない画面外にあるオブジェクトは描画しない
	if(m_TypeID != PLAYER
		&& m_Pos.x < (m_BasePointPos.x - AreaCorrectionVal)
		&& m_Pos.x > (m_BasePointPos.x + AreaCorrectionVal + m_DisplayArea.m_Right))
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
