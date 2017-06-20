//==================================================================================================================================//
//!< @file		EventListener.cpp
//!< @brief		ar::EventListenerクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "EventListener.h"
#include "GameEventManager.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

EventListener::EventListener(void)
{}

EventListener::~EventListener(void)
{}

void EventListener::RegisterSynEventFunc(std::string eventType, std::function<void(void)> callBackFunc)
{
	m_SynEventFunc[eventType] = callBackFunc;
}

void EventListener::ReceiveEvent(std::string eventType)
{
	m_CuurentEvent.push_back(eventType);
}

void EventListener::DelEvent(void)
{
	m_CuurentEvent.clear();
}

void EventListener::HandleSynEvent(std::string eventType)
{
	m_SynEventFunc[eventType]();
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
