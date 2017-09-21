//==================================================================================================================================//
//!< @file		CommonSoundManager.cpp
//!< @brief		ar::CommonSoundManagerクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "CommonSoundManager.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

void CommonSoundManager::Initialize(void)
{
	m_pLibrary = sl::ISharokuLibrary::Instance();
}

void CommonSoundManager::LoadSound(int id, char* pFilePath)
{
	m_pLibrary->LoadSound(id, pFilePath);
	m_SoundID.push_back(id);
}

void CommonSoundManager::PlayBackSound(int id, int soundMode)
{
	m_pLibrary->PlayBackSound(id, soundMode);
}

void CommonSoundManager::ReleaseSoundALL(void)
{
	if(m_SoundID.empty())
	{
		return;
	}

	for(auto& id : m_SoundID)
	{
		m_pLibrary->ReleaseSound(id);
	}

	m_SoundID.clear();
	std::vector<int>().swap(m_SoundID);
}

/* Private Functions ------------------------------------------------------------------------------------------ */

CommonSoundManager::~CommonSoundManager(void)
{
	ReleaseSoundALL();
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
