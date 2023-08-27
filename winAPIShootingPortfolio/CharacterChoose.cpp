#include "stdafx.h"
#include "CharacterChoose.h"

HRESULT CharacterChoose::init()
{
	_goNextScene = false;

	_image = IMAGEMANAGER->addFrameImage("캐릭터선택","Resources/Images/ShootingGame/Title/Character.bmp",
		WINSIZE_X*6, WINSIZE_Y,
		6,1,
		true,
		RGB(255,0,255));
	
	return S_OK;
}

void CharacterChoose::release()
{
}

void CharacterChoose::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		if (_curIdx > 0)
		{
			_curIdx--;
		}
		
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		if (_curIdx < 6)
		{
			_curIdx++;
		}
		
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		_goNextScene = true;
	}

}

void CharacterChoose::render()
{
	_image->frameRender(getMemDC(), 0, 0, _curIdx, 0);
}
