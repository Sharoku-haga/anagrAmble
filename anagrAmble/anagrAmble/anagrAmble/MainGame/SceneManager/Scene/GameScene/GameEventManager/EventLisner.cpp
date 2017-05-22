//==================================================================================================================================//
//!< @file		EventLisner.cpp
//!< @brief		ar::EventLisnerクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "EventLisner.h"
#include "GameEventManager.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

EventLisner::EventLisner(void)
{}

EventLisner::~EventLisner(void)
{}

void EventLisner::RegisterSynEventFunc(std::string eventType, std::function<void(void)> callBackFunc)
{
	m_SynEventFunc[eventType] = callBackFunc;
}

void EventLisner::ReceiveEvent(std::string eventType)
{
	m_CuurentEvent.push_back(eventType);
}

void EventLisner::DelEvent(void)
{
	m_CuurentEvent.clear();
}

void EventLisner::HandleSynEvent(std::string eventType)
{
	m_SynEventFunc[eventType]();
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
