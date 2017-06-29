//==================================================================================================================================//
//!< @file		SandwichEffect.h
//!< @brief		SandwichEffectクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "SandwichEffect.h"

namespace ar
{

/* Unnamed namespace ------------------------------------------------------------------------------------------ */

namespace
{

const float			EffectBasicSpeed = 1.0f;		// 挟む効果の基本スピード

}

/* Public Functions ------------------------------------------------------------------------------------------- */

SandwichEffect::SandwichEffect(const sl::SLVECTOR2& rOwnerPos, const sl::fRect rRectSize 
								, const  sl::DrawingID& rOwnerID, float stageChipSize)
	: m_OwnerPos(rOwnerPos)
	, m_SandwichedSpaceCenterPos({ 0.0f, 0.0f })
	, m_BasicRectSize(rRectSize)
	, m_OwnerID(rOwnerID)
	, m_StageChipSize(stageChipSize)
	, m_EffectSpeed(0.0f)
	, m_EndEffect(true)
{}

SandwichEffect::~SandwichEffect(void)
{}

void SandwichEffect::ProcessBeforeEffectStart(const sl::SLVECTOR2& rSandwichedSpaceCenterPos)
{
	m_Pos = m_OwnerPos;
	m_SandwichedSpaceCenterPos = rSandwichedSpaceCenterPos;
	m_RectSize = m_BasicRectSize;
	m_EndEffect = false;

	// スピードを計算する。離れている分(マップチップ分)だけ速くする
	// 左側、右側で処理を変更
	if((m_SandwichedSpaceCenterPos.x  - m_OwnerPos.x ) > 0.0f)
	{
		int chipCount = static_cast<int>((m_SandwichedSpaceCenterPos.x - m_Pos.x) / m_StageChipSize);
		m_EffectSpeed = (EffectBasicSpeed * chipCount);
	}
	else
	{
		int chipCount = static_cast<int>((m_Pos.x - m_SandwichedSpaceCenterPos.x) / m_StageChipSize);
		m_EffectSpeed = (EffectBasicSpeed * chipCount);
	}
}

void SandwichEffect::ChangeUV(void)
{
	sl::fRect uv = m_pLibrary->GetUVRect(m_OwnerID.m_VtxID);
	m_pLibrary->SetVtxUV(m_DrawingID.m_VtxID, uv);
}

void SandwichEffect::ChangeAlpha(float alpha)
{
	m_pLibrary->SetVtxColor(m_DrawingID.m_VtxID, 1.0f, 1.0f, 1.0f, alpha);
}

void SandwichEffect::Initialize(void)
{
	m_Pos = m_OwnerPos;

	// 描画関連の初期化
	m_DrawingID.m_TexID = m_OwnerID.m_TexID;
	m_RectSize = m_BasicRectSize;
	sl::fRect uv = m_pLibrary->GetUVRect(m_OwnerID.m_VtxID);
	m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, uv);
}

void SandwichEffect::ChangeStagePos(const sl::SLVECTOR2& rPos)
{
	m_Pos = m_OwnerPos = rPos;
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void SandwichEffect::Run(void)
{
	if(m_EndEffect)
	{	// 効果が終了していたら即return
		return;
	}

	m_Pos.y = m_OwnerPos.y;

	// ブロックの位置(左側.真ん中.右側)によって処理を変える
	if((m_SandwichedSpaceCenterPos.x - m_OwnerPos.x) > 0.0f)
	{	// 左側
		if((m_RectSize.m_Left + m_Pos.x) < m_Pos.x
			&& m_Pos.x < m_SandwichedSpaceCenterPos.x)
		{
			m_RectSize.m_Left += EffectBasicSpeed;
			m_Pos.x += m_EffectSpeed;
		}
		else if((m_RectSize.m_Right + m_Pos.x) < m_SandwichedSpaceCenterPos.x
			&& m_Pos.x < m_SandwichedSpaceCenterPos.x)
		{
			m_Pos.x += m_EffectSpeed;
		}
		else if(m_Pos.x < m_SandwichedSpaceCenterPos.x
				&& m_EffectSpeed != 0.0f)
		{
			m_Pos.x += m_EffectSpeed;
			m_RectSize.m_Right = m_SandwichedSpaceCenterPos.x - m_Pos.x;
		}
		else if(m_Pos.x < m_SandwichedSpaceCenterPos.x
				&& m_EffectSpeed == 0.0f)
		{
			m_Pos.x += ( EffectBasicSpeed / 2.0f);
			m_RectSize.m_Right = m_SandwichedSpaceCenterPos.x - m_Pos.x;
		}
		else
		{
			m_EndEffect = true;
		}

	}
	else if((m_SandwichedSpaceCenterPos.x - m_OwnerPos.x) < 0.0f)
	{	// 右側
		if((m_RectSize.m_Right  + m_Pos.x) > m_Pos.x
			&& m_Pos.x > m_SandwichedSpaceCenterPos.x)
		{
			m_RectSize.m_Right -= EffectBasicSpeed;
			m_Pos.x -= m_EffectSpeed;
		}
		else if((m_RectSize.m_Left + m_Pos.x) > m_SandwichedSpaceCenterPos.x
			&& m_Pos.x > m_SandwichedSpaceCenterPos.x)
		{
			m_Pos.x -= m_EffectSpeed;
		}
		else if(m_Pos.x > m_SandwichedSpaceCenterPos.x
				&& m_EffectSpeed != 0.0f)
		{
			m_Pos.x -=  m_EffectSpeed;
			m_RectSize.m_Left = -(m_Pos.x - m_SandwichedSpaceCenterPos.x);
		}
		else if(m_Pos.x > m_SandwichedSpaceCenterPos.x
				&& m_EffectSpeed == 0.0f)
		{
			m_Pos.x -=  ( EffectBasicSpeed / 2.0f );
			m_RectSize.m_Left = -(m_Pos.x - m_SandwichedSpaceCenterPos.x);
		}
		else
		{
			m_EndEffect = true;
		}
	}
	else
	{	// 真ん中
		if((m_RectSize.m_Right + m_Pos.x) > m_SandwichedSpaceCenterPos.x
			&& (m_RectSize.m_Left + m_Pos.x) < m_SandwichedSpaceCenterPos.x)
		{
			m_RectSize.m_Right -= EffectBasicSpeed;
			m_RectSize.m_Left += EffectBasicSpeed;
		}
		else
		{
			m_EndEffect = true;
		}
	}
}

void SandwichEffect::Render(void)
{
	m_pLibrary->SetVtxSize(m_DrawingID.m_VtxID, m_RectSize);
	m_pLibrary->Draw2D(m_DrawingID, (m_Pos - m_BasePointPos));
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
