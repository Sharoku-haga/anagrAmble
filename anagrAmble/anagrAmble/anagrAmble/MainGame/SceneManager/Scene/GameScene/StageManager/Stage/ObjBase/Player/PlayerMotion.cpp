//==================================================================================================================================//
//!< @file		PlayerMotion.cpp
//!< @brief		ar::PlayerMotionクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "PlayerMotion.h"
#include "../../../../../../../ControllerEnum.h"
#include "../../../../GameEventManager/GameEventManager.h"
#include "../../../../GameSceneSoundID.h"

namespace ar
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const		float		RectSizeCorrectionVal	= 3.f;				// 矩形サイズ補正値
const		float		MoveSpeed				= 4.f;				// プレイヤーの移動スピード
const		float		ScrollSpeed				= 0.2f;				// スクロールスピード(入場、退場スピード)
const		float		JumpSpeed				= 16.f;				// ジャンプスピード
const		float		JumpPower				= 36.f;				// ジャンプの初動
const		float		GravityPower			= 0.6f;				// 重力

}

/* Public Functions ------------------------------------------------------------------------------------------- */

PlayerMotion::PlayerMotion(const sl::fRect& rPlayerRect)
	: m_pLibrary(sl::ISharokuLibrary::Instance())
	, m_CurrentMotion(ENTERING)
	, m_PreviousMotion(ENTERING)
	, m_BasicRectSize(rPlayerRect)
	, m_CurrentMoveVector({ 0.0f, 0.0f })
	, m_DashSpeedCorrectionVal(0.0f)
	, m_IsFacingRight(true)
{
	InitializeVertex();
}

PlayerMotion::~PlayerMotion(void)
{}

const sl::SLVECTOR2& PlayerMotion::Control(const Player::MovableDirection& rMovableDirection)
{
	// 移動量を初期化
	m_CurrentMoveVector.x = 0.0f;
	m_CurrentMoveVector.y = 0.0f;

	// 前のモーションと違ったら、前のモーションのアニメーションを初期化して、
	// 前のモーションを更新しておく
	if(m_CurrentMotion != m_PreviousMotion)
	{
		m_pLibrary->ReturnUVAnimeInitialState(m_VtxID[m_PreviousMotion], m_UVAnimeID[m_PreviousMotion]);
		m_PreviousMotion = m_CurrentMotion;
	}

	if(m_CurrentMotion == DEATH)
	{	// モーションが死亡しているなら死亡処理を行い 即リターン
		ControlDeathMotion();
		ProcessSound();
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
		&& rMovableDirection.m_Down)
	{
		m_CurrentMoveVector.y -= JumpSpeed;
	}

	// 左右キー処理
	if(m_pLibrary->CheckCustomizeState(LEFT, sl::ON))
	{
		m_IsFacingRight = false;
		m_CurrentMoveVector.x -= MoveSpeed;
	}

	if(m_pLibrary->CheckCustomizeState(RIGHT, sl::ON))
	{
		m_IsFacingRight = true;
		m_CurrentMoveVector.x += MoveSpeed;
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

		m_CurrentMoveVector.x += m_DashSpeedCorrectionVal;
		ProcessSound();
		ProcessUVAnimation();
		return m_CurrentMoveVector;
	}
	else
	{
		m_FlightDurationCount = 0;
	}

	// ダッシュ補正値を入れる
	if( m_pLibrary->CheckCustomizeState(DASH, sl::PUSH)
		, m_pLibrary->CheckCustomizeState(DASH, sl::ON))
	{
		if(m_IsFacingRight)
		{
			m_DashSpeedCorrectionVal = MoveSpeed;
		}
		else
		{
			m_DashSpeedCorrectionVal = -MoveSpeed;
		}
	}
	else
	{
		m_DashSpeedCorrectionVal = 0;
	}

	// ジャンプ条件
	if(m_pLibrary->CheckCustomizeState(JUMP, sl::PUSH)
		&& rMovableDirection.m_Up
		&& RESULT_FAILED(rMovableDirection.m_Down)
		&& m_PreviousMotion != SQUATING
		&& m_PreviousMotion != SQUAT_WALKING)
	{
		m_CurrentMoveVector.y -= JumpPower;
		m_CurrentMotion = JUMPING;

		m_CurrentMoveVector.x += m_DashSpeedCorrectionVal;
		ProcessSound();
		m_pLibrary->PlayBackSound(static_cast<int>(GAME_SCENE_SOUND_ID::JUMP), sl::RESET_PLAY);
		ProcessUVAnimation();
		return m_CurrentMoveVector;
	}

	if(m_CurrentMoveVector.x == 0.0f 
		&& m_CurrentMoveVector.y == 0.0f)
	{	// 位置が変化していなかったら待機状態へ
		m_CurrentMotion = WAITING;
	}
	
	if(m_CurrentMoveVector.x != 0.0f)
	{
		m_CurrentMotion = WALKING;
	}

	// ダッシュ補正値が0じゃないなら走っているとみなす
	if(m_DashSpeedCorrectionVal != 0
		&& m_CurrentMoveVector.x != 0.0f)
	{
		m_CurrentMotion = RUNNING;
		m_CurrentMoveVector.x += m_DashSpeedCorrectionVal;
	}

	// しゃがみ動作
	if(m_pLibrary->CheckCustomizeState(SQUAT, sl::ON))
	{
		if(m_CurrentMotion == RUNNING)
		{
			m_CurrentMoveVector.x -= m_DashSpeedCorrectionVal;
		}

		if(m_CurrentMotion == WAITING)
		{
			m_CurrentMotion = SQUATING;
		}
		else
		{
			m_CurrentMotion = SQUAT_WALKING;
			m_CurrentMoveVector.x = m_CurrentMoveVector.x / 2;
		}
	}

	ProcessUVAnimation();
	ProcessSound();
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

void PlayerMotion::ChangeSquatingMotion(void)
{
	if(m_CurrentMotion == JUMPING)
	{
		return;
	}

	if(m_CurrentMoveVector.x != 0.0f)
	{
		m_CurrentMotion = SQUAT_WALKING;
	}
	else
	{
		m_CurrentMotion = SQUATING;
		m_pLibrary->ReturnUVAnimeInitialState(m_VtxID[m_PreviousMotion], m_UVAnimeID[m_PreviousMotion]);
	}

	ProcessUVAnimation();
	m_PreviousMotion = m_CurrentMotion;
}

bool PlayerMotion::RunEnteringMotion(void)
{
	if(m_CurrentMotion != ENTERING)
	{
		m_CurrentMotion = ENTERING;
	}

	if(m_RectSize[ENTERING].m_Left <= m_BasicRectSize.m_Left
		&& m_RectSize[ENTERING].m_Top <= m_BasicRectSize.m_Top
		&& m_RectSize[ENTERING].m_Right >= m_BasicRectSize.m_Right
		&& m_RectSize[ENTERING].m_Bottom >= m_BasicRectSize.m_Bottom)
	{
		m_CurrentMotion = WAITING;
		m_pLibrary->PlayBackSound(static_cast<int>(GAME_SCENE_SOUND_ID::WALK), sl::STOP);
		return true;
	}
	else
	{
		m_RectSize[ENTERING].m_Left	-= ScrollSpeed;
		m_RectSize[ENTERING].m_Top		-= ScrollSpeed * 2;
		m_RectSize[ENTERING].m_Right	+= ScrollSpeed;
		m_RectSize[ENTERING].m_Bottom	+= ScrollSpeed * 2;
		m_pLibrary->SetVtxSize(m_VtxID[ENTERING], m_RectSize[ENTERING]);
	}
	m_pLibrary->PlayBackSound(static_cast<int>(GAME_SCENE_SOUND_ID::WALK), sl::PLAY);
	// アニメーションを更新する
	m_pLibrary->UpdateUVAnime(m_VtxID[m_CurrentMotion], m_UVAnimeID[m_CurrentMotion]);
	return false;
}

bool PlayerMotion::RunExitingMotion(void)
{
	if(m_CurrentMotion != EXITING)
	{
		m_CurrentMotion = EXITING;
	}

	if(m_RectSize[EXITING] .m_Left >= 0.0f
		&& m_RectSize[EXITING] .m_Top >= 0.0f
		&& m_RectSize[EXITING] .m_Right <= 0.0f
		&& m_RectSize[EXITING] .m_Bottom <= 0.0f)
	{
		m_pLibrary->PlayBackSound(static_cast<int>(GAME_SCENE_SOUND_ID::WALK), sl::STOP);
		return true;
	}
	else
	{
		m_RectSize[EXITING] .m_Left += ScrollSpeed;
		m_RectSize[EXITING] .m_Top += ScrollSpeed * 2;
		m_RectSize[EXITING] .m_Right -= ScrollSpeed;
		m_RectSize[EXITING] .m_Bottom -= ScrollSpeed * 2;
		m_pLibrary->SetVtxSize(m_VtxID[EXITING], m_RectSize[EXITING] );
	}

	// アニメーションを更新する
	m_pLibrary->PlayBackSound(static_cast<int>(GAME_SCENE_SOUND_ID::WALK), sl::PLAY);
	m_pLibrary->UpdateUVAnime(m_VtxID[m_CurrentMotion], m_UVAnimeID[m_CurrentMotion]);
	return false;
}

bool PlayerMotion::IsCurrrentMotionDeath(void)
{
	if(m_CurrentMotion == DEATH)
	{
		return true;
	}

	return false;
}

bool PlayerMotion::IsCurrrentMotionJumping(void)
{
	if(m_CurrentMotion == JUMPING)
	{
		return true;
	}

	return false;
}

bool PlayerMotion::IsCurrrentMotionFalling(void)
{	
	if(m_CurrentMotion == FALLING)
	{
		return true;
	}

	return false;
}

bool PlayerMotion::IsCurrrentMotionSquat(void)
{
	if(m_CurrentMotion == SQUATING 
		|| m_CurrentMotion == SQUAT_WALKING)
	{
		return true;
	}
	return false;
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void PlayerMotion::InitializeVertex(void)
{
	// 状態ごとのVertexとUVアニメのIDと矩形サイズを作成
	m_VtxID.resize(ID_MAX);
	m_UVAnimeID.resize(ID_MAX);
	m_RectSize.resize(ID_MAX);

	// 待機
	{
		m_RectSize[WAITING] = m_BasicRectSize;
		sl::fRect		uv = { 0.0f, 0.0f, 0.05f, 0.176f };
		m_VtxID[WAITING] = m_pLibrary->CreateVertex2D(m_RectSize[WAITING], uv);
		m_UVAnimeID[WAITING] = m_pLibrary->RegisterUVAnimeID(m_VtxID[WAITING], 17, true);
		m_pLibrary->CreateUVAnimeData(m_VtxID[WAITING], m_UVAnimeID[WAITING], 17, 0, uv, 8);
		m_RectSize[WAITING].m_Left += RectSizeCorrectionVal;
		m_RectSize[WAITING].m_Right -= RectSizeCorrectionVal;
	}

	// 歩き
	{
		m_RectSize[WALKING] = m_BasicRectSize;
		sl::fRect		uv = { 0.5f, 0.177f, 0.55f, 0.354f };
		m_VtxID[WALKING] = m_pLibrary->CreateVertex2D(m_RectSize[WALKING], uv);
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
		m_RectSize[WALKING].m_Left += RectSizeCorrectionVal;
		m_RectSize[WALKING].m_Right -= RectSizeCorrectionVal;
	}

	// 走っている
	{
		m_RectSize[RUNNING] = m_BasicRectSize;
		sl::fRect		uv = { 0.0f, 0.355f, 0.05f, 0.533f };
		m_VtxID[RUNNING] = m_pLibrary->CreateVertex2D(m_RectSize[RUNNING], uv);
		m_UVAnimeID[RUNNING] = m_pLibrary->RegisterUVAnimeID(m_VtxID[RUNNING], 10, true);
		m_pLibrary->CreateUVAnimeData(m_VtxID[RUNNING], m_UVAnimeID[RUNNING], 10, 0, uv, 2);
		m_RectSize[RUNNING].m_Left += RectSizeCorrectionVal;
		m_RectSize[RUNNING].m_Right -= RectSizeCorrectionVal;
	}

	// ジャンプ
	{
		m_RectSize[JUMPING] = m_BasicRectSize;
		sl::fRect		uv = { 0.5f, 0.355f, 0.55f, 0.533f };
		m_VtxID[JUMPING] = m_pLibrary->CreateVertex2D(m_RectSize[JUMPING], uv);
		m_UVAnimeID[JUMPING] = m_pLibrary->RegisterUVAnimeID(m_VtxID[JUMPING], 4);
		m_pLibrary->CreateUVAnimeData(m_VtxID[JUMPING], m_UVAnimeID[JUMPING], 4, 0, uv, 2);
		m_RectSize[JUMPING].m_Left += RectSizeCorrectionVal;
		m_RectSize[JUMPING].m_Right -= RectSizeCorrectionVal;
	}

	// しゃがみ
	// Vertex作成はm_BasicRectSizeを元に作成するが、m_RectSize[SQUATING]にはサイズを変更していれる
	{
		sl::fRect		uv = { 0.15f, 0.533f, 0.2f, 0.711f };
		m_VtxID[SQUATING] = m_pLibrary->CreateVertex2D(m_BasicRectSize, uv);
		m_UVAnimeID[SQUATING] = m_pLibrary->RegisterUVAnimeID(m_VtxID[SQUATING], 1, true);
		m_pLibrary->CreateUVAnimeData(m_VtxID[SQUATING], m_UVAnimeID[SQUATING], 1, 0, uv, 3);

		m_RectSize[SQUATING].m_Left = m_BasicRectSize.m_Left + RectSizeCorrectionVal;
		m_RectSize[SQUATING].m_Top = -0.0f;
		m_RectSize[SQUATING].m_Right = m_BasicRectSize.m_Right - RectSizeCorrectionVal;
		m_RectSize[SQUATING].m_Bottom = m_BasicRectSize.m_Bottom;
	}

	// しゃがみ歩き
	// Vertex作成はm_BasicRectSizeを元に作成するが、m_RectSize[SQUATING]にはサイズを変更していれる
	{
		sl::fRect		uv = { 0.15f, 0.533f, 0.2f, 0.711f };
		m_VtxID[SQUAT_WALKING] = m_pLibrary->CreateVertex2D(m_BasicRectSize, uv);
		m_UVAnimeID[SQUAT_WALKING] = m_pLibrary->RegisterUVAnimeID(m_VtxID[SQUAT_WALKING], 3, true);
		m_pLibrary->CreateUVAnimeData(m_VtxID[SQUAT_WALKING], m_UVAnimeID[SQUAT_WALKING], 3, 0, uv, 3);

		// アニメーションの順番指定
		std::vector<int> animeOrder;
		for(int i = 0; i < 3; ++i)
		{
			animeOrder.push_back(i);
		}
		// 逆に番号を入れる
		for(int i = 2; i >= 0; --i)
		{
			animeOrder.push_back(i);
		}
		m_pLibrary->SeUVtAnimeOrder(m_VtxID[SQUAT_WALKING], m_UVAnimeID[SQUAT_WALKING], animeOrder);

		m_RectSize[SQUAT_WALKING].m_Left = m_BasicRectSize.m_Left + RectSizeCorrectionVal;
		m_RectSize[SQUAT_WALKING].m_Top = 0.0f;
		m_RectSize[SQUAT_WALKING].m_Right = m_BasicRectSize.m_Right - RectSizeCorrectionVal;
		m_RectSize[SQUAT_WALKING].m_Bottom = m_BasicRectSize.m_Bottom;
	}

	// 落下(今のところは待機と一緒)
	{
		m_RectSize[FALLING] = m_BasicRectSize;
		sl::fRect		uv = { 0.75f, 0.355f, 0.8f, 0.533f };
		m_VtxID[FALLING] = m_pLibrary->CreateVertex2D(m_BasicRectSize, uv);
		m_UVAnimeID[FALLING] = m_pLibrary->RegisterUVAnimeID(m_VtxID[FALLING], 1);
		m_pLibrary->CreateUVAnimeData(m_VtxID[FALLING], m_UVAnimeID[FALLING], 1, 0, uv, 10);

		m_RectSize[FALLING].m_Left += RectSizeCorrectionVal;
		m_RectSize[FALLING].m_Right -= RectSizeCorrectionVal;
	}

	// 死亡
	{
		m_RectSize[DEATH] = m_BasicRectSize;
		sl::fRect		uv = { 0.35f, 0.533f, 0.4f, 0.711f };
		m_VtxID[DEATH] = m_pLibrary->CreateVertex2D(m_BasicRectSize, uv);
		m_UVAnimeID[DEATH] = m_pLibrary->RegisterUVAnimeID(m_VtxID[DEATH], 10);
		m_pLibrary->CreateUVAnimeData(m_VtxID[DEATH], m_UVAnimeID[DEATH], 10, 0, uv, 4);
	}

	// 入場
	// 入場の最初の矩形サイズは0.0f
	{
		m_RectSize[ENTERING].m_Left = 0.0f;
		m_RectSize[ENTERING].m_Top = 0.0f;
		m_RectSize[ENTERING].m_Right = 0.0f;
		m_RectSize[ENTERING].m_Bottom = 0.0f;
		
		sl::fRect		uv = { 0.0f, 0.711f, 0.05f, 0.888f };
		m_VtxID[ENTERING] = m_pLibrary->CreateVertex2D(m_RectSize[ENTERING], uv);
		m_UVAnimeID[ENTERING] = m_pLibrary->RegisterUVAnimeID(m_VtxID[ENTERING], 6, true);
		m_pLibrary->CreateUVAnimeData(m_VtxID[ENTERING], m_UVAnimeID[ENTERING], 6, 0, uv, 5);

		// アニメーションの順番指定
		std::vector<int> animeOrder;
		for(int i = 0; i < 6; ++i)
		{
			animeOrder.push_back(i);
		}
		// 逆に番号を入れる
		for(int i = 5; i >= 0; --i)
		{
			animeOrder.push_back(i);
		}

		m_pLibrary->SeUVtAnimeOrder(m_VtxID[ENTERING], m_UVAnimeID[ENTERING], animeOrder);
	}

	// 退場
	{
		m_RectSize[EXITING]  = m_BasicRectSize;
		sl::fRect		uv = { 0.35f, 0.711f, 0.4f, 0.888f };
		m_VtxID[EXITING] = m_pLibrary->CreateVertex2D(m_RectSize[EXITING] , uv);
		m_UVAnimeID[EXITING] = m_pLibrary->RegisterUVAnimeID(m_VtxID[EXITING], 6, true);
		m_pLibrary->CreateUVAnimeData(m_VtxID[EXITING], m_UVAnimeID[EXITING], 6, 0, uv, 5);

		// アニメーションの順番指定
		std::vector<int> animeOrder;
		for(int i = 0; i < 6; ++i)
		{
			animeOrder.push_back(i);
		}
		// 逆に番号を入れる
		for(int i = 5; i >= 0; --i)
		{
			animeOrder.push_back(i);
		}

		m_pLibrary->SeUVtAnimeOrder(m_VtxID[EXITING], m_UVAnimeID[EXITING], animeOrder);
	}
}

void PlayerMotion::ControlDeathMotion(void)
{
	if(m_pLibrary->CheckLastNumCurrnttUVAnime(m_VtxID[DEATH], m_UVAnimeID[DEATH]))
	{
		// ここで死亡動作の処理(主にアニメーションを書く)
		GameEventManager::Instance().TriggerSynEvent("player_death_anime_end");		// アニメが終了したらイベント通知をする
		m_pLibrary->PlayBackSound(static_cast<int>(GAME_SCENE_SOUND_ID::DEATH), sl::STOP_RESET);
	}
}

void PlayerMotion::ProcessUVAnimation(void)
{
	// アニメーションを更新する
	m_pLibrary->UpdateUVAnime(m_VtxID[m_CurrentMotion], m_UVAnimeID[m_CurrentMotion]);

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

void PlayerMotion::ProcessSound(void)
{
	if(m_CurrentMotion == WALKING)
	{
		m_pLibrary->PlayBackSound(static_cast<int>(GAME_SCENE_SOUND_ID::WALK), sl::PLAY);
		return;
	}
	else
	{
		m_pLibrary->PlayBackSound(static_cast<int>(GAME_SCENE_SOUND_ID::WALK), sl::STOP);
	}

	if(m_CurrentMotion == RUNNING)
	{
		m_pLibrary->PlayBackSound(static_cast<int>(GAME_SCENE_SOUND_ID::RUN), sl::PLAY);
		return;
	}
	else
	{
		m_pLibrary->PlayBackSound(static_cast<int>(GAME_SCENE_SOUND_ID::RUN), sl::STOP);
	}

	if(m_CurrentMotion == DEATH)
	{
		m_pLibrary->PlayBackSound(static_cast<int>(GAME_SCENE_SOUND_ID::DEATH), sl::PLAY);
		return;
	}
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
