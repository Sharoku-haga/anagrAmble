//==================================================================================================================================//
//!< @file		NormalBlock.h
//!< @brief		ar::NormalBlockBlockクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_NORMAL_BLOCK_H
#define AR_NORMAL_BLOCK_H

#include "../StageObj.h"

namespace ar
{

//======================================================================//
//!< ステージオブジェクトである通常ブロッククラス
//======================================================================//
class NormalBlock : public StageObj
{

public:
	/** 
	* Constructor
	* @param[in] pStageDataManager	StageDataManagerクラスのインスタンスへのポインタ
	* @param[in] pCollisionManager	CollisionManagerクラスのインスタンスへのポインタ
	* @param[in] rStageIndexData	ステージインデックスデータ
	* @param[in] rID				描画関連のID
	*/
	NormalBlock(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager, 
					const Stage::INDEX_DATA& rStageIndexData, const sl::DrawingID& rID);

	/** Destructor */
	virtual ~NormalBlock(void);

	/** 
	* ステージの位置を変更する関数. 
	* @param[in] yIndexNum	y軸方向のインデックス
	* @param[in] xIndexNum  x軸方向のインデックス
	*/
	virtual void ChangeStagePos(short yIndexNum, short xIndexNum)override;

	/**
	* 衝突処理関数
	* @param[in] rData 衝突判定に関連するデータ
	*/
	virtual void ProcessCollision(const CollisionManager::CollisionData& rData)override;

private:
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

};	// class NormalBlock

}	// namespace ar

#endif	// AR_NORMAL_BLOCK_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
