//==================================================================================================================================//
//!< @file		CommonSoundManager.h
//!< @brief		ar::CommonSoundManagerクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef SL_COMMON_SOUND_MANAGER_H
#define SL_COMMON_SOUND_MANAGER_H

#include <vector>
#include "../SharokuLibrary/sl/sl.h"

namespace ar
{

//======================================================================//
//!< ゲーム内にて共通で使用するサウンドを管理するクラス
//!< シングルトンパターン
//======================================================================//
class CommonSoundManager
{

public:
	/** 共通サウンド登録用ID */
	enum SOUND_ID 
	{
		SELECT	= 98,	//!< 選択音
		ENTER	= 99	//!< 決定音
	};

	/**
	* インスタンスを取得する関数
	* @return インスタンスへの参照
	*/
	static CommonSoundManager& Instance(void)
	{
		static CommonSoundManager soundManager;
		return soundManager;
	}

	/** 
	* 初期化関数
	* @attention このクラスを使用する前に必ずよぶこと
	*/
	void Initialize(void);

	/** 
	* サウンドをファイルからロードする関数
	* @param[in] id				登録するID
	* @param[in] pFilePath		ファイルパス
	*/
	void LoadSound(int id, char* pFilePath);

	/**
	* サウンドを再生する関数
	* @param[in] id			登録したサウンドID
	* @param[in] soundMode	サウンドの再生モード.種類に関してはライブラリを確認すること
	*/
	void PlayBackSound(int id, int soundMode);

	/** 登録した音を全て解放する関数 */
	void ReleaseSoundALL(void);

private:
	sl::ISharokuLibrary*	m_pLibrary;				//!< sl::ISharokuLibraryクラスのインスタンスへのポインタ
	std::vector<int>		m_SoundID;				//!< 共通で使用するサウンドの登録IDを保持しているコンテナ

	/** Constructor */
	CommonSoundManager(void) = default ;

	/** Destructor*/
	~CommonSoundManager(void);

}; // class CommonSoundManager

}	// namespace ar

#endif	// SL_COMMON_SOUND_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
