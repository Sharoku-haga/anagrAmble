//==================================================================================================================================//
//!< @file		slDX11Library.cpp
//!< @brief		sl::DX11Libraryクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "slDX11Library.h"
#include "Window/dx11Window/dx11Window.h"
#include "Graphics/dx11GraphicsDevice/dx11GraphicsDevice.h"
#include "Texture/dx11Texture/dx11TextureManager.h"
#include "Vertex/dx11Vertex/dx11Vertex2DManager.h"
#include "Input/DirectInput/diInputManager.h"
#include "Input/XInput/xiGamePad.h"
#include "Input\slCustomizeInputManager.h"
#include "UVAnimation/slUVAnimationManager.h"
#include "../Common/slTemplate.h"
#include "../slBuild.h"

namespace sl
{

/* Public Functions ------------------------------------------------------------------------------------------- */

DX11Library::DX11Library(void)
	: m_pWindow(nullptr)
	, m_pGraphicsDevice(nullptr)
	, m_pTextureManager(nullptr)
	, m_pVertex2DManager(nullptr)
	, m_pInputManager(nullptr)
	, m_pGamePad(nullptr)
	, m_pCustomizeInputManager(nullptr)
	, m_pUVAnimationManager(nullptr)
{}

DX11Library::~DX11Library(void)
{
	Finalize();
}

void DX11Library::Initialize(t_char*  pWinTitle, int winWidth, int winHeight)
{
	m_pWindow = new dx11::Window();
	m_pWindow->Initialize(pWinTitle, winWidth, winHeight);

	m_pGraphicsDevice = new dx11::GraphicsDevice();
	m_pGraphicsDevice->Initialize(m_pWindow->GetHwnd());

	m_pTextureManager = new dx11::TextureManager(m_pGraphicsDevice->GetDevice(), m_pGraphicsDevice->GetDeviceContext());

	m_pVertex2DManager = new dx11::Vertex2DManager();
	m_pVertex2DManager->Initialize(m_pGraphicsDevice);

	m_pInputManager = new di::InputManager();
	m_pInputManager->Initialize(m_pWindow->GetHwnd());

#ifdef USING_XI_GAMEPAD
	m_pGamePad = new xi::GamePad();
#endif

	m_pCustomizeInputManager = new CustomizeInputManager(m_pInputManager, m_pGamePad);
	m_pUVAnimationManager = new UVAnimationManager();
}

void DX11Library::Finalize(void)
{
	DeleteSafely(&m_pUVAnimationManager);
	DeleteSafely(&m_pCustomizeInputManager);
#ifdef USING_XI_GAMEPAD
	DeleteSafely(&m_pGamePad);
#endif
	DeleteSafely(&m_pInputManager);
	DeleteSafely(&m_pVertex2DManager);
	DeleteSafely(&m_pTextureManager);
	DeleteSafely(&m_pGraphicsDevice);
	DeleteSafely(&m_pWindow);
}

bool DX11Library::UpdateWindow(void)
{
	return m_pWindow->Update();
}

void DX11Library::ChangeWindowMode(bool isFullScreen)
{
	m_pGraphicsDevice->ChangeWindowMode(isFullScreen);
}

fRect DX11Library::GetClientSize(void)
{
	return m_pWindow->GetClientSize();
}

int DX11Library::LoadTexture(const t_char* pFileName)
{
	return m_pTextureManager->LoadTexture(pFileName);
}

void DX11Library::ReleaseTex(int texID)
{
	m_pTextureManager->Release(texID);
}

void DX11Library::ReleaseTexALL(void)
{
	m_pTextureManager->ReleaseALL();
}

int DX11Library::CreateVertex2D(const fRect& rSize, const fRect& rUV)
{
	return m_pVertex2DManager->CreateVertex(rSize, rUV);
}

void DX11Library::SetVtxSize(int vtxID, const fRect& rSize)
{
	m_pVertex2DManager->SetSize(vtxID, rSize);
}

void DX11Library::SetVtxUV(int vtxID, const fRect& rUv)
{
	m_pVertex2DManager->SetUV(vtxID, rUv);
}

void DX11Library::SetVtxColor(int vtxID, float red, float green, float blue, float alpha)
{
	m_pVertex2DManager->SetColor(vtxID, D3DXCOLOR(red, green, blue, alpha));
}

fRect DX11Library::GetSizeRect(int vtxID)
{
	return m_pVertex2DManager->GetSizeRect(vtxID);
}

fRect DX11Library::GetUVRect(int vtxID)
{
	return m_pVertex2DManager->GetUVRect(vtxID);
}

void DX11Library::ReleaseVertex2D(int vtxID)
{
	m_pVertex2DManager->ReleaseVertex2D(vtxID);
}

void DX11Library::ReleaseVertexALL(void)
{
	m_pVertex2DManager->ReleaseALL();
}

int DX11Library::RegisterUVAnimeID(int vtxID, int patternCount, bool repeat)
{
	return m_pUVAnimationManager->RegisterAnimationID(vtxID, patternCount, repeat);
}

void DX11Library::CreateUVAnimeData(int vtxID, int animeID, int tuCount, int tvCount
						, const sl::fRect& rStartUVVal, int dispFlameCount)
{
	m_pUVAnimationManager->CreateUVAnimationData(vtxID, animeID, tuCount, tvCount
												, rStartUVVal, dispFlameCount);
}

void DX11Library::UpdateUVAnime(int vtxID, int animeID)
{
	if(m_pUVAnimationManager->UpdateUVAnimation(vtxID, animeID))
	{
		m_pVertex2DManager->SetUV(vtxID, m_pUVAnimationManager->GetCurrentAnimeUV(vtxID, animeID));
	}
}

void DX11Library::ReturnUVAnimeInitialState(int vtxID, int animeID)
{
	m_pUVAnimationManager->ReturnUVAnimeInitialState(vtxID, animeID);
	m_pVertex2DManager->SetUV(vtxID, m_pUVAnimationManager->GetCurrentAnimeUV(vtxID, animeID));
}

bool DX11Library::CheckLastNumCurrnttUVAnime(int vtxID, int animeID)
{
	return m_pUVAnimationManager->CheckLastNumCurrnttAnime(vtxID, animeID);
}

void DX11Library::SetUVAnimeData(int vtxID, int animeID, int index
					, const sl::fRect& rUV, int dispFlameCount)
{
	m_pUVAnimationManager->SetAnimeData(vtxID, animeID, index, rUV, dispFlameCount);
}

void  DX11Library::SeUVtAnimeOrder(int vtxID, int animeID, const std::vector<int>& rAnimeOrder)
{
	m_pUVAnimationManager->SetAnimeOrder(vtxID, animeID, rAnimeOrder);
}

void DX11Library::SetDepthStencilTest(bool isStencilTest)
{
	m_pGraphicsDevice->SetDepthStencilTest(isStencilTest);
}

void DX11Library::StartRender(void)
{
	m_pGraphicsDevice->StartRender();
}

void DX11Library::EndRender(void)
{
	m_pGraphicsDevice->EndRender();
}

void DX11Library::Draw2D(const DrawingID& rID, const SLVECTOR2& rPos, const SLVECTOR3& rScale, float angle)
{
	m_pVertex2DManager->SetupShadar();
	m_pVertex2DManager->SetupConstantBuffer(D3DXVECTOR2(rPos.x, rPos.y), D3DXVECTOR3(rScale.x, rScale.y, rScale.z), angle);
	m_pVertex2DManager->SetupBlendState();
	m_pTextureManager->SetUpTexture(rID.m_TexID);
	UINT stride = sizeof(sl::dx11::BasicVertex);
	UINT offset = 0;
	ID3D11Buffer* pVertexBuffer = m_pVertex2DManager->GetBuffer(rID.m_VtxID);
	m_pGraphicsDevice->GetDeviceContext()->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);
	m_pGraphicsDevice->GetDeviceContext()->Draw(m_pVertex2DManager->GetVertexCount(), 0);
}

void DX11Library::UpdateInputDevice(void)
{
	m_pInputManager->Update();

#ifdef USING_XI_GAMEPAD
	m_pGamePad->Update();
#endif
}

DEVICE_STATE DX11Library::CheckKey(int keyID)
{
	return m_pInputManager->CheckKey(keyID);
}

DEVICE_STATE DX11Library::CheckGamePad(int actionID, int  padNum)
{
#ifdef USING_DI_GAMEPAD
	// DirectInputの処理をここに入れる
#else 

#ifdef USING_XI_GAMEPAD
	
	return m_pGamePad->CheckState(actionID, padNum);

#endif	// USING_XI_GAMEPAD
#endif	//  USING_DI_GAMEPAD

}

void DX11Library::RegisterCustomizeType(int ID, HID_TYPE device, int inputType)
{
	m_pCustomizeInputManager->RegisterCustomizeType(ID, device, inputType);
}


bool DX11Library::CheckCustomizeState(int ID, DEVICE_STATE  checkState, int deviceNum)
{
	return m_pCustomizeInputManager->CheckState(ID, checkState, deviceNum);
}

}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
