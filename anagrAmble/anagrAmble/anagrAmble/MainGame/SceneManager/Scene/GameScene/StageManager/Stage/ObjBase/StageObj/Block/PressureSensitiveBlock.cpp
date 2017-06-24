//==================================================================================================================================//
//!< @file		PressureSensitiveBlock.cpp
//!< @brief		ar::PressureSensitiveBlockクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "PressureSensitiveBlock.h"
#include "../../../../StageDataManager.h"
#include "../../SwitchOperatingArea/SwitchOperatingArea.h"

namespace ar
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const sl::fRect		BlockOnUV						= { 0.15f, 0.0f, 0.2f, 0.088f};				// 感圧ONのときのUV値
const sl::fRect		BlockOffUV						= { 0.1f, 0.0f, 0.15f,  0.088f};			// 感圧OFFのときのUV値
const float			CollisionCorrectionVal			= 12.f;										// 衝突における判定の補正値

}

/* Public Functions ------------------------------------------------------------------------------------------- */

PressureSensitiveBlock::PressureSensitiveBlock(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
	, const Stage::INDEX_DATA& rStageIndexData, int texID)
	: StageObj(pStageDataManager, pCollisionManager, rStageIndexData)
	, m_pSwitchOperatingArea(nullptr)
	, m_HasCollidedWithPlayer(true)
{
	m_TypeID = PRESSURE_SENSITIVE_B;
	m_DrawingID.m_TexID = texID;	
}

PressureSensitiveBlock::~PressureSensitiveBlock(void)
{
	sl::DeleteSafely(&m_pSwitchOperatingArea);
	m_pLibrary->ReleaseVertex2D(m_DrawingID.m_VtxID);
}

void PressureSensitiveBlock::Initialize(void)
{
	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize + (m_StageChipSize / 2);

	// ブロックサイズのRect構造体を作成
	m_RectSize.m_Left		= -(m_StageChipSize / 2);
	m_RectSize.m_Top		= -(m_StageChipSize / 2);
	m_RectSize.m_Right		= (m_StageChipSize / 2);
	m_RectSize.m_Bottom		= (m_StageChipSize / 2);

	m_pSwitchOperatingArea = new SwitchOperatingArea(m_pStageDataManager, m_pCollisionManager, m_StageIndexData, this);
	m_pSwitchOperatingArea->Initialize();

	m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, BlockOffUV);
}

void PressureSensitiveBlock::ChangeStagePos(short yIndexNum, short xIndexNum)
{
	m_StageIndexData.m_YNum = yIndexNum;
	m_StageIndexData.m_XNum = xIndexNum;

	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize + (m_StageChipSize / 2);

	m_pSwitchOperatingArea->SwitchOffState();
	m_pSwitchOperatingArea->ChangeStagePos(yIndexNum, xIndexNum);
}

void PressureSensitiveBlock::ProcessCollision(const CollisionManager::CollisionData& rData)
{
	switch(rData.m_ObjType)
	{
	case PLAYER:
		// 上方向に当たっていたらONの状態にする
		if(m_Pos.y > rData.m_ObjPos.y
			&& m_CurrentRectData.m_Top < rData.m_ObjRect.m_Bottom
			&& std::abs(m_Pos.x - rData.m_ObjPos.x) < m_StageChipSize - CollisionCorrectionVal)
		{
			m_HasCollidedWithPlayer = true;
		}

		break;

	default:
		// do nothing
		break;
	}
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void PressureSensitiveBlock::Run(void)
{
	if(m_HasCollidedWithPlayer)
	{
		m_HasCollidedWithPlayer = false;
		m_pSwitchOperatingArea->SwitchOnState();
		m_pLibrary->SetVtxUV(m_DrawingID.m_VtxID, BlockOnUV);
		return;
	}
	else
	{
		m_pSwitchOperatingArea->SwitchOffState();
		m_pLibrary->SetVtxUV(m_DrawingID.m_VtxID, BlockOffUV);
	}

	// 上に何かのっていたらON状態にする
	if(m_pStageDataManager->GetTypeID((m_StageIndexData.m_YNum - 1), m_StageIndexData.m_XNum) != BLANK)
	{
		m_pSwitchOperatingArea->SwitchOnState();
		m_pLibrary->SetVtxUV(m_DrawingID.m_VtxID, BlockOnUV);
	}
}

void PressureSensitiveBlock::Render(void)
{
	m_pLibrary->Draw2D( m_DrawingID, (m_Pos - m_BasePointPos));
}

void PressureSensitiveBlock::HandleEvent(void)
{}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
