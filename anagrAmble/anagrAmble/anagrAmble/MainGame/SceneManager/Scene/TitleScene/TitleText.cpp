﻿//==================================================================================================================================//
//!< @file		TilteText.cpp
//!< @brief		ar::TilteTextクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "TitleText.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

TitleText::TitleText(int texID)
	: m_Pos({448.0f, 0.0f})
	, m_pLibrary(sl::ISharokuLibrary::Instance())
{
	m_ID.m_TexID		= texID;
	sl::fRect	size	= { 0.0f, 0.0f, 1024.f, 512.f};
	sl::fRect	uv		= { 0.0f, 0.0f, 1.0f, 1.0f};
	m_ID.m_VtxID		= m_pLibrary->CreateVertex2D(size, uv);
}

TitleText::~TitleText(void)
{
	m_pLibrary->ReleaseVertex2D(m_ID.m_VtxID);
}

void TitleText::Draw(void)
{
	m_pLibrary->Draw2D(m_ID, m_Pos);
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
