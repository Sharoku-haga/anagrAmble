//==================================================================================================================================//
//!< @file		SmallScoreCharacterDrawer.cpp
//!< @brief		SmallScoreCharacterDrawerクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "SmallScoreCharacterDrawer.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

SmallScoreCharacterDrawer::SmallScoreCharacterDrawer(int texID)
	: ScoreCharacterDrawer(texID)
{
	m_RectSize.m_Left	= -24.0f;
	m_RectSize.m_Top	= -24.0f;
	m_RectSize.m_Right	=  24.0f;
	m_RectSize.m_Bottom =  24.0f;
}

SmallScoreCharacterDrawer::~SmallScoreCharacterDrawer(void)
{
	for(auto& drawingID : m_ScoreCharacterDrawingID)
	{
		m_pLibrary->ReleaseVertex2D(drawingID.m_VtxID);
	}
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void SmallScoreCharacterDrawer::CreateScoreCharacterDrawingID(void)
{
	// 「Time」文字列
	{
		sl::fRect timeRectSize;						// 少し大きめのRect構造体を作成する
		timeRectSize.m_Left = (m_RectSize.m_Left * 3);
		timeRectSize.m_Top = m_RectSize.m_Top;
		timeRectSize.m_Right = (m_RectSize.m_Right * 3);
		timeRectSize.m_Bottom = m_RectSize.m_Bottom;

		sl::fRect uv = {0.195f, 0.585f, 0.292f, 0.683f};
		m_ScoreCharacterDrawingID[TIME].m_TexID = m_TexID;
		m_ScoreCharacterDrawingID[TIME].m_VtxID = m_pLibrary->CreateVertex2D(timeRectSize, uv);
	}

	// 「HighScore」文字列
	{
		sl::fRect highScoreRectSize;
		highScoreRectSize.m_Left = (m_RectSize.m_Left * 5);
		highScoreRectSize.m_Top = m_RectSize.m_Top;
		highScoreRectSize.m_Right = (m_RectSize.m_Right * 5);
		highScoreRectSize.m_Bottom = m_RectSize.m_Bottom;

		sl::fRect uv = {0.195f, 0.488f, 0.4f, 0.585f};
		m_ScoreCharacterDrawingID[HIGH_SCORE].m_TexID = m_TexID;
		m_ScoreCharacterDrawingID[HIGH_SCORE].m_VtxID = m_pLibrary->CreateVertex2D(highScoreRectSize, uv);
	}

	// 秒単位「S」文字列
	{
		sl::fRect uv = {0.343f, 0.195f, 0.375f, 0.292f};
		m_ScoreCharacterDrawingID[SECOND_UNITS].m_TexID = m_TexID;
		m_ScoreCharacterDrawingID[SECOND_UNITS].m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, uv);
	}

	// 分単位「M」文字列

	{
		sl::fRect uv = {0.3125f, 0.195f, 0.343f, 0.292f};
		m_ScoreCharacterDrawingID[MINUTE_UNITS].m_TexID = m_TexID;
		m_ScoreCharacterDrawingID[MINUTE_UNITS].m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, uv);
	}

	// コロンの文字
	{
		sl::fRect uv = {0.375f, 0.195f, 0.406f, 0.292f};
		m_ScoreCharacterDrawingID[COLON].m_TexID = m_TexID;
		m_ScoreCharacterDrawingID[COLON].m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, uv);
	}
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
