//==================================================================================================================================//
//!< @file		SceneFactory.h
//!< @brief		SceneFactoryクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_SCENE_FACTORY_H
#define AR_SCENE_FACTORY_H

#include "Scene/Scene.h"

namespace ar
{

class GameDataManager;

//======================================================================//
//!< Sceneクラスの生成を行うクラス
//!< モノステイトパターン
//======================================================================//
class SceneFactory
{

public:

	/**
	* 初期化関数
	* @param[in] pGameDataManager GameDataManagerクラスのインスタンスへのポインタ
	*/
	static void Initialize(GameDataManager*	pGameDataManager);

	/** 
	* シーンを作成する関数
	* @param[in] id		作成したいSceneのID
	* @return 作成したSceneのインスタンスへのポインタ
	*/
	static Scene* CreateScene(Scene::ID id);

private:
	static GameDataManager*		m_pGameDataManager;		//!< GameDataManagerクラスのインスタンスへのポインタ

	/** Constructor */
	SceneFactory(void) = default;

	/** Destructor */
	~SceneFactory(void) = default;
	
};

}	// namespace ar

#endif	// AR_SCENE_FACTORY_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
