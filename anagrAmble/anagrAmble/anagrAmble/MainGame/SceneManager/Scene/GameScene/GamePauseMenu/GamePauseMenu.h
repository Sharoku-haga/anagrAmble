//==================================================================================================================================//
//!< @file		GamePauseMenu.h
//!< @brief		ar::GamePauseMenuクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_GAME_PAUSE_MENU_H
#define AR_GAME_PAUSE_MENU_H


namespace sl
{

class ISharokuLibrary;

}	// namespace sl

namespace ar
{

class Button;
class GamePauseMenuBackground;

//======================================================================//
//!< ゲームシーンのポーズメニュークラス
//======================================================================//
class GamePauseMenu
{
public:
	/** 
	* Constructor
	* @param[in] bgTexID	メニュー背景のテクスチャーID
	* @param[in] btnTexID	ボタンのテクスチャーID
	*/
	GamePauseMenu(int bgTexID, int btnTexID);

	/** Destructor */
	~GamePauseMenu(void);

	/** コントロール関数 */
	void Control(void);

	/** 描画関数 */
	void Draw(void);

private:
	sl::ISharokuLibrary*		m_pLibrary;				//!< sl::ISharokuLibraryクラスのインスタンスへのポインタ 
	GamePauseMenuBackground*	m_pBackground;			//!< ポーズメニューの背景
	Button*						m_pButton;				//!< タイトルへ移行ボタン(Buttonクラスのインスタンスへのポインタ)
	int							m_ButtonMoveTimeCount;	//!< ボタンの動作時間カウント変数
	bool						m_MovesButton;			//!< ボタンが動いているかどうか


};	// class GamePauseMenu

}	// namespace ar

#endif	// AR_GAME_PAUSE_MENU_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//	
