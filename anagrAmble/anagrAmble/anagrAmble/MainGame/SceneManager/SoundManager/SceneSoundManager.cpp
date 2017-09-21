//==================================================================================================================================//
//!< @file		SceneSoundManager.cpp
//!< @brief		ar::SceneSoundManagerクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "SceneSoundManager.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

void SceneSoundManager::Initialize(void)
{
	m_pLibrary = sl::ISharokuLibrary::Instance();
}

void SceneSoundManager::LoadSound(int id, char* pFilePath)
{
	m_pLibrary->LoadSound(id, pFilePath);
	m_SoundID.push_back(id);
}

void SceneSoundManager::PlayBackSound(int id, int soundMode)
{
	m_pLibrary->PlayBackSound(id, soundMode);
}

void SceneSoundManager::ReleaseSoundALL(void)
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

SceneSoundManager::~SceneSoundManager(void)
{
	ReleaseSoundALL();
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
