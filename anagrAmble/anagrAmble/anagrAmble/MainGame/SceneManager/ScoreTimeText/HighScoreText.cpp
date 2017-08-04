//==================================================================================================================================//
//!< @file		HighScoreText.cpp
//!< @brief		ar::HighScoreTextクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "HighScoreText.h"
#include "../NumberDrawer/NumberDrawer.h"
#include "../ScoreCharacterDrawer/ScoreCharacterDrawer.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

HighScoreText::HighScoreText(NumberDrawer* pNumberDrawer, ScoreCharacterDrawer* pScoreCharacterDrawer)
	: ScoreTimeText(pNumberDrawer, pScoreCharacterDrawer)
{}

/* Private Functions ------------------------------------------------------------------------------------------ */

void HighScoreText::DrawLeadText(void)
{
	m_pScoreCharacterDrawer->Draw(ScoreCharacterDrawer::HIGH_SCORE, m_DispTextPos[LEAD_TEXT]);
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
