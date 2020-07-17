#include "stdafx.h"
#include "boss.h"

HRESULT boss::init()
{
	//�÷��̾� �̹��� �ʱ�ȭ
	_bossImage = IMAGEMANAGER->addFrameImage("����", "�׸�����/���� ������.bmp", 2080, 700, 4, 1, true, RGB(255, 0, 255));
	_bullet = IMAGEMANAGER->addFrameImage("ū�Ѿ�", "�׸�����/ū�Ѿ� ������.bmp", 150, 50, 3, 1, true, RGB(255, 0, 255));

	_state = NORMAL;

	
	_boss.speed = 2.0f;
	_boss.angle = RANDOM->Range(PI * 2);
	_boss.radius = 200;
	_bossHP = _bossTopHP = _bossBotHP = 200;
	
	_boss.x = WINSIZEX + 400;
	_boss.y = 300;
	_boss.xT = _boss.x - 80;
	_boss.yT = _boss.y - 200;
	_boss.xB = _boss.x - 50;
	_boss.yB = _boss.y + 200;
	_motion = _index = 0;
	_gameClear = false;
	_boss.angleT = _boss.angleM = _boss.angleB = PI;
	_count = 1;
	random = RANDOM->Range(2 * PI);

	//�̻��� Ŭ���� �ʱ�ȭ
	_missile = new missileB;
	_missile->init(30, 1500);
	_missileE = new missileE;
	_missileE->init(30, 1500);


	return S_OK;
}

void boss::release()
{
	//�̻��� Ŭ���� ����
	_missile->release();
	SAFE_DELETE(_missile);
	_missileE->release();
	SAFE_DELETE(_missileE);
}

void boss::update()
{
	//�÷��̾� �����̱� & ȭ������� ������ ���ϰ� �����
	
	_boss.xT = _boss.x - 80;
	_boss.yT = _boss.y - 200;
	_boss.xB = _boss.x - 50;
	_boss.yB = _boss.y + 200;
	_count++;

	if (_bossTopHP > 0 && _bossHP > 0 && _bossBotHP > 0)
	{
		_rcBossT = RectMakeCenter(_boss.xT, _boss.yT, 100, 150);
		_rcBoss = RectMakeCenter(_boss.x, _boss.y, 100, 150);
		_rcBossB = RectMakeCenter(_boss.xB, _boss.yB, 100, 150);
	}
	else if (_bossTopHP <= 0 && _bossHP > 0 && _bossBotHP > 0)
	{
		_state = TOP;
		_rcBossT = RectMakeCenter(_boss.xT, _boss.yT, 0, 0);
		_rcBoss = RectMakeCenter(_boss.x, _boss.y, 100, 150);
		_rcBossB = RectMakeCenter(_boss.xB, _boss.yB, 100, 150);
	}
	else if (_bossBotHP <= 0 && _bossTopHP > 0 && _bossHP > 0)
	{
		_state = BOTTOM;
		_rcBossT = RectMakeCenter(_boss.xT, _boss.yT, 100, 150);
		_rcBoss = RectMakeCenter(_boss.x, _boss.y, 100, 150);
		_rcBossB = RectMakeCenter(_boss.xB, _boss.yB, 0, 0);
	}
	else if (_bossBotHP <= 0 && _bossHP > 0 && _bossTopHP <= 0)
	{
		_state = BOTH;
		_rcBossT = RectMakeCenter(_boss.xT, _boss.yT, 0, 0);
		_rcBoss = RectMakeCenter(_boss.x, _boss.y, 100, 150);
		_rcBossB = RectMakeCenter(_boss.xB, _boss.yB, 0, 0);
	}
	else if (_bossHP <= 0)
	{
		_rcBossT = RectMakeCenter(_boss.xT, _boss.yT, 0, 0);
		_rcBoss = RectMakeCenter(_boss.x, _boss.y, 0, 0);
		_rcBossB = RectMakeCenter(_boss.xB, _boss.yB, 0, 0);
		_gameClear = true;
	}
	
	if (_bossTopHP > 0)
	{
		if (_count % 190 == 0)
		{
			_boss.angleT = getAngle(_boss.xT - 190, _boss.yT - 115, getPlayerx(), getPlayery());
			_boss.angleM = getAngle(_boss.xT - 20, _boss.yT - 235, getPlayerx(), getPlayery());
			_boss.angleB = getAngle(_boss.xT - 210, _boss.yT + 70, getPlayerx(), getPlayery());
			_missile->fire(_rcBossT.left - 140, _rcBossT.top - 40, _boss.angleT);
			_missile->fire(_rcBossT.left +30 , _rcBossT.top - 160, _boss.angleM);
			_missile->fire(_rcBossT.left - 160, _rcBossT.top + 135, _boss.angleB);
		}
	}
	if (_bossHP > 0)
	{
		if (_count % 125 == 0)
		{
			_missileE->fire(_rcBoss.left - 100, RANDOM->Range(0 ,WINSIZEY));
			_missileE->fire(_rcBoss.left - 100, RANDOM->Range(0, WINSIZEY));
			_missileE->fire(_rcBoss.left - 100, RANDOM->Range(0, WINSIZEY));
			_missileE->fire(_rcBoss.left - 100, RANDOM->Range(0, WINSIZEY));
			_missileE->fire(_rcBoss.left - 100, RANDOM->Range(0, WINSIZEY));
			_missileE->fire(_rcBoss.left - 100, RANDOM->Range(0, WINSIZEY));
			_missileE->fire(_rcBoss.left - 100, RANDOM->Range(0, WINSIZEY));
			_missileE->fire(_rcBoss.left - 100, RANDOM->Range(0, WINSIZEY));
			_missileE->fire(_rcBoss.left - 100, RANDOM->Range(0, WINSIZEY));
			_missileE->fire(_rcBoss.left - 100, RANDOM->Range(0, WINSIZEY));
			_missileE->fire(_rcBoss.left - 100, RANDOM->Range(0, WINSIZEY));
			_missileE->fire(_rcBoss.left - 100, RANDOM->Range(0, WINSIZEY));
		}
	}
	if (_bossBotHP > 0)
	{
		if (_count % 300 == 0)
		{
			_missile->fire(_rcBossB.left - 110, _rcBossB.top + 50, PI * 1.5);
			_missile->fire(_rcBossB.left - 110, _rcBossB.top + 50, PI * 1.4);
			_missile->fire(_rcBossB.left - 110, _rcBossB.top + 50, PI * 1.3);
			_missile->fire(_rcBossB.left - 110, _rcBossB.top + 50, PI * 1.2);
			_missile->fire(_rcBossB.left - 110, _rcBossB.top + 50, PI * 1.1);
			_missile->fire(_rcBossB.left - 110, _rcBossB.top + 50, PI);
			_missile->fire(_rcBossB.left - 110, _rcBossB.top + 50, PI * 9 /10);
			_missile->fire(_rcBossB.left - 110, _rcBossB.top + 50, PI * 8 / 10);
			_missile->fire(_rcBossB.left - 110, _rcBossB.top + 50, PI * 7 / 10);
			_missile->fire(_rcBossB.left - 110, _rcBossB.top + 50, PI * 6 / 10);
			_missile->fire(_rcBossB.left - 110, _rcBossB.top + 50, PI * 5 / 10);
			_missile->fire(_rcBossB.left - 110, _rcBossB.top + 50, PI * 4 / 10);
			_missile->fire(_rcBossB.left - 110, _rcBossB.top + 50, PI * 3 / 10);
			_missile->fire(_rcBossB.left - 110, _rcBossB.top + 50, PI * 2 / 10);
		}
	}


	
	
	//		if (_count % 150 == 0)
	//		{
	//			if (_life[0])
	//			{
	//				_Enemy[0].angle = getAngle(_Enemy[0].x, _Enemy[0].y, getPlayerx() + 40, getPlayery());
	//				_missile->fire(_rcEnemy1[0].left - 30, _rcEnemy1[0].top + 40, _Enemy[0].angle);
	//			}
	//			if (_life[1])
	//			{
	//				_Enemy[1].angle = getAngle(_Enemy[1].x, _Enemy[1].y, getPlayerx() + 40, getPlayery());
	//				_missile->fire(_rcEnemy1[1].left - 30, _rcEnemy1[1].top + 40, _Enemy[1].angle);
	//			}
	//			if (_life[2])
	//			{
	//				_Enemy[2].angle = getAngle(_Enemy[2].x, _Enemy[2].y, getPlayerx() + 40, getPlayery());
	//				_missile->fire(_rcEnemy1[2].left - 30, _rcEnemy1[2].top + 40, _Enemy[2].angle);
	//			}
	//		}
	//	}
	//	if (_enemyHP[i] <= 0)
	//	{
	//		_life[i] = false;
	//	}
	//	if (!_life[i])
	//	{
	//		_rcEnemy1[i].left = -500;
	//		_rcEnemy1[i].right = -500;
	//		_rcEnemy1[i].top = 2000;
	//		_rcEnemy1[i].bottom = 2000;
	//	}
	//}


	//�̻��� Ŭ���� ������Ʈ


	this->Move();

	this->animation();
	_missile->update();
	_missileE->update();
}

void boss::render()
{
	//�÷��̾� ����
	//_rocket->render(getMemDC(), _rocket->getX(), _rocket->getY());
	//_rocket->render(getMemDC(), _rcPlayer.left, _rcPlayer.top);

	if (_bossHP > 0)
	{
	IMAGEMANAGER->frameRender("����", getMemDC(), _boss.xT - 200, _boss.yT - 200);
	}
	//�̻��� Ŭ���� ����
	_missile->render();
	_missileE->render();
}

void boss::animation()
{
	_motion++;
	_bossImage->setFrameY(0);
	
	
		if (_state == NORMAL)
		{
			_bossImage->setFrameX(0);
		}
		if (_state == TOP)
		{
			_bossImage->setFrameX(1);
		}
		if (_state == BOTTOM)
		{
			_bossImage->setFrameX(2);
		}
		if (_state == BOTH)
		{
			_bossImage->setFrameX(3);
		}
	
}

void boss::Move()
{
	//�������� ������Ѿ� �Ѵ�
	_boss.x += cosf(_boss.angle) * _boss.speed;
	_boss.y += -sinf(_boss.angle) * _boss.speed;

	//�Ѿ��� ȭ������� ��������
	//����
	if (_boss.xT - _boss.radius < 400)
	{
		//_boss.fire = false;
		_boss.x += 7;
		//_boss.angle = PI - _boss.angle;
		_boss.angle = RANDOM->Range(0.1,PI);
	}
	//������
	if (_boss.x + 100 > WINSIZEX)
	{
		//_boss.fire = false;
		_boss.x -= 7;
		//_boss.angle = PI - _boss.angle;
		_boss.angle = RANDOM->Range(PI + 0.1,PI * 2);
	}
	//��
	if (_boss.yT < 0)
	{
		//_boss.fire = false;
		_boss.y += 7;
		//_boss.angle = PI * 2 - _boss.angle;
		_boss.angle = RANDOM->Range(PI + 0.1,PI * 2);
	}
	//�Ʒ�
	if (_boss.yB + 50> WINSIZEY)
	{
		//_boss.fire = false;
		_boss.y -= 7;
		//_boss.angle = PI * 2 - _boss.angle;
		_boss.angle = RANDOM->Range( 0.1,PI );

		//_boss.gravity = 0.0f;
		//_boss.fire = false;
	}
}

float boss::getDistance(float startX, float startY, float endX, float endY)
{
	float x = endX - startX;
	float y = endY - startY;

	return sqrtf(x * x + y * y);
}

float boss::getAngle(float startX, float startY, float endX, float endY)
{
	float x = endX - startX;
	float y = endY - startY;
	//���� ������ �Ÿ�(����)
	float distance = sqrtf(x * x + y * y);
	//���� ������ ���� ���ϴ� ����(���Լ� ���)
	//������ X�� ���̸� �˰� ������ ������ �˼��ִ�
	float angle = acosf(x / distance);
	//����ó��
	//������ API���� acosf�� 0 ~ 180�� ������
	//���Ȱ�(0.0f ~ 3.14f) ���Ͻ�Ų��
	//180�� �̻��� �������� ����ó���� ����� �Ѵ�
	if (endY > startY)
	{
		angle = (PI * 2) - angle;
	}
	return angle;
}

