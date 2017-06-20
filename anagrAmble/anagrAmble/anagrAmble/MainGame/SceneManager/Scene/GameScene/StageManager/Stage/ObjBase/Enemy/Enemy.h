//==================================================================================================================================//
//!< @file		Enemy.h
//!< @brief		ar::Enemyクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_ENEMY_H
#define AR_ENEMY_H

#include "../ObjBase.h"

namespace ar
{

//======================================================================//
//!< ゲーム画面の敵の基底クラス
//======================================================================//
class Enemy : public ObjBase
{

public:
	/** 
	* Constructor
	* @param[in] pStageDataManager	StageDataManagerクラスのインスタンスへのポインタ
	* @param[in] pCollisionManager	CollisionManagerクラスのインスタンスへのポインタ
	* @param[in] rStageIndexData	ステージインデックスデータ
	*/
	Enemy(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager, const Stage::INDEX_DATA& rStageIndexData);

	/** Destructor */
	~Enemy(void);

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
	* 衝突処理関数
	* @param[in] rData 衝突判定に関連するデータ
	*/
	virtual void ProcessCollision(const CollisionManager::CollisionData& rData)override;

private:
	/** 
	* イベント処理関数
	* この関数内でEventListenerから受け取ったイベントの処理を行う
	*/
	virtual void HandleEvent(void)override;

};	// class Enemy

}	// namespace ar

#endif	// AR_ENEMY_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
