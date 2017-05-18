//==================================================================================================================================//
//!< @file		LogoBackground.cpp
//!< @brief		ar::LogoBackgroundクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "LogoBackground.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

LogoBackground::LogoBackground(int texID)
	: m_Pos({0.0f, 0.0f})
	, m_pLibrary(sl::ISharokuLibrary::Instance())
{
	m_ID.m_TexID = texID;
	sl::fRect	size = {0.0f, 0.0f, 1920.f, 1080.f};
	sl::fRect	uv = { 0.0f, 0.0f, 1.0f, 1.0f};
	m_ID.m_VtxID = m_pLibrary->CreateVertex2D(size, uv);
}

LogoBackground::~LogoBackground(void)
{
	m_pLibrary->ReleaseVertex2D(m_ID.m_VtxID);
}

void LogoBackground::Draw(void)
{
	m_pLibrary->Draw2D(m_ID, m_Pos);
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
