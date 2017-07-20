//==================================================================================================================================//
//!< @file		StageObj.cpp
//!< @brief		ar::StageObjクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "StageObj.h"
#include "../../CollisionManager.h"

namespace ar
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const float AreaCorrectionVal	= 576.f;		//!< 表示画面エリアの補正値. この値を使用して少し画面外まで描画するようにする。

}

/* Public Functions ------------------------------------------------------------------------------------------- */

StageObj::StageObj(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager, const Stage::INDEX_DATA& rStageIndexData)
	: ObjBase(pStageDataManager, pCollisionManager, rStageIndexData)
{}

void StageObj::Control(void)
{
	HandleEvent();

	Run();

	// 画面外にあるオブジェクトは衝突処理を登録せずに即return
	if( m_Pos.x < (m_BasePointPos.x - AreaCorrectionVal)
		|| m_Pos.x > (m_BasePointPos.x + AreaCorrectionVal + m_DisplayArea.m_Right))
	{
		return;
	}

	// 衝突処理に登録する
	m_pCollisionManager->SetObjBasePointer(this);
}

void StageObj::Draw(void)
{
	// 画面外にあるオブジェクトは描画しない
	if( m_Pos.x < (m_BasePointPos.x - AreaCorrectionVal)
		|| m_Pos.x > (m_BasePointPos.x + AreaCorrectionVal + m_DisplayArea.m_Right))
	{
		return;
	}
	
	Render();
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
