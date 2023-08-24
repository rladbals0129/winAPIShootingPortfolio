#include "stdafx.h"
#include "Rocket.h"

HRESULT Rocket::init(void)
{
	_x = static_cast<float>(WINSIZE_X / 2);
	_y = static_cast<float>(WINSIZE_Y / 2);
	_createY = WINSIZE_Y + 40;

	_image = IMAGEMANAGER->addFrameImage("肺南", "Resources/Images/ShootingGame/Player/Move_LR_A.bmp",
		446, 78,
		7, 1,
		true,
		RGB(255, 0, 255));



	_imageCreate = IMAGEMANAGER->addImage("肺南积己", "Resources/Images/ShootingGame/Player/Player_Ending.bmp",
		446,
		152,
		true, RGB(255, 0, 255));
	_animA = new Animation;


	_animA->init(_imageCreate->getWidth(), _imageCreate->getHeight(), 63, 152);
	
	_animA->setDefPlayFrame(false, true);
	_animA->setFPS(3);

	_createPlayer = false;


	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	_flame = new Flame;
	_flame->init("阂", &_x, &_y);

	_currentFrame = 1;
	_beam = new Beam;
	_beam->init(1, 0.5f);
	_beamIrradiation = false;

	_missile = new MissileM1;
	_missile->init(50, 600.f);

	return S_OK;
}

void Rocket::release(void)
{
	_flame->release();
	SAFE_DELETE(_flame);

	_missile->release();
	SAFE_DELETE(_missile);

	_beam->release();
	SAFE_DELETE(_beam);

	_animA->release();
	SAFE_DELETE(_animA);

}

void Rocket::update(void)
{
	if (!_createPlayer)
	{
		
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
		//cout << _createPlayer << endl;
	}

	if (_createPlayer)
	{

		if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _rc.right < WINSIZE_X && !_beamIrradiation)
		{
			_x += ROCKET_SPEED;
			
		}
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			
		}

		if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _rc.left > 0 && !_beamIrradiation)
		{
			_x -= ROCKET_SPEED;
			
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			
		}

		if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _rc.bottom < WINSIZE_Y)
		{
			_y += ROCKET_SPEED;
		}

		if (KEYMANAGER->isStayKeyDown(VK_UP) && _rc.top > 0)
		{
			_y -= ROCKET_SPEED;
		}

		_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());



		usingSkill();

		switch (_setWeapon)
		{
		case MISSILE:
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_missile->fire((_rc.left + _rc.right) / 2, _rc.top);
			}
			break;
		case BEAM:
			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			{
				_beam->fire(_x, _y - 430);
				_beamIrradiation = true;
			}
			else
			{
				_beamIrradiation = false;
			}

			break;
		default:
			break;
		}



		_missile->update();
		_beam->update();
		_flame->update();
	}
	
}

void Rocket::render()
{
	if (!_createPlayer)
	{
		_imageCreate->aniRender(getMemDC(), WINSIZE_X / 2, _createY, _animA);
	}
	else
	{
		_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrame, 0);
		_flame->render();
		_missile->render();
		_beam->render();
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
		_setWeapon = BEAM;
		//_missile = nullptr;


		//_missile = new MissileShotGun;
		//_missile->init(50,600.f);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{

	}
	if (KEYMANAGER->isOnceKeyDown(VK_F4))
	{

	}
	if (KEYMANAGER->isOnceKeyDown(VK_F5))
	{

	}
	if (KEYMANAGER->isOnceKeyDown(VK_F6))
	{

	}
	if (KEYMANAGER->isOnceKeyDown(VK_F7))
	{

	}
}

void Rocket::removeMissile(int arrNum)
{
	_missile->removeBullet(arrNum);
}

