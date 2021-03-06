﻿//==================================================================================================================================//
//!< @file		Player.cpp
//!< @brief		ar::Playerクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include <cmath> 
#include "Player.h"
#include "PlayerMotion.h"
#include "PlayerMode.h"
#include "../../../StageDataManager.h"
#include "../../CollisionManager.h"
#include "../../../../../../../ControllerEnum.h"
#include "../../../../GameEventManager/GameEventManager.h"
#include "../../../../GameEventManager/EventListener.h"
#include "../../../StageDataChangeManager.h"
#include "../../../../GameSceneSoundID.h"
#include "../../../../../../SoundManager/SceneSoundManager.h"

namespace ar
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const		int			WidthChipCount					= 1;				// プレイヤーの矩形の横のチップ数
const		int			HeightChipCount					= 2;				// プレイヤーの矩形の縦のチップ数
const		int			GoddessPointMaxVal				= 3;				// 女神の加護の最大数
const		float		CollisionCorrectionVal			= 12.f;				// 衝突における判定の補正値
const		float		DownCollisionCorrectionVal		= 1.0f;				// 下の衝突判定補正値
const		float		RightCollisionCorrectionVal		= -1.0f;			// 右の衝突判定補正値
const		float		LeftCollisionCorrectionVal		= -0.5f;			// 左の衝突判定補正値
const		float		DeathAreaCorrectionVal			= 15.f;				// 死亡判定エリアの補正値
const		float		FallLimitVal					= 1368.f;			// 落下限界値. 
const		float		BeltConverSpeed					= 15.f;				// ベルトコンベアーのスピード
	
}

/* Public Functions ------------------------------------------------------------------------------------------- */

Player::Player(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
				, const Stage::INDEX_DATA& rStageIndexData, int playerTexID)
	: ObjBase(pStageDataManager, pCollisionManager, rStageIndexData)
	, m_pPlayerMotion(nullptr)
	, m_pPlayerMode(nullptr)
	, m_GoalPos({ 0.0f, 0.0f })
	, m_GoddessPointCount(GoddessPointMaxVal)
{
	m_TypeID = PLAYER;		// タイプID
	m_DrawingID.m_TexID = playerTexID;	// テクスチャーIDを格納
}

Player::~Player(void)
{
	sl::DeleteSafely(&m_pPlayerMode);
	sl::DeleteSafely(&m_pPlayerMotion);

	for(auto& vtxID : m_VtxID)
	{
		m_pLibrary->ReleaseVertex2D(vtxID);
	}
}

bool Player::StartStage(void)
{
	if(m_pPlayerMotion->RunEnteringMotion())
	{	
		return true;
	}

	return false;
}

bool Player::CompleteStage(void)
{
	if(m_Pos.x != m_GoalPos.x)
	{	// プレイヤーのモードをリセットする
		m_pPlayerMode->Reset();
		m_Pos.x = m_GoalPos.x;
	}

	if(m_pPlayerMotion->RunExitingMotion())
	{
		return true;
	}

	return false;
}

void Player::Control(void)
{
	// イベント処理
	HandleEvent();

	if(m_Pos.y > FallLimitVal && RESULT_FAILED(m_pPlayerMotion->IsCurrrentMotionDeath()))
	{	// 落下限界値以上落ちていたら死亡状態にし、女神の加護の回数も減らす
		m_pPlayerMotion->ChangeDeathMotion();
	}

	// 状態による処理をおこなう
	sl::SLVECTOR2 currentMoveVector = m_pPlayerMotion->Control(m_MovableDirection);
	m_Pos +=  currentMoveVector;
	m_RectSize = m_pPlayerMotion->GetCurrentMotionRectSize();


	if(m_pPlayerMotion->IsCurrrentMotionDeath())
	{	// 死亡動作ならここから下の処理はいらないので、
		// 衝突チェックにnullptrを渡して即return;
		m_pCollisionManager->SetPlayerPointer(nullptr);
		return;
	}

	if(currentMoveVector.x != 0.0f || currentMoveVector.y != 0.0f)
	{	// 動いていたらイベントをとばす
		GameEventManager::Instance().TriggerSynEvent("player_move");
	}

	// 移動方向をすべてtrueにする
	m_MovableDirection.m_Up		= true;
	m_MovableDirection.m_Down	= true;
	m_MovableDirection.m_Right	= true;
	m_MovableDirection.m_Left	= true;
	
	CalculateStageIndexData();

	// モードによる処理
	m_pPlayerMode->Control();

	if(m_pLibrary->CheckCustomizeState(SPECIAL_ACTION, sl::PUSH))
	{	// 特殊アクションボタンが押されたら、イベントを通知する
		GameEventManager::Instance().ReceiveEvent("special_action");
	}

	if(m_pLibrary->CheckCustomizeState(TIME_RETURN_L, sl::ON) 
		&& m_pLibrary->CheckCustomizeState(TIME_RETURN_R, sl::PUSH)
		&& m_GoddessPointCount > 0
		&& m_pStageDataManager->ExistStockStageData())
	{	// 時戻しボタンが押されたら イベントを通知する
		GameEventManager::Instance().ReceiveEvent("space_change_return_start");
	}

	m_pCollisionManager->SetPlayerPointer(this);
}

void Player::Draw(void)
{
	m_pPlayerMode->Draw();
	m_DrawingID.m_VtxID = m_pPlayerMotion->GetCurrentMotionVtxID();
	m_pLibrary->Draw2D( m_DrawingID, (m_Pos - m_BasePointPos));
}

bool Player::IsFacingRight(void)
{
	return m_pPlayerMotion->IsFacingRight(); 
}

void Player::Initialize(void)
{
	// 位置座標計算
	m_Pos.x = m_StageIndexData.m_XIndexNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YIndexNum * m_StageChipSize;
	GameEventManager::Instance().TriggerSynEvent("player_move");

	RegisterEvent();		// イベント登録

	// 矩形サイズを設定
	m_RectSize.m_Left	= -(m_StageChipSize / 2) * WidthChipCount;
	m_RectSize.m_Top	= -(m_StageChipSize / 2) * HeightChipCount;
	m_RectSize.m_Right	=  (m_StageChipSize / 2) * WidthChipCount;
	m_RectSize.m_Bottom =  (m_StageChipSize / 2) * HeightChipCount;
 
	m_pPlayerMotion = new PlayerMotion(m_RectSize);
	m_pPlayerMode = new PlayerMode(m_pStageDataManager, m_pCollisionManager, this, m_DrawingID.m_TexID);
	m_pPlayerMode->InitializeAnchor();

	// 移動可能方向フラグの初期化
	m_MovableDirection.m_Up		= false;
	m_MovableDirection.m_Down	= false;
	m_MovableDirection.m_Right	= false;
	m_MovableDirection.m_Left	= false;

}

void Player::ChangeStagePos(short yIndexNum, short xIndexNum)
{
	m_StageIndexData.m_YIndexNum = yIndexNum;
	m_StageIndexData.m_XIndexNum = xIndexNum;

	m_Pos.x = m_StageIndexData.m_XIndexNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YIndexNum * m_StageChipSize;
	GameEventManager::Instance().TriggerSynEvent("player_move");
}

void Player::ProcessCollision(const CollisionManager::CollisionData& rData)
{
	if(m_pPlayerMotion->IsCurrrentMotionDeath())
	{	// 死亡動作ならここから下の処理はいらないので、即return
		return;
	}

	switch(rData.m_ObjType)
	{
	case NORMAL_B:
		break;

	case GROUND_B:
		break;

	case ELECTICAL_B:
		if(RESULT_FAILED(m_pPlayerMotion->IsCurrrentMotionDeath())
			&& CheckCollisionDeathArea(rData.m_ObjRect))
		{
			m_pPlayerMotion->ChangeDeathMotion();
			SceneSoundManager::Instance().PlayBackSound(static_cast<int>(GAME_SCENE_SOUND_ID::HIT), sl::PLAY);
		}
		return;
		break;

	case LEVER:
		return;
		break;

	case GOAL:
		m_GoalPos = rData.m_ObjPos;
		return;
		break;

	case GOAL_KEY:
		return;
		break;

	case LOCKED_GOAL:
		m_GoalPos = rData.m_ObjPos;
		return;
		break;

	case BELT_CONVER_B_R:
		m_Pos.x += BeltConverSpeed;
		break;

	case BELT_CONVER_B_L:
		m_Pos.x -= BeltConverSpeed;
		break;

	case SPEAR:
		if(RESULT_FAILED(m_pPlayerMotion->IsCurrrentMotionDeath())
			&& CheckCollisionDeathArea(rData.m_ObjRect))
		{
			m_pPlayerMotion->ChangeDeathMotion();
			SceneSoundManager::Instance().PlayBackSound(static_cast<int>(GAME_SCENE_SOUND_ID::HIT), sl::PLAY);
		}
		break;

	case ANCHOR:
		return;
		break;

	case SWITCH_OPERATING_AREA_ON:
		return;
		break;

	case SWITCH_OPERATING_AREA_OFF:
		return;
		break;

	case ENTRANCE:
		return;
		break;

	default:
		// do nothing
		break;
	}

	// 移動可能な方向の確認と補正値を足す
		
	// 右方向
	if(m_Pos.x < rData.m_ObjPos.x
		&& m_CurrentRectData.m_Right < rData.m_ObjPos.x
		&&  std::abs(m_Pos.y - rData.m_ObjPos.y) < (m_StageChipSize + m_StageChipSize / 2 - CollisionCorrectionVal))
	{
		m_MovableDirection.m_Right = false;
		m_Pos.x -= ((m_CurrentRectData.m_Right - rData.m_ObjRect.m_Left) + RightCollisionCorrectionVal);
	}

	// 左方向
	if(m_Pos.x > rData.m_ObjPos.x
		&& m_CurrentRectData.m_Left > rData.m_ObjPos.x
		&& std::abs(m_Pos.y - rData.m_ObjPos.y) < (m_StageChipSize + m_StageChipSize / 2 - CollisionCorrectionVal))
	{
		m_MovableDirection.m_Left = false;
		m_Pos.x += ((rData.m_ObjRect.m_Right - m_CurrentRectData.m_Left) + LeftCollisionCorrectionVal);
	}

	// 上方向
	if(m_Pos.y > rData.m_ObjPos.y
		&& m_CurrentRectData.m_Top < rData.m_ObjRect.m_Bottom
		&& std::abs(m_Pos.x - rData.m_ObjPos.x) < (m_StageChipSize - CollisionCorrectionVal))
	{
		if(m_Pos.y > rData.m_ObjRect.m_Bottom
			&& RESULT_FAILED(m_pPlayerMotion->IsCurrrentMotionJumping())
			&& RESULT_FAILED(m_pPlayerMotion->IsCurrrentMotionFalling()))
		{
			// しゃがみ処理へ変更
			m_pPlayerMotion->ChangeSquatingMotion();
			m_RectSize = m_pPlayerMotion->GetCurrentMotionRectSize();
			m_CurrentRectData.m_Left = m_Pos.x + m_RectSize.m_Left;
			m_CurrentRectData.m_Top = m_Pos.y;
			m_CurrentRectData.m_Right = m_Pos.x + m_RectSize.m_Right;
			m_CurrentRectData.m_Bottom = m_Pos.y + m_RectSize.m_Bottom;
		}
		else
		{
			m_MovableDirection.m_Up = false;
			m_Pos.y += rData.m_ObjRect.m_Bottom - m_CurrentRectData.m_Top;
		}

	}

	// 下方向
	if(m_Pos.y < rData.m_ObjPos.y
		&& m_CurrentRectData.m_Bottom < rData.m_ObjPos.y
		&& std::abs(m_Pos.x - rData.m_ObjPos.x) < (m_StageChipSize - CollisionCorrectionVal))
	{
		m_MovableDirection.m_Down = false;

		// はみだした部分が下の衝突補正値より大きかったら、調整する
		if( m_CurrentRectData.m_Bottom - rData.m_ObjRect.m_Top > DownCollisionCorrectionVal)
		{
			m_Pos.y -= m_CurrentRectData.m_Bottom - rData.m_ObjRect.m_Top;
		}
	}

	// 変更した座標を元にインデックスデータを計算しなおす
	CalculateStageIndexData();

	GameEventManager::Instance().TriggerSynEvent("player_move");
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void Player::HandleEvent(void)
{
	if(m_pEventListener->EmptyCurrentEvent())
	{
		return;
	}
	else
	{
		const std::deque<std::string>& currentEvents = m_pEventListener->GetEvent();

		std::string eventType;			
		for(auto& gameEvent : currentEvents)
		{
			if(gameEvent == "space_change_return_end")
			{
				// 通常の入れ替え戻しが完了したら、女神の加護の数値を減らし、イベントをとばす
				--m_GoddessPointCount;
				GameEventManager::Instance().ReceiveEvent("goddess_point_minus");

				// 元データから消しておく
				m_pStageDataManager->SetCurrentStageChipData(m_StageIndexData.m_YIndexNum, m_StageIndexData.m_XIndexNum);
			}
			else if(gameEvent == "player_respawn_end")
			{
				// 通常の入れ替え戻しが完了したら、女神の加護の数値を減らし、イベントをとばす
				--m_GoddessPointCount;
				GameEventManager::Instance().ReceiveEvent("goddess_point_minus");

				// 待機状態に戻す
				m_pPlayerMotion->ChangeWaitingMotion();

				// 元データから消しておく
				m_pStageDataManager->SetCurrentStageChipData(m_StageIndexData.m_YIndexNum, m_StageIndexData.m_XIndexNum);
			}
		}

		m_pEventListener->DelEvent();
	}
}

void Player::RegisterEvent(void)
{
	// 死亡動作アニメーション終了イベント
	GameEventManager::Instance().RegisterEventType("player_death_anime_end", m_pEventListener);
	m_pEventListener->RegisterSynEventFunc("player_death_anime_end", std::bind(&ar::Player::RunDeathAnimeEndProcessing, this));

	// 入れ替え処理開始イベント
	GameEventManager::Instance().RegisterEventType("space_change_start", m_pEventListener);
	m_pEventListener->RegisterSynEventFunc("space_change_start", std::bind(&ar::Player::PrepareSpaceChange, this));

	// 入れ替え処理終了イベント
	GameEventManager::Instance().RegisterEventType("space_change_end", m_pEventListener);
	m_pEventListener->RegisterSynEventFunc("space_change_end", std::bind(&ar::Player::RunSpaceChangeEndProcessing, this));

	// 入れ替え戻し終了イベント
	GameEventManager::Instance().RegisterEventType("space_change_return_end", m_pEventListener);

	// プレイヤーリスポーン終了イベント
	GameEventManager::Instance().RegisterEventType("player_respawn_end", m_pEventListener);
}

void Player::PrepareSpaceChange(void)
{
	StageDataChangeManager::Instance().SetPlayerPointer(this);
}

void  Player::RunSpaceChangeEndProcessing(void)
{
	// ストックのラストデータにプレイヤー座標を設定する
	m_pStageDataManager->SetNewStockStageChipData(m_StageIndexData.m_YIndexNum, m_StageIndexData.m_XIndexNum, this);

	// 入れ替え終了したら、モードを通常モードに変更する
	m_pPlayerMode->ChangeNormalMode();
}

void Player::RunDeathAnimeEndProcessing(void)
{
	if(m_GoddessPointCount > 0)
	{	// 加護があるなら復活させる
		GameEventManager::Instance().ReceiveEvent("player_respawn_start");
		SceneSoundManager::Instance().PlayBackSound(static_cast<int>(GAME_SCENE_SOUND_ID::REVIVE), sl::RESET_PLAY);
		// モードをリセットする
		m_pPlayerMode->Reset();
	}
	else
	{	// 加護がないならゲームオーバーイベントをとばす
		GameEventManager::Instance().ReceiveEvent("game_over");
	}
}

void Player::CalculateStageIndexData(void)
{
	if(m_pPlayerMotion->IsFacingRight())
	{ 
		m_StageIndexData.m_XIndexNum = static_cast<short>((m_Pos.x - (m_StageChipSize / 2)) / m_StageChipSize);
 	    m_StageIndexData.m_YIndexNum  = static_cast<short>(m_Pos.y / m_StageChipSize);
	}
	else
	{
		m_StageIndexData.m_XIndexNum = static_cast<short>((m_Pos.x + (m_StageChipSize / 2)) / m_StageChipSize);
 	    m_StageIndexData.m_YIndexNum  = static_cast<short>(m_Pos.y / m_StageChipSize);
	}
}

bool Player::CheckCollisionDeathArea(const sl::fRect& rCollidedObjRect)
{
	sl::fRect deathAreaRect;
	deathAreaRect.m_Left	= m_CurrentRectData.m_Left + DeathAreaCorrectionVal;
	deathAreaRect.m_Bottom	= m_CurrentRectData.m_Bottom;
	deathAreaRect.m_Right	= m_CurrentRectData.m_Right - DeathAreaCorrectionVal;
	deathAreaRect.m_Top		= m_CurrentRectData.m_Top;

	if(deathAreaRect.m_Right > rCollidedObjRect.m_Left
		&& deathAreaRect.m_Top < rCollidedObjRect.m_Bottom
		&& deathAreaRect.m_Left < rCollidedObjRect.m_Right
		&& deathAreaRect.m_Bottom > rCollidedObjRect.m_Top)
	{
		return true;
	}

	return false;
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//

