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
class Player;

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
	~CollisionManager(void) = default;

	/** 
	* 更新関数
	* 毎フレーム呼ばれて衝突判定の処理を行う関数
	*/
	void Update(void);

	/** 
	 * 衝突判定を行うステージ上のオブジェクトのインスタンスへのポインタを登録する関数 
	 * @param[in] pObj 衝突判定を行いたいObjBaseクラスのインスタンスへのポインタ
	 */
	void SetObjBasePointer(ObjBase* pObj);

	/** 
	 * 衝突判定を行うOFF状態であるスイッチの作動範囲のデータを登録する関数 
	 * @param[in] pObj データを登録したいObjBaseクラスのインスタンス(OFF状態であるスイッチの作動範囲)へのポインタ
	 */
	void SetSwitchOperatingAreaOffData(ObjBase* pArea);

	
	/** 
	 * 衝突判定を行うON状態であるスイッチの作動範囲のデータを登録する関数 
	 * @param[in] pObj データを登録したいObjBaseクラスのインスタンス(ON状態であるスイッチの作動範囲)へのポインタ
	 */
	void SetSwitchOperatingAreaOnData(ObjBase* pArea);

	/** 
	 * 衝突判定を行うプレイヤーオブジェクトを登録する関数 
	 * @param[in] pObj 衝突判定を行いたいObjBaseクラスのインスタンス(プレイヤー)へのポインタ
	 */
	void SetPlayerPointer(Player* pPlayer) { m_pPlayer = pPlayer; }

private:

	/** スイッチの作動範囲の衝突判定を行うときに使用するデータ構造体 */
	struct SwitchOperatingAreaData
	{
		short	m_YIndexNum;		//!< Y軸(縦)のインデックス番号
		short	m_XIndexNum;		//!< X軸(横)のインデックス番号
		int		m_TypeID;			//!< スイッチ作動範囲のID ONかOFFか

		/** Constructor */
		SwitchOperatingAreaData(short	yIndexNum, short xIndexNum, int typeID)
			: m_YIndexNum(yIndexNum)
			, m_XIndexNum(xIndexNum)
			, m_TypeID(typeID)
		{}
	};

	StageDataManager*								m_pStageDataManager;			//!< StageDataManagerクラスのインスタンスへのポインタ
	std::vector<ObjBase*>							m_pStageObj;					//!< 衝突判定を行うObjBase群
	std::vector<SwitchOperatingAreaData>			m_SwitchOperatingAreaOffData;	//!< OFF状態であるスイッチの作動範囲をチェックするときに使用するデータ
	std::vector<SwitchOperatingAreaData>			m_SwitchOperatingAreaOnData;	//!< ON状態であるスイッチの作動範囲をチェックするときに使用するデータ
	Player*											m_pPlayer;						//!< 衝突判定を行うプレイヤー

	/**
	* プレイヤーとの衝突判定を行う関数
	* @param[in]  pObj チェックしたいObjBaseクラスのインスタンスへのポインタ
	*/
	void CheckCollisionPlayer(ObjBase* pObj);

	/**
	* スイッチの作動範囲の衝突判定を行う関数
	* @param[in] rArea チェックを行いたいスイッチの作動範囲のデータ
	*/
	void CheckCollisionSwitchOperatingArea(const SwitchOperatingAreaData& rArea);
	
	/**
	* 矩形の衝突判定を行う関数.
	* @param[in] pObjA 衝突判定を行いたいObjBaseのインスタンスへのポインタ
	* @param[in] pObjB 衝突判定を行いたいObjBaseのインスタンスへのポインタ
	* @return 衝突しているかどうか true→衝突している false→衝突していない
	*/
	bool CheckRectCollision(ObjBase* pObjA, ObjBase* pObjB);

};	// class CollisionManager

}	// namespace ar

#endif	// AR_COLLISION_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
