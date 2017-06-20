//==================================================================================================================================//
//!< @file		LightDoor.h
//!< @brief		ar::LightDoorクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_LIGHT_DOOR_H
#define AR_LIGHT_DOOR_H

#include "../StageObj.h"

namespace ar
{

class LightBlock;

//======================================================================//
//!< ステージオブジェクトである光の扉クラス
//======================================================================//
class LightDoor : public StageObj
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
	LightDoor(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
			, const Stage::INDEX_DATA& rStageIndexData,  int texID,  ObjBase::TYPE_ID typeID);

	/** Destructor */
	virtual ~LightDoor(void);

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
	bool								m_HasOpened;			//!< 扉が開いているかどうか true→開いている false→開いていない

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
	* 扉を開ける関数
	* 光ブロックを収納する関数
	*/
	void Open(void);

	/**
	* 扉を閉じる関数
	* 光ブロックを展開する関数
	*/
	void Close(void);

};	// class LightDoor

}	// namespace ar

#endif	// AR_LIGHT_DOOR_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
