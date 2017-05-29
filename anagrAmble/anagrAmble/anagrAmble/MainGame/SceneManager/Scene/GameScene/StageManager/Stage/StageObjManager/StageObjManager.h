//==================================================================================================================================//
//!< @file		StageObjManager.h
//!< @brief		ar::StageObjManagerクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_STAGE_OBJ_MANAGER_H
#define AR_STAGE_OBJ_MANAGER_H

#include <vector>
#include "../ObjBase/StageObj/StageObj.h"
#include "../Stage.h"

namespace ar
{

class CollisionManager;
class StageDataManager;
class StageObjFactory;

//======================================================================//
//!< ゲーム内のオブジェクトを管理するクラス
//======================================================================//
class StageObjManager
{

public:
	/** 
	* Constructor 
	* @param[in] pStageDataManager StageDataManagerクラスのインスタンスへのポインタ
	* @param[in] pColisionManager  CollisionManagerクラスのインスタンスへのポインタ
	* @param[in] texID			   テクスチャーID
	*/
	StageObjManager(StageDataManager* pStageDataManager, CollisionManager*	pColisionManager, int texID);

	/** Destructor */
	~StageObjManager(void);

	/** 
	* StageObjを生成し、登録する関数
	* @param[in] rId		オブジェクトのID
	* @param[in] rIndex		ステージのインデックス番号
	*/
	void CreateStageObj(const ObjBase::TYPE_ID& rId, const Stage::INDEX_DATA rIndex);

	/** コントロール関数 */
	void Control(void);

	/** 描画関数 */
	void Draw(void);

private:
	StageDataManager*			m_pStageDataManager;		//!< StageDataManagerクラスのインスタンスへのポインタ
	CollisionManager*			m_pCollisionManager;		//!< CollisionManagerクラスのインスタンスへのポインタ
	StageObjFactory*			m_pStageObjFactory;			//!< StageFactoryクラスのインスタンスへのポインタ
	std::vector<StageObj*>		m_pStageObj;				//!< StageObjクラスのインスタンスへのポインタを格納するvector 

};	// class StageObjManager

}	// namespace ar

#endif	// AR_STAGE_OBJ_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
