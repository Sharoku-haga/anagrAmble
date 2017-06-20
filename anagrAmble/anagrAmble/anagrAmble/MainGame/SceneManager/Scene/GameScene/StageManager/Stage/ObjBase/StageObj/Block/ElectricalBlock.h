//==================================================================================================================================//
//!< @file		ElectricalBlock.h
//!< @brief		ar::ElectricalBlockクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_ELECTRICAL_BLOCK_H
#define AR_ELECTRICAL_BLOCK_H

#include "../StageObj.h"

namespace ar
{

//======================================================================//
//!< ステージオブジェクトである通電ブロッククラス
//======================================================================//
class ElectricalBlock : public StageObj
{

public:
	/** 
	* Constructor
	* @param[in] pStageDataManager	StageDataManagerクラスのインスタンスへのポインタ
	* @param[in] pCollisionManager	CollisionManagerクラスのインスタンスへのポインタ
	* @param[in] rStageIndexData	ステージインデックスデータ
	* @param[in] texID				テクスチャーのID
	*/
	ElectricalBlock(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager,
					const Stage::INDEX_DATA& rStageIndexData, int texID);

	/** Destructor */
	virtual ~ElectricalBlock(void);

	/**
	* 初期化関数. 
	* オブジェクトの生成後(ステージ初期化の時)によぶ
	*/
	virtual void Initialize(void)override;

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
	bool			m_IsEnergizedState;					//!< 通電状態かどうかフラグ true→通電している  false→通電していない

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
	* この関数内でEventListenerから受け取ったイベントの処理を行う
	*/
	virtual void HandleEvent(void)override;

};	// class ElectricalBlock

}	// namespace ar

#endif	// AR_ELECTRICAL_BLOCK_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
