//==================================================================================================================================//
//!< @file		ElectricEffect.cpp
//!< @brief		ar::ElectricEffectクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "ElectricEffect.h"

namespace ar
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const	float	SizeRectCorrectionVal		= 20.f;			// サイズ補正値
const	float	SizeRectTopCorrectionVal	= 15.f;			// 上方向のサイズ補正値

}

/* Public Functions ------------------------------------------------------------------------------------------- */

ElectricEffect::ElectricEffect(int texID, const sl::fRect& rRectSize)
	: m_DrawingID({0, texID})
{
	m_RectSize = rRectSize;
}

ElectricEffect::~ElectricEffect(void)
{
	m_pLibrary->ReleaseVertex2D(m_DrawingID.m_VtxID);
}

void ElectricEffect::Initialize(void)
{
	// Vertex作成
	m_RectSize.m_Left	= m_RectSize.m_Left - SizeRectCorrectionVal;
	m_RectSize.m_Top	= m_RectSize.m_Top - SizeRectCorrectionVal - SizeRectTopCorrectionVal;
	m_RectSize.m_Right	= m_RectSize.m_Right + SizeRectCorrectionVal;
	m_RectSize.m_Bottom = m_RectSize.m_Bottom + SizeRectCorrectionVal;

	sl::fRect		uv = { 0.751f, 0.17797f, 0.8f, 0.266f };
	m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, uv);

	// 透明度を下げておく
	m_pLibrary->SetVtxColor(m_DrawingID.m_VtxID, 1.0f, 1.0f, 1.0f, 0.7f);

	// アニメーション作成
	m_UVAnimeID = m_pLibrary->RegisterUVAnimeID(m_DrawingID.m_VtxID, 6, true);
	m_pLibrary->CreateUVAnimeData(m_DrawingID.m_VtxID, m_UVAnimeID, 1, 6, uv, 3);
}

void ElectricEffect::ChangeStagePos(const sl::SLVECTOR2& rPos)
{
	m_Pos = rPos;
	m_pLibrary->ReturnUVAnimeInitialState(m_DrawingID.m_VtxID, m_UVAnimeID);
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void ElectricEffect::Run(void)
{
	m_pLibrary->UpdateUVAnime(m_DrawingID.m_VtxID, m_UVAnimeID);
}

void ElectricEffect::Render(void)
{
	m_pLibrary->Draw2D(m_DrawingID, (m_Pos - m_BasePointPos));
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
