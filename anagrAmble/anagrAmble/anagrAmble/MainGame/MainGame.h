//==================================================================================================================================//
//!< @file		MainGame.h
//!< @brief		ar::MainGameクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef MAIN_GAME_H
#define MAIN_GAME_H

namespace sl
{

class ISharokuLibrary;

}	// namespace sl

namespace ar
{

class SceneManager;

//======================================================================//
//!< 「anagrAmble」ゲーム本体クラス
//!< ライブラリの初期化やゲームループなどを行う
//======================================================================//
class MainGame
{

public:
	/** Constructor */
	MainGame(void);

	/** Destructor */
	~MainGame(void);

	/** ゲームループ関数 */
	void Loop(void);

private:
	sl::ISharokuLibrary*			m_pLibrary;				//!< sl::ISharokuLibraryクラスのインスタンスへのポインタ
	SceneManager*					m_pSceneManager;		//!< SceneManagerクラスのインスタンスへのポインタ

	/** デバイスインプットの設定を行う */
	void CustomizeInput(void);

#ifdef _DEBUG

	/** デバック用 デバイスインプットの設定 */
	void CutomizeInputDebug(void);

#endif // _DEBUG

	
};	// class MainGame

} // namespace ar

#endif	// MAIN_GAME_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
