#pragma once
#include "GameNode.h"
#include "Title.h"
#include "ShootingMap.h"
//#include "ResourceClass.h"

class MainGame : public GameNode
{
private:
	int _alphaA;
	bool _isAlphaIncrese;

	//ResourceClass _re; 
	//StartScene* _start;
	//SecondScene* _second;
	//Rocket* _rocket;
	Title* _title;
	ShootingMap* _shootingMap;

	GameNode* _currentScene; 

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();

	MainGame() : _currentScene(nullptr) {} 
};



