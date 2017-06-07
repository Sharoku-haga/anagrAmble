//==================================================================================================================================//
//!< @file		Spear.cpp
//!< @brief		ar::Spearクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "Spear.h"
#include "../../../../../StageDataManager.h"

namespace ar
{

/* Unnamed Namespace------------------------------------------------------------------------------------------- */

namespace
{

const float		MoveSpeed = 3.f;		//!< 槍の動くスピード

}

/* Public Functions ------------------------------------------------------------------------------------------- */

Spear::Spear(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
				, const Stage::INDEX_DATA& rStageIndexData, int texID)
	: StageObj(pStageDataManager, pCollisionManager, rStageIndexData)
	, m_MovePosYMAXLimit(0.0f)
	, m_MovePosYMINLimit(0.0f)
	, m_MoveSpeed()
{
	CalculatePos();
	m_TypeID = SPEAR;
	m_DrawingID.m_TexID = texID;

	// ブロックサイズのRect構造体を作成
	float chipSize = m_pStageDataManager->GetStageChipSize();
	m_RectSize.m_Left		= -(chipSize / 2);
	m_RectSize.m_Top		= -(chipSize / 2);
	m_RectSize.m_Right		= (chipSize / 2);
	m_RectSize.m_Bottom		= (chipSize / 2);

	const sl::fRect		uv = {0.3f, 0.1777f, 0.35f, 0.264f};

	m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, uv);

	m_CurrentRectData.m_Left	= m_Pos.x + m_RectSize.m_Left;
	m_CurrentRectData.m_Top		= m_Pos.y + m_RectSize.m_Top;
	m_CurrentRectData.m_Right	= m_Pos.x + m_RectSize.m_Right;
	m_CurrentRectData.m_Bottom	= m_Pos.y + m_RectSize.m_Bottom;

	// 動作スピードと動作限界
	m_MoveSpeed = MoveSpeed;
	m_MovePosYMAXLimit = m_Pos.y - m_pStageDataManager->GetStageChipSize();
	m_MovePosYMINLimit = m_Pos.y;
}

Spear::~Spear(void)
{
	m_pLibrary->ReleaseVertex2D(m_DrawingID.m_VtxID);
}

void Spear::ProcessCollision(const CollisionManager::CollisionData& rData)
{}

/* Private Functions ------------------------------------------------------------------------------------------ */

void Spear::Run(void)
{
	if(m_pStageDataManager->GetTypeID((m_StageIndexData.m_YNum - 1), m_StageIndexData.m_XNum) != BLANK)
	{	// 上が空白がじゃないなら、即処理終了
		return;
	}

	if(m_Pos.y < m_MovePosYMAXLimit)
	{
		m_MoveSpeed = MoveSpeed;
	}
	else if(m_Pos.y > m_MovePosYMINLimit)
	{
		m_MoveSpeed = -MoveSpeed;
	}

	m_Pos.y += m_MoveSpeed;
}

void Spear::Render(void)
{
	m_pLibrary->Draw2D( m_DrawingID, (m_Pos - m_BasePointPos));
}

void Spear::HandleEvent(void)
{}

void Spear::CalculatePos(void)
{
	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize + (m_StageChipSize / 2);
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
