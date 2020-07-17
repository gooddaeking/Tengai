#pragma once
#include "gameNode.h"

//�Ѿ� ����ü
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
//	## bullet ## (�����Ѿ� - ������� ������ ��)
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
//	## missile ## (missile[0] -> �迭ó�� �̸� �����صΰ� �Ѿ˹߻�)
//=============================================================
class missile : public gameNode
{
private:
	//�Ѿ� ����ü�� ���� ����, �ݺ���
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	//�÷��̾� ����
private:
	float _range;		//�Ѿ� ��Ÿ�
	int _bulletMax;		//�Ѿ� �ִ밹��
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

	//�Ѿ˹߻�
	void fire(float x, float y);
	//�Ѿ˹���
	void move();
	//�÷��̾� ��


	

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
	//�Ѿ� ����ü�� ���� ����, �ݺ���
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	//�÷��̾� ����
private:
	float _range;		//�Ѿ� ��Ÿ�
	int _bulletMax;		//�Ѿ� �ִ밹��
	int frameX[30];
	int frameY[30];
	int _count;

public:

	vector<tagBullet> getBullet() { return _vBullet; }
	void setBullet(int num, bool fire);
	void setRC(int num);

	//�Ѿ˹߻�
	void fire(float x, float y);
	//�Ѿ˹���
	void move();
	//�÷��̾� ��




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
	//�Ѿ� ����ü�� ���� ����, �ݺ���
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	//�÷��̾� ����
private:
	float _range;		//�Ѿ� ��Ÿ�
	int _bulletMax;		//�Ѿ� �ִ밹��
	int frameX[30];
	int frameY[30];
	int _count;

public:

	vector<tagBullet> getBullet() { return _vBullet; }
	void setBullet(int num, bool fire);
	void setRC(int num);

	//�Ѿ˹߻�
	void fire(float x, float y);
	//�Ѿ˹���
	void move();
	//�÷��̾� ��




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
	//�Ѿ� ����ü�� ���� ����, �ݺ���
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	//�÷��̾� ����
private:
	float _range;		//�Ѿ� ��Ÿ�
	int _bulletMax;		//�Ѿ� �ִ밹��
	int frameX[30];
	int frameY[30];
	int _count;

public:

	vector<tagBullet> getBullet() { return _vBullet; }
	void setBullet(int num, bool fire);
	void setRC(int num);

	//�Ѿ˹߻�
	void fire(float x, float y);
	//�Ѿ˹���
	void move();
	//�÷��̾� ��

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
	//�Ѿ� ����ü�� ���� ����, �ݺ���
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	//�÷��̾� ����
private:
	float _range;		//�Ѿ� ��Ÿ�
	int _bulletMax;		//�Ѿ� �ִ밹��
	int frameX[30];
	int frameY[30];
	int _count;

	//����ź
	float angle;
	float _playerX;
	float _playerY;
	bool _stop;

public:

	vector<tagBullet> getBullet() { return _vBullet; }
	void setBullet(int num, bool fire);
	void setRC(int num);

	//����ź
	float getPlayerx() { return _playerX; }
	void setPlayerx(float playerx) { _playerX = playerx; }
	float getPlayery() { return _playerY; }
	void setPlayery(float playery) { _playerY = playery; }

	//�Ѿ˹߻�
	void fire(float x, float y, float angle);
	//�Ѿ˹���
	void move();
	//�÷��̾� ��

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
	//�Ѿ� ����ü�� ���� ����, �ݺ���
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	//�÷��̾� ����
private:
	float _range;		//�Ѿ� ��Ÿ�
	int _bulletMax;		//�Ѿ� �ִ밹��
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

	//�Ѿ˹߻�
	void fire(float x, float y);
	//�Ѿ˹���
	void move();
	//�÷��̾� ��




	missileZ() {}
	~missileZ() {}

	HRESULT init(int bulletMax, float range);
	void release();
	void update();
	void render();
};