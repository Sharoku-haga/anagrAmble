//==================================================================================================================================//
//!< @file		StageObj.h
//!< @brief		ar::StageObjクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_STAGE_OBJ_H
#define AR_STAGE_OBJ_H

#include "../ObjBase.h"

namespace ar
{

//======================================================================//
//!< ステージに存在するオブジェクトの基底クラス
//======================================================================//
class StageObj : public ObjBase
{

public:
	/** 
	* Constructor
	* @param[in] pStageDataManager	StageDataManagerクラスのインスタンスへのポインタ
	* @param[in] pCollisionManager	CollisionManagerクラスのインスタンスへのポインタ
	* @param[in] rStageIndexData ステージインデックスデータ
	*/
	StageObj(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager, const Stage::INDEX_DATA& rStageIndexData);

	/** Destructor */
	virtual ~StageObj(void);

	/**
	* 衝突処理関数.純粋仮想関数 
	* @param[in] typeID		衝突したオブジェクトのID
	* @param[in] isDeath	衝突したことで死んだかどうかのフラグ. true→死亡, flase→死んでいない. デフォルトはflase
	*/ 
	virtual void ProcessCollision(int typeID, bool isDeath = false) = 0;

protected:
	/** 
	* 処理実行関数.純粋仮想関数 
	* Control()内で使用
	*/
	virtual void Run(void) = 0;

	/** 
	* 描画関数.純粋仮想関数 
	* Draw()内で使用する
	*/
	virtual void Render(void) = 0;

	/** イベント処理関数.純粋仮想関数  */
	virtual void HandleEvent(void) = 0;

	/** 
	* Constructorの引数で得たインデックスを元に位置座標を計算する関数. 
	* 位置座標は中心座標で計算する. 純粋仮想関数
	*/
	virtual void CalculatePos(void) = 0;

};	// class StageObj

}	// namespace ar

#endif	// AR_STAGE_OBJ_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
