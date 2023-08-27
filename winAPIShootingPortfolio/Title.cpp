#include "stdafx.h"
#include "Title.h"

#include <Vfw.h>
#pragma comment(lib, "vfw32.lib")

HRESULT Title::init(void)
{
	_hWndVideo = MCIWndCreate(_hWnd, _hInstance, MCIWNDF_NOPLAYBAR, "Resources/Video/Title.wmv");

	MoveWindow(_hWndVideo, 0, 0, WINSIZE_X, WINSIZE_Y, FALSE);

	MCIWndPlay(_hWndVideo);
    _nextScene = false;
	return S_OK;
}

void Title::release(void)
{
	MCIWndClose(_hWndVideo);
	MCIWndDestroy(_hWndVideo);
}

void Title::update(void)
{
    if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
    {
        _nextScene = true;
        release();
    }
    else if (MCIWndGetLength(_hWndVideo) <= MCIWndGetPosition(_hWndVideo))
    {
        MCIWndSeek(_hWndVideo, 0);
        MCIWndPlay(_hWndVideo);
    }
}

void Title::render()
{
}
