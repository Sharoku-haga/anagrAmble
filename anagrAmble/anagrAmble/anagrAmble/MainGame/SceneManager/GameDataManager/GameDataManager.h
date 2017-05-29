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
//!< @todo 2017/05/29時点はまだ完全実装していない
//======================================================================//
class GameDataManager
{

public:
	/** Constructor */
	GameDataManager(void);

	/** Destructor */
	~GameDataManager(void);

	/**
	* Getter.選択しているステージ名を取得する関数
	* @return 選択しているステージ名
	*/
	inline std::string	GetSelectStageName(void) { return m_SelectStageName; }

	/**
	* Setter.選択しているステージ名をセットする関数
	* @param[in] rStageName セットしたいステージ名
	*/
	inline void	SetSelectStageName(const std::string& rStageName) { m_SelectStageName = rStageName; }

private:
	std::string		m_SelectStageName;		//!< 選択しているステージ名

};	// class GameDataManager

} // namespace ar

#endif // AR_GAME_DATA_MANAGER_H


//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
