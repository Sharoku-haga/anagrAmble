//==================================================================================================================================//
//!< @file		ObjBase.h
//!< @brief		ar::ObjBaseクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_OBJBASE_H
#define AR_OBJBASE_H

#include "../SharokuLibrary/sl/sl.h"
#include "../CollisionManager.h"
#include "../Stage.h"


namespace ar
{

class EventLisner;
class StageDataManager;

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
		BLANK,								//!< 空白.何もなし
		NORMAL_B,							//!< 通常ブロック
		GROUND_B,							//!< 地面ブロック
		ELECTICAL_B,						//!< 通電ブロック
		PRESSURE_SENSITIVE_B,				//!< 感圧ブロック
		LIGHT_ROAD_B,						//!< 足場排出ブロック
		LEVER,								//!< レバー
		GOAL,								//!< ゴール
		LOCLED_GOAL,						//!< 鍵付きゴール
		GOAL_KEY,							//!< ゴールキー
		PAIR_OF_EMBLME_B_R,					//!< 2つで1つの紋章ブロックの右側
		PAIR_OF_EMBLME_B_L,					//!< 2つで1つの紋章ブロックの左側		
		SET_OF_THREE_EMBLME_B_R,			//!< 3つで1つの紋章ブロックの左側
		SET_OF_THREE_EMBLME_B_F,			//!< 3つで1つの紋章ブロックの中央側
		SET_OF_THREE_EMBLME_B_L,			//!< 3つで1つの紋章ブロックの左側
		REVOLVING_LIGHT_DOOR_HORIZONTAL,	//!< 横向きの光の回転扉	
		REVOLVING_LIGHT_DOOR_VERTICAL,		//!< 縦向きの光の回転扉
		LIGHT_DOOR_UP,						//!< 上に向かって伸びている光の扉
		LIGHT_DOOR_DOWN,					//!< 下に向かって伸びている光の扉
		LIGHT_DOOR_RIGHT,					//!< 右に向かって伸びている光の扉
		LIGHT_DOOR_LEFT,					//!< 左に向かって伸びている光の扉
		BELT_CONVER_B_L,					//!< 左向きに進むベルトコンベアブロック
		BELT_CONVER_B_R,					//!< 右向きに進むベルトコンベアブロック
		SPEAR_B,							//!< 槍ブロック
		SPEAR,								//!< 槍
		LIGHT_B,							//!< 光ブロック
		ANCHOR,								//!< アンカー
		PLAYER = 99,						//!< プレイヤー
		ID_MAX,
		TYPE_ERROR = -1,					//!< エラー番号
	};

	/**  
	* Constructor
	* @attention 位置座標はStage::INDEX_DATAから継承クラスごとに設定すること
	* @param[in] pStageDataManager	StageDataManagerクラスのインスタンスへのポインタ
	* @param[in] pCollisionManager	CollisionManagerクラスのインスタンスへのポインタ
	* @param[in] rStageIndexData	ステージインデックスデータ
	*/
	ObjBase(StageDataManager* pStageDataManager, CollisionManager* pCollisionManager
			, const Stage::INDEX_DATA& rStageIndexData);

	/** Destructor */
	virtual ~ObjBase(void);

	/** 
	* ステージの位置を変更する関数. 純粋仮想関数
	* @param[in] yIndexNum	y軸方向のインデックス
	* @param[in] xIndexNum  x軸方向のインデックス
	*/
	virtual void ChangeStagePos(short yIndexNum, short xIndexNum) = 0;

	/**
	* 衝突処理関数.純粋仮想関数 
	* @param[in] rData 衝突判定に関連するデータ
	*/ 
	virtual void ProcessCollision(const CollisionManager::CollisionData& rData) = 0;

	/** 
	* Getter 位置座標を取得する関数
	* @return 位置座標
	*/
	const sl::SLVECTOR2& GetPos(void) const { return m_Pos; }

	/** 
	* Getter 矩形サイズを取得する関数
	* @return 矩形サイズ
	*/
	const sl::fRect& GetRectSize(void) { return m_RectSize; }

	/** 
	* Getter 現在の矩形データ(位置座標 + 基本矩形サイズ)を取得する関数
	* 中で現在の矩形データを計算して返す処理
	* @return 現在の矩形データ
	*/
	const sl::fRect& GetCurrentRectData(void);

	/** 
	* Getter 現在のステージのインデックスデータを取得する関数
	* @return ステージのインデックスデータ
	*/
	const Stage::INDEX_DATA& GetStageIndex(void) const { return m_StageIndexData; }

	/** 
	* Getter オブジェクトのタイプを取得する関数
	* @return オブジェクトのタイプ
	*/
	TYPE_ID GetTypeID(void) const { return m_TypeID; }

	/** 
	* Getter オブジェクトの描画IDを取得する関数
	* @return 描画ID
	*/
	sl::DrawingID	GetDrawingID(void)const { return m_DrawingID; }

	/** 
	* Setter ステージのインデックスデータを取得する関数
	* @param[in] rStageIndexData
	*/
	void SetStageIndex(const Stage::INDEX_DATA& rStageIndexData){ m_StageIndexData = rStageIndexData; }

	/** 
	* Setter ステージのチップサイズをセットする関数.static
	* @param[in]  stageChipSize ステージチップのサイズ
	*/
	static void SetStageChipSize(float stageChipSize) { m_StageChipSize = stageChipSize; }

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
	static	float			m_StageChipSize;				//!< ステージチップ1つのサイズ

	sl::ISharokuLibrary*	m_pLibrary;						//!< sl::ISharokuLibrary*クラスのインスタンスへのポインタ
	sl::SLVECTOR2			m_Pos;							//!< 位置座標
	Stage::INDEX_DATA		m_StageIndexData;				//!< 現在登録しているステージのインデックスデータ
	sl::fRect				m_RectSize;						//!< 基本矩形サイズ
	sl::fRect				m_CurrentRectData;				//!< 位置座標 + 基本矩形サイズ
	sl::DrawingID			m_DrawingID;					//!< 描画関連のIDをまとめた群
	TYPE_ID					m_TypeID;						//!< オブジェクトのタイプID
	EventLisner*			m_pEventLisner;					//!< EventLisnerクラスのインスタンスへのポインタ
	StageDataManager*		m_pStageDataManager;			//!< StageDataManagerクラスのインスタンスへのポインタ
	CollisionManager*		m_pCollisionManager;			//!< CollisionManagerクラスのインスタンスへのポインタ

	/** 
	* イベント処理関数.純粋仮想関数 
	* この関数内でEventLisnerから受け取ったイベントの処理を行う
	*/
	virtual void HandleEvent(void) = 0;

};	// class ObjBase

}	// namespace ar

#endif	// AR_OBJBASE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
