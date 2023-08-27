#pragma once
#include "GameNode.h"
class Enemy : public GameNode
{
protected:
	GImage* _image;
	RECT _rc;

	int _currentFrameX;
	int _currentFrameY;

	float _x, _y;
	float _rndTimeCount;
	float _worldTimeCount;

	float _angle;
	float _startAngle;

	bool _die;
	bool _deleteObject;
	int _diePosX;
	int _diePosY;

	float _rndFireCount;
	float _bulletFireCount;


	float radius;
	POINT _center;
	virtual void move(void);
	virtual void draw(void);
	virtual void animation(void);

private:

	int _effectCurrentFrameX;
	int _effectCurrentFrameY;
	bool _effectPlaying;
	int _animationSpeed;
	int _animationCount;

public:
	virtual HRESULT init(void);
	virtual HRESULT init(const char* imageName, POINT position);
	virtual HRESULT init(const char* imageName, POINT position, float startAngle);
	void release(void);
	virtual void update(void);
	virtual void render(void);
	virtual void d2drender(void);
	virtual bool bulletCountFire();
	void playEffect();

	RECT getRect(void) { return _rc; }


	int getDiePosX() { return _diePosX; }
	int getDiePosY() { return _diePosY; }


	bool getDie() { return _die; }
	bool getDeleteObjet() { return _deleteObject; }
	void setDie(bool die) { _die = die; _diePosX = _rc.left - 80; _diePosY = _rc.top - 50; if (die) playEffect(); }
	bool isEffectPlaying() { return _effectPlaying; }


	




	Enemy(void);
	~Enemy(void) {}

};
