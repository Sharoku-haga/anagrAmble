//==================================================================================================================================//
//!< @file		GoalKey.cpp
//!< @brief		ar::GoalKeyクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "GoalKey.h"
#include "../../../../StageDataManager.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

GoalKey::GoalKey(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
				, const Stage::INDEX_DATA& rStageIndexData, int texID)
	: StageObj(pStageDataManager, pCollisionManager, rStageIndexData)
{
	// 位置座標を求める
	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize + (m_StageChipSize / 2);

	m_TypeID = GOAL_KEY;

	m_DrawingID.m_TexID = texID;

	// ブロックサイズのRect構造体を作成
	m_RectSize.m_Left		= -(m_StageChipSize / 2);
	m_RectSize.m_Top		= -(m_StageChipSize / 2);
	m_RectSize.m_Right		= (m_StageChipSize / 2);
	m_RectSize.m_Bottom		= (m_StageChipSize / 2);

	const sl::fRect		uv = { 0.0f, 0.0f, 0.1f, 0.176f };		/** @todo 2017/06/17 UV値がわからないので適当あたいにしておく*/ 

	m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, uv);
}

GoalKey::~GoalKey(void)
{
	m_pLibrary->ReleaseVertex2D(m_DrawingID.m_VtxID);
}

void GoalKey::ChangeStagePos(short yIndexNum, short xIndexNum)
{
	m_StageIndexData.m_YNum = yIndexNum;
	m_StageIndexData.m_XNum = xIndexNum;

	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize + (m_StageChipSize / 2);
}

void GoalKey::ProcessCollision(const CollisionManager::CollisionData& rData)
{}

/* Private Functions ------------------------------------------------------------------------------------------ */

void GoalKey::Run(void)
{}

void GoalKey::Render(void)
{
	m_pLibrary->Draw2D( m_DrawingID, (m_Pos - m_BasePointPos));
}

void GoalKey::HandleEvent(void)
{}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
