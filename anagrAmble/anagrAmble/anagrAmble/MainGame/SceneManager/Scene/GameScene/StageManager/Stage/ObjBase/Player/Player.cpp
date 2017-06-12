//==================================================================================================================================//
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
#include "../../../../GameEventManager/EventLisner.h"

namespace ar
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const		int			WidthChipCount	= 1;				// プレイヤーの矩形の横のチップ数
const		int			HeightChipCount = 2;				// プレイヤーの矩形の縦のチップ数
const		float		CollisionCorrectionVal = 12.f;		// 衝突における判定の補正値
const		float		UpCollisionCorrectionVal = 1.0f;	// 下の衝突判定補正値
const		float		FallLimitVal = 1368.f;				// 落下限界値. 
	
}

/* Public Functions ------------------------------------------------------------------------------------------- */

Player::Player(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
				, const Stage::INDEX_DATA& rStageIndexData, int playerTexID)
	: ObjBase(pStageDataManager, pCollisionManager, rStageIndexData)
	, m_pEventLisner(new EventLisner())
	, m_pPlayerMotion(nullptr)
	, m_pPlayerMode(nullptr)
{
	RegisterEvent();
	m_TypeID = PLAYER;
	CalculatePos();
	m_DrawingID.m_TexID = playerTexID;	// テクスチャーIDを格納

	// 矩形サイズを生成
	m_RectSize.m_Left	= -(m_StageChipSize / 2) * WidthChipCount;
	m_RectSize.m_Top	= -(m_StageChipSize / 2) * HeightChipCount;
	m_RectSize.m_Right	=  (m_StageChipSize / 2) * WidthChipCount;
	m_RectSize.m_Bottom =  (m_StageChipSize / 2) * HeightChipCount;

	m_pPlayerMotion = new PlayerMotion(m_RectSize);
	m_pPlayerMode = new PlayerMode(m_pStageDataManager, m_pCollisionManager, this, playerTexID);
	m_MovableDirection.m_Up = false;
	m_MovableDirection.m_Down = false;
	m_MovableDirection.m_Right = false;
	m_MovableDirection.m_Left = false;
}

Player::~Player(void)
{
	sl::DeleteSafely(m_pPlayerMode);
	sl::DeleteSafely(m_pPlayerMotion);
	sl::DeleteSafely(m_pEventLisner);

	for(auto& vtxID : m_VtxID)
	{
		m_pLibrary->ReleaseVertex2D(vtxID);
	}
}

void Player::StartStage(void)
{
	// ステージ開始時の処理を書く
}

void Player::CompleteStage(void)
{
	// ステージクリア時の処理を書く
	GameEventManager::Instance().ReceiveEvent("game_clear");
}

void Player::Control(void)
{
	// イベント処理
	HandleEvent();

	if(m_Pos.y > FallLimitVal)
	{	// 落下限界値以上落ちていたら死亡状態にする
		m_pPlayerMotion->ChangeDeathMotion();
	}

	// 状態による処理をおこなう
	sl::SLVECTOR2 currentMoveVector = m_pPlayerMotion->Control(m_MovableDirection);
	m_Pos +=  currentMoveVector;

	if(m_Pos.y > FallLimitVal)
	{	// 落下限界値以上落ちていたら死亡状態にする
		m_pPlayerMotion->ChangeDeathMotion();
	}

	if(m_pPlayerMotion->IsCurrrentMotionDeath())
	{	// 死亡動作ならここから下の処理はいらないので、
		// 衝突チェックにnullptrを渡して即return;
		m_pCollisionManager->SetPlayerPointa(nullptr);
		return;
	}

	if(currentMoveVector.x != 0.0f || currentMoveVector.y != 0.0f)
	{	// 動いていたらイベントをとばす
		GameEventManager::Instance().TriggerSynEvent("player_move");
	}

	// 移動方向を初期化する
	m_MovableDirection.m_Up = true;
	m_MovableDirection.m_Down = true;
	m_MovableDirection.m_Right = true;
	m_MovableDirection.m_Left = true;
	
	// 向きによってステージインデックスの計算方法をかえる
	if(m_pPlayerMotion->IsFacingRight())
	{ 
		m_StageIndexData.m_XNum = static_cast<short>((m_Pos.x - (m_StageChipSize / 2)) / m_StageChipSize);
 	    m_StageIndexData.m_YNum  = static_cast<short>(m_Pos.y / m_StageChipSize);
	}
	else
	{
		m_StageIndexData.m_XNum = static_cast<short>((m_Pos.x + (m_StageChipSize / 2)) / m_StageChipSize);
 	    m_StageIndexData.m_YNum  = static_cast<short>(m_Pos.y / m_StageChipSize);
	}

	// モードによる処理
	m_pPlayerMode->Control();

	if(m_pLibrary->CheckCustomizeState(SPECIAL_ACTION, sl::ON))
	{	// 特殊アクションボタンが押されたら、イベントを通知する
		GameEventManager::Instance().ReceiveEvent("special_action");
	}

	m_pCollisionManager->SetPlayerPointa(this);
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

void Player::ProcessCollision(const CollisionManager::CollisionData& rData)
{
	switch(rData.m_ObjType)
	{
	case GROUND_B:
		break;

	case GOAL:
		return;
		break;

	case ANCHOR:
		return;
		break;

	default:
		// do nothing
		break;
	}

	// 移動可能な方向の確認と補正値を足す

	// 上方向
	if(m_Pos.y > rData.m_ObjPos.y
		&& m_CurrentRectData.m_Top < rData.m_ObjRect.m_Bottom
		&& std::abs(m_Pos.x - rData.m_ObjPos.x) < m_StageChipSize - CollisionCorrectionVal)
	{
		m_MovableDirection.m_Up = false;
		m_Pos.y += rData.m_ObjRect.m_Bottom - m_CurrentRectData.m_Top;
	}

	// 下方向
	if(m_Pos.y < rData.m_ObjPos.y
		&& m_CurrentRectData.m_Bottom < rData.m_ObjPos.y
		&& std::abs(m_Pos.x - rData.m_ObjPos.x) < m_StageChipSize - CollisionCorrectionVal)
	{
		m_MovableDirection.m_Down = false;

		// はみだした部分が下の衝突補正値より大きかったら、調整する
		if( m_CurrentRectData.m_Bottom - rData.m_ObjRect.m_Top > UpCollisionCorrectionVal)
		{
			m_Pos.y -= m_CurrentRectData.m_Bottom - rData.m_ObjRect.m_Top;
		}
	}
	
	// 左方向
	if(m_Pos.x > rData.m_ObjPos.x
		&& m_CurrentRectData.m_Left > rData.m_ObjPos.x
		&& std::abs(m_Pos.y - rData.m_ObjPos.y) < m_StageChipSize + m_StageChipSize / 2  - CollisionCorrectionVal)
	{
		m_MovableDirection.m_Left = false;
		m_Pos.x += rData.m_ObjRect.m_Right - m_CurrentRectData.m_Left;
	}

	// 右方向
	if(m_Pos.x < rData.m_ObjPos.x
			&& m_CurrentRectData.m_Right < rData.m_ObjPos.x
		&&  std::abs(m_Pos.y - rData.m_ObjPos.y) < m_StageChipSize + m_StageChipSize / 2 - CollisionCorrectionVal)
	{
		m_MovableDirection.m_Right = false;
		m_Pos.x -= m_CurrentRectData.m_Right - rData.m_ObjRect.m_Left;
	}
	

	// 座標が動いたのでステージインデックスを計算しなおす
	if(m_pPlayerMotion->IsFacingRight())
	{ 
		m_StageIndexData.m_XNum = static_cast<short>((m_Pos.x - (m_StageChipSize / 2)) / m_StageChipSize);
 	    m_StageIndexData.m_YNum  = static_cast<short>(m_Pos.y / m_StageChipSize);
	}
	else
	{
		m_StageIndexData.m_XNum = static_cast<short>((m_Pos.x + (m_StageChipSize / 2)) / m_StageChipSize);
 	    m_StageIndexData.m_YNum  = static_cast<short>(m_Pos.y / m_StageChipSize);
	}

	GameEventManager::Instance().TriggerSynEvent("player_move");
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void Player::HandleEvent(void)
{
	if(m_pEventLisner->EmptyCurrentEvent())
	{
		return;
	}
	else
	{
		const std::deque<std::string>& currentEvents = m_pEventLisner->GetEvent();

		std::string eventType;			
		for(auto& gameEvent : currentEvents)
		{
			if(gameEvent == "player_death_anime_end")
			{	// 死亡アニメーションが終了したらゲームオーバーイベントをとばして,return
				GameEventManager::Instance().ReceiveEvent("game_over");
				return;								
			}
		}

		m_pEventLisner->DelEvent();
	}
}

void Player::CalculatePos(void)
{
	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2);
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize;
}

void Player::RegisterEvent(void)
{
	// 死亡動作アニメーション終了イベント
	GameEventManager::Instance().RegisterEventType("player_death_anime_end", m_pEventLisner);
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//

