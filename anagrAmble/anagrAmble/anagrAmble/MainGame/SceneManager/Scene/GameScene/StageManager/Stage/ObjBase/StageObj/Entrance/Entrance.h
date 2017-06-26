﻿//==================================================================================================================================//
//!< @file		Entrance.h
//!< @brief		ar::Entranceクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_ENTRANCE_H
#define AR_ENTRANCE_H

#include "../StageObj.h"

namespace ar
{

//======================================================================//
//!< ステージに存在する入口クラス
//======================================================================//
class Entrance : public StageObj
{

public:
	/** 
	* Constructor
	* @param[in] pStageDataManager	StageDataManagerクラスのインスタンスへのポインタ
	* @param[in] pCollisionManager	CollisionManagerクラスのインスタンスへのポインタ
	* @param[in] rStageIndexData	ステージインデックスデータ
	* @param[in] texID				テクスチャーID
	*/
	Entrance(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
		, const Stage::INDEX_DATA& rStageIndexData, int texID);

	/** Destructor */
	virtual ~Entrance(void);

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
	int		m_UVAnimeID;		//!< UVアニメーションのIDを格納する変数
	bool	m_HasClosed;		//!< 閉まったかどうかのフラグ true→閉まった false→閉まっていない
	bool	m_HasStartedStage;	//!<

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

};	// class Entrance

}	// namespace ar

#endif	// AR_ENTRANCE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
