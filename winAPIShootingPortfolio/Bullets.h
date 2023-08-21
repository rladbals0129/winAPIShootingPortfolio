#pragma once
#include "GameNode.h"

#define BULLETS_COUNT 4.0f

//���� �Ѿ˾��� ���� �Ѿ˾���.. ���ð��ӿ��� �翬�ϴ�. ����Ǵ� Ư������ ��������
//����� ������ �������ִ°� ����
struct tagBullet
{
	GImage* img;
	RECT rc;
	int radius;
	int count;
	float x, y;
	float fireX, fireY;
	float angle;
	float speed;
	float frameTick;
	bool fire;
};

//�Ѿ��� ���갴ü. �������� ��� �߻�ȴ�
//��� �Ѿ��� ������ : �����̰�, �׷�����, �浹�Ѵ�

//�迭ó�� �̸� ������ �صΰ� �߻�
class Missile : public GameNode
{
protected:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
	float _range;

public:


	virtual HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render();

	void draw(void);
	//int fire(float x, float y);
	virtual void fire(float x, float y);

	virtual void move(void);

	Missile() {}
	~Missile() {}


};

// �߻簡 �ɶ����� ����� ����
class MissileM1 : public GameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
	float _range;

	int _bulletMax; // �����̵����� �ʱ⶧���� �ʿ�

public:
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render();

	void fire(float x, float y);
	void draw(void);
	void move(void);

	vector<tagBullet> getBullets(void) { return _vBullet; }
	void removeBullet(int arrNum);
	MissileM1() {}
	~MissileM1() {}
	//RECT getPos()
//{
//	for (auto& bullet : _vBullet)
//	{
//		if (!bullet.fire) continue;

//		return bullet.rc;
//	}
//}
};

class Beam : public GameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
	float _range;

	int _bulletMax;

public:
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render();

	void fire(float x, float y);
	void draw(void);
	void move(void);
	vector<tagBullet> getBullets(void) { return _vBullet; }



	Beam() {}
	~Beam() {}


};

class EnemyMissile : public GameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
	float _range;

	int _bulletMax; // �����̵����� �ʱ⶧���� �ʿ�

public:
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render();

	void fire(float x, float y);
	void draw(void);
	void move(void);

	vector<tagBullet> getBullets(void) { return _vBullet; }
	void removeBullet(int arrNum);

};