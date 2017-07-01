//==================================================================================================================================//
//!< @file		LogoBackground.h
//!< @brief		ar::LogoBackgroundクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_LOGO_BACKGROUND_H
#define AR_LOGO_BACKGROUND_H

#include "../SharokuLibrary/sl/sl.h"

namespace ar
{

//======================================================================//
//!< ロゴシーンの背景クラス
//======================================================================//
class LogoBackground
{

public:
	/** 
	* Constructor 
	* @param[in] texID	テクスチャーID
	*/
	explicit LogoBackground(int texID);

	/** Destructor */
	~LogoBackground(void);

	/** 
	* コントロール関数. 制御関数 
	* @return 処理(フェードアウトまで)が終了しているかどうか true→終了している. false→終了していない
	*/
	bool Control(void);

	/** 描画関数 */
	void Draw(void);

private:
	/** 背景の状態 */
	enum STATE
	{
		FADE_IN,					//!< フェードイン
		DISPLAYING,					//!< 表示中
		FADE_OUT,					//!< フェードアウト
	};

	sl::ISharokuLibrary*		m_pLibrary;							//!< sl::ISharokuLibraryクラスのインスタンスへのポインタ
	sl::SLVECTOR2				m_Pos;								//!< 位置座標
	sl::DrawingID				m_DrawingID;						//!< グラフィック関連のIDをまとめた構造体
	STATE						m_CurrentState;						//!< 現在の状態
	float						m_CurrentAlphaVal;					//!< 現在のアルファ値.フェードイン、フェードアウト処理で使用
	bool						m_EndsProcessing;					//!< 処理(フェードアウトまで)が終了したかどうか true→終了している. false→終了していない 
	int							m_DisplayTimeCount;					//!< 背景表示時間のカウント数

};	// class LogoBackground

}	// namespace ar

#endif	// AR_LOGO_BACKGROUND_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//

