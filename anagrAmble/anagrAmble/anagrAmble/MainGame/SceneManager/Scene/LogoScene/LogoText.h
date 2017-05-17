//==================================================================================================================================//
//!< @file		LogoText.h
//!< @brief		LogoTextクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_LOGO_TEXT_H
#define AR_LOGO_TEXT_H

#include "../SharokuLibrary/sl/sl.h"

namespace ar
{

class LogoText
{
public:
	/** 
	* Constructor 
	* @param[in] texID	テクスチャーID
	*/
	explicit LogoText(int texID);

	/** Destructor */
	~LogoText(void);

	/** 
	* コントロール関数
	* @return ロゴ表示時間が終わったかどうか true→終了 false→表示中
	*/
	bool Control(void);

	/** 描画関数 */
	void Draw(void);

private:
	sl::SLVECTOR2			m_Pos;					//!< 位置座標
	sl::GraphicsIDs			m_ID;					//!< グラフィック関連のIDをまとめた構造体
	sl::ISharokuLibrary*	m_pLibrary;				//!< ISharokuLibraryクラスのインスタンスへのポインタ
	int						m_DispTimeCount;		//!< 表示時間をカウントする変数
	bool					m_IsEnd;				//!< 表示が終わったどうかのフラグ

};

}	// namespace ar

#endif	// AR_LOGO_TEXT_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
