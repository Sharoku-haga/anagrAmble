//==================================================================================================================================//
//!< @file		TilteMenu.h
//!< @brief		ar::TilteMenuクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_TITLE_MENU_H
#define AR_TITLE_MENU_H

#include <vector>
#include "TitleScene.h"
#include "../SharokuLibrary/sl/sl.h"

namespace ar
{

class Button;

//======================================================================//
//!< タイトルシーンのメニュークラス
//======================================================================//
class TitleMenu
{

public:
	/** 
	* Constructor
	* @param[in] btnTexID ボタンテクスチャーID
	*/
	explicit TitleMenu(int btnTexID);

	/** Destructor */
	~TitleMenu(void);

	/** 
	* コントロール関数 
	* @return 次のSceneID
	*/
	Scene::ID Control(void);

	/** 描画関数 */
	void Draw(void);

private:

	/** メニューのボタン種類 */
	enum BTN_TYPE
	{
		GAME_START,		//!< ゲームスタートボタン 
		GAME_END,		//!< ゲーム終了ボタン
		BTN_MAX,		//!< ボタンの種類のMAX値
	};

	sl::ISharokuLibrary*	m_pLibrary;				//!< sl::ISharokuLibraryクラスのインスタンスへのポインタ
	BTN_TYPE				m_CurrentSelectBtn;		//!< 現在選んでいるボタンの種類
	std::vector<Button*>	m_pButtons;				//!< Buttonクラスのインスタンス
	int						m_ButtonMoveTimeCount;	//!< ボタンの動作時間カウント変数
	bool					m_MovesButton;			//!< ボタンが動いているかどうか. true→ボタンが動作している. false→ボタンは動いていない

	/** コントローラー処理によりボタンを選択する関数 */
	void SelectButton(void);

};	// class TitleMenu

}	// namespace ar

#endif // AR_TITLE_MENU_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
