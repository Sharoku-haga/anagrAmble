//==================================================================================================================================//
//!< @file		Goal.cpp
//!< @brief		ar::Goalクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "Goal.h"
#include "../../../../StageDataManager.h"
#include "../../../../../GameEventManager/GameEventManager.h"
#include "../../../../../GameEventManager/EventListener.h"
#include "../../../../../GameSceneSoundID.h"
#include "../../../../../../../SoundManager/SceneSoundManager.h"

namespace ar
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const sl::fRect		GoalUV			= { 0.0f, 0.088f, 0.15f, 0.444f	};		// Goalの画像のUV値
const int			SizeChipCount	= 3;									// サイズのチップ数

}

/* Public Functions ------------------------------------------------------------------------------------------- */

Goal::Goal(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
			, const Stage::INDEX_DATA& rStageIndexData,  int texID,  ObjBase::TYPE_ID typeID)
	: StageObj(pStageDataManager, pCollisionManager, rStageIndexData)
	, m_HasCollidedWithPlayer(false)
	, m_CurrentState(HAS_OPENED_DOOR)
{
	m_TypeID = typeID;
	m_DrawingID.m_TexID = texID;
}

Goal::~Goal(void)
{
	m_pLibrary->ReleaseVertex2D(m_DrawingID.m_VtxID);
}

void  Goal::Initialize(void)
{
	m_Pos.x = m_StageIndexData.m_XIndexNum * m_StageChipSize + (m_StageChipSize / 2) + m_StageChipSize;
	m_Pos.y = m_StageIndexData.m_YIndexNum * m_StageChipSize - (m_StageChipSize / 2);

	// 矩形サイズを設定
	m_RectSize.m_Left	=  -((m_StageChipSize * SizeChipCount) / 2);
	m_RectSize.m_Top	=  -((m_StageChipSize * SizeChipCount) / 2);
	m_RectSize.m_Right	= ((m_StageChipSize * SizeChipCount) / 2);
	m_RectSize.m_Bottom = ((m_StageChipSize * SizeChipCount) / 2);

	// Vertexの生成
	m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, GoalUV);
	
	// アニメーション登録と作成
	m_UVAnimeID = m_pLibrary->RegisterUVAnimeID(m_DrawingID.m_VtxID, 9);
	m_pLibrary->CreateUVAnimeData(m_DrawingID.m_VtxID, m_UVAnimeID, 5, 1, GoalUV, 12);
	
	// IDごとの処理
	if(m_TypeID == GOAL)
	{	
		// GOALの場合は番号の順番を逆にアニメーションを設定する
		std::vector<int> animeOrder;
	
		for(int i = 8; i >= 0; --i)
		{
			animeOrder.push_back(i);
		}

		m_pLibrary->SeUVtAnimeOrder(m_DrawingID.m_VtxID, m_UVAnimeID, animeOrder);
		m_pLibrary->ReturnUVAnimeInitialState(m_DrawingID.m_VtxID, m_UVAnimeID);
	}
	else
	{	// こちらはLOCKED_GOALの処理
		m_CurrentState = HAS_CLOSED_DOOR;
	}

	// イベント登録
	// 特殊アクションボタンが押されるイベント
	GameEventManager::Instance().RegisterEventType("special_action", m_pEventListener);

	// ゴールキーを取得するイベント
	GameEventManager::Instance().RegisterEventType("goal_key_get", m_pEventListener);

	// ステージ終了イベント
	GameEventManager::Instance().RegisterEventType("stage_end", m_pEventListener);

	// ゴールの位置を固定する
	m_pStageDataManager->SetCurrentStageChipData(m_StageIndexData.m_YIndexNum, m_StageIndexData.m_XIndexNum);
}

void Goal::ChangeStagePos(short yIndexNum, short xIndexNum)
{
	m_StageIndexData.m_YIndexNum = yIndexNum;
	m_StageIndexData.m_XIndexNum = xIndexNum;

	m_Pos.x = m_StageIndexData.m_XIndexNum * m_StageChipSize + (m_StageChipSize / 2) + m_StageChipSize;
	m_Pos.y = m_StageIndexData.m_YIndexNum * m_StageChipSize - (m_StageChipSize / 2);

}

void Goal::ProcessCollision(const CollisionManager::CollisionData& rData)
{
	switch(rData.m_ObjType)
	{

	case ObjBase::PLAYER:
		if(m_CurrentRectData.m_Left < rData.m_ObjRect.m_Left
			&& m_CurrentRectData.m_Top < rData.m_ObjRect.m_Top
			&& m_CurrentRectData.m_Right > rData.m_ObjRect.m_Right)
		{
			m_HasCollidedWithPlayer = true;
		}
		
		break;

	default:
		// do nothing
		break;

	}
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void Goal::Run(void)
{
	m_HasCollidedWithPlayer = false;

	switch(m_CurrentState)
	{

	case IS_OPENING_DOOR:
		m_pLibrary->UpdateUVAnime(m_DrawingID.m_VtxID, m_UVAnimeID);
		if(m_pLibrary->CheckLastNumCurrnttUVAnime(m_DrawingID.m_VtxID, m_UVAnimeID))
		{
			SceneSoundManager::Instance().PlayBackSound(static_cast<int>(GAME_SCENE_SOUND_ID::DOOR), sl::STOP);
			m_CurrentState = HAS_OPENED_DOOR;

			if(m_TypeID == LOCKED_GOAL)
			{
				std::vector<int> animeOrder;

				for(int i = 8; i >= 0; --i)
				{
					animeOrder.push_back(i);
				}
				m_pLibrary->SeUVtAnimeOrder(m_DrawingID.m_VtxID, m_UVAnimeID, animeOrder);
				m_pLibrary->ReturnUVAnimeInitialState(m_DrawingID.m_VtxID, m_UVAnimeID);
			}
		}
			break;

	case HAS_OPENED_DOOR:
		// do nothing
		break;

	case IS_CLOSEING_DOOR:
		m_pLibrary->UpdateUVAnime(m_DrawingID.m_VtxID, m_UVAnimeID);
		if(m_pLibrary->CheckLastNumCurrnttUVAnime(m_DrawingID.m_VtxID, m_UVAnimeID))
		{
			SceneSoundManager::Instance().PlayBackSound(static_cast<int>(GAME_SCENE_SOUND_ID::DOOR), sl::STOP);
			GameEventManager::Instance().ReceiveEvent("game_clear");
		}
		break;

	case HAS_CLOSED_DOOR:
		// do nothing
		break;

	default:
		// do nothing
		break;
	}
}

void Goal::Render(void)
{
	m_pLibrary->Draw2D( m_DrawingID, (m_Pos - m_BasePointPos));
}

void Goal::HandleEvent(void)
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
			if(gameEvent == "special_action" && m_HasCollidedWithPlayer && m_CurrentState == HAS_OPENED_DOOR)
			{
				// ゴールに到達したイベントを通知する
				GameEventManager::Instance().ReceiveEvent("goal_touch");
				break;
			}
			else if(gameEvent == "goal_key_get"  && m_TypeID == LOCKED_GOAL)
			{
				SceneSoundManager::Instance().PlayBackSound(static_cast<int>(GAME_SCENE_SOUND_ID::DOOR), sl::PLAY_LOOP);
				m_CurrentState = IS_OPENING_DOOR;
				break;
			}
			else if(gameEvent == "stage_end"  && m_CurrentState == HAS_OPENED_DOOR)
			{
				SceneSoundManager::Instance().PlayBackSound(static_cast<int>(GAME_SCENE_SOUND_ID::DOOR), sl::PLAY_LOOP);
				m_CurrentState = IS_CLOSEING_DOOR;
				break;
			}
		}

		m_pEventListener->DelEvent();
	}
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
