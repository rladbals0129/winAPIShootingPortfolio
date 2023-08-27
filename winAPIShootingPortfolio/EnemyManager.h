#pragma once
#include "GameNode.h"
#include "Enemy.h"
#include "Bullets.h"
#include "Boss.h"
class Rocket;

class EnemyManager : public GameNode
{
private:
	typedef vector<Enemy*> vEnemy;
	typedef vector<Enemy*>::iterator viEnemy;
private:
	vEnemy _vMinion; 
	viEnemy _viMinion;

private:
	EnemyBullet* _bullet;
	Rocket* _rocket;
	
	float _gameTime;

private:
	Boss* _boss;
	EnemyBullet* _bossBullet1;
	EnemyBullet* _bossBullet2;
	EnemyBullet* _bossBullet3;
	bool _bossCreate;

private:
	int _wave;
	int _enemyIndex;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void d2drender(void);

	
	void spawnEnemy(void);



	void removeMinion(int arrNum);

	void minionBulletFire(void);
	void collision(void);

	vector<Enemy*> getMinions(void) { return _vMinion; }
	EnemyBullet* getBullet(void) { return _bullet; }

	Boss* getBoss(void) { return _boss; }


	void setRocketMemoryAddress(Rocket* rk) { _rocket = rk; }
};

