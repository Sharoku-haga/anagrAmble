//==================================================================================================================================//
//!< @file		ThisPlayedTimeText.h
//!< @brief		ar::ThisPlayedTimeTextクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_THIS_PLAYED_TIME_TEXT_H
#define AR_THIS_PLAYED_TIME_TEXT_H

#include <vector>
#include "../SharokuLibrary/sl/sl.h"

namespace ar
{

class NumberDrawer;
class ScoreTextDrawer;

//======================================================================//
//!< 今回プレイした時間を表示するテキストクラス
//======================================================================//
class ThisPlayedTimeText
{

public:
	ThisPlayedTimeText(unsigned long thisPlayedTime, NumberDrawer* pNumberDrawer, ScoreTextDrawer* pScoreTextDrawer);

	/** Destructor */
	~ThisPlayedTimeText(void);

	/** 初期化関数 */
	void Initialize(const sl::SLVECTOR2& rDrawStartPos);

	/** 描画関数 */
	void Draw(void);

private:
	/** 時間単位 */
	enum TIME_UNIT
	{
		ONE_SECOND_UNITS,	//!< 1秒単位
		TEN_SECOND_UNITS,	//!< 10秒単位
		ONE_MINUTE_UNITS,	//!< 1分単位
		TEN_MINUTE_UNITS,	//!< 10分単位
		UNIT_MAX,
	};

	/** 今回プレイした時間に表示する数字と文字の種類 */
	enum HIGH_SCORE_DISP_TYPE_ID
	{
		TIME_TEXT,					//!< 「TIME」のテキスト
		COLON_TEXT,					//!< コロンテキスト
		TEN_MINUTE_UNITS_NUM,		//!< 10分単位の数値
		ONE_MINUTE_UNITS_NUM,		//!< 1分単位の数値
		MINUTE_UNIT,				//!< 分単位(M)
		TEN_SECOND_UNITS_NUM,		//!< 10秒単位の数値
		ONE_SECOND_UNITS_NUM,		//!< 1秒単位の数値
		SECOND_UNIT,				//!< 秒単位(S)
		TYPE_ID_MAX,
	};

	sl::ISharokuLibrary*			m_pLibrary;					//!< ライブラリ.sl::ISharokuLibraryクラスのインスタンスへのポインタ
	NumberDrawer*					m_pNumberDrawer;			//!< NumberDrawerクラスのインスタンスへのポインタ
	ScoreTextDrawer*				m_pScoreTextDrawer;			//!< ScoreTextDrawerクラスのインスタンスへのポインタ
	sl::SLVECTOR2					m_DrawStartPos;				//!< 描画開始座標
	sl::fRect						m_DispRectSize;				//!< 表示の矩形サイズ
	std::vector<sl::SLVECTOR2>		m_DispTextPos;				//!< テキスト表示座標	
	std::vector<int>				m_ThisPlayedTimeNum;		//!< 今回プレイした時間の数字.1単位ごとに収納している 
	unsigned long					m_ThisPlayedTime;			//!< 今回プレイした時間

	/** 今回プレイした時間を単位ごとに格納する関数 */
	void StoreThisPlayedTimeUnit(void);

};	// class ThisPlayedTimeText

}	// namespace ar


#endif	// AR_THIS_PLAYED_TIME_TEXT_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//

