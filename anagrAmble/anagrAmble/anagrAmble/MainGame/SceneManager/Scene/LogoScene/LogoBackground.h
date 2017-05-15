//==================================================================================================================================//
//!< @file		LogoBackground.h
//!< @brief		LogoBackgroundクラスヘッダ
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

	/** 描画関数 */
	void Draw(void);

private:
	sl::SLVECTOR2			m_Pos;					//!< 位置座標
	sl::GraphicsIDs			m_ID;					//!< グラフィック関連のIDをまとめた構造体
	sl::ISharokuLibrary*	m_pLibrary;				//!< ISharokuLibraryクラスのインスタンスへのポインタ


};

}	// namespace ar

#endif	// AR_LOGO_BACKGROUND_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//

