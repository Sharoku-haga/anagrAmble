//==================================================================================================================================//
//!< @file		Scene.h
//!< @brief		ar::Sceneクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_SCENE_H
#define AR_SCENE_H

namespace sl
{

class ISharokuLibrary;

}	// namespace sl

namespace ar
{

//======================================================================//
//!< ゲームにおけるシーンの基底クラス
//!< 抽象クラス
//======================================================================//
class Scene
{

public:
	/** SceneのID */
	enum ID
	{
		LOGO,				//!< ロゴシーン
		TITLE,				//!< タイトルシーン
		GAME,				//!< ゲームシーン
		GAME_CLEAR,			//!< ゲームクリアシーン
		CREDITS_ROLL,		//!< エンドロールシーン
		END,				//!< ゲーム終了
	};

	/** Constructor */
	Scene(void);

	/** Destructor */
	virtual ~Scene(void);

	/** 
	* 更新関数
	* @return 次のSceneID
	*/
	Scene::ID Update(void);

protected:
	sl::ISharokuLibrary*	m_pLibrary;			//!< sl::ISharokuLibraryクラスのインスタンスへのポインタ
	Scene::ID				m_NextSceneID;		//!< 次のシーンID

	/** 
	* コントロール関数 
	* @return 次のSceneID
	*/
	virtual Scene::ID Control(void) = 0;

	/** 描画関数 */
	virtual void Draw(void) = 0;

};	// class Scene

}	// namespace ar

#endif	// AR_SCENE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
