﻿//==================================================================================================================================//
//!< @file		dx11Window.cpp
//!< @brief		sl::dx11::Windowクラス実装
//!< @author	T.Haga
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "dx11Window.h"
#include "../../../slBuild.h"

namespace sl
{
namespace dx11
{

/* Global Function -------------------------------------------------------------------------------------------- */

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch(iMsg)
	{

	case WM_CLOSE:
		DestroyWindow(hWnd);
		return 0;
		break;

	case WM_KEYDOWN:
		switch(static_cast<char>(wParam))
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			return 0;
			break;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;

	}

	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}

/* Public Functions ------------------------------------------------------------------------------------------- */

Window::Window(void)
	: m_hWnd(NULL)
	, m_hWndParent(NULL)
{
	ZeroMemory(&m_WinMsg, sizeof(m_WinMsg));
}

Window::~Window(void)
{}

bool Window::Initialize(t_char*  pWinTitle, int winWidth, int winHeight, HWND hWndParent)
{
	// ウィンドウ情報の設定
	WNDCLASSEX  WndClass;
	WndClass.cbSize				= sizeof(WndClass);
	WndClass.style				= CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc		= WndProc;
	WndClass.cbClsExtra			= 0;
	WndClass.cbWndExtra			= 0;
	WndClass.hInstance			= GetModuleHandle(NULL);
	WndClass.hIcon				= LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor			= LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground		= (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName		= NULL;
	WndClass.lpszClassName		= pWinTitle;
	WndClass.hIconSm			= LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);

	// ウィンドウ作成
	m_hWnd = CreateWindow(
		pWinTitle,
		pWinTitle,
		WS_OVERLAPPEDWINDOW,
		0,
		0,
		winWidth,
		winHeight,
		hWndParent,
		NULL,
		GetModuleHandle(NULL),
		NULL);

	SetProcessDPIAware();					// WindowsにDPIAwareであることを示す(不適切なサイズやフォントが使用されるのを防ぐ)

	// クライアント領域を指定したサイズに調整する
#ifdef ADJUST_CLIENT_SIZE
	// ウィンドウサイズとクライアントサイズを求める
	RECT widowRect;
	GetWindowRect(m_hWnd, &widowRect);
	RECT clientRect;
	GetClientRect(m_hWnd, &clientRect);

	// ウィンドウサイズとクライアントサイズの差からウィンドウの枠の長さを求める
	int winFlameWidth  = static_cast<int>((widowRect.right - widowRect.left) - (clientRect.right - clientRect.left));
	int winFlameHeight = static_cast<int>((widowRect.bottom - widowRect.top) - (clientRect.bottom - clientRect.top));

	// ウィンドウの幅を再設定する
	SetWindowPos(m_hWnd, HWND_TOP, 0, 0, (winWidth + winFlameWidth), (winHeight + (widowRect.bottom - clientRect.bottom)), SWP_NOMOVE);
#endif	// ADJUST_CLIENT_SIZE

	if(m_hWnd == NULL)
	{
		MessageBox(0, "ウィンドウ生成に失敗しました。", NULL, MB_OK);
		return false;	
	}

	m_hWndParent = hWndParent;
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);
	SetWindowText(m_hWnd, pWinTitle);

	// 現在のクライアント領域のサイズを保存する
	RECT clientSize;
	GetClientRect(m_hWnd, &clientSize);
	m_ClientSize.m_Left		= 0.0f;
	m_ClientSize.m_Top		= 0.0f;
	m_ClientSize.m_Right	= static_cast<float>(clientSize.right - clientSize.left);
	m_ClientSize.m_Bottom	= static_cast<float>(clientSize.bottom - clientSize.top);

	return true;
}

void Window::Finalize(void)
{
	if(m_hWnd != NULL)
	{
		SendMessage(m_hWnd, WM_CLOSE, 0, 0);						// SendMessageの処理は同期
	}
	else
	{
		MessageBox(0, "破棄すべきウィンドウはありません。", NULL, MB_OK);
	}
}

bool Window::Update(void)
{
	if(m_WinMsg.message != WM_QUIT)
	{
		if(PeekMessage(&m_WinMsg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&m_WinMsg);
			DispatchMessage(&m_WinMsg);
		}

		return false;
	}

	m_hWnd = NULL;
	return true;
}

}	// namespace dx11
}	// namespace sl

	//==================================================================================================================================//
	// END OF FILE
	//==================================================================================================================================//
