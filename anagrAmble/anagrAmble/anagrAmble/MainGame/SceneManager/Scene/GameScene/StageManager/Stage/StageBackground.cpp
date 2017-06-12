//==================================================================================================================================//
//!< @file		StageBackground.cpp
//!< @brief		ar::StageBackgroundクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "StageBackground.h"
#include "BasePoint.h"

namespace ar
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */
namespace
{

const float		PosCorrectionVal	= 96.f;		// 座標の補正値

}

/* Public Functions ------------------------------------------------------------------------------------------- */

StageBackground::StageBackground(BasePoint* pBasePoint, int texID)
	: m_pLibrary(sl::ISharokuLibrary::Instance())
	, m_pBasePoint(pBasePoint)
{
	m_ID.m_TexID = texID;

	// 矩形サイズの設定とVertexの生成
	m_RectSize = m_pLibrary->GetClientSize();
	m_RectSize.m_Left  -= PosCorrectionVal;
	m_RectSize.m_Right += PosCorrectionVal;
	sl::fRect	uv = { 0.0f, 0.0f, 1.0f, 1.0f};
	m_ID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, uv);

	m_OldBasePointPos = m_pBasePoint->GetPos();

	// 1つ目の背景座標の初期化
	m_FirstPos.x = m_OldBasePointPos.x;
	m_FirstPos.y = m_OldBasePointPos.y;

	// 2つ目の背景座標の初期化
	m_SecondPos.x = m_OldBasePointPos.x + m_RectSize.m_Right;
	m_SecondPos.y = m_OldBasePointPos.y;
}

StageBackground::~StageBackground(void)
{
	m_pLibrary->ReleaseVertex2D(m_ID.m_VtxID);
}

void StageBackground::Control(void)
{
	sl::SLVECTOR2 cuurentBasePointPos = m_pBasePoint->GetPos();
	if(m_OldBasePointPos.x == cuurentBasePointPos.x)
	{	// BasePointが動いていないなら処理をとばす
		return;
	}

	// 1つ目の背景座標処理
	if((cuurentBasePointPos.x - m_FirstPos.x) >= 0.0f
		&& (m_RectSize.m_Right + PosCorrectionVal / 2) < (cuurentBasePointPos.x - m_FirstPos.x))
	{	// 背景が左の画面外にでたらまた右の画面外に配置しなおす
		m_FirstPos.x = m_SecondPos.x + m_RectSize.m_Right;
	}
	else if((cuurentBasePointPos.x - m_FirstPos.x) < 0.0f 
			&& (m_RectSize.m_Right + PosCorrectionVal / 2) < (m_FirstPos.x - cuurentBasePointPos.x))
	{	// 背景が右の画面外にでたらまた左の画面外に配置しなおす
		m_FirstPos.x = m_SecondPos.x - m_RectSize.m_Right;
	}

	// 2つ目の背景座標処理
	if((cuurentBasePointPos.x - m_SecondPos.x ) >= 0.0f
		&& (m_RectSize.m_Right + PosCorrectionVal / 2) < (cuurentBasePointPos.x - m_SecondPos.x ))
	{	// 背景が左の画面外にでたらまた右の画面外に配置しなおす
		m_SecondPos.x = m_FirstPos.x + m_RectSize.m_Right;
	}
	else if((cuurentBasePointPos.x - m_SecondPos.x ) < 0.0f 
			&& (m_RectSize.m_Right + PosCorrectionVal / 2) < (m_SecondPos.x  - cuurentBasePointPos.x))
	{	// 背景が右の画面外にでたらまた左の画面外に配置しなおす
		m_SecondPos.x  = m_FirstPos.x - m_RectSize.m_Right;
	}

	m_OldBasePointPos = cuurentBasePointPos;
}

void StageBackground::Draw(void)
{
	m_pLibrary->Draw2D(m_ID, m_FirstPos - m_OldBasePointPos);
	m_pLibrary->Draw2D(m_ID, m_SecondPos - m_OldBasePointPos);
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
