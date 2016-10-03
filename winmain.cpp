#include <d3d9.h>
#include <d3dx9.h>
#include <time.h>
#include <stdio.h>
#include "game.h"
#include "dxgraphics.h"
#include "dxinput.h"

LRESULT WINAPI WinProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_DESTROY:
		if (d3ddv != NULL)
			d3ddv->Release();

		if (d3d != NULL)
			d3d->Release();
		
		//them
		Kill_Keyboard();
		Kill_Mouse();
		if (dinput != NULL) dinput->Release();
		//het

		Game_End(hwnd);

		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = APPTITLE;
	wc.hIconSm = NULL;
	return RegisterClassEx(&wc);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	HWND hwnd;
	MyRegisterClass(hInstance);
	DWORD style;
	if (FULLSCREEN)
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	else style = WS_OVERLAPPED;

	hwnd = CreateWindow(APPTITLE,
		APPTITLE,
		style,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!hwnd)
		return FALSE;

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	if (!Init_Direct3D(hwnd, SCREEN_WIDTH, SCREEN_HEIGHT, FULLSCREEN))
		return 0;

	if (!Game_Init(hwnd))
	{
		MessageBox(hwnd, "Error intializing the game.", "Error", MB_OK);
		return 0;
	}

	//them vao thoi

	if (!Init_DirectInput(hwnd))
	{
		MessageBox(hwnd, "Error intializing DirectInput", "Error", MB_OK);
		return 0;
	}

	//het roi

	int done = 0;
	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else Game_Run(hwnd);
	}
	return msg.wParam;
}