#pragma once
#include "gameNode.h"
#include "bullet.h"

struct tagEnemy2
{
	float x, y;
	float angle;
	float speed;
	float radius;
};

class enemy2 : public gameNode
{
private:
	tagEnemy2 _Enemy[5];
	image* _enemy;		//�÷��̾� �̹���
	image* _enemy2;
	image* _bullet;
	image* _powers;
	missile* _missile;	//�̻��� Ŭ����

	RECT _rcPower;
	int _motion;
	int _index;
	int _indexP;
	float _anglePower;

public:


	HRESULT init();
	void release();
	void update();
	void render();

	RECT getRcPower() { return _rcPower; }
	void setRcPower(RECT rcPower) { _rcPower = rcPower; }

	RECT _rcEnemy1[4];		//�÷��̾� ������ ��Ʈ
	RECT _rcEnemy2;
	bool _life[5];
	float random;
	bool _power;
	POINT power;

	void animation();
	//image* getPlayerImg() { return _rocket; }
	//RECT getPlayerRc() { return _rcPlayer; }
	//tagRc* getTagRc() { return _rc; }

	void Move();
	void powerMove();

	//���� ������ �Ÿ� ���ϴ� �Լ�
	float getDistance(float startX, float startY, float endX, float endY);
	//���� ������ ���� ���ϴ� �Լ�
	float getAngle(float startX, float startY, float endX, float endY);

	enemy2() {}
	~enemy2() {}
};

