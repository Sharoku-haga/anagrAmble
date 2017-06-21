//==================================================================================================================================//
//!< @file		slUVAnimationManager.cpp	
//!< @brief		sl::UVAnimationManagerクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "slUVAnimationManager.h"
#include "slUVAnimation.h"
#include "../../Common/slTemplate.h"

namespace sl
{

/* Public Functions ------------------------------------------------------------------------------------------- */

UVAnimationManager::UVAnimationManager(void)
{}

UVAnimationManager::~UVAnimationManager(void)
{
	for(auto& pAnime : m_pUVAnimations)
	{
		for(auto& pUVAnimation : pAnime.second)
		{
			sl::DeleteSafely(&pUVAnimation);
		}
	}
}

int UVAnimationManager::RegisterAnimationID(int vtxID, int patternCount, bool repeat)
{
	int id = m_pUVAnimations.size();

	m_pUVAnimations[vtxID].emplace_back(new UVAnimation(patternCount, repeat));

	return id;
}

void UVAnimationManager::CreateUVAnimationData(int vtxID, int animeID, int tuCount, int tvCount
											, const sl::fRect& rStartUVVal, int dispFlameCount)
{
	m_pUVAnimations[vtxID][animeID]->CreateAnimeData(tuCount, tvCount, rStartUVVal, dispFlameCount);
}

bool UVAnimationManager::UpdateUVAnimation(int vtxID, int animeID)
{
	return (m_pUVAnimations[vtxID][animeID]->Upadate());
}

void  UVAnimationManager::ReturnUVAnimeInitialState(int vtxID, int animeID)
{
	m_pUVAnimations[vtxID][animeID]->ReturnInitialState();
}

bool UVAnimationManager::CheckLastNumCurrnttAnime(int vtxID, int animeID)
{
	return (m_pUVAnimations[vtxID][animeID]->CheckLastNumCurrnttAnime());
}

const sl::fRect& UVAnimationManager::GetCurrentAnimeUV(int vtxID, int animeID)
{
	return (m_pUVAnimations[vtxID][animeID]->GetCurrentAnimeUV());
}

void UVAnimationManager::SetAnimeData(int vtxID, int animeID, int index
										, const sl::fRect& rUV, int dispFlameCount)
{
	m_pUVAnimations[vtxID][animeID]->SetAnimeData(index, rUV, dispFlameCount);
}

void UVAnimationManager::SetAnimeOrder(int vtxID, int animeID, const std::vector<int>& rAnimeOrder)
{
	m_pUVAnimations[vtxID][animeID]->SetAnimeOrder(rAnimeOrder);
}

}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
