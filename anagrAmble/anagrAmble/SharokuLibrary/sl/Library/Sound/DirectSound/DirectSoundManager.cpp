//==================================================================================================================================//
//!< @file		DirectSoundManager.cpp
//!< @brief		sl::DirectSoundManagerクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "DirectSoundManager.h"
#include "../../../Common/slTemplate.h"
#include "../../../Common/slSoundEnum.h"

namespace sl
{

/* Static Variable -------------------------------------------------------------------------------------------- */

WAVEFORMATEX				DirectSoundManager::m_WFmt;	

/* Public Functions ------------------------------------------------------------------------------------------- */

DirectSoundManager::DirectSoundManager(void)
	: m_pDSound8(NULL)
{}

DirectSoundManager::~DirectSoundManager(void)
{
	ReleaseALL();
	ReleaseSafely(m_pDSound8);
}

void DirectSoundManager::Initialize(HWND hWnd)
{
	DirectSoundCreate8(NULL, &m_pDSound8, NULL);
	// 協調レベル設定
	m_pDSound8->SetCooperativeLevel(hWnd, DSSCL_NORMAL);
}

bool DirectSoundManager::LoadSound(int id, TCHAR* pFilePath)
{
	LPDIRECTSOUNDBUFFER8 pDSBuffer = NULL;
	m_Sounds[id] = pDSBuffer;

	// Waveファイルオープン
	char *pWaveData = 0;
	DWORD waveSize = 0;

	if(!OpenWave((pFilePath), &m_WFmt, &pWaveData, &waveSize))
	{
		MessageBox(0, "WAVEファイルオープンに失敗しました。", NULL, MB_OK);
		return false;
	}

	DSBUFFERDESC DSBufferDesc;
	DSBufferDesc.dwSize				= sizeof(DSBUFFERDESC);
	DSBufferDesc.dwFlags			= 0;
	DSBufferDesc.dwBufferBytes		= waveSize;
	DSBufferDesc.dwReserved			= 0;
	DSBufferDesc.lpwfxFormat		= &m_WFmt;
	DSBufferDesc.guid3DAlgorithm	= GUID_NULL;

	IDirectSoundBuffer *ptmpBuf = 0;
	m_pDSound8->CreateSoundBuffer(&DSBufferDesc, &ptmpBuf, NULL);
	ptmpBuf->QueryInterface(IID_IDirectSoundBuffer8, (void**)&m_Sounds[id]);

	ptmpBuf->Release();
	if (m_Sounds[id] == NULL)
	{
		m_pDSound8->Release();
		MessageBox(0, "WAVEファイルオープンに失敗しました。", NULL, MB_OK);
		return false;
	}

	// セカンダリバッファにWaveデータ書き込み
	{
		//音声データ
		LPVOID lpvWrite = 0;
		//音声データの大きさ
		DWORD dwLength = 0;
		if(DS_OK == m_Sounds[id]->Lock(0, 0, &lpvWrite, &dwLength, NULL, NULL, DSBLOCK_ENTIREBUFFER))
		{
			memcpy(lpvWrite, pWaveData, dwLength);
			m_Sounds[id]->Unlock(lpvWrite, dwLength, NULL, 0);
		}
	}

	delete[] pWaveData; // 元音はもういらない

	return true;
}

void DirectSoundManager::PlayBackSound(int id, int soundMode)
{
	switch (soundMode)
	{
	case PLAY:
		m_Sounds[id]->Play(0, 0, 0);
		break;
	case PLAY_LOOP:
		m_Sounds[id]->Play(0, 0, DSBPLAY_LOOPING);
		break;
	case STOP:
		m_Sounds[id]->Stop();
		break;
	case RESET:
		m_Sounds[id]->SetCurrentPosition(0);
		break;
	case STOP_RESET:
		m_Sounds[id]->Stop();
		m_Sounds[id]->SetCurrentPosition(0);
		break;
	case RESET_PLAY:
		m_Sounds[id]->SetCurrentPosition(0);
		m_Sounds[id]->Play(0, 0, 0);
		break;

	default:
		// do nothing
		break;
	}
}

void DirectSoundManager::Release(int id)
{
	if(m_Sounds[id] != NULL)
	{
		m_Sounds[id]->Release();
		m_Sounds[id] = NULL;
	}
}

void DirectSoundManager::ReleaseALL(void)
{
	for(auto& itr = m_Sounds.begin(); itr != m_Sounds.end(); ++itr)
	{
		if (itr->second)
		{
			itr->second->Release();
			itr->second = NULL;
		}
	}

	m_Sounds.clear();
}

/* Private Functions ------------------------------------------------------------------------------------------ */

bool DirectSoundManager::OpenWave(TCHAR* pFilepath, WAVEFORMATEX* pWaveFormatEx, char** pWaveData, DWORD* pDataSize)
{
	if (pFilepath == 0)
		return false;

	HMMIO hMmio = NULL;
	MMIOINFO mmioInfo;

	// waveファイルオープン
	memset(&mmioInfo, 0, sizeof(MMIOINFO));
	hMmio = mmioOpen(pFilepath, &mmioInfo, MMIO_READ);
	if(!hMmio)
		return false; // ファイルオープン失敗

	// RIFFチャンク検索
	MMRESULT mmRes;
	MMCKINFO riffChunk;
	riffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	mmRes = mmioDescend(hMmio, &riffChunk, NULL, MMIO_FINDRIFF);
	if(mmRes != MMSYSERR_NOERROR) {
		mmioClose(hMmio, 0);
		return false;
	}

	// フォーマットチャンク検索
	MMCKINFO formatChunk;
	formatChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmRes = mmioDescend(hMmio, &formatChunk, &riffChunk, MMIO_FINDCHUNK);
	if(mmRes != MMSYSERR_NOERROR) {
		mmioClose(hMmio, 0);
		return false;
	}
	DWORD fmsize = formatChunk.cksize;
	DWORD size = mmioRead(hMmio, (HPSTR)pWaveFormatEx, fmsize);
	if(size != fmsize) {
		mmioClose(hMmio, 0);
		return false;
	}

	mmioAscend(hMmio, &formatChunk, 0);

	// データチャンク検索
	MMCKINFO dataChunk;
	dataChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmRes = mmioDescend(hMmio, &dataChunk, &riffChunk, MMIO_FINDCHUNK);
	if(mmRes != MMSYSERR_NOERROR) {
		mmioClose(hMmio, 0);
		return false;
	}
	*pWaveData = new char[dataChunk.cksize];
	size = mmioRead(hMmio, (HPSTR)*pWaveData, dataChunk.cksize);
	if(size != dataChunk.cksize) {
		delete[] *pWaveData;
		return false;
	}
	*pDataSize = size;

	// ハンドルクローズ
	mmioClose(hMmio, 0);

	return true;
}

}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
