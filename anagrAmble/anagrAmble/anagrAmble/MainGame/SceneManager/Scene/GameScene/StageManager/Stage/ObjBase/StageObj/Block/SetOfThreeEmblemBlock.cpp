//==================================================================================================================================//
//!< @file		SetOfThreeEmblemBlock.cpp
//!< @brief		ar::SetOfThreeEmblemBlockクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "SetOfThreeEmblemBlock.h"
#include "../../../../StageDataManager.h"
#include "../../SwitchOperatingArea/SwitchOperatingArea.h"
#include "../../../../../GameEventManager/GameEventManager.h"
#include "../../../../../GameEventManager/EventListener.h"

namespace ar
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const sl::fRect		EmblemLOnUV = { 0.75f, 0.0f, 0.8f, 0.088f};				// 左側の紋章ONのときのUV値
const sl::fRect		EmblemLOffUV = {0.65f, 0.0f, 0.7f,  0.088f};			// 左側の紋章OFFのときのUV値

const sl::fRect		EmblemFOnUV = { 0.8f, 0.0f, 0.85f, 0.088f};				// 真ん中の紋章ONのときのUV値
const sl::fRect		EmblemFOffUV = {0.7f, 0.0f, 0.75f,  0.088f};			// 真ん中の紋章OFFのときのUV値

const sl::fRect		EmblemROnUV = { 0.8f, 0.0f, 0.75f, 0.088f};				// 右側の紋章ONのときのUV値
const sl::fRect		EmblemROffUV = {0.7f, 0.0f, 0.65f,  0.088f};			// 右側の紋章OFFのときのUV値


}

/* Public Functions ------------------------------------------------------------------------------------------- */

SetOfThreeEmblemBlock::SetOfThreeEmblemBlock(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
			, const Stage::INDEX_DATA& rStageIndexData,  int texID,  ObjBase::TYPE_ID typeID)
	: StageObj(pStageDataManager, pCollisionManager, rStageIndexData)
{
	m_TypeID = typeID;
	m_DrawingID.m_TexID = texID;
}

SetOfThreeEmblemBlock::~SetOfThreeEmblemBlock(void)
{
	sl::DeleteSafely(m_pSwitchOperatingArea);
	m_pLibrary->ReleaseVertex2D(m_DrawingID.m_VtxID);
}

void SetOfThreeEmblemBlock::Initialize(void)
{
	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize + (m_StageChipSize / 2);

	// ブロックサイズのRect構造体を作成
	m_RectSize.m_Left	= -(m_StageChipSize / 2);
	m_RectSize.m_Top	= -(m_StageChipSize / 2);
	m_RectSize.m_Right	= (m_StageChipSize / 2);
	m_RectSize.m_Bottom	= (m_StageChipSize / 2);

	m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, m_TexUV);

	m_pSwitchOperatingArea = new SwitchOperatingArea(m_pStageDataManager, m_pCollisionManager, m_StageIndexData, this);
	m_pSwitchOperatingArea->Initialize();

	CheckSetofThreeBlock();

	// 入れ替え処理終了イベント
	GameEventManager::Instance().RegisterEventType("space_change_end", m_pEventListener);
	m_pEventListener->RegisterSynEventFunc("space_change_end", std::bind(&ar::SetOfThreeEmblemBlock::CheckSetofThreeBlock, this));
}

void SetOfThreeEmblemBlock::ChangeStagePos(short yIndexNum, short xIndexNum)
{
	m_StageIndexData.m_YNum = yIndexNum;
	m_StageIndexData.m_XNum = xIndexNum;

	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize + (m_StageChipSize / 2);

	m_pSwitchOperatingArea->SwitchOffState();
	m_pSwitchOperatingArea->ChangeStagePos(yIndexNum, xIndexNum);

	CheckSetofThreeBlock();
}

void SetOfThreeEmblemBlock::ProcessCollision(const CollisionManager::CollisionData& rData)
{}

/* Private Functions ------------------------------------------------------------------------------------------ */

void SetOfThreeEmblemBlock::Run(void)
{}

void SetOfThreeEmblemBlock::Render(void)
{
	m_pLibrary->Draw2D( m_DrawingID, (m_Pos - m_BasePointPos));
}

void SetOfThreeEmblemBlock::HandleEvent(void)
{}

void SetOfThreeEmblemBlock::CheckSetofThreeBlock(void)
{
	switch(m_TypeID)
	{
	case ObjBase::SET_OF_THREE_EMBLME_B_R:
		if(m_pStageDataManager->GetTypeID(m_StageIndexData.m_YNum, (m_StageIndexData.m_XNum - 1)) == ObjBase::SET_OF_THREE_EMBLME_B_F
			&& m_pStageDataManager->GetTypeID(m_StageIndexData.m_YNum, (m_StageIndexData.m_XNum - 2)) == ObjBase::SET_OF_THREE_EMBLME_B_L)
		{
			m_TexUV = EmblemROnUV;
			m_pSwitchOperatingArea->SwitchOnState();
		}
		else
		{
			m_TexUV = EmblemROffUV;
			m_pSwitchOperatingArea->SwitchOffState();
		}

		break;

	case ObjBase::SET_OF_THREE_EMBLME_B_F:
		if(m_pStageDataManager->GetTypeID(m_StageIndexData.m_YNum, (m_StageIndexData.m_XNum + 1)) == ObjBase::SET_OF_THREE_EMBLME_B_R
			&& m_pStageDataManager->GetTypeID(m_StageIndexData.m_YNum, (m_StageIndexData.m_XNum - 1)) == ObjBase::SET_OF_THREE_EMBLME_B_L)
		{
			m_TexUV = EmblemFOnUV;
			m_pSwitchOperatingArea->SwitchOnState();
		}
		else
		{
			m_TexUV = EmblemFOffUV;
			m_pSwitchOperatingArea->SwitchOffState();
		}

		break;

	case ObjBase::SET_OF_THREE_EMBLME_B_L:
		if(m_pStageDataManager->GetTypeID(m_StageIndexData.m_YNum, (m_StageIndexData.m_XNum + 1)) == ObjBase::SET_OF_THREE_EMBLME_B_F
			&& m_pStageDataManager->GetTypeID(m_StageIndexData.m_YNum, (m_StageIndexData.m_XNum + 2)) == ObjBase::SET_OF_THREE_EMBLME_B_R)
		{
			m_TexUV = EmblemLOnUV;
			m_pSwitchOperatingArea->SwitchOnState();
		}
		else
		{
			m_TexUV = EmblemLOffUV;
			m_pSwitchOperatingArea->SwitchOffState();
		}

		break;

	default:
		// do nothing
		break;
	}

	m_pLibrary->SetVtxUV(m_DrawingID.m_VtxID, m_TexUV);
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
