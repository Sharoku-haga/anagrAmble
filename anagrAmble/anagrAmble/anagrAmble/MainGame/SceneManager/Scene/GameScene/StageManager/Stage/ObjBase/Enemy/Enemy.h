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
	* 衝突処理関数
	* @param[in] rData 衝突判定に関連するデータ
	*/
	virtual void ProcessCollision(const CollisionManager::CollisionData& rData)override;

private:
	/** 
	* イベント処理関数
	* この関数内でEventLisnerから受け取ったイベントの処理を行う
	*/
	virtual void HandleEvent(void)override;

	/** 
	* Constructorの引数で得たインデックスを元に位置座標を計算する関数. 
	* 位置座標は中心座標で計算する. 
	*/
	virtual void CalculatePos(void)override;

};	// class Enemy

}	// namespace ar

#endif	// AR_ENEMY_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
