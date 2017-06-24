//==================================================================================================================================//
//!< @file		SwitchOperatingArea.h		
//!< @brief		ar::SwitchOperatingAreaクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_SWITCH_OPERATING_AREA_H
#define AR_SWITCH_OPERATING_AREA_H

#include "../ObjBase.h"

namespace ar
{

//======================================================================//
//!< スイッチの作動範囲クラス
//!< ギミックの挙動に変化を与えるスイッチの作動範囲を管理するクラス
//======================================================================//
class SwitchOperatingArea : public ObjBase
{

public:
	/**  
	* Constructor
	* @attention 位置座標はStage::INDEX_DATAから継承クラスごとに設定すること
	* @param[in] pStageDataManager	StageDataManagerクラスのインスタンスへのポインタ
	* @param[in] pCollisionManager	CollisionManagerクラスのインスタンスへのポインタ
	* @param[in] rStageIndexData	ステージインデックスデータ
	* @param[in] pOwner				このオブジェクトのオーナーになるObjbaseクラスのインスタンスへのポインタ
	*/
	SwitchOperatingArea(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
			, const Stage::INDEX_DATA& rStageIndexData, ObjBase* pOwner);

	/** Destructor */
	virtual ~SwitchOperatingArea(void);

	/** 
	* 描画関数
	* 描画処理を行う関数
	*/
	void Draw(void);

	/**
	* ON状態に切り替える関数
	* ObjBase::TypeIDをSWITCH_OPERATING_AREA_ONにする
	*/
	void SwitchOnState(void);

	/**
	* OFF状態に切り替える関数
	* ObjBase::TypeIDをSWITCH_OPERATING_AREA_OFFにする
	*/
	void SwitchOffState(void);

	/**
	* 初期化関数. 
	* このクラスの場合、
	* このクラスのインスタンスへのポインタを持つクラスの初期化関数内でよぶ
	*/
	virtual void Initialize(void)override;


	/** 
	* ステージの位置を変更する関数. 純粋仮想関数
	* @param[in] yIndexNum	y軸方向のインデックス
	* @param[in] xIndexNum  x軸方向のインデックス
	*/
	virtual void ChangeStagePos(short yIndexNum, short xIndexNum)override;

	/**
	* 衝突処理関数.純粋仮想関数 
	* @param[in] rData 衝突判定に関連するデータ
	*/ 
	virtual void ProcessCollision(const CollisionManager::CollisionData& rData)override;

private:
	ObjBase*			m_pOwner;			//!< このオブジェクトのオーナーになるObjbaseクラスのインスタンスへのポインタ

	/** 
	* イベント処理関数.純粋仮想関数 
	* この関数内でEventListenerから受け取ったイベントの処理を行う
	*/
	virtual void HandleEvent(void)override;

	/**
	* 衝突判定に登録する関数. コールバック関数
	* "space_change_end"と"space_change_return_end"のイベントの際によばれる
	*/
	void ResisterCollision(void);

};	// class SwitchOperatingArea

}	// namespace ar

#endif	// AR_SWITCH_OPERATING_AREA_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
