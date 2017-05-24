//==================================================================================================================================//
//!< @file		BasicButton.cpp
//!< @brief		ar::BasicButtonクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "BasicButton.h"
#include "../SharokuLibrary/sl/slISharokuLibrary.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

BasicButton::BasicButton(int texID, const sl::fRect& rSize, const sl::fRect& rUv, const sl::SLVECTOR2& rPos)
	: m_Pos(rPos)
{
	m_ID.m_TexID = texID;
	m_ID.m_VtxID = m_pLibrary->CreateVertex2D(rSize, rUv);
}

BasicButton::~BasicButton(void)
{
	m_pLibrary->ReleaseVertex2D(m_ID.m_VtxID);
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void BasicButton::Run(void)
{}

void BasicButton::Render(void)
{
	m_pLibrary->Draw2D(m_ID, m_Pos);
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
