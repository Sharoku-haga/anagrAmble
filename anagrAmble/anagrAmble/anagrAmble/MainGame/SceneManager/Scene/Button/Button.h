//==================================================================================================================================//
//!< @file		Button.h
//!< @brief		ar::Buttonクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_BUTTON_H
#define AR_BUTTON_H

#include "../SharokuLibrary/sl/Common/slStruct.h"

namespace sl
{

class ISharokuLibrary;

}	// namespace sl

namespace ar
{

//======================================================================//
//!< anagrAmbleにおけるボタンの抽象クラス
//======================================================================//
class Button
{

public:
	/** Constructor */
	Button(void);

	/** Destructor */
	virtual ~Button(void) = default;

	/** コントロール関数 */
	void Control(void);

	/** 描画関数 */
	void Draw(void);

	/** 
	* Getter
	* VertexIDを取得する関数
	*/
	inline int GetVtxID(void) { return m_ID.m_VtxID; }

protected:
	sl::ISharokuLibrary*		m_pLibrary;			//!< sl::ISharokuLibraryクラスのインスタンスへのポインタ
	sl::DrawingID				m_ID;				//!< 描画関連のID群

	/** 
	* 処理実行関数 
	* Control()におけるメイン処理
	*/
	virtual void Run(void) = 0;

	/** 
	* 描画処理関数
	* Draw()におけるメイン処理
	*/
	virtual void Render(void) = 0;

};	// class Button

}	// namespace ar

#endif	// AR_BUTTON_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
