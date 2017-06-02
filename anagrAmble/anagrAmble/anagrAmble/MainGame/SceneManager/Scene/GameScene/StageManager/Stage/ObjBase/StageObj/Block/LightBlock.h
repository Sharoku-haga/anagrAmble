﻿//==================================================================================================================================//
//!< @file		LightBlock.h
//!< @brief		ar::LightBlockクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_LIGHT_BLOCK_H
#define AR_LIGHT_BLOCK_H

#include "../StageObj.h"

namespace ar
{

//======================================================================//
//!< ステージオブジェクトである光ブロックのクラス
//======================================================================//
class LightBlock : public StageObj
{

public:
	/** 
	* Constructor
	* @param[in] pStageDataManager	StageDataManagerクラスのインスタンスへのポインタ
	* @param[in] pCollisionManager	CollisionManagerクラスのインスタンスへのポインタ
	* @param[in] rStageIndexData	ステージインデックスデータ
	* @param[in] texID				テクスチャーのID
	*/
	LightBlock(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
								, const Stage::INDEX_DATA& rStageIndexData, int texID);

	/** Destructor */
	virtual ~LightBlock(void);

	/**
	* 衝突処理関数 
	* @param[in] typeID		衝突したオブジェクトのID
	* @param[in] isDeath	衝突したことで死んだかどうかのフラグ. true→死亡, flase→死んでいない. デフォルトはflase
	*/ 
	virtual void ProcessCollision(int typeID, bool isDeath = false)override;

private:
	/** 
	* 処理実行関数
	* StageObj::Control()内で使用
	*/
	virtual void Run(void)override;

	/** 
	* 描画関数
	* StageObj::Draw()内で使用する
	*/
	virtual void Render(void)override;

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

};	// class LightBlock

}	// namespace ar

#endif	// AR_LIGHT_BLOCK_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
