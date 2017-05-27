//==================================================================================================================================//
//!< @file		BasePoint.cpp
//!< @brief		ar::BasePointクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "BasePoint.h"
#include "../../GameEventManager/GameEventManager.h"
#include "../../GameEventManager/EventLisner.h"

namespace ar
{

/* Unnmaed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const float PlayerInterVal = 810.f;		//!< プレイヤーとの間隔

}

/* Public Functions ------------------------------------------------------------------------------------------- */

BasePoint::BasePoint(void)
	: m_Pos({0.0f, 0.0f})
	, m_CuurentPlayerPos({0.0f, 0.0f})
	, m_OldPlayerPos({0.0f, 0.0f})
	, m_pEventLisner(nullptr)
	, m_StageWidth(0.0f)
{
	m_pEventLisner = new EventLisner();
	GameEventManager::Instance().RegisterEventType("player_move", m_pEventLisner);
}

BasePoint::~BasePoint(void)
{
	sl::DeleteSafely(m_pEventLisner);
}

void BasePoint::Initialize(float stageWidth, const sl::SLVECTOR2& rPlayerPos)
{
	m_StageWidth		= stageWidth;
	m_CuurentPlayerPos	= rPlayerPos;
	m_OldPlayerPos		= rPlayerPos;

	// プレイヤーがステージの左端付近にいない場合はベースポイントの位置を動かす
	if(m_CuurentPlayerPos.x > PlayerInterVal)
	{
		// 右端付近にいた場合はステージの１番右端にへ
		// それ以外はプレイヤー座標に補正をかけて移動
		if(m_CuurentPlayerPos.x  >  (m_StageWidth - PlayerInterVal))
		{	
			m_Pos.x = m_StageWidth;
		}
		else
		{	
			m_Pos.x = m_CuurentPlayerPos.x - PlayerInterVal;
		}
	}
}

void BasePoint::Update(void)
{
	HandleEvent();
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void BasePoint::HandleEvent(void)
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
			if(gameEvent == "player_move")
			{
				Move();
			}
		}

		m_pEventLisner->DelEvent();
	}
}

void BasePoint::Move(void)
{
	if(m_CuurentPlayerPos.x < PlayerInterVal || 
		m_CuurentPlayerPos.x > (m_StageWidth - PlayerInterVal))
	{	// ステージ左端付近と右端付近にプレイヤーがいるときは動かない
		return;
	}
	else
	{
		m_Pos.x += (m_CuurentPlayerPos.x - m_OldPlayerPos.x);
		GameEventManager::Instance().ReceiveEvent("base_point_move");
	}
}


}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
