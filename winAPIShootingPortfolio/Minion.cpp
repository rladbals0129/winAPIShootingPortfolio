#include "stdafx.h"
#include "Minion.h"




HRESULT Minion::init(const char* imageName, POINT position)
{
	Enemy::init(imageName, position);

	_speedX = 2;
	_speedY = 2;
	return S_OK;
}

HRESULT Minion::init(const char* imageName, POINT position, float startAngle)
{
	Enemy::init(imageName, position, startAngle);

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

}

void Minion::move()
{
	switch (_movePattern)
	{
		case CIRCLE_PATTERN:
		{
			radius = 500.0f;
			_angle += 0.01f;
			_x = _center.x + radius * cos(_angle + _startAngle);
			_y = _center.y + radius * sin(_angle + _startAngle);

		
			break;
		}
		case BOUNCE_PATTERN:
		{		
			_x += _speedX;	
			

			if (_x < 0)
			{
				_x = 0;
				_speedX = -_speedX;
			}
			else if (_x > WINSIZE_X)
			{
				_x = WINSIZE_X ;
				_speedX = -_speedX;
			}
						
			break;
		}
		case CENTER_CIRCLE_PATTERN:
		{
			radius = 100.0f;
			_angle += 0.05f;
			_x = _center.x + radius * cos(_angle + _startAngle);
			_y = _center.y + radius * sin(_angle + _startAngle);

			
			break;
		}
		case WAVE_PATTERN:
		{
			float amplitude = 100.0f; 
			float frequency = 0.05f; 
			_x += _speedX; 
			_y = _center.y + amplitude * sin(frequency * _x + _startAngle);

			if (_x < 0)
			{
				_x = 0;
				_speedX = -_speedX;
			}
			else if (_x > WINSIZE_X)
			{
				_x = WINSIZE_X;
				_speedX = -_speedX;
			}
		}
	}
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}

bool Minion::bulletCountFire()
{
	if (_rndFireCount + _bulletFireCount <= TIMEMANAGER->getWorldTime())
	{
		_bulletFireCount = TIMEMANAGER->getWorldTime();
		_rndFireCount = RND->getFromFloatTo(2.0f, 6.0f);
	
		return true;
	}
	return false;
}




Minion::Minion(MovePattern movePattern) : _movePattern(movePattern)
{

}

Minion::~Minion()
{
	//!Do Nothing
}
