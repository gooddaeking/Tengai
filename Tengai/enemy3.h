#pragma once
#include "gameNode.h"
#include "bullet.h"

struct tagEnemy3
{
	float x, y;
	float angle;
	float speed;
	float radius;
};

class enemy3 : public gameNode
{
private:
	
	image* _enemy;		//플레이어 이미지
	image* _bullet;
	

	int _motion;
	int _index;
	int _count;

public:
	tagEnemy3 _Enemy[10];
	missileE* _missile;	//미사일 클래스

	HRESULT init();
	void release();
	void update();
	void render();

	RECT _rcEnemy1[10];		//플레이어 움직일 렉트
	float random;
	bool _life[10];

	missileE* getMissile() { return _missile; }

	void animation();
	//image* getPlayerImg() { return _rocket; }
	//RECT getPlayerRc() { return _rcPlayer; }
	//tagRc* getTagRc() { return _rc; }

	void Move();

	//두점 사이의 거리 구하는 함수
	float getDistance(float startX, float startY, float endX, float endY);
	//두점 사이의 각도 구하는 함수
	float getAngle(float startX, float startY, float endX, float endY);

	enemy3() {}
	~enemy3() {}
};

