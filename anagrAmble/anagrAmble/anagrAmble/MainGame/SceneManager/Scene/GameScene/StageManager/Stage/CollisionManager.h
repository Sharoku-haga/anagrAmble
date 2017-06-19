//==================================================================================================================================//
//!< @file		CollisionManager.h
//!< @brief		ar::CollisionManagerクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_COLLISION_MANAGER_H
#define AR_COLLISION_MANAGER_H

#include <vector>
#include "../SharokuLibrary/sl/sl.h"

namespace ar
{

class StageDataManager;
class ObjBase;

//======================================================================//
//!< 衝突判定などを管理するクラス
//======================================================================//
class CollisionManager
{

public:
	/** 
	* 衝突したときに衝突処理関数にわたされるデータ
	*/
	struct CollisionData
	{
		int					m_ObjType;		//!< 衝突したオブジェクトのタイプ
		sl::SLVECTOR2		m_ObjPos;		//!< 衝突したオブジェクトの座標
		sl::fRect			m_ObjRect;		//!< 衝突したオブジェクトのRect構造体
	};

	/** 
	* Constructor
	* @param[in] pStageDataManager StageDataManagerクラスのインスタンスへのポインタ
	*/
	explicit CollisionManager(StageDataManager*	pStageDataManager);

	/** Destructor */
	~CollisionManager(void);

	/** 
	* 更新関数
	* 毎フレーム呼ばれて衝突判定の処理を行う関数
	*/
	void UpDate(void);

	/** 
	 * 衝突判定を行うステージ上のオブジェクトのインスタンスへのポインタを登録する関数 
	 * @param[in] pObj 衝突判定を行いたいObjBaseクラスのインスタンスへのポインタ
	 */
	void SetObjBasePointer(ObjBase* pObj);

	/** 
	 * 衝突判定を行うスイッチの作動範囲オブジェクトを登録する関数 
	 * @param[in] pObj 衝突判定を行いたいObjBaseクラスのインスタンス(スイッチの作動範囲)へのポインタ
	 */
	void SetSwitchOperatingAreaPointer(ObjBase* pArea);

	/** 
	 * 衝突判定を行うプレイヤーオブジェクトを登録する関数 
	 * @param[in] pObj 衝突判定を行いたいObjBaseクラスのインスタンス(プレイヤー)へのポインタ
	 */
	void SetPlayerPointer(ObjBase* pPlayer) { m_pPlayer = pPlayer; }

private:
	StageDataManager*			m_pStageDataManager;	//!< StageDataManagerクラスのインスタンスへのポインタ
	std::vector<ObjBase*>		m_pStageObj;			//!< 衝突判定を行うObjBase群
	std::vector<ObjBase*>		m_pSwitchOperatingArea;	//!< スイッチの作動範囲(SwitchOperatingAreaクラス)オブジェクト
	ObjBase*					m_pPlayer;				//!< 衝突判定を行うプレイヤー

	/**
	* プレイヤーとの衝突判定を行う関数
	* @param[in]  pObj チェックしたいObjBaseクラスのインスタンスへのポインタ
	*/
	void CheckCollisionPlayer(ObjBase* pObj);

	/**
	* スイッチの作動範囲の衝突判定を行う関数
	* @param[in] pArea チェックを行いたいスイッチの作動範囲(ObjBaseクラス)のインスタンスへのポインタ
	*/
	void CheckCollisionSwitchOperatingArea(ObjBase* pArea);

	/**
	* 矩形で衝突判定を行う関数.
	* @param[in] pObjA 衝突判定を行いたいObjBaseのインスタンスへのポインタ
	* @param[in] pObjB 衝突判定を行いたいObjBaseのインスタンスへのポインタ
	* @return 衝突しているかどうか true→衝突している false→衝突していない
	*/
	bool CheckCollisionRect(ObjBase* pObjA, ObjBase* pObjB);

};	// class CollisionManager

}	// namespace ar

#endif	// AR_COLLISION_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
