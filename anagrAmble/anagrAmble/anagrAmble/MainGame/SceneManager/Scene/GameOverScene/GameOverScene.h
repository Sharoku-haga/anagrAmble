//==================================================================================================================================//
//!< @file		GameOverScene.h
//!< @brief		ar::GameOverSceneクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_GAME_OVER_SCENE_H
#define AR_GAME_OVER_SCENE_H

#include "../Scene.h"

namespace ar
{

class GameOverBackground;

//======================================================================//
//!< anagrAmbleにおけるゲームオ-バーシーンのクラス
//======================================================================//
class GameOverScene : public Scene
{

public:
	/** Constructor */
	GameOverScene(void);

	/** Destructor */
	~GameOverScene(void);

private:
	GameOverBackground*			m_pBackground;		//!< 背景. GameOverBackgroundクラスのインスタンスへのポインタ 
	/** 
	* コントロール関数 
	* @return 次のSceneID
	*/
	virtual Scene::ID Control(void)override;

	/** 描画関数 */
	virtual void Draw(void)override;

};	// class GameOverScene

}	// namespace ar

#endif	// AR_GAME_OVER_SCENE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
