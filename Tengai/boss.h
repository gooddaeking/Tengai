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

	image* _bossImage;		//�÷��̾� �̹���
	image* _bullet;

	//����ź
	float _playerX;
	float _playerY;

	int _motion;
	int _index;
	int _count;
	bool _gameClear;

public:
	tagBoss _boss;
	missileB* _missile;	//�̻��� Ŭ����
	missileE* _missileE;

	//����ź
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
	RECT _rcBoss;		//�÷��̾� ������ ��Ʈ
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

	//���� ������ �Ÿ� ���ϴ� �Լ�
	float getDistance(float startX, float startY, float endX, float endY);
	//���� ������ ���� ���ϴ� �Լ�
	float getAngle(float startX, float startY, float endX, float endY);

	boss() {}
	~boss() {}
};

