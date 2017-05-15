//==================================================================================================================================//
//!< @file		SceneManager.h
//!< @brief		SceneManagerクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_SCENE_MANAGER_H
#define AR_SCENE_MANAGER_H

#include "Scene/Scene.h"

namespace ar
{

class GameDataManager;

//======================================================================//
//!< Sceneクラスを管理するクラス
//!< 主にSceneの生成や削除などを行う
//======================================================================//
class SceneManager
{

public:
	/** Constructor */
	SceneManager(void);

	/** Destructor */
	~SceneManager(void);

	/** 
	* アップデート関数
	* @return ゲームが終了しているどうか true→終了 false→継続
	*/
	bool Updtae(void);

private:
	/** SceneManagerの状態 */
	enum STATE
	{
		CREATE_SCENE,					//!< Scene作成
		UPADATE_SCENE,					//!< Scene更新
		DELETE_SCENE,					//!< Scene削除
	};

	STATE				m_CurrentState;			//!< 現在のSceneManagerの状態
	Scene*				m_pScene;				//!< Sceneクラスのインスタンスへのポインタ
	Scene::ID			m_CurrentSceneID;		//!< 現在のSceneID
	Scene::ID			m_NextSceneID;			//!< 次のSceneID
	bool				m_IsGameEnd;			//!< ゲーム終了したかどうか

	GameDataManager*	m_pGameDataManager;		//!< GameDataManagerクラスのインスタンスへのポインタ

};

}	// namespace ar

#endif	// AR_SCENE_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
