﻿//==================================================================================================================================//
//!< @file		StageDataManager.h
//!< @brief		ar::StageDataManagerクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_STAGE_DATA_MANAGER_H
#define AR_STAGE_DATA_MANAGER_H

#include <vector>
#include <deque>
#include <string>

namespace ar
{

class GameDataManager;
class ObjBase;

//======================================================================//
//!< ステージ関連のデータを管理するクラス
//======================================================================//
class StageDataManager
{

public:
	/** 
	* Constructor 
	* @param[in] pGameDataManager GameDataManagerクラスのインスタンスへのポインタ
	*/
	StageDataManager(GameDataManager* pGameDataManager);

	/** Destructor */
	~StageDataManager(void);

	/** 
	* ファイルからマップデータをロードする関数
	* @return 結果 true→成功, false→失敗
	*/
	bool LoadDataFile(void);

	/**
	* ステージのオリジナルデータを保存する関数
	* StageManagerの初期化がすべて終わったらよぶ
	*/
	void SaveStageOriginalData(void);

	/** 
	* リスポーンステージデータをセーブする関数
	* StageManagerの初期化か、プレイヤーが一定値に達したらよばれる
	*/
	void SaveRespawnStageData(void);

	/**
	* StockStageDataに現在のステージデータを加える関数
	* ステージを入れ替える際によぶ
	*/
	void AddStockStageData(void);

	/**
	* リスポーンステージデータに戻す関数
	* リスポーンステージデータがない場合は開始地点のステージデータにもどす
	* @return 結果 true→成功  false→失敗
	*/
	void ReturnmRespawnStageData(void);

	/**
	* 変更前(入れ替え前)のステージデータに戻す関数
	* @return 結果 true→成功  false→失敗
	*/
	void ReturnStageDataChangeBefore(void);

	/**
	* ストックデータ存在するかどうか確認する関数
	* @return 結果 true→存在する  false→存在しない
	*/
	bool ExistStockStageData(void);

	/**
	* Getter. ファイルからロードしたステージデータへの参照を取得する関数
	* @return ファイルからロードしたステージデータ
	*/
	const std::vector<std:: vector<short>>& GetLoadStageData() { return m_LoadStageIndexData; }

	/**
	* Getter. ステージチップのサイズを取得する関数
	* @return ステージチップのサイズ
	*/
	inline float GetStageChipSize(void) { return m_StageChipSize; }

	/**
	* Getter.ステージの横の長さを取得する関数
	* @return ステージの横の長さ
	*/
	inline float GetStageWidth(void) { return m_StageWidth; }

	/**
	* Getter.ステージの縦の長さを取得する関数
	* @return ステージの縦の長さ
	*/
	inline float GetStageHeight(void) { return m_StageHeight; }

	/**
	* Getter. ステージの横のチップ数を取得する関数
	* @return ステージの横のチップ数
	*/
	inline short GetStageWidthChipCount(void) { return m_StageWidthChipCount; }

	/**
	* Getter. ステージの高さのチップ数を取得する関数
	* @return ステージの高さのチップ数
	*/
	inline short GetStageHeightChipCount(void) { return m_StageHeightChipCount; }

	/**
	* Getter.ステージの背景のテクスチャーファイル名を取得する関数
	* @return ステージ背景のテクスチャーファイル名
	*/
	inline const std::string&	GetBackGoundTexFileName(void) { return m_BackGoundTexFileName; }

	/**
	* Getter. 指定したｲﾝデックスからそこに存在するオブジェクトを取得する関数
	* @param[in] yIndexNum  y方向のインデックス番号
	* @param[in] xIndexNum	x方向のインデックス番号
	* @return 引数のインデックスに存在するオブジェクトID.
	* インデックスがステージの範囲外を指定していたら0(空白)を返す
	*/
	int GetTypeID(int yIndexNum, int xIndexNum);

	/**
	* Getter. 指定したｲﾝデックスからそこに現在存在するオブジェクトのポインタを取得する関数
	* その地点が空白、もしくはエラーの場合はnullptrがかえってくる
	* @param[in] yIndexNum y方向のインデックス番号
	* @param[in] xIndexNum	x方向のインデックス番号
	* @return 指定したインデックス番号に存在するオブジェクトのポインタ
	*/
	 ObjBase* const GetObjBasePointer(int yIndexNum, int xIndexNum);

	/**
	* Setter. 現在のステージデータにインデックスのデータをセットする関数
	* @param[in] yIndexNum y方向のインデックス番号
	* @param[in] xIndexNum	x方向のインデックス番号
	* @param[in] pObj	上記のインデックスにあるObjBaseクラスのインスタンスへのポインタ
	*/
	void SetCurrentStageChipData(int yIndexNum, int xIndexNum, ObjBase* pObj = nullptr);

	/**
	* Setter. ステージデータのストックの最新データにインデックスのデータをセットする関数
	* 入れ替え処理を行った後にインデックスデータを変更したい場合に使用する
	* @param[in] yIndexNum  y方向のインデックス番号
	* @param[in] xIndexNum	x方向のインデックス番号
	* @param[in] pObj	上記のインデックスにあるObjBaseクラスのインスタンスへのポインタ
	*/
	void SetNewStockStageChipData(int yIndexNum, int xIndexNum, ObjBase* pObj);

private:
	static const int									m_StockStageDataOrderCount;	//!< m_StockStageDataのデータ数

	GameDataManager*									m_pGameDataManager;			//!< GameDataManagerクラスのインスタンスへのポインタ
	float												m_StageWidth;				//!< ステージチップの横の長さ
	float												m_StageHeight;				//!< ステージチップの縦の長さ
	float												m_StageChipSize;			//!< ステージチップのサイズ
	short												m_StageWidthChipCount;		//!< ステージチップの横の数
	short												m_StageHeightChipCount;		//!< ステージチップの縦の数
	std::vector<std::vector<short>>						m_LoadStageIndexData;		//!< ファイルからロードしたステージのインデックスデータを格納する二次元配列(vector)
	std::vector<std::vector<ObjBase*>>					m_StageOriginalData;		//!< 今回のステージの元データを格納する二次元配列(vector)
	std::vector<std::vector<ObjBase*>>					m_RespawnStageData;			//!< リスポーンするステージのデータを格納する二次元配列(vector)
	std::vector<std::vector<ObjBase*>>					m_CurrentStageData;			//!< 現在のステージデータを格納する二次元配列(vector)
	std::vector<int>									m_StockStageDataOrder;		//!< ストックしているステージデータの順番
	std::vector<std::vector<std::vector<ObjBase*>>>		m_StockStageData;			//!< ストックしているステージデータを格納する三次元配列(vector)
	std::string											m_BackGoundTexFileName;		//!< ステージ背景のテクスチャーファイル名

	/**
	* 引数のインデックス番号がステージの範囲内に存在するかどうか確認する関数
	* @param[in] yIndexNum  y方向のインデックス番号
	* @param[in] xIndexNum	x方向のインデックス番号
	* @return 結果 true→存在する false→存在しない
	*/
	bool ExistsIndexNum(int yIndexNum, int xIndexNum);

};	// class StageDataManager

}	// namespace ar

#endif	// AR_STAGE_DATA_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
