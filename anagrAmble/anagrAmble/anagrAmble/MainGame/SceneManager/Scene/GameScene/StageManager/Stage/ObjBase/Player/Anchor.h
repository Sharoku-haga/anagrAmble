//==================================================================================================================================//
//!< @file		Anchor.h
//!< @brief		ar::Anchorクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_ANCHOR_H
#define AR_ANCHOR_H

#include "../ObjBase.h"

namespace ar
{

class Player;

//======================================================================//
//!< プレイヤーが使用するアンカーのクラス
//!< 同じクラス2つ１組で運用するクラス
//======================================================================//
class Anchor : public ObjBase
{

public:
	/** 
	* Constructor
	* @param[in] pStageDataManager	StageDataManagerクラスのインスタンスへのポインタ
	* @param[in] pCollisionManager	CollisionManagerクラスのインスタンスへのポインタ
	* @param[in] rStageIndexData	ステージインデックスデータ
	* @param[in] pPlayer			オ-ナーとなるPlayerクラスのインスタンスへのポインタ
	* @param[in] texID				テクスチャーID
	*/
	Anchor(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
			, const Stage::INDEX_DATA& rStageIndexData, Player* pPlayer, int texID);

	/** Destructor */
	virtual ~Anchor(void);

	/**
	* ペアとなるAnchorクラスのインスタンスへのポインタをセットする関数
	* @attention ペアになるAnchorクラスのインスタンスを生成したら、ペアのクラスとともに必ずよぶこと
	* @param[in] pPairAnchor ペアになるAnchorクラスのインスタンスへのポインタ
	*/
	void SetPairAnchorPointer(Anchor* pPairAnchor) { m_pPairAnchor = pPairAnchor; }

	/**
	* コントロール関数
	* 主にイベント処理と衝突判定登録を行う
	*/
	void Control(void);

	/**
	* 描画関数
	* 設置モード時と設置後のアンカーを描画する処理を行う
	*/
	void Draw(void);

	/**
	* ステージ内にアンカーをおけるかどうか確認する関数
	* @return 結果 true→置ける false→置けない
	*/
	bool CanPlaceStage(void);

	/**
	* 位置座標をステージ内に置く関数
	* 使用タイミングとしては、アンカーセットボタンが押されたときのみ
	*/
	void PlacePosStage(void);

	/**
	* 位置座標をプレイヤーの前に置く関数
	* 使用タイミングとしては、エリア入れ替え後、プレイヤーに回収されたときなど
	*/
	void PlacePosPlayerFront(void);

	/**
	* ステージ内に置かれたかどうか確認する関数
	* @return 確認結果 true→置かれている false→置かれていない
	*/
	bool GetHasPlacePosStage(void) { return m_HasPlacePosStage; }

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
	Player*		m_pPlayer;					//!< オーナーとなるPlayerクラスのインスタンスへのポインタ
	Anchor*		m_pPairAnchor;				//!< ペアとなるAnchorクラスのインスタンスへのポインタ
	bool		m_HasPlacePosStage;			//!< 位置座標がステージに置かれたかどうか. true→置かれている false→置かれていない
	bool		m_HasCollidedWithPlayer;	//!< プレイヤー衝突したかどうか. true→衝突している false→衝突していない

	/** 
	* イベント処理関数
	* この関数内でEventLisnerから受け取ったイベントの処理を行う
	*/
	virtual void HandleEvent(void)override;

	/**
	* 位置を調整するコールバック関数
	* 衝突処理により、プレイヤーの位置が変更に使用する
	*/
	void AdjustPos(void);

};	// class Anchor

}	// namespace ar

#endif	// AR_ANCHOR_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
