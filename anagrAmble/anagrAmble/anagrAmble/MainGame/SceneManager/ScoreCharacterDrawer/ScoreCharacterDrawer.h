//==================================================================================================================================//
//!< @file		ScoreCharacterDrawer.h
//!< @brief		ScoreCharacterDrawerクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_SCORE_CHARACTER_DRAWER_H
#define AR_SCORE_CHARACTER_DRAWER_H

#include <vector>
#include "../Scene/Scene.h"
#include "../SharokuLibrary/sl/sl.h"

namespace ar
{

//======================================================================//
//!< スコア関連の文字列を描画するクラス
//======================================================================//
class ScoreCharacterDrawer
{

public:
	/** テキストの種類ID */
	enum TYPE_ID
	{
		TIME,					//!< 「Time」文字列
		HIGH_SCORE,				//!< 「HighScore」文字列
		SECOND_UNITS,			//!< 秒単位「S」文字列
		MINUTE_UNITS,			//!< 分単位「M」文字列
		COLON,					//!< コロン の文字
		ID_MAX,
	};

	/** 
	* Constructor
	* @param[in] texID テクスチャーID
	*/
	ScoreCharacterDrawer(int texID);

	/** Destructor */
	virtual ~ScoreCharacterDrawer(void) = default;

	/** 初期化関数 */
	void Initialize(void);

	/** 
	* 描画関数 
	* @param[in] typeID		テキストタイプID
	* @param[in] rPos		位置座標
	*/
	void Draw(int typeID, const sl::SLVECTOR2& rPos);

	/** 
	* 矩形サイズを取得する関数
	* @return 矩形サイズ
	*/
	const sl::fRect&	GetRectSize(void) { return m_RectSize; }

protected:
	sl::ISharokuLibrary*			m_pLibrary;					//!< ライブラリ.sl::ISharokuLibraryクラスのインスタンスへのポインタ
	int								m_TexID;					//!< テクスチャーID
	sl::fRect						m_RectSize;					//!< 矩形サイズ
	std::vector<sl::DrawingID>		m_ScoreCharacterDrawingID;	//!< スコア関連文字列の描画ID群

	/** 描画IDを生成する関数 */
	virtual void CreateScoreCharacterDrawingID(void) = 0;

};	// class ScoreCharacterDrawer

}	// namespace ar

#endif	// AR_SCORE_TEXT_DRAWER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
