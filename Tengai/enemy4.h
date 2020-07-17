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
	
	image* _enemy;		//플레이어 이미지
	image* _bullet;

	//유도탄
	float _playerX;
	float _playerY;

	int _motion;
	int _index;
	int _count;

public:
	tagEnemy4 _Enemy[3];
	missileB* _missile;	//미사일 클래스


	//유도탄
	float getPlayerx() { return _playerX; }
	void setPlayerx(float playerx) { _playerX = playerx; }
	float getPlayery() { return _playerY; }
	void setPlayery(float playery) { _playerY = playery; }

	HRESULT init();
	void release();
	void update();
	void render();

	RECT _rcEnemy1[3];		//플레이어 움직일 렉트
	float random;
	int _enemyHP[3];
	bool _life[3];

	missileB* getMissile() { return _missile; }

	void animation();
	//image* getPlayerImg() { return _rocket; }
	//RECT getPlayerRc() { return _rcPlayer; }
	//tagRc* getTagRc() { return _rc; }

	void Move();

	//두점 사이의 거리 구하는 함수
	float getDistance(float startX, float startY, float endX, float endY);
	//두점 사이의 각도 구하는 함수
	float getAngle(float startX, float startY, float endX, float endY);

	enemy4() {}
	~enemy4() {}
};

