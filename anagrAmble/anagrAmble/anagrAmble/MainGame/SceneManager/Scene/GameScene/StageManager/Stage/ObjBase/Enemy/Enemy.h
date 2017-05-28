//==================================================================================================================================//
//!< @file		Enemy.h
//!< @brief		ar::Enemyクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_ENEMY_H
#define AR_ENEMY_H

#include "../ObjBase.h"

namespace ar
{

//======================================================================//
//!< ゲーム画面の敵の基底クラス
//======================================================================//
class Enemy : public ObjBase
{

public:
	/** Constructor*/
	Enemy(const Stage::INDEX_DATA& rStageIndexData);

	/** Destructor */
	~Enemy();

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

};	// class Enemy

}	// namespace ar

#endif	// AR_ENEMY_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
