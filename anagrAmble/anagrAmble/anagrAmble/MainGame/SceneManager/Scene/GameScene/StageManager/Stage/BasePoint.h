//==================================================================================================================================//
//!< @file		BasePoint.h
//!< @brief		ar::BasePointクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_BASE_POINT_H
#define AR_BASE_POINT_H

#include "../SharokuLibrary/sl/sl.h"

namespace ar
{

class EventLisner;
class Player;

//======================================================================//
//!< ベースポイントクラス
//!< 表示する画面範囲の基準となるポイントのこと
//======================================================================//
class BasePoint
{

public:
	/** Constructor */
	BasePoint(void);

	/** Destructor */
	~BasePoint(void);

	/** 
	* 初期化関数. ステージ生成時に呼ぶ関数
	* @param[in] stageWidth ステージの横の長さ
	* @param[in] pPlayer	プレイヤーのクラスのインスタンスへのポインタ
	*/
	void Initialize(float stageWidth, Player* pPlayer);

	/** 
	* Getter. BasePointの位置座標を取得する関数 
	* @return BasePointの位置座標
	*/
	inline const sl::SLVECTOR2& GetPos(void) const{ return m_Pos; }

private:
	sl::SLVECTOR2				m_Pos;						//!< 位置座標
	sl::SLVECTOR2				m_CurrentPlayerPos;			//!< 現在のプレイヤー座標
	sl::SLVECTOR2				m_OldPlayerPos;				//!< 以前のプレイヤー座標
	float						m_StageWidth;				//!< ステージ全体の横の長さ
	EventLisner*				m_pEventLisner;				//!< EventLisnerクラスのインスタンスへのポインタ
	Player*						m_pPlayer;					//!< Playerクラスのインスタンスへのポインタ

	SL_DISALLOW_COPY_AND_ASSIGN(BasePoint);					//!< コピー禁止マクロ

	/** 
	* BasePointの移動を制御する関数
	* プレイヤーが動いたというイベント(playe_move)が発生したときに呼ばれる
	* コールバック関数
	*/
	void Move(void);
	
};	// class BasePoint

}	// namespace ar

#endif	// AR_BASE_POINT_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
