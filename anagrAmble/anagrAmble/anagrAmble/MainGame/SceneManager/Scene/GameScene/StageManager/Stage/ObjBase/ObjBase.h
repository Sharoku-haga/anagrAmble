﻿//==================================================================================================================================//
//!< @file		ObjBase.h
//!< @brief		ar::ObjBaseクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_OBJBASE_H
#define AR_OBJBASE_H

#include "../SharokuLibrary/sl/sl.h"
#include "../Stage.h"

namespace ar
{

class EventLisner;

//======================================================================//
//!< ゲーム画面のオブジェクトの基底クラス
//======================================================================//
class ObjBase
{

public:
	/** 
	* オブジェクトのID
	* ステージ生成時にも使用する
	*/
	enum TYPE_ID
	{
		BLANK,				//!< 空白.何もなし
		NOMAL_BLOCK,		//!< 通常ブロック
		PLAYER,				//!< プレイヤー
		ID_MAX
	};

	/**  
	* Constructor
	* @attention 位置座標はStage::INDEX_DATAから継承クラスごとに設定すること
	* @param[in] rStageIndexData ステージインデックスデータ
	*/
	ObjBase(const Stage::INDEX_DATA& rStageIndexData);

	/** Destructor */
	virtual ~ObjBase(void);

	/** コントロール関数 */
	void Control(void);

	/** 描画関数 */
	void Draw(void);

	/**
	* 衝突処理関数.純粋仮想関数 
	* @param[in] typeID		衝突したオブジェクトのID
	* @param[in] isDeath	衝突したことで死んだかどうかのフラグ. true→死亡, flase→死んでいない. デフォルトはflase
	*/ 
	virtual void ProcessCollision(int typeID, bool isDeath = false) = 0;

	/** 
	* Getter 位置座標を取得する関数
	* @return 位置座標
	*/
	const sl::SLVECTOR2& GetPos(void) const { return m_Pos; }

	/** 
	* Getter 現在の矩形データ(位置座標 + 基本矩形サイズ)を取得する関数
	* @return 現在の矩形データ
	*/
	const sl::fRect& GetCurrentRectData(void) const { return m_CurrentRectData; }

	/** 
	* Getter 現在のステージのインデックスデータを取得する関数
	* @return ステージのインデックスデータ
	*/
	const Stage::INDEX_DATA& GetStageIndex(void) const { return m_StageIndexData; }

	/** 
	* Setter ステージのインデックスデータを取得する関数
	* @param[in] rStageIndexData
	*/
	void SetStageIndex(const Stage::INDEX_DATA& rStageIndexData){ m_StageIndexData = rStageIndexData; }

	/** 
	* Setter ベースポイントの位置座標をセットする関数.static
	* @param[in]  basePoitPos ベースポイントの位置座標
	*/
	static void SetBasePointPos(const sl::SLVECTOR2 basePointPos) { m_BasePointPos = basePointPos; }

	/** 
	* Setter 表示している画面範囲をセットする関数.static
	* @param[in] displayWidth	画面の横サイズ
	* @param[in] displayHeight	画面の縦サイズ
	*/
	static void SetDisplayArea(float displayWidth, float displayHeight)
	{
		m_DisplayArea.m_Right = displayWidth;
		m_DisplayArea.m_Bottom = displayHeight;
	}

protected:
	static	sl::SLVECTOR2	m_BasePointPos;					//!< ベースポイントの位置座標.static
	static  sl::fRect		m_DisplayArea;					//!< 画面範囲.static

	sl::SLVECTOR2			m_Pos;							//!< 位置座標
	sl::fRect				m_RectSize;						//!< 基本矩形サイズ
	sl::fRect				m_CurrentRectData;				//!< 位置座標 + 基本矩形サイズ
	Stage::INDEX_DATA		m_StageIndexData;				//!< 現在登録しているステージのインデックスデータ
	sl::DrawingID			m_DrawingID;					//!< 描画関連のIDをまとめた群
	TYPE_ID					m_TypeID;						//!< オブジェクトのタイプID
	EventLisner*			m_pEventLisner;					//!< EventLisnerクラスのインスタンスへのポインタ

	/** 
	* 処理実行関数.純粋仮想関数 
	* Constrol()内で使用
	*/
	virtual void Run(void) = 0;

	/** 
	* 描画関数.純粋仮想関数 
	* Draw()内で使用する
	*/
	virtual void Render(void) = 0;

	/** イベント処理関数.純粋仮想関数  */
	virtual void HandleEvent(void) = 0;

};	// class ObjBase

}	// namespace ar

#endif	// AR_OBJBASE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//