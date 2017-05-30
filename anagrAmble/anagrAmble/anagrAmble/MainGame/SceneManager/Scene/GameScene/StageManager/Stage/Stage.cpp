//==================================================================================================================================//
//!< @file		Stage.cpp
//!< @brief		ar::Stageクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "Stage.h"
#include "../../GameEventManager/EventLisner.h"
#include "../StageDataManager.h"
#include "CollisionManager.h"
#include "BasePoint.h"
#include "StageObjManager/StageObjManager.h"
#include "StageBackground.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

Stage::Stage(StageDataManager*	pStageDataManager)
	: m_pLibrary(sl::ISharokuLibrary::Instance())
	, m_pEventLisiner(new EventLisner())
	, m_pStageDataManager(pStageDataManager)
	, m_pCollisionManager(new CollisionManager())
	, m_pBasePoint(new BasePoint())
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
	sl::DeleteSafely(m_pBasePoint);
	sl::DeleteSafely(m_pCollisionManager);
	sl::DeleteSafely(m_pEventLisiner);
}

void Stage::Initialize(void)
{
	int stageObjTexID = m_pLibrary->LoadTexture("../Resource/GameScene/Object_File.png");
	m_pStageObjManager = new StageObjManager(m_pStageDataManager, m_pCollisionManager, stageObjTexID);

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
	/** @todo 現在仮実装 */
	sl::SLVECTOR2 testPos = {0.0f, 0.0f};/*==========================================================================================================修正予定*/
	m_pBasePoint->Initialize(m_pStageDataManager->GetStageWidth(), testPos);

	// 背景の設定を行う
	int stageBGTexID = m_pLibrary->LoadTexture(m_pStageDataManager->GetBackGoundTexFileName().c_str());
	m_pBackground = new StageBackground(m_pBasePoint, stageBGTexID);

}

void Stage::Control(void)
{
	HandleEvent();

	switch(m_CurrentState)
	{
	case ENTER:
		break;

	case EXECUTE:
		// プレイヤー処理

		// 下記はデバック用のベースポイント
		m_pBasePoint->Update();

		m_pStageObjManager->Control();
		m_pBackground->Control();
		break;

	case AREA_CHANGE:
		break;

	case EXIT:
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

	// プレイヤーの描画
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void Stage::CreateObj(int typeID, int yNum, int xNum)
{
	switch(typeID)
	{
	case ObjBase::BLANK:
		// do noting
		break;

	case ObjBase::PLAYER:
		// 後で実装
		break;

	default:
	{
		INDEX_DATA data;
		data.m_YNum = yNum;
		data.m_XNum = xNum;
		m_pStageObjManager->CreateStageObj(typeID, data);
	}
		break;
	}
}

void Stage::HandleEvent(void)
{}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
