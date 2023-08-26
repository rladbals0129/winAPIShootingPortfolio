#pragma once
#include "GameNode.h"
//#include "Flame.h"
#include "Bullets.h"
#include "Animation.h"
#include "ProgressBar.h"

#define ROCKET_SPEED 3.0f

enum GameState
{
	PLAY, END
};

enum EWeapon
{
	MISSILE, BEAM ,
	MISSILE2,MISSILE3,
	MISSILE4
};

class EnemyManager;
class Boss;

class Rocket : public GameNode
{
private:
	GImage* _imageEnd;
	GImage* _image;
	GameState _gameState;
	//Flame* _flame;
	EnemyManager* _em;
	Boss* _boss;

	float _leftRightCount;
	int _currentFrame;
	Animation* _animA;
	Animation* _animMove;
	//skill
	EWeapon _setWeapon;
	MissileM1* _missile;
	AssistanceM1* _assistM1Left;
	AssistanceM1* _assistM1Right;
	BoomMissile* _boomMissile;
	bool _beamIrradiation;

	int _createY;
	bool _animCrate;
	bool _setCreateAnim;

	RECT _rc;
	float _x, _y;

	bool _createPlayer;

	int attackDeleyTime;

	ProgressBar* _hpBar;
	int _maxHp;
	int _currentHp;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();

	void usingSkill();

	MissileM1* getMissileM1() { return _missile; }
	AssistanceM1* getAssiM1L() { return _assistM1Left; }
	AssistanceM1* getAssiM1R() { return _assistM1Right; }
	BoomMissile* getBoomMissile() { return _boomMissile; }

	RECT getRect(void) { return _rc; }
	void removeMissile(int arrNum);
	void removeAssiMissileLeft(int arrNum);
	void removeAssiMissileRight(int arrNum);
	void hitDamage(float x) { _currentHp -= x; }
	void setEnemyManagerMemoryAddress(EnemyManager* em) { _em = em; }
	void setBossMemoryAddress(Boss* boss) { _boss = boss; }
	

	POINT getPosition() { return PointMake((int)_x, (int)_y); }
};
