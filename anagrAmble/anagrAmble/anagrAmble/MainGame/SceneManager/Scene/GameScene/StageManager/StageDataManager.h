//==================================================================================================================================//
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
	void SaveStageOriginData(void);

	/**
	* StockStageDataに現在のステージデータを加える関数
	* ステージを入れ替える際によぶ
	*/
	void AddStockStageData(void);

	/**
	* 現在のステージデータを1つ入れ替える前のデータに戻す関数
	* ステージを1つ前に戻す際によぶ
	* @return 結果 true→成功  false→失敗
	*/
	bool ReturnBeforeCurrentStageData(void);

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
	* Getter. ステージの横のチップ数を取得する関数
	* @return ステージの横のチップ数
	*/
	inline short GetStageWidthChipNum(void) { return m_StageWidthChipNum; }

	/**
	* Getter. ステージの高さのチップ数を取得する関数
	* @return ステージの高さのチップ数
	*/
	inline short GetStageHeightChipNum(void) { return m_StageHeightChipNum; }

	/**
	* Getter.ステージの背景のテクスチャーファイル名を取得する関数
	* @return ステージ背景のテクスチャーファイル名
	*/
	inline const std::string&	GetBackGoundTexFileName(void) { return m_BackGoundTexFileName; }

	/**
	* Getter. 指定したｲﾝデックスからそこに存在するオブジェクトを取得する関数
	* @param[in] indexY y方向のインデックス
	* @param[in] indexX	x方向のインデックス
	* @return 引数のインデックスに存在するオブジェクトID.
	* インデックスがステージの範囲外を指定していたら0(空白)を返す
	*/
	int GetTypeID(int indexY, int indexX);

	/**
	* Getter. 指定したｲﾝデックスからそこに存在するオブジェクトのポインタを取得する関数
	* その地点が空白、もしくはエラーの場合はnullptrがかえってくる
	* @param[in] indexY y方向のインデックス
	* @param[in] indexX	x方向のインデックス
	*/
	 ObjBase* const GetObjBasePointer(int indexY, int indexX);

	/**
	* Setter. 現在のステージデータにインデックスのデータをセットする関数
	* @param[in] indexY y方向のインデックス
	* @param[in] indexX	x方向のインデックス
	* @param[in] pObj	上記のインデックスにあるObjBaseクラスのインスタンスへのポインタ
	*/
	void SetCurrentStageChipData(int indexY, int indexX, ObjBase* pObj = nullptr);

	/**
	* Setter. ステージデータのストックの最新データにインデックスのデータをセットする関数
	* 入れ替え処理を行った後にインデックスデータを変更したい場合に使用する
	* @param[in] indexY y方向のインデックス
	* @param[in] indexX	x方向のインデックス
	* @param[in] pObj	上記のインデックスにあるObjBaseクラスのインスタンスへのポインタ
	*/
	void SetNewStockStageChipData(int indexY, int indexX, ObjBase* pObj);

private:
	static const int									m_StockStageDataOrderCount;	//!< m_StockStageDataのデータ数

	GameDataManager*									m_pGameDataManager;			//!< GameDataManagerクラスのインスタンスへのポインタ
	float												m_StageWidth;				//!< ステージチップの横の長さ
	float												m_StageHeight;				//!< ステージチップの縦の長さ
	float												m_StageChipSize;			//!< ステージチップのサイズ
	short												m_StageWidthChipNum;		//!< ステージチップの横の数
	short												m_StageHeightChipNum;		//!< ステージチップの縦の数
	std::vector<std::vector<short>>						m_LoadStageIndexData;		//!< ファイルからロードしたステージのインデックスデータを格納する二次元配列(vector)
	std::vector<std::vector<ObjBase*>>					m_StageOriginData;			//!< 今回のステージの元データを格納する二次元配列(vector)
	std::vector<std::vector<ObjBase*>>					m_CurrentStageData;			//!< 現在のステージデータを格納する二次元配列(vector)
	std::vector<int>									m_StockStageDataOrder;		//!< ストックしているステージデータの順番
	std::vector<std::vector<std::vector<ObjBase*>>>		m_StockStageData;			//!< ストックしているステージデータを格納する三次元配列(vector)
	std::string											m_BackGoundTexFileName;		//!< ステージ背景のテクスチャーファイル名

	

};	// class StageDataManager

}	// namespace ar

#endif	// AR_STAGE_DATA_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
