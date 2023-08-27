#include "stdafx.h"
#include "Rocket.h"
#include "EnemyManager.h"
#include "Boss.h"

HRESULT Rocket::init(void)
{
	_x = static_cast<float>(WINSIZE_X / 2);
	_y = static_cast<float>(WINSIZE_Y + 40);
	_createY = WINSIZE_Y + 40;

	_image = IMAGEMANAGER->addFrameImage("로켓", "Resources/Images/ShootingGame/Player/Move_LR_A.bmp",
		560, 78,
		9, 1,
		true,
		RGB(255, 0, 255));


	
	_imageEnd = IMAGEMANAGER->addImage("로켓엔딩", "Resources/Images/ShootingGame/Player/Player_Ending.bmp",
		446,
		152,
		true, RGB(255, 0, 255));
	_animA = new Animation;


	_animA->init(_imageEnd->getWidth(), _imageEnd->getHeight(), 63, 152);
	
	_animA->setDefPlayFrame(false, true);
	_animA->setFPS(12);	

	//_animMove = new Animation;
	//_animMove->init(_image->getWidth(), _image->getHeight(), 63, 78);
	//_animMove->setDefPlayFrame(false, true);
	//_animMove->setFPS(12);
	_createPlayer = false;

	_currentHp = 10;
	_maxHp = 10;
	_hpBar = new ProgressBar;
	_hpBar->init(_x, _y, 54, 4);

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	//_flame = new Flame;
	//_flame->init("불", &_x, &_y);
	_gameClear = false;
	_goTitle = false;
	_currentFrame = 3;
	_boomMissile = new BoomMissile;
	_boomMissile->init(2, 800.f);
	_beamIrradiation = false;

	_missile = new MissileM1;
	_missile->init(50, 800.f);

	_assistM1Left = new AssistanceM1;
	_assistM1Right = new AssistanceM1;
	_assistM1Left->init(1, 800.f);
	_assistM1Right->init(1, 800.f);

	return S_OK;
}

void Rocket::release(void)
{
	//_flame->release();
	//SAFE_DELETE(_flame);

	_missile->release();
	SAFE_DELETE(_missile);

	_boomMissile->release();
	SAFE_DELETE(_boomMissile);

	_animA->release();
	SAFE_DELETE(_animA);

}

void Rocket::update(void)
{
	if (!_createPlayer)
	{
		
		
		_y--;
		_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		if (_y < WINSIZE_Y - 120)
		{
			_createPlayer = true;
		}
		
	}

	if (_createPlayer && !_gameClear)
	{

		if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _rc.right < WINSIZE_X && !_beamIrradiation)
		{
			_x += ROCKET_SPEED;
			_leftRightCount += TIMEMANAGER->getElapsedTime();
			if (_leftRightCount >= 1.f/6.f && _currentFrame <6)
			{
				_leftRightCount -= 1.f / 6.f;
				_currentFrame++;
				cout << _currentFrame << endl;
			}	
		}
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			_leftRightCount = 0;
			_currentFrame = 3;
		}

		if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _rc.left > 0 && !_beamIrradiation)
		{
			_x -= ROCKET_SPEED;
			_leftRightCount += TIMEMANAGER->getElapsedTime();
			if (_leftRightCount >= 1.f / 6.f && _currentFrame > 0)
			{
				_leftRightCount -= 1.f / 6.f;
				_currentFrame--;
				cout << _currentFrame << endl;
			}
			
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			_leftRightCount = 0;
			_currentFrame = 3;
		}

		if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _rc.bottom < WINSIZE_Y)
		{
			_y += (ROCKET_SPEED+2);
		}

		if (KEYMANAGER->isStayKeyDown(VK_UP) && _rc.top > 0)
		{
			_y -= ROCKET_SPEED;
		}

		_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight()- 10);



		usingSkill();
		
		if (KEYMANAGER->isOnceKeyDown('A'))
		{
			_boomMissile->fire(286, WINSIZE_Y);
			_boomMissile->fire(WINSIZE_X/2 + 286, WINSIZE_Y);
		}

		switch (_setWeapon)
		{
		case MISSILE:
			if (KEYMANAGER->isStayKeyDown(VK_SPACE))
			{
				if (attackDeleyTime % 8 == 0)
				{
					_missile->fire("Resources/Images/ShootingGame/Bullet/BulletPower1.bmp",(_rc.left + _rc.right) / 2, _rc.top);
				}
				if (attackDeleyTime % 20 == 0 && attackDeleyTime !=0)
				{
					_assistM1Left->fire(_rc.left, _rc.top);
					//_assistM1Left->fire(_rc.right, _rc.top);
					_assistM1Right->fire(_rc.right, _rc.top);
				}
				
				attackDeleyTime++;
			}
			else if(KEYMANAGER->isOnceKeyUp(VK_SPACE))
			{
				attackDeleyTime = 0;
			}
			break;
		case MISSILE2:
			if (KEYMANAGER->isStayKeyDown(VK_SPACE))
			{
				if (attackDeleyTime % 8 == 0)
				{
					_missile->fire("Resources/Images/ShootingGame/Bullet/AV_8_Player_Bullet2.bmp", (_rc.left + _rc.right) / 2, _rc.top);
				}
				if (attackDeleyTime % 20 == 0 && attackDeleyTime != 0)
				{
					_assistM1Left->fire(_rc.left, _rc.top);
					_assistM1Right->fire(_rc.right, _rc.top);
				}

				attackDeleyTime++;
			}
			else if (KEYMANAGER->isOnceKeyUp(VK_SPACE))
			{
				attackDeleyTime = 0;
			}

			break;
		case MISSILE3:
			if (KEYMANAGER->isStayKeyDown(VK_SPACE))
			{
				if (attackDeleyTime % 8 == 0)
				{
					_missile->fire("Resources/Images/ShootingGame/Bullet/AV_8_Player_Bullet3.bmp", _rc.left +44, _rc.top);
					_missile->fire("Resources/Images/ShootingGame/Bullet/AV_8_Player_Bullet3.bmp", _rc.right-44 , _rc.top);
				}
				if (attackDeleyTime % 20 == 0 && attackDeleyTime != 0)
				{
					_assistM1Left->fire(_rc.left, _rc.top);
					_assistM1Right->fire(_rc.right, _rc.top);
				}

				attackDeleyTime++;
			}
			else if (KEYMANAGER->isOnceKeyUp(VK_SPACE))
			{
				attackDeleyTime = 0;
			}

			break;
		case MISSILE4:
			if (KEYMANAGER->isStayKeyDown(VK_SPACE))
			{
				if (attackDeleyTime % 8 == 0)
				{
					_missile->fire("Resources/Images/ShootingGame/Bullet/AV_8_Player_Bullet4.bmp", (_rc.left + _rc.right) / 2, _rc.top);
					_missile->fire("Resources/Images/ShootingGame/Bullet/AV_8_Player_Bullet4.bmp", _rc.left, _rc.top);
					_missile->fire("Resources/Images/ShootingGame/Bullet/AV_8_Player_Bullet4.bmp", _rc.right, _rc.top);
				}
				if (attackDeleyTime % 20 == 0 && attackDeleyTime != 0)
				{
					_assistM1Left->fire(_rc.left, _rc.top);
					_assistM1Right->fire(_rc.right, _rc.top);
				}

				attackDeleyTime++;
			}
			else if (KEYMANAGER->isOnceKeyUp(VK_SPACE))
			{
				attackDeleyTime = 0;
			}
			break;
		case BEAM:
			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			{
				//_boomMissile->fire(_x, _y - 430);
				//_beamIrradiation = true;
			}
			else
			{
				//_beamIrradiation = false;
			}

			break;
		default:
			break;
		}



		_hpBar->setX(_x - (_rc.right - _rc.left) / 2);
		_hpBar->setY(_y - (_rc.bottom - _rc.top) / 2);
		_hpBar->update();
		_hpBar->setGauge(_currentHp, _maxHp);
		_hpBar->update();

		_missile->update();
		_assistM1Left->update();
		_assistM1Right->update();
		_boomMissile->update();
		//_flame->update();
	}

	else if (_gameClear)
	{
		//_rc = RectMakeCenter(_x, _y, _imageEnd->getFrameWidth(), _imageEnd->getFrameHeight() - 10);
		if (!_animCrate)
		{
			_animA->AniStart();
			_animCrate = true;
		}

		if (_animA->getNowPlayIdx() > 4)
		{
			if (!_setCreateAnim)
			{
				_animA->setPlayFrame(4, 6, false, true);

				_setCreateAnim = true;
			}

		}

		if (!_setCreateAnim)
		{
			_rc.top--;
			_rc.bottom--;
			_animA->frameUpdate(0.016f);
		}
		else
		{
			_animA->frameUpdate(0.016f, 4);
			_rc.top-=3;
			_rc.bottom -= 3;
			if (_rc.bottom < -100)
			{
				_goTitle = true;
			//	cout << "굿ㅋㅋ" << endl;
			}
		}
	}
}

void Rocket::render()
{
	if (KEYMANAGER->isToggleKey(VK_F7))
	{
		DrawRectMake(getMemDC(), _rc);
	}
	if (!_gameClear)
	{
		_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrame, 0);
		//_flame->render();
		_missile->render();
		_assistM1Left->render();
		_assistM1Right->render();
		_boomMissile->render();
		_hpBar->render();
	}

	
	if (_gameClear)
	{
		_imageEnd->aniRender(getMemDC(), _rc.left, _rc.top, _animA);
	}
	
	
}

void Rocket::usingSkill()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		_setWeapon = MISSILE;
		/*_missile = nullptr;
		_missile = new MissileBase;
		_missile->init(50,600.f);*/
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		_setWeapon = MISSILE2;
		//_missile = nullptr;


		//_missile = new MissileShotGun;
		//_missile->init(50,600.f);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		_setWeapon = MISSILE3;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F4))
	{
		_setWeapon = MISSILE4;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F5))
	{
		_setWeapon = BEAM;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F6))
	{

	}
	
}

void Rocket::removeMissile(int arrNum)
{
	_missile->removeBullet(arrNum);
}

void Rocket::removeAssiMissileLeft(int arrNum)
{
	_assistM1Left->removeBullet(arrNum);
}

void Rocket::removeAssiMissileRight(int arrNum)
{
	_assistM1Right->removeBullet(arrNum);
}



/*
엔딩에쓰기

if(!_animCrate)
		{
			_animA->AniStart();
			_animCrate = true;
		}

		if (_animA->getNowPlayIdx() > 4)
		{
			if (!_setCreateAnim)
			{
				_animA->setPlayFrame(4, 6, false, true);

				_setCreateAnim = true;
			}

		}

		if (!_setCreateAnim)
		{
			_createY -= 5;
			_animA->frameUpdate(0.016f);
		}
		else
		{
			_animA->frameUpdate(0.016f,4);
			_createY += 1;
			if (_createY > 700)
			{
				_createPlayer = true;
			}
		}


		cout << _animA->getNowPlayIdx() << endl;


		==렌더==
			_imageEnd->aniRender(getMemDC(), WINSIZE_X / 2, _createY, _animA);
*/