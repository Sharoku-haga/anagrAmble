//==================================================================================================================================//
//!< @file		StageDataChangeManager.h
//!< @brief		ar::StageDataChangeManagerクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_STAGE_DATA_CHANGE_MANAGER_H
#define AR_STAGE_DATA_CHANGE_MANAGER_H

#include <vector>
#include "../SharokuLibrary/sl/sl.h"
#include "Stage/Stage.h"

namespace ar
{

class ObjBase;
class Player;
class StageDataManager;

//======================================================================//
//!< ステージデータの入れ替え操作を管理するクラス
//!< シングルトンパターン
//======================================================================//
class StageDataChangeManager
{

public:
	/***
	* 実体取得関数
	* @return StageDataChangeManagerクラスのインスタンス
	*/
	static StageDataChangeManager& Instance(void)
	{
		static StageDataChangeManager stageDataChangeManager;
		return stageDataChangeManager;
	}

	/** 
	* 初期化関数
	* StageDataManagerクラスのインスタンスを生成したらよぶ
	* @param[in] pStageDataManager StageDataManagerクラスのインスタンスへのポインタ
	*/
	void InitialIze(StageDataManager* pStageDataManager);

	/**
	* スペース入れ替え処理を行う関数
	* Stageクラス内でよぶ関数
	* @return 結果 true→入れ替え成功、 false→失敗
	*/
	bool ChangeSpace(void);

	/**
	* 入れ替えたスペースを元に戻す処理を行う関数
	* Stageクラス内でよぶ関数
	* @return 結果 true→処理終了、 false→処理継続
	*/
	bool ReturnChangedSpace(void);

	/**
	* 現在のステージデータを前のデータに戻す処理を行う関数
	* Stageクラス内でよぶ関数
	* @return 結果 true→処理終了、 false→処理継続
	*/
	bool ReturnBeforeStageData(void);

	/**
	* Setter.挟んだ空間の開始インデックスデータをセットする関数
	* @param[in] rSandwichedSpaceStartIndex  挟んだ空間の開始インデックスデータ
	*/
	inline void SetSandwichedSpaceStartIndex(const Stage::INDEX_DATA&	rSandwichedSpaceStartIndex) 
	{ 
		m_SandwichedSpaceStartIndex = rSandwichedSpaceStartIndex; 
	}

	/**
	* Setter.挟んだ空間の終了インデックスデータをセットする関数
	* @param[in] rSandwichedSpaceEndIndex  挟んだ空間の終了インデックスデータ
	*/
	inline void SetSandwichedSpaceEndIndex(const Stage::INDEX_DATA&		rSandwichedSpaceEndIndex) 
	{ 
		m_SandwichedSpaceEndIndex = rSandwichedSpaceEndIndex;
	}

	/**
	* Setter. Playerクラスのインスタンスへのポインタをセットする関数
	* @param[in] pPlayer Playerクラスのインスタンスへのポインタ
	*/
	inline void SetPlayerPointer(Player* pPlayer) { m_pPlayer = pPlayer; }
	
	/** Destructor */
	~StageDataChangeManager(void) = default;

private:
	/** 入れ替えに使用するデータ構造体 */
	struct ChangeData
	{
		short				m_XIndexNum;		//!< X軸方向のインデックス番号
		short				m_YIndexNum;		//!< Y軸方向のインデックス番号
		ObjBase*			m_pObj;				//!< 上記の番号の場所にあるObjbaseポインタ
	};

	StageDataManager*			m_pStageDataManager;				//!< StageDataManagerクラスのインスタンスへのポインタ
	Stage::INDEX_DATA			m_SandwichedSpaceStartIndex;		//!< 挟んだ空間の開始地点のインデックスデータ
	Stage::INDEX_DATA			m_SandwichedSpaceEndIndex;			//!< 挟んだ空間の終了地点のインデックスデータ
	Player*						m_pPlayer;							//!< Playerクラスのインスタンスへのポインタ
	float						m_StageMapChipSize;					//!< ステージのチップサイズ
	int							m_WhiteOutTimeCount;				//!< ホワイトアウトの時間のカウント数

	/**
	* 入れ替えたい空間の開始地点のインデックスデータを計算する関数
	* プレイヤー座標と向いている方向から求める
	* @return 入れ替えたい空間の開始地点のインデックスデータ
	*/
	Stage::INDEX_DATA CalculateChangeStartIndex(void);

	/**
	* ステージデータを入れ替えを行う関数
	* @param[in] changeSpaceYCount		入れ替え空間のチップの横の数
	* @param[in] changeSpaceXCount		入れ替え空間のチップの縦の数
	* @param[in] rChangeStartIndexData	入れ替え空間の開始インデックスデータ
	* @param[in] rChangingStageData		入れ替え空間のステージデータ
	*/
	void ChangeStageData(short changeSpaceYCount
						, short changeSpaceXCount
						, Stage::INDEX_DATA&	rChangeStartIndexData
						, std::vector<std::vector<ChangeData>>& rChangingStageData);

	/** Constructor */
	StageDataChangeManager(void) = default;

	/** コピー禁止 */	
	SL_DISALLOW_COPY_AND_ASSIGN(StageDataChangeManager);
	
};	// class StageDataChangeManager

}	// namespace ar

#endif	// AR_STAGE_DATA_CHANGE_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
