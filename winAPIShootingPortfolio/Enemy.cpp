#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(void) : _rc(RectMake(0, 0, 0, 0)),
_currentFrameX(0),
_currentFrameY(0),
_x(0.f),
_y(0.f),
_worldTimeCount(0.f),
_rndTimeCount(0.f),
_animationCount(0),
_animationSpeed(100)
{
}

HRESULT Enemy::init(void)
{
	//!DO nothing
	return S_OK;
}

HRESULT Enemy::init(const char* imageName, POINT position)
{
	_worldTimeCount = GetTickCount();
	_rndTimeCount = RND->getFromFloatTo(50.f, 150.f);

	_image = IMAGEMANAGER->findImage(imageName);
	_x = position.x;
	_y = position.y;
	_rc = RectMakeCenter(_x, _y,
		_image->getFrameWidth(), _image->getFrameHeight());
	_die = false;


	//_effectPNGRender = new PNGRender;
	//_effectPNGRender->init();
	//_effectPNGRender->addImage(L"Resources/Images/ShootingGame/Effect/boom.png", 960, 576, 5, 3);
	_effectPlaying = false;

	D2DMANAGER->loadImageD2D("ÆøÆÄ", L"Resources/Images/ShootingGame/Effect/boom2.png", 360, 27, 12, 1);
	_effectCurrentFrameX = 0;
	_effectCurrentFrameY = 0;
	return S_OK;
}

HRESULT Enemy::init(const char* imageName, POINT position, float startAngle)
{
	_worldTimeCount = GetTickCount();
	_rndTimeCount = RND->getFromFloatTo(50.f, 150.f);

	_image = IMAGEMANAGER->findImage(imageName);
	_x = position.x;
	_y = position.y;
	_rc = RectMakeCenter(_x, _y,
		_image->getFrameWidth(), _image->getFrameHeight());
	_startAngle = startAngle;
	_center = position;
	_angle = 0.f;
	radius = 300.f;
	_die = false;



	//_effectPNGRender = new PNGRender;
	//_effectPNGRender->init();
	//_effectPNGRender->addImage(L"Resources/Images/ShootingGame/Effect/boom.png", 960, 576, 5, 3);
	D2DMANAGER->loadImageD2D("ÆøÆÄ", L"Resources/Images/ShootingGame/Effect/boom2.png", 360, 27, 12, 1);
	_effectPlaying = false;
	_effectCurrentFrameX = 0;
	_effectCurrentFrameY = 0;
	return S_OK;
}

void Enemy::release(void)
{
}

void Enemy::update(void)
{
	if (!_die)
	{
		move();
	}



}

void Enemy::render(void)
{
	if (!_die)
	{
		draw();
		animation();
		//D2DMANAGER->beginDraw();
		

		//D2DMANAGER->endDraw();
		/*_effectPNGRender->frameRender(getMemDC(),
			_x - _effectPNGRender->getFrameWidth() / 2,
			_y - _effectPNGRender->getFrameHeight() / 2,
			_effectCurrentFrameX,
			_effectCurrentFrameY);
		_effectCurrentFrameX++;
		if (_effectPNGRender->getMaxFrameX() < _effectCurrentFrameX)
		{
			_effectCurrentFrameX = 0;
			_effectCurrentFrameY++;
			if (_effectPNGRender->getMaxFrameY() < _effectCurrentFrameY)
			{
				_effectPlaying = false;
			}
		}*/
	}


	
	else if (_effectPlaying)
	{
		//D2DMANAGER->beginDraw();
		//D2DMANAGER->render("ÆøÆÄ", _x - D2DMANAGER->getFrameWidth() / 2, _y - D2DMANAGER->getFrameHeight() / 2,
		//	_effectCurrentFrameX, _effectCurrentFrameY);

		//_effectCurrentFrameX++;
		//if (D2DMANAGER-> getMaxFrameX() < _effectCurrentFrameX)
		//{
		//	_effectCurrentFrameX = 0;
		//	_effectCurrentFrameY++;
		//	if (D2DMANAGER->getMaxFrameY() < _effectCurrentFrameY)
		//	{
		//		_effectPlaying = false;
		//	}
		//}

		//D2DMANAGER->endDraw();
		// 
		// 
		//_effectPNGRender->frameRender(getMemDC(),
		//	_x - _effectPNGRender->getFrameWidth() / 2,
		//	_y - _effectPNGRender->getFrameHeight() / 2,
		//	_effectCurrentFrameX,
		//	_effectCurrentFrameY);
		//_effectCurrentFrameX++;
		//if (_effectPNGRender->getMaxFrameX() < _effectCurrentFrameX)
		//{
		//	_effectCurrentFrameX = 0;
		//	_effectCurrentFrameY++;
		//	if (_effectPNGRender->getMaxFrameY() < _effectCurrentFrameY)
		//	{
		//		_effectPlaying = false;
		//	}
		//}
	}

}

void Enemy::d2drender(void)
{/*
	D2DMANAGER->render("ÆøÆÄ", _x - D2DMANAGER->getFrameWidth() / 2, _y - D2DMANAGER->getFrameHeight() / 2,
		_effectCurrentFrameX, _effectCurrentFrameY);

	_effectCurrentFrameX++;
	if (D2DMANAGER->getMaxFrameX() < _effectCurrentFrameX)
	{
		_effectCurrentFrameX = 0;
		_effectCurrentFrameY++;
		if (D2DMANAGER->getMaxFrameY() < _effectCurrentFrameY)
		{
			_effectPlaying = false;
		}
	}*/


	if (_effectPlaying)
	{
		D2DMANAGER->render("ÆøÆÄ", _x - D2DMANAGER->getFrameWidth() / 2, _y - D2DMANAGER->getFrameHeight() / 2,
			_effectCurrentFrameX, _effectCurrentFrameY);

		_effectCurrentFrameX++;
		if (D2DMANAGER->getMaxFrameX() < _effectCurrentFrameX)
		{
			_effectCurrentFrameX = 0;
			_effectCurrentFrameY++;
			if (D2DMANAGER->getMaxFrameY() < _effectCurrentFrameY)
			{
				_effectPlaying = false;
			}
		}

	}
}

void Enemy::playEffect()
{
	if (!_effectPlaying)
	{
		_effectPlaying = true;
		_effectCurrentFrameX = 0;
		_effectCurrentFrameY = 0;
	}
}


void Enemy::draw(void)
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top,
		_currentFrameX, _currentFrameY);
}

void Enemy::move(void)
{
	//Àû¸¶´Ù ±¸Çö ´Ù¸£¹Ç·Î ÀÚ½Ä¿¡¼­
}


void Enemy::animation(void)
{
	if (_rndTimeCount + _worldTimeCount <= GetTickCount())
	{
		_worldTimeCount = GetTickCount();
		_currentFrameX++;
		if (_image->getMaxFrameX() < _currentFrameX)
		{
			_currentFrameX = 0;

		}
	}
}

