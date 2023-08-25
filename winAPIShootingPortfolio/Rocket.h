#pragma once
#include "GameNode.h"
//#include "Flame.h"
#include "Bullets.h"
#include "Animation.h"

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

class Rocket : public GameNode
{
private:
	GImage* _imageEnd;
	GImage* _image;
	GameState _gameState;
	//Flame* _flame;

	float _leftRightCount;
	int _currentFrame;
	Animation* _animA;
	Animation* _animMove;
	//skill
	EWeapon _setWeapon;
	MissileM1* _missile;
	AssistanceM1* _assistM1Left;
	AssistanceM1* _assistM1Right;
	Beam* _beam;
	bool _beamIrradiation;

	int _createY;
	bool _animCrate;
	bool _setCreateAnim;

	RECT _rc;
	float _x, _y;

	bool _createPlayer;

	int attackDeleyTime;



public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();

	void usingSkill();

	MissileM1* getMissileM1() { return _missile; }
	AssistanceM1* getAssiM1L() { return _assistM1Left; }
	AssistanceM1* getAssiM1R() { return _assistM1Right; }
	Beam* getBeam() { return _beam; }
	RECT getRect(void) { return _rc; }
	void removeMissile(int arrNum);
	void removeAssiMissileLeft(int arrNum);
	void removeAssiMissileRight(int arrNum);
};
