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
	virtual ~StageObj(void) = default;

	/** コントロール関数 */
	void Control(void);

	/** 描画関数 */
	void Draw(void);

	/** 
	* ステージの位置を変更する関数. 純粋仮想関数
	* @param[in] yIndexNum	y軸方向のインデックス
	* @param[in] xIndexNum  x軸方向のインデックス
	*/
	virtual void ChangeStagePos(short yIndexNum, short xIndexNum) = 0;

	/**
	* 衝突処理関数. 純粋仮想関数
	* @param[in] rData 衝突判定に関連するデータ
	*/
	virtual void ProcessCollision(const CollisionManager::CollisionData& rData) = 0;

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

	/** 
	* イベント処理関数.純粋仮想関数 
	* この関数内でEventListenerから受け取ったイベントの処理を行う
	*/
	virtual void HandleEvent(void) = 0;

};	// class StageObj

}	// namespace ar

#endif	// AR_STAGE_OBJ_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
