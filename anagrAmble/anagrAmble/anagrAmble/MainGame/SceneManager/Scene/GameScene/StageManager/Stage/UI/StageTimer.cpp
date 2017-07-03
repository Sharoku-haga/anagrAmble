//==================================================================================================================================//
//!< @file		StageTimer.cpp
//!< @brief		StageTimerクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "windows.h"
#include "StageTimer.h"
#include "../../../../../GameDataManager/GameDataManager.h"
#include "../../../../../GameDataManager/NumberDrawer.h"
#include "../../../../../GameDataManager/ScoreTextDrawer.h"

namespace ar
{

/* Unnamed namespace ------------------------------------------------------------------------------------------ */

namespace
{

const float		CounterSpeed = 0.6f;			//!< カウンターのスピード

}

/* Public Functions ------------------------------------------------------------------------------------------- */

StageTimer::StageTimer(GameDataManager*	pGameDataManager, NumberDrawer*	 pNumberDrawer, ScoreTextDrawer* pScoreDrawer)
	: m_pGameDataManager(pGameDataManager)
	, m_pNumberDrawer(pNumberDrawer)
	, m_pScoreTextDrawer(pScoreDrawer)
	, m_ThisPlayTime(0)
	, m_OldTime(0)
	, m_CurrentTime(0)
	, m_HasBeenMeasured(false)
{}

StageTimer::~StageTimer(void)
{}

void StageTimer::Initialize(void)
{
	// 表示座標の初期化
	m_DispPlayTimePos.resize(TYPE_ID_MAX);
	m_BackBufferPlayTimePos.resize(TYPE_ID_MAX);
	m_DispRectSize = m_pNumberDrawer->GetCurrentRectSize();

	// タイムテキストだけ先に作成
	sl::SLVECTOR2 textPos = {((m_DispRectSize .m_Right - m_DispRectSize .m_Left) / 2.0f) + (m_DispRectSize .m_Right - m_DispRectSize .m_Left) 
								, ((m_DispRectSize .m_Bottom - m_DispRectSize.m_Top) / 2.0f)};
	m_DispPlayTimePos[TIME_TEXT] = textPos;


	// 他の表示テキスト作成
	float	posXScrollVal = m_DispRectSize .m_Right - m_DispRectSize .m_Left;
	sl::SLVECTOR2 currentPos;	// 現在の座標 
	sl::SLVECTOR2 startPos;
	startPos.x = posXScrollVal * 2 + (posXScrollVal)/ 2;
	startPos.y = ((m_DispRectSize .m_Bottom - m_DispRectSize.m_Top) / 2.0f);
	
	for(int i = COLON_TEXT ; i < TYPE_ID_MAX; ++i)
	{
		currentPos.x = startPos.x + posXScrollVal * i;
		currentPos.y = startPos.y;
		m_DispPlayTimePos[i] = currentPos;
		m_BackBufferPlayTimePos[i] = currentPos;
	}

	// 0で初期化
	m_DispPlayTimeNum.resize(UNIT_MAX);
	for(auto& timeNum : m_DispPlayTimeNum)
	{
		timeNum = 0;
	}

	m_BackBufferPlayTimeNum.resize(UNIT_MAX);
	for(auto& timeNum : m_BackBufferPlayTimeNum)
	{
		timeNum = 0;
	}
}

void StageTimer::Control(void)
{
	if(RESULT_FAILED(m_HasBeenMeasured))
	{
		return;
	}
	// 時間を計測
	m_CurrentTime = timeGetTime();
	m_ThisPlayTime += (m_CurrentTime - m_OldTime);
	m_OldTime = m_CurrentTime;

	StorePlayTimeUnit();
}

void StageTimer::Draw(void)
{
	// Timeテキスト
	{
		m_pScoreTextDrawer->Draw(ScoreTextDrawer::TIME, m_DispPlayTimePos[TIME_TEXT]);
	}

	// コロン
	{
		m_pScoreTextDrawer->Draw(ScoreTextDrawer::COLON, m_DispPlayTimePos[COLON_TEXT]);
	}

	// 10分単位
	{
		//m_pNumberDrawer->DrawNumber(m_BackBufferPlayTimeNum[TEN_MINUTE_UNITS], m_BackBufferPlayTimePos[TEN_MINUTE_UNITS_NUM]);
		m_pNumberDrawer->DrawNumber(m_DispPlayTimeNum[TEN_MINUTE_UNITS], m_DispPlayTimePos[TEN_MINUTE_UNITS_NUM]);
	}

	// 1分単位 
	{
		//m_pNumberDrawer->DrawNumber(m_BackBufferPlayTimeNum[ONE_MINUTE_UNITS], m_BackBufferPlayTimePos[ONE_MINUTE_UNITS_NUM]);
		m_pNumberDrawer->DrawNumber(m_DispPlayTimeNum[ONE_MINUTE_UNITS], m_DispPlayTimePos[ONE_MINUTE_UNITS_NUM]);
	}

	// 分単位
	{
		m_pScoreTextDrawer->Draw(ScoreTextDrawer::MINUTE_UNITS ,m_DispPlayTimePos[MINUTE_UNIT]);
	}

	// 10秒単位
	{
		//m_pNumberDrawer->DrawNumber(m_BackBufferPlayTimeNum[TEN_SECOND_UNITS], m_BackBufferPlayTimePos[TEN_SECOND_UNITS_NUM]);
		m_pNumberDrawer->DrawNumber(m_DispPlayTimeNum[TEN_SECOND_UNITS], m_DispPlayTimePos[TEN_SECOND_UNITS_NUM]);
	}

	// 1秒単位
	{
		//m_pNumberDrawer->DrawNumber(m_BackBufferPlayTimeNum[ONE_SECOND_UNITS], m_BackBufferPlayTimePos[ONE_SECOND_UNITS_NUM]);
		m_pNumberDrawer->DrawNumber(m_DispPlayTimeNum[ONE_SECOND_UNITS], m_DispPlayTimePos[ONE_SECOND_UNITS_NUM]);
	}

	// 秒単位
	{
		m_pScoreTextDrawer->Draw(ScoreTextDrawer::SECOND_UNITS ,m_DispPlayTimePos[SECOND_UNIT]);
	}
}

void StageTimer::StartTimeMeasurement(void)
{
	m_ThisPlayTime = 0;
	m_CurrentTime = timeGetTime();
	m_OldTime = m_CurrentTime;
	m_HasBeenMeasured = true;
}

void StageTimer::EndTimeMeasurment(void)
{
	m_CurrentTime = timeGetTime();
	m_ThisPlayTime += (m_CurrentTime - m_OldTime);
	m_OldTime = m_CurrentTime;
	m_HasBeenMeasured = false;

	m_pGameDataManager->SetPlayedGameTime(m_ThisPlayTime);
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void StageTimer::StorePlayTimeUnit(void)
{
	// 10分単位
	//m_DispPlayTimeNum[TEN_MINUTE_UNITS] = static_cast<int>(m_ThisPlayTime / 3600000);
	int tM =  static_cast<int>((m_ThisPlayTime % 3600000) / 600000);
	m_DispPlayTimeNum[TEN_MINUTE_UNITS] = tM;

	// 1分単位
	//m_DispPlayTimeNum[ONE_MINUTE_UNITS] = static_cast<int>((m_ThisPlayTime % 3600000) / 60000);
	int oM = static_cast<int>(((m_ThisPlayTime % 3600000) % 600000)/ 60000);
	m_DispPlayTimeNum[ONE_MINUTE_UNITS] = oM;

	// 10秒単位
	//m_DispPlayTimeNum[TEN_SECOND_UNITS] = static_cast<int>(((m_ThisPlayTime % 3600000) % 60000) / 10000);
	int tS = static_cast<int>(((m_ThisPlayTime % 3600000) % 60000) / 10000);
	m_DispPlayTimeNum[TEN_SECOND_UNITS] = tS;


	// 1秒単位
	//m_DispPlayTimeNum[ONE_SECOND_UNITS] = static_cast<int>((((m_ThisPlayTime % 3600000) % 60000) % 10000) / 1000);
	int oS = static_cast<int>((((m_ThisPlayTime % 3600000) % 60000) % 10000) / 1000);
	m_DispPlayTimeNum[ONE_SECOND_UNITS] = oS;
}


}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
