﻿//==================================================================================================================================//
//!< @file		PairOfEmblemBlock.h	
//!< @brief		ar::PairOfEmblemBlockクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_PAIR_OF_EMBLEM_BLOCK_H
#define AR_PAIR_OF_EMBLEM_BLOCK_H

#include "../StageObj.h"

namespace ar
{

//======================================================================//
//!< 2つのブロックで紋章を形成するブロッククラス
//======================================================================//
class PairOfEmblemBlock : public StageObj
{

public:
	/** 
	* Constructor
	* @param[in] pStageDataManager	StageDataManagerクラスのインスタンスへのポインタ
	* @param[in] pCollisionManager	CollisionManagerクラスのインスタンスへのポインタ
	* @param[in] rStageIndexData	ステージインデックスデータ
	* @param[in] texID				テクスチャーのID
	* @param[in] typeID				オブジェクトのタイプID
	*/
	PairOfEmblemBlock(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
			, const Stage::INDEX_DATA& rStageIndexData,  int texID,  ObjBase::TYPE_ID typeID);

	/** Destructor */
	virtual ~PairOfEmblemBlock(void);

	/**
	* 衝突処理関数 
	* @param[in] typeID		衝突したオブジェクトのID
	* @param[in] isDeath	衝突したことで死んだかどうかのフラグ. true→死亡, flase→死んでいない. デフォルトはflase
	*/ 
	virtual void ProcessCollision(int typeID, bool isDeath = false)override;

private:
	sl::fRect		m_TexUV;			//!< Vertexを生成する際に使用するUV値. SearchPairBlock()の結果次第で値変動

	/** 
	* 処理実行関数 
	* ObjBase::Control()内で使用
	*/
	virtual void Run(void)override;

	/** 
	* 描画関数
	* ObjBase::Draw()内で使用する
	*/
	virtual void Render(void)override;

	/** イベント処理関数 */
	virtual void HandleEvent(void)override;

	/** 
	* Constructorの引数で得たインデックスを元に位置座標を計算する関数. 
	* 位置座標は中心座標で計算する. 
	*/
	virtual void CalculatePos(void)override;

	/** 
	* ペアブロックがあるかどうかチェックする関数 
	* ペアブロックが左右正しく並んでいたら、ONのテクスチャーへ、
	* そうじゃないならOFFのテクスチャーになるように処理している
	*/
	void CheckPairBlock(void);

};	// class PairOfEmblemBlock

}	// namespace ar

#endif	// AR_PAIR_OF_EMBLEM_BLOCK_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
