//==================================================================================================================================//
//!< @file		Entrance.cpp
//!< @brief		ar::Entranceクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "Entrance.h"
#include "../../../../StageDataManager.h"
#include "../../../../../GameEventManager/GameEventManager.h"
#include "../../../../../GameEventManager/EventListener.h"
#include "../../../../../GameSceneSoundID.h"


namespace ar
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const	int		SizeChipCount = 3;		// サイズのチップ数

}

/* Public Functions ------------------------------------------------------------------------------------------- */

Entrance::Entrance(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
		, const Stage::INDEX_DATA& rStageIndexData, int texID)
	: StageObj(pStageDataManager, pCollisionManager, rStageIndexData)
	, m_HasClosed(false)
	, m_HasStartedStage(false)
{
	m_TypeID = ENTRANCE;
	m_DrawingID.m_TexID = texID;
}

Entrance::~Entrance(void)
{
	m_pLibrary->ReleaseVertex2D(m_DrawingID.m_VtxID);
}

void Entrance::Initialize(void)
{
	m_Pos.x = m_StageIndexData.m_XNum * m_StageChipSize + (m_StageChipSize / 2) + m_StageChipSize;
	m_Pos.y = m_StageIndexData.m_YNum * m_StageChipSize - (m_StageChipSize / 2);

	// Vertex作成
	m_RectSize.m_Left = -((m_StageChipSize * SizeChipCount) / 2);
	m_RectSize.m_Top = -((m_StageChipSize * SizeChipCount) / 2);
	m_RectSize.m_Right = ((m_StageChipSize * SizeChipCount) / 2);
	m_RectSize.m_Bottom = ((m_StageChipSize * SizeChipCount) / 2);

	sl::fRect	uv = { 0.0f, 0.088f, 0.15f, 0.444f };			// UV座標

	m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(m_RectSize, uv);

	m_pLibrary->SetVtxColor(m_DrawingID.m_VtxID, 0.5f, 0.5f, 0.5f, 1.0f);

	// アニメーション登録と作成
	m_UVAnimeID = m_pLibrary->RegisterUVAnimeID(m_DrawingID.m_VtxID, 9);
	m_pLibrary->CreateUVAnimeData(m_DrawingID.m_VtxID, m_UVAnimeID, 5, 1, uv, 12);

	// アニメーション番号の順番を逆にする
	std::vector<int> animeOrder;
	for(int i = 8; i >= 0; --i)
	{
		animeOrder.push_back(i);
	}
	m_pLibrary->SeUVtAnimeOrder(m_DrawingID.m_VtxID, m_UVAnimeID, animeOrder);
	m_pLibrary->ReturnUVAnimeInitialState(m_DrawingID.m_VtxID, m_UVAnimeID);

	// イベント登録
	// ステージ開始イベント
	GameEventManager::Instance().RegisterEventType("stage_start", m_pEventListener);

	// 入口の位置を固定する
	m_pStageDataManager->SetCurrentStageChipData(m_StageIndexData.m_YNum, m_StageIndexData.m_XNum);
}

void Entrance::ChangeStagePos(short yIndexNum, short xIndexNum)
{
	// ステージは初期位置から移動しないため処理なし
}

void Entrance::ProcessCollision(const CollisionManager::CollisionData& rData)
{}

/* Private Functions ------------------------------------------------------------------------------------------ */

void Entrance::Run(void)
{
	if(m_HasClosed)
	{	// 閉まっているなら即return
		return;
	}

	if(m_HasStartedStage)
	{
		m_pLibrary->UpdateUVAnime(m_DrawingID.m_VtxID, m_UVAnimeID);
		m_pLibrary->PlayBackSound(static_cast<int>(GAME_SCENE_SOUND_ID::DOOR), sl::PLAY_LOOP);

		if(m_pLibrary->CheckLastNumCurrnttUVAnime(m_DrawingID.m_VtxID, m_UVAnimeID))
		{
			m_pLibrary->PlayBackSound(static_cast<int>(GAME_SCENE_SOUND_ID::DOOR), sl::STOP);
			m_HasClosed = true;
			// 閉じたら少し透明にする
			m_pLibrary->SetVtxColor(m_DrawingID.m_VtxID, 0.5f, 0.5f, 0.5f, 0.3f);
		}
	}
}

void Entrance::Render(void)
{
	m_pLibrary->Draw2D( m_DrawingID, (m_Pos - m_BasePointPos));
}

void Entrance::HandleEvent(void)
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
			if(gameEvent == "stage_start" )
			{
				m_HasStartedStage = true;
			}
		}

		m_pEventListener->DelEvent();
	}
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
