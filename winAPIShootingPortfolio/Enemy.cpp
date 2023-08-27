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
_animationSpeed(100),
_rndFireCount(0.0f),
_bulletFireCount(0.0f)
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
	_center = position;

	_bulletFireCount = TIMEMANAGER->getWorldTime();
	_rndFireCount = RND->getFromFloatTo(1.5f, 4.5f);

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

	_bulletFireCount = TIMEMANAGER->getWorldTime();
	_rndFireCount = RND->getFromFloatTo(1.5f, 4.5f);

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
	}


	
	

}

void Enemy::d2drender(void)
{
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
				_deleteObject = true;
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

bool Enemy::bulletCountFire()
{
	return false;
}
