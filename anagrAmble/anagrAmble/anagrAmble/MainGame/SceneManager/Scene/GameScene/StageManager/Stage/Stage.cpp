//==================================================================================================================================//
//!< @file		Stage.cpp
//!< @brief		ar::Stageクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "Stage.h"
#include "../../GameEventManager/EventLisner.h"
#include "../../GameEventManager/GameEventManager.h"
#include "../StageDataManager.h"
#include "CollisionManager.h"
#include "BasePoint.h"
#include "ObjBase/Player/Player.h"
#include "StageObjManager/StageObjManager.h"
#include "StageBackground.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

Stage::Stage(StageDataManager*	pStageDataManager)
	: m_pLibrary(sl::ISharokuLibrary::Instance())
	, m_pEventLisner(new EventLisner())
	, m_pStageDataManager(pStageDataManager)
	, m_pCollisionManager(new CollisionManager(pStageDataManager))
	, m_pBasePoint(new BasePoint())
	, m_pPlayer(nullptr)
	, m_pStageObjManager(nullptr)
	, m_pBackground(nullptr)
	, m_CurrentState(ENTER)
{
	// デバック用
	m_CurrentState = EXECUTE;
}

Stage::~Stage(void)
{
	sl::DeleteSafely(m_pBackground);
	sl::DeleteSafely(m_pStageObjManager);
	sl::DeleteSafely(m_pPlayer);
	sl::DeleteSafely(m_pBasePoint);
	sl::DeleteSafely(m_pCollisionManager);
	sl::DeleteSafely(m_pEventLisner);
}

void Stage::Initialize(void)
{
	ObjBase::SetStageChipSize(m_pStageDataManager->GetStageChipSize());
	
	m_PlayerTexID = m_pLibrary->LoadTexture("../Resource/GameScene/Player.png");

	m_StageObjTexID = m_pLibrary->LoadTexture("../Resource/GameScene/Object_File.png");
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

	// ベースポイントの設定を行う 
	m_pBasePoint->Initialize(m_pStageDataManager->GetStageWidth(), m_pPlayer);

	// 背景の設定を行う
	int stageBGTexID = m_pLibrary->LoadTexture(m_pStageDataManager->GetBackGoundTexFileName().c_str());
	m_pBackground = new StageBackground(m_pBasePoint, stageBGTexID);

	// イベント登録
	GameEventManager::Instance().RegisterEventType("goal_touch", m_pEventLisner);

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

	case AREA_CHANGE:
		break;

	case EXIT:
		m_pPlayer->CompleteStage();
		break;

	default:
		// do nothing
		break;
	}
}

void Stage::Draw(void)
{
	m_pBackground->Draw();
	m_pStageObjManager->Draw();
	m_pPlayer->Draw();

	// プレイヤーの描画
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void Stage::CreateObj(int typeID, int yNum, int xNum)
{
	INDEX_DATA data;
	switch(typeID)
	{
	case ObjBase::BLANK:
		// do noting
		break;

	case ObjBase::PLAYER:
		if(m_pPlayer == nullptr)
		{
			data.m_YNum = yNum;
			data.m_XNum = xNum;
			m_pPlayer = new Player(m_pStageDataManager, m_pCollisionManager, data, m_PlayerTexID);
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
			if(gameEvent == "goal_touch")
			{
				m_CurrentState = EXIT;
				return;
			}
		}

		m_pEventLisner->DelEvent();
	}

}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
