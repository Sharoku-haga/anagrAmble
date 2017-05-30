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

class EventLisner;
class StageDataManager;
class CollisionManager;
class BasePoint;
class StageObjManager;
class StageBackground;

//======================================================================//
//!< ゲームステージクラス
//======================================================================//
class Stage
{

public:
	/** ステージのインデックスIDの構造体 */
	struct INDEX_DATA
	{
		short m_YNum;		//!< Y軸のインデックス
		short m_XNum;		//!< X軸のインデックス
	};

	/** 
	* Constructor
	* @param[in] pStageDataManager StageDataManagerクラスのインスタンスへのポインタ
	*/
	explicit Stage(StageDataManager*	pStageDataManager);

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
		ENTER,			//!< 開始処理
		EXECUTE,		//!< 通常処理
		AREA_CHANGE,	//!< ステージ入れ替え処理
		EXIT,			//!< 終了処理
	};

	sl::ISharokuLibrary*				m_pLibrary;				//!< sl::ISharokuLibraryクラスのインスタンスへのポインタ
	EventLisner*						m_pEventLisiner;		//!< EventLisnerクラスのインスタンスへのポインタ
	StageDataManager*					m_pStageDataManager;	//!< StageDataManagerクラスのインスタンスへのポインタ
	CollisionManager*					m_pCollisionManager;	//!< CollisionManagerクラスのインスタンスへのポインタ
	BasePoint*							m_pBasePoint;			//!< BasePointクラスのインスタンスへのポインタ
	StageObjManager*					m_pStageObjManager;		//!< StageObjManagerクラスのインスタンスへのポインタ
	StageBackground*					m_pBackground;			//!< StageBackgroundクラスのインスタンスへのポインタ
	std::vector<std::vector<short>>		m_CurrentStageData;		//!< 現在のステージデータを格納する二次元配列(vector)
	STATE								m_CurrentState;			//!< 現在のステージの状態

	/** 
	* オブジェクトを作成し、初期位置に配置させる関数
	* @param[in] typeID オブジェクトのID
	* @param[in] yNum	ｙ方向のインデックス
	* @param[in] xNum	x方向のインデックス
	*/
	void CreateObj(int typeID , int yNum, int xNum);

	/** イベントを処理する関数 */
	void HandleEvent(void);

};	// class Stage

}	// namespace ar

#endif	// AR_STAGE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//

