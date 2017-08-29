//==================================================================================================================================//
//!< @file		Spear.cpp
//!< @brief		ar::Spearクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "Spear.h"
#include "../../../../../StageDataManager.h"
#include "../../../../StageEffect/SandwichEffect.h"

namespace ar
{

/* Unnamed Namespace------------------------------------------------------------------------------------------- */

namespace
{

const float		MoveUpSpeed			 = 16.f;				//!< 槍の上に動くスピード
const float		MoveDownSpeed		 = 1.f;					//!< 槍の下に動くスピード
const float		VertexCorrectionVal	 = 10.f;				//!< Vertexの調整値

}

/* Public Functions ------------------------------------------------------------------------------------------- */

Spear::Spear(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
				, const Stage::INDEX_DATA& rStageIndexData, int texID)
	: StageObj(pStageDataManager, pCollisionManager, rStageIndexData)
	, m_MovePosYMAXLimit(0.0f)
	, m_MovePosYMINLimit(0.0f)
	, m_HasMoved(true)
	, m_MoveSpeed(MoveUpSpeed)
{
	m_TypeID = SPEAR;
	m_DrawingID.m_TexID = texID;
}

Spear::~Spear(void)
{
	sl::DeleteSafely(&m_pSandwichEffect);
	m_pLibrary->ReleaseVertex2D(m_DrawingID.m_VtxID);
}

void Spear::Move(void)
{
	m_HasMoved = true;
}

void Spear::Stop(void)
{
	m_HasMoved = false;
	m_Pos.x = m_StageIndexData.m_XIndexNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YIndexNum * m_StageChipSize + (m_StageChipSize / 2);
}

void Spear::Initialize(void)
{
	m_Pos.x = m_StageIndexData.m_XIndexNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YIndexNum * m_StageChipSize + (m_StageChipSize / 2);

	// 矩形サイズを設定
	m_RectSize.m_Left	= -(m_StageChipSize / 2) + VertexCorrectionVal;
	m_RectSize.m_Top	= -(m_StageChipSize / 2) + VertexCorrectionVal;
	m_RectSize.m_Right	= (m_StageChipSize / 2) - VertexCorrectionVal;
	m_RectSize.m_Bottom = (m_StageChipSize / 2);

	const sl::fRect		uv = { 0.751f, 0.090f, 0.8f, 0.1777f };

	m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, uv);

	// 挟むエフェクトには少し大きめ(通常ブロックと同じ大きさの矩形を渡す)
	sl::fRect effectRectSize = {  -(m_StageChipSize / 2), -(m_StageChipSize / 2), (m_StageChipSize / 2), (m_StageChipSize / 2)};
	m_pSandwichEffect = new SandwichEffect(m_Pos, effectRectSize, m_DrawingID, m_StageChipSize);
	m_pSandwichEffect->Initialize();

	// 動作スピードと動作限界
	m_MovePosYMAXLimit = m_Pos.y - m_pStageDataManager->GetStageChipSize() + VertexCorrectionVal;
	m_MovePosYMINLimit = m_Pos.y;

	if(m_pStageDataManager->GetTypeID((m_StageIndexData.m_YIndexNum - 1), m_StageIndexData.m_XIndexNum) != BLANK)
	{	// 上が空白じゃないなら、動かない
		m_HasMoved = false;
	}
}

void Spear::ChangeStagePos(short yIndexNum, short xIndexNum)
{
	m_StageIndexData.m_YIndexNum = yIndexNum;
	m_StageIndexData.m_XIndexNum = xIndexNum;

	m_Pos.x = m_StageIndexData.m_XIndexNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YIndexNum * m_StageChipSize + (m_StageChipSize / 2);

	if(m_pStageDataManager->GetTypeID((m_StageIndexData.m_YIndexNum - 1), m_StageIndexData.m_XIndexNum) != BLANK)
	{	// 上が空白じゃないなら、動かない
		m_HasMoved = false;
	}
	else
	{
		m_HasMoved = true;
	}
}

void Spear::ProcessCollision(const CollisionManager::CollisionData& rData)
{}

/* Private Functions ------------------------------------------------------------------------------------------ */

void Spear::Run(void)
{
	if(RESULT_FAILED(m_HasMoved)
		|| m_pStageDataManager->GetTypeID((m_StageIndexData.m_YIndexNum - 1), m_StageIndexData.m_XIndexNum) != BLANK)
	{
		m_HasMoved = false;
		m_Pos.x = m_StageIndexData.m_XIndexNum * m_StageChipSize + (m_StageChipSize / 2);
		m_Pos.y = m_StageIndexData.m_YIndexNum * m_StageChipSize + (m_StageChipSize / 2);
		m_pSandwichEffect->SetOwnerPos(m_Pos);

		if(m_HasBeenSandwiched)
		{
			m_pSandwichEffect->Control();
		}
		return;
	}

	if(m_Pos.y < m_MovePosYMAXLimit)
	{
		m_MoveSpeed = MoveDownSpeed;
	}
	else if(m_Pos.y > m_MovePosYMINLimit)
	{	
		m_MoveSpeed = -MoveUpSpeed * 2 ;
	}

	m_Pos.y += m_MoveSpeed;
	m_pSandwichEffect->SetOwnerPos(m_Pos);

	if(m_HasBeenSandwiched)
	{	
		m_pSandwichEffect->Control();
	}
}

void Spear::Render(void)
{
	m_pLibrary->Draw2D( m_DrawingID, (m_Pos - m_BasePointPos));

	if(m_HasBeenSandwiched)
	{	
		m_pSandwichEffect->Draw();
	}
}

void Spear::HandleEvent(void)
{}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
