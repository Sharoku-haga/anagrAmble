//==================================================================================================================================//
//!< @file		Lever.h
//!< @brief		ar::Leverクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_LEVER_H
#define AR_LEVER_H

#include "../StageObj.h"

namespace ar
{

//======================================================================//
//!< ゲーム画面のレバー(スイッチ)のクラス
//======================================================================//
class Lever : public StageObj
{

public:
	/** 
	* Constructor
	* @param[in] pStageDataManager	StageDataManagerクラスのインスタンスへのポインタ
	* @param[in] pCollisionManager	CollisionManagerクラスのインスタンスへのポインタ
	* @param[in] rStageIndexData	ステージインデックスデータ
	* @param[in] texID				テクスチャーのID
	*/
	Lever(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
								, const Stage::INDEX_DATA& rStageIndexData, int texID);

	/** Constructor */
	virtual ~Lever(void);

	/**
	* 衝突処理関数 
	* @param[in] typeID		衝突したオブジェクトのID
	* @param[in] isDeath	衝突したことで死んだかどうかのフラグ. true→死亡, flase→死んでいない. デフォルトはflase
	*/ 
	virtual void ProcessCollision(int typeID, bool isDeath = false)override;

private:
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

};	// class Lever

}	// namespace ar

#endif	// AR_LEVER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
