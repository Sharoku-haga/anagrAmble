//==================================================================================================================================//
//!< @file		GameScene.h
//!< @brief		ar::GameSceneクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_GAME_SCENE_H
#define AR_GAME_SCENE_H

#include "../Scene.h"

namespace ar
{

class GameDataManager;

//======================================================================//
//!< anagrAmbleにおけるゲームシーンのクラス
//======================================================================//
class GameScene : public Scene
{

public:
	/** 
	* Constructor 
	* @param[in] pGameDataManager GameDataManagerクラスのインスタンスへのポインタ
	*/
	explicit GameScene(GameDataManager* pGameDataManager);

	/** Destructor */
	virtual ~GameScene(void);

private:
	GameDataManager*		m_pGameDataManager;		//!< GameDataManagerクラスのインスタンスへのポインタ

	/** 
	* コントロール関数 
	* @return 次のSceneID
	*/
	virtual Scene::ID Control(void)override;

	/** 描画関数 */
	virtual void Draw(void)override;

};	// class GameScene

}	// namespace ar

#endif	// AR_GAME_SCENE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
