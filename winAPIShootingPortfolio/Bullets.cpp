#include "stdafx.h"
#include "Bullets.h"
//
//HRESULT Missile::init(int bulletMax, float range)
//{
//	_range = range;
//	cout << "부모" << endl;
//	for (int i = 0; i < bulletMax; i++)
//	{
//		tagBullet bullet;
//		ZeroMemory(&bullet, sizeof(tagBullet)); //ZeroMemory : 0으로 채운다 (memset)차이점 -> 1. 0으로초기화 2. 0이아닌 값으로 초기화 가능
//		/*
//			MoveMemory
//			CopyMemory
//			FillMemory
//			ZeroMemory
//		*/
//		bullet.img = new GImage;
//		bullet.img->init("Resources/Images/ShootingGame/Bullet/Missile.bmp",
//			0.0f, 0.0f,
//			416, 64,
//			13, 1,
//			true,
//			RGB(255, 0, 255));
//		bullet.fire = false;
//		bullet.frameTick = 7.0f;
//		bullet.speed = 5.0f;
//		_vBullet.push_back(bullet);
//	}
//
//	return S_OK;
//}
//
//void Missile::release(void)
//{
//	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
//	{
//		SAFE_DELETE(_viBullet->img);
//	}
//	_vBullet.clear();
//
//
//}
//
//void Missile::update(void)
//{
//	move();
//}
//
//void Missile::render()
//{
//	draw();
//}
//
//void Missile::fire(float x, float y)
//{
//	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
//	{
//		if (_viBullet->fire) continue;
//
//		_viBullet->fire = true;
//		_viBullet->x = _viBullet->fireX = x;
//		_viBullet->y = _viBullet->fireY = y;
//		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());
//		//_viBullet->angle = getAngle(x, y, _ptMouse.x, _ptMouse.y);
//		break;
//	}
//
//
//}
//
//void Missile::draw(void)
//{
//	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
//	{
//		if (_viBullet->fire)
//		{
//			_viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top, _viBullet->img->getFrameX(), _viBullet->img->getFrameY());
//
//		}
//
//	}
//}
//
//void Missile::move(void)
//{
//	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
//	{
//		if (!_viBullet->fire) continue;
//
//
//		//_viBullet->fireX += cos(_viBullet->angle) * _viBullet->speed;
//		_viBullet->fireY -= sin(_viBullet->angle) * _viBullet->speed;
//
//		_viBullet->rc = RectMakeCenter(_viBullet->fireX, _viBullet->fireY, _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());
//
//
//
//		if (_viBullet->frameTick + BULLETS_COUNT <= GetTickCount())
//		{
//			_viBullet->frameTick = GetTickCount();
//			_viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);
//			if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX())
//			{
//				_viBullet->img->setFrameX(0);
//			}
//		}
//
//		if (getDistance(_viBullet->x, _viBullet->y, _viBullet->fireX, _viBullet->fireY) > _range)
//		{
//			_viBullet->fire = false;
//
//		}
//
//
//	}
//}
//
//
//
////===========================================





HRESULT MissileM1::init(int bulletMax, float range)
{
	_range = range;
	_bulletMax = bulletMax;




	return S_OK;
}

void MissileM1::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img);
	}
	_vBullet.clear();
}

void MissileM1::update(void)
{
	move();

}

void MissileM1::render()
{
	draw();
}

void MissileM1::fire(const char* filepath,float x, float y)
{
	if (_bulletMax <= _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.img = new GImage;
	//"Resources/Images/ShootingGame/Bullet/BulletPower1.bmp"
	bullet.img->init(filepath,
		0, 0,
		132, 49,
		4, 1,
		true,
		RGB(255, 0, 255));
	bullet.speed = 10.0f;

	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.img->getFrameWidth(), bullet.img->getFrameHeight());
	_vBullet.push_back(bullet);



	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->fire) continue;

		_viBullet->fire = true;
		_viBullet->x = _viBullet->fireX = x;
		_viBullet->y = _viBullet->fireY = y;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

		break;
	}
}

void MissileM1::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top,
			_viBullet->img->getFrameX(), _viBullet->img->getFrameY());
		_viBullet->count++;

		if (_viBullet->count % 5 == 0)
		{
			_viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);

			if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX())
			{
				_viBullet->img->setFrameX(0);
			}
			_viBullet->count = 0;
		}
	}
}

void MissileM1::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		//_viBullet->x += cos(_viBullet->angle) * _viBullet->speed;
		//_viBullet->y -= sin(_viBullet->angle) * _viBullet->speed;
		_viBullet->y -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->getFrameWidth(),
			_viBullet->img->getFrameHeight());

		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
		{
			SAFE_DELETE(_viBullet->img);
			_viBullet = _vBullet.erase(_viBullet);

		
		}
		else
		{
			++_viBullet;
		}
	}
}

void MissileM1::removeBullet(int arrNum)
{
	SAFE_DELETE(_vBullet[arrNum].img);
	_vBullet.erase(_vBullet.begin() + arrNum);
}

HRESULT AssistanceM1::init(int bulletMax, float range)
{
	_range = range;
	_bulletMax = bulletMax;




	return S_OK;
}

void AssistanceM1::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img);
	}
	_vBullet.clear();
}

void AssistanceM1::update(void)
{
	move();

}

void AssistanceM1::render()
{
	draw();
}

void AssistanceM1::fire(float x, float y)
{
	if (_bulletMax <= _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.img = new GImage;

	bullet.img->init("Resources/Images/ShootingGame/Bullet/AV_8_Player_Bullet_2.bmp",
		0, 0,
		45 , 32 ,
		3, 1,
		true,
		RGB(255, 0, 255));
	bullet.speed = 15.0f;

	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.img->getFrameWidth(), bullet.img->getFrameHeight());
	_vBullet.push_back(bullet);



	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->fire) continue;

		_viBullet->fire = true;
		_viBullet->x = _viBullet->fireX = x;
		_viBullet->y = _viBullet->fireY = y;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

		break;
	}
}

void AssistanceM1::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top,
			_viBullet->img->getFrameX(), _viBullet->img->getFrameY());
		_viBullet->count++;

		if (_viBullet->count % 5 == 0)
		{
			_viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);

			if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX())
			{
				_viBullet->img->setFrameX(0);
			}
			_viBullet->count = 0;
		}
	}
}

void AssistanceM1::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		//_viBullet->x += cos(_viBullet->angle) * _viBullet->speed;
		//_viBullet->y -= sin(_viBullet->angle) * _viBullet->speed;
		_viBullet->y -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->getFrameWidth(),
			_viBullet->img->getFrameHeight());

		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
		{
			SAFE_DELETE(_viBullet->img);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{
			++_viBullet;
		}
	}
}

void AssistanceM1::removeBullet(int arrNum)
{
	SAFE_DELETE(_vBullet[arrNum].img);
	_vBullet.erase(_vBullet.begin() + arrNum);
}


HRESULT BoomMissile::init(int bulletMax, float range)
{
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void BoomMissile::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img);
	}
	_vBullet.clear();
}

void BoomMissile::update(void)
{
	move();
}

void BoomMissile::render()
{
	draw();
}

void BoomMissile::fire(float x, float y)
{
	if (_bulletMax <= _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.img = new GImage;
	bullet.img->init("Resources/Images/ShootingGame/Bullet/Bomb_Airplan.bmp",
		572, 504,
		1, 1,
		true,
		RGB(255, 0, 255));

	bullet.speed = 10.f;

	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.img->getFrameWidth(), bullet.img->getFrameHeight());

	_vBullet.push_back(bullet);

	//tagBullet boomer;
	//boomer.img = new GImage;
	//boomer.img->init("Resources/Images/ShootingGame/Bullet/Bomb_Bullet4.bmp",
	//	120, 128,
	//	8, 4,
	//	true,
	//	RGB(255, 0, 255));
	//boomer.x = boomer.fireX = x+100;
	//boomer.y = boomer.fireY = y+100;
	//boomer.rc = RectMakeCenter(boomer.x, boomer.y,
	//	boomer.img->getFrameWidth(), boomer.img->getFrameHeight());
	//_vBoom.push_back(boomer);

	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->fire) continue;

		_viBullet->fire = true;
		_viBullet->x = _viBullet->fireX = x;
		_viBullet->y = _viBullet->fireY = y;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

		break;
	}
}

void BoomMissile::draw(void)
{
	
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		
			_viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top, _viBullet->img->getFrameX(), _viBullet->img->getFrameY());
			
			_viBullet->count++;

			if (_viBullet->count % 5 == 0)
			{
				_viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);

				if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX())
				{
					_viBullet->img->setFrameX(0);
				}
				_viBullet->count = 0;
			}
		
		
	}


	

}

void BoomMissile::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->y -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
		{			
			SAFE_DELETE(_viBullet->img);
			_viBullet = _vBullet.erase(_viBullet);						
		}
		else
		{
			++_viBullet;
		}
	}
}



/*
_viBullet->boom->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top, _viBullet->boom->getFrameX(), _viBullet->boom->getFrameY());

			_viBullet->count++;

			if (_viBullet->count % 5 == 0)
			{
				_viBullet->boom->setFrameX(_viBullet->boom->getFrameX() + 1);

				if (_viBullet->boom->getFrameX() >= _viBullet->boom->getMaxFrameX())
				{
					_viBullet->boom->setFrameX(0);
				}
				_viBullet->count = 0;
			}*/

HRESULT EnemyBullet::init(const char* imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_range = range;
	_bulletMax = bulletMax;

	return S_OK;
}

void EnemyBullet::release(void)
{
	_vBullet.clear();
}

void EnemyBullet::update(void)
{
	move();
	/*if (_imageName == "적미사일")
	{
		move();
		cout << "일반" << endl;
	}
	else if (_imageName == "보스미사일1")
	{
		bossMove1();
		cout << "나는1" << endl;
	}
	else if (_imageName == "보스미사일2")
	{
		bossMove2();
		cout << "나는2" << endl;
	}
	else if (_imageName == "보스미사일3")
	{
		bossMove3();
		cout << "나는3" << endl;
	}*/

}

void EnemyBullet::render()
{
	draw();
}

void EnemyBullet::fire(float x, float y, float angle, float speed)
{
	if (_bulletMax <= _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.img = IMAGEMANAGER->findImage(_imageName);
	bullet.angle = angle;
	bullet.count = 0;

	bullet.speed = speed;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.img->getFrameWidth(), bullet.img->getFrameHeight());

	_vBullet.push_back(bullet);
}

void EnemyBullet::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{

		_viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top,
			_viBullet->frameX, _viBullet->frameY);
		_viBullet->count++;

		if (_viBullet->count % 15 == 0)
		{
			_viBullet->frameX++;
			//_viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);

			if (_viBullet->frameX >= _viBullet->img->getMaxFrameX())
			{
				_viBullet->frameX = 0;
				//_viBullet->img->setFrameX(0);
			}
			_viBullet->count = 0;
		}
	}
}

void EnemyBullet::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += cos(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{
			++_viBullet;
		}
	}
}

void EnemyBullet::bossMove1()
{

}

void EnemyBullet::bossMove2()
{

}

void EnemyBullet::bossMove3()
{

}

void EnemyBullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);

}


