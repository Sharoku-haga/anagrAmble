//==================================================================================================================================//
//!< @file		DirectSoundManager.h
//!< @brief		sl::DirectSoundManagerクラスヘッダ
//!< @author	T.Haga
//==================================================================================================================================//

#ifndef SL_DIRECT_SOUND_MANAGER_H
#define SL_DIRECT_SOUND_MANAGER_H

#include <windows.h>
#include <mmsystem.h>
#include <vector>
#include <dsound.h>

namespace sl
{

//======================================================================//
//!< DirectSoundを使用したサウンド管理クラス
//======================================================================//
class DirectSoundManager
{

public:
	/** Constructor */
	DirectSoundManager(void);

	/** Destructor */
	~DirectSoundManager(void);

	/**
	* 初期化関数
	* @param[in] hWnd ウィンドウハンドル
	*/
	void Initialize(HWND hWnd);

	/**
	* 音楽を読み込む関数.
	* @param[in]	pFilepath	音楽ファイル名
	* @return		登録したID もし読み込みに失敗した場合はINT_MAXが返ってくる
	*/
	int LoadSound(TCHAR* pFilePath);

	/**
	* 音を再生する関数
	* @param[in]	id				登録したID
	* @param[in]	soundMode		音楽の再生方式
	*/
	void PlayBackSound(int id, int soundMode); 

	/**
	* 登録しているサウンドを解放関数
	* @param[in] id 登録したID
	*/
	void Release(int id);

	/** 登録しているサウンド全てを解放する関数 */
	void ReleaseALL(void);

private:
	static	WAVEFORMATEX						m_WFmt;				//!< WAVEオーディオデータのフォーマット情報

	IDirectSound8*								m_pDSound8;			//!< DirectSoundのインターフェイス
	std::vector<LPDIRECTSOUNDBUFFER8>			m_Sounds;			//!< サウンドを格納する動的配列

	/**
	* WAVEファイルオープン関数.
	* @param[in]	pFilepath		音楽ファイル名
	* @param[out]   pWaveFormatEx	waveフォーマット
	* @param[out]	pWaveData		waveデータ
	* @param[out]	pDataSize		データサイズ
	* @retval	true	waveファイルオープン成功
	* @retval	false	waveファイルオープン失敗
	*/
	bool OpenWave(TCHAR* pFilepath, WAVEFORMATEX* pWaveFormatEx, char** pWaveData, DWORD* pDataSize);

};	// class DirectSoundManager

}	// namespace sl

#endif	// SL_DIRECT_SOUND_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
