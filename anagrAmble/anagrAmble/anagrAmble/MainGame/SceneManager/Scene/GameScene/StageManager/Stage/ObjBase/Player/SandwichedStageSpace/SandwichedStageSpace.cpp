﻿//==================================================================================================================================//
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
#include "../../../../../GameEventManager/EventLisner.h"

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
	: m_pEventLisner(new EventLisner())
	, m_pStageDataManager(pStageDataManager)
	, m_pCollisionManager(pCollisionManager)
	, m_pPlayer(pPlayer)
	, m_pBackground(new SandwichedSpaceBackground())
{
	m_StageChipSize = m_pStageDataManager->GetStageChipSize();
	GameEventManager::Instance().RegisterEventType("sandwiched_space_release", m_pEventLisner);
	GameEventManager::Instance().RegisterEventType("player_move", m_pEventLisner);
	m_pEventLisner->RegisterSynEventFunc("player_move", std::bind(&ar::SandwichedStageSpace::Move, this));
}

SandwichedStageSpace::~SandwichedStageSpace(void)
{
	for(auto& pObj : m_pObjs)
	{
		sl::DeleteSafely(pObj);
	}

	sl::DeleteSafely(m_pBackground);
	sl::DeleteSafely(m_pEventLisner);
}

void SandwichedStageSpace::InitializeData(Anchor* pAnchorOne, Anchor*	pAnchorTwo)
{
	Stage::INDEX_DATA anchorOneIndex = pAnchorOne->GetStageIndex();
	Stage::INDEX_DATA anchorTwoIndex = pAnchorTwo->GetStageIndex();

	// 2つのアンカーからステージの開始インデックスと終了インデックスを求める
	// なおm_EndIndex.m_YNumの計算で2ひいているのは、インデックス番号を1低いものにする為
	if(anchorOneIndex.m_XNum < anchorTwoIndex.m_XNum)
	{
		m_StartIndex.m_XNum = anchorOneIndex.m_XNum;
		m_StartIndex.m_YNum =  SpaceYIndexMin;
		m_EndIndex.m_XNum = anchorTwoIndex.m_XNum;
		m_EndIndex.m_YNum = (m_pStageDataManager->GetStageHeightChipNum() - 2);
	}
	else
	{
		m_StartIndex.m_XNum = anchorTwoIndex.m_XNum;
		m_StartIndex.m_YNum =  SpaceYIndexMin;
		m_EndIndex.m_XNum = anchorOneIndex.m_XNum;
		m_EndIndex.m_YNum = (m_pStageDataManager->GetStageHeightChipNum() - 2);
	}

	// 描画に必要なデータを設定する
	{
		SandwichedStageSpaceObj::SetPlayerRect(m_pPlayer->GetCurrentRectData());
		m_pBackground->SetPlayerRect(m_pPlayer->GetCurrentRectData());

		SandwichedStageSpaceObj::SetIsPlayerFacingRight(m_pPlayer->IsFacingRight());
		m_pBackground->SetIsPlayerFacingRight(m_pPlayer->IsFacingRight());

		float spaceWidth = (m_EndIndex.m_XNum - m_StartIndex.m_XNum) * m_StageChipSize;
		SandwichedStageSpaceObj::SetSandwichedSpaceWidth(spaceWidth);

		SandwichedStageSpaceObj::SetStageMapChipSize(m_pStageDataManager->GetStageChipSize());
		SandwichedSpaceBackground::SetStageMapChipSize(m_pStageDataManager->GetStageChipSize());
	}

	// 挟んだ空間の初期化を行う
	{
		sl::SLVECTOR2 pos = {0.0f, static_cast<float>(m_StartIndex.m_YNum * m_StageChipSize)};
		float spaceWidth = (m_EndIndex.m_XNum - m_StartIndex.m_XNum) * m_StageChipSize;
		float spaceHeight = (m_EndIndex.m_YNum - m_StartIndex.m_YNum) * m_StageChipSize + m_StageChipSize;
		m_pBackground->InitializeData(pos, spaceWidth, spaceHeight);
	}
	
	// 描画オブジェクトを生成する
	for(short yNum = m_StartIndex.m_YNum; yNum <= m_EndIndex.m_YNum; ++yNum)
	{
		for(short xNum = m_StartIndex.m_XNum ; xNum < m_EndIndex.m_XNum; ++xNum)
		{
			// 挟んだ空間のオブジェクトの設定する
			const ObjBase* pObj = m_pStageDataManager->GetObjBasePointer(yNum, xNum);
			if(pObj == nullptr)
			{
				continue;
			}

			sl::SLVECTOR2 pos;
			pos.x = pObj->GetPos().x - (m_StartIndex.m_XNum * m_StageChipSize);
			pos.y = pObj->GetPos().y;
			sl::DrawingID id = pObj->GetDrawingID();
			m_pObjs.push_back(new SandwichedStageSpaceObj(pos, id));
		}
	}
}

void SandwichedStageSpace::DiscardData(void)
{
	m_StartIndex.m_XNum = 0;
	m_StartIndex.m_YNum = 0;

	m_EndIndex.m_XNum = 0;
	m_EndIndex.m_YNum = 0;

	for(auto& pObj : m_pObjs)
	{
		sl::DeleteSafely(pObj);
	}

	std::vector<SandwichedStageSpaceObj*>().swap(m_pObjs);

	m_pBackground->DiscardData();
}

void SandwichedStageSpace::Control(void)
{
	HandleEvent();
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
			if(gameEvent == "sandwiched_space_release")
			{
				DiscardData();
			}
		}

		m_pEventLisner->DelEvent();
	}
}

void SandwichedStageSpace::Move(void)
{
	SandwichedStageSpaceObj::SetPlayerRect(m_pPlayer->GetCurrentRectData());
	m_pBackground->SetPlayerRect(m_pPlayer->GetCurrentRectData());

	SandwichedStageSpaceObj::SetIsPlayerFacingRight(m_pPlayer->IsFacingRight());
	m_pBackground->SetIsPlayerFacingRight(m_pPlayer->IsFacingRight());

	SandwichedStageSpaceObj::SetPlayerIndexData(m_pPlayer->GetStageIndex());
	m_pBackground->SetPlayerIndexData(m_pPlayer->GetStageIndex());
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
