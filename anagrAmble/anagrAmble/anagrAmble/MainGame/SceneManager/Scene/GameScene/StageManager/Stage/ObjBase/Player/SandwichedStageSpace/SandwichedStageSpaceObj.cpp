//==================================================================================================================================//
//!< @file		SandwichedStageSpaceObj.cpp
//!< @brief		ar::SandwichedStageSpaceObjクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "SandwichedStageSpaceObj.h"
#include "../../ObjBase.h"

namespace ar
{

/* Unnmaed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const float ColorVal[4] = {1.0f, 1.0f, 1.0f, 0.7f};			

}

/* Static Variable -------------------------------------------------------------------------------------------- */

sl::SLVECTOR2				SandwichedStageSpaceObj::m_BasePointPos				= { 0.0f, 0.0f };
sl::fRect					SandwichedStageSpaceObj::m_PlayerRect				= { 0.0f, 0.0f, 0.0f, 0.0f };
Stage::INDEX_DATA			SandwichedStageSpaceObj::m_PlayerIndexData			= { 0, 0 };
float						SandwichedStageSpaceObj::m_StageMapChipSize			= 0.0f;
bool						SandwichedStageSpaceObj::m_IsPlayerFacingRight		= false;
float						SandwichedStageSpaceObj::m_SandwichedSpaceWidth		= 0.0f;

/* Public Functions ------------------------------------------------------------------------------------------- */

SandwichedStageSpaceObj::SandwichedStageSpaceObj(const sl::SLVECTOR2& rPos, const sl::DrawingID& rID )
	: m_pLibrary(sl::ISharokuLibrary::Instance())
	, m_Pos(rPos)
{
	// 描画関連のIDの初期化
	m_DrawingID.m_TexID = rID.m_TexID;		
	sl::fRect	size = m_pLibrary->GetSizeRect(rID.m_VtxID);
	sl::fRect	uv = m_pLibrary->GetUVRect(rID.m_VtxID);		
	m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(size, uv);
	m_pLibrary->SetVtxColor(m_DrawingID.m_VtxID, ColorVal[0], ColorVal[1], ColorVal[2], ColorVal[3]);
}

SandwichedStageSpaceObj::~SandwichedStageSpaceObj(void)
{
	m_pLibrary->ReleaseVertex2D(m_DrawingID.m_VtxID);
}

void SandwichedStageSpaceObj::Draw(void)
{
	sl::SLVECTOR2 drawPos;			// 描画用座標

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
			drawPos.x = (m_PlayerIndexData.m_XIndexNum + 1) * m_StageMapChipSize +  m_Pos.x;
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
			drawPos.x = (m_PlayerIndexData.m_XIndexNum - 1)* m_StageMapChipSize + (m_Pos.x - m_SandwichedSpaceWidth);
		}
		drawPos.y = m_Pos.y;
	}

	m_pLibrary->Draw2D(m_DrawingID, (drawPos - m_BasePointPos));
}


}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
