#pragma once
#include "gameNode.h"
#include "bullet.h"

struct tagEnemy
{
	float x, y;
	float angle;
	float speed;
	float radius;
};

class enemy1 : public gameNode
{
private:
	tagEnemy _Enemy[5];
	image* _enemy;		//플레이어 이미지
	image* _enemy2;
	image* _bullet;
	image* _powers;
	missile* _missile;	//미사일 클래스

	RECT _rcPower;
	int _motion;
	int _index;
	int _indexP;

public:

	HRESULT init();
	void release();
	void update();
	void render();

	RECT getRcPower() { return _rcPower; }
	void setRcPower(RECT rcPower) { _rcPower = rcPower; }

	RECT _rcEnemy1[4];		//플레이어 움직일 렉트
	RECT _rcEnemy2;
	float random;
	bool _life[5];
	bool _power;
	POINT power;

	void animation();
	//image* getPlayerImg() { return _rocket; }
	//RECT getPlayerRc() { return _rcPlayer; }
	//tagRc* getTagRc() { return _rc; }

	void Move();
	void powerMove();

	//두점 사이의 거리 구하는 함수
	float getDistance(float startX, float startY, float endX, float endY);
	//두점 사이의 각도 구하는 함수
	float getAngle(float startX, float startY, float endX, float endY);

	enemy1() {}
	~enemy1() {}
};

