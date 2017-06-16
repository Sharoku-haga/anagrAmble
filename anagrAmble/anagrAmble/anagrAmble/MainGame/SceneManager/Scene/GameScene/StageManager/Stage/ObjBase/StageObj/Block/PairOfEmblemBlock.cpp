//==================================================================================================================================//
//!< @file		PairOfEmblemBlock.cpp
//!< @brief		ar::PairOfEmblemBlockクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "PairOfEmblemBlock.h"
#include "../../../../StageDataManager.h"

namespace ar
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const sl::fRect		EmblemLOnUV = { 0.9f, 0.0f, 0.95f, 0.088f};				// 左側の紋章ONのときのUV値
const sl::fRect		EmblemLOffUV = {0.85f, 0.0f, 0.9f,  0.088f};			// 左側の紋章OFFのときのUV値

const sl::fRect		EmblemROnUV = { 0.95f, 0.0f, 0.9f, 0.088f};				// 右側の紋章ONのときのUV値
const sl::fRect		EmblemROffUV = {0.9f, 0.0f, 0.85f,  0.088f};			// 右側の紋章OFFのときのUV値

}

/* Public Functions ------------------------------------------------------------------------------------------- */

PairOfEmblemBlock::PairOfEmblemBlock(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
			, const Stage::INDEX_DATA& rStageIndexData,  int texID,  ObjBase::TYPE_ID typeID)
	: StageObj(pStageDataManager, pCollisionManager, rStageIndexData)
{
	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize + (m_StageChipSize / 2);
	
	m_TypeID = typeID;

	m_DrawingID.m_TexID = texID;

	// ブロックサイズのRect構造体を作成
	m_RectSize.m_Left		= -(m_StageChipSize / 2);
	m_RectSize.m_Top		= -(m_StageChipSize / 2);
	m_RectSize.m_Right		= (m_StageChipSize / 2);
	m_RectSize.m_Bottom		= (m_StageChipSize / 2);

	CheckPairBlock();

	m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, m_TexUV);

}

PairOfEmblemBlock::~PairOfEmblemBlock(void)
{
	m_pLibrary->ReleaseVertex2D(m_DrawingID.m_VtxID);
}

void PairOfEmblemBlock::ChangeStagePos(short yIndexNum, short xIndexNum)
{
	m_StageIndexData.m_YNum = yIndexNum;
	m_StageIndexData.m_XNum = xIndexNum;

	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize + (m_StageChipSize / 2);
}

void PairOfEmblemBlock::ProcessCollision(const CollisionManager::CollisionData& rData)
{}

/* Private Functions ------------------------------------------------------------------------------------------ */

void PairOfEmblemBlock::Run(void)
{}

void PairOfEmblemBlock::Render(void)
{
	m_pLibrary->Draw2D( m_DrawingID, (m_Pos - m_BasePointPos));
}

void PairOfEmblemBlock::HandleEvent(void)
{}

void PairOfEmblemBlock::CheckPairBlock(void)
{
	// タイプにあわせて左右のどちらかの確認を行い、ペアブロックがあればONになり、なければOFFとなる
	if(m_TypeID == ObjBase::PAIR_OF_EMBLME_B_L)
	{
		if(m_pStageDataManager->GetTypeID(m_StageIndexData.m_YNum, (m_StageIndexData.m_XNum + 1)) == ObjBase::PAIR_OF_EMBLME_B_R)
		{
			m_TexUV = EmblemLOnUV;
		}
		else
		{
			m_TexUV = EmblemLOffUV;
		}
	}
	else
	{
		if(m_pStageDataManager->GetTypeID(m_StageIndexData.m_YNum, (m_StageIndexData.m_XNum - 1)) == ObjBase::PAIR_OF_EMBLME_B_L)
		{
			m_TexUV = EmblemROnUV;
		}
		else
		{
			m_TexUV = EmblemROffUV;
		}
	}
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
