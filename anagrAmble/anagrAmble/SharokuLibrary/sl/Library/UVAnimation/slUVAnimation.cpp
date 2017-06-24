//==================================================================================================================================//
//!< @file		slUVAnimation.cpp
//!< @brief		sl::UVAnimationクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "slUVAnimation.h"


namespace sl
{

/* Unnamed namespace ------------------------------------------------------------------------------------------ */

namespace
{

const	sl::fRect	InitialUV = { 0.0f, 0.0f, 0.0f, 0.0f };		// 初期化用UV値

}

/* Public Functions ------------------------------------------------------------------------------------------- */

UVAnimation::UVAnimation(int patternCount, bool repeat)
	: m_AnimePatternCount(patternCount)
	, m_CurrentAnimeOrderNum(0)
	, m_CurentDispFlameCount(0)
	, m_CurrentAnimeData(InitialUV, 0)
	, m_Repeat(repeat)
{
	for(int count = 0; count < m_AnimePatternCount; ++count)
	{
		m_AnimeData.emplace_back(InitialUV, 0);
		m_AnimeOrder.emplace_back(count);
	}
}

UVAnimation::~UVAnimation(void)
{
	m_AnimeData.clear();
	m_AnimeOrder.clear();
}

void UVAnimation::CreateAnimeData(int tuCount, int tvCount, const sl::fRect& rBasicUV, int dispFlameCount)
{
	int currentTuCount = 0;			// 現在カウントしているTU方向のカウント数
	int currentTvCount = 0;			// 現在カウントしているTV方向のカウント数

	sl::fRect currentUV;			// ループにしようするUV値いれもの

	float scrollTu = rBasicUV.m_Right - rBasicUV.m_Left;
	float scrollTv = rBasicUV.m_Bottom - rBasicUV.m_Top;

	for(auto& animeData : m_AnimeData)
	{
		if(currentTuCount == tuCount)
		{
			if(currentTvCount == tvCount)
			{	// カウント数に達したら即終了
				return;
			}
			else
			{
				currentTuCount = 0;
				++currentTvCount;
			}
		}

		currentUV.m_Left = rBasicUV.m_Left + scrollTu * currentTuCount;
		currentUV.m_Top = rBasicUV.m_Top + scrollTv *currentTvCount;
		currentUV.m_Right = rBasicUV.m_Right + scrollTu * currentTuCount;
		currentUV.m_Bottom = rBasicUV.m_Bottom + scrollTv *currentTvCount;

		animeData.m_UV = currentUV;
		animeData.m_DispFlameCount = dispFlameCount;

		++currentTuCount;
	}

	// 現在のアニメーデータを更新する
	m_CurrentAnimeData = m_AnimeData[0];
}

bool UVAnimation::Upadate(void)
{
	if(m_CurrentAnimeData.m_DispFlameCount == m_CurentDispFlameCount)
	{
		
		if(m_CurrentAnimeOrderNum >= (m_AnimeOrder.size() - 1))
		{
			if(m_Repeat)
			{
				m_CurrentAnimeOrderNum = m_AnimeOrder[0];
			}
			else
			{
				return false;
			}
		}
		else
		{
			m_CurrentAnimeOrderNum += 1;
		}

		m_CurrentAnimeData = m_AnimeData[m_AnimeOrder[m_CurrentAnimeOrderNum]];
		m_CurentDispFlameCount = 0;
		return true;
	}

	++m_CurentDispFlameCount;

	return false;
}

void UVAnimation::ReturnInitialState(void)
{
	m_CurrentAnimeOrderNum = 0;
	m_CurentDispFlameCount = 0;
	m_CurrentAnimeData = m_AnimeData[0];
}

bool UVAnimation::CheckLastNumCurrnttAnime(void)
{
	if(m_CurrentAnimeOrderNum == (m_AnimeData.size() - 1) )
	{
		return true;
	}
	return false;
}

void UVAnimation::SetAnimeData(int index, const sl::fRect& rUV, int dispFlameCount)
{
	m_AnimeData[index].m_UV = rUV;
	m_AnimeData[index].m_DispFlameCount = dispFlameCount;
}

void UVAnimation::SetAnimeOrder(const std::vector<int>& rAnimeOrder)
{
	m_AnimeOrder.clear();
	std::vector<int>().swap(m_AnimeOrder);
	m_AnimeOrder = rAnimeOrder;
}

}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
