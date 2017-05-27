//==================================================================================================================================//
//!< @file		GoalKey.h
//!< @brief		ar::GoalKeyクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_GOAL_KEY_H
#define AR_GOAL_KEY_H

#include "ObjBase.h"

namespace ar
{

//======================================================================//
//!< ゲーム画面のゴールの鍵クラス
//======================================================================//
class GoalKey : public ObjBase
{

public:
	/** Constructor */
	GoalKey(const Stage::INDEX_DATA& rStageIndexData);

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

};	// class GoalKey

}	// namespace ar

#endif	// AR_GOAL_KEY_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
