//==================================================================================================================================//
//!< @file		ThisPlayedTimeText.cpp
//!< @brief		ar::ThisPlayedTimeTextクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "ThisPlayedTimeText.h"
#include "NumberDrawer.h"
#include "ScoreTextDrawer.h"

namespace ar
{

/* Public Functions ------------------------------------------------------------------------------------------- */

ThisPlayedTimeText::ThisPlayedTimeText(unsigned long thisPlayedTime, NumberDrawer* pNumberDrawer, ScoreTextDrawer* pScoreTextDrawer)
	: m_pLibrary(sl::ISharokuLibrary::Instance())
	, m_pNumberDrawer(pNumberDrawer)
	, m_pScoreTextDrawer(pScoreTextDrawer)
	, m_ThisPlayedTime(thisPlayedTime)
{}

ThisPlayedTimeText::~ThisPlayedTimeText(void)
{}

void ThisPlayedTimeText::Initialize(const sl::SLVECTOR2& rDrawStartPos)
{
	m_DrawStartPos = rDrawStartPos;

	// 今回プレイした時間を単位ごとに格納
	m_ThisPlayedTimeNum.resize(TIME_UNIT::UNIT_MAX);
	StoreThisPlayedTimeUnit();

	// 座標の配置
	m_DispTextPos.resize(HIGH_SCORE_DISP_TYPE_ID::TYPE_ID_MAX);
	m_DispRectSize = m_pNumberDrawer->GetCurrentRectSize();

	// タイムテキストだけ先に作成;
	m_DispTextPos[TIME_TEXT] = m_DrawStartPos;

	// 他の表示テキスト作成
	float	posXScrollVal = m_DispRectSize .m_Right - m_DispRectSize .m_Left;
	sl::SLVECTOR2 currentPos;	// 現在の座標 
	sl::SLVECTOR2 startPos;
	startPos.x = m_DrawStartPos.x + posXScrollVal * 2 + (posXScrollVal)/ 2;
	startPos.y = m_DrawStartPos.y;
	
	for(int i = COLON_TEXT ; i < TYPE_ID_MAX; ++i)
	{
		currentPos.x = startPos.x + posXScrollVal * i;
		currentPos.y = startPos.y;
		m_DispTextPos[i] = currentPos;
	}
}

void ThisPlayedTimeText::Draw(void)
{
	// TIMEというテキスト
	{
		m_pScoreTextDrawer->Draw(ScoreTextDrawer::TIME, m_DispTextPos[TIME_TEXT]);
	}

	// コロン
	{
		m_pScoreTextDrawer->Draw(ScoreTextDrawer::COLON, m_DispTextPos[COLON_TEXT]);
	}

	// 10分単位
	{
		m_pNumberDrawer->DrawNumber(m_ThisPlayedTimeNum[TEN_MINUTE_UNITS], m_DispTextPos[TEN_MINUTE_UNITS_NUM]);
	}

	// 1分単位 
	{
		m_pNumberDrawer->DrawNumber(m_ThisPlayedTimeNum[ONE_MINUTE_UNITS], m_DispTextPos[ONE_MINUTE_UNITS_NUM]);

	}

	// 分単位
	{
		m_pScoreTextDrawer->Draw(ScoreTextDrawer::MINUTE_UNITS , m_DispTextPos[MINUTE_UNIT]);
	}

	// 10秒単位
	{
		m_pNumberDrawer->DrawNumber(m_ThisPlayedTimeNum[TEN_SECOND_UNITS], m_DispTextPos[TEN_SECOND_UNITS_NUM]);
	}

	// 1秒単位
	{
		m_pNumberDrawer->DrawNumber(m_ThisPlayedTimeNum[ONE_SECOND_UNITS], m_DispTextPos[ONE_SECOND_UNITS_NUM]);
	}

	// 秒単位
	{
		m_pScoreTextDrawer->Draw(ScoreTextDrawer::SECOND_UNITS , m_DispTextPos[SECOND_UNIT]);
	}
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void ThisPlayedTimeText::StoreThisPlayedTimeUnit(void)
{
	// 10分単位
	//m_DispPlayTimeNum[TEN_MINUTE_UNITS] = static_cast<int>(m_ThisPlayTime / 3600000);
	int tM =  static_cast<int>((m_ThisPlayedTime % 3600000) / 600000);
	m_ThisPlayedTimeNum[TEN_MINUTE_UNITS] = tM;

	// 1分単位
	//m_DispPlayTimeNum[ONE_MINUTE_UNITS] = static_cast<int>((m_ThisPlayTime % 3600000) / 60000);
	int oM = static_cast<int>(((m_ThisPlayedTime % 3600000) % 600000)/ 60000);
	m_ThisPlayedTimeNum[ONE_MINUTE_UNITS] = oM;

	// 10秒単位
	//m_DispPlayTimeNum[TEN_SECOND_UNITS] = static_cast<int>(((m_ThisPlayTime % 3600000) % 60000) / 10000);
	int tS = static_cast<int>(((m_ThisPlayedTime % 3600000) % 60000) / 10000);
	m_ThisPlayedTimeNum[TEN_SECOND_UNITS] = tS;


	// 1秒単位
	//m_DispPlayTimeNum[ONE_SECOND_UNITS] = static_cast<int>((((m_ThisPlayTime % 3600000) % 60000) % 10000) / 1000);
	int oS = static_cast<int>((((m_ThisPlayedTime % 3600000) % 60000) % 10000) / 1000);
	m_ThisPlayedTimeNum[ONE_SECOND_UNITS] = oS;
}

}	// namespace ar

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//

