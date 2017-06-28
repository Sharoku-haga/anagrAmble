//==================================================================================================================================//
//!< @file		Anchor.cpp
//!< @brief		ar::Anchorクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include <cmath> 
#include "Anchor.h"
#include "Player.h"
#include "../../StageEffect/AnchorLightEffect.h"
#include "../../../StageDataManager.h"
#include "../../../../GameEventManager/GameEventManager.h"
#include "../../../../GameEventManager/EventListener.h"
#include "../../../../GameSceneSoundID.h"

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
	, m_pLightEffect(nullptr)
	, m_HasPlacePosStage(false)
	, m_HasCollidedWithPlayer(false)

{
	m_TypeID = ANCHOR;
	m_DrawingID.m_TexID = texID;
	m_pPairAnchor;
}

Anchor::~Anchor(void)
{
	sl::DeleteSafely(&m_pLightEffect);
	m_pLibrary->ReleaseVertex2D(m_DrawingID.m_VtxID);
}

void Anchor::Control(void)
{
	HandleEvent();

	m_HasCollidedWithPlayer = false;	// 毎フレームfalseへ trueの処理はHandleEvent内に処理

	if(m_HasPlacePosStage)
	{
		if(m_Pos.x >= m_BasePointPos.x
			|| m_Pos.x  <= (m_BasePointPos.x + m_DisplayArea.m_Right))
		{
			// フィールドに置かれており、かつ画面内にあるなら衝突判定に登録する
			m_pCollisionManager->SetObjBasePointer(this);
		}
	}
	else
	{
		// プレイヤーの前を常に動く
		MovePlayerFront();
	}

	m_pLightEffect->Control();
}

void Anchor::Draw(void)
{
	m_pLightEffect->Draw();

	// 画面内にあるなら描画する
	m_pLibrary->Draw2D(m_DrawingID, (m_Pos - m_BasePointPos));
}

bool Anchor::CanPlaceStage(void)
{
	if(m_HasPlacePosStage)
	{	// すでにステージにおかれていたらfalse
		return false;
	}

	// ステージインデックスにプレイヤーのインデックスを入れる
	Stage::INDEX_DATA playerIndex = m_pPlayer->GetStageIndex();
	m_StageIndexData.m_XNum = playerIndex.m_XNum;
	m_StageIndexData.m_YNum = playerIndex.m_YNum;

	// ブロックとブロックの隙間に位置するように座標を調整
	if(std::abs(m_pPlayer->GetPos().x - playerIndex.m_XNum * m_StageChipSize) > ((m_StageChipSize / 2) + (m_StageChipSize / 4)))
	{
		// プレイヤーの位置座標からインデックスをずらして位置調整をする
		short xNumCorrectionVal =  m_pPlayer->IsFacingRight() ?  2 : -2 ;

		m_StageIndexData.m_XNum += xNumCorrectionVal;
	}
	else
	{
		short xNumCorrectionVal = m_pPlayer->IsFacingRight() ? 1 : -1;
		m_StageIndexData.m_XNum += xNumCorrectionVal;
	}

	if(std::abs(m_StageIndexData.m_XNum - m_pPairAnchor->GetStageIndex().m_XNum) > PairAreaIntervalChipCount)
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

		if( m_pPairAnchor->GetHasPlacePosStage()
			&& (playerIndex.m_XNum + xNumCorrectionVal) == m_pPairAnchor->GetStageIndex().m_XNum)
		{	// ぺアとなるアンカーがすでにおかれているなら即return
			return;
		}

		if(std::abs((playerIndex.m_XNum + xNumCorrectionVal) - m_pPairAnchor->GetStageIndex().m_XNum) > PairAreaIntervalChipCount)
		{	// アンカーの間がペアとのエリア間隔チップ数よりはなれていたら即return
			return;
		}

		m_Pos.x = ((playerIndex.m_XNum + xNumCorrectionVal) * m_StageChipSize);
		m_StageIndexData.m_XNum += xNumCorrectionVal;
	}
	else
	{
		short xNumCorrectionVal = m_pPlayer->IsFacingRight() ? 1 : -1;

		if(m_pPairAnchor->GetHasPlacePosStage()
			&& (playerIndex.m_XNum + xNumCorrectionVal) == m_pPairAnchor->GetStageIndex().m_XNum)
		{	// ぺアとなるアンカーがすでにおかれているなら即return
			return;
		}

		if(std::abs((playerIndex.m_XNum + xNumCorrectionVal) - m_pPairAnchor->GetStageIndex().m_XNum) > PairAreaIntervalChipCount)
		{	// アンカーの間がペアとのエリア間隔チップ数よりはなれていたら即return
			return;
		}

		m_Pos.x = ((playerIndex.m_XNum + xNumCorrectionVal) * m_StageChipSize);
		m_StageIndexData.m_XNum += xNumCorrectionVal;
	}
	
	m_HasPlacePosStage = true;
	m_Pos.y = m_pPlayer->GetPos().y + m_StageChipSize / 2;

	m_pLightEffect->ChangeStagePos(m_Pos);

	// 設置されるのでサイズ(見えている光エフェクトの範囲)を大きくし、透明にする
	m_RectSize.m_Top	=  -((m_pStageDataManager->GetStageHeight()) / 2);
	m_RectSize.m_Bottom = ((m_pStageDataManager->GetStageHeight()) / 2);
	m_pLibrary->SetVtxColor(m_DrawingID.m_VtxID, 1.0f, 1.0f, 1.0f, 0.0f);

	// 音を鳴らす
	m_pLibrary->PlayBackSound(static_cast<int>(GAME_SCENE_SOUND_ID::ANCHOR), sl::RESET_PLAY);
}

void Anchor::PlacePosPlayerFront(void)
{
	m_HasPlacePosStage = false;
	m_HasCollidedWithPlayer = false;

	// プレイヤー前に移動
	MovePlayerFront();

	m_pLightEffect->ChangeStagePos(m_Pos);

	// ステージに設置されていないのでサイズを元に戻し、透明を解除する
	m_RectSize.m_Top	=  -(m_StageChipSize / 2);
	m_RectSize.m_Bottom = (m_StageChipSize / 2);
	m_pLibrary->SetVtxColor(m_DrawingID.m_VtxID, 1.0f, 1.0f, 1.0f, 1.0f);
	m_HasCollidedWithPlayer = false;
}

void Anchor::InitializeData(Anchor* pPairAnchor)
{
	m_pPairAnchor = pPairAnchor;
	Initialize();
}

void Anchor::Initialize(void)
{
	m_RectSize.m_Left	=  -(m_StageChipSize / 2);
	m_RectSize.m_Top	=  -(m_StageChipSize / 2);
	m_RectSize.m_Right	= (m_StageChipSize / 2);
	m_RectSize.m_Bottom = (m_StageChipSize / 2);
	
	const sl::fRect		uv = {0.891f, 0.91f, 0.916f, 0.955f};

	m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, uv);

	/** エフェクトの作成 */
	m_pLightEffect = new AnchorLightEffect(this, m_pPairAnchor, m_pStageDataManager->GetStageHeight(), m_DrawingID.m_TexID);
	m_pLightEffect->Initialize();

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
{}

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

void Anchor::AdjustPos(void)
{
	if(m_HasPlacePosStage)
	{	// ステージにおかれていたら即return
		return;
	}

	MovePlayerFront();
}

void Anchor::MovePlayerFront(void)
{
	// ステージインデックスにプレイヤーのインデックスを入れる
	Stage::INDEX_DATA playerIndex = m_pPlayer->GetStageIndex();
	m_StageIndexData.m_XNum = playerIndex.m_XNum;
	m_StageIndexData.m_YNum = playerIndex.m_YNum;

	// ブロックとブロックの隙間に位置するように座標を調整
	if(std::abs(m_pPlayer->GetPos().x - playerIndex.m_XNum * m_StageChipSize) > ((m_StageChipSize / 2) + (m_StageChipSize / 4)))
	{
		// プレイヤーの位置座標からインデックスをずらして位置調整をする
		short xNumCorrectionVal =  m_pPlayer->IsFacingRight() ?  2 : -2 ;

		m_StageIndexData.m_XNum += xNumCorrectionVal;
	}
	else
	{
		short xNumCorrectionVal = m_pPlayer->IsFacingRight() ? 1 : -1;
		m_StageIndexData.m_XNum += xNumCorrectionVal;
	}

	// 座標計算
	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize;
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize;
}

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
				if(m_HasCollidedWithPlayer)
				{
					PlacePosPlayerFront();
					if(m_pPairAnchor->GetHasPlacePosStage())
					{	// もう片方が置かれている状況なら挟んでいる空間を開放するイベントをとばす
						GameEventManager::Instance().ReceiveEvent("sandwiched_space_release");
					}
				}
			}
		}

		m_pEventListener->DelEvent();
	}
}


}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
