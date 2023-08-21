#include "stdafx.h"
#include "Minion.h"




HRESULT Minion::init(const char* imageName, POINT position)
{
	Enemy::init(imageName, position);
	_hp = 100;
	//cout << _hp << endl;
	_speedX = 2;
	_speedY = 2;
	return S_OK;
}

HRESULT Minion::init(const char* imageName, POINT position, float startAngle)
{
	Enemy::init(imageName, position, startAngle);
	_hp = 100;
	//cout << _hp << endl;
	_speedX = 2;
	_speedY = 2;
	return S_OK;
}

void Minion::update(void)
{
	move();
}

void Minion::render(void)
{
	Enemy::render();
	//	IMAGEMANAGER->render("체력", getMemDC(), _rc.left, _rc.bottom);
	//	IMAGEMANAGER->render("체력바", getMemDC(), _rc.left+40, _rc.bottom);

}

void Minion::move()
{
	switch (_movePattern)
	{
	case CIRCLE_PATTERN:
	{
		radius = 300.0f;
		_angle += 0.01f;
		_x = _center.x + radius * cos(_angle + _startAngle);
		_y = _center.y + radius * sin(_angle + _startAngle);

		_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		break;
	}
	case BOUNCE_PATTERN:
	{

		_x += _speedX;
		_y += _speedY;
		if (_x < 0 || _x > WINSIZE_X) _speedX = -_speedX;
		if (_y < 0 || _y > WINSIZE_Y) _speedY = -_speedY;
		break;
	}
	case CENTER_CIRCLE_PATTERN:
	{
		radius = 100.0f;
		_angle += 0.05f;
		_x = _center.x + radius * cos(_angle + _startAngle);
		_y = _center.y + radius * sin(_angle + _startAngle);

		_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		break;
	}
	}
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}




Minion::Minion(MovePattern movePattern) : _movePattern(movePattern)
{

}

Minion::~Minion()
{
	//!Do Nothing
}
