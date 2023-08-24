#include "stdafx.h"
#include "ShootingMap.h"

HRESULT ShootingMap::init(void)
{
	//GameNode::init(true);

	IMAGEMANAGER->addImage("½´ÆÃ¸Ê", "Resources/Images/ShootingGame/BackGround/Stage_1.bmp",
		WINSIZE_X,18164);

	_rocket = new Rocket;
	_rocket->init();
	_em = new EnemyManager;
	_em->init();
	_y = -18164 + WINSIZE_Y;
	//_em->setMissileM1(_rocket->getMissileM1());
	//_em->setBeam(_rocket->getBeam());
	return S_OK;
}

void ShootingMap::release(void)
{


}

void ShootingMap::update(void)
{
	collision();

	_y +=2;

	_rocket->update();
	_em->update();
}

void ShootingMap::render(void)
{
	//RECT rc = { 0,0, WINSIZE_X,WINSIZE_Y };
	IMAGEMANAGER->findImage("½´ÆÃ¸Ê")->render(getMemDC(),_x,_y);
	_rocket->render();
	_em->render();


}

void ShootingMap::d2drender(void)
{
	_em->d2drender();
}
