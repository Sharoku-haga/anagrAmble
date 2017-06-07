//==================================================================================================================================//
//!< @file		PlayerMotion.cpp
//!< @brief		ar::PlayerMotionクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "PlayerMotion.h"
#include "../../../../../../../ControllerEnum.h"
#include "../../../../GameEventManager/GameEventManager.h"

namespace ar
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const		float		MoveSpeed = 6.f;				//!< プレイヤーの移動スピード
const		float		JumpSpeed = 8.f;				//!< ジャンプスピード
const		float		JumpPower = 36.f;				//!< ジャンプの初動
const		float		GravityPower = 0.16f;			//!< 重力

}
/* Public Functions ------------------------------------------------------------------------------------------- */

PlayerMotion::PlayerMotion(const sl::fRect& rPlayerRect)
	: m_pLibrary(sl::ISharokuLibrary::Instance())
	, m_CurrentMotion(WAITING)
	, m_CurrentMoveVector({ 0.0f, 0.0f })
	, m_IsFacingRight(false)
{
	InitializeVertex(rPlayerRect);
}

PlayerMotion::~PlayerMotion(void)
{}

const sl::SLVECTOR2& PlayerMotion::Control(const Player::MovableDirection& rMovableDirection)
{
	// 移動量を初期化
	m_CurrentMoveVector.x = 0.0f;
	m_CurrentMoveVector.y = 0.0f;

	if(m_CurrentMotion == DEATH)
	{
		// 死亡処理を行い 即リターン
		return m_CurrentMoveVector;
	}

	if(m_CurrentMotion == JUMPING
		&& RESULT_FAILED(rMovableDirection.m_Up))
	{
		m_CurrentMotion = WAITING;
		m_FlightDurationCount = 0;
	}

	// ジャンプ処理
	if(m_CurrentMotion == JUMPING
		&& rMovableDirection.m_Up
		&& rMovableDirection.m_Down
		)
	{
		m_CurrentMoveVector.y -= JumpSpeed;
	}

	// 左右キー処理
	if(m_pLibrary->CheckCustomizeState(LEFT, sl::ON)
		&& rMovableDirection.m_Left)
	{
		m_CurrentMoveVector.x -= MoveSpeed;
		m_IsFacingRight = false;
	}

	if(m_pLibrary->CheckCustomizeState(RIGHT, sl::ON)
		&& rMovableDirection.m_Right)
	{
		m_CurrentMoveVector.x += MoveSpeed;
		m_IsFacingRight = true;
	}

	if(rMovableDirection.m_Down)
	{	// 下の空間に何もないなら重力をかけてreturnする
		++m_FlightDurationCount;
		m_CurrentMoveVector.y += GravityPower * m_FlightDurationCount;
		return m_CurrentMoveVector;
	}
	else
	{
		m_CurrentMotion = WALKING;
		m_FlightDurationCount = 0;
	}


	if(m_pLibrary->CheckCustomizeState(DASH, sl::ON))
	{
		m_CurrentMoveVector.x = m_CurrentMoveVector.x * 2;
		m_CurrentMotion = RUNNING;
	}

	if(m_pLibrary->CheckCustomizeState(JUMP, sl::ON)
		&& m_CurrentMotion != JUMPING
		&& rMovableDirection.m_Up
		&& !rMovableDirection.m_Down)
	{
		m_CurrentMoveVector.y -= JumpPower;
		m_CurrentMotion = JUMPING;
	}

	if(m_CurrentMoveVector.x == 0.0f && m_CurrentMoveVector.y == 0.0f)
	{	// 位置が変化していなかったら待機状態へ
		m_CurrentMotion = WAITING;
	}

	return m_CurrentMoveVector;
}


/* Private Functions ------------------------------------------------------------------------------------------ */

void PlayerMotion::InitializeVertex(const sl::fRect& rPlayerRect)
{
	// 状態ごとのVertexを作成
	m_VtxID.resize(ID_MAX);

	// 待機
	{
		const sl::fRect		uv = { 0.0f, 0.0f, 1.0f, 1.0f };
		m_VtxID[WAITING] = m_pLibrary->CreateVertex2D(rPlayerRect, uv);
	}

	// 歩き
	{
		const sl::fRect		uv = { 0.0f, 0.0f, 1.0f, 1.0f };
		m_VtxID[WALKING] = m_pLibrary->CreateVertex2D(rPlayerRect, uv);
	}

	// 走っている
	{
		const sl::fRect		uv = { 0.0f, 0.0f, 1.0f, 1.0f };
		m_VtxID[RUNNING] = m_pLibrary->CreateVertex2D(rPlayerRect, uv);
	}

	// ジャンプ
	{
		const sl::fRect		uv = { 0.0f, 0.0f, 1.0f, 1.0f };
		m_VtxID[JUMPING] = m_pLibrary->CreateVertex2D(rPlayerRect, uv);
	}

	// 落下(今のところは待機と一緒)
	{
		m_VtxID[FALLING] = m_VtxID[WAITING];
	}

	// 死亡
	{
		const sl::fRect		uv = { 0.0f, 0.0f, 1.0f, 1.0f };
		m_VtxID[DEATH] = m_pLibrary->CreateVertex2D(rPlayerRect, uv);
	}
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
