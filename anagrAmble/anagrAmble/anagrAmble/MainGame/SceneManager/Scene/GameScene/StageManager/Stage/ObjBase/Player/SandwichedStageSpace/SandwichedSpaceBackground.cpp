//==================================================================================================================================//
//!< @file		SandwichedSpaceBackground.cpp
//!< @brief		ar::SandwichedSpaceBackgroundクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "SandwichedSpaceBackground.h"

namespace ar
{

/* Unnmaed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const sl::fRect				SizeInitVal		= {0.0f, 0.0f, 0.0f, 0.0f};		// Vertexのサイズの初期化値
const sl::fRect				UVInitVal		= {0.0f, 0.911f, 0.051f, 1.0f};		// VertexのUVの初期化値.textureを使わない
const float					ColorVal[4]		= {1.0f, 1.0f, 1.0f, 0.7f};		// 背景の色.青色		

}

/* Static Variable -------------------------------------------------------------------------------------------- */

sl::SLVECTOR2				SandwichedSpaceBackground::m_BasePointPos		= {0.0f, 0.0f};
float						SandwichedSpaceBackground::m_StageMapChipSize	= 0.0f;			

/* Public Functions ------------------------------------------------------------------------------------------- */

SandwichedSpaceBackground::SandwichedSpaceBackground(int texID)
	: m_pLibrary(sl::ISharokuLibrary::Instance())
	, m_Pos({0.0f, 0.0f})
	, m_SandwichedSpaceWidth(0.0f)
	, m_PlayerRect({0.0f, 0.0f, 0.0f, 0.0f})
	, m_PlayerIndexData({0, 0})
	, m_IsPlayerFacingRight(true)
{
	// 描画ID関連の初期化
	m_DrawingID.m_TexID = texID;	
	m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(SizeInitVal, UVInitVal);

	// 色変更
	m_pLibrary->SetVtxColor(m_DrawingID.m_VtxID, ColorVal[0], ColorVal[1], ColorVal[2], ColorVal[3]);
}


SandwichedSpaceBackground::~SandwichedSpaceBackground(void)
{
	m_pLibrary->ReleaseVertex2D(m_DrawingID.m_VtxID);
}

void SandwichedSpaceBackground::InitializeData(const sl::SLVECTOR2& rPos, float spaceWidth, float spaceHeight)
{
	m_Pos = rPos;
	m_SandwichedSpaceWidth = spaceWidth;

	// サイズ変更
	sl::fRect		size	= {0.0f, 0.0f, spaceWidth, spaceHeight};
	m_pLibrary->SetVtxSize(m_DrawingID.m_VtxID, size);
}

void SandwichedSpaceBackground::DiscardData(void)
{
	m_Pos.x = 0.0f;
	m_Pos.y = 0.0f;
	m_SandwichedSpaceWidth = 0.0f;

	// サイズを初期値に戻す
	m_pLibrary->SetVtxSize(m_DrawingID.m_VtxID, SizeInitVal);
}

void SandwichedSpaceBackground::Draw(void)
{
	sl::SLVECTOR2 drawPos;		// 描画用座標

	// 向きによって座標計算をかえる
	if(m_IsPlayerFacingRight)
	{
		// プレイヤーの左端がプレイヤーがいるステージチップの左端より大きい場合は、
		// 2マス右にオブジェクトを移動させ、それ以外は1マス右に移動させる
		if(m_PlayerRect.m_Left >(m_PlayerIndexData.m_XIndexNum * m_StageMapChipSize))
		{
			drawPos.x = (m_PlayerIndexData.m_XIndexNum + 2) * m_StageMapChipSize +  m_Pos.x;
		}
		else
		{
			drawPos.x = (m_PlayerIndexData.m_XIndexNum +1) * m_StageMapChipSize +  m_Pos.x;
		}
		drawPos.y = m_Pos.y;
	}
	else
	{
		// プレイヤーの右端がプレイヤーがいるステージチップの右端より小さい場合は、
		// 2マス左にオブジェクトを移動させ、それ以外は1マス左に移動させる
		if(m_PlayerRect.m_Right < (m_PlayerIndexData.m_XIndexNum * m_StageMapChipSize))
		{
			drawPos.x = (m_PlayerIndexData.m_XIndexNum - 2) * m_StageMapChipSize + (m_Pos.x - m_SandwichedSpaceWidth);

		}
		else
		{
			drawPos.x = (m_PlayerIndexData.m_XIndexNum - 1)* m_StageMapChipSize +  (m_Pos.x - m_SandwichedSpaceWidth);
		}

		drawPos.y = m_Pos.y;
	}

	m_pLibrary->Draw2D(m_DrawingID, (drawPos - m_BasePointPos));
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
