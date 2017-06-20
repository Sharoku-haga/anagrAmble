//==================================================================================================================================//
//!< @file		SetOfThreeEmblemBlock.h
//!< @brief		ar::SetOfThreeEmblemBlockクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_SET_OF_THREE_EMBLEM_BLOCK_H
#define AR_SET_OF_THREE_EMBLEM_BLOCK_H

#include "../StageObj.h"

namespace ar
{

//======================================================================//
//!< 3つのブロックで紋章を形成するブロッククラス
//======================================================================//
class SetOfThreeEmblemBlock : public StageObj
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
	SetOfThreeEmblemBlock(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
			, const Stage::INDEX_DATA& rStageIndexData,  int texID,  ObjBase::TYPE_ID typeID);

	/** Destructor */
	virtual ~SetOfThreeEmblemBlock(void);

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
	sl::fRect		m_TexUV;			//!< Vertexを生成する際に使用するUV値. SearchSetofThreeBlock()の結果次第で値変動

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
	* セットになるブロック2つがあるかどうかチェックする関数
	* 2つのブロックが順番どおりに並んでいたら、ONのテクスチャーへ、
	* そうじゃないならOFFのテクスチャーになるように処理している
	*/
	void CheckSetofThreeBlock(void);

};	// class SetOfThreeEmblemBlock

}	// namespace ar

#endif	// AR_SET_OF_THREE_EMBLEM_BLOCK_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//

