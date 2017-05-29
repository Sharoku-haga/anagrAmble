//==================================================================================================================================//
//!< @file		StageObjFactory.h
//!< @brief		ar::StageObjFactoryクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_STEGE_OBJ_FACTORY_H
#define AR_STEGE_OBJ_FACTORY_H

#include "../ObjBase/StageObj/StageObj.h"
#include "../SharokuLibrary/sl/sl.h"

namespace ar
{

class CollisionManager;
class StageDataManager;

//======================================================================//
//!< StageObjを生成するクラス
//======================================================================//
class StageObjFactory
{

public:
	/** 
	* Constructor 
	* @param[in] pStageDataManager StageDataManagerクラスのインスタンスへのポインタ
	* @param[in] pColisionManager  CollisionManagerクラスのインスタンスへのポインタ
	* @param[in] texID			   テクスチャーID
	*/
	StageObjFactory(StageDataManager* pStageDataManager, CollisionManager*	pCollisionManager, int texID);

	/** Destructor */
	~StageObjFactory(void);

	/** StageObjを生成する関数 */
	StageObj*	CreateStageObj(const ObjBase::TYPE_ID& rId, const Stage::INDEX_DATA rIndex);

private:
	sl::ISharokuLibrary*		m_pLibrary;					//!< sl::ISharokuLibraryクラスのインスタンスへのポインタ
	StageDataManager*			m_pStageDataManager;		//!< StageDataManagerクラスのインスタンスへのポインタ
	CollisionManager*			m_pCollisionManager;		//!< CollisionManagerクラスのインスタンスへのポインタ
	int							m_TexID;					//!< テクスチャーID
	sl::fRect					m_BlockSize;				//!< ブロック矩形サイズ



};	// class StageObjFactory

}	// namespace ar 

#endif	// AR_STEGE_OBJ_FACTORY_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
