//==================================================================================================================================//
//!< @file		ElectricalBlock.cpp
//!< @brief		ar::ElectricalBlockクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "ElectricalBlock.h"
#include "../../../../StageDataManager.h"
#include "../../../StageEffect/ElectricEffect.h"
#include "../../../../../GameSceneSoundID.h"
#include "../../../StageEffect/SandwichEffect.h"

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
	, m_pEffect(nullptr)
{
	m_TypeID = ELECTICAL_B;
	m_DrawingID.m_TexID = texID;
}

ElectricalBlock::~ElectricalBlock(void)
{
	sl::DeleteSafely(&m_pEffect);
	sl::DeleteSafely(&m_pSandwichEffect);
	m_pLibrary->ReleaseVertex2D(m_DrawingID.m_VtxID);
}

void ElectricalBlock::Initialize(void)
{
	m_Pos.x = m_StageIndexData.m_XIndexNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YIndexNum * m_StageChipSize + (m_StageChipSize / 2);

	// 矩形サイズを設定
	m_RectSize.m_Left		= -(m_StageChipSize / 2);
	m_RectSize.m_Top		= -(m_StageChipSize / 2);
	m_RectSize.m_Right		= (m_StageChipSize / 2);
	m_RectSize.m_Bottom		= (m_StageChipSize / 2);

	m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, ElectricalOnUV);

	m_pSandwichEffect = new SandwichEffect(m_Pos, m_RectSize, m_DrawingID, m_StageChipSize);
	m_pSandwichEffect->Initialize();

	// エフェクトの作成
	m_pEffect = new ElectricEffect(m_DrawingID.m_TexID, m_RectSize);
	m_pEffect->Initialize();
	m_pEffect->ChangeStagePos(m_Pos);
}

void ElectricalBlock::ChangeStagePos(short yIndexNum, short xIndexNum)
{
	m_StageIndexData.m_YIndexNum = yIndexNum;
	m_StageIndexData.m_XIndexNum = xIndexNum;

	m_Pos.x = m_StageIndexData.m_XIndexNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YIndexNum * m_StageChipSize + (m_StageChipSize / 2);
	m_pLibrary->SetVtxUV(m_DrawingID.m_VtxID, ElectricalOnUV);
	m_TypeID = ELECTICAL_B;

	m_pSandwichEffect->ChangeStagePos(m_Pos);

	m_pEffect->ChangeStagePos(m_Pos);
}

void ElectricalBlock::ProcessCollision(const CollisionManager::CollisionData& rData)
{
	switch(rData.m_ObjType)
	{

	case SWITCH_OPERATING_AREA_ON:
		// スイッチがON状態なら通電状態を解除する
		m_pLibrary->SetVtxUV(m_DrawingID.m_VtxID, ElectricalOffUV);
		m_TypeID = NORMAL_B;
		m_pLibrary->PlayBackSound(static_cast<int>(GAME_SCENE_SOUND_ID::ELECTICAL), sl::STOP);
		break;

	case SWITCH_OPERATING_AREA_OFF:
		// スイッチがOFF状態なら通電状態にする
		m_pLibrary->SetVtxUV(m_DrawingID.m_VtxID, ElectricalOnUV);
		m_TypeID = ELECTICAL_B;
		break;

	default:
		// do nothing
		break;
	}
	m_pSandwichEffect->ChangeUV();
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void ElectricalBlock::Run(void)
{
	if(m_HasBeenSandwiched)
	{	
		m_pSandwichEffect->Control();
		if(RESULT_FAILED(m_pEffect->HasBeenSandwiched()))
		{
			m_pEffect->ApplySandwichEffect(m_pSandwichEffect->GetSandwichedSpaceCenterPos());
		}
		else if(m_pEffect->EndSandwichEffect())
		{
			m_pEffect->DetachSandwichEffect();
			m_pEffect->ApplySandwichEffect(m_pSandwichEffect->GetSandwichedSpaceCenterPos());
		}
	}
	else
	{
		if(m_pEffect->HasBeenSandwiched())
		{
			m_pEffect->DetachSandwichEffect();
		}
	}


	m_pEffect->Control();
	if(m_TypeID == ELECTICAL_B)
	{
		// 画面内にあるならオブジェクトを鳴らす
		if(m_Pos.x > m_BasePointPos.x
			&& m_Pos.x < (m_BasePointPos.x + m_DisplayArea.m_Right))
		{
			m_pLibrary->PlayBackSound(static_cast<int>(GAME_SCENE_SOUND_ID::ELECTICAL), sl::PLAY);
		}
	}
}

void ElectricalBlock::Render(void)
{
	m_pLibrary->Draw2D( m_DrawingID, (m_Pos - m_BasePointPos));

	if(m_HasBeenSandwiched)
	{
		m_pSandwichEffect->Draw();
	}

	if(m_TypeID == ELECTICAL_B)
	{
		m_pEffect->Draw();
	}
}

void ElectricalBlock::HandleEvent(void)
{}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
