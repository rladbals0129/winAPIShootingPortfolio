#include "stdafx.h"
#include "Boss.h"
#include "Rocket.h"

HRESULT Boss::init(const char* imageName, POINT position)
{
	_worldTimeCount = GetTickCount();
	_timeCount = 10.f;
	_hp = 1000;
	_curPatternCount = 0;
	_image = IMAGEMANAGER->findImage(imageName);

	_x = position.x;
	_y = position.y;
	_rc = RectMakeCenter(_x, _y,
		_image->getFrameWidth(), _image->getFrameHeight());
	_die = false;
	_center = position;

	_bulletFireCount = TIMEMANAGER->getWorldTime();
	_fireCount = 0.2f;
	_speedX = 5.f;

	_effectPlaying = false;

	IMAGEMANAGER->addFrameImage("º¸½º»ç¸ÁÀÌÆåÆ®", "Resources/Images/ShootingGame/Effect/bossExplosions.bmp", 4000, 200,
		20, 1,
		true,
		RGB(255, 0, 255));
	_effectCurrentFrameX = 0;
	_effectCurrentFrameY = 0;


	_lastPatternTime = TIMEMANAGER->getWorldTime();
	_patternDelayTime = 3.0f;


	IMAGEMANAGER->addFrameImage("º¸½º¹Ì»çÀÏ1", "Resources/Images/ShootingGame/Bullet/BossBullet1.bmp",
		16, 16,
		1, 1,
		true,
		RGB(255, 0, 255));
	_bossBullet1 = new EnemyBullet;
	_bossBullet1->init("º¸½º¹Ì»çÀÏ1", 400, 1000);


	IMAGEMANAGER->addFrameImage("º¸½º¹Ì»çÀÏ2", "Resources/Images/ShootingGame/Bullet/BossBullet2.bmp",
		82, 21,
		4, 1,
		true,
		RGB(255, 0, 255));
	_bossBullet2 = new EnemyBullet;
	_bossBullet2->init("º¸½º¹Ì»çÀÏ2", 400, 1000);

	IMAGEMANAGER->addFrameImage("º¸½º¹Ì»çÀÏ3", "Resources/Images/ShootingGame/Bullet/BossBullet1.bmp",
		16, 16,
		1, 1,
		true,
		RGB(255, 0, 255));
	_bossBullet3 = new EnemyBullet;
	_bossBullet3->init("º¸½º¹Ì»çÀÏ3",400, 1000);

	
	_spiralAngle = 0;

	return S_OK;
}

void Boss::release(void)
{

}



void Boss::update(void)
{

	move();

	if (!_die && _create)
	{
		
		if (TIMEMANAGER->getWorldTime() - _lastPatternTime >= _patternDelayTime)
		{
			_lastPatternTime = TIMEMANAGER->getWorldTime();
			_patternIndex = _patternIndex == 4 ? 0 : _patternIndex + 1;
		}

		switch (_patternIndex)
		{
		case 0:
			pattern1();
		
			break;
		case 1:
		{
			pattern2();
			_x += _speedX;
			

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
			break;
		}
		case 2:
			pattern3();
	
			break;
		case 3:
			pattern4();
			break;
		case 4:
			pattern5();
			break;
		default:
			break;
		}
	}
	if (_hp <= 0)
	{
		dieEffect();
	}
	
	_rc = RectMakeCenter(_x, _y,
		_image->getFrameWidth(), _image->getFrameHeight());
	
	_bossBullet1->update();
	_bossBullet2->update();
	_bossBullet3->update();
	collision();

}

void Boss::render()
{
	if (!_die)
	{
		animation();
		_image->frameRender(getMemDC(), _rc.left, _rc.top,
			_currentFrameX, _currentFrameY);
	}


	if (_effectPlaying)
	{
		IMAGEMANAGER->frameRender("º¸½º»ç¸ÁÀÌÆåÆ®",getMemDC(),
			_x - IMAGEMANAGER->findImage("º¸½º»ç¸ÁÀÌÆåÆ®")->getFrameWidth() / 2,
			_y - IMAGEMANAGER->findImage("º¸½º»ç¸ÁÀÌÆåÆ®")->getFrameHeight() / 2,
			_effectCurrentFrameX, _effectCurrentFrameY);

		IMAGEMANAGER->frameRender("º¸½º»ç¸ÁÀÌÆåÆ®", getMemDC(),
			_x - IMAGEMANAGER->findImage("º¸½º»ç¸ÁÀÌÆåÆ®")->getFrameWidth(),
			_y - IMAGEMANAGER->findImage("º¸½º»ç¸ÁÀÌÆåÆ®")->getFrameHeight() / 2,
			_effectCurrentFrameX, _effectCurrentFrameY);

		IMAGEMANAGER->frameRender("º¸½º»ç¸ÁÀÌÆåÆ®", getMemDC(),
			_x + IMAGEMANAGER->findImage("º¸½º»ç¸ÁÀÌÆåÆ®")->getFrameWidth() / 2,
			_y - IMAGEMANAGER->findImage("º¸½º»ç¸ÁÀÌÆåÆ®")->getFrameHeight() / 2,
			_effectCurrentFrameX, _effectCurrentFrameY);

		IMAGEMANAGER->frameRender("º¸½º»ç¸ÁÀÌÆåÆ®", getMemDC(),
			_x - IMAGEMANAGER->findImage("º¸½º»ç¸ÁÀÌÆåÆ®")->getFrameWidth() / 2,
			_y + IMAGEMANAGER->findImage("º¸½º»ç¸ÁÀÌÆåÆ®")->getFrameHeight() / 2,
			_effectCurrentFrameX, _effectCurrentFrameY);

		IMAGEMANAGER->frameRender("º¸½º»ç¸ÁÀÌÆåÆ®", getMemDC(),
			_x - IMAGEMANAGER->findImage("º¸½º»ç¸ÁÀÌÆåÆ®")->getFrameWidth() / 2,
			_y - IMAGEMANAGER->findImage("º¸½º»ç¸ÁÀÌÆåÆ®")->getFrameHeight(),
			_effectCurrentFrameX, _effectCurrentFrameY);

		_effectCurrentFrameX++;
		if (IMAGEMANAGER->findImage("º¸½º»ç¸ÁÀÌÆåÆ®")->getMaxFrameX() < _effectCurrentFrameX)
		{

			_effectCurrentFrameX = 0;
			_effectPlaying = false;
			_die = true;
		}



	}

	_bossBullet1->render();
	_bossBullet2->render();
	_bossBullet3->render();
}

void Boss::pattern1()
{

	

	if (bulletCountFire())
	{
		float angleStep = PI / 10;
		for (int i = 0; i < 20; ++i)
		{
			float angle = i * angleStep;
			float speed = 4.f;
			_bossBullet1->fire(_rc.left + (_image->getFrameWidth() / 2), _rc.top + (_image->getFrameHeight() / 2) , angle, speed);
		}
		
	}

}

void Boss::pattern2()
{
	
	if (bulletCountFire())
	{
		_bossBullet2->fire(_rc.left + (_rc.right + -_rc.left) / 2, _rc.bottom + (_rc.top - _rc.bottom) / 2 + 30,
			getAngle(_rc.left + (_rc.right + -_rc.left) / 2,
				_rc.bottom + (_rc.top - _rc.bottom) / 2,
				_rocket->getPosition().x,
				_rocket->getPosition().y), 3.f);
	}
}

void Boss::pattern3()
{

	if (bulletCountFire())
	{
		float startAngle = PI / 6;  
		float endAngle = PI * 5 / 6;  
		int bulletNum = 10; 

		float angleStep = (endAngle - startAngle) / bulletNum;

		for (int i = 0; i < bulletNum; ++i) {
			float angle = -(startAngle + i * angleStep);
			float speed = 4.f;
			_bossBullet3->fire(_rc.left + (_rc.right + -_rc.left) / 2, _rc.bottom + (_rc.top - _rc.bottom) / 2 + 30, angle, speed);
		}
	}
}

void Boss::pattern4()
{
	if (bulletCountFire2())
	{
		float speed = 6.f;
		_bossBullet2->fire(_rc.left + (_rc.right + -_rc.left) / 2, _rc.bottom + (_rc.top - _rc.bottom) / 2 + 30, _spiralAngle, speed);

	
		_spiralAngle += PI / 10;

		if (_spiralAngle >= 2 * PI)
		{
			_spiralAngle -= 2 * PI;  
		}
	}
}

void Boss::pattern5()
{
	if (bulletCountFire())
	{
		const int bulletNum = 5;  
		for (int i = 0; i < bulletNum; ++i)
		{
		
			_spiralAngle += PI / 10 *(i+RND->getFromFloatTo(40.f,60.f));

			if (_spiralAngle >= 2 * PI)
			{
				_spiralAngle -= 2 * PI * (i + RND->getFromFloatTo(40.f, 60.f));
			}
			float speed = 4.f;
			_bossBullet1->fire(_rc.left + (_rc.right + -_rc.left) / 2, _rc.bottom + (_rc.top - _rc.bottom) / 2, _spiralAngle, speed);
		}
	}
}

void Boss::collision()
{
	for (int i = 0; i < _bossBullet1->getBullet().size(); i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &CollisionAreaResizing(_bossBullet1->getBullet()[i].rc,5,5),
			&CollisionAreaResizing(_rocket->getRect(),10,5)))
		{
			_bossBullet1->removeBullet(i);
			_rocket->hitDamage(2.f);
		}
	}
	for (int i = 0; i < _bossBullet2->getBullet().size(); i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &CollisionAreaResizing(_bossBullet2->getBullet()[i].rc,5,5),
			&CollisionAreaResizing(_rocket->getRect(), 10, 5)))
		{
			_bossBullet2->removeBullet(i);
			_rocket->hitDamage(2.f);
		}
	}
	for (int i = 0; i < _bossBullet3->getBullet().size(); i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &CollisionAreaResizing(_bossBullet3->getBullet()[i].rc,5,5),
			&CollisionAreaResizing(_rocket->getRect(), 10, 5)))
		{
			_bossBullet3->removeBullet(i);
			_rocket->hitDamage(2.f);
		}
	}
}

bool Boss::bulletCountFire()
{
	if (_fireCount + _bulletFireCount <= TIMEMANAGER->getWorldTime())
	{
		_bulletFireCount = TIMEMANAGER->getWorldTime();
		_fireCount = 0.2f;

		return true;
	}
	return false;
}

bool Boss::bulletCountFire2()
{
	if (_fireCount + _bulletFireCount <= TIMEMANAGER->getWorldTime())
	{
		_bulletFireCount = TIMEMANAGER->getWorldTime();
		_fireCount = 0.05f;

		return true;
	}
	return false;
}

void Boss::dieEffect()
{
	if (!_effectPlaying)
	{
		_effectPlaying = true;
		_effectCurrentFrameX = 0;
		_effectCurrentFrameY = 0;
	}
}

void Boss::animation()
{
	if (_timeCount + _worldTimeCount <= GetTickCount())
	{
		_worldTimeCount = GetTickCount();
		if (_returnAnim == 0)
		{
			_currentFrameX++;

			if (_image->getMaxFrameX() < _currentFrameX)
			{
				_returnAnim = 1 - _returnAnim;
			}
		}
		else
		{
			_currentFrameX--;

			if (_currentFrameX < 1)
			{
				_returnAnim = 1 - _returnAnim;
			}

		}	
	}
}

void Boss::move()
{
	if (!_create)
	{
		_y += 4;
		if (_y > 200)
		{
			_create = true;
		}
	}
	else
	{

	}
	
}
