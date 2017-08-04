//==================================================================================================================================//
//!< @file		SmallNumberDrawer.cpp
//!< @brief		SmallNumberDrawerクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

#include "SmallNumberDrawer.h"

namespace ar
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const		int			TuCount								= 10;									// tu方向のカウント数
const		float		TuScrollVal							= 0.03125f;								// tuのスクロール値

}

/* Public Functions ------------------------------------------------------------------------------------------- */

SmallNumberDrawer::SmallNumberDrawer(int texID)
	: NumberDrawer(texID)
{
	m_RectSize.m_Left	= -24.0f;
	m_RectSize.m_Top	= -24.0f;
	m_RectSize.m_Right	=  24.0f;
	m_RectSize.m_Bottom =  24.0f;
}

SmallNumberDrawer::~SmallNumberDrawer(void)
{
	for(auto& drawingID : m_NumDrawingID)
	{
		m_pLibrary->ReleaseVertex2D(drawingID.m_VtxID);
	}
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void SmallNumberDrawer::CreateNumDrawingID(void)
{
	int currentTuCount = 0;			// 現在カウントしているTU方向のカウント数

	sl::fRect currentUV;			// ループにしようするUV値いれもの
	sl::fRect startUV = { 0.0f, 0.195f, TuScrollVal, 0.292f };		// 開始UV値

	for(int i = 0; i < m_NumberCount; ++i)
	{
		if(currentTuCount == TuCount)
		{
			return;
		}

		currentUV.m_Left	= startUV.m_Left + TuScrollVal * currentTuCount;
		currentUV.m_Top		= startUV.m_Top;
		currentUV.m_Right	= startUV.m_Right + TuScrollVal* currentTuCount;
		currentUV.m_Bottom	= startUV.m_Bottom;

		m_NumDrawingID[i].m_TexID = m_TexID;
		m_NumDrawingID[i].m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, currentUV);

		++currentTuCount;
	}
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
