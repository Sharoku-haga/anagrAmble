//==================================================================================================================================//
//!< @file		StageBackground.h
//!< @brief		ar::StageBackgroundクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_STAGE_BACKGROUND_H
#define AR_STAGE_BACKGROUND_H

#include <vector>
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
	std::vector< sl::SLVECTOR2>			m_Pos;					//!< 位置座標を格納したvector
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
