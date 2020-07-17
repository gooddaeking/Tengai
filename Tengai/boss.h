#pragma once
#include "gameNode.h"
#include "bullet.h"

enum STATEBOSS
{
	NORMAL,
	TOP,
	BOTTOM,
	BOTH
};

struct tagBoss
{
	float x, y;
	float xT, yT;
	float xB, yB;
	float angle;
	float angleT;
	float angleM;
	float angleB;
	float speed;
	float radius;
};

class boss : public gameNode
{
private:
	STATEBOSS _state;

	image* _bossImage;		//플레이어 이미지
	image* _bullet;

	//유도탄
	float _playerX;
	float _playerY;

	int _motion;
	int _index;
	int _count;
	bool _gameClear;

public:
	tagBoss _boss;
	missileB* _missile;	//미사일 클래스
	missileE* _missileE;

	//유도탄
	float getPlayerx() { return _playerX; }
	void setPlayerx(float playerx) { _playerX = playerx; }
	float getPlayery() { return _playerY; }
	void setPlayery(float playery) { _playerY = playery; }
	bool getGameClear() { return _gameClear; }
	void setGameClear(bool gameClear) { _gameClear = gameClear; }

	HRESULT init();
	void release();
	void update();
	void render();

	RECT _rcBossT;
	RECT _rcBoss;		//플레이어 움직일 렉트
	RECT _rcBossB;
	float random;
	int _bossHP;
	int _bossTopHP;
	int _bossBotHP;

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

	boss() {}
	~boss() {}
};

