#include "stdafx.h"
#include "ShootingMap.h"

HRESULT ShootingMap::init(void)
{
	TIMEMANAGER->init();
	IMAGEMANAGER->addImage("½´ÆÃ¸Ê", "Resources/Images/ShootingGame/BackGround/Stage_1.bmp",
		WINSIZE_X,18164);

	_rocket = new Rocket;
	_rocket->init();
	_em = new EnemyManager;
	_em->init();
	_y = - 18164 + WINSIZE_Y;
	_boss = new Boss;

	_em->setRocketMemoryAddress(_rocket);
	_rocket->setEnemyManagerMemoryAddress(_em);

	_rocket->setBossMemoryAddress(_em->getBoss());
	_em->getBoss()->setRocketMemoryAddress(_rocket);


	return S_OK;
}

void ShootingMap::release(void)
{


}

void ShootingMap::update(void)
{
	collision();

	_y -= 6;

	_rocket->update();
	_em->update();
	if (_rocket->getGoTitle())
	{
		_goTitle = true;
	}
}

void ShootingMap::render(void)
{
	RECT rc = { 0,0, WINSIZE_X,18164 };
	IMAGEMANAGER->findImage("½´ÆÃ¸Ê")->loopRender(getMemDC(),&rc,_x,_y);
	_rocket->render();
	_em->render();


}

void ShootingMap::d2drender(void)
{
	_em->d2drender();
}
