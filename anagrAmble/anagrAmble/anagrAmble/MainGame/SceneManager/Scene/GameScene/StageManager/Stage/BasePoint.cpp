﻿//==================================================================================================================================//
//!< @file		BasePoint.cpp
//!< @brief		ar::BasePointクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "BasePoint.h"
#include "../../GameEventManager/GameEventManager.h"
#include "../../GameEventManager/EventLisner.h"
#include "ObjBase/ObjBase.h"
#include "ObjBase/Player/Player.h"
#include "../../../../../ControllerEnum.h"
#include "ObjBase/Player/SandwichedStageSpace/SandwichedStageSpaceObj.h"
#include "ObjBase/Player/SandwichedStageSpace/SandwichedSpaceBackground.h"

namespace ar
{

/* Unnmaed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const float PlayerInterVal	= 960.f;		//!< プレイヤーとの間隔
const float CorrectionVal	= 100.f;			//!< 補正値。ステージが少しはみだしてしまう為

}

/* Public Functions ------------------------------------------------------------------------------------------- */

BasePoint::BasePoint(void)
	: m_Pos({0.0f, 0.0f})
	, m_CurrentPlayerPos({0.0f, 0.0f})
	, m_OldPlayerPos({0.0f, 0.0f})
	, m_pEventLisner(nullptr)
	, m_StageWidth(0.0f)
{
	m_pEventLisner = new EventLisner();
	GameEventManager::Instance().RegisterEventType("player_move", m_pEventLisner);
	m_pEventLisner->RegisterSynEventFunc("player_move", std::bind(&ar::BasePoint::Move, this));
}

BasePoint::~BasePoint(void)
{
	sl::DeleteSafely(m_pEventLisner);
}

void BasePoint::Initialize(float stageWidth, Player* pPlayer)
{
	m_StageWidth		= stageWidth;
	m_pPlayer			= pPlayer;
	m_CurrentPlayerPos = m_OldPlayerPos = m_pPlayer->GetPos();;

	// プレイヤーがステージの左端付近にいない場合はベースポイントの位置を動かす
	if(m_CurrentPlayerPos.x > PlayerInterVal)
	{
		// 右端付近にいた場合はステージの１番右端にへ
		// それ以外はプレイヤー座標に補正をかけて移動
		if(m_CurrentPlayerPos.x  >  (m_StageWidth - PlayerInterVal))
		{	
			m_Pos.x = m_StageWidth;
		}
		else
		{	
			m_Pos.x = m_CurrentPlayerPos.x - PlayerInterVal;
		}
	}

	// ObJbaseのBasePointPosを更新する
	ObjBase::SetBasePointPos(m_Pos);
	SandwichedStageSpaceObj::SetBasePointPos(m_Pos);
	SandwichedSpaceBackground::SetBasePointPos(m_Pos);

}

/* Private Functions ------------------------------------------------------------------------------------------ */

void BasePoint::Move(void)
{
	if(m_pPlayer == nullptr)
	{
		return;
	}

	m_CurrentPlayerPos = m_pPlayer->GetPos();	// 現在のプレイヤー座標を更新する

	if((m_CurrentPlayerPos.x - 0.0f) < PlayerInterVal)
	{	// 左端付近にプレイヤーがいるときは動かない
		ObjBase::SetBasePointPos(m_Pos);
		SandwichedStageSpaceObj::SetBasePointPos(m_Pos);
		SandwichedSpaceBackground::SetBasePointPos(m_Pos);
		m_OldPlayerPos = m_CurrentPlayerPos;
		return;
	}
	else if	(m_CurrentPlayerPos.x > (m_StageWidth - PlayerInterVal - CorrectionVal))
	{	// 右端付近にプレイヤーがいるときは動かない
		ObjBase::SetBasePointPos(m_Pos);
		SandwichedStageSpaceObj::SetBasePointPos(m_Pos);
		SandwichedSpaceBackground::SetBasePointPos(m_Pos);
		m_OldPlayerPos = m_CurrentPlayerPos;
		return;
	}
	else
	{	// プレイヤーが動いた分だけ動かし、ObJbaseのBasePointPosを更新する
		m_Pos.x += (m_CurrentPlayerPos.x - m_OldPlayerPos.x);

		// プレイヤーとの間が離れすぎていたら調整する
		if((m_CurrentPlayerPos.x - m_Pos.x) >  PlayerInterVal)
		{
			m_Pos.x += ((m_CurrentPlayerPos.x - m_Pos.x) - PlayerInterVal);
		}

		ObjBase::SetBasePointPos(m_Pos);
		SandwichedStageSpaceObj::SetBasePointPos(m_Pos);
		SandwichedSpaceBackground::SetBasePointPos(m_Pos);
		m_OldPlayerPos = m_CurrentPlayerPos;
	}
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
