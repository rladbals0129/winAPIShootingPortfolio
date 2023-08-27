#include "stdafx.h"
#include "GameNode.h"

HRESULT GameNode::init(void)
{


	return S_OK;
}

HRESULT GameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (managerInit)
	{
		

		RND->init();
		KEYMANAGER->init();
		IMAGEMANAGER->init();
		TIMEMANAGER->init();
		D2DMANAGER->init(getMemDC());
		
	}


	return S_OK;
}

void GameNode::release(void)
{
	KillTimer(_hWnd, 1);
	if (_managerInit)
	{
		RND->releaseSingleton();
		KEYMANAGER->releaseSingleton();
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();
		D2DMANAGER->release();
		D2DMANAGER->releaseSingleton();
	

	}
	ReleaseDC(_hWnd, _hdc);



}

void GameNode::update(void)
{
	
}

void GameNode::render(void)
{
}

void GameNode::d2drender(void)
{
}

LRESULT GameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_TIMER:
		this->update();
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		this->render();
		EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEMOVE:
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

GameNode::~GameNode()
{
}
