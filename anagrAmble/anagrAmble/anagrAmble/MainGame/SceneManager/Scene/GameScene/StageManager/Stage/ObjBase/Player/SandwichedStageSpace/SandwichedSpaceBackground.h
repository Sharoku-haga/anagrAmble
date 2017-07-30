//==================================================================================================================================//
//!< @file		SandwichedSpaceBackground.h
//!< @brief		ar::SandwichedSpaceBackgroundクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_SANDWICHED_SPACE_BACKGROUND_H
#define AR_SANDWICHED_SPACE_BACKGROUND_H

#include "../SharokuLibrary/sl/sl.h"
#include "../../../Stage.h"

namespace ar
{

//======================================================================//
//!< ゲームにおいてプレイヤーのアンカーで挟んだ空間の背景クラス
//======================================================================//
class SandwichedSpaceBackground
{

public:
	/** 
	* Constructor
	* @param[in] texID	テクスチャーのID
	*/
	explicit SandwichedSpaceBackground(int texID);

	/** Destructor */
	~SandwichedSpaceBackground(void);

	/**
	* データ初期化関数
	* SandwichedStageSpaceクラスのInitializeData関数内で呼ぶ
	* @param[in] pos			位置座標
	* @param[in] spaceWidth		挟んだ空間の横の長さ
	* @param[in] spaceHeight	挟んだ空間の縦の長さ
	*/
	void InitializeData(const sl::SLVECTOR2& rPos, float spaceWidth, float spaceHeight);

	/**
	* データを破棄する関数
	* SandwichedStageSpaceクラスのDiscardData関数内で呼ぶ
	*/
	void DiscardData(void);

	/** 
	* 描画関数
	* 描画処理を行う関数
	*/
	void Draw(void);

	/**
	* プレイヤーのRect構造体をセットする関数
	* @attention この関数は必ずSandwichedStageSpaceクラスの関数内だけでよぶこと
	* @param[in] rPlayerPos			プレイヤー座標
	*/
	void SetPlayerRect(const sl::fRect& rPlayerRect) { m_PlayerRect = rPlayerRect; }

	/**
	* プレイヤーが右を向いているかどうかのフラグをセットする関数
	* @attention この関数は必ずSandwichedStageSpaceクラスの関数内だけでよぶこと
	* @param[in] isPlayerFacingRight	プレイヤーが右を向いているかどうかのフラグ
	*/
	void SetIsPlayerFacingRight(bool isPlayerFacingRight) { m_IsPlayerFacingRight = isPlayerFacingRight; }

	/**
	* プレイヤーのステージインデックスデータの座標をセットする関数
	* @attention この関数は必ずSandwichedStageSpaceクラスの関数内だけでよぶこと
	* @param[in] rPlayerIndexData		プレイヤーのステージインデックスデータ
	*/
	void SetPlayerIndexData(const Stage::INDEX_DATA& rPlayerIndexData) { m_PlayerIndexData = rPlayerIndexData; }

	/**
	* BasePointの座標をセットする関数
	* @attention この関数は必ずBasePointクラスの関数内だけでよぶこと
	* @param[in] rBasePointPos		BasePoint座標
	*/
	static void SetBasePointPos(const sl::SLVECTOR2 rBasePointPos) { m_BasePointPos = rBasePointPos; }

	/**
	* ステージマップチップサイズをセットする関数
	* @attention この関数は必ずSandwichedStageSpaceクラスの関数内だけでよぶこと
	* @param[in] stageMapChipSize		ステージマップチップサイズ
	*/
	static void SetStageMapChipSize(float stageMapChipSize) { m_StageMapChipSize = stageMapChipSize; }

private:
	static sl::SLVECTOR2					m_BasePointPos;					//!< ベースポイントの座標
	static float							m_StageMapChipSize;				//!< ステージマップチップサイズ

	sl::ISharokuLibrary*					m_pLibrary;						//!< ライブラリ. sl::ISharokuLibraryクラスのインスタンスへのポインタ
	sl::SLVECTOR2							m_Pos;							//!< 位置座標
	sl::DrawingID							m_DrawingID;					//!< 描画の為ID群
	float									m_SandwichedSpaceWidth;			//!< 挟んだ空間の横の長さ.
	sl::fRect								m_PlayerRect;					//!< プレイヤーのRect構造体
	Stage::INDEX_DATA						m_PlayerIndexData;				//!< プレイヤーのインデックスデータ
	bool									m_IsPlayerFacingRight;			//!< プレイヤーが右を向いているかどうかのフラグ true→右を向いている false→左を向いている

};	// class SandwichedSpaceBackground

}	// namespace ar

#endif	// AR_SANDWICHED_SPACE_BACKGROUND_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
