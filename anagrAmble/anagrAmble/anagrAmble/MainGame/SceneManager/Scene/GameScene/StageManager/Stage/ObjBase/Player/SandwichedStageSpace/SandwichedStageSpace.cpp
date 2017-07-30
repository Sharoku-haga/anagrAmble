//==================================================================================================================================//
//!< @file		SandwichedStageSpace.cpp
//!< @brief		ar::SandwichedStageSpaceクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "SandwichedStageSpace.h"
#include "../../../../StageDataManager.h"
#include "../../../CollisionManager.h"
#include "../Player.h"
#include "SandwichedStageSpaceObj.h"
#include "SandwichedSpaceBackground.h"
#include "../Anchor.h"
#include "../../../../../GameEventManager/GameEventManager.h"
#include "../../../../../GameEventManager/EventListener.h"
#include "../../../../StageDataChangeManager.h"
#include "../SharokuLibrary/sl/sl.h"

namespace ar
{

/* Unnmaed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const	short  SpaceYIndexMin= 1;			//!< 挟まれた空間内のY軸方向の最小インデックス番号. 固定値

}

/* Public Functions ------------------------------------------------------------------------------------------- */

SandwichedStageSpace::SandwichedStageSpace(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager, 
											Player*	pPlayer)
	: m_pLibrary(sl::ISharokuLibrary::Instance())
	, m_pEventListener(new EventListener())
	, m_pStageDataManager(pStageDataManager)
	, m_pCollisionManager(pCollisionManager)
	, m_pPlayer(pPlayer)
	, m_pBackground(new SandwichedSpaceBackground(pPlayer->GetDrawingID().m_TexID))
{
	m_StageChipSize = m_pStageDataManager->GetStageChipSize();

	// 挟まれた空間解除イベント
	GameEventManager::Instance().RegisterEventType("sandwiched_space_release", m_pEventListener);

	// プレイヤーが移動したというイベント
	GameEventManager::Instance().RegisterEventType("player_move", m_pEventListener);
	m_pEventListener->RegisterSynEventFunc("player_move", std::bind(&ar::SandwichedStageSpace::Move, this));

	// ステージ変更開始イベント
	GameEventManager::Instance().RegisterEventType("space_change_start", m_pEventListener);
	m_pEventListener->RegisterSynEventFunc("space_change_start", std::bind(&ar::SandwichedStageSpace::PrepareSpaceChange, this));

	// ステージ変更終了イベント
	GameEventManager::Instance().RegisterEventType("space_change_end", m_pEventListener);
	m_pEventListener->RegisterSynEventFunc("space_change_end", std::bind(&ar::SandwichedStageSpace::DiscardData, this));

	// 入れ替え戻し終了イベント
	GameEventManager::Instance().RegisterEventType("space_change_return_end", m_pEventListener);
}

SandwichedStageSpace::~SandwichedStageSpace(void)
{
	for(auto& pObj : m_pObjs)
	{
		sl::DeleteSafely(&pObj);
	}

	sl::DeleteSafely(&m_pBackground);
	sl::DeleteSafely(&m_pEventListener);
}

void SandwichedStageSpace::InitializeData(Anchor* pAnchorOne, Anchor* pAnchorTwo)
{
	Stage::INDEX_DATA anchorOneIndex = pAnchorOne->GetStageIndex();
	Stage::INDEX_DATA anchorTwoIndex = pAnchorTwo->GetStageIndex();

	// 2つのアンカーからステージの開始インデックスと終了インデックスを求める
	// X軸方向のインデックスの設定. X軸インデックスが低い数値を開始インデックス、X軸インデックスが高い数値を終了インデックスに設定
	if(anchorOneIndex.m_XIndexNum < anchorTwoIndex.m_XIndexNum)
	{
		m_StartIndex.m_XIndexNum = anchorOneIndex.m_XIndexNum;
		m_EndIndex.m_XIndexNum = anchorTwoIndex.m_XIndexNum;
	}
	else
	{
		m_StartIndex.m_XIndexNum = anchorTwoIndex.m_XIndexNum;
		m_EndIndex.m_XIndexNum = anchorOneIndex.m_XIndexNum;
	}

	// Y軸方向のインデックスの設定. m_EndIndex.m_YIndexNumの計算で2ひいているのは、インデックス番号を1低いものにする為
	m_StartIndex.m_YIndexNum =  SpaceYIndexMin;
	m_EndIndex.m_YIndexNum = (m_pStageDataManager->GetStageHeightChipCount() - 2);

	// 描画に必要なデータを設定
	{
		SandwichedStageSpaceObj::SetPlayerRect(m_pPlayer->GetCurrentRectData());
		m_pBackground->SetPlayerRect(m_pPlayer->GetCurrentRectData());

		SandwichedStageSpaceObj::SetIsPlayerFacingRight(m_pPlayer->IsFacingRight());
		m_pBackground->SetIsPlayerFacingRight(m_pPlayer->IsFacingRight());

		float spaceWidth = (m_EndIndex.m_XIndexNum - m_StartIndex.m_XIndexNum) * m_StageChipSize;
		SandwichedStageSpaceObj::SetSandwichedSpaceWidth(spaceWidth);

		SandwichedStageSpaceObj::SetStageMapChipSize(m_pStageDataManager->GetStageChipSize());
		SandwichedSpaceBackground::SetStageMapChipSize(m_pStageDataManager->GetStageChipSize());
	}

	// 挟んだ空間内のオブジェクトを生成する
	CreateSandwichedObj();
}

void SandwichedStageSpace::DiscardData(void)
{
	DetachSandwichEffect();

	m_StartIndex.m_XIndexNum = 0;
	m_StartIndex.m_YIndexNum = 0;
	m_EndIndex.m_XIndexNum = 0;
	m_EndIndex.m_YIndexNum = 0;

	if(m_pObjs.empty())
	{	// 破棄すべきオブジェクトがないならreturn;
		return;
	}

	for(auto& pObj : m_pObjs)
	{
		m_pLibrary->ReleaseVertex2D(pObj->GetDrawingID().m_VtxID);
		sl::DeleteSafely(&pObj);
	}

	m_pObjs.clear();
	std::vector<SandwichedStageSpaceObj*>().swap(m_pObjs);

	m_pBackground->DiscardData();
}

void SandwichedStageSpace::Control(void)
{
	HandleEvent();

	// 挟まれた空間内のオブジェクトの挟む効果が全て終わっているかチェック
	for(short yIndexNum = m_StartIndex.m_YIndexNum; yIndexNum <= m_EndIndex.m_YIndexNum; ++yIndexNum)
	{
		for(short xIndexNum = m_StartIndex.m_XIndexNum; xIndexNum < m_EndIndex.m_XIndexNum; ++xIndexNum)
		{
			ObjBase* pObj = m_pStageDataManager->GetObjBasePointer(yIndexNum, xIndexNum);
			if(pObj == nullptr
				|| pObj->GetTypeID() == ObjBase::GROUND_B)
			{
				continue;
			}

			if(!pObj->EndSandwichEffect())
			{	// 1つでも挟む効果が終わっていなかったらreturn
				return;
			}
		}
	}

	ApplySandwichEffect();
}

void SandwichedStageSpace::Draw(void)
{
	m_pBackground->Draw();

	for(auto& pObj : m_pObjs)
	{
		pObj->Draw();
	}
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void SandwichedStageSpace::HandleEvent(void)
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
			if(gameEvent == "sandwiched_space_release")
			{	// データを破棄する
				DiscardData();
			}
			else if(gameEvent == "space_change_return_end")
			{	// もし挟んだ空間にオブジェクトがあるなら
				// データが入れ替わっている場合は一旦オブジェクトを破棄してから再度構成し直す
				if(RESULT_FAILED(m_pObjs.empty()))
				{
					DetachSandwichEffect();
				
					for(auto& pObj : m_pObjs)
					{
						sl::DeleteSafely(&pObj);
					}

					m_pObjs.clear();
					std::vector<SandwichedStageSpaceObj*>().swap(m_pObjs);

					m_pBackground->DiscardData();

					CreateSandwichedObj();
				}
			}
		}

		m_pEventListener->DelEvent();
	}
}

void SandwichedStageSpace::CreateSandwichedObj(void)
{
	// 挟んだ空間の初期化を行う
	{
		sl::SLVECTOR2 pos = { 0.0f, static_cast<float>(m_StartIndex.m_YIndexNum * m_StageChipSize) };
		float spaceWidth = (m_EndIndex.m_XIndexNum - m_StartIndex.m_XIndexNum) * m_StageChipSize;
		float spaceHeight = (m_EndIndex.m_YIndexNum - m_StartIndex.m_YIndexNum) * m_StageChipSize + m_StageChipSize;
		m_pBackground->InitializeData(pos, spaceWidth, spaceHeight);
	}

	// 描画オブジェクトを生成する
	for(short yIndexNum = m_StartIndex.m_YIndexNum; yIndexNum <= m_EndIndex.m_YIndexNum; ++yIndexNum)
	{
		for(short xIndexNum = m_StartIndex.m_XIndexNum; xIndexNum < m_EndIndex.m_XIndexNum; ++xIndexNum)
		{
			// 挟んだ空間のオブジェクトの設定する
			ObjBase* pObj = m_pStageDataManager->GetObjBasePointer(yIndexNum, xIndexNum);
			if(pObj == nullptr
				|| pObj->GetTypeID() == ObjBase::GROUND_B
				|| pObj->GetTypeID() == ObjBase::LIGHT_B)
			{
				continue;
			}

			sl::SLVECTOR2 pos;
			pos.x = pObj->GetPos().x - (m_StartIndex.m_XIndexNum * m_StageChipSize);
			pos.y = pObj->GetPos().y;
			sl::DrawingID id = pObj->GetDrawingID();
			m_pObjs.push_back(new SandwichedStageSpaceObj(pos, id));
		}
	}

	ApplySandwichEffect();
}

void SandwichedStageSpace::Move(void)
{
	SandwichedStageSpaceObj::SetPlayerRect(m_pPlayer->GetCurrentRectData());
	m_pBackground->SetPlayerRect(m_pPlayer->GetCurrentRectData());

	SandwichedStageSpaceObj::SetIsPlayerFacingRight(m_pPlayer->IsFacingRight());
	m_pBackground->SetIsPlayerFacingRight(m_pPlayer->IsFacingRight());

	Stage::INDEX_DATA playerIndexData = m_pPlayer->GetStageIndex();

	SandwichedStageSpaceObj::SetPlayerIndexData(playerIndexData);
	m_pBackground->SetPlayerIndexData(playerIndexData);
}

void SandwichedStageSpace::PrepareSpaceChange(void)
{
	StageDataChangeManager::Instance().SetSandwichedSpaceStartIndex(m_StartIndex);
	StageDataChangeManager::Instance().SetSandwichedSpaceEndIndex(m_EndIndex);
}

void SandwichedStageSpace::ApplySandwichEffect(void)
{
	sl::SLVECTOR2 spaceCenterPos;
	spaceCenterPos.x = ((m_EndIndex.m_XIndexNum * m_StageChipSize) - (m_StartIndex.m_XIndexNum * m_StageChipSize)) / 2 
						+ (m_StartIndex.m_XIndexNum * m_StageChipSize);
	spaceCenterPos.y = 0.0f;

	for(short yIndexNum = m_StartIndex.m_YIndexNum; yIndexNum <= m_EndIndex.m_YIndexNum; ++yIndexNum)
	{
		for(short xIndexNum = m_StartIndex.m_XIndexNum; xIndexNum < m_EndIndex.m_XIndexNum; ++xIndexNum)
		{
			// 挟んだ空間のオブジェクトの設定する
			ObjBase* pObj = m_pStageDataManager->GetObjBasePointer(yIndexNum, xIndexNum);
			if(pObj == nullptr
				|| pObj->GetTypeID() == ObjBase::GROUND_B)
			{
				continue;
			}

			pObj->ApplySandwichEffect(spaceCenterPos);
		}
	}
}

void SandwichedStageSpace::DetachSandwichEffect(void)
{
	for(short yIndexNum = m_StartIndex.m_YIndexNum; yIndexNum <= m_EndIndex.m_YIndexNum; ++yIndexNum)
	{
		for(short xIndexNum = m_StartIndex.m_XIndexNum; xIndexNum < m_EndIndex.m_XIndexNum; ++xIndexNum)
		{
			ObjBase* pObj = m_pStageDataManager->GetObjBasePointer(yIndexNum, xIndexNum);
			if(pObj == nullptr
				|| pObj->GetTypeID() == ObjBase::GROUND_B)
			{
				continue;
			}

			pObj->DetachSandwichEffect();
		}
	}
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
