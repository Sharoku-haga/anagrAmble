
//==================================================================================================================================//
//!< @file		GamePauseMenuBackground.cpp
//!< @brief		ar::GamePauseMenuBackgroundクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "GamePauseMenuBackground.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

GamePauseMenuBackground::GamePauseMenuBackground(int texID)
	: m_pLibrary(sl::ISharokuLibrary::Instance())
	, m_Pos({ 0.0f, 0.0f })
{
	m_ID.m_TexID = texID;
	sl::fRect	size	= { 0.0f, 0.0f, 1920.f, 1080.f};
	sl::fRect	uv		= { 0.0f, 0.0f, 1.0f, 1.0f};
	m_ID.m_VtxID = m_pLibrary->CreateVertex2D(size, uv);
	m_pLibrary->SetVtxColor(m_ID.m_VtxID, 1.0f, 1.0f, 1.0f, 0.5f);		// 半透明にする
}

GamePauseMenuBackground::~GamePauseMenuBackground(void)
{
	m_pLibrary->ReleaseVertex2D(m_ID.m_VtxID);
}

void GamePauseMenuBackground::Draw(void)
{
	m_pLibrary->Draw2D(m_ID, m_Pos);
}

} // namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
