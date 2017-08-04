//==================================================================================================================================//
//!< @file		LargeScoreCharacterDrawer.cpp
//!< @brief		LargeScoreCharacterDrawerクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "LargeScoreCharacterDrawer.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

LargeScoreCharacterDrawer::LargeScoreCharacterDrawer(int texID)
	: ScoreCharacterDrawer(texID)
{
	m_RectSize.m_Left	= -32.0f;
	m_RectSize.m_Top	= -32.0f;
	m_RectSize.m_Right	=  32.0f;
	m_RectSize.m_Bottom =  32.0f;
}

LargeScoreCharacterDrawer::~LargeScoreCharacterDrawer(void)
{
	for(auto& drawingID : m_ScoreCharacterDrawingID)
	{
		m_pLibrary->ReleaseVertex2D(drawingID.m_VtxID);
	}
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void LargeScoreCharacterDrawer::CreateScoreCharacterDrawingID(void)
{
	// 「Time」文字列
	{
		sl::fRect timeRectSize;						
		timeRectSize.m_Left = (m_RectSize.m_Left * 3);
		timeRectSize.m_Top = m_RectSize.m_Top;
		timeRectSize.m_Right = (m_RectSize.m_Right * 3);
		timeRectSize.m_Bottom = m_RectSize.m_Bottom;

		sl::fRect uv = { 0.0f, 0.488f, 0.192f, 0.650f };
		m_ScoreCharacterDrawingID[ScoreCharacterDrawer::TIME].m_TexID = m_TexID;
		m_ScoreCharacterDrawingID[ScoreCharacterDrawer::TIME].m_VtxID = m_pLibrary->CreateVertex2D(timeRectSize, uv);
	}

	// 「HighScore」文字列
	{
		sl::fRect highScoreRectSize;
		highScoreRectSize.m_Left = (m_RectSize.m_Left * 5);
		highScoreRectSize.m_Top = m_RectSize.m_Top;
		highScoreRectSize.m_Right = (m_RectSize.m_Right * 5);
		highScoreRectSize.m_Bottom = m_RectSize.m_Bottom;

		sl::fRect uv = { 0.0f, 0.292f, 0.369f, 0.488f };
		m_ScoreCharacterDrawingID[ScoreCharacterDrawer::HIGH_SCORE].m_TexID = m_TexID;
		m_ScoreCharacterDrawingID[ScoreCharacterDrawer::HIGH_SCORE].m_VtxID = m_pLibrary->CreateVertex2D(highScoreRectSize, uv);
	}

	// 秒単位「S」文字列
	{
		sl::fRect uv = { 0.6769f, 0.0f, 0.7384f, 0.1953f };
		m_ScoreCharacterDrawingID[ScoreCharacterDrawer::SECOND_UNITS].m_TexID = m_TexID;
		m_ScoreCharacterDrawingID[ScoreCharacterDrawer::SECOND_UNITS].m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, uv);
	}

	// 分単位「M」文字列
	{
		sl::fRect uv = { 0.615f, 0.0f, 0.6769f, 0.1953f };
		m_ScoreCharacterDrawingID[ScoreCharacterDrawer::MINUTE_UNITS].m_TexID = m_TexID;
		m_ScoreCharacterDrawingID[ScoreCharacterDrawer::MINUTE_UNITS].m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, uv);
	}

	// コロン の文字
	{
		sl::fRect uv = { 0.738f, 0.195f, 0.8f, 0.195f };
		m_ScoreCharacterDrawingID[ScoreCharacterDrawer::COLON].m_TexID = m_TexID;
		m_ScoreCharacterDrawingID[ScoreCharacterDrawer::COLON].m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, uv);
	}
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
