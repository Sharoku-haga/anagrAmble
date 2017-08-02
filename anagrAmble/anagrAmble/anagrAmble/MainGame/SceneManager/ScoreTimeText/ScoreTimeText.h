//==================================================================================================================================//
//!< @file		ScoreTimeText.h
//!< @brief		ScoreTimeTextクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef SCORE_TIME_TEXT_H
#define SCORE_TIME_TEXT_H

#include <vector>
#include "../SharokuLibrary/sl/sl.h"

namespace ar
{

class NumberDrawer;
class ScoreCharacterDrawer;

//======================================================================//
//!< スコアである時間を表示するテキストクラス
//======================================================================//
class ScoreTimeText
{

public:
	/**
	* Constructor
	* @param[in] pNumberDrawer			NumberDrawerクラスのインスタンスへのポインタ
	* @param[in] pScoreCharacterDrawer	ScoreCharacterDrawerクラスのインスタンスへのポインタ
	*/
	ScoreTimeText(NumberDrawer* pNumberDrawer, ScoreCharacterDrawer* pScoreCharacterDrawer);

	/** Destructor */
	virtual ~ScoreTimeText(void) = default;

	/** 
	* 初期化関数 
	* @param[in] scoreTime		表示したいスコア時間
	* @param[in] rDrawStartPos	描画開始座標
	*/
	void Initialize(unsigned long	scoreTime, const sl::SLVECTOR2& rDrawStartPos);

	/** 描画関数 */
	void Draw(void);

	/** 
	* 表示したいスコア時間をセットする関数 
	* @param[in] scoreTime		表示したいスコア時間 
	*/
	void SetScoreTimeNum(unsigned long	scoreTime);

protected:
	/** 時間単位 */
	enum TIME_UNIT
	{
		ONE_SECOND_UNITS,	//!< 1秒単位
		TEN_SECOND_UNITS,	//!< 10秒単位
		ONE_MINUTE_UNITS,	//!< 1分単位
		TEN_MINUTE_UNITS,	//!< 10分単位
		UNIT_MAX,
	};

	/** 表示するテキストの種類 */
	enum DISP_TEXT_TYPE_ID
	{
		LEAD_TEXT,					//!< 先頭に表示するテキスト.
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
	ScoreCharacterDrawer*			m_pScoreCharacterDrawer;	//!< ScoreCharacterDrawerクラスのインスタンスへのポインタ
	sl::fRect						m_DispRectSize;				//!< 表示の矩形サイズ
	std::vector<sl::SLVECTOR2>		m_DispTextPos;				//!< テキスト表示座標	
	std::vector<int>				m_ScoreTimeNum;				//!< スコア時間の数字.1単位ごとに収納している 

	/** 
	* スコア時間を単位ごとに格納する関数 
	* @param[in] scoreTime		表示したいスコア時間 
	*/
	void StoreScoreTimeUnit(unsigned long	scoreTime);

	/** 先頭テキストを描画する関数 */
	virtual void DrawLeadText(void)  = 0;

};	// class ScoreTimeText

}	// namespace ar

#endif	// SCORE_TIME_TEXT_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
