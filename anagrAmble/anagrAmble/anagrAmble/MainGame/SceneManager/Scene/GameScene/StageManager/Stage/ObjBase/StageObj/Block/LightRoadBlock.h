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
//!< ステージオブジェクトである足場(光ブロック)排出ブロックのクラス
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
	* @param[in] rData 衝突判定に関連するデータ
	*/
	virtual void ProcessCollision(const CollisionManager::CollisionData& rData)override;

private:
	std::vector<LightBlock*>			m_pLightBlocks;			//!< LightBlockクラスのインスタンスへのポインタを格納するvector

	/** 
	* 処理実行関数
	* StageObj::Control()内で使用
	*/
	virtual void Run(void)override;

	/** 
	* 描画関数
	* StageObj::Draw()内で使用する
	*/
	virtual void Render(void)override;

	/** 
	* イベント処理関数
	* この関数内でEventLisnerから受け取ったイベントの処理を行う
	*/
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
