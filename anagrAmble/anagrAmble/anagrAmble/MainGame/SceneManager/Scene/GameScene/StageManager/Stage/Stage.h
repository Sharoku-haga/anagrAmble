﻿//==================================================================================================================================//
//!< @file		Stage.h
//!< @brief		ar::Stageクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_STAGE_H
#define AR_STAGE_H

#include "../SharokuLibrary/sl/sl.h"
#include <vector>

namespace ar
{

class GameDataManager;
class EventListener;
class StageDataManager;
class CollisionManager;
class BasePoint;
class Player;
class StageObjManager;
class StageBackground;
class GoddessPointUI;
class NumberDrawer;
class ScoreCharacterDrawer;
class StageTimer;
class ScoreTimeText;

//======================================================================//
//!< ゲームステージクラス
//======================================================================//
class Stage
{

public:
	/** ステージのインデックスIDの構造体 */
	struct INDEX_DATA
	{
		short m_YIndexNum;		//!< Y軸(縦)のインデックス番号
		short m_XIndexNum;		//!< X軸(横)のインデックス番号
	};

	/** 
	* Constructor
	* @param[in] pGameDataManager	GameDataManagerクラスのインスタンスへのポインタ
	* @param[in] pStageDataManager	StageDataManagerクラスのインスタンスへのポインタ
	*/
	Stage(GameDataManager* pGameDataManager, StageDataManager*	pStageDataManager);

	/** Destructor */
	~Stage(void);

	/** 
	* 初期化関数.
	* ステージのオブジェクトの初期配置などの処理を行う
	*/
	void Initialize(void);

	/** コントロール関数 */
	void Control(void);

	/** 描画関数 */
	void Draw(void);

private:
	/** ステージの状態 */
	enum STATE 
	{
		ENTER,				//!< 開始処理
		EXECUTE,			//!< 通常処理
		STAGE_SPACE_CHANGE,	//!< ステージ入れ替え処理
		STAGE_SPACE_RETURN,	//!< ステージを元に戻す処理
		PLAYER_RESPAWN,		//!< プレイヤーを復活させる処理
		EXIT,				//!< 終了処理
	};

	sl::ISharokuLibrary*				m_pLibrary;					//!< sl::ISharokuLibraryクラスのインスタンスへのポインタ
	GameDataManager*					m_pGameDataManager;			//!< GameDataManagerクラスのインスタンスへのポインタ
	EventListener*						m_pEventListener;			//!< EventListenerクラスのインスタンスへのポインタ
	StageDataManager*					m_pStageDataManager;		//!< StageDataManagerクラスのインスタンスへのポインタ
	CollisionManager*					m_pCollisionManager;		//!< CollisionManagerクラスのインスタンスへのポインタ
	BasePoint*							m_pBasePoint;				//!< BasePointクラスのインスタンスへのポインタ
	Player*								m_pPlayer;					//!< Playerクラスのインスタンスへのポインタ
	StageObjManager*					m_pStageObjManager;			//!< StageObjManagerクラスのインスタンスへのポインタ
	StageBackground*					m_pBackground;				//!< StageBackgroundクラスのインスタンスへのポインタ
	GoddessPointUI*						m_pGoddessPointUI;			//!< GoddessPointUIクラスのインスタンスへのポインタ
	NumberDrawer*						m_pNumberDrawer;			//!< NumberDrawerクラスのインスタンスへのポインタ
	ScoreCharacterDrawer*				m_pScoreCharacterDrawer;	//!< ScoreCharacterDrawerクラスのインスタンスへのポインタ
	StageTimer*							m_pStageTimer;				//!< StageTimerクラスのインスタンスへのポインタ
	ScoreTimeText*						m_pHighScoreText;			//!< ハイスコアを表示するテキスト.ScoreTimeTextクラスのインスタンスへのポインタ
	std::vector<std::vector<short>>		m_CurrentStageData;			//!< 現在のステージデータを格納する二次元配列(vector)
	STATE								m_CurrentState;				//!< 現在のステージの状態
	int									m_PlayerTexID;				//!< プレイヤーのテクスチャーID
	int									m_StageObjTexID;			//!< ステージオブジェクトのテクチャーID

	/** 
	* オブジェクトを作成し、初期位置に配置させる関数
	* @param[in] typeID		オブジェクトのID
	* @param[in] yIndexNum	y方向のインデックス番号
	* @param[in] xIndexNum	x方向のインデックス番号
	*/
	void CreateObj(int typeID , int yIndexNum, int xIndexNum);

	/** イベントを処理する関数 */
	void HandleEvent(void);

	/**
	* 空間入れ替えの為の準備を行う関数.コールバック関数
	* "space_change_start"のイベントがおこった際によばれる
	*/
	void PrepareSpaceChange(void);

};	// class Stage

}	// namespace ar

#endif	// AR_STAGE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//

