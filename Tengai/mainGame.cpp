#include "stdafx.h"
#include "mainGame.h"

//=============================================================
//	## 초기화 ## init()
//=============================================================
HRESULT mainGame::init()
{
	gameNode::init();
	//클래스 초기화를 이곳에서 한다

	//백그라운드 이미지 초기화
	IMAGEMANAGER->addImage("오프닝", "그림파일/오프닝.bmp", 1142, 800);
	_opening = IMAGEMANAGER->addFrameImage("오프닝2", "그림파일/오프닝프레임.bmp", 3426, 800, 3,1);
	IMAGEMANAGER->addImage("백그라운드", "그림파일/챕터1 하늘.bmp", 1142, 2400);
	bg = RectMake(0, -1600, WINSIZEX, 2400);
	IMAGEMANAGER->addImage("맨앞나무", "그림파일/맨앞나무1.bmp", 1142, 170, true, RGB(255, 0, 255));
	trees = RectMake(0, 630, WINSIZEX, 170);
	IMAGEMANAGER->addImage("맨앞나무2", "그림파일/뒤나무.bmp", 1142, 200, true, RGB(255, 0, 255));
	trees2 = RectMake(0, 600, WINSIZEX, 200);
	IMAGEMANAGER->addImage("앞산", "그림파일/나무뒷산.bmp", 1142, 179, true, RGB(255, 0, 255));
	mountain = RectMake(0, 550, WINSIZEX, 179);
	IMAGEMANAGER->addImage("앞산2", "그림파일/나무뒷산1.bmp", 1142, 179, true, RGB(255, 0, 255));
	mountain2 = RectMake(0, 530, WINSIZEX, 179);
	IMAGEMANAGER->addImage("구름", "그림파일/맨뒤구름.bmp", 1142, 350, true, RGB(255, 0, 255));
	cloud = RectMake(0, 200, WINSIZEX, 350);
	IMAGEMANAGER->addImage("구름2", "그림파일/맨뒤구름앞.bmp", 1142, 350, true, RGB(255, 0, 255));
	cloud2 = RectMake(0, 50, WINSIZEX, 350);
	IMAGEMANAGER->addImage("구름3", "그림파일/맨뒤구름3.bmp", 1142, 350, true, RGB(255, 0, 255));
	cloud3 = RectMake(0, -100, WINSIZEX, 350);
	IMAGEMANAGER->addImage("구름4", "그림파일/맨뒤구름앞2.bmp", 1142, 350, true, RGB(255, 0, 255));
	cloud4 = RectMake(0, -250, WINSIZEX, 350);
	IMAGEMANAGER->addImage("구름5", "그림파일/맨뒤구름2.bmp", 1142, 350, true, RGB(255, 0, 255));
	cloud5 = RectMake(0, -400, WINSIZEX, 350);
	IMAGEMANAGER->addImage("작은구름", "그림파일/맨앞구름1.bmp", 1600, 500, true, RGB(255, 0, 255));
	miniCloud = RectMake(0, -150, 1600, 500);
	IMAGEMANAGER->addImage("작은구름2", "그림파일/맨앞구름2.bmp", 1600, 500, true, RGB(255, 0, 255));
	miniCloud2 = RectMake(-100, -650, 1600, 500);
	IMAGEMANAGER->addImage("하늘", "그림파일/하늘구름1.bmp", 1142, 200, true, RGB(255, 0, 255));
	sky = RectMake(0, -1080, 1142, 200);
	IMAGEMANAGER->addImage("하늘2", "그림파일/하늘구름2.bmp", 1142, 389, true, RGB(255, 0, 255));
	sky2 = RectMake(0, -950, 1142, 389);
	_explo = IMAGEMANAGER->addFrameImage("폭파", "그림파일/폭파 프레임.bmp", 1350, 150, 9,1, true, RGB(255, 0, 255));
	_score = IMAGEMANAGER->addFrameImage("스코어", "그림파일/스코어프레임.bmp", 200, 20, 10, 1, true, RGB(255, 0, 255));
	_scoreBoard = IMAGEMANAGER->addImage("점수판", "그림파일/스코어.bmp", 55, 35, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("엔딩", "그림파일/엔딩.bmp", 1142, 800);

	_alpha = 255;
	_delta = 300;
	tempx = tempy = 0;
	_count = 0;
	_Score = 0;
	_enemyCount = 0;
	_isGameover = false;
	_gameStart = false;
	_gameClear = false;
	_ending = false;
	_openingCount = _openIndex = _exploCount = 0;

	for (int i = 0; i < 5; i++)
	{
		_exploEnemy1[i] = 0;
		_exploEnemy2[i] = 0;
	}
	for (int i = 0; i < 10; i++)
	{
		_exploEnemy3[i] = 0;
	}
	for (int i = 0; i < 3; i++)
	{
		_exploEnemy4[i] = 0;
	}
	_exploBossT = _exploBoss = _exploBossB = 0;
	

	_loopX1 = _loopY1 = 0;
	_loopX2 = _loopY2 = 0;
	_loopX3 = _loopY3 = 0;
	_loopX4 = _loopY4 = 0;
	_loopX5 = _loopY5 = 0;

	//플레이어 클래스 초기화
	_player = new player;
	_player->init();
	_enemy1 = new enemy1;
	_enemy1->init();
	_enemy2 = new enemy2;
	_enemy2->init();
	_enemy3 = new enemy3;
	_enemy3->init();
	_enemy4 = new enemy4;
	_enemy4->init();
	_boss = new boss;
	_boss->init();

	return S_OK;
}

//=============================================================
//	## 해제 ## release()
//=============================================================
void mainGame::release()
{
	gameNode::release();
	//클래스 해제를 이곳에서 한다

	//플레이어 클래스 해제
	_player->release();
	SAFE_DELETE(_player);
	_enemy1->release();
	SAFE_DELETE(_enemy1);
	_enemy2->release();
	SAFE_DELETE(_enemy2);
	_enemy3->release();
	SAFE_DELETE(_enemy3);
	_enemy4->release();
	SAFE_DELETE(_enemy4);
	_boss->release();
	SAFE_DELETE(_boss);

}

//=============================================================
//	## 업데이트 ## update()
//=============================================================
void mainGame::update()
{
	gameNode::update();
	//클래스 업데이트를 이곳에서 한다

	//플레이어 클래스 업데이트
	_delta++;
	_exploCount++;

	if (_delta > 300)
	{
		_alpha--;
	}
	if (_alpha < 0)
	{
		_alpha = 0;
	}
	if (!_gameStart)
	{
		if (INPUT->GetKeyDown(VK_SPACE) && _alpha < 30)
		{
			_gameStart = true;
		}
	}
	else
	{
		if (_isGameover && !_gameClear)
		{
			if (INPUT->GetKeyDown(VK_SPACE))
			{
				init();
			}
		}
		else if (_gameClear)
		{
			_player->_rcPlayer.left += 7;
			_player->_rcPlayer.right += 7;
			if (_player->_rcPlayer.left > WINSIZEX)
			{
				_ending = true;
				if (INPUT->GetKeyDown(VK_SPACE))
				{
					init();
				}
			}
		}
		else
		{
			tempx = _player->getpX();
			tempy = _player->getpY();
			_enemy4->setPlayerx(tempx);
			_enemy4->setPlayery(tempy);
			_boss->setPlayerx(tempx);
			_boss->setPlayery(tempy);
			//맨뒷배경
			_count++;
			_enemyCount++;

			_gameClear = _boss->getGameClear();

			if (_count > 1200 && _count <= 2800)
				//if (_count < 1600)
			{
				_loopY1 += -1;
				trees.top += 1;
				trees2.top += 1;
				mountain.top += 1;
				mountain.bottom += 1;
				mountain2.top += 1;
				mountain2.bottom += 1;
				cloud.top += 1;
				cloud.bottom += 1;
				cloud2.top += 1;
				cloud2.bottom += 1;
				cloud3.top += 1;
				cloud3.bottom += 1;
				cloud4.top += 1;
				cloud4.bottom += 1;
				cloud5.top += 1;
				cloud5.bottom += 1;
				miniCloud.top += 1;
				miniCloud.bottom += 1;
				miniCloud2.top += 1;
				miniCloud2.bottom += 1;
				sky.top += 1;
				sky.bottom += 1;
				sky2.top += 1;
				sky2.bottom += 1;
			}
			_loopX2 += 0.5f;
			_loopX3 += 1;
			_loopX4 += 1.5f;
			_loopX5 += 2;

			for (int i = 0; i < _player->_missile->getBullet().size(); i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if (IntersectRect(&temp, &_player->_missile->getBullet()[i].rc, &_enemy1->_rcEnemy1[j]))
					{
						//_player->_missile->_viBullet[i].fire = false;
						_player->_missile->setBullet(i, false);
						_player->_missile->setRC(i);
						_enemy1->_life[j] = false;
						_Score += 100;
					}
					else if (IntersectRect(&temp, &_player->_missile->getBullet()[i].rc, &_enemy1->_rcEnemy2))
					{
						//_player->_missile->_viBullet[i].fire = false;
						_player->_missile->setBullet(i, false);
						_player->_missile->setRC(i);
						_enemy1->_life[4] = false;
						_Score += 100;
					}
					else if (IntersectRect(&temp, &_player->_missile->getBullet()[i].rc, &_enemy2->_rcEnemy1[j]))
					{
						//_player->_missile->_viBullet[i].fire = false;
						_player->_missile->setBullet(i, false);
						_player->_missile->setRC(i);
						_enemy2->_life[j] = false;
						_Score += 100;
					}
					else if (IntersectRect(&temp, &_player->_missile->getBullet()[i].rc, &_enemy2->_rcEnemy2))
					{
						//_player->_missile->_viBullet[i].fire = false;
						_player->_missile->setBullet(i, false);
						_player->_missile->setRC(i);
						_enemy2->_life[4] = false;
						_Score += 100;
					}
				}
				for (int k = 0; k < 10; k++)
				{
					if (IntersectRect(&temp, &_player->_missile->getBullet()[i].rc, &_enemy3->_rcEnemy1[k]))
					{
						//_player->_missile->_viBullet[i].fire = false;
						_player->_missile->setBullet(i, false);
						_player->_missile->setRC(i);
						_enemy3->_life[k] = false;
						_Score += 200;
					}
				}
				for (int l = 0; l < 3; l++)
				{
					if (IntersectRect(&temp, &_player->_missile->getBullet()[i].rc, &_enemy4->_rcEnemy1[l]))
					{
						//_player->_missile->_viBullet[i].fire = false;
						_player->_missile->setBullet(i, false);
						_player->_missile->setRC(i);
						_enemy4->_enemyHP[l] --;
						_Score += 50;
					}
				}
				if (IntersectRect(&temp, &_player->_missile->getBullet()[i].rc, &_boss->_rcBossT))
				{
					//_player->_missile->_viBullet[i].fire = false;
					_player->_missile->setBullet(i, false);
					_player->_missile->setRC(i);
					_boss->_bossTopHP --;
					_Score += 200;

				}
				if (IntersectRect(&temp, &_player->_missile->getBullet()[i].rc, &_boss->_rcBoss))
				{
					//_player->_missile->_viBullet[i].fire = false;
					_player->_missile->setBullet(i, false);
					_player->_missile->setRC(i);
					_boss->_bossHP--;
					_Score += 200;
				}
				if (IntersectRect(&temp, &_player->_missile->getBullet()[i].rc, &_boss->_rcBossB))
				{
					//_player->_missile->_viBullet[i].fire = false;
					_player->_missile->setBullet(i, false);
					_player->_missile->setRC(i);
					_boss->_bossBotHP--;
					_Score += 200;
				}
			}

			for (int i = 0; i < _player->_missileP->getBullet().size(); i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if (IntersectRect(&temp, &_player->_missileP->getBullet()[i].rc, &_enemy1->_rcEnemy1[j]))
					{
						//_player->_missileP->_viBullet[i].fire = false;
						_player->_missileP->setBullet(i, false);
						_player->_missileP->setRC(i);
						_enemy1->_life[j] = false;
						_Score += 100;
					}
					else if (IntersectRect(&temp, &_player->_missileP->getBullet()[i].rc, &_enemy1->_rcEnemy2))
					{
						//_player->_missileP->_viBullet[i].fire = false;
						_player->_missileP->setBullet(i, false);
						_player->_missileP->setRC(i);
						_enemy1->_life[4] = false;
						_Score += 100;
					}
					else if (IntersectRect(&temp, &_player->_missileP->getBullet()[i].rc, &_enemy2->_rcEnemy1[j]))
					{
						//_player->_missileP->_viBullet[i].fire = false;
						_player->_missileP->setBullet(i, false);
						_player->_missileP->setRC(i);
						_enemy2->_life[j] = false;
						_Score += 100;
					}
					else if (IntersectRect(&temp, &_player->_missileP->getBullet()[i].rc, &_enemy2->_rcEnemy2))
					{
						//_player->_missileP->_viBullet[i].fire = false;
						_player->_missileP->setBullet(i, false);
						_player->_missileP->setRC(i);
						_enemy2->_life[4] = false;
						_Score += 100;
					}
				}
				for (int k = 0; k < 10; k++)
				{
					if (IntersectRect(&temp, &_player->_missileP->getBullet()[i].rc, &_enemy3->_rcEnemy1[k]))
					{
						//_player->_missileP->_viBullet[i].fire = false;
						_player->_missileP->setBullet(i, false);
						_player->_missileP->setRC(i);
						_enemy3->_life[k] = false;
						_Score += 200;
					}
				}
				for (int l = 0; l < 3; l++)
				{
					if (IntersectRect(&temp, &_player->_missileP->getBullet()[i].rc, &_enemy4->_rcEnemy1[l]))
					{
						//_player->_missileP->_viBullet[i].fire = false;
						_player->_missileP->setBullet(i, false);
						_player->_missileP->setRC(i);
						_enemy4->_enemyHP[l] --;
						_Score += 50;
					}
				}
				if (IntersectRect(&temp, &_player->_missileP->getBullet()[i].rc, &_boss->_rcBossT))
				{
					//_player->_missileP->_viBullet[i].fire = false;
					_player->_missileP->setBullet(i, false);
					_player->_missileP->setRC(i);
					_boss->_bossTopHP--;
					_Score += 200;
				}
				if (IntersectRect(&temp, &_player->_missileP->getBullet()[i].rc, &_boss->_rcBoss))
				{
					//_player->_missileP->_viBullet[i].fire = false;
					_player->_missileP->setBullet(i, false);
					_player->_missileP->setRC(i);
					_boss->_bossHP--;
					_Score += 200;
				}
				if (IntersectRect(&temp, &_player->_missileP->getBullet()[i].rc, &_boss->_rcBossB))
				{
					//_player->_missileP->_viBullet[i].fire = false;
					_player->_missileP->setBullet(i, false);
					_player->_missileP->setRC(i);
					_boss->_bossBotHP--;
					_Score += 200;
				}
			}

			for (int i = 0; i < _player->_missileP2->getBullet().size(); i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if (IntersectRect(&temp, &_player->_missileP2->getBullet()[i].rc, &_enemy1->_rcEnemy1[j]))
					{
						//_player->_missileP2->_viBullet[i].fire = false;
						_player->_missileP2->setBullet(i, false);
						_player->_missileP2->setRC(i);
						_enemy1->_life[j] = false;
						_Score += 100;
					}
					else if (IntersectRect(&temp, &_player->_missileP2->getBullet()[i].rc, &_enemy1->_rcEnemy2))
					{
						//_player->_missileP2->_viBullet[i].fire = false;
						_player->_missileP2->setBullet(i, false);
						_player->_missileP2->setRC(i);
						_enemy1->_life[4] = false;
						_Score += 100;
					}
					else if (IntersectRect(&temp, &_player->_missileP2->getBullet()[i].rc, &_enemy2->_rcEnemy1[j]))
					{
						//_player->_missileP2->_viBullet[i].fire = false;
						_player->_missileP2->setBullet(i, false);
						_player->_missileP2->setRC(i);
						_enemy2->_life[j] = false;
						_Score += 100;
					}
					else if (IntersectRect(&temp, &_player->_missileP2->getBullet()[i].rc, &_enemy2->_rcEnemy2))
					{
						//_player->_missileP2->_viBullet[i].fire = false;
						_player->_missileP2->setBullet(i, false);
						_player->_missileP2->setRC(i);
						_enemy2->_life[4] = false;
						_Score += 100;
					}
				}
				for (int k = 0; k < 10; k++)
				{
					if (IntersectRect(&temp, &_player->_missileP2->getBullet()[i].rc, &_enemy3->_rcEnemy1[k]))
					{
						//_player->_missileP2->_viBullet[i].fire = false;
						_player->_missileP2->setBullet(i, false);
						_player->_missileP2->setRC(i);
						_enemy3->_life[k] = false;
						_Score += 200;
					}
				}
				for (int l = 0; l < 3; l++)
				{
					if (IntersectRect(&temp, &_player->_missileP2->getBullet()[i].rc, &_enemy4->_rcEnemy1[l]))
					{
						//_player->_missileP2->_viBullet[i].fire = false;
						_player->_missileP2->setBullet(i, false);
						_player->_missileP2->setRC(i);
						_enemy4->_enemyHP[l] --;
						_Score += 50;
					}
				}
				if (IntersectRect(&temp, &_player->_missileP2->getBullet()[i].rc, &_boss->_rcBossT))
				{
					//_player->_missileP2->_viBullet[i].fire = false;
					_player->_missileP2->setBullet(i, false);
					_player->_missileP2->setRC(i);
					_boss->_bossTopHP--;
					_Score += 200;
				}
				if (IntersectRect(&temp, &_player->_missileP2->getBullet()[i].rc, &_boss->_rcBoss))
				{
					//_player->_missileP2->_viBullet[i].fire = false;
					_player->_missileP2->setBullet(i, false);
					_player->_missileP2->setRC(i);
					_boss->_bossHP--;
					_Score += 200;
				}
				if (IntersectRect(&temp, &_player->_missileP2->getBullet()[i].rc, &_boss->_rcBossB))
				{
					//_player->_missileP2->_viBullet[i].fire = false;
					_player->_missileP2->setBullet(i, false);
					_player->_missileP2->setRC(i);
					_boss->_bossBotHP--;
					_Score += 200;
				}
			}

			for (int i = 0; i < _player->_missileZ->getBullet().size(); i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if (IntersectRect(&temp, &_player->_missileZ->getBullet()[i].rc, &_enemy1->_rcEnemy1[j]))
					{
						//_player->_missileZ->_viBullet[i].fire = false;
						//_player->_missileZ->setBullet(i, false);
						_player->_missileZ->setRC(i);
						_player->_missileZ->setSpeed(6);
						_enemy1->_life[j] = false;
						_Score += 100;
					}
					else if (IntersectRect(&temp, &_player->_missileZ->getBullet()[i].rc, &_enemy1->_rcEnemy2))
					{
						//_player->_missileZ->_viBullet[i].fire = false;
						//_player->_missileZ->setBullet(i, false);
						_player->_missileZ->setRC(i);
						_player->_missileZ->setSpeed(6);
						_enemy1->_life[4] = false;
						_Score += 100;
					}
					else if (IntersectRect(&temp, &_player->_missileZ->getBullet()[i].rc, &_enemy2->_rcEnemy1[j]))
					{
						//_player->_missileZ->_viBullet[i].fire = false;
						//_player->_missileZ->setBullet(i, false);
						_player->_missileZ->setRC(i);
						_player->_missileZ->setSpeed(6);
						_enemy2->_life[j] = false;
						_Score += 100;
					}
					else if (IntersectRect(&temp, &_player->_missileZ->getBullet()[i].rc, &_enemy2->_rcEnemy2))
					{
						//_player->_missileZ->_viBullet[i].fire = false;
						//_player->_missileZ->setBullet(i, false);
						_player->_missileZ->setRC(i);
						_player->_missileZ->setSpeed(6);
						_enemy2->_life[4] = false;
						_Score += 100;
					}
				}
				for (int k = 0; k < 10; k++)
				{
					if (IntersectRect(&temp, &_player->_missileZ->getBullet()[i].rc, &_enemy3->_rcEnemy1[k]))
					{
						//_player->_missileZ->_viBullet[i].fire = false;
						//_player->_missileZ->setBullet(i, false);
						_player->_missileZ->setRC(i);
						_player->_missileZ->setSpeed(6);
						_enemy3->_life[k] = false;
						_Score += 200;
					}
				}
				for (int l = 0; l < 3; l++)
				{
					if (IntersectRect(&temp, &_player->_missileZ->getBullet()[i].rc, &_enemy4->_rcEnemy1[l]))
					{
						//_player->_missileZ->_viBullet[i].fire = false;
						//_player->_missileZ->setBullet(i, false);
						_player->_missileZ->setRC(i);
						_player->_missileZ->setSpeed(6);
						_enemy4->_enemyHP[l] --;
						_Score += 50;
					}
				}
				if (IntersectRect(&temp, &_player->_missileZ->getBullet()[i].rc, &_boss->_rcBossT))
				{
					//_player->_missileZ->_viBullet[i].fire = false;
					//_player->_missileZ->setBullet(i, false);
					_player->_missileZ->setRC(i);
					_player->_missileZ->setSpeed(6);
					_boss->_bossTopHP--;
					_Score += 200;
				}
				if (IntersectRect(&temp, &_player->_missileZ->getBullet()[i].rc, &_boss->_rcBoss))
				{
					//_player->_missileZ->_viBullet[i].fire = false;
					//_player->_missileZ->setBullet(i, false);
					_player->_missileZ->setRC(i);
					_player->_missileZ->setSpeed(6);
					_boss->_bossHP--;
					_Score += 200;
				}
				if (IntersectRect(&temp, &_player->_missileZ->getBullet()[i].rc, &_boss->_rcBossB))
				{
					//_player->_missileZ->_viBullet[i].fire = false;
					//_player->_missileZ->setBullet(i, false);
					_player->_missileZ->setRC(i);
					_player->_missileZ->setSpeed(6);
					_boss->_bossBotHP--;
					_Score += 200;
				}
			}

			for (int i = 0; i < _enemy3->_missile->getBullet().size(); i++)
			{
				if (IntersectRect(&temp, &_enemy3->_missile->getBullet()[i].rc, &_player->getRcPlayer()))
				{
					//_player->_missile->_viBullet[i].fire = false;
					_enemy3->_missile->setBullet(i, false);
					_enemy3->_missile->setRC(i);
					_player->_pcLife--;
				}

			}
			for (int i = 0; i < _enemy4->_missile->getBullet().size(); i++)
			{
				if (IntersectRect(&temp, &_enemy4->_missile->getBullet()[i].rc, &_player->getRcPlayer()))
				{
					//_player->_missile->_viBullet[i].fire = false;
					_enemy4->_missile->setBullet(i, false);
					_enemy4->_missile->setRC(i);
					_player->_pcLife -= 0.5;
				}
			}
			for (int i = 0; i < _boss->_missile->getBullet().size(); i++)
			{
				if (IntersectRect(&temp, &_boss->_missile->getBullet()[i].rc, &_player->getRcPlayer()))
				{
					//_player->_missile->_viBullet[i].fire = false;
					_boss->_missile->setBullet(i, false);
					_boss->_missile->setRC(i);
					_player->_pcLife--;
				}
			}
			for (int i = 0; i < _boss->_missileE->getBullet().size(); i++)
			{
				if (IntersectRect(&temp, &_boss->_missileE->getBullet()[i].rc, &_player->getRcPlayer()))
				{
					//_player->_missile->_viBullet[i].fire = false;
					_boss->_missileE->setBullet(i, false);
					_boss->_missileE->setRC(i);
					_player->_pcLife--;
				}
			}

			if (IntersectRect(&temp, &_player->getRcPlayer(), &_enemy1->getRcPower()))
			{
				_enemy1->_power = false;
				_enemy1->setRcPower(RectMakeCenter(_enemy1->_rcEnemy2.left, _enemy1->_rcEnemy2.bottom, 80, 80));
				_player->setPower(_player->getPower() + 1);
			}
			if (IntersectRect(&temp, &_player->getRcPlayer(), &_enemy2->getRcPower()))
			{
				_enemy2->_power = false;
				_enemy2->setRcPower(RectMakeCenter(_enemy2->_rcEnemy2.left, _enemy2->_rcEnemy2.bottom, 80, 80));
				_player->setPower(_player->getPower() + 1);
			}

			_player->update();
			if (_enemyCount / 10 > 10)
			{
				_enemy1->update();
			}
			if (_enemyCount / 10 > 50)
			{
				_enemy2->update();
			}
			if (_enemyCount / 10 > 30)
			{
				_enemy3->update();
			}
			if (_enemyCount / 10 > 70)
			{
				_enemy4->update();
			}
			if (_enemyCount / 10 > 300)
			{
				_boss->update();
			}
			if (_player->_pcLife <= 0)
			{
				_isGameover = true;
			}
			
		}
		//RECT rc;
		//if (PtInRect(&_player->getPlayerImg()->boudingBox(), _ptMouse))
		//if (PtInRect(&_player->getPlayerRc(), _ptMouse))
		//if (PtInRect(&_player->getTagRc()->rc, _ptMouse))
		//{
		//}

	}
}

//=============================================================
//	## 렌더 ## render()
//=============================================================
void mainGame::render()
{
	//흰색 빈 비트맵
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
//=============================================================	
	//클래스 렌더를 이곳에서 한다
	
	
	//백그라운드 렌더
	
	if (!_gameStart)
	{
		
		IMAGEMANAGER->frameRender("오프닝2", getMemDC(), 0, 0);
		_opening->setFrameY(0);
		_openingCount++;
		if (_openingCount % 20 == 0)
		{
			_openIndex++;
			if (_openIndex > 2)
			{
				_openIndex = 0;
			}
		}
		_opening->setFrameX(_openIndex);
		IMAGEMANAGER->alphaRender("오프닝", getMemDC(), _alpha);
		
	}
	else
	{
		IMAGEMANAGER->loopRender("백그라운드", getMemDC(), &bg, _loopX1, _loopY1);
		IMAGEMANAGER->loopRender("하늘", getMemDC(), &sky, _loopX3, 0);
		IMAGEMANAGER->loopRender("하늘2", getMemDC(), &sky2, _loopX4, 0);
		IMAGEMANAGER->loopRender("앞산2", getMemDC(), &mountain2, _loopX2, 0);
		IMAGEMANAGER->loopRender("앞산", getMemDC(), &mountain, _loopX3, 0);
		IMAGEMANAGER->loopRender("맨앞나무2", getMemDC(), &trees2, _loopX4, 0);
		IMAGEMANAGER->loopRender("맨앞나무", getMemDC(), &trees, _loopX5, 0);
		IMAGEMANAGER->loopRender("구름", getMemDC(), &cloud, _loopX2, 0);
		IMAGEMANAGER->loopRender("구름2", getMemDC(), &cloud2, _loopX3, 0);
		IMAGEMANAGER->loopRender("구름5", getMemDC(), &cloud5, _loopX2, 0);
		IMAGEMANAGER->loopRender("구름4", getMemDC(), &cloud4, _loopX3, 0);
		IMAGEMANAGER->loopRender("구름3", getMemDC(), &cloud3, _loopX4, 0);
		IMAGEMANAGER->loopRender("작은구름", getMemDC(), &miniCloud, _loopX5, 0);
		IMAGEMANAGER->loopRender("작은구름2", getMemDC(), &miniCloud2, _loopX5, 0);
		
		//enemy1 폭파
		for (int i = 0; i < 5; i++) // enemy1 폭파
		{
			if (!_enemy1->_life[i])
			{
				IMAGEMANAGER->frameRender("폭파", getMemDC(), _enemy1->_rcEnemy1[i].left, _enemy1->_rcEnemy1[i].top);
				_explo->setFrameY(0);
				if (_exploCount % 4 == 0)
				{
					_exploEnemy1[i]++;
					if (_exploEnemy1[i] > 8)
					{
						_exploEnemy1[i] = 8;
					}
				}
				_explo->setFrameX(_exploEnemy1[i]);
			}
			if (!_enemy1->_life[4])
			{
				IMAGEMANAGER->frameRender("폭파", getMemDC(), _enemy1->_rcEnemy2.left, _enemy1->_rcEnemy2.top);
				_explo->setFrameY(0);
				if (_exploCount % 4 == 0)
				{
					_exploEnemy1[4]++;
					if (_exploEnemy1[4] > 8)
					{
						_exploEnemy1[4] = 8;
					}
				}
				_explo->setFrameX(_exploEnemy1[4]);
			}
			else if(_enemy1->_life[i])
			{
				_exploEnemy1[i] = 0;
			}
			
		}

		//enemy2 폭파
		for (int i = 0; i < 5; i++) //에너지2 폭파
		{
			if (!_enemy2->_life[i])
			{
				IMAGEMANAGER->frameRender("폭파", getMemDC(), _enemy2->_rcEnemy1[i].left, _enemy2->_rcEnemy1[i].top);
				_explo->setFrameY(0);
				if (_exploCount % 4 == 0)
				{
					_exploEnemy2[i]++;
					if (_exploEnemy2[i] > 8)
					{
						_exploEnemy2[i] = 8;
					}
				}
				_explo->setFrameX(_exploEnemy2[i]);
			}
			if (!_enemy2->_life[4])
			{
				IMAGEMANAGER->frameRender("폭파", getMemDC(), _enemy2->_rcEnemy2.left, _enemy2->_rcEnemy2.top);
				_explo->setFrameY(0);
				if (_exploCount % 4 == 0)
				{
					_exploEnemy2[4]++;
					if (_exploEnemy2[4] > 8)
					{
						_exploEnemy2[4] = 8;
					}
				}
				_explo->setFrameX(_exploEnemy2[4]);
			}
			else if (_enemy2->_life[i])
			{
				_exploEnemy2[i] = 0;
			}

		}

		//enemy3 폭파
		for (int i = 0; i < 10; i++)
		{
			if (!_enemy3->_life[i])
			{
				IMAGEMANAGER->frameRender("폭파", getMemDC(), _enemy3->_Enemy[i].x - 25, _enemy3->_Enemy[i].y - 25);
				_explo->setFrameY(0);
				if (_exploCount % 4 == 0)
				{
					_exploEnemy3[i]++;
					if (_exploEnemy3[i] > 8)
					{
						_exploEnemy3[i] = 8;
					}
				}
				_explo->setFrameX(_exploEnemy3[i]);
			}
			else if (_enemy3->_life[i])
			{
				_exploEnemy3[i] = 0;
			}

		}

		//enemy4 폭파
		for (int i = 0; i < 3; i++)
		{
			if (_enemy4->_enemyHP[i] >= 0)
			{
				IMAGEMANAGER->frameRender("폭파", getMemDC(), _enemy4->_Enemy[i].x, _enemy4->_Enemy[i].y);
				_explo->setFrameY(0);
				if (_exploCount % 5 == 0)
				{
					_exploEnemy4[i]++;
					if (_exploEnemy4[i] > 8)
					{
						_exploEnemy4[i] = 8;
					}
				}
				_explo->setFrameX(_exploEnemy4[i]);
			}
			else if (_enemy4->_life[i])
			{
				_exploEnemy4[i] = 0;
			}
		}

		//보스 폭파
		if (_boss->_bossTopHP <= 0)
		{
			IMAGEMANAGER->frameRender("폭파", getMemDC(), _boss->_boss.x - 270, _boss->_boss.y - 390);
			IMAGEMANAGER->frameRender("폭파", getMemDC(), _boss->_boss.x - 240, _boss->_boss.y - 350);
			IMAGEMANAGER->frameRender("폭파", getMemDC(), _boss->_boss.x - 260, _boss->_boss.y - 330);
			IMAGEMANAGER->frameRender("폭파", getMemDC(), _boss->_boss.x - 230, _boss->_boss.y - 350);
			IMAGEMANAGER->frameRender("폭파", getMemDC(), _boss->_boss.x - 210, _boss->_boss.y - 330);
			IMAGEMANAGER->frameRender("폭파", getMemDC(), _boss->_boss.x - 220, _boss->_boss.y - 320);
			IMAGEMANAGER->frameRender("폭파", getMemDC(), _boss->_boss.x - 190, _boss->_boss.y - 320);
			_explo->setFrameY(0);
			if (_exploCount % 4 == 0)
			{
				_exploBossT++;
				if (_exploBossT > 8)
				{
					_exploBossT = 8;
				}
			}
			_explo->setFrameX(_exploBossT);
		}
		if (_boss->_bossHP <= 0)
		{
			IMAGEMANAGER->frameRender("폭파", getMemDC(), _boss->_boss.x - 190, _boss->_boss.y - 190);
			IMAGEMANAGER->frameRender("폭파", getMemDC(), _boss->_boss.x - 160, _boss->_boss.y - 150);
			IMAGEMANAGER->frameRender("폭파", getMemDC(), _boss->_boss.x - 180, _boss->_boss.y - 130);
			IMAGEMANAGER->frameRender("폭파", getMemDC(), _boss->_boss.x - 150, _boss->_boss.y - 150);
			IMAGEMANAGER->frameRender("폭파", getMemDC(), _boss->_boss.x - 130, _boss->_boss.y - 130);
			IMAGEMANAGER->frameRender("폭파", getMemDC(), _boss->_boss.x - 140, _boss->_boss.y - 120);
			IMAGEMANAGER->frameRender("폭파", getMemDC(), _boss->_boss.x - 110, _boss->_boss.y - 120);
			_explo->setFrameY(0);
			if (_exploCount % 4 == 0)
			{
				_exploBoss++;
				if (_exploBoss > 8)
				{
					_exploBoss = 8;
				}
			}
			_explo->setFrameX(_exploBoss);
		}
		if (_boss->_bossTopHP <= 0)
		{
			IMAGEMANAGER->frameRender("폭파", getMemDC(), _boss->_boss.x - 240, _boss->_boss.y + 10);
			IMAGEMANAGER->frameRender("폭파", getMemDC(), _boss->_boss.x - 210, _boss->_boss.y + 50);
			IMAGEMANAGER->frameRender("폭파", getMemDC(), _boss->_boss.x - 230, _boss->_boss.y + 70);
			IMAGEMANAGER->frameRender("폭파", getMemDC(), _boss->_boss.x - 200, _boss->_boss.y + 50);
			IMAGEMANAGER->frameRender("폭파", getMemDC(), _boss->_boss.x - 180, _boss->_boss.y + 70);
			IMAGEMANAGER->frameRender("폭파", getMemDC(), _boss->_boss.x - 190, _boss->_boss.y + 80);
			IMAGEMANAGER->frameRender("폭파", getMemDC(), _boss->_boss.x - 160, _boss->_boss.y + 80);
			_explo->setFrameY(0);
			if (_exploCount % 4 == 0)
			{
				_exploBossB++;
				if (_exploBossB > 8)
				{
					_exploBossB = 8;
				}
			}
			_explo->setFrameX(_exploBossB);
		}

		_boss->render();
		_enemy1->render();
		_enemy2->render();
		_enemy3->render();
		_enemy4->render();
		_player->render();
		
		//IMAGEMANAGER->render("점수판", getMemDC(), 50, 50);
		//for (int i = 0; i < 10; i++)
		//{
		//	if(_Score % 10 == i)
		//	{
		//		IMAGEMANAGER->frameRender("스코어", getMemDC(), 210, 55);
		//		_score->setFrameY(0);
		//		_score->setFrameX(i);
		//	}
		//	if ((_Score / 10) % 10 == i)
		//	{
		//		IMAGEMANAGER->frameRender("스코어", getMemDC(), 190, 55);
		//		_score->setFrameY(0);
		//		_score->setFrameX(i);
		//	}
		//	if ((_Score / 100) % 10 == i)
		//	{
		//		IMAGEMANAGER->frameRender("스코어", getMemDC(), 170, 55);
		//		_score->setFrameY(0);
		//		_score->setFrameX(i);
		//	}
		//	if ((_Score / 1000) % 10 == i)
		//	{
		//		IMAGEMANAGER->frameRender("스코어", getMemDC(), 150, 55);
		//		_score->setFrameY(0);
		//		_score->setFrameX(i);
		//	}
		//	if ((_Score / 10000) % 10 == i)
		//	{
		//		IMAGEMANAGER->frameRender("스코어", getMemDC(), 130, 55);
		//		_score->setFrameY(0);
		//		_score->setFrameX(i);
		//	}
		//	if ((_Score / 100000) % 10 == i)
		//	{
		//		IMAGEMANAGER->frameRender("스코어", getMemDC(), 110, 55);
		//		_score->setFrameY(0);
		//		_score->setFrameX(i);
		//	}
		//}

	}
	if (_ending)
	{
		IMAGEMANAGER->render("엔딩", getMemDC(), 0, 0);
	}

	//플레이어 클래스 렌더
	
	


//=============================================================
	//백버퍼의 내용을 화면DC에 그린다
	this->getBackBuffer()->render(getHDC());
}

