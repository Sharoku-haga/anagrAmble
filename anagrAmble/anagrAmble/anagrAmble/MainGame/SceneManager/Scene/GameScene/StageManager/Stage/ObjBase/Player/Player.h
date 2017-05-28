//==================================================================================================================================//
//!< @file		Player.h
//!< @brief		ar::Playerクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_PLAYER_H
#define AR_PLAYER_H

#include "../ObjBase.h"

namespace ar
{

//======================================================================//
//!< ゲームのプレイヤークラス
//======================================================================//
class Player : public ObjBase
{
public:

	/** Constructor */
	Player(const Stage::INDEX_DATA& rStageIndexData);

	/** Destructor */
	~Player();

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

};

}	// namespace ar

#endif	//AR_PLAYER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
