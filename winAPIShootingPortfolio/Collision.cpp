#include "stdafx.h"
#include "ShootingMap.h"

void ShootingMap::collision(void)
{
	for (int i = 0; i < _rocket->getMissileM1()->getBullets().size(); i++)
	{
		for (int j = 0; j < _em->getMinions().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_rocket->getMissileM1()->getBullets()[i].rc,
				&CollisionAreaResizing(_em->getMinions()[j]->getRect(), 40, 30)))
			{
				_em->getMinions()[j]->setDie(true);

				_rocket->removeMissile(i);
				break;
			}
		}
	}

	for (int i = 0; i < _rocket->getMissileM1()->getBullets().size(); i++)
	{

		RECT rc;
		if (IntersectRect(&rc, &_rocket->getMissileM1()->getBullets()[i].rc,
			&_em->getBoss()->getRect()))
		{
			_em->getBoss()->setDmg(10);
			_rocket->removeMissile(i);
			break;
		}
	}

	for (int i = 0; i < _rocket->getAssiM1L()->getBullets().size(); i++)
	{

		RECT rc;
		if (IntersectRect(&rc, &_rocket->getAssiM1L()->getBullets()[i].rc,
			&_em->getBoss()->getRect()))
		{
			_em->getBoss()->setDmg(10);
			_rocket->removeAssiMissileLeft(i);
			_rocket->removeAssiMissileRight(i);
			break;
		}
	}

	for (int i = 0; i < _rocket->getBoomMissile()->getBullets().size(); i++)
	{
		for (int j = 0; j < _em->getMinions().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_rocket->getBoomMissile()->getBullets()[i].rc,
				&CollisionAreaResizing(_em->getMinions()[j]->getRect(), 40, 30)))
			{
				_em->getMinions()[j]->setDie(true);
				//_em->setErased(j);
				//_em->removeMinion(j);
				break;
			}
		}
	}


	for (int i = 0; i < _rocket->getAssiM1L()->getBullets().size(); i++)
	{
		for (int j = 0; j < _em->getMinions().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_rocket->getAssiM1L()->getBullets()[i].rc,
				&CollisionAreaResizing(_em->getMinions()[j]->getRect(), 40, 30)))
			{
				_em->getMinions()[j]->setDie(true);
				_rocket->removeAssiMissileLeft(i);
				break;
			}
		}
	}

	for (int i = 0; i < _rocket->getAssiM1R()->getBullets().size(); i++)
	{
		for (int j = 0; j < _em->getMinions().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_rocket->getAssiM1R()->getBullets()[i].rc,
				&CollisionAreaResizing(_em->getMinions()[j]->getRect(), 40, 30)))
			{
				_em->getMinions()[j]->setDie(true);
				_rocket->removeAssiMissileRight(i);
				break;
			}
		}
	}
}

