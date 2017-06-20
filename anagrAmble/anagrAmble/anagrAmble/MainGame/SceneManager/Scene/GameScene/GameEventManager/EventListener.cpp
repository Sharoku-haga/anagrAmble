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

void EventListener::RegisterSynEventFunc(const std::string& rEventType, const std::function<void(void)>& rCallBackFunc)
{
	m_SynEventFunc[rEventType] = rCallBackFunc;
}

void EventListener::ReceiveEvent(const std::string& rEventType)
{
	m_CuurentEvent.push_back(rEventType);
}

void EventListener::DelEvent(void)
{
	m_CuurentEvent.clear();
}

void EventListener::HandleSynEvent(const std::string& rEventType)
{
	m_SynEventFunc[rEventType]();
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
