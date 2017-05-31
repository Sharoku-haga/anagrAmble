//==================================================================================================================================//
//!< @file		Goal.h
//!< @brief		ar::Goalクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_GOAL_H
#define AR_GOAL_H

#include "../StageObj.h"

namespace ar
{

//======================================================================//
//!< ゲーム画面のゴールクラス
//======================================================================//
class Goal : public StageObj
{

public:
	/** Constructor */
	Goal(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager, const Stage::INDEX_DATA& rStageIndexData);

	/** Destructor */
	~Goal();

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


};	// class Goal

}	// namespace ar

#endif	// AR_GOAL_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
