//==================================================================================================================================//
//!< @file		LightRoadBlock.h
//!< @brief		ar::LightRoadBlockクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_LIGHT_ROAD_BLOCK_H
#define AR_LIGHT_ROAD_BLOCK_H

#include <vector>
#include "../StageObj.h"

namespace ar
{

class LightBlock;

//======================================================================//
//!< ゲーム画面の足場(光ブロック)排出ブロックのクラス
//======================================================================//
class LightRoadBlock : public StageObj
{

public:
	/** 
	* Constructor
	* @param[in] pStageDataManager	StageDataManagerクラスのインスタンスへのポインタ
	* @param[in] pCollisionManager	CollisionManagerクラスのインスタンスへのポインタ
	* @param[in] rStageIndexData	ステージインデックスデータ
	* @param[in] texID				テクスチャーのID
	*/
	LightRoadBlock(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
								, const Stage::INDEX_DATA& rStageIndexData, int texID);

	/** Destrucrtor */
	virtual ~LightRoadBlock(void);

	/**
	* 衝突処理関数 
	* @param[in] typeID		衝突したオブジェクトのID
	* @param[in] isDeath	衝突したことで死んだかどうかのフラグ. true→死亡, flase→死んでいない. デフォルトはflase
	*/ 
	virtual void ProcessCollision(int typeID, bool isDeath = false)override;

private:
	std::vector<LightBlock*>			m_pLightBlock;			//!< LightBlockクラスのインスタンスへのポインタを格納するvector

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

	/** 光ブロックを作成する関数 */
	void CreateLightBlock(void);

};	// class LightRoadBlock

}	// namespace ar

#endif	//	AR_LIGHT_ROAD_BLOCK_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
