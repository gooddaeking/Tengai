#pragma once
#include "gameNode.h"

//총알 구조체
struct tagBullet
{
	image* bulletImage;
	RECT rc;
	float x, y;
	float fireX, fireY;
	float speed;
	float speed2;
	float angle;
	float gravity;
	float radius;
	bool fire;
};

//=============================================================
//	## bullet ## (공용총알 - 너희들이 만들어야 함)
//=============================================================
class bullet : public gameNode
{
public:
	HRESULT init();
	void release();
	void update();
	void render();

	bullet() {}
	~bullet() {}
};


//=============================================================
//	## missile ## (missile[0] -> 배열처럼 미리 장전해두고 총알발사)
//=============================================================
class missile : public gameNode
{
private:
	//총알 구조체를 담을 벡터, 반복자
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	//플레이어 시작
private:
	float _range;		//총알 사거리
	int _bulletMax;		//총알 최대갯수
	int frameX[30];
	int frameY[30];
	int _count;
	int _power;

public:

	vector<tagBullet> getBullet() { return _vBullet; }
	void setBullet(int num, bool fire);
	void setRC(int num);
	int getPower() { return _power; }
	void setPower(int power) { _power = power; }

	//총알발사
	void fire(float x, float y);
	//총알무브
	void move();
	//플레이어 끝


	

	missile() {}
	~missile() {}

	HRESULT init(int bulletMax, float range);
	void release();
	void update();
	void render();
};

class missileP : public gameNode
{
private:
	//총알 구조체를 담을 벡터, 반복자
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	//플레이어 시작
private:
	float _range;		//총알 사거리
	int _bulletMax;		//총알 최대갯수
	int frameX[30];
	int frameY[30];
	int _count;

public:

	vector<tagBullet> getBullet() { return _vBullet; }
	void setBullet(int num, bool fire);
	void setRC(int num);

	//총알발사
	void fire(float x, float y);
	//총알무브
	void move();
	//플레이어 끝




	missileP() {}
	~missileP() {}

	HRESULT init(int bulletMax, float range);
	void release();
	void update();
	void render();
};

class missileP2 : public gameNode
{
private:
	//총알 구조체를 담을 벡터, 반복자
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	//플레이어 시작
private:
	float _range;		//총알 사거리
	int _bulletMax;		//총알 최대갯수
	int frameX[30];
	int frameY[30];
	int _count;

public:

	vector<tagBullet> getBullet() { return _vBullet; }
	void setBullet(int num, bool fire);
	void setRC(int num);

	//총알발사
	void fire(float x, float y);
	//총알무브
	void move();
	//플레이어 끝




	missileP2() {}
	~missileP2() {}

	HRESULT init(int bulletMax, float range);
	void release();
	void update();
	void render();
};

class missileE : public gameNode
{
private:
	//총알 구조체를 담을 벡터, 반복자
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	//플레이어 시작
private:
	float _range;		//총알 사거리
	int _bulletMax;		//총알 최대갯수
	int frameX[30];
	int frameY[30];
	int _count;

public:

	vector<tagBullet> getBullet() { return _vBullet; }
	void setBullet(int num, bool fire);
	void setRC(int num);

	//총알발사
	void fire(float x, float y);
	//총알무브
	void move();
	//플레이어 끝

	missileE() {}
	~missileE() {}

	HRESULT init(int bulletMax, float range);
	void release();
	void update();
	void render();
};

class missileB : public gameNode
{
private:
	//총알 구조체를 담을 벡터, 반복자
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	//플레이어 시작
private:
	float _range;		//총알 사거리
	int _bulletMax;		//총알 최대갯수
	int frameX[30];
	int frameY[30];
	int _count;

	//유도탄
	float angle;
	float _playerX;
	float _playerY;
	bool _stop;

public:

	vector<tagBullet> getBullet() { return _vBullet; }
	void setBullet(int num, bool fire);
	void setRC(int num);

	//유도탄
	float getPlayerx() { return _playerX; }
	void setPlayerx(float playerx) { _playerX = playerx; }
	float getPlayery() { return _playerY; }
	void setPlayery(float playery) { _playerY = playery; }

	//총알발사
	void fire(float x, float y, float angle);
	//총알무브
	void move();
	//플레이어 끝

	missileB() {}
	~missileB() {}

	HRESULT init(int bulletMax, float range);
	void release();
	void update();
	void render();
};

class missileZ : public gameNode
{
private:
	//총알 구조체를 담을 벡터, 반복자
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	//플레이어 시작
private:
	float _range;		//총알 사거리
	int _bulletMax;		//총알 최대갯수
	int frameX[30];
	int frameY[30];
	int _count;
	int _power;
	float _speed;

public:

	vector<tagBullet> getBullet() { return _vBullet; }
	void setBullet(int num, bool fire);
	void setRC(int num);
	int getPower() { return _power; }
	void setPower(int power) { _power = power; }
	float getSpeed() { return _speed; }
	void setSpeed(float speed) { _speed = speed; }

	//총알발사
	void fire(float x, float y);
	//총알무브
	void move();
	//플레이어 끝




	missileZ() {}
	~missileZ() {}

	HRESULT init(int bulletMax, float range);
	void release();
	void update();
	void render();
};