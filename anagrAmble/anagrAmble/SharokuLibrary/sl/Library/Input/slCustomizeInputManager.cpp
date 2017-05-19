//==================================================================================================================================//
//!< @file		slCustomizeInputManager.cpp
//!< @brief		sl::CustomizeInputManagerƒNƒ‰ƒXŽÀ‘•
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "slCustomizeInputManager.h"
#include "DirectInput/diInputManager.h"
#include "DirectInput\diKeyDevice.h"
#include "XInput/xiGamePad.h"
#include "../../slBuild.h"

namespace sl
{

/* Public Functions ------------------------------------------------------------------------------------------- */

CustomizeInputManager::CustomizeInputManager(di::InputManager* pInputManager, xi::GamePad* pGamePad)
	: m_pKeyDevice(pInputManager->GetKeyDevice())
	, m_pXiGamePad(pGamePad)
{}

CustomizeInputManager::~CustomizeInputManager(void)
{}

void CustomizeInputManager::RegisterCustomizeType(int ID, HID_TYPE device, int inputType)
{
	m_CustomizeInfos[ID].emplace_back(CUSTOMIZE_INFO (device, inputType));
}

bool CustomizeInputManager::CheckState(int ID, DEVICE_STATE  checkState, int deviceNum)
{
	DEVICE_STATE state = NONE;
	std::vector<CUSTOMIZE_INFO> customizeInfo = m_CustomizeInfos[ID];

	for(auto& info : customizeInfo)
	{
		switch(info.m_DeviceType)
		{
		case KEYBOARD:
			state = m_pKeyDevice->CheckKey(info.m_InputType);
			break;

		case MOUSE:
			/** @todo ‚Ü‚¾ŽÀ‘•‚µ‚Ä‚¢‚È‚¢*/
			break;

		case GAMEPAD:
#ifdef USING_XI_GAMEPAD
			state = m_pXiGamePad->CheckState(info.m_InputType, deviceNum);
#endif
			break;

		default:
			// do nothing
			break;
		}

		if(state == checkState)
		{
			return true;
		}
	}
	return false;
}

}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
