//==================================================================================================================================//
//!< @file		ThisScoreTimeText.h
//!< @brief		ar::ThisScoreTimeTextクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_THIS_PLAYED_TIME_TEXT_H
#define AR_THIS_PLAYED_TIME_TEXT_H

#include <vector>
#include "ScoreTimeText.h"
#include "../SharokuLibrary/sl/sl.h"

namespace ar
{

class NumberDrawer;
class ScoreCharacterDrawer;

//======================================================================//
//!< 今回のプレイ時間を表示するテキストクラス
//======================================================================//
class ThisScoreTimeText : public ScoreTimeText
{

public:
	/**
	* Constructor
	* @param[in] pNumberDrawer			NumberDrawerクラスのインスタンスへのポインタ
	* @param[in] pScoreCharacterDrawer	ScoreCharacterDrawerクラスのインスタンスへのポインタ
	*/
	ThisScoreTimeText(NumberDrawer* pNumberDrawer, ScoreCharacterDrawer* pScoreCharacterDrawer);

	/** Destructor */
	virtual ~ThisScoreTimeText(void) = default;

private:
	/** 先頭テキストを描画する関数 */
	virtual void DrawLeadText(void)override;

};	// class ThisScoreTimeText

}	// namespace ar


#endif	// AR_THIS_PLAYED_TIME_TEXT_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//

