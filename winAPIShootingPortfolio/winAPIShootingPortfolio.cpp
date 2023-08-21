﻿#include "Stdafx.h"
#include "MainGame.h"
HINSTANCE _hInstance;
HWND _hWnd;
POINT _ptMouse;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void setWindowSize(int x, int y, int width, int hight);

MainGame* _mg;
//_currentScene 이 세팅nullptr

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hProvInstance, LPSTR lpszCmdstr, int nCmdShow)
{
	_mg = new MainGame(); //나를 힙 영역에 할당해라.

	_hInstance = hInstance;

	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = WINNAME;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	//굳이 assert를 쓰자면 여기서 쓸 수 있겠다.
	//HRESULT hr; 
	//hr = RegisterClass(&wndClass);
	//assert(SUCCEEDED(hr));
	RegisterClass(&wndClass);

#ifdef FULLSCREEN
	//디바이스 모드 구조체(화면 디스플레이 관련 구조체)
	DEVMODE dm;
	ZeroMemory(&dm, sizeof(DEVMODE));

	dm.dmSize = sizeof(DEVMODE);
	dm.dmBitsPerPel = 32; //32비트 트루컬러
	dm.dmPanningWidth = 1920;		//가로
	dm.dmPelsHeight = 1080;			//세로
	dm.dmDisplayFrequency = 60; // 주사율(60hz)


	//필드설정
	dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

	if (ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
	{
		ChangeDisplaySettings(&dm, 0);
	}

	_hWnd = CreateWindow(
		WINNAME,
		WINNAME,
		WS_OVERLAPPEDWINDOW,
		WINSTART_X,
		WINSTART_Y,
		WINSIZE_X,
		WINSIZE_Y,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL);
#else
	_hWnd = CreateWindow(
		WINNAME,
		WINNAME,
		WS_OVERLAPPEDWINDOW,
		WINSTART_X,
		WINSTART_Y,
		WINSIZE_X,
		WINSIZE_Y,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL);
#endif
	setWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);
	ShowWindow(_hWnd, nCmdShow);

	if (FAILED(_mg->init())) //FAILED : mg의 초기화가 실패할경우 트루반환 후 종료
	{
		return 0;
	}

	MSG message;

	while (true)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT) break;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			TIMEMANAGER->update(60.f);
			_mg->update();
			_mg->render();
		}
	}


	//while (GetMessage(&message, 0, 0, 0))
	//{
	//	TranslateMessage(&message);
	//	DispatchMessage(&message);
	//}

	_mg->release();
	UnregisterClass(WINNAME, hInstance); //지워주기

	return (int)message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _mg->MainProc(hWnd, iMessage, wParam, lParam);
	// init함수 실행
}



void setWindowSize(int x, int y, int width, int hight)
{
	RECT rc = { 0,0,width,hight };

	AdjustWindowRect(&rc, WINSTYLE, false);

	SetWindowPos(_hWnd, NULL, x, y, (rc.right - rc.left), (rc.bottom - rc.top),
		SWP_NOZORDER | SWP_NOMOVE);

}