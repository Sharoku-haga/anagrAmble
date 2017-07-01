//==================================================================================================================================//
//!< @file		ScoreTextDrawer.h
//!< @brief		ScoreTextDrawerクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_SCORE_TEXT_DRAWER_H
#define AR_SCORE_TEXT_DRAWER_H

#include <vector>
#include "../Scene/Scene.h"
#include "../SharokuLibrary/sl/sl.h"

namespace ar
{

//======================================================================//
//!< スコア関連のテキストを描画するクラス
//======================================================================//
class ScoreTextDrawer
{

public:
	/** テキストの種類ID */
	enum TYPE_ID
	{
		TIME,					//!< 「TIME」テキスト
		HIGH_SCORE,				//!< 「HighScore」テキスト
		SECOND_UNITS,			//!< 秒単位「S」テキスト
		MINUTE_UNITS,			//!< 分単位「M」テキスト
		COLON,					//!< コロン
		ID_MAX,
	};

	/** 
	* Constructor
	* @param[in] このクラスを使用するSceneID
	* @param[in] texID テクスチャーID
	*/
	ScoreTextDrawer(Scene::ID sceneID, int texID);

	/** Destructor */
	~ScoreTextDrawer(void);

	/** 初期化関数 */
	void Initialize(void);

	/** 
	* 描画関数 
	* @param[in] typeID		テキストタイプID
	* @param[in] rPos		位置座標
	*/
	void Draw(int typeID, const sl::SLVECTOR2& rPos);

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
	std::vector<sl::DrawingID>		m_ScoreTextDrawingID;	//!< スコア関連テキストの描画ID群

	/** 描画IDを生成する関数 */
	void CreateNumDrawingID(void);

};	// class ScoreTextDrawer

}	// namespace ar

#endif	// AR_SCORE_TEXT_DRAWER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
