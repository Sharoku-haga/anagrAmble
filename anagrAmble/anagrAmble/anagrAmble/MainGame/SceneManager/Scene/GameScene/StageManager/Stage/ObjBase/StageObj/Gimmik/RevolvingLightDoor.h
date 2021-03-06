﻿//==================================================================================================================================//
//!< @file		RevolvingLightDoor.h
//!< @brief		ar::RevolvingLightDoorクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_REVOLVING_LIGHT_DOOR_H
#define AR_REVOLVING_LIGHT_DOOR_H

#include "../StageObj.h"

namespace ar
{
class LightBlock;

//======================================================================//
//!< ステージオブジェクトである回転する光の扉のクラス
//======================================================================//
class RevolvingLightDoor : public StageObj
{

public:
	/** 
	* Constructor
	* @param[in] pStageDataManager	StageDataManagerクラスのインスタンスへのポインタ
	* @param[in] pCollisionManager	CollisionManagerクラスのインスタンスへのポインタ
	* @param[in] rStageIndexData	ステージインデックスデータ
	* @param[in] texID				テクスチャーのID
	* @param[in] typeID				オブジェクトのタイプID
	*/
	RevolvingLightDoor(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
			, const Stage::INDEX_DATA& rStageIndexData,  int texID,  ObjBase::TYPE_ID typeID);
	
	/** Destructor */
	virtual ~RevolvingLightDoor(void);

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
	std::vector<LightBlock*>			m_pLightBlocks;			//!< LightBlockクラスのインスタンスへのポインタを格納するvector
	ObjBase::TYPE_ID					m_OriginalTypeID;		//!< 元のタイプID

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

	/** 
	* 光の扉が回転する関数
	* 光ブロックを位置を変える
	*/
	void Revolve(void);

};	// class RevolvingLightDoor

}	// namespace ar

#endif	// AR_REVOLVING_LIGHT_DOOR_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
