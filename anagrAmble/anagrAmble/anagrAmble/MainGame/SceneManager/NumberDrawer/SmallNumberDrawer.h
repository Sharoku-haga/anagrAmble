//==================================================================================================================================//
//!< @file		SmallNumberDrawer.h
//!< @brief		SmallNumberDrawerクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef SMALL_NUMBER_DRAWER_H
#define SMALL_NUMBER_DRAWER_H

#include "NumberDrawer.h"

namespace ar
{

//======================================================================//
//!< 小さいサイズの1桁の数だけ描画するクラス
//======================================================================//
class SmallNumberDrawer : public NumberDrawer
{

public:
	/** 
	* Constructor
	* @param[in] texID テクスチャーID
	*/
	SmallNumberDrawer(int texID);

	/** Destructor */
	virtual ~SmallNumberDrawer(void);

	/** 描画IDを生成する関数 */
	virtual void CreateNumDrawingID(void)override;

};	// class SmallNumberDrawer

}	// namespace ar

#endif	// SMALL_NUMBER_DRAWER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
