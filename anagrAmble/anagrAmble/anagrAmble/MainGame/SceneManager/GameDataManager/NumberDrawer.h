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
//!< 数を描画するクラス
//!< 1桁の数だけ描画する
//======================================================================//
class NumberDrawer
{

public:
	/** 
	* Constructor
	* @param[in] このクラスを使用するSceneID
	* @param[in] texID テクスチャーID
	*/
	NumberDrawer(Scene::ID sceneID, int texID);

	/** Destructor */
	~NumberDrawer(void);

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
	* 現在の矩形サイズを取得する関数
	* @return 現在の矩形サイズ
	*/
	const sl::fRect&	GetCurrentRectSize(void) { return m_CurrentRectSize; }

private:
	sl::ISharokuLibrary*			m_pLibrary;				//!< ライブラリ.sl::ISharokuLibraryクラスのインスタンスへのポインタ
	Scene::ID						m_SceneID;				//!< このクラスを使用するSceneID
	int								m_TexID;				//!< テクスチャーID
	sl::fRect						m_CurrentRectSize;		//!< 現在の矩形サイズ
	std::vector<sl::DrawingID>		m_NumDrawingID;			//!< 番号の描画IDを格納したvector

	/** 描画IDを生成する関数 */
	void CreateNumDrawingID(void);


};	// class NumberDrawer

}	// namespace ar

#endif	// AR_NUMBER_DRAWER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
