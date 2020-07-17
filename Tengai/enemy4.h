#pragma once
#include "gameNode.h"
#include "bullet.h"

enum STATE2
{
	MOVE,
	STOP
};

struct tagEnemy4
{
	float x, y;
	float angle;
	float speed;
	float radius;
};

class enemy4 : public gameNode
{
private:
	STATE2 _state;
	
	image* _enemy;		//�÷��̾� �̹���
	image* _bullet;

	//����ź
	float _playerX;
	float _playerY;

	int _motion;
	int _index;
	int _count;

public:
	tagEnemy4 _Enemy[3];
	missileB* _missile;	//�̻��� Ŭ����


	//����ź
	float getPlayerx() { return _playerX; }
	void setPlayerx(float playerx) { _playerX = playerx; }
	float getPlayery() { return _playerY; }
	void setPlayery(float playery) { _playerY = playery; }

	HRESULT init();
	void release();
	void update();
	void render();

	RECT _rcEnemy1[3];		//�÷��̾� ������ ��Ʈ
	float random;
	int _enemyHP[3];
	bool _life[3];

	missileB* getMissile() { return _missile; }

	void animation();
	//image* getPlayerImg() { return _rocket; }
	//RECT getPlayerRc() { return _rcPlayer; }
	//tagRc* getTagRc() { return _rc; }

	void Move();

	//���� ������ �Ÿ� ���ϴ� �Լ�
	float getDistance(float startX, float startY, float endX, float endY);
	//���� ������ ���� ���ϴ� �Լ�
	float getAngle(float startX, float startY, float endX, float endY);

	enemy4() {}
	~enemy4() {}
};

