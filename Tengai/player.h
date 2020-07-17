#pragma once
#include "gameNode.h"
#include "bullet.h"

enum STATE
{
	IDLE,
	BACK,
	POWER,
	DEAD
};

struct tagRc
{
	RECT rc;
};

class player : public gameNode
{
private:
	STATE _state;
	image* _idle;		//플레이어 이미지
	image* _bird;		//새(파워) 이미지
	image* _bullet;
	image* _angryBird;
	image* _bird2;
			//플레이어 움직일 렉트
	//tagRc* _rc;
	

	int _power;
	int _motion;
	int _index;
	int _angryCount;
	int _birdCount;
	int _birdIndex;
	int _birdIndex2;
	float _x;
	float _y;
	bool _angry;
	

public:
	missile* _missile;	//미사일 클래스
	missileP* _missileP;
	missileP2* _missileP2;
	missileZ* _missileZ;

	RECT _rcPlayer;

	//유도탄
	float getpX() { return _x; }
	float getpY() { return _y; }

	int getPower() { return _power; }
	void setPower(int power) { _power = power; }
	missile* getMissile() { return _missile; }
	RECT getRcPlayer() { return _rcPlayer; }
	float _pcLife;

	HRESULT init();
	void release();
	void update();
	void render();

	void animation();
	//image* getPlayerImg() { return _rocket; }
	//RECT getPlayerRc() { return _rcPlayer; }
	//tagRc* getTagRc() { return _rc; }

	player() {}
	~player() {}
};

