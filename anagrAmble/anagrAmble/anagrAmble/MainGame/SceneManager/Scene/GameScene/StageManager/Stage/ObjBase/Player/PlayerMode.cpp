//==================================================================================================================================//
//!< @file		PlayerMode.cpp
//!< @brief		ar::PlayerModeクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "PlayerMode.h"
#include "Player.h"
#include "Anchor.h"
#include "SandwichedStageSpace/SandwichedStageSpace.h"
#include "../../../../GameEventManager/GameEventManager.h"
#include "../../../../../../../ControllerEnum.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

PlayerMode::PlayerMode(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager, 
				Player*	pPlayer, int texID)
	: m_pLibrary(sl::ISharokuLibrary::Instance())
	, m_pStageDataManager(pStageDataManager)
	, m_pCollisionManager(pCollisionManager)
	, m_pPlayer(pPlayer)
	, m_CurrentModeType(NORMAL)
{
	for(auto& pAnchor : m_pAnchors)
	{
		pAnchor = new Anchor(m_pStageDataManager, m_pCollisionManager
							, m_pPlayer->GetStageIndex(), m_pPlayer, texID);
	}

	m_pSandwichedStageSpace = new SandwichedStageSpace(pStageDataManager, pCollisionManager, pPlayer);
}

PlayerMode::~PlayerMode(void)
{
	sl::DeleteSafely(&m_pSandwichedStageSpace);

	for(auto& pAnchor : m_pAnchors)
	{
		sl::DeleteSafely(&pAnchor);
	}
}

void PlayerMode::InitializeAnchor(void)
{
	m_pAnchors[0]->InitializeData(m_pAnchors[1]);
	m_pAnchors[1]->InitializeData(m_pAnchors[0]);
}

void PlayerMode::Control(void)
{
	if(m_pLibrary->CheckCustomizeState(ANCHOR_RETRIEVE, sl::PUSH))
	{
		// アンカー回収
		for(auto& pAnchor : m_pAnchors)
		{
			if(pAnchor->GetHasPlacePosStage())
			{
				GameEventManager::Instance().ReceiveEvent("anchor_retrieve");
				break;
			}
		}
	}

	switch(m_CurrentModeType)
	{
	case NORMAL:
		if(m_pLibrary->CheckCustomizeState(MODE_CHANGE, sl::PUSH))
		{
			if(m_pAnchors[0]->GetHasPlacePosStage() && m_pAnchors[1]->GetHasPlacePosStage())
			{	// どちらのアンカ-もすでにステージにおかれているなら エリア入れ替えモードへ
				m_CurrentModeType = AREA_CHENGE;
			}
			else
			{
				m_CurrentModeType = ANCHOR_ACTION;
			}
		}
		break;

	case ANCHOR_ACTION:
		
		if(m_pLibrary->CheckCustomizeState(ANCHOR_SET, sl::PUSH))
		{
			// アンカー設置
			for(auto& pAnchor : m_pAnchors)
			{
				if(pAnchor->CanPlaceStage())
				{
					pAnchor->PlacePosStage();
					break;
				}
			}
		}

		if(m_pAnchors[0]->GetHasPlacePosStage() && m_pAnchors[1]->GetHasPlacePosStage())
		{	// どちらのアンカ-もステージにおかれたら モードをエリア入れ換えモードへ
			m_pSandwichedStageSpace->InitializeData(m_pAnchors[0], m_pAnchors[1]);
			m_CurrentModeType = AREA_CHENGE;
		}

		if(m_pLibrary->CheckCustomizeState(MODE_CHANGE, sl::PUSH))
		{
			m_CurrentModeType = NORMAL;
		}

		break;

	case AREA_CHENGE:
		if(RESULT_FAILED(m_pAnchors[0]->GetHasPlacePosStage())
			|| RESULT_FAILED(m_pAnchors[1]->GetHasPlacePosStage()))
		{	// どちらかのアンカーが置かれていなかったら、挟んだ空間を破棄して、
			// アンカーセットモードで移行
			m_pSandwichedStageSpace->DiscardData();
				m_CurrentModeType = ANCHOR_ACTION;
				break;
		}

		if(m_pLibrary->CheckCustomizeState(SPACE_CHANGE, sl::PUSH))
		{
			GameEventManager::Instance().TriggerSynEvent("space_change_start");
			break;
		}

		if(m_pLibrary->CheckCustomizeState(MODE_CHANGE, sl::PUSH))
		{
			m_CurrentModeType = NORMAL;
		}
		break;

	default:
		// do nothing
		break;
	}

	for(auto& pAnchor : m_pAnchors)
	{
		pAnchor->Control();
	}

	m_pSandwichedStageSpace->Control();
}

void PlayerMode::Draw(void)
{
	switch(m_CurrentModeType)
	{
	case NORMAL:
		break;

	case ANCHOR_ACTION:
		for(auto& pAnchor : m_pAnchors)
		{
			if(RESULT_FAILED(pAnchor->GetHasPlacePosStage()))
			{
				pAnchor->Draw();
				break;
			}
		}
		break;

	case AREA_CHENGE:
		m_pSandwichedStageSpace->Draw();
		break;

	default:
		// do nothing
		break;
	}

	for(auto& pAnchor : m_pAnchors)
	{
		if(pAnchor->GetHasPlacePosStage())
		{
			pAnchor->Draw();
		}
	}
}

void PlayerMode::Reset(void)
{
	// 挟んだ空間を削除
	m_pSandwichedStageSpace->DiscardData();

	// アンカーをプレイヤーの元に戻す
	for(auto& pAnchor : m_pAnchors)
	{
		pAnchor->PlacePosPlayerFront();
	}

	// 通常モードに変更する
	m_CurrentModeType = NORMAL;
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
