//==================================================================================================================================//
//!< @file		Goal.cpp
//!< @brief		ar::Goalクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "Goal.h"
#include "../../../../StageDataManager.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

Goal::Goal(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
			, const Stage::INDEX_DATA& rStageIndexData,  int texID,  ObjBase::TYPE_ID typeID)
	: StageObj(pStageDataManager, pCollisionManager, rStageIndexData)
{
	CalculatePos();
	m_TypeID = typeID;
	m_DrawingID.m_TexID = texID;

	// ブロックサイズのRect構造体を作成
	float chipSize = m_pStageDataManager->GetStageChipSize();
	m_RectSize.m_Left	=  -((chipSize * 3) / 2);
	m_RectSize.m_Top	=  -((chipSize * 3) / 2);
	m_RectSize.m_Right	= ((chipSize * 3) / 2);
	m_RectSize.m_Bottom = ((chipSize * 3) / 2);

	const sl::fRect		uv = { 0.0f, 0.2666f, 0.15f, 0.6222f};

	m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, uv);
}

Goal::~Goal(void)
{
	m_pLibrary->ReleaseVertex2D(m_DrawingID.m_VtxID);
}

void Goal::ProcessCollision(const CollisionManager::CollisionData& rData)
{}

/* Private Functions ------------------------------------------------------------------------------------------ */

void Goal::Run(void)
{}

void Goal::Render(void)
{
	m_pLibrary->Draw2D( m_DrawingID, (m_Pos - m_BasePointPos));
}

void Goal::HandleEvent(void)
{}

void Goal::CalculatePos(void)
{
	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2) + m_StageChipSize;
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize - (m_StageChipSize / 2);
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
