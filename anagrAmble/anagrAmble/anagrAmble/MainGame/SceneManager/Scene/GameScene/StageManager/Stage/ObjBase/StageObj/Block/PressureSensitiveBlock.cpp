//==================================================================================================================================//
//!< @file		PressureSensitiveBlock.cpp
//!< @brief		ar::PressureSensitiveBlockクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "PressureSensitiveBlock.h"
#include "../../../../StageDataManager.h"
#include "../../SwitchOperatingArea/SwitchOperatingArea.h"
#include "../../../../../GameSceneSoundID.h"
#include "../../../StageEffect/SandwichEffect.h"
#include "../.../../../../../../../../SoundManager/SceneSoundManager.h"

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
	sl::DeleteSafely(&m_pSandwichEffect);
	sl::DeleteSafely(&m_pSwitchOperatingArea);
	m_pLibrary->ReleaseVertex2D(m_DrawingID.m_VtxID);
}

void PressureSensitiveBlock::Initialize(void)
{
	m_Pos.x = m_StageIndexData.m_XIndexNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YIndexNum * m_StageChipSize + (m_StageChipSize / 2);

	// 矩形サイズを設定
	m_RectSize.m_Left		= -(m_StageChipSize / 2);
	m_RectSize.m_Top		= -(m_StageChipSize / 2);
	m_RectSize.m_Right		= (m_StageChipSize / 2);
	m_RectSize.m_Bottom		= (m_StageChipSize / 2);

	m_pSwitchOperatingArea = new SwitchOperatingArea(m_pStageDataManager, m_pCollisionManager, m_StageIndexData, this);
	m_pSwitchOperatingArea->Initialize();

	m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, BlockOffUV);
	m_pSandwichEffect = new SandwichEffect(m_Pos, m_RectSize, m_DrawingID, m_StageChipSize);
	m_pSandwichEffect->Initialize();
}

void PressureSensitiveBlock::ChangeStagePos(short yIndexNum, short xIndexNum)
{
	m_StageIndexData.m_YIndexNum = yIndexNum;
	m_StageIndexData.m_XIndexNum = xIndexNum;

	m_Pos.x = m_StageIndexData.m_XIndexNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YIndexNum * m_StageChipSize + (m_StageChipSize / 2);

	m_pSwitchOperatingArea->SwitchOffState();
	m_pSwitchOperatingArea->ChangeStagePos(yIndexNum, xIndexNum);

	m_pSandwichEffect->ChangeStagePos(m_Pos);
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
		SceneSoundManager::Instance().PlayBackSound(static_cast<int>(GAME_SCENE_SOUND_ID::PRESSURE_SENSITIVE_ON), sl::PLAY);
		m_pLibrary->SetVtxUV(m_DrawingID.m_VtxID, BlockOnUV);
		m_pSandwichEffect->ChangeUV();
	}
	else
	{
		m_pSwitchOperatingArea->SwitchOffState();
		m_pLibrary->SetVtxUV(m_DrawingID.m_VtxID, BlockOffUV);
		m_pSandwichEffect->ChangeUV();
	}

	// 上に何かのっていたらON状態にする
	if(m_pStageDataManager->GetTypeID((m_StageIndexData.m_YIndexNum - 1), m_StageIndexData.m_XIndexNum) != BLANK)
	{
		m_pSwitchOperatingArea->SwitchOnState();
		SceneSoundManager::Instance().PlayBackSound(static_cast<int>(GAME_SCENE_SOUND_ID::PRESSURE_SENSITIVE_ON), sl::PLAY);
		m_pLibrary->SetVtxUV(m_DrawingID.m_VtxID, BlockOnUV);
		m_pSandwichEffect->ChangeUV();
	}

	m_pSwitchOperatingArea->Control();

	if(m_HasBeenSandwiched)
	{	
		m_pSandwichEffect->Control();
	}
}

void PressureSensitiveBlock::Render(void)
{
	m_pLibrary->Draw2D( m_DrawingID, (m_Pos - m_BasePointPos));

	if(m_HasBeenSandwiched)
	{
		m_pSandwichEffect->Draw();
	}
}

void PressureSensitiveBlock::HandleEvent(void)
{}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
