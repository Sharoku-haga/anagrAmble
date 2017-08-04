//==================================================================================================================================//
//!< @file		NumberDrawer.h
//!< @brief		NumberDrawerクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_NUMBER_DRAWER_H
#define AR_NUMBER_DRAWER_H

#include <vector>
#include "../Scene/Scene.h"
#include "../SharokuLibrary/sl/sl.h"

namespace ar
{

//======================================================================//
//!< 1桁の数だけ描画するクラス
//!< 基底クラス
//======================================================================//
class NumberDrawer
{

public:
	/** 
	* Constructor
	* @param[in] texID テクスチャーID
	*/
	NumberDrawer(int texID);

	/** Destructor */
	virtual ~NumberDrawer(void) = default;

	/** 初期化関数 */
	void Initialize(void);

	/** 
	* 数を描画する関数 
	* 0～9までの数字を描画することが出来る
	* @param[in] drawNum 描画したい数字
	* @param[in] rPos	 描画したい位置座標
	*/
	void DrawNumber(unsigned int drawNum, const sl::SLVECTOR2& rPos);

	/** 
	* 矩形サイズを取得する関数
	* @return 矩形サイズ
	*/
	const sl::fRect&	GetRectSize(void) { return m_RectSize; }

protected:
	static const int				m_NumberCount = 10;		//!< 番号の数0～9までの10個

	sl::ISharokuLibrary*			m_pLibrary;				//!< ライブラリ.sl::ISharokuLibraryクラスのインスタンスへのポインタ
	int								m_TexID;				//!< テクスチャーID
	sl::fRect						m_RectSize;				//!< 矩形サイズ
	std::vector<sl::DrawingID>		m_NumDrawingID;			//!< 番号の描画IDを格納したvector

	/** 描画IDを生成する関数 */
	virtual void CreateNumDrawingID(void) = 0;

};	// class NumberDrawer

}	// namespace ar

#endif	// AR_NUMBER_DRAWER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
