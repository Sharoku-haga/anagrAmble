//==================================================================================================================================//
//!< @file		GamePauseMenu.h
//!< @brief		ar::GamePauseMenuクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_GAME_PAUSE_MENU_H
#define AR_GAME_PAUSE_MENU_H

#include <vector>

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
	* @param[in] bgTexID			メニュー背景のテクスチャーID
	* @param[in] pauseBtnTexID		ポーズボタンのテクスチャーID
	* @param[in] titleReturnBtnID	タイトルへ戻るボタンのテクスチャーID
	*/
	GamePauseMenu(int bgTexID, int pauseBtnTexID, int titleReturnBtnID);

	/** Destructor */
	~GamePauseMenu(void);

	/** コントロール関数 */
	void Control(void);

	/** 描画関数 */
	void Draw(void);

private:
	/** ポーズメニューのボタン種類 */
	enum BTN_TYPE
	{
		PAUSE,			//!< ポーズボタン (表示のみ)
		TITLE_RETUN,	//!< ゲーム終了ボタン
		BTN_MAX,		//!< ボタンの種類のMAX値
	};

	sl::ISharokuLibrary*		m_pLibrary;				//!< sl::ISharokuLibraryクラスのインスタンスへのポインタ 
	GamePauseMenuBackground*	m_pBackground;			//!< ポーズメニューの背景
	std::vector<Button*>		m_pButtons;				//!< Buttonクラスのインスタンス
	int							m_ButtonMoveTimeCount;	//!< ボタンの動作時間カウント変数
	bool						m_MovesButton;			//!< ボタンが動いているかどうか. true→ボタンが動作している. false→ボタンは動いていない

};	// class GamePauseMenu

}	// namespace ar

#endif	// AR_GAME_PAUSE_MENU_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//	
