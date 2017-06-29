//==================================================================================================================================//
//!< @file		NumberDrawer.cpp
//!< @brief		NumberDrawerクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "NumberDrawer.h"

namespace ar
{

/* Unnamed namespace ------------------------------------------------------------------------------------------ */

namespace
{

const		int			NumberCount							= 10;									// 番号の数0～9までの10個
const		sl::fRect	GameSceneRectSize					= { -24.f, -24.f, 24.f, 24.f };			// 矩形サイズ
const		sl::fRect	GameClearSceneRectSize				= {-32.0f, -32.0f, 32.0f, 32.0f};			//!< ゲームシーンにおけるRectSize
const		int			TuCount								= 10;									// tu方向のカウント数
const		float		GameSceneTuScrollVal				= 0.03125f;								// ゲームシーンのtuのスクロール値
const		float		GameClearSceneTuScrollVal			= 0.0625f;								// ゲームクリアシーンのtuのスクロール値

}

/* Public Functions ------------------------------------------------------------------------------------------- */

NumberDrawer::NumberDrawer(Scene::ID sceneID, int texID)
	: m_pLibrary(sl::ISharokuLibrary::Instance())
	, m_SceneID(sceneID)
	, m_TexID(texID)
{}

NumberDrawer::~NumberDrawer(void)
{
	for(auto& drawingID : m_NumDrawingID)
	{
		m_pLibrary->ReleaseVertex2D(drawingID.m_VtxID);
	}
}

void NumberDrawer::Initialize(void)
{
	CreateNumDrawingID();
}

void NumberDrawer::DrawNumber(unsigned int drawNum, const sl::SLVECTOR2& rPos)
{
	if(drawNum >= NumberCount)
	{
		return;
	}

	m_pLibrary->Draw2D(m_NumDrawingID[drawNum], rPos);
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void NumberDrawer::CreateNumDrawingID(void)
{
	// 数字分確保
	m_NumDrawingID.resize(NumberCount);

	switch(m_SceneID)
	{
	case Scene::GAME:
		m_CurrentRectSize = GameSceneRectSize;
	{
		int currentTuCount = 0;			// 現在カウントしているTU方向のカウント数

		sl::fRect currentUV;			// ループにしようするUV値いれもの
		sl::fRect startUV = { 0.0f, 0.195f, GameSceneTuScrollVal, 0.292f };		// 開始UV値

		for(int i = 0; i < NumberCount; ++i)
		{
			if(currentTuCount == TuCount)
			{
				return;
			}

			currentUV.m_Left = startUV.m_Left + GameSceneTuScrollVal * currentTuCount;
			currentUV.m_Top = startUV.m_Top;
			currentUV.m_Right = startUV.m_Right + GameSceneTuScrollVal* currentTuCount;
			currentUV.m_Bottom = startUV.m_Bottom;

			m_NumDrawingID[i].m_TexID = m_TexID;
			m_NumDrawingID[i].m_VtxID = m_pLibrary->CreateVertex2D(m_CurrentRectSize, currentUV);

			++currentTuCount;
		}
	}
		break;

	case Scene::GAME_CLEAR:
		m_CurrentRectSize = GameClearSceneRectSize;
	{
		int currentTuCount = 0;			// 現在カウントしているTU方向のカウント数
		int currentTvCount = 0;			// 現在カウントしているTV方向のカウント数

		sl::fRect currentUV;			// ループにしようするUV値いれもの
		sl::fRect startUV = { 0.0f, 0.0f, GameClearSceneTuScrollVal, 0.195f };		// 開始UV値

		for(int i = 0; i < NumberCount; ++i)
		{
			if(currentTuCount == TuCount)
			{
				return;
			}

			currentUV.m_Left = startUV.m_Left + GameClearSceneTuScrollVal * currentTuCount;
			currentUV.m_Top = startUV.m_Top;
			currentUV.m_Right = startUV.m_Right + GameClearSceneTuScrollVal* currentTuCount;
			currentUV.m_Bottom = startUV.m_Bottom;

			m_NumDrawingID[i].m_TexID = m_TexID;
			m_NumDrawingID[i].m_VtxID = m_pLibrary->CreateVertex2D(m_CurrentRectSize, currentUV);

			++currentTuCount;
		}
	}
			break;

	default:
		// do nothing
		break;
	}

}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
