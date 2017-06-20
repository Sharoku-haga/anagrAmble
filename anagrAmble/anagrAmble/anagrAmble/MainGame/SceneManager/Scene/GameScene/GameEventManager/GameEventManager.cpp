//==================================================================================================================================//
//!< @file		GameEventManager.cpp
//!< @brief		ar::GameEventManagerクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "GameEventManager.h"
#include "EventListener.h"

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
		std::vector<EventListener*>().swap(eventType.second);
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
			std::vector<EventListener*>& pListeners = m_EventType[currentEvent];

			for(auto& plistener : pListeners)
			{
				plistener->ReceiveEvent(currentEvent);
			}
		}

		m_CuurentEvent.clear();
		std::deque<std::string>().swap(m_CuurentEvent);
	}
}

void GameEventManager::RegisterEventType(const std::string& rEventType, EventListener* pLisner)
{
	m_EventType[rEventType].push_back(pLisner);
}

void GameEventManager::DelEventType(const std::string& rEventType)
{
	m_EventType[rEventType].clear();
	std::vector<EventListener*>().swap(m_EventType[rEventType]);
	m_EventType.erase(rEventType);
}

void GameEventManager::TriggerSynEvent(const std::string& rEventType)
{
	std::vector<EventListener*>& pListeners = m_EventType[rEventType];

	for(auto& plistener : pListeners)
	{
		plistener->HandleSynEvent(rEventType);
	}
}

void GameEventManager::ReceiveEvent(const std::string& rEventType)
{
	for(auto& currentEvent : m_CuurentEvent )
	{
		if(currentEvent == rEventType)
		{ // すでにイベントが登録されていたらreturn
			return;
		}
	}
	m_CuurentEvent.push_back(rEventType);
}


}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
