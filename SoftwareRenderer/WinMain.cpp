/*
	WinMain.cpp
	Author: Dean Marsinelli

	This file provides the entry-point into the program.
*/

#include <Windows.h>

#include "Game.h"

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, INT)
{
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WinProc, 0, 0,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		L"SoftwareRenderer", NULL };
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	RegisterClassEx(&wc);

	RECT wr;
	wr.left = 650;
	wr.right = 800 + wr.left;
	wr.top = 150;
	wr.bottom = 600 + wr.top;
	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);

	HWND hWnd = CreateWindow(L"SoftwareRenderer", L"Software Renderer",
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, wr.left, wr.top, wr.right - wr.left, wr.bottom - wr.top,
		NULL, NULL, wc.hInstance, NULL);

	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);

	Game game(hWnd);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			game.Update();
			game.Draw();
		}
	}

	UnregisterClass(L"SoftwareRenderer", wc.hInstance);
	return 0;
}
