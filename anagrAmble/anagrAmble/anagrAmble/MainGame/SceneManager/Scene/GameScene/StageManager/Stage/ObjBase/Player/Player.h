//==================================================================================================================================//
//!< @file		Player.h
//!< @brief		ar::Playerクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_PLAYER_H
#define AR_PLAYER_H

//#include "PlayerMotion.h"
#include "../ObjBase.h"
#include <vector>

namespace ar
{

class EventListener;
class PlayerMode;
class PlayerMotion;

//======================================================================//
//!< ゲームのプレイヤークラス
//======================================================================//
class Player : public ObjBase
{

public:
	/** 
	* 移動可能な方向の構造体
	* trueならその方向にすすめる, falseならその方向に進めない
	*/
	struct MovableDirection
	{
		bool m_Up;		//!< 上
		bool m_Down;	//!< 下
		bool m_Right;	//!< 右
		bool m_Left;	//!< 左
		MovableDirection(void)
			: m_Up(true)
			, m_Down(true)
			, m_Right(true)
			, m_Left(true)
		{}
	};

	/** プレイヤーの状態 */
	enum STATE
	{				
		WAITING,		//!< 待機している状態
		WALKING,		//!< 歩いている状態
		RUNNING,		//!< 走っている状態
		JUMPING,		//!< ジャンプ
		FALLING,		//!< 落下
		DEATH,			//!< 死亡
		ID_MAX,
	};

	/** 
	* Constructor
	* @param[in] pStageDataManager	StageDataManagerクラスのインスタンスへのポインタ
	* @param[in] pCollisionManager	CollisionManagerクラスのインスタンスへのポインタ
	* @param[in] rStageIndexData	ステージインデックスデータ
	* @param[in] playerTexID		プレイヤーのテクスチャーのID
	*/
	Player(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
			, const Stage::INDEX_DATA& rStageIndexData, int playerTexID);

	/** Destructor */
	virtual ~Player(void);

	/**
	* ステージ開始処理時の関数
	* ステージが開始したらよぶ
	*/
	void StartStage(void);

	/**
	* ステージクリア時の処理関数
	* プレイヤーがステージをクリアしたらよぶ
	*/
	void CompleteStage(void);

	/**
	* 制御関数
	* ステージプレイ中に毎フレームよぶ関数
	*/
	void Control(void);

	/** 描画関数 */
	void Draw(void);

	/**
	* プレイヤーが右を向いているかどうかを取得する関数
	* @return 結果 右向きかどうか true→右向き false→右を向いていない(左向き)
	*/
	bool IsFacingRight(void);

	/**
	* 女神の加護の数を取得する関数
	* @return 女神の加護の数
	*/
	int GetGoddessPointCount(void) { return m_GoddessPointCount; }

	/**
	* 初期化関数. 
	* オブジェクトの生成後(ステージ初期化の時)によぶ
	*/
	virtual void Initialize(void)override;
	
	/** 
	* ステージの位置を変更する関数. 
	* @param[in] yIndexNum	y軸方向のインデックス
	* @param[in] xIndexNum  x軸方向のインデックス
	*/
	virtual void ChangeStagePos(short yIndexNum, short xIndexNum)override;

	/**
	* 衝突処理関数.
	* @param[in] rData 衝突判定に関連するデータ
	*/ 
	virtual void ProcessCollision(const CollisionManager::CollisionData& rData)override;

private:
	std::vector<int>	m_VtxID;					//!< VertexIDを格納したvector
	PlayerMotion*		m_pPlayerMotion;			//!< プレイヤーの動作.  PlayerMotionクラスのインスタンスへのポインタ
	PlayerMode*			m_pPlayerMode;				//!< プレイヤーのモード. PlayerModeクラスのインスタンスへのポインタ
	MovableDirection	m_MovableDirection;			//!< 移動可能方向の構造体
	int					m_GoddessPointCount;		//!< ゲーム中女神の加護の回数。死んだり、時戻しを使用すると数値が減る

	/** 
	* イベント処理関数
	* この関数内でEventListenerから受け取ったイベントの処理を行う
	*/
	virtual void HandleEvent(void)override;

	/** 
	* イベント登録関数 
	* Constructor内で使用する
	*/
	void RegisterEvent(void);

	/**
	* 空間入れ替えの為の準備を行う関数.コールバック関数
	* "space_change_start"のイベントがおこった際によばれる
	*/
	void PrepareSpaceChange(void);

	/**
	* 空間入れ替えの終了した後の処理を行う関数.コールバック関数
	* "space_change_end"のイベントがおこった際によばれる
	*/
	void RunSpaceChangeEndProcessing(void);

	/**
	* 死亡アニメが終了した後の処理を行う関数.コールバック関数
	* "player_death_anime_end"のイベントがおこった際によばれる
	*/
	void RunDeathEndProcessing(void);

};	// class Player

}	// namespace ar

#endif	//AR_PLAYER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
