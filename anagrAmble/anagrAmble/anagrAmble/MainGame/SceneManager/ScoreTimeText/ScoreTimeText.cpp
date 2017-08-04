//==================================================================================================================================//
//!< @file		ScoreTimeText.cpp
//!< @brief		ScoreTimeTextクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "ScoreTimeText.h"
#include "../NumberDrawer/NumberDrawer.h"
#include "../ScoreCharacterDrawer/ScoreCharacterDrawer.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

ScoreTimeText::ScoreTimeText(NumberDrawer* pNumberDrawer, ScoreCharacterDrawer* pScoreCharacterDrawer)
	: m_pNumberDrawer(pNumberDrawer)
	, m_pScoreCharacterDrawer(pScoreCharacterDrawer)
{}

void ScoreTimeText::Initialize(unsigned long	scoreTime, const sl::SLVECTOR2& rDrawStartPos)
{
	// 今回プレイした時間を単位ごとに格納
	m_ScoreTimeNum.resize(TIME_UNIT::UNIT_MAX);
	StoreScoreTimeUnit(scoreTime);

	// 座標の配置
	m_DispTextPos.resize(DISP_TEXT_TYPE_ID::TYPE_ID_MAX);
	m_DispRectSize = m_pNumberDrawer->GetRectSize();

	// 先頭テキストを作成;
	m_DispTextPos[LEAD_TEXT] = rDrawStartPos;

	// 他の表示テキスト作成
	float	posXScrollVal = m_DispRectSize .m_Right - m_DispRectSize .m_Left;
	sl::SLVECTOR2 currentPos;	// 現在の座標 
	sl::SLVECTOR2 startPos;
	startPos.x = rDrawStartPos.x + posXScrollVal * 2 + (posXScrollVal)/ 2;
	startPos.y = rDrawStartPos.y;
	
	for(int i = COLON_TEXT ; i < TYPE_ID_MAX; ++i)
	{
		currentPos.x = startPos.x + posXScrollVal * i;
		currentPos.y = startPos.y;
		m_DispTextPos[i] = currentPos;
	}
}

void ScoreTimeText::Draw(void)
{
	// 先頭テキスト
	{
		DrawLeadText();
	}

	// コロン
	{
		m_pScoreCharacterDrawer->Draw(ScoreCharacterDrawer::COLON, m_DispTextPos[COLON_TEXT]);
	}

	// 10分単位
	{
		m_pNumberDrawer->DrawNumber(m_ScoreTimeNum[TEN_MINUTE_UNITS], m_DispTextPos[TEN_MINUTE_UNITS_NUM]);
	}

	// 1分単位 
	{
		m_pNumberDrawer->DrawNumber(m_ScoreTimeNum[ONE_MINUTE_UNITS], m_DispTextPos[ONE_MINUTE_UNITS_NUM]);
	}

	// 分単位
	{
		m_pScoreCharacterDrawer->Draw(ScoreCharacterDrawer::MINUTE_UNITS , m_DispTextPos[MINUTE_UNIT]);
	}

	// 10秒単位
	{
		m_pNumberDrawer->DrawNumber(m_ScoreTimeNum[TEN_SECOND_UNITS], m_DispTextPos[TEN_SECOND_UNITS_NUM]);
	}

	// 1秒単位
	{
		m_pNumberDrawer->DrawNumber(m_ScoreTimeNum[ONE_SECOND_UNITS], m_DispTextPos[ONE_SECOND_UNITS_NUM]);
	}

	// 秒単位
	{
		m_pScoreCharacterDrawer->Draw(ScoreCharacterDrawer::SECOND_UNITS , m_DispTextPos[SECOND_UNIT]);
	}
}

void ScoreTimeText::SetScoreTimeNum(unsigned long	scoreTime)
{
	StoreScoreTimeUnit(scoreTime);
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void ScoreTimeText::StoreScoreTimeUnit(unsigned long	scoreTime)
{
	// 10分単位
	m_ScoreTimeNum[TEN_MINUTE_UNITS] =  static_cast<int>((scoreTime % 3600000) / 600000);

	// 1分単位
	m_ScoreTimeNum[ONE_MINUTE_UNITS] = static_cast<int>(((scoreTime % 3600000) % 600000)/ 60000);

	// 10秒単位
	m_ScoreTimeNum[TEN_SECOND_UNITS] = static_cast<int>(((scoreTime % 3600000) % 60000) / 10000);

	// 1秒単位
	m_ScoreTimeNum[ONE_SECOND_UNITS] = static_cast<int>((((scoreTime % 3600000) % 60000) % 10000) / 1000);
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
