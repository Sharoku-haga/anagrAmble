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
class ScoreCharacterDrawer;
class ScoreTimeText;

//======================================================================//
//!< ステージの時間計測、表示を管理するクラス
//======================================================================//
class StageTimer
{

public:
	/**
	* Constructor
	* @param[in] pGameDataManager		GameDataManagerクラスのインスタンスへのポインタ
	* @param[in] pNumberDrawer			NumberDrawerクラスのインスタンスへのポインタ
	* @param[in] pScoreCharacterDrawer	ScoreCharacterDrawerクラスのインスタンスへのポインタ
	*/
	StageTimer(GameDataManager*	pGameDataManager, NumberDrawer*	 pNumberDrawer, ScoreCharacterDrawer* pScoreCharacterDrawer);

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
	GameDataManager*			m_pGameDataManager;			//!< GameDataManagerクラスのインスタンスへのポインタ
	ScoreTimeText*				m_pThisScoreTimeText;		//!< 現在の時間を表示するテキスト.ScoreTimeTextクラスのインスタンスへのポインタ
	unsigned long				m_ThisScoreTime;			//!< 今回のスコア時間
	unsigned long				m_OldTime;					//!< 前に計測した時間
	unsigned long				m_CurrentTime;				//!< 現在の計測時間
	bool						m_HasBeenMeasured;			//!< 計測しているかどうかのフラグ true→計測している false→計測していない

};	// class StageTimer

}	// namespace ar

#endif	// AR_STAGE_TIMER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
