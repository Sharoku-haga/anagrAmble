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

const sl::fRect		RightDirectionUV = {0.95f, 0.0f, 1.0f, 0.088f};				// 右方向のときのUV値
const sl::fRect		LeftDirectionUV  = {1.0f, 0.0f, 0.95f, 0.088f};				// 左方向のときのUV値

}

/* Public Functions ------------------------------------------------------------------------------------------- */

BeltConverBlock::BeltConverBlock(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
			, const Stage::INDEX_DATA& rStageIndexData,  int texID,  ObjBase::TYPE_ID typeID)
	: StageObj(pStageDataManager, pCollisionManager, rStageIndexData)
{
	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize + (m_StageChipSize / 2);

	m_TypeID = typeID;

	m_DrawingID.m_TexID = texID;

	// ブロックサイズのRect構造体を作成
	m_RectSize.m_Left	=  -(m_StageChipSize / 2);
	m_RectSize.m_Top	=  -(m_StageChipSize / 2);
	m_RectSize.m_Right	= (m_StageChipSize / 2);
	m_RectSize.m_Bottom = (m_StageChipSize / 2);

	if(m_TypeID == BELT_CONVER_B_R)
	{
		m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, RightDirectionUV);
	}
	else
	{
		m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, LeftDirectionUV);
	}
}

BeltConverBlock::~BeltConverBlock(void)
{
	m_pLibrary->ReleaseVertex2D(m_DrawingID.m_VtxID);
}

void BeltConverBlock::ChangeStagePos(short yIndexNum, short xIndexNum)
{
	m_StageIndexData.m_YNum = yIndexNum;
	m_StageIndexData.m_XNum = xIndexNum;

	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize + (m_StageChipSize / 2);
}

void BeltConverBlock::ProcessCollision(const CollisionManager::CollisionData& rData)
{
	// スイッチのONとOFFで向きを逆転する
	switch(rData.m_ObjType)
	{

	case SWITCH_OPERATING_AREA_ON:

		if(m_TypeID == BELT_CONVER_B_R)
		{
			m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, LeftDirectionUV);
			m_TypeID = BELT_CONVER_B_L;
		}
		else
		{
			m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, RightDirectionUV);
			m_TypeID = BELT_CONVER_B_R;
		}
		break;

	case SWITCH_OPERATING_AREA_OFF:
		if(m_TypeID == BELT_CONVER_B_R)
		{
			m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, LeftDirectionUV);
			m_TypeID = BELT_CONVER_B_L;
		}
		else
		{
			m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, RightDirectionUV);
			m_TypeID = BELT_CONVER_B_R;
		}

		break;

	default:
		// do nothing
		break;
	}
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void BeltConverBlock::Run(void)
{}

void BeltConverBlock::Render(void)
{
	m_pLibrary->Draw2D( m_DrawingID, (m_Pos - m_BasePointPos));
}

void BeltConverBlock::HandleEvent(void)
{}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
