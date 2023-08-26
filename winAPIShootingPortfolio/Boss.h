#pragma once
#include "GameNode.h"
#include "Bullets.h"

class Rocket;

class Boss : public GameNode
{
private:
	GImage* _image;

	//포지션(hitBox)
	RECT _rc;
	POINT _center;
	float _speedX;



	float _initialX;  // 시작 x 위치
	float _amplitude;  // 사인 파동의 진폭
	float _frequency;  // 사인 파동의 주파수

	//==애니메이션
	float _worldTimeCount;
	float _timeCount;
	int _currentFrameX;
	int _currentFrameY;
	int _returnAnim;
	//==이펙트
	bool _effectPlaying;
	int _effectCurrentFrameX;
	int _effectCurrentFrameY;
	//==

	
	int _diePosX;
	int _diePosY;

	int _hp;
	bool _die;

	float _x, _y;

	float _angle;

	int _patternIndex;
	int _curPatternCount;

	//====총알을 발사하는 부분
	int _firePosX;
	int _firePosY;
	RECT _fireRc;
	float _spiralAngle;
	//===총알 발사 주기
	float _bulletFireCount;
	float _fireCount;

	float _lastBulletFireTime;  // 마지막으로 총알을 발사한 시간을 저장하는 변수입니다.
	float _bulletFireDelay;

	//==

	bool _create;

	//패턴주기
	float _patternDelayTime;  
	float _lastPatternTime;

	//==총알==
	EnemyBullet* _bossBullet1;
	EnemyBullet* _bossBullet2;
	EnemyBullet* _bossBullet3;

	Rocket* _rocket;
	

public:
	HRESULT init(const char* imageName, POINT position);
	void release(void);
	void update(void);
	void render();

	void pattern1();
	void pattern2();
	void pattern3();
	void pattern4();
	void pattern5();

	void collision();

	bool bulletCountFire();
	bool bulletCountFire2();
	void dieEffect();
	void animation();
	void move();

	inline RECT getRect(void) { return _rc; }
	inline RECT getFireRect(void) { return _fireRc; }
	inline int getDiePosX() { return _diePosX; }
	inline int getDiePosY() { return _diePosY; }

	inline int getPatternIndex() { return _patternIndex; }

	inline void setDmg(int dmg) { _hp -= dmg; }

	void setRocketMemoryAddress(Rocket* rocket) { _rocket = rocket; }


};

