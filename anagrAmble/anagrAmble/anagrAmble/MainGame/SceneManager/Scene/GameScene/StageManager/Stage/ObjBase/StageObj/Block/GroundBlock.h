//==================================================================================================================================//
//!< @file		GroundBlockBlock.h
//!< @brief		ar::GroundBlockBlockBlockクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_GROUND_BLOCK_H
#define AR_GROUND_BLOCK_H

#include "../StageObj.h"

namespace ar
{

//======================================================================//
//!< ゲーム画面の地面ブロッククラス
//======================================================================//
class GroundBlock : public StageObj
{

public:
	/** 
	* Constructor
	* @param[in] pStageDataManager	StageDataManagerクラスのインスタンスへのポインタ
	* @param[in] pCollisionManager	CollisionManagerクラスのインスタンスへのポインタ
	* @param[in] rStageIndexData	ステージインデックスデータ
	* @param[in] rID				描画関連のID
	*/
	GroundBlock(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
				, const Stage::INDEX_DATA& rStageIndexData, const sl::DrawingID& rID);

	/** Destructor */
	virtual ~GroundBlock(void);

		/**
	* 衝突処理関数 
	* @param[in] typeID		衝突したオブジェクトのID
	* @param[in] isDeath	衝突したことで死んだかどうかのフラグ. true→死亡, flase→死んでいない. デフォルトはflase
	*/ 
	virtual void ProcessCollision(int typeID, bool isDeath = false)override;

private:
	/** 
	* 処理実行関数
	* ObjBase::Constrol()内で使用
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

};	// class GroundBlock

}	// namespace ar

#endif	// AR_GROUND_BLOCK_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
