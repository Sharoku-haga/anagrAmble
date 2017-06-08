//==================================================================================================================================//
//!< @file		GameClearScene.h
//!< @brief		ar::GameClearSceneクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_GAME_CLEAR_SCENE_H
#define AR_GAME_CLEAR_SCENE_H

#include "../Scene.h"

namespace ar
{

class GameClearBackground;

//======================================================================//
//!< anagrAmbleにおけるゲームクリアシーンのクラス
//======================================================================//
class GameClearScene : public Scene
{

public:
	/** Constructor */
	GameClearScene(void);

	/** Destructor */
	~GameClearScene(void);

private:
	GameClearBackground*		m_pBackground;		//!< 背景. GameClearBackgroundクラスのインスタンスへのポインタ 

	/** 
	* コントロール関数 
	* @return 次のSceneID
	*/
	virtual Scene::ID Control(void)override;

	/** 描画関数 */
	virtual void Draw(void)override;

};	// class GameClearScene

}	// namespace ar

#endif	// AR_GAME_CLEAR_SCENE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
