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
	*待機状態に変更する関数
	* 死亡してまだ加護がある場合よぶ関数
	*/
	void ChangeWaitingMotion(void);

	/** 
	* 動作を死亡動作に変更する関数
	* 死亡条件を満たした場合によぶ関数
	*/
	void ChangeDeathMotion(void);

	/**
	* 現材の動作が死亡かどうか確認する関数
	* @return 結果 true→死んでいる false→死んでいない
	*/
	bool IsCurrrentMotionDeath(void);

	/**
	* プレイヤーが右を向いているかどうかを確認する関数
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
	std::vector<int>				m_VtxID;					//!< VertexIDを格納した配列(vector)
	std::vector<int>				m_UVAnimeID;				//!< UVAnimationIDを格納した配列(vector)
	MOTION_ID						m_CurrentMotion;			//!< 現在の動作
	MOTION_ID						m_PreviousMotion;			//!< 前の動作
	sl::SLVECTOR2					m_CurrentMoveVector;		//!< 現在の移動ベクトル. 毎フレーム0に初期化される
	bool							m_IsFacingRight;			//!< 右向きかどうか true→右向き false→右を向いていない(左向き)
	int								m_FlightDurationCount;		//!< 滞空時間カウント数 

	/** 
	* 動作ごとのVertexを作成する関数
	* @param[in] rPlayerRect プレイヤーのRect構造体
	*/
	void InitializeVertex(const sl::fRect& rPlayerRect);

	/** 
	* 死亡動作の制御関数
	* m_CurrentMotionがDeathになったら使用する関数
	*/
	void ControlDeathMotion(void);

	/** 
	* UVアニメーションを処理する関数 
	*/
	void ProcessUVAnimation(void);

};	// class PlayerMotion

}	// namespace ar

#endif	// AR_PLAYER_MOTION_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//