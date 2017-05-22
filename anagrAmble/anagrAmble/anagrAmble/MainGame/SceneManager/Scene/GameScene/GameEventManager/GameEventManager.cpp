//==================================================================================================================================//
//!< @file		GameEventManager.cpp
//!< @brief		ar::GameEventManagerクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "GameEventManager.h"
#include "EventLisner.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

GameEventManager::~GameEventManager(void)
{}

void GameEventManager::InitEventType(void)
{
	m_CuurentEvent.clear();
	std::deque<std::string>().swap(m_CuurentEvent);

	for(auto& eventType : m_EventType)
	{
		eventType.second.clear();
		std::vector<EventLisner*>().swap(eventType.second);
	}

	m_EventType.clear();
}

void GameEventManager::Update(void)
{
	if(m_EventType.empty())
	{	// イベントが空なら即returnする
		return;
	}
	else
	{
		// イベントがある場合はそれそれ対応するリスナーに通知する
		for(auto& currentEvent : m_CuurentEvent)
		{
			std::vector<EventLisner*>& pLisners = m_EventType[currentEvent];

			for(auto& plisner : pLisners)
			{
				plisner->ReceiveEvent(currentEvent);
			}
		}

		m_CuurentEvent.clear();
		std::deque<std::string>().swap(m_CuurentEvent);
	}
}

void GameEventManager::RegisterEventType(std::string eventType, EventLisner* pLisner)
{
	m_EventType[eventType].push_back(pLisner);
}

void GameEventManager::DelEventType(std::string eventType)
{
	m_EventType[eventType].clear();
	std::vector<EventLisner*>().swap(m_EventType[eventType]);
	m_EventType.erase(eventType);
}

void GameEventManager::TriggerSynEvent(std::string eventType)
{
	std::vector<EventLisner*>& pLisners = m_EventType[eventType];

	for(auto& plisner : pLisners)
	{
		plisner->HandleSynEvent(eventType);
	}
}

void GameEventManager::ReceiveEvent(std::string eventType)
{
	for(auto& currentEvent : m_CuurentEvent )
	{
		if(currentEvent == eventType)
		{ // すでにイベントが登録されていたらreturn
			return;
		}
	}
	m_CuurentEvent.push_back(eventType);
}


}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
