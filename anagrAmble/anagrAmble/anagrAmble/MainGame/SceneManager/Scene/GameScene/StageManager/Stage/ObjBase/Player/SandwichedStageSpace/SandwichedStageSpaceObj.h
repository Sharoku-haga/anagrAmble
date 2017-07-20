//==================================================================================================================================//
//!< @file		SandwichedStageSpaceObj.h
//!< @brief		ar::SandwichedStageSpaceObjクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_SANDWICHED_STAGE_SPACE_OBJ_H
#define AR_SANDWICHED_STAGE_SPACE_OBJ_H

#include "../SharokuLibrary/sl/sl.h"
#include "../../../Stage.h"

namespace ar
{

class ObjBase;

//======================================================================//
//!< ゲームにおいてプレイヤーのアンカーで
//!< 挟んだ空間のオブジェクトの描画を管理するクラス
//======================================================================//
class SandwichedStageSpaceObj
{

public:
	/** 
	* Constructor 
	* @param[in] rPos 位置座標
	* @param[in] rID  描画ID
	*/
	SandwichedStageSpaceObj(const sl::SLVECTOR2& rPos, const sl::DrawingID& rID );

	/** Destructor */
	~SandwichedStageSpaceObj(void);

	/** 
	* 描画処理を行う関数
	*/
	void Draw(void);

	/**
	* 描画関連のIDを取得する関数
	* @return 描画ID
	*/
	const sl::DrawingID& GetDrawingID(void) { return m_DrawingID; }
	
	/**
	* BasePointの座標をセットする関数
	* @attention この関数は必ずBasePointクラスの関数内だけでよぶこと
	* @param[in] rBasePointPos		BasePoint座標
	*/
	static void SetBasePointPos(const sl::SLVECTOR2 rBasePointPos) { m_BasePointPos = rBasePointPos; }
	
	/**
	* プレイヤーのRect構造体をセットする関数
	* @attention この関数は必ずSandwichedStageSpaceクラスの関数内だけでよぶこと
	* @param[in] rPlayerPos			プレイヤー座標
	*/
	static void SetPlayerRect(const sl::fRect& rPlayerRect) { m_PlayerRect = rPlayerRect; }

	/**
	* プレイヤーが右を向いているかどうかのフラグをセットする関数
	* @attention この関数は必ずSandwichedStageSpaceクラスの関数内だけでよぶこと
	* @param[in] isPlayerFacingRight	プレイヤーが右を向いているかどうかのフラグ
	*/
	static void SetIsPlayerFacingRight(bool isPlayerFacingRight) { m_IsPlayerFacingRight = isPlayerFacingRight; }

	/**
	* プレイヤーが右を向いているかどうかのフラグをセットする関数
	* @attention この関数は必ずSandwichedStageSpaceクラスの関数内だけでよぶこと
	* @param[in] isPlayerFacingRight	プレイヤーが右を向いているかどうかのフラグ
	*/
	static void SetSandwichedSpaceWidth(float sandwichedSpaceWidth) { m_SandwichedSpaceWidth = sandwichedSpaceWidth; }

	/**
	* プレイヤーのステージインデックスデータの座標をセットする関数
	* @attention この関数は必ずSandwichedStageSpaceクラスの関数内だけでよぶこと
	* @param[in] rPlayerIndexData		プレイヤーのステージインデックスデータ
	*/
	static void SetPlayerIndexData(const Stage::INDEX_DATA& rPlayerIndexData) { m_PlayerIndexData = rPlayerIndexData; }
	
	/**
	* ステージマップチップサイズをセットする関数
	* @attention この関数は必ずSandwichedStageSpaceクラスの関数内だけでよぶこと
	* @param[in] stageMapChipSize		ステージマップチップサイズ
	*/
	static void SetStageMapChipSize(float stageMapChipSize) { m_StageMapChipSize = stageMapChipSize; }

private:
	static sl::SLVECTOR2					m_BasePointPos;					//!< ベースポイントの座標
	static sl::fRect						m_PlayerRect;					//!< プレイヤーのRect構造体
	static Stage::INDEX_DATA				m_PlayerIndexData;				//!< プレイヤーのインデックスデータ
	static float							m_StageMapChipSize;				//!< ステージマップチップサイズ
	static bool								m_IsPlayerFacingRight;			//!< プレイヤーが右を向いているかどうかのフラグ true→右を向いている false→左を向いている
	static float							m_SandwichedSpaceWidth;			//!< 挟んだ空間の横の長さ

	sl::ISharokuLibrary*					m_pLibrary;						//!< ライブラリ. sl::ISharokuLibraryクラスのインスタンスへのポインタ
	sl::SLVECTOR2							m_Pos;							//!< 位置座標. 
	sl::DrawingID							m_DrawingID;					//!< 描画関連のID

};	// class SandwichedStageSpaceObj

}	// namespace ar

#endif	// AR_SANDWICHED_STAGE_SPACE_OBJ_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
