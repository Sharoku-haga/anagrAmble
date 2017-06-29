//==================================================================================================================================//
//!< @file		ScoreTextDrawer.cpp
//!< @brief		ScoreTextDrawerクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "ScoreTextDrawer.h"

namespace ar
{

/* Unnamed namespace ------------------------------------------------------------------------------------------ */

namespace
{

const sl::fRect		GameSceneRectSize = {-24.0f, -24.0f, 24.0f, 24.0f};					//!< ゲームシーンにおけるRectSize
const sl::fRect		GameClearSceneRectSize = {-32.0f, -32.0f, 32.0f, 32.0f};			//!< ゲームシーンにおけるRectSize

}

/* Public Functions ------------------------------------------------------------------------------------------- */

ScoreTextDrawer::ScoreTextDrawer(Scene::ID sceneID, int texID)
	: m_pLibrary(sl::ISharokuLibrary::Instance())
	, m_SceneID(sceneID)
	, m_TexID(texID)
{}

ScoreTextDrawer::~ScoreTextDrawer(void)
{}

void ScoreTextDrawer::Initialize(void)
{
	CreateNumDrawingID();
}

void ScoreTextDrawer::Draw(int typeID, const sl::SLVECTOR2& rPos)
{
	m_pLibrary->Draw2D(m_ScoreTextDrawingID[typeID], rPos);
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void ScoreTextDrawer::CreateNumDrawingID(void)
{
	m_ScoreTextDrawingID.resize(ID_MAX);
	
	// Sceneごとに作成する
	switch(m_SceneID)
	{
	case Scene::GAME:
		m_CurrentRectSize = GameSceneRectSize;
	// タイム
	{
		sl::fRect timeRectSize;						// 少し大きめのRect構造体を作成する
		timeRectSize.m_Left = (m_CurrentRectSize.m_Left * 3);
		timeRectSize.m_Top = m_CurrentRectSize.m_Top;
		timeRectSize.m_Right = (m_CurrentRectSize.m_Right * 3);
		timeRectSize.m_Bottom = m_CurrentRectSize.m_Bottom;

		sl::fRect uv = {0.195f, 0.585f, 0.292f, 0.683f};
		m_ScoreTextDrawingID[TIME].m_TexID = m_TexID;
		m_ScoreTextDrawingID[TIME].m_VtxID = m_pLibrary->CreateVertex2D(timeRectSize, uv);
	}

	// ハイスコア
	{
		sl::fRect highScoreRectSize;
		highScoreRectSize.m_Left = (m_CurrentRectSize.m_Left * 5);
		highScoreRectSize.m_Top = m_CurrentRectSize.m_Top;
		highScoreRectSize.m_Right = (m_CurrentRectSize.m_Right * 5);
		highScoreRectSize.m_Bottom = m_CurrentRectSize.m_Bottom;

		sl::fRect uv = {0.195f, 0.488f, 0.4f, 0.585f};
		m_ScoreTextDrawingID[HIGH_SCORE].m_TexID = m_TexID;
		m_ScoreTextDrawingID[HIGH_SCORE].m_VtxID = m_pLibrary->CreateVertex2D(highScoreRectSize, uv);
	}

	// 秒単位
	{
		sl::fRect uv = {0.343f, 0.195f, 0.375f, 0.292f};
		m_ScoreTextDrawingID[SECOND_UNITS].m_TexID = m_TexID;
		m_ScoreTextDrawingID[SECOND_UNITS].m_VtxID = m_pLibrary->CreateVertex2D(m_CurrentRectSize, uv);
	}

	// 分単位
	{
		sl::fRect uv = {0.3125f, 0.195f, 0.343f, 0.292f};
		m_ScoreTextDrawingID[MINUTE_UNITS].m_TexID = m_TexID;
		m_ScoreTextDrawingID[MINUTE_UNITS].m_VtxID = m_pLibrary->CreateVertex2D(m_CurrentRectSize, uv);
	}

	// コロン
	{
		sl::fRect uv = {0.375f, 0.195f, 0.406f, 0.292f};
		m_ScoreTextDrawingID[COLON].m_TexID = m_TexID;
		m_ScoreTextDrawingID[COLON].m_VtxID = m_pLibrary->CreateVertex2D(m_CurrentRectSize, uv);
	}
		break;

	case Scene::GAME_CLEAR:
		m_CurrentRectSize = GameClearSceneRectSize;
	// タイム
	{
		sl::fRect timeRectSize;						// 少し大きめのRect構造体を作成する
		timeRectSize.m_Left = (m_CurrentRectSize.m_Left * 3);
		timeRectSize.m_Top = m_CurrentRectSize.m_Top;
		timeRectSize.m_Right = (m_CurrentRectSize.m_Right * 3);
		timeRectSize.m_Bottom = m_CurrentRectSize.m_Bottom;

		sl::fRect uv = { 0.0f, 0.488f, 0.192f, 0.650f };
		m_ScoreTextDrawingID[TIME].m_TexID = m_TexID;
		m_ScoreTextDrawingID[TIME].m_VtxID = m_pLibrary->CreateVertex2D(timeRectSize, uv);
	}

	// ハイスコア
	{
		sl::fRect highScoreRectSize;
		highScoreRectSize.m_Left = (m_CurrentRectSize.m_Left * 5);
		highScoreRectSize.m_Top = m_CurrentRectSize.m_Top;
		highScoreRectSize.m_Right = (m_CurrentRectSize.m_Right * 5);
		highScoreRectSize.m_Bottom = m_CurrentRectSize.m_Bottom;

		sl::fRect uv = {0.0f, 0.292f, 0.369f, 0.488f};
		m_ScoreTextDrawingID[HIGH_SCORE].m_TexID = m_TexID;
		m_ScoreTextDrawingID[HIGH_SCORE].m_VtxID = m_pLibrary->CreateVertex2D(highScoreRectSize, uv);
	}

	// 秒単位
	{
		sl::fRect uv = {0.6769f, 0.0f, 0.7384f, 0.1953f};
		m_ScoreTextDrawingID[SECOND_UNITS].m_TexID = m_TexID;
		m_ScoreTextDrawingID[SECOND_UNITS].m_VtxID = m_pLibrary->CreateVertex2D(m_CurrentRectSize, uv);
	}

	// 分単位
	{
		sl::fRect uv = {0.615f, 0.0f, 0.6769f, 0.1953f};
		m_ScoreTextDrawingID[MINUTE_UNITS].m_TexID = m_TexID;
		m_ScoreTextDrawingID[MINUTE_UNITS].m_VtxID = m_pLibrary->CreateVertex2D(m_CurrentRectSize, uv);
	}

	// コロン
	{
		sl::fRect uv = {0.738f, 0.195f, 0.8f, 0.195f};
		m_ScoreTextDrawingID[COLON].m_TexID = m_TexID;
		m_ScoreTextDrawingID[COLON].m_VtxID = m_pLibrary->CreateVertex2D(m_CurrentRectSize, uv);
	}
		break;

	default:
		// do noting
		break;
	}

}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
