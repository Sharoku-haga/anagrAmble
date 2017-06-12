//==================================================================================================================================//
//!< @file		StageBackground.h
//!< @brief		ar::StageBackgroundクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_STAGE_BACKGROUND_H
#define AR_STAGE_BACKGROUND_H

#include "../SharokuLibrary/sl/sl.h"

namespace ar
{

class BasePoint;

//======================================================================//
//!< ゲームステージの背景クラス
//======================================================================//
class StageBackground
{

public:
	/** 
	* Constructor
	* @param[in] pBasePoint BasePointクラスのインスタンスへのポインタ
	* @param[in] texID		テクスチャーID
	*/
	StageBackground(BasePoint* pBasePoint, int texID);

	/** Destructor */
	~StageBackground(void);

	/** コントロール関数 */
	void Control(void);

	/** 描画関数 */
	void Draw(void);

private:
	sl::SLVECTOR2						m_FirstPos;				//!< 1つ目の背景の座標
	sl::SLVECTOR2						m_SecondPos;			//!< 2つ目の背景の座標
	sl::DrawingID						m_ID;					//!< グラフィック関連のIDをまとめた構造体
	sl::fRect							m_RectSize;				//!< 矩形サイズ
	sl::ISharokuLibrary*				m_pLibrary;				//!< sl::ISharokuLibraryクラスのインスタンスへのポインタ
	BasePoint*							m_pBasePoint;			//!< BasePointクラスのインスタンスへのポインタ
	sl::SLVECTOR2						m_OldBasePointPos;		//!< 動く前のBasePointの座標

};	// class StageBackground

}	// namespace ar

#endif	// AR_STAGE_BACKGROUND_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
