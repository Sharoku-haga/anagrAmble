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

	/** 
	* Constructor
	* @param[in] pStageDataManager	StageDataManagerクラスのインスタンスへのポインタ
	* @param[in] pCollisionManager	CollisionManagerクラスのインスタンスへのポインタ
	* @param[in] rStageIndexData	ステージインデックスデータ
	*/
	Player(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager, const Stage::INDEX_DATA& rStageIndexData);

	/** Destructor */
	~Player();

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

};

}	// namespace ar

#endif	//AR_PLAYER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
