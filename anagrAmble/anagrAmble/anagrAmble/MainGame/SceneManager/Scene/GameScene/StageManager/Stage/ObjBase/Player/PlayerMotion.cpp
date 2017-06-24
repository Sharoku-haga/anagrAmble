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

const		float		MoveSpeed		= 6.f;				// プレイヤーの移動スピード
const		float		JumpSpeed		= 16.f;				// ジャンプスピード
const		float		JumpPower		= 36.f;				// ジャンプの初動
const		float		GravityPower	= 0.6f;				// 重力

}
/* Public Functions ------------------------------------------------------------------------------------------- */

PlayerMotion::PlayerMotion(const sl::fRect& rPlayerRect)
	: m_pLibrary(sl::ISharokuLibrary::Instance())
	, m_CurrentMotion(WAITING)
	, m_PreviousMotion(WAITING)
	, m_CurrentMoveVector({ 0.0f, 0.0f })
	, m_IsFacingRight(true)
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
	{	// モーションが死亡しているなら死亡処理を行い 即リターン
		ControlDeathMotion();
		ProcessUVAnimation();
		return m_CurrentMoveVector;
	}

	if(m_CurrentMotion == JUMPING
		&& RESULT_FAILED(rMovableDirection.m_Up))
	{	// ジャンプ中に上にぶつかったら落下モーションへ移行
		m_CurrentMotion = FALLING;
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

		if(m_CurrentMotion == JUMPING 
			&& JumpSpeed <= GravityPower * m_FlightDurationCount)
		{
			m_CurrentMotion = FALLING;
			m_FlightDurationCount = 0;
		}

		if(m_CurrentMotion != FALLING && m_CurrentMotion != JUMPING)
		{
			m_CurrentMotion = FALLING;
			m_FlightDurationCount = 0;
		}

		ProcessUVAnimation();
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

	if(m_pLibrary->CheckCustomizeState(JUMP, sl::PUSH)
		&& m_CurrentMotion != JUMPING
		&& m_CurrentMotion != FALLING
		&& rMovableDirection.m_Up
		&& RESULT_FAILED(rMovableDirection.m_Down))
	{
		m_CurrentMoveVector.y -= JumpPower;
		m_CurrentMotion = JUMPING;
	}

	if(m_CurrentMoveVector.x == 0.0f && m_CurrentMoveVector.y == 0.0f)
	{	// 位置が変化していなかったら待機状態へ
		m_CurrentMotion = WAITING;
	}

	ProcessUVAnimation();
	return m_CurrentMoveVector;
}

void PlayerMotion::ChangeWaitingMotion(void)
{
	m_CurrentMotion = PlayerMotion::MOTION_ID::WAITING;
	m_pLibrary->ReturnUVAnimeInitialState(m_VtxID[m_PreviousMotion], m_UVAnimeID[m_PreviousMotion]);
	m_PreviousMotion = m_CurrentMotion;
}

void PlayerMotion::ChangeDeathMotion(void)
{
	m_CurrentMotion = PlayerMotion::MOTION_ID::DEATH;
	m_pLibrary->ReturnUVAnimeInitialState(m_VtxID[m_PreviousMotion], m_UVAnimeID[m_PreviousMotion]);
	m_PreviousMotion = m_CurrentMotion;
}

bool PlayerMotion::IsCurrrentMotionDeath(void)
{
	if(m_CurrentMotion == DEATH)
	{
		return true;
	}

	return false;
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void PlayerMotion::InitializeVertex(const sl::fRect& rPlayerRect)
{
	// 状態ごとのVertexとUVアニメのIDを個数分を作成
	m_VtxID.resize(ID_MAX);
	m_UVAnimeID.resize(ID_MAX);

	// 待機
	{
		const sl::fRect		uv = { 0.0f, 0.0f, 0.05f, 0.176f };
		m_VtxID[WAITING] = m_pLibrary->CreateVertex2D(rPlayerRect, uv);
		m_UVAnimeID[WAITING] = m_pLibrary->RegisterUVAnimeID(m_VtxID[WAITING], 5, true);
		m_pLibrary->CreateUVAnimeData(m_VtxID[WAITING], m_UVAnimeID[WAITING], 5, 0, uv, 8);
	}

	// 歩き
	{
		const sl::fRect		uv = { 0.5f, 0.177f, 0.55f, 0.354f };
		m_VtxID[WALKING] = m_pLibrary->CreateVertex2D(rPlayerRect, uv);
		m_UVAnimeID[WALKING] = m_pLibrary->RegisterUVAnimeID(m_VtxID[WALKING], 7, true);
		m_pLibrary->CreateUVAnimeData(m_VtxID[WALKING], m_UVAnimeID[WALKING], 7, 0, uv, 3);

		// アニメーションの順番指定

		std::vector<int> animeOrder;
		for(int i = 0; i < 7; ++i)
		{
			animeOrder.push_back(i);
		}
		// 逆に番号を入れる
		for(int i = 6; i >= 0; --i)
		{
			animeOrder.push_back(i);
		}

		m_pLibrary->SeUVtAnimeOrder(m_VtxID[WALKING], m_UVAnimeID[WALKING], animeOrder);
	}

	// 走っている
	{
		const sl::fRect		uv = { 0.0f, 0.355f, 0.05f, 0.533f };
		m_VtxID[RUNNING] = m_pLibrary->CreateVertex2D(rPlayerRect, uv);
		m_UVAnimeID[RUNNING] = m_pLibrary->RegisterUVAnimeID(m_VtxID[RUNNING], 9, true);
		m_pLibrary->CreateUVAnimeData(m_VtxID[RUNNING], m_UVAnimeID[RUNNING], 9, 0, uv, 2);
	}

	// ジャンプ
	{
		const sl::fRect		uv = { 0.5f, 0.355f, 0.55f, 0.533f };
		m_VtxID[JUMPING] = m_pLibrary->CreateVertex2D(rPlayerRect, uv);
		m_UVAnimeID[JUMPING] = m_pLibrary->RegisterUVAnimeID(m_VtxID[JUMPING], 4);
		m_pLibrary->CreateUVAnimeData(m_VtxID[JUMPING], m_UVAnimeID[JUMPING], 4, 0, uv, 2);
	}

	// 落下(今のところは待機と一緒)
	{
		const sl::fRect		uv = { 0.75f, 0.355f, 0.8f, 0.533f };
		m_VtxID[FALLING] = m_pLibrary->CreateVertex2D(rPlayerRect, uv);
		m_UVAnimeID[FALLING] = m_pLibrary->RegisterUVAnimeID(m_VtxID[FALLING], 1);
		m_pLibrary->CreateUVAnimeData(m_VtxID[FALLING], m_UVAnimeID[FALLING], 1, 0, uv, 10);
	}

	// 死亡
	{
		const sl::fRect		uv = { 0.35f, 0.533f, 0.4f, 0.711f };
		m_VtxID[DEATH] = m_pLibrary->CreateVertex2D(rPlayerRect, uv);
		m_UVAnimeID[DEATH] = m_pLibrary->RegisterUVAnimeID(m_VtxID[DEATH], 10);
		m_pLibrary->CreateUVAnimeData(m_VtxID[DEATH], m_UVAnimeID[DEATH], 10, 0, uv, 4);
	}
}

void PlayerMotion::ControlDeathMotion(void)
{
	if(m_pLibrary->CheckLastNumCurrnttUVAnime(m_VtxID[DEATH], m_UVAnimeID[DEATH]))
	{
		// ここで死亡動作の処理(主にアニメーションを書く)
		GameEventManager::Instance().TriggerSynEvent("player_death_anime_end");		// アニメが終了したらイベント通知をする
	}
}

void PlayerMotion::ProcessUVAnimation(void)
{
	// アニメーションを更新する
	m_pLibrary->UpdateUVAnime(m_VtxID[m_CurrentMotion], m_UVAnimeID[m_CurrentMotion]);

	// 前のモーションと違ったら、前のモーションのアニメーションを初期化して、
	// 前のモーションを更新しておく
	if(m_CurrentMotion != m_PreviousMotion)
	{
		m_pLibrary->ReturnUVAnimeInitialState(m_VtxID[m_PreviousMotion], m_UVAnimeID[m_PreviousMotion]);
		m_PreviousMotion = m_CurrentMotion;
	}

	// アニメーション反転処理
	sl::fRect uv = m_pLibrary->GetUVRect(m_VtxID[m_CurrentMotion]);
	if(m_IsFacingRight
		&& uv.m_Left > uv.m_Right)
	{
		float tmp = uv.m_Left;
		uv.m_Left = uv.m_Right;
		uv.m_Right = tmp;
		m_pLibrary->SetVtxUV(m_VtxID[m_CurrentMotion], uv);
	}
	else if(RESULT_FAILED(m_IsFacingRight)
			&& uv.m_Left < uv.m_Right)
	{
		float tmp = uv.m_Left;
		uv.m_Left = uv.m_Right;
		uv.m_Right = tmp;
		m_pLibrary->SetVtxUV(m_VtxID[m_CurrentMotion], uv);
	}
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
