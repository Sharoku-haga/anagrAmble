//==================================================================================================================================//
//!< @file		GameClearBackground.cpp
//!< @brief		ar::GameClearBackgroundクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "GameClearBackground.h"

namespace ar
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const float			AlphaMinVal				= 0.0f;				// アルファ値の最小値
const float			AlphaMaxVal				= 1.0f;				// アルファ値の最大値
const float			FadeSpeed				= 0.01f;			// フェードスピード値
const int			DisplayTime				= 300;				// 背景表示時間. 60FPS
const int			ChangeSceneWaitingTime	= 30;				// シーン変更するまでの待機時間. 60FPS

}

/* Public Functions ------------------------------------------------------------------------------------------- */

GameClearBackground::GameClearBackground(int texID)
	: m_pLibrary(sl::ISharokuLibrary::Instance())
	, m_Pos({ 0.0f, 0.0f })
	, m_CurrentAlphaVal(AlphaMinVal)
	, m_DisplayTimeCount(0)
{
	m_DrawingID.m_TexID = texID;

	// Vertex作成. vtxSize.m_Left、m_Topの0.0ｆは左上位置座標の為
	sl::fRect windowSize = m_pLibrary->GetClientSize();		// ウィンドウサイズ取得(クライアント領域)
	sl::fRect vtxSize;	// Vertexのサイズ
	vtxSize.m_Left = 0.0f;
	vtxSize.m_Top = 0.0f;
	vtxSize.m_Right = (windowSize.m_Right - windowSize.m_Left);
	vtxSize.m_Bottom = (windowSize.m_Bottom - windowSize.m_Top);

	sl::fRect	uv = { 0.0f, 0.0f, 1.0f, 1.0f};		// UV値

	m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(vtxSize, uv);
}

GameClearBackground::~GameClearBackground(void)
{
	m_pLibrary->ReleaseVertex2D(m_DrawingID.m_VtxID);
}

bool GameClearBackground::ControlDisplayTime(void)
{
	++m_DisplayTimeCount;
	if(m_DisplayTimeCount >= DisplayTime)
	{	// 表示時間に達したらtrueをかえす
		return true;
	}

	return false;
}

bool GameClearBackground::FadeIn(void)
{
	m_CurrentAlphaVal += FadeSpeed;
	if(m_CurrentAlphaVal >= AlphaMaxVal)
	{	// アルファ値が最大値になったらtrueをかえす
		m_CurrentAlphaVal = AlphaMaxVal;
		return true;
	}
	return false;
}

bool GameClearBackground::FadeOut(void)
{
	m_CurrentAlphaVal -= FadeSpeed;
	if(m_CurrentAlphaVal <= AlphaMinVal)
	{	// アルファ値が最小値になったらtrueをかえす
		m_CurrentAlphaVal = AlphaMinVal;
		return true;
	}
	return false;
}

void GameClearBackground::Draw(void)
{
	m_pLibrary->SetVtxColor(m_DrawingID.m_VtxID, 1.0f, 1.0f, 1.0f, m_CurrentAlphaVal);
	m_pLibrary->Draw2D(m_DrawingID, m_Pos);
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
