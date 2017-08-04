//==================================================================================================================================//
//!< @file		LargeScoreCharacterDrawer.h
//!< @brief		LargeScoreCharacterDrawerクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_LARGE_SCORE_CHARACTER_DRAWER_H
#define AR_LARGE_SCORE_CHARACTER_DRAWER_H

#include "ScoreCharacterDrawer.h"

namespace ar
{

//======================================================================//
//!< 大きいサイズのスコア関連の文字列を描画するクラス
//======================================================================//
class LargeScoreCharacterDrawer : public ScoreCharacterDrawer
{

public:
	/** 
	* Constructor
	* @param[in] texID テクスチャーID
	*/
	LargeScoreCharacterDrawer(int texID);

	/** Destructor */
	~LargeScoreCharacterDrawer(void);

private:
	/** 描画IDを生成する関数 */
	virtual void CreateScoreCharacterDrawingID(void)override;

};	// class LargeScoreCharacterDrawer

}	// namespace ar

#endif	// AR_LARGE_SCORE_CHARACTER_DRAWER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
