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
	* コントロール関数. 制御関数 
	* @return 処理(フェードアウトまで)が終了しているかどうか true→終了している. false→終了していない
	*/
	bool Control(void);

	/** 
	* 描画関数 
	* 背景の描画を行う
	*/
	void Draw(void);

private:
	/** 背景の状態 */
	enum STATE
	{
		FADE_IN,					//!< フェードイン
		DISPLAYING,					//!< 表示中
		FADE_OUT,					//!< フェードアウト
		WAITING_CHANGE_OF_SCENE,	//!< シーンチェンジ待機(余韻をのこす時間)
	};

	sl::ISharokuLibrary*		m_pLibrary;							//!< ライブラリ. sl::ISharokuLibraryクラスのインスタンスへのポインタ
	sl::SLVECTOR2				m_Pos;								//!< 位置座標
	sl::DrawingID				m_DrawingID;						//!< 描画で使用するID群
	STATE						m_CurrentState;						//!< 現在の状態
	float						m_CurrentAlphaVal;					//!< 現在のアルファ値.フェードイン、フェードアウト処理で使用
	bool						m_EndsProcessing;					//!< 処理(フェードアウトまで)が終了したかどうか true→終了している. false→終了していない 
	int							m_DisplayTimeCount;					//!< 背景表示時間のカウント数
	int							m_ChangeSceneWaitingTimeCount;		//!< シーン変更までの待機時間のカウント数

};	// class GameClearBackground

}	// namespace ar

#endif	// AR_GAME_CLEAR_BACKGROUND_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
