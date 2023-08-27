#pragma once
#include "Enemy.h"
enum MovePattern
{
	CIRCLE_PATTERN,
	BOUNCE_PATTERN,
	CENTER_CIRCLE_PATTERN,
	WAVE_PATTERN
};
class Minion : public Enemy
{
private:
	RECT _hpBar;
	RECT _currentHpBar;
	int _hp;
	bool _die;
	MovePattern _movePattern;
	int _speedX;
	int _speedY;

	int attackSpeed;
	int attackDelayTime;

	bool _create;
public:
	HRESULT init(const char* imageName, POINT position);
	HRESULT init(const char* imageName, POINT position, float startAngle);
	void update(void);
	void render(void);
	void move();
	

	bool bulletCountFire();


	Minion(MovePattern movePattern = CIRCLE_PATTERN);
	~Minion();
};
