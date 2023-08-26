#pragma once
#include "GameNode.h"
#include "Rocket.h"
#include "EnemyManager.h"
#include "Boss.h"
class ShootingMap : public GameNode
{
private:
	Rocket* _rocket;
	EnemyManager* _em;
	Boss* _boss;
	int _x; 
	int _y;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void d2drender(void);
	virtual void collision(void);

};

