#include "Stdafx.h"
#include "MainGame.h"




HRESULT MainGame::init(void)
{
	GameNode::init(true);



	//_re.init(); 


	//_start = new StartScene();
	//_start->init();

	//_second = new SecondScene();
	//_second->init();
	_title = new Title;
	
	_currentScene = _title;

	assert(_currentScene != nullptr, "MainGame 초기화 부분에서 노드 파트 오류 발생"); 	// <->








	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
	//SAFE_DELETE(_start);
//	SAFE_DELETE(_second);

}

void MainGame::update(void)
{
	GameNode::update();

	_currentScene->update();

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{ 
		_shootingMap = new ShootingMap;
		_shootingMap->init();
		_currentScene = _shootingMap; 
	}


	if (KEYMANAGER->isOnceKeyDown(VK_BACK)) 
	{ 
		_shootingMap->release();
		_title->init();


		_currentScene = _title;


	}


}

void MainGame::render(void)
{

	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS); 
	//=================================================

	

	_currentScene->render();

	TIMEMANAGER->render(getMemDC());

	//=================================================
	this->getBackBuffer()->render(getHDC());

}