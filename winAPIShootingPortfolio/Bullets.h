#pragma once
#include "GameNode.h"

#define BULLETS_COUNT 4.0f


struct tagBullet
{
	GImage* img;

	GImage* boom;

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


//class Missile : public GameNode
//{
//protected:
//	vector<tagBullet> _vBullet;
//	vector<tagBullet>::iterator _viBullet;
//	float _range;
//
//public:
//
//
//	virtual HRESULT init(int bulletMax, float range);
//	void release(void);
//	void update(void);
//	void render();
//
//	void draw(void);
//	//int fire(float x, float y);
//	virtual void fire(float x, float y);
//
//	virtual void move(void);
//
//	Missile() {}
//	~Missile() {}
//
//
//};


class MissileM1 : public GameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
	float _range;

	int _bulletMax; // 장전이되있지 않기때문에 필요

public:
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render();

	void fire(const char* filepath, float x, float y);
	void draw(void);
	void move(void);

	vector<tagBullet> getBullets(void) { return _vBullet; }
	void removeBullet(int arrNum);
	MissileM1() {}
	~MissileM1() {}

};

class Beam : public GameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
	vector<tagBullet> _vBoom;
	vector<tagBullet>::iterator _viBoom;
	float _range;

	int _bulletMax;
	bool _createBoobBullet;

public:
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render();

	void fire(float x, float y);
	void draw(void);
	void move(void);
	void boobBulletAnim();
	vector<tagBullet> getBullets(void) { return _vBullet; }



	Beam() {}
	~Beam() {}


};

class AssistanceM1 : public GameNode
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
	void removeBullet(int arrNum);

	AssistanceM1() {}
	~AssistanceM1() {}
};

class EnemyMissile : public GameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
	float _range;

	int _bulletMax; // 장전이되있지 않기때문에 필요

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