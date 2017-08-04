//==================================================================================================================================//
//!< @file		ThisScoreTimeText.cpp
//!< @brief		ar::ThisScoreTimeTextクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "ThisScoreTimeText.h"
#include "../NumberDrawer/NumberDrawer.h"
#include "../ScoreCharacterDrawer/ScoreCharacterDrawer.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

ThisScoreTimeText::ThisScoreTimeText(NumberDrawer* pNumberDrawer, ScoreCharacterDrawer* pScoreCharacterDrawer)
	: ScoreTimeText(pNumberDrawer, pScoreCharacterDrawer)
{}

/* Private Functions ------------------------------------------------------------------------------------------ */

void ThisScoreTimeText::DrawLeadText(void)
{
	m_pScoreCharacterDrawer->Draw(ScoreCharacterDrawer::TIME, m_DispTextPos[LEAD_TEXT]);
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//

