//==================================================================================================================================//
//!< @file		StageTimer.h
//!< @brief		StageTimerクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_STAGE_TIMER_H
#define AR_STAGE_TIMER_H

#include <vector>
#include "../SharokuLibrary/sl/sl.h"

namespace ar
{

class GameDataManager;
class NumberDrawer;
class ScoreTextDrawer;

//======================================================================//
//!< ステージの時間計測、表示を管理するクラス
//======================================================================//
class StageTimer
{

public:
	/** Constructor */
	StageTimer(GameDataManager*	pGameDataManager, NumberDrawer*	 pNumberDrawer, ScoreTextDrawer* pScoreTextDrawer);

	/** Destructor */
	~StageTimer(void);

	/** 初期化関数 */
	void Initialize(void);

	/** コントロール関数 */
	void Control(void);

	/** 描画関数 */
	void Draw(void);

	/** 時間計測開始関数 */
	void StartTimeMeasurement(void);

	/** 時間計測終了関数 */
	void EndTimeMeasurment(void);

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

	/** タイムカウンターに表示する数字と文字の種類*/
	enum TIME_COUNTER_DISP_TYPE_ID
	{
		TIME_TEXT,					//!< [TIME]テキスト
		COLON_TEXT,					//!< コロン
		TEN_MINUTE_UNITS_NUM,		//!< 10分単位の数値
		ONE_MINUTE_UNITS_NUM,		//!< 1分単位の数値
		MINUTE_UNIT,				//!< 分単位(M)
		TEN_SECOND_UNITS_NUM,		//!< 10秒単位の数値
		ONE_SECOND_UNITS_NUM,		//!< 1秒単位の数値
		SECOND_UNIT,				//!< 秒単位(S)
		TYPE_ID_MAX,
	};

	
	GameDataManager*			m_pGameDataManager;			//!< GameDataManagerクラスのインスタンスへのポインタ
	NumberDrawer*				m_pNumberDrawer;			//!< NumberDrawerクラスのインスタンスへのポインタ
	ScoreTextDrawer*			m_pScoreTextDrawer;			//!< ScoreTextDarwerクラスのインスタンスへのポインタ
	sl::fRect					m_DispRectSize;				//!< 表示の矩形サイズ
	std::vector<sl::SLVECTOR2>	m_DispPlayTimePos;			//!< プレイ時間を表示する位置座標
	std::vector<sl::SLVECTOR2>	m_BackBufferPlayTimePos;	//!< バックバッファのプレイ時間の位置座標
	std::vector<int>			m_DispPlayTimeNum;			//!< 表示するプレイ時間の数字.1単位ごとに収納している 
	std::vector<int>			m_BackBufferPlayTimeNum;	//!< 表示するプレイ時間の数字.1単位ごとに収納している 
	unsigned long				m_ThisPlayTime;				//!< 今回のプレイ時間
	unsigned long				m_OldTime;					//!< 前に計測した時間
	unsigned long				m_CurrentTime;				//!< 現在の計測時間
	bool						m_HasBeenMeasured;			//!< 計測しているかどうかのフラグ true→計測している false→計測していない

	/** プレイ時間を単位ごとに格納する関数 */
	void StorePlayTimeUnit(void);


};	// class StageTimer

}	// namespace ar

#endif	// AR_STAGE_TIMER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
