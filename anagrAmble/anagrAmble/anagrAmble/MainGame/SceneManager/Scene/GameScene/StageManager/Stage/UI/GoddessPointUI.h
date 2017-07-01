//==================================================================================================================================//
//!< @file		GoddessPointUI.h
//!< @brief		ar::GoddessPointUIクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_GODDESS_POINT_UI_H
#define AR_GODDESS_POINT_UI_H

#include <vector>
#include "../SharokuLibrary/sl/sl.h"

namespace ar
{
class EventListener;

//======================================================================//
//!< 女神の加護の数を表示するUIのクラス
//======================================================================//
class GoddessPointUI
{

public:
	/** 
	* Constructor 
	* @param[in] texID					テクスチャーID
	* @param[in] goddessPointCount		女神の加護数
	*/
	GoddessPointUI(int texID, int goddessPointCount);

	/** Destructor */
	~GoddessPointUI(void);

	/** 初期化関数 */
	void Initialize(void);

	/** コントロール関数 */
	void Control(void);

	/** 描画関数 */
	void Draw(void);

private:
	sl::ISharokuLibrary*			m_pLibrary;				//!< ライブラリ. sl::ISharokuLibraryクラスのインスタンスへのポインタ			
	std::vector<sl::SLVECTOR2>		m_Pos;					//!< UIの位置座標.女神の数分用意する
	sl::DrawingID					m_DrawingID;			//!< 描画に関するID群
	EventListener*					m_pEventListener;		//!< EventListenerクラスのインスタンスへのポインタ
	int								m_GoddessPointCount;	//!< 女神の加護数

	/** イベント処理関数 */
	void HandleEvent(void);

};	// class GoddessPointUI

}	// namespace ar

#endif	// AR_GODDESS_POINT_UI_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
