//==================================================================================================================================//
//!< @file		GamePauseMenuBackground.h
//!< @brief		ar::GamePauseMenuBackgroundクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_GAME_PAUSE_MENU_BACKGROUND_H
#define AR_GAME_PAUSE_MENU_BACKGROUND_H

#include "../SharokuLibrary/sl/sl.h"

namespace ar
{

//======================================================================//
//!< ゲームシーンのポーズメニューの背景クラス
//======================================================================//
class GamePauseMenuBackground
{

public:
	/** 
	* Constructor
	* @param[in] texID テクスチャーID
	*/
	explicit GamePauseMenuBackground(int texID);

	/** Destructor */
	~GamePauseMenuBackground(void);

	/** 描画関数 */
	void Draw(void);

private:
	sl::ISharokuLibrary*	m_pLibrary;				//!< sl::ISharokuLibraryクラスのインスタンスへのポインタ
	sl::SLVECTOR2			m_Pos;					//!< 位置座標
	sl::DrawingID			m_ID;					//!< グラフィック関連のIDをまとめた構造体
	
};	// GamePauseMenuBackground

}	// namespace ar

#endif	// AR_GAME_PAUSE_MENU_BACKGROUND_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
