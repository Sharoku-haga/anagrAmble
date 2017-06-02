//==================================================================================================================================//
//!< @file		BeltConverBlock.cpp	
//!< @brief		ar::BeltConverBlockクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "BeltConverBlock.h"
#include "../../../../StageDataManager.h"

namespace ar
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const sl::fRect		RightDirectionUV = {0.25f, 0.1777f, 0.3f, 0.264f};				// 右方向のときのUV値
const sl::fRect		LeftDirectionUV  = {0.3f, 0.1777f, 0.25f, 0.264f};				// 左方向のときのUV値

}

/* Public Functions ------------------------------------------------------------------------------------------- */

BeltConverBlock::BeltConverBlock(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
			, const Stage::INDEX_DATA& rStageIndexData,  int texID,  ObjBase::TYPE_ID typeID)
	: StageObj(pStageDataManager, pCollisionManager, rStageIndexData)
{
	CalculatePos();
	m_TypeID = typeID;

	m_DrawingID.m_TexID = texID;

	// ブロックサイズのRect構造体を作成
	float chipSize = m_pStageDataManager->GetStageChipSize();
	m_RectSize.m_Left	=  -(chipSize / 2);
	m_RectSize.m_Top	=  -(chipSize / 2);
	m_RectSize.m_Right	= (chipSize / 2);
	m_RectSize.m_Bottom = (chipSize / 2);

	if(m_TypeID == BELT_CONVER_B_R)
	{
		m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, RightDirectionUV);
	}
	else
	{
		m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, LeftDirectionUV);
	}

	m_CurrentRectData.m_Left	= m_Pos.x + m_RectSize.m_Left; 
	m_CurrentRectData.m_Top		= m_Pos.y + m_RectSize.m_Top;
	m_CurrentRectData.m_Right	= m_Pos.x + m_RectSize.m_Right;
	m_CurrentRectData.m_Bottom	= m_Pos.y + m_RectSize.m_Bottom;
}

BeltConverBlock::~BeltConverBlock(void)
{
	m_pLibrary->ReleaseVertex2D(m_DrawingID.m_VtxID);
}

void BeltConverBlock::ProcessCollision(int typeID, bool isDeath)
{}

/* Private Functions ------------------------------------------------------------------------------------------ */

void BeltConverBlock::Run(void)
{}

void BeltConverBlock::Render(void)
{
	m_pLibrary->Draw2D( m_DrawingID, (m_Pos - m_BasePointPos));
}

void BeltConverBlock::HandleEvent(void)
{}

void BeltConverBlock::CalculatePos(void)
{
	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize + (m_StageChipSize / 2);
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
