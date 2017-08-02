//==================================================================================================================================//
//!< @file		ScoreCharacterDrawer.cpp
//!< @brief		ScoreCharacterDrawerクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "ScoreCharacterDrawer.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

ScoreCharacterDrawer::ScoreCharacterDrawer(int texID)
	: m_pLibrary(sl::ISharokuLibrary::Instance())
	, m_TexID(texID)
{}

void ScoreCharacterDrawer::Initialize(void)
{
	m_ScoreCharacterDrawingID.resize(ID_MAX);
	CreateScoreCharacterDrawingID();
}

void ScoreCharacterDrawer::Draw(int typeID, const sl::SLVECTOR2& rPos)
{
	m_pLibrary->Draw2D(m_ScoreCharacterDrawingID[typeID], rPos);
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
