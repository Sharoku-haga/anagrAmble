//==================================================================================================================================//
//!< @file		Spear.h
//!< @brief		ar::Spearクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_SPEAR_H
#define AR_SPEAR_H

#include "../../StageObj.h"

namespace ar
{

//======================================================================//
//!< ステージオブジェクトであるブロックから飛び出す槍槍クラス
//======================================================================//
class Spear : public StageObj
{

public:
	/** 
	* Constructor
	* @param[in] pStageDataManager	StageDataManagerクラスのインスタンスへのポインタ
	* @param[in] pCollisionManager	CollisionManagerクラスのインスタンスへのポインタ
	* @param[in] rStageIndexData	ステージインデックスデータ
	* @param[in] texID				描画関連のID
	*/
	Spear(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
				, const Stage::INDEX_DATA& rStageIndexData, int texID);

	/** Destructor */
	virtual ~Spear(void);

	/**
	* 槍を動かす関数
	*/
	void Move(void);

	/**
	* 槍の動きを止める関数
	*/
	void Stop(void);

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
	float						m_MovePosYMAXLimit;			//!< y方向への動作のMax値
	float						m_MovePosYMINLimit;			//!< y方向への動作のMin値
	float						m_MoveSpeed;				//!< 動作スピード
	bool						m_HasMoved;					//!< 動いているかどうかのフラグ true→動いている false→動いていない

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

};	// class Spear

}	// namespace ar

#endif	// AR_SPEAR_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
