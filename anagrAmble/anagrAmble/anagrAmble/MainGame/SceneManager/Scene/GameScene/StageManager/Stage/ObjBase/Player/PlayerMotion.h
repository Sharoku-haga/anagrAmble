//==================================================================================================================================//
//!< @file		PlayerMotion.h
//!< @brief		ar::PlayerMotionクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_PLAYER_MOTION_H
#define AR_PLAYER_MOTION_H

#include "Player.h"
#include "../SharokuLibrary/sl/sl.h"

namespace ar
{

//======================================================================//
//!< プレイヤーのモーションクラス
//!< 動作を管理するクラス
//======================================================================//
class PlayerMotion
{

public:
	/** 
	* Constructor 
	* @param[in] rPlayerRect プレイヤーのRect構造体
	*/
	explicit PlayerMotion(const sl::fRect& rPlayerRect);

	/** Destructor */
	~PlayerMotion(void);

	/**
	* コントロール関数
	* @param[in] rMovableDirection 現在移動可能な方向の情報
	* @return 動作によって変動した移動量
	*/
	const sl::SLVECTOR2& Control(const Player::MovableDirection& rMovableDirection);

	/**
	* プレイヤーが右を向いているかどうかを取得する関数
	* @return 結果 右向きかどうか true→右向き false→右を向いていない(左向き)
	*/
	bool IsFacingRight(void) { return m_IsFacingRight; }

	/**
	* 現在の動作VertexIDを取得する関数
	* @return 現在のVtxIDを取得する関数
	*/
	inline int GetCurrentMotionVtxID(void) { return m_VtxID[m_CurrentMotion];  }

private:
	/** プレイヤーの動作ID */
	enum MOTION_ID
	{				
		WAITING,		//!< 待機している
		WALKING,		//!< 歩いている
		RUNNING,		//!< 走っている
		JUMPING,		//!< ジャンプ
		FALLING,		//!< 落下
		DEATH,			//!< 死亡
		ID_MAX,
	};

	sl::ISharokuLibrary*			m_pLibrary;					//!< ライブラリ.sl::ISharokuLibraryクラスのインスタンスへのポインタ
	std::vector<int>				m_VtxID;					//!< VertexIDを格納したvector
	MOTION_ID						m_CurrentMotion;			//!< 現在の動作
	sl::SLVECTOR2					m_CurrentMoveVector;		//!< 現在の移動ベクトル. 毎フレーム0に初期化される
	bool							m_IsFacingRight;			//!< 右向きかどうか true→右向き false→右を向いていない(左向き)
	int								m_FlightDurationCount;		//!< 滞空時間カウント数 

	/** 
	* 動作ごとのVertexを作成する関数
	* @param[in] rPlayerRect プレイヤーのRect構造体
	*/
	void InitializeVertex(const sl::fRect& rPlayerRect);

};	// class PlayerMotion

}	// namespace ar

#endif	// AR_PLAYER_MOTION_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//