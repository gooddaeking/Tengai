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
	image* _idle;		//�÷��̾� �̹���
	image* _bird;		//��(�Ŀ�) �̹���
	image* _bullet;
	image* _angryBird;
	image* _bird2;
			//�÷��̾� ������ ��Ʈ
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
	missile* _missile;	//�̻��� Ŭ����
	missileP* _missileP;
	missileP2* _missileP2;
	missileZ* _missileZ;

	RECT _rcPlayer;

	//����ź
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

