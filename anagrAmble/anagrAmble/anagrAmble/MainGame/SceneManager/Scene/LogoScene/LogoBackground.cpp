//==================================================================================================================================//
//!< @file		LogoBackground.cpp
//!< @brief		ar::LogoBackgroundクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "LogoBackground.h"

namespace ar
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const float			AlphaMinVal				= 0.0f;		// アルファ値の最小値
const float			AlphaMaxVal				= 1.0f;		// アルファ値の最大値
const float			FadeSpeed				= 0.01f;	// フェードスピード値
const int			DisplayTime				= 120;		// 背景表示時間. 60FPS

}

/* Public Functions ------------------------------------------------------------------------------------------- */

LogoBackground::LogoBackground(int texID)
	: m_pLibrary(sl::ISharokuLibrary::Instance()) 
	, m_Pos({ 0.0f, 0.0f })
	, m_CurrentState(FADE_IN)
	, m_CurrentAlphaVal(AlphaMinVal)
	, m_EndsProcessing(false)
	, m_DisplayTimeCount(0)
{
	m_DrawingID.m_TexID = texID;
	sl::fRect	size = m_pLibrary->GetClientSize();
	sl::fRect	uv = { 0.0f, 0.0f, 1.0f, 1.0f};
	m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(size, uv);
}

LogoBackground::~LogoBackground(void)
{
	m_pLibrary->ReleaseVertex2D(m_DrawingID.m_VtxID);
}

bool LogoBackground::Control(void)
{
	switch(m_CurrentState)
	{
	case FADE_IN:
		m_CurrentAlphaVal += FadeSpeed;
		if(m_CurrentAlphaVal >= AlphaMaxVal)
		{	// アルファ値が最大値になったら表示中へ
			m_CurrentAlphaVal = AlphaMaxVal;
			m_CurrentState = DISPLAYING;
		}
		break;

	case DISPLAYING:
		if(m_DisplayTimeCount >= DisplayTime)
		{
			m_CurrentState = FADE_OUT;
		}
		else
		{
			++m_DisplayTimeCount;
		}
		break;

	case FADE_OUT:
		m_CurrentAlphaVal -= FadeSpeed;
		if(m_CurrentAlphaVal <= AlphaMinVal)
		{	// アルファ値が最小値になったら処理完了フラグをたてる
			m_CurrentAlphaVal = AlphaMinVal;
			m_EndsProcessing = true;
		}
		break;

	default:
		// do nothing
		break;
	}
		return m_EndsProcessing;
}

void LogoBackground::Draw(void)
{
	m_pLibrary->SetVtxColor(m_DrawingID.m_VtxID, 1.0f, 1.0f, 1.0f, m_CurrentAlphaVal);
	m_pLibrary->Draw2D(m_DrawingID, m_Pos);
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
