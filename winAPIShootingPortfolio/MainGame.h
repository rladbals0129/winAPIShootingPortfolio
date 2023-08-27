#pragma once
#include "GameNode.h"
#include "Title.h"
#include "CharacterChoose.h"
#include "ShootingMap.h"

class MainGame : public GameNode
{
private:

	bool _isTitle;
	bool _isChoice;
	bool _inGame;
	Title* _title;
	CharacterChoose* _CharacterChoose;
	ShootingMap* _shootingMap;	


	GameNode* _currentScene; 



public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();

	MainGame() : _currentScene(nullptr) {} 
};



