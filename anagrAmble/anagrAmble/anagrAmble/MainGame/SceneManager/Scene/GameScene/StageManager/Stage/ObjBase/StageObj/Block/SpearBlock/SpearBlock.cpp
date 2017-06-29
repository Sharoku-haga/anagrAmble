//==================================================================================================================================//
//!< @file		SpearBlock.cpp
//!< @brief		ar::SpearBlockクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "SpearBlock.h"
#include "Spear.h"
#include "../../../../../StageDataManager.h"
#include "../../../../StageEffect/SandwichEffect.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

SpearBlock::SpearBlock(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
				, const Stage::INDEX_DATA& rStageIndexData, int texID)
	: StageObj(pStageDataManager, pCollisionManager, rStageIndexData)
{
	m_TypeID = SPEAR_B;
	m_DrawingID.m_TexID = texID;
}

SpearBlock::~SpearBlock(void)
{
	sl::DeleteSafely(&m_pSandwichEffect);
	sl::DeleteSafely(&m_pSpear);
	m_pLibrary->ReleaseVertex2D(m_DrawingID.m_VtxID);
}

void SpearBlock::Initialize(void)
{
	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize + (m_StageChipSize / 2);

	// ブロックサイズのRect構造体を作成
	m_RectSize.m_Left		= -(m_StageChipSize / 2);
	m_RectSize.m_Top		= -(m_StageChipSize / 2);
	m_RectSize.m_Right		= (m_StageChipSize / 2);
	m_RectSize.m_Bottom		= (m_StageChipSize / 2);

	const sl::fRect		uv = {0.8f, 0.088f, 0.85f, 0.1777f};

	m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, uv);
	
	m_pSpear = new Spear(m_pStageDataManager, m_pCollisionManager, m_StageIndexData, m_DrawingID.m_TexID);
	m_pSpear->Initialize();

	m_pSandwichEffect = new SandwichEffect(m_Pos, m_RectSize, m_DrawingID, m_StageChipSize);
	m_pSandwichEffect->Initialize();
}

void SpearBlock::ChangeStagePos(short yIndexNum, short xIndexNum)
{
	m_StageIndexData.m_YNum = yIndexNum;
	m_StageIndexData.m_XNum = xIndexNum;

	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize + (m_StageChipSize / 2);

	m_pSpear->ChangeStagePos(yIndexNum, xIndexNum);

	m_pSandwichEffect->ChangeStagePos(m_Pos);
}

void SpearBlock::ProcessCollision(const CollisionManager::CollisionData& rData)
{
	// スイッチONなら動きを止め、OFFなら動く
	switch(rData.m_ObjType)
	{

	case SWITCH_OPERATING_AREA_ON:
		m_pSpear->Stop();
		break;

	case SWITCH_OPERATING_AREA_OFF:
		m_pSpear->Move();
		break;

	default:
		// do nothing
		break;
	}
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void SpearBlock::Run(void)
{
	if(m_HasBeenSandwiched)
	{	
		m_pSandwichEffect->Control();

		if(RESULT_FAILED(m_pSpear->HasBeenSandwiched()))
		{
			m_pSpear->ApplySandwichEffect(m_pSandwichEffect->GetSandwichedSpaceCenterPos());
		}
		else if(m_pSpear->EndSandwichEffect())
		{
			m_pSpear->DetachSandwichEffect();
			m_pSpear->ApplySandwichEffect(m_pSandwichEffect->GetSandwichedSpaceCenterPos());
		}
	}
	else
	{
		if(m_pSpear->HasBeenSandwiched())
		{
			m_pSpear->DetachSandwichEffect();
		}
	}

	m_pSpear->Control();
}

void SpearBlock::Render(void)
{
	m_pSpear->Draw();
	m_pLibrary->Draw2D( m_DrawingID, (m_Pos - m_BasePointPos));	

	if(m_HasBeenSandwiched)
	{
		m_pSandwichEffect->Draw();
	}
}

void SpearBlock::HandleEvent(void)
{}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
