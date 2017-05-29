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

const char		BackgroundCount		= 2;			// 背景の数
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
	for(char i = 0; i < BackgroundCount ; ++i)
	{
		m_Pos.emplace_back((m_OldBasePointPos.x + m_RectSize.m_Right * i), m_OldBasePointPos.y);
	}
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

	for(auto& backgroundPos : m_Pos)
	{
		if((cuurentBasePointPos.x - backgroundPos.x) >= 0.0f && (m_RectSize.m_Right + PosCorrectionVal / 2) < (cuurentBasePointPos.x - backgroundPos.x))
		{	// 背景が左の画面外にでたらまた右の画面外に配置しなおす
			backgroundPos.x = cuurentBasePointPos.x + m_RectSize.m_Right;
		}
		else if((cuurentBasePointPos.x - backgroundPos.x) < 0.0f && (m_RectSize.m_Right + PosCorrectionVal / 2) < (backgroundPos.x - cuurentBasePointPos.x))
		{
			backgroundPos.x = cuurentBasePointPos.x - m_RectSize.m_Right;
		}
	}

	m_OldBasePointPos = cuurentBasePointPos;
}

void StageBackground::Draw(void)
{
	for(auto& backgroundPos : m_Pos)
	{
		m_pLibrary->Draw2D(m_ID, backgroundPos - m_OldBasePointPos);
	}
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
