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

int DirectSoundManager::LoadSound(TCHAR* pFilePath)
{
	LPDIRECTSOUNDBUFFER8 pDSBuffer = NULL;

	// Waveファイルオープン
	char *pWaveData = 0;
	DWORD waveSize = 0;

	if(!OpenWave((pFilePath), &m_WFmt, &pWaveData, &waveSize))
	{
		MessageBox(0, "WAVEファイルオープンに失敗しました。", NULL, MB_OK);
		return INT_MAX;
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
	ptmpBuf->QueryInterface(IID_IDirectSoundBuffer8, (void**)&pDSBuffer);

	ptmpBuf->Release();
	if (pDSBuffer == NULL)
	{
		m_pDSound8->Release();
		MessageBox(0, "WAVEファイルオープンに失敗しました。", NULL, MB_OK);
		return INT_MAX;
	}

	// セカンダリバッファにWaveデータ書き込み
	{
		//音声データ
		LPVOID lpvWrite = 0;
		//音声データの大きさ
		DWORD dwLength = 0;
		if(DS_OK == pDSBuffer->Lock(0, 0, &lpvWrite, &dwLength, NULL, NULL, DSBLOCK_ENTIREBUFFER))
		{
			memcpy(lpvWrite, pWaveData, dwLength);
			pDSBuffer->Unlock(lpvWrite, dwLength, NULL, 0);
		}
	}

	delete[] pWaveData; // 元音はもういらない

	int id = m_Sounds.size();		// 登録キー

	m_Sounds.push_back(pDSBuffer);

	return id;
}

void DirectSoundManager::PlayBackSound(int id, int soundMode)
{
	switch (soundMode)
	{
	case PLAY:
		m_Sounds[id]->Play(0, 0, 0);
		break;
	case PLAYLOOP:
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
	m_Sounds[id]->Release();
	m_Sounds[id] = NULL;
}

void DirectSoundManager::ReleaseALL(void)
{
	for(auto& itr = m_Sounds.begin(); itr != m_Sounds.end(); ++itr)
	{
		if((*itr) != NULL)
		{
			(*itr)->Release();
			(*itr) = NULL;
		}
	}

	std::vector<LPDIRECTSOUNDBUFFER8>().swap(m_Sounds);
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
