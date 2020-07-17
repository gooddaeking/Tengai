#pragma once
#include "gameNode.h"
#include "player.h"
#include "enemy1.h"
#include "enemy2.h"
#include "enemy3.h"
#include "enemy4.h"
#include "boss.h"

class mainGame : public gameNode
{
private:
	player* _player; //플레이어 클래스
	enemy1* _enemy1;
	enemy2* _enemy2;
	enemy3* _enemy3;
	enemy4* _enemy4;
	boss* _boss;

	image* _explo;
	image* _score;
	image* _scoreBoard;
	int _Score;
	int _exploCount;
	int _exploEnemy1[5];
	int _exploEnemy2[5];
	int _exploEnemy3[10];
	int _exploEnemy4[3];
	int _exploBossT;
	int _exploBoss;
	int _exploBossB;
	image* _opening;
	int _openingCount;
	int _openIndex;

	//백그라운드 렉트
	RECT bg;
	RECT trees;
	RECT trees2;
	RECT mountain;
	RECT mountain2;
	RECT cloud;
	RECT cloud2;
	RECT cloud3;
	RECT cloud4;
	RECT cloud5;
	RECT miniCloud;
	RECT miniCloud2;
	RECT sky;
	RECT sky2;
	RECT temp;

	int _alpha;
	int _delta;
	int _count;
	int _enemyCount;
	float _loopX1, _loopY1;
	float _loopX2, _loopY2;
	float _loopX3, _loopY3;
	float _loopX4, _loopY4;
	float _loopX5, _loopY5;

	bool _gameStart;
	bool _isGameover;
	bool _gameClear;
	bool _ending;
	float tempx;
	float tempy;
public:
	HRESULT init();
	void release();
	void update();
	void render();


	mainGame() {}
	~mainGame() {}
};

