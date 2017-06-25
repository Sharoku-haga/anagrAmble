﻿//==================================================================================================================================//
//!< @file		Stage.cpp
//!< @brief		ar::Stageクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "Stage.h"
#include "../../GameEventManager/EventListener.h"
#include "../../GameEventManager/GameEventManager.h"
#include "../StageDataManager.h"
#include "../StageDataChangeManager.h"
#include "CollisionManager.h"
#include "BasePoint.h"
#include "StageEffect/StageEffect.h"
#include "ObjBase/Player/Player.h"
#include "StageObjManager/StageObjManager.h"
#include "StageBackground.h"
#include "GoddessPointUI/GoddessPointUI.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

Stage::Stage(StageDataManager*	pStageDataManager)
	: m_pLibrary(sl::ISharokuLibrary::Instance())
	, m_pEventListener(new EventListener())
	, m_pStageDataManager(pStageDataManager)
	, m_pCollisionManager(new CollisionManager(pStageDataManager))
	, m_pBasePoint(new BasePoint())
	, m_pPlayer(nullptr)
	, m_pStageObjManager(nullptr)
	, m_pBackground(nullptr)
	, m_pGoddessPointUI(nullptr)
	, m_CurrentState(ENTER)
{
	// デバック用
	m_CurrentState = EXECUTE;
}

Stage::~Stage(void)
{
	sl::DeleteSafely(&m_pGoddessPointUI);
	sl::DeleteSafely(&m_pBackground);
	sl::DeleteSafely(&m_pStageObjManager);
	sl::DeleteSafely(&m_pPlayer);
	sl::DeleteSafely(&m_pBasePoint);
	sl::DeleteSafely(&m_pCollisionManager);
	sl::DeleteSafely(&m_pEventListener);
}

void Stage::Initialize(void)
{
	m_PlayerTexID = m_pLibrary->LoadTexture("../Resource/GameScene/PlayerFile.png");
	m_StageObjTexID = m_pLibrary->LoadTexture("../Resource/GameScene/ObjectFile.png");
	int	goddessPointUI = m_pLibrary->LoadTexture("../Resource/GameScene/GoddessPoint.png");

	ObjBase::SetDisplayArea(m_pLibrary->GetClientSize().m_Right, m_pLibrary->GetClientSize().m_Bottom);
	StageEffect::SetDisplayArea(m_pLibrary->GetClientSize().m_Right, m_pLibrary->GetClientSize().m_Bottom);
	ObjBase::SetStageChipSize(m_pStageDataManager->GetStageChipSize());
	

	m_pStageObjManager = new StageObjManager(m_pStageDataManager, m_pCollisionManager, m_StageObjTexID);

	// オブジェクトを生成し、初期位置へ
	m_CurrentStageData = m_pStageDataManager->GetLoadStageData();
	for(unsigned int yNum = 0; yNum < m_CurrentStageData.size(); ++yNum)
	{
		for(unsigned int xNum = 0; xNum < m_CurrentStageData[yNum].size(); ++xNum)
		{
			CreateObj(m_CurrentStageData[yNum][xNum], yNum, xNum);
		}
	}

	m_pPlayer->Initialize();
	m_pStageObjManager->InitializeStageObj();

	// ステージの元データをセーブする
	m_pStageDataManager->SaveStageOriginalData();
	// プレイヤーが入れ替えできないようにする為ステージデータから消す
	m_pStageDataManager->SetCurrentStageChipData(m_pPlayer->GetStageIndex().m_YNum, m_pPlayer->GetStageIndex().m_XNum);

	// ベースポイントの設定を行う 
	m_pBasePoint->Initialize(m_pStageDataManager->GetStageWidth(), m_pPlayer);

	// 背景の設定を行う
	int stageBGTexID = m_pLibrary->LoadTexture(m_pStageDataManager->GetBackGoundTexFileName().c_str());
	m_pBackground = new StageBackground(m_pBasePoint, stageBGTexID);

	// UIの設定を行う
	m_pGoddessPointUI = new GoddessPointUI(goddessPointUI, m_pPlayer->GetGoddessPointCount());
	m_pGoddessPointUI->Initialize();

	// イベント登録
	// ゴール到達イベント
	GameEventManager::Instance().RegisterEventType("goal_touch", m_pEventListener);

	// ステージ入れ替え開始イベント
	GameEventManager::Instance().RegisterEventType("space_change_start", m_pEventListener);
	m_pEventListener->RegisterSynEventFunc("space_change_start", std::bind(&ar::Stage::PrepareSpaceChange, this));

	// 時戻し(ステージを入れ替える前の状態に戻す)イベント
	GameEventManager::Instance().RegisterEventType("space_change_return_start", m_pEventListener);

	// プレイヤーリスポーン開始イベント
	GameEventManager::Instance().RegisterEventType("player_respawn_start", m_pEventListener);
}

void Stage::Control(void)
{
	HandleEvent();

	switch(m_CurrentState)
	{
	case ENTER:
		m_pPlayer->StartStage();
		break;

	case EXECUTE:
		m_pPlayer->Control();
		m_pStageObjManager->Control();
		m_pCollisionManager->UpDate();
		m_pBackground->Control();
		break;

	case STAGE_SPACE_CHANGE:
		if(StageDataChangeManager::Instance().ChangeSpace())
		{
			m_pCollisionManager->UpDate();
			GameEventManager::Instance().TriggerSynEvent("space_change_end");
		}
		m_CurrentState = EXECUTE;
		break;

	case STAGE_SPACE_RETURN:
		if(StageDataChangeManager::Instance().ReturnChangedSpace())
		{
			m_pCollisionManager->UpDate();
			// 入れ替え戻しが完了したら終了イベントをとばす
			GameEventManager::Instance().ReceiveEvent("space_change_return_end");
			GameEventManager::Instance().TriggerSynEvent("player_move");

			// 2回Controlをよぶことで背景を調整する
			m_pBackground->Control();
			m_pBackground->Control();
			m_CurrentState = EXECUTE;
		}
		break;

	case PLAYER_RESPAWN:
		// リスポーン処理は前に入れ替えた場所まで戻る処理を行う
		if(StageDataChangeManager::Instance().ReturnBeforeStageData())
		{
			m_pCollisionManager->UpDate();
			// 処理が完了したら終了イベントをとばす
			GameEventManager::Instance().ReceiveEvent("player_respawn_end");
			GameEventManager::Instance().TriggerSynEvent("player_move");

			// 2回Controlをよぶことで背景を調整する
			m_pBackground->Control();
			m_pBackground->Control();
			m_CurrentState = EXECUTE;
		}

		break;

	case EXIT:
		m_pPlayer->CompleteStage();
		break;

	default:
		// do nothing
		break;
	}

	m_pGoddessPointUI->Control();
}

void Stage::Draw(void)
{
	switch(m_CurrentState)
	{
	case STAGE_SPACE_RETURN:
		return;
		break;

	case PLAYER_RESPAWN:
		return;
		break;

	default:
		// do nothing
		break;
	}
	m_pBackground->Draw();
	m_pStageObjManager->Draw();
	m_pPlayer->Draw();
	m_pGoddessPointUI->Draw();
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void Stage::CreateObj(int typeID, int yNum, int xNum)
{
	INDEX_DATA data;
	switch(typeID)
	{
	case ObjBase::BLANK:
	{
		m_pStageDataManager->SetCurrentStageChipData(yNum, xNum);

	}
		break;

	case ObjBase::PLAYER:
		if(m_pPlayer == nullptr)
		{
			data.m_YNum = yNum;
			data.m_XNum = xNum;
			m_pPlayer = new Player(m_pStageDataManager, m_pCollisionManager, data, m_PlayerTexID);
			m_pStageDataManager->SetCurrentStageChipData(yNum, xNum, m_pPlayer);
		}

		break;

	default:
	{
		data.m_YNum = yNum;
		data.m_XNum = xNum;
		m_pStageObjManager->CreateStageObj(typeID, data);
	}
		break;
	}
}

void Stage::HandleEvent(void)
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
			if(gameEvent == "goal_touch")
			{
				m_CurrentState = EXIT;
				return;
			}
			else if(gameEvent == "space_change_return_start")
			{
				m_CurrentState = STAGE_SPACE_RETURN;
				m_pEventListener->DelEvent();
				return;
			}
			else if(gameEvent == "player_respawn_start")
			{
				m_CurrentState = PLAYER_RESPAWN;
				m_pEventListener->DelEvent();
				return;
			}

		}

		m_pEventListener->DelEvent();
	}

}

void Stage::PrepareSpaceChange(void)
{
	m_CurrentState = STAGE_SPACE_CHANGE;
}


}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
