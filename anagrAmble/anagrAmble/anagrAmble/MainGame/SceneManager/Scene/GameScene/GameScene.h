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
class GamePauseMenu;
class GameEventManager;
class EventListener;
class StageManager;

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
	/** GameScene状態 */
	enum STATE
	{
		GAME_PLAY,					//!< ゲームプレイ中
		PAUSE_MENU,					//!< ポーズメニュー
		CHANGE_SCENE,				//!< シーン移行
	};

	GameDataManager*		m_pGameDataManager;		//!< GameDataManagerクラスのインスタンスへのポインタ
	GameEventManager&		m_rGameEventManager;	//!< GameEventManagerクラスのインスタンスへの参照
	EventListener*			m_pEventListener;			//!< EventListenerクラスのインスタンスへのポインタ
	GamePauseMenu*			m_pPauseMenu;			//!< GamePauseMenuクラスのインスタンスへのポインタ
	StageManager*			m_pStageManager;		//!< m_pStageManagerクラスのインスタンスへのポインタ
	STATE					m_CurrentState;			//!< GameSecneの現在の状態

	/** 
	* コントロール関数 
	* @return 次のSceneID
	*/
	virtual Scene::ID Control(void)override;

	/** 描画関数 */
	virtual void Draw(void)override;

	/** イベントを処理する関数 */
	void HandleEvent(void);

	/** イベントを登録する関数 */
	void RegisterEvent(void);


};	// class GameScene

}	// namespace ar

#endif	// AR_GAME_SCENE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
