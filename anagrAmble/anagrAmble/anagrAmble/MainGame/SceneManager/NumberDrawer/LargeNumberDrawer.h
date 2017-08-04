//==================================================================================================================================//
//!< @file		LargeNumberDrawer.h
//!< @brief		LargeNumberDrawerクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef LARGE_NUMBER_DRAWER_H
#define	LARGE_NUMBER_DRAWER_H

#include "NumberDrawer.h"

namespace ar
{

//======================================================================//
//!< 大きいサイズの1桁の数だけ描画するクラス
//======================================================================//
class LargeNumberDrawer : public NumberDrawer
{

public:
	/** 
	* Constructor
	* @param[in] texID テクスチャーID
	*/
	LargeNumberDrawer(int texID);

	/** Destructor */
	~LargeNumberDrawer(void);

private:
	/** 描画IDを生成する関数 */
	virtual void CreateNumDrawingID(void)override;

};	// class LargeNumberDrawer

}	// namespace ar

#endif	// LARGE_NUMBER_DRAWER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
