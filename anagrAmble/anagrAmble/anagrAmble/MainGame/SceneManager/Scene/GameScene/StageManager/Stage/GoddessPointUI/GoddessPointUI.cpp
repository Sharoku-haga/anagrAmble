//==================================================================================================================================//
//!< @file		GoddessPointUI.cpp
//!< @brief		ar::GoddessPointUIクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "GoddessPointUI.h"
#include "../../../GameEventManager/GameEventManager.h"
#include "../../../GameEventManager/EventListener.h"

namespace ar
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const	float		UISize = 96.f;			// UIのサイズ

}

/* Public Functions ------------------------------------------------------------------------------------------- */

GoddessPointUI::GoddessPointUI(int texID, int goddessPointCount)
	: m_pLibrary(sl::ISharokuLibrary::Instance())
	, m_DrawingID({0, texID})
	, m_pEventListener(nullptr)
	, m_GoddessPointCount(goddessPointCount)
{}

GoddessPointUI::~GoddessPointUI(void)
{
	sl::DeleteSafely(&m_pEventListener);
}

void GoddessPointUI::Initialize(void)
{
	// 座標の設定
	sl::SLVECTOR2 startPos = {1680.f, 48.0f};			// 開始座標
	float	scrollPosX = UISize;						// X方向にスクロールする量

	for(int i = 0; i < m_GoddessPointCount; ++i)
	{
		m_Pos.emplace_back((startPos.x + (scrollPosX * i)), startPos.y);
	}

	// Vertexの作成
	sl::fRect rectSize = {-(UISize / 2.0f ), -(UISize / 2.0f ), (UISize / 2.0f ), (UISize / 2.0f ) }; 
	sl::fRect	uv = {0.0f, 0.0f, 1.0f, 1.0f};
	m_DrawingID.m_VtxID = m_pLibrary->CreateVertex2D(rectSize, uv);

	// イベントの登録
	m_pEventListener = new EventListener();

	//  加護消費イベント
	GameEventManager::Instance().RegisterEventType("goddess_point_minus", m_pEventListener);	

}

void GoddessPointUI::Control(void)
{
	HandleEvent();
}

void GoddessPointUI::Draw(void)
{
	for(int i = 0; i < m_GoddessPointCount; ++i)
	{
		m_pLibrary->Draw2D(m_DrawingID, m_Pos[i]);
	}
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void GoddessPointUI::HandleEvent(void)
{
	if(m_pEventListener->EmptyCurrentEvent())
	{
		return;
	}
	else
	{
		const std::deque<std::string>& currentEvents = m_pEventListener->GetEvent();

		std::string eventType;			
		for(auto& gameEvent : currentEvents)
		{
			if(gameEvent == "goddess_point_minus")
			{
				--m_GoddessPointCount;
			}
		}

		m_pEventListener->DelEvent();
	}
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
