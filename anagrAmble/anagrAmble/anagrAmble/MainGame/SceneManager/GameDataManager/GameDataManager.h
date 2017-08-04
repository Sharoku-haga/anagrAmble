//==================================================================================================================================//
//!< @file		GameDataManager.h
//!< @brief		ar::GameDataManagerクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef AR_GAME_DATA_MANAGER_H
#define AR_GAME_DATA_MANAGER_H

#include <string>

namespace ar
{

//======================================================================//
//!< ゲームデータを管理するクラス
//======================================================================//
class GameDataManager
{

public:
	/** Constructor */
	GameDataManager(void);

	/** Destructor */
	~GameDataManager(void) = default;

	/** 初期化関数 */
	void Initialize(void);

	/** ゲームクリア処理関数 */
	void ProcessGameClear(void);

	/**
	* Getter.選択しているステージ名を取得する関数
	* @return 選択しているステージ名
	*/
	inline std::string	GetSelectStageName(void) { return m_SelectStageName; }

	/**
	* Getter.ハイスコアを取得する関数
	* @return ハイスコアゲーム時間
	*/
	inline unsigned long GetHighScoreTime(void) { return m_HighScoreTime; }

	/**
	* Getter.今回のスコア時間を取得する関数
	* @return プレイしたゲーム時間
	*/
	inline unsigned long GetThisScoreTime(void) { return m_ThisScoreTime; }

	/**
	* Setter 今回のスコア時間をセットする関数
	* @param[in] thisPlayedGameTime 今回プレイしたゲーム時間
	*/
	inline void SetThisScoreTime(unsigned long thisScoreTime) { m_ThisScoreTime = thisScoreTime; }

	/**
	* Setter.選択しているステージ名をセットする関数
	* @param[in] rStageName セットしたいステージ名
	*/
	inline void	SetSelectStageName(const std::string& rStageName) { m_SelectStageName = rStageName; }

private:
	std::string		m_SelectStageName;		//!< 選択しているステージ名
	unsigned long	m_ThisScoreTime;		//!< 今回のスコア時間(ゲームをプレイするごとに変動する)
	unsigned long	m_HighScoreTime;		//!< 現在のハイスコア

	/** ハイスコアデータを読み込む関数 */
	void LoadHighScoreData(void);

	/** ハイスコアデータをセーブする関数 */
	void SaveHighScoreData(void);

};	// class GameDataManager

} // namespace ar

#endif // AR_GAME_DATA_MANAGER_H


//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
