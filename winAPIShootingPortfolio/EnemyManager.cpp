#include "stdafx.h"
#include "EnemyManager.h"
#include "Minion.h"
#include "Rocket.h"
//#include "Snake.h"
HRESULT EnemyManager::init(void)
{
	IMAGEMANAGER->addFrameImage("적1", "Resources/Images/ShootingGame/Enemy/enemy1.bmp", 0.f, 0.f,
		78, 64,
		1, 1, true, RGB(255, 0, 255));
	
	_gameTime = TIMEMANAGER->getWorldTime();
	_wave = 0;
	_enemyIndex = 0;

	IMAGEMANAGER->addFrameImage("적미사일", "Resources/Images/ShootingGame/Bullet/enemyBullets2.bmp",
		120, 20,
		9,1,
		true,
		RGB(255, 0, 255));
	_bullet = new EnemyBullet;
	_bullet->init("적미사일", 30, 1000);


	IMAGEMANAGER->addFrameImage("보스", "Resources/Images/ShootingGame/Enemy/enemyBoss1.bmp",0,0,
		7520, 372,
		20, 1,
		true,
		RGB(255, 0, 255));

	_boss = new Boss;
	_boss->setRocketMemoryAddress(_rocket);
	//_wave = 3;


	return S_OK;
}

void EnemyManager::release(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->release();
		SAFE_DELETE(*_viMinion);
	}
}

void EnemyManager::update(void)
{
	_gameTime = TIMEMANAGER->getWorldTime();
	
	

	float spawnIntervalInSeconds = 1.f;
	static float nextSpawnTime = spawnIntervalInSeconds + 10.f;
	if (_gameTime > nextSpawnTime)
	{
		spawnEnemy();
		nextSpawnTime += spawnIntervalInSeconds;
	}

	for (int i = 0; i < _vMinion.size(); i++)
	{

		if (_vMinion[i]->getDie() && !_vMinion[i]->isEffectPlaying()) 
		{
			removeMinion(i); 
			--i;
		}
		else
		{
			_vMinion[i]->update();
		}

	}

	if (_wave == 3 && _bossCreate)
	{
		_boss->update();

		//_bossBullet1->update();
		//_bossBullet2->update();
	}



	minionBulletFire();
	_bullet->update();
	collision();
}

void EnemyManager::render()
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->render();
	}

	if (_wave == 3 && _bossCreate)
	{
		_boss->render();
		//_bossBullet1->render();
		//_bossBullet2->render();
	}
	
	_bullet->render();
	
}

void EnemyManager::d2drender()
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->d2drender();
	}

}


void EnemyManager::spawnEnemy(void)
{

	if (_wave == 0)
	{
		if (_enemyIndex < 8)
		{
			//int i = _enemyIndex / 4;
			//int j = _enemyIndex % 4;

			Enemy* jellyFish = new Minion(MovePattern::CIRCLE_PATTERN);
			float startAngle = 0;
			jellyFish->init("적1", PointMake(0, 0), startAngle);

			_vMinion.push_back(jellyFish);
		}
		else if (_enemyIndex < 16)
		{
			int i = _enemyIndex / 4;
			int j = _enemyIndex % 4;

			Enemy* jellyFish = new Minion(MovePattern::CIRCLE_PATTERN);
			float startAngle = static_cast<float>(i * 4 + j) / (4 * 2) * (2 * PI);
			jellyFish->init("적1", PointMake(WINSIZE_X, 0), startAngle);

			_vMinion.push_back(jellyFish);
		}
		++_enemyIndex;
		if (_enemyIndex >=24)
		{
			_wave++;
			_enemyIndex = 0;
			cout <<"웨이브1종료"<< _wave << "   " << _enemyIndex << endl;
			
		}
	}
	else if (_wave == 1)
	{
		cout << "웨이브1진입" << _wave << "   " << _enemyIndex << endl;
		if (_enemyIndex < 8)
		{
			for (int i = 0; i < 3; i++)
			{
				Enemy* jellyFish;
				jellyFish = new Minion(MovePattern::BOUNCE_PATTERN);
				jellyFish->init("적1", PointMake(0, 100 + i * 100));

				_vMinion.push_back(jellyFish);
			}
		
		}
		else if (_enemyIndex < 16)
		{
			
			for (int i = 0; i < 3; i++)
			{
				Enemy* jellyFish;
				jellyFish = new Minion(MovePattern::BOUNCE_PATTERN);
				jellyFish->init("적1", PointMake(WINSIZE_X, 100 + i * 100));

				_vMinion.push_back(jellyFish);
			}
		
		}
		_enemyIndex++;
		if (_enemyIndex >= 24)
		{
			_wave++;
			_enemyIndex = 0;
			cout << "웨이브2종료" << _wave << "   " << _enemyIndex << endl;

		}
	}
	else if (_wave == 2)
	{
		if (_enemyIndex < 8)
		{
			Enemy* jellyFish;
			jellyFish = new Minion(MovePattern::WAVE_PATTERN);
			jellyFish->init("적1", PointMake(0, 300));

			_vMinion.push_back(jellyFish);
		}
		else if (_enemyIndex < 16)
		{
			Enemy* jellyFish;
			jellyFish = new Minion(MovePattern::WAVE_PATTERN);
			jellyFish->init("적1", PointMake(WINSIZE_X, 300));

			_vMinion.push_back(jellyFish);
		}
		_enemyIndex++;

		if (_enemyIndex >= 24)
		{
			_wave++;
			_enemyIndex = 0;
			cout << "웨이브3종료" << _wave << "   " << _enemyIndex << endl;

		}

	}
	else if (_wave == 3)
	{
		if (!_bossCreate)
		{
			_boss->init("보스", PointMake(WINSIZE_X / 2, -200));
			_bossCreate = true;
		}
		
	}



}


void EnemyManager::removeMinion(int arrNum)
{
	SAFE_DELETE(_vMinion[arrNum]);
	_vMinion.erase(_vMinion.begin() + arrNum);
}

void EnemyManager::minionBulletFire(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		if ((*_viMinion)->bulletCountFire())
		{
			RECT rc = (*_viMinion)->getRect();
			_bullet->fire(rc.left + (rc.right + -rc.left) / 2, rc.bottom + (rc.top - rc.bottom) / 2 + 30,
				getAngle(rc.left + (rc.right + -rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2,
					_rocket->getPosition().x,
					_rocket->getPosition().y), RND->getFromFloatTo(2.f, 4.f));
		}
	}
}

void EnemyManager::collision(void)
{
	for (int i = 0; i < _bullet->getBullet().size(); i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_bullet->getBullet()[i].rc,
			&_rocket->getRect()))
		{
			_bullet->removeBullet(i);
			_rocket->hitDamage(2.f);
		}
	}
}






/*


void EnemyManager::setMinion(void)
{


		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				Enemy* jellyFish;
				jellyFish = new Minion(MovePattern::CIRCLE_PATTERN);// Minion 객체 생성
				// 적 추가 및 초기화
				float startAngle = static_cast<float>(i * 4 + j) / (4 * 2) * (2 * PI);
				jellyFish->init("적1", PointMake(0, 0), startAngle);

				_vMinion.push_back(jellyFish); // 벡터에 적 객체 추가

			}
		}



		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				Enemy* jellyFish;
				jellyFish = new Minion(MovePattern::CIRCLE_PATTERN);// Minion 객체 생성
				// 적 추가 및 초기화
				float startAngle = static_cast<float>(i * 4 + j) / (4 * 2) * (2 * PI);
				jellyFish->init("적1", PointMake(WINSIZE_X, 0), startAngle);

				_vMinion.push_back(jellyFish); // 벡터에 적 객체 추가

			}
		}




	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Enemy* jellyFish;
			jellyFish = new Minion(MovePattern::BOUNCE_PATTERN); //업케스팅
			jellyFish->init("적1", PointMake(250 + j * 200, 100 + i * 100));

			_vMinion.push_back(jellyFish);


		}

	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			POINT start = { 250 + j * 200, 100 + i * 100 };
			Enemy* jellyFish;
			jellyFish = new Minion(MovePattern::CENTER_CIRCLE_PATTERN);
			float startAngle = 0;
			jellyFish->init("적1", start, startAngle);
			_vMinion.push_back(jellyFish);


		}

	}



}


*/