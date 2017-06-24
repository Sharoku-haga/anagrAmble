//==================================================================================================================================//
//!< @file		ElectricalBlock.cpp
//!< @brief		ar::ElectricalBlockクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "ElectricalBlock.h"
#include "../../../../StageDataManager.h"

namespace ar
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const sl::fRect		ElectricalOffUV = { 0.2f, 0.0f, 0.25f, 0.088f};				// 通電ONのときのUV値
const sl::fRect		ElectricalOnUV = { 0.25f, 0.0f, 0.3f, 0.088f};				// 通電OFFのときのUV値

}

/* Public Functions ------------------------------------------------------------------------------------------- */

ElectricalBlock::ElectricalBlock(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager,
								const Stage::INDEX_DATA& rStageIndexData, int texID)
	: StageObj(pStageDataManager, pCollisionManager, rStageIndexData)
	, m_IsEnergizedState(true)
{
	m_TypeID = ELECTICAL_B;
	m_DrawingID.m_TexID = texID;
}

ElectricalBlock::~ElectricalBlock(void)
{
	m_pLibrary->ReleaseVertex2D(m_DrawingID.m_VtxID);
}

void ElectricalBlock::Initialize(void)
{
	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize + (m_StageChipSize / 2);
	
	// ブロックサイズのRect構造体を作成
	m_RectSize.m_Left	=  -(m_StageChipSize  / 2);
	m_RectSize.m_Top	=  -(m_StageChipSize  / 2);
	m_RectSize.m_Right	= (m_StageChipSize  / 2);
	m_RectSize.m_Bottom = (m_StageChipSize  / 2);

	m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, ElectricalOnUV);
}

void ElectricalBlock::ChangeStagePos(short yIndexNum, short xIndexNum)
{
	m_StageIndexData.m_YNum = yIndexNum;
	m_StageIndexData.m_XNum = xIndexNum;

	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize + (m_StageChipSize / 2);
	m_pLibrary->SetVtxUV(m_DrawingID.m_VtxID, ElectricalOnUV);
	m_IsEnergizedState = true;
	m_TypeID = ELECTICAL_B;
}

void ElectricalBlock::ProcessCollision(const CollisionManager::CollisionData& rData)
{
	switch(rData.m_ObjType)
	{

	case SWITCH_OPERATING_AREA_ON:
		// スイッチがON状態なら通電状態を解除する
		m_pLibrary->SetVtxUV(m_DrawingID.m_VtxID, ElectricalOffUV);
		m_IsEnergizedState = false;
		m_TypeID = NORMAL_B;
		break;

	case SWITCH_OPERATING_AREA_OFF:
		// スイッチがOFF状態なら通電状態にする
		m_pLibrary->SetVtxUV(m_DrawingID.m_VtxID, ElectricalOnUV);
		m_IsEnergizedState = true;
		m_TypeID = ELECTICAL_B;
		break;

	default:
		// do nothing
		break;
	}
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void ElectricalBlock::Run(void)
{}

void ElectricalBlock::Render(void)
{
	m_pLibrary->Draw2D( m_DrawingID, (m_Pos - m_BasePointPos));
}

void ElectricalBlock::HandleEvent(void)
{}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
