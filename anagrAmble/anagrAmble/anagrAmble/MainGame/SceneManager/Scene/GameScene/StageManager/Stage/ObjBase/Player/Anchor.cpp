//==================================================================================================================================//
//!< @file		Anchor.cpp
//!< @brief		ar::Anchorクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include <cmath> 
#include "Anchor.h"
#include "Player.h"
#include "../../../StageDataManager.h"
#include "../../../../GameEventManager/GameEventManager.h"
#include "../../../../GameEventManager/EventListener.h"

namespace ar
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const short  PairAreaIntervalChipCount = 6;			//!< ペアAnchorとのエリア間隔チップ数

}

/* Public Functions ------------------------------------------------------------------------------------------- */

Anchor::Anchor(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
			, const Stage::INDEX_DATA& rStageIndexData, Player* pPlayer, int texID)
	: ObjBase(pStageDataManager, pCollisionManager, rStageIndexData)
	, m_pPlayer(pPlayer)
	, m_HasPlacePosStage(false)
	, m_HasCollidedWithPlayer(false)

{
	m_TypeID = ANCHOR;
	m_DrawingID.m_TexID = texID;
}

Anchor::~Anchor(void)
{
	m_pLibrary->ReleaseVertex2D(m_DrawingID.m_VtxID);
}

void Anchor::Control(void)
{
	HandleEvent();

	m_HasCollidedWithPlayer = false;	// 毎フレームfalseへ trueの処理はHandleEvent内に処理

	if(m_HasPlacePosStage)
	{
		if(m_Pos.x < m_BasePointPos.x
			|| m_Pos.x >(m_BasePointPos.x + m_DisplayArea.m_Right))
		{
			return;
		}
		
		// フィールドに置かれており、かつ画面内にあるなら衝突判定に登録する
		m_pCollisionManager->SetObjBasePointer(this);
	}
	else
	{
		// プレイヤーの前に常に座標を置く
		PlacePosPlayerFront();
	}
}

void Anchor::Draw(void)
{
	if(m_Pos.x < m_BasePointPos.x
		|| m_Pos.x >(m_BasePointPos.x + m_DisplayArea.m_Right))
	{
		return;
	}
	// 画面内にあるなら描画する
	m_pLibrary->Draw2D(m_DrawingID, (m_Pos - m_BasePointPos));
}

bool Anchor::CanPlaceStage(void)
{
	if(m_HasPlacePosStage)
	{	// すでにステージにおかれていたらfalse
		return false;
	}

	if(std::abs(m_pPlayer->GetStageIndex().m_XNum - m_pPairAnchor->GetStageIndex().m_XNum) > PairAreaIntervalChipCount)
	{	// アンカーの間がペアとのエリア間隔チップ数よりはなれていたらfalse
		return false;
	}

	return true;
}

void Anchor::PlacePosStage(void)
{
	// ステージインデックスを更新
	Stage::INDEX_DATA playerIndex = m_pPlayer->GetStageIndex();
	m_StageIndexData.m_XNum = playerIndex.m_XNum;
	m_StageIndexData.m_YNum = playerIndex.m_YNum;

	if(playerIndex.m_XNum <= 1 
		|| playerIndex.m_XNum >= (m_pStageDataManager->GetStageWidthChipNum() - 1))
	{	// 端にはアンカーがおけないので即return
		return;
	}

	// ブロックとブロックの隙間に位置するように座標を調整
	if(std::abs(m_pPlayer->GetPos().x - playerIndex.m_XNum * m_StageChipSize) > ((m_StageChipSize / 2) + (m_StageChipSize / 4)))
	{
		// プレイヤーの位置座標からインデックスをずらして位置調整をする
		short xNumCorrectionVal =  m_pPlayer->IsFacingRight() ?  2 : -2 ;

		if(std::abs((playerIndex.m_XNum + xNumCorrectionVal) - m_pPairAnchor->GetStageIndex().m_XNum) > PairAreaIntervalChipCount)
		{	// アンカーの間がペアとのエリア間隔チップ数よりはなれていたら即return
			return;
		}

		m_Pos.x = ((playerIndex.m_XNum + xNumCorrectionVal) * m_StageChipSize);
		m_StageIndexData.m_XNum += xNumCorrectionVal;
	}
	else 
	{
		short xNumCorrectionVal =  m_pPlayer->IsFacingRight() ?  1 : -1 ;

		if(std::abs((playerIndex.m_XNum + xNumCorrectionVal) - m_pPairAnchor->GetStageIndex().m_XNum) > PairAreaIntervalChipCount)
		{	// アンカーの間がペアとのエリア間隔チップ数よりはなれていたら即return
			return;
		}

		m_Pos.x = ((playerIndex.m_XNum + xNumCorrectionVal) * m_StageChipSize);
		m_StageIndexData.m_XNum += xNumCorrectionVal;
	}
	
	m_HasPlacePosStage = true;
	m_Pos.y = m_pPlayer->GetPos().y + m_StageChipSize / 2;

	// 設置されるので半透明を解除する
	m_pLibrary->SetVtxColor(m_DrawingID.m_VtxID, 1.0f, 1.0f, 1.0f, 1.0f);
}

void Anchor::PlacePosPlayerFront(void)
{
	m_HasPlacePosStage = false;
	m_HasCollidedWithPlayer = false;

	// ステージインデックスをプレイヤーにあわせる
	Stage::INDEX_DATA playerIndex = m_pPlayer->GetStageIndex();
	m_StageIndexData.m_XNum = playerIndex.m_XNum;
	m_StageIndexData.m_YNum = playerIndex.m_YNum;

	// プレイヤーの前に位置するよう座標を調整
	// 向きのによって位置調整
	float posXCorrectionVal =  m_pPlayer->IsFacingRight() ?  m_StageChipSize / 2 : -(m_StageChipSize / 2) ;
	m_Pos.x = m_pPlayer->GetPos().x + posXCorrectionVal;
	m_Pos.y = m_pPlayer->GetPos().y + m_StageChipSize / 2;

	m_StageIndexData.m_XNum = 0;
	m_StageIndexData.m_YNum = 0;

	// ステージに設置されていないので少し半透明にしておく
	m_pLibrary->SetVtxColor(m_DrawingID.m_VtxID, 1.0f, 1.0f, 1.0f, 0.5f);
	m_HasCollidedWithPlayer = false;
}

void Anchor::Initialize(void)
{
	m_RectSize.m_Left	=  -(m_StageChipSize / 2);
	m_RectSize.m_Top	=  -(m_StageChipSize / 2);
	m_RectSize.m_Right	= (m_StageChipSize / 2);
	m_RectSize.m_Bottom = (m_StageChipSize / 2);
	
	const sl::fRect		uv = {0.891f, 0.955f, 0.916f, 1.0f};

	m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, uv);

	/** プレイヤーの前に座標をおく */
	PlacePosPlayerFront();

	// イベント登録
	//  アンカー回収イベント
	GameEventManager::Instance().RegisterEventType("anchor_retrieve", m_pEventListener);	
	
	// プレイヤーが動いたときのイベント
	GameEventManager::Instance().RegisterEventType("player_move", m_pEventListener);
	m_pEventListener->RegisterSynEventFunc("player_move", std::bind(&ar::Anchor::AdjustPos, this));

	// ステージ変更終了イベント
	GameEventManager::Instance().RegisterEventType("space_change_end", m_pEventListener);
	m_pEventListener->RegisterSynEventFunc("space_change_end", std::bind(&ar::Anchor::PlacePosPlayerFront, this));
}

void Anchor::ChangeStagePos(short yIndexNum, short xIndexNum)
{
	// 空処理.よばれることはない
}

void Anchor::ProcessCollision(const CollisionManager::CollisionData& rData)
{
	switch(rData.m_ObjType)
	{
	case PLAYER:
		m_HasCollidedWithPlayer = true;
		break;

	default:
		// do nothing
		break;
	}
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void Anchor::HandleEvent(void)
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
			if(gameEvent == "anchor_retrieve")
			{
				if(m_HasCollidedWithPlayer )
				{
					PlacePosPlayerFront();
				}

				if(m_pPairAnchor->GetHasPlacePosStage())
				{	// もう片方が置かれている状況なら挟んでいる空間を開放するイベントをとばす
					GameEventManager::Instance().ReceiveEvent("sandwiched_space_release");
				}
			}
		}

		m_pEventListener->DelEvent();
	}
}

void Anchor::AdjustPos(void)
{
	if(m_HasPlacePosStage)
	{	// ステージにおかれていたら即return
		return;
	}

	// ステージインデックスをプレイヤーにあわせる
	Stage::INDEX_DATA playerIndex = m_pPlayer->GetStageIndex();
	m_StageIndexData.m_XNum = playerIndex.m_XNum;
	m_StageIndexData.m_YNum = playerIndex.m_YNum;

	// プレイヤーの前に位置するよう座標を調整
	// 向きのによって位置調整
	float posXCorrectionVal =  m_pPlayer->IsFacingRight() ?  m_StageChipSize / 2 : -(m_StageChipSize / 2) ;
	m_Pos.x = m_pPlayer->GetPos().x + posXCorrectionVal;
	m_Pos.y = m_pPlayer->GetPos().y + m_StageChipSize / 2;
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
