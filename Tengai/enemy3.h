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
	
	image* _enemy;		//�÷��̾� �̹���
	image* _bullet;
	

	int _motion;
	int _index;
	int _count;

public:
	tagEnemy3 _Enemy[10];
	missileE* _missile;	//�̻��� Ŭ����

	HRESULT init();
	void release();
	void update();
	void render();

	RECT _rcEnemy1[10];		//�÷��̾� ������ ��Ʈ
	float random;
	bool _life[10];

	missileE* getMissile() { return _missile; }

	void animation();
	//image* getPlayerImg() { return _rocket; }
	//RECT getPlayerRc() { return _rcPlayer; }
	//tagRc* getTagRc() { return _rc; }

	void Move();

	//���� ������ �Ÿ� ���ϴ� �Լ�
	float getDistance(float startX, float startY, float endX, float endY);
	//���� ������ ���� ���ϴ� �Լ�
	float getAngle(float startX, float startY, float endX, float endY);

	enemy3() {}
	~enemy3() {}
};

