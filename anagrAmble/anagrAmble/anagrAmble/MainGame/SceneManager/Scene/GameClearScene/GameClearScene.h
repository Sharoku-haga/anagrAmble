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

class GameDataManager;
class GameClearBackground;
class NumberDrawer;
class ScoreTextDrawer;
class HighScoreText;
class ThisPlayedTimeText;

//======================================================================//
//!< anagrAmbleにおけるゲームクリアシーンのクラス
//======================================================================//
class GameClearScene : public Scene
{

public:
	/** 
	* Constructor
	* @param[in] pGameDataManager GameDataManagerクラスのインスタンスへのポインタ
	*/
	explicit GameClearScene(GameDataManager*	pGameDataManager);

	/** Destructor */
	~GameClearScene(void);

private:
	/** 現在の処理 */
	enum STATE
	{
		FADE_IN_SCREEN,				//!< 画面フェードイン処理
		DISPLAY_SCREEN,				//!< 画面表示処理
		FADE_OUT_SCREEN,			//!< 画面フェードアウト処理
	};

	GameDataManager*			m_pGameDataManager;		//!< GameDataManagerクラスのインスタンスへのポインタ
	NumberDrawer*				m_pNumberDrawer;		//!< NumberDrawerクラスのインスタンスへのポインタ 
	ScoreTextDrawer*			m_pScoreTextDrawer;		//!< ScoreTextDrawerクラスのインスタンスへのポインタ
	HighScoreText*				m_pHighScoreText;		//!< HighScoreTextクラスのインスタンスへのポインタ
	ThisPlayedTimeText*			m_pThisPlayedTimeText;	//!< ThisPlayedTimeTextクラスのインスタンスへのポインタ
	GameClearBackground*		m_pBackground;			//!< 背景. GameClearBackgroundクラスのインスタンスへのポインタ 
	STATE						m_CurrentState;			//!< 現在のシーンの状態

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
