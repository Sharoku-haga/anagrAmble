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

	/** 
	* StageObjを生成する関数 
	* @param[in]  typeID オブジェクトID
	* @param[in]  rIndex インデックスデータ
	*/
	StageObj*	CreateStageObj(int typeID, const Stage::INDEX_DATA rIndex);

private:
	sl::ISharokuLibrary*		m_pLibrary;					//!< sl::ISharokuLibraryクラスのインスタンスへのポインタ
	StageDataManager*			m_pStageDataManager;		//!< StageDataManagerクラスのインスタンスへのポインタ
	CollisionManager*			m_pCollisionManager;		//!< CollisionManagerクラスのインスタンスへのポインタ
	int							m_TexID;					//!< テクスチャーID
	int							m_NormalBlockVtxID;
	int							m_GroundBlockVtxID;
	sl::fRect					m_BlockSize;				//!< ブロック矩形サイズ

	/** 
	* Vertex初期化関数 
	* 使いまわしができるオブジェクトのVertexを作成する
	* Constructorでよんでいる
	*/
	void InitializeVertex(void);

};	// class StageObjFactory

}	// namespace ar 

#endif	// AR_STEGE_OBJ_FACTORY_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
