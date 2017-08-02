//==================================================================================================================================//
//!< @file		SmallScoreCharacterDrawer.h
//!< @brief		SmallScoreCharacterDrawerクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_SMALL_SCORE_CHARACTER_DRAWER_H
#define AR_SMALL_SCORE_CHARACTER_DRAWER_H

#include "ScoreCharacterDrawer.h"

namespace ar
{

//======================================================================//
//!< 小さいサイズのスコア関連の文字列を描画するクラス
//======================================================================//
class SmallScoreCharacterDrawer : public ScoreCharacterDrawer
{

public:
	/** 
	* Constructor
	* @param[in] texID テクスチャーID
	*/
	SmallScoreCharacterDrawer(int texID);
	
	/** Destructor */
	virtual ~SmallScoreCharacterDrawer(void);

private:
	/** 描画IDを生成する関数 */
	virtual void CreateScoreCharacterDrawingID(void)override;

};	// class SmallScoreCharacterDrawer

}	// namespace ar

#endif	// AR_SMALL_SCORE_CHARACTER_DRAWER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
