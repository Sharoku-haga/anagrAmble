//==================================================================================================================================//
//!< @file		LogoText.cpp
//!< @brief		LogoTextクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "LogoText.h"

namespace ar
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const int   DispTime = 300;				// ロゴ表示時間

}

/* Public Functions ------------------------------------------------------------------------------------------- */

LogoText::LogoText(int texID)
	: m_Pos({480.0f, 60.0f})
	, m_pLibrary(sl::ISharokuLibrary::Instance())
	, m_DispTimeCount(0)
	, m_IsEnd(false)
{
	m_ID.m_TexID = texID;
	sl::fRect	size = {0.0f, 0.0f, 960.f, 960.f};
	sl::fRect	uv = { 0.0f, 0.0f, 1.0f, 1.0f};
	m_ID.m_VtxID = m_pLibrary->CreateVertex2D(size, uv);
}

LogoText::~LogoText(void)
{
	m_pLibrary->ReleaseVertex2D(m_ID.m_VtxID);
}

bool LogoText::Control(void)
{

	if(m_DispTimeCount == DispTime)
	{
		m_IsEnd = true;
	}
	else
	{
		++m_DispTimeCount;
	}
	
	return m_IsEnd;
}

void LogoText::Draw(void)
{
	m_pLibrary->Draw2D(m_ID, m_Pos);
}

}	// namespace ar
//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//