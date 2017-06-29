//==================================================================================================================================//
//!< @file		GameClearBackground.h
//!< @brief		ar::GameClearBackgroundクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_GAME_CLEAR_BACKGROUND_H
#define AR_GAME_CLEAR_BACKGROUND_H


#include "../SharokuLibrary/sl/sl.h"

namespace ar
{

//======================================================================//
//!< anagrAmbleにおけるゲームクリアシーンの背景クラス
//======================================================================//
class GameClearBackground
{

public:
	/** 
	* Constructor 
	* @param[in] texID 使用するテクスチャーのID
	*/
	explicit GameClearBackground(int texID);

	/** Destructor */
	~GameClearBackground(void);
	
	/** 
	* 表示時間をコントロールする関数. 
	* @return 表示時間が規定数に達しているかどうか  true→達している. false→達していない
	*/
	bool ControlDisplayTime(void);

	/**
	* 背景のフェードインの処理を行う関数
	* @return 処理が終了しているかどうか true→終了している. false→終了していない
	*/
	bool FadeIn(void);

	/**
	* 背景のフェードアウトの処理を行う関数
	* @return 処理が終了しているかどうか true→終了している. false→終了していない
	*/
	bool FadeOut(void);

	/** 
	* 描画関数 
	* 背景の描画を行う
	*/
	void Draw(void);

private:
	sl::ISharokuLibrary*		m_pLibrary;							//!< ライブラリ. sl::ISharokuLibraryクラスのインスタンスへのポインタ
	sl::SLVECTOR2				m_Pos;								//!< 位置座標
	sl::DrawingID				m_DrawingID;						//!< 描画で使用するID群
	float						m_CurrentAlphaVal;					//!< 現在のアルファ値.フェードイン、フェードアウト処理で使用
	int							m_DisplayTimeCount;					//!< 背景表示時間のカウント数

};	// class GameClearBackground

}	// namespace ar

#endif	// AR_GAME_CLEAR_BACKGROUND_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
