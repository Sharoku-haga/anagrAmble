﻿//==================================================================================================================================//
//!< @file		Goal.h
//!< @brief		ar::Goalクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_GOAL_H
#define AR_GOAL_H

#include "ObjBase.h"

namespace ar
{

//======================================================================//
//!< ゲーム画面のゴールクラス
//======================================================================//
class Goal : public ObjBase
{

public:
	/** Constructor */
	Goal(const Stage::INDEX_DATA& rStageIndexData);

	/** Destructor */
	~Goal();

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

};	// class Goal

}	// namespace ar

#endif	// AR_GOAL_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//