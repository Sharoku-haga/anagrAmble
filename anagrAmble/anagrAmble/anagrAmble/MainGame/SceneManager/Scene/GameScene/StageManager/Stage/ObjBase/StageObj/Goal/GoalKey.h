//==================================================================================================================================//
//!< @file		GoalKey.h
//!< @brief		ar::GoalKeyクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_GOAL_KEY_H
#define AR_GOAL_KEY_H

#include "../StageObj.h"

namespace ar
{

//======================================================================//
//!< ステージのゴールの鍵クラス
//======================================================================//
class GoalKey : public StageObj
{

public:
	/** Constructor */
	GoalKey(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager, const Stage::INDEX_DATA& rStageIndexData);

	/** Destructor */
	~GoalKey();

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

};	// class GoalKey

}	// namespace ar

#endif	// AR_GOAL_KEY_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
