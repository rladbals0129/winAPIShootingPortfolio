#include "Stdafx.h"
#include "MainGame.h"




HRESULT MainGame::init(void)
{
	GameNode::init(true);

	_shootingMap = new ShootingMap;
	_CharacterChoose = new CharacterChoose;
	_title = new Title;
	_title->init();

	_currentScene = _title;

	assert(_currentScene != nullptr, "MainGame �ʱ�ȭ �κп��� ��� ��Ʈ ���� �߻�"); 	// <->








	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();


}

void MainGame::update(void)
{
	GameNode::update();

	_currentScene->update();

	if (_title->getNextScene())
	{
		if (_currentScene == _title)
		{
			_CharacterChoose->init();
			_currentScene = _CharacterChoose;
		}
	}

	if (_CharacterChoose->getNextScene())
	{
		if (_currentScene == _CharacterChoose)
		{
			_shootingMap->init();
			_currentScene = _shootingMap;
		}
	}


	if (_shootingMap->getGoTitle())
	{
		if (_currentScene == _shootingMap)
		{
			
			_title->init();
			_currentScene = _title;
		}
	}

	

}

void MainGame::render(void)
{

	if (_currentScene != _title)
	{
		PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
		//=================================================
		_currentScene->render();
		D2DMANAGER->beginDraw();
		_currentScene->d2drender();
		D2DMANAGER->endDraw();
		TIMEMANAGER->render(getMemDC());
		//=================================================
		this->getBackBuffer()->render(getHDC());
	}


}