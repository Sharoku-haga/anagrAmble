//==================================================================================================================================//
//!< @file		StageDataManager.h
//!< @brief		ar::StageDataManagerクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_STAGE_DATA_MANAGER_H
#define AR_STAGE_DATA_MANAGER_H

#include <vector>
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
	* ファイルからロードしたステージデータを取得する関数
	* @return ファイルからロードしたステージデータ
	*/
	const std::vector<std::vector<short>>& GetLoadStageData() { return m_LoadStageData; }

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

private:
	/** ステージチップ1つのデータ構造体 */
	struct StageChipData
	{
		short			m_YNum;		//!< Y軸のインデックス
		short			m_XNum;		//!< X軸のインデックス
		ObjBase*		m_pObj;		//!< チップに存在するOBJBaseクラスのインスタンスへのポインタ
	};

	GameDataManager*					m_pGameDataManager;			//!< GameDataManagerクラスのインスタンスへのポインタ
	float								m_StageWidth;				//!< ステージチップの横の長さ
	float								m_StageHeight;				//!< ステージチップの縦の長さ
	float								m_StageChipSize;			//!< ステージチップのサイズ
	short								m_StageWidthChipNum;		//!< ステージチップの横の数
	short								m_StageHeightChipNum;		//!< ステージチップの縦の数
	std::vector<std::vector<short>>		m_LoadStageData;			//!< ファイルからロードしたステージデータを格納する二次元配列(vector)
	std::vector<std::vector<short>>		m_CuurentStageData;			//!< 現在のステージデータを格納する二次元配列(vector)
	std::string							m_BackGoundTexFileName;		//!< ステージ背景のテクスチャーファイル名

};	// class StageDataManager

}	// namespace ar

#endif	// AR_STAGE_DATA_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
