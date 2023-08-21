#pragma once
#include "GameNode.h"
#include "Enemy.h"

class EnemyManager : public GameNode
{
private:
	typedef vector<Enemy*> vEnemy;
	//Ÿ�� ������: ���� ������ ���� �����ϱ� ����
	//Enemy������ ����
	typedef vector<Enemy*>::iterator viEnemy;
private:
	vEnemy _vMinion; //������ �θ� ��ü�� �������
	//�Ļ��� ���� ������ ����
	viEnemy _viMinion;
	int* _minionHP;

	//vEnemy _vSnake;
	//viEnemy _viSnake;

	/*
	vEnemy ������
	....���


	*/
private:
	
	RECT _colider;

private:


	RECT _hpBar;
	RECT _currentHpBar;

	vector<bool> _vIsErased;

private:

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setMinion(void);
	//void setSnake(void);


	void removeMinion(int arrNum);

	vector<Enemy*> getMinions(void) { return _vMinion; }
	//vector<Enemy*> getSnake(void) { return _vSnake; }
	void setErased(int arrNum) { _vIsErased[arrNum] = true; }

};