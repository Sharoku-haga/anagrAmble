//==================================================================================================================================//
//!< @file		TitleBackground.h
//!< @brief		ar::TitleBackgroundクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_TITLE_BACKGROUND_H
#define AR_TITLE_BACKGROUND_H

#include "../SharokuLibrary/sl/sl.h"

namespace ar
{

//======================================================================//
//!< タイトルシーンの背景クラス
//======================================================================//
class TitleBackground
{

public:
	/** 
	* Constructor
	* @param[in] texID テクスチャーID
	*/
	explicit TitleBackground(int texID);

	/** Destructor */
	~TitleBackground(void);

	/** 描画関数 */
	void Draw(void);

private:
	sl::SLVECTOR2			m_Pos;					//!< 位置座標
	sl::DrawingID			m_ID;					//!< グラフィック関連のIDをまとめた構造体
	sl::ISharokuLibrary*	m_pLibrary;				//!< sl::ISharokuLibraryクラスのインスタンスへのポインタ

};	// class TitleBackground

}	// namespace ar

#endif	// AR_TITLE_BACKGROUND_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
