//==================================================================================================================================//
//!< @file		NumberDrawer.cpp
//!< @brief		NumberDrawerクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "NumberDrawer.h"

namespace ar
{

/* Static Variable -------------------------------------------------------------------------------------------- */

const int		NumberDrawer::m_NumberCount;

/* Public Functions ------------------------------------------------------------------------------------------- */

NumberDrawer::NumberDrawer(int texID)
	: m_pLibrary(sl::ISharokuLibrary::Instance())
	, m_TexID(texID)
{}

void NumberDrawer::Initialize(void)
{
	// 数字分確保
	m_NumDrawingID.resize(m_NumberCount);

	CreateNumDrawingID();
}

void NumberDrawer::DrawNumber(unsigned int drawNum, const sl::SLVECTOR2& rPos)
{
	if(drawNum >= m_NumberCount
		|| drawNum < 0)
	{
		return;
	}

	m_pLibrary->Draw2D(m_NumDrawingID[drawNum], rPos);
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
