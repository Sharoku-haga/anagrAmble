//==================================================================================================================================//
//!< @file		StageTimer.cpp
//!< @brief		StageTimerクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "windows.h"
#include "StageTimer.h"
#include "../../../../../GameDataManager/GameDataManager.h"
#include "../../../../../NumberDrawer/NumberDrawer.h"
#include "../../../../../ScoreCharacterDrawer/ScoreCharacterDrawer.h"
#include "../../../../../ScoreTimeText/ScoreTimeText.h"
#include "../../../../../ScoreTimeText/ThisScoreTimeText.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

StageTimer::StageTimer(GameDataManager*	pGameDataManager, NumberDrawer*	 pNumberDrawer, ScoreCharacterDrawer* pScoreCharacterDrawer)
	: m_pGameDataManager(pGameDataManager)
	, m_pThisScoreTimeText(new ThisScoreTimeText(pNumberDrawer, pScoreCharacterDrawer))
	, m_ThisScoreTime(0)
	, m_OldTime(0)
	, m_CurrentTime(0)
	, m_HasBeenMeasured(false)
{}

StageTimer::~StageTimer(void)
{
	sl::DeleteSafely(&m_pThisScoreTimeText);
}

void StageTimer::Initialize(void)
{
	sl::SLVECTOR2 drawStartPos = { 72.f, 24.f};
	m_pThisScoreTimeText->Initialize(m_ThisScoreTime, drawStartPos);
}

void StageTimer::Control(void)
{
	if(RESULT_FAILED(m_HasBeenMeasured))
	{
		return;
	}
	// 時間を計測
	m_CurrentTime = timeGetTime();
	m_ThisScoreTime += (m_CurrentTime - m_OldTime);
	m_OldTime = m_CurrentTime;

	// 表示する時間を更新
	m_pThisScoreTimeText->SetScoreTimeNum(m_ThisScoreTime);
}

void StageTimer::Draw(void)
{
	m_pThisScoreTimeText->Draw();
}

void StageTimer::StartTimeMeasurement(void)
{
	m_ThisScoreTime= 0;
	m_CurrentTime = timeGetTime();
	m_OldTime = m_CurrentTime;
	m_pThisScoreTimeText->SetScoreTimeNum(m_ThisScoreTime);
	m_HasBeenMeasured = true;
}

void StageTimer::EndTimeMeasurment(void)
{
	m_CurrentTime = timeGetTime();
	m_ThisScoreTime += (m_CurrentTime - m_OldTime);
	m_OldTime = m_CurrentTime;
	m_pGameDataManager->SetThisScoreTime(m_ThisScoreTime);
	m_HasBeenMeasured = false;
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
