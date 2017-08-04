//==================================================================================================================================//
//!< @file		HighScoreText.h
//!< @brief		ar::HighScoreTextクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_HIGH_SCORE_TEXT_H
#define AR_HIGH_SCORE_TEXT_H

#include <vector>
#include "ScoreTimeText.h"
#include "../SharokuLibrary/sl/sl.h"

namespace ar
{

class NumberDrawer;
class ScoreCharacterDrawer;

//======================================================================//
//!< ハイスコア時間を表示するテキストクラス
//======================================================================//
class HighScoreText : public ScoreTimeText
{
public:	
	/**
	* Constructor
	* @param[in] pNumberDrawer			NumberDrawerクラスのインスタンスへのポインタ
	* @param[in] pScoreCharacterDrawer	ScoreCharacterDrawerクラスのインスタンスへのポインタ
	*/
	HighScoreText(NumberDrawer* pNumberDrawer, ScoreCharacterDrawer* pScoreCharacterDrawer);

	/**  Destructor */
	virtual ~HighScoreText(void) = default;

private:
	/** 先頭テキストを描画する関数 */
	virtual void DrawLeadText(void)override;

};	// class HighScoreText

}	// namespace ar

#endif	// AR_HIGH_SCORE_TEXT_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
