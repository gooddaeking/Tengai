#include "stdafx.h"
#include "enemy4.h"

HRESULT enemy4::init()
{
	//�÷��̾� �̹��� �ʱ�ȭ
	_enemy = IMAGEMANAGER->addFrameImage("Ȱ����", "�׸�����/Ȱ���� ������.bmp", 850, 180, 5, 1, true, RGB(255, 0, 255));
	_bullet = IMAGEMANAGER->addFrameImage("ū�Ѿ�", "�׸�����/ū�Ѿ� ������.bmp", 150, 50, 3, 1, true, RGB(255, 0, 255));

	_state = MOVE;

	for (int i = 0; i < 3; i++)
	{
		_Enemy[i].speed = 4.0f;
		_Enemy[i].radius = 65;
		_Enemy[i].angle = PI;
		_enemyHP[i] = 20;
		_life[i] = true;
	}
	_Enemy[0].x = WINSIZEX + 150;
	_Enemy[0].y = 100;
	_Enemy[1].x = WINSIZEX + 350;
	_Enemy[1].y = 350;
	_Enemy[2].x = WINSIZEX + 200;
	_Enemy[2].y = 650;
	_motion = _index =  0;
	_count = 1;
	random = RANDOM->Range(2 * PI);

	//�̻��� Ŭ���� �ʱ�ȭ
	_missile = new missileB;
	_missile->init(30, 1500);
	

	return S_OK;
}

void enemy4::release()
{
	//�̻��� Ŭ���� ����
	_missile->release();
	SAFE_DELETE(_missile);
}

void enemy4::update()
{
	//�÷��̾� �����̱� & ȭ������� ������ ���ϰ� �����
	_count++;
	if (_count % 2000 == 0)
	{
		_Enemy[0].x = WINSIZEX + 150;
		_Enemy[0].y = 100;
		_Enemy[1].x = WINSIZEX + 350;
		_Enemy[1].y = 350;
		_Enemy[2].x = WINSIZEX + 200;
		_Enemy[2].y = 650;
		for (int i = 0; i < 3; i++)
		{
			_enemyHP[i] = 20;
			_life[i] = true;
			_state = MOVE;
		}
	}
	for (int i = 0; i < 3; i++)
	{
		_rcEnemy1[i] = RectMakeCenter(_Enemy[i].x, _Enemy[i].y, 120, 120);
	}

	//_Enemy[0].angle += 0f;
	for (int i = 0; i < 3; i++)
	{
		if (_rcEnemy1[0].left > 600)
		{
			_Enemy[i].x -= 5;
		}
		if (_rcEnemy1[0].left < 610)
		{
			_state = STOP;
		}
		if (_state == STOP)
		{
			if (_count % 150 == 0)
			{
				if (_life[0])
				{
					_Enemy[0].angle = getAngle(_Enemy[0].x, _Enemy[0].y, getPlayerx() + 40, getPlayery());
					_missile->fire(_rcEnemy1[0].left - 30, _rcEnemy1[0].top + 40, _Enemy[0].angle);
				}
				if (_life[1])
				{
					_Enemy[1].angle = getAngle(_Enemy[1].x, _Enemy[1].y, getPlayerx() + 40, getPlayery());
					_missile->fire(_rcEnemy1[1].left - 30, _rcEnemy1[1].top + 40, _Enemy[1].angle);
				}
				if (_life[2])
				{
					_Enemy[2].angle = getAngle(_Enemy[2].x, _Enemy[2].y, getPlayerx() + 40, getPlayery());
					_missile->fire(_rcEnemy1[2].left - 30, _rcEnemy1[2].top + 40, _Enemy[2].angle);
				}
			}
		}
		if (_enemyHP[i] <= 0)
		{
			_life[i] = false;
		}
		if (!_life[i])
		{
			_rcEnemy1[i].left = -500;
			_rcEnemy1[i].right = -500;
			_rcEnemy1[i].top = 2000;
			_rcEnemy1[i].bottom = 2000;
		}
	}


	//�̻��� Ŭ���� ������Ʈ


	//this->Move();

	this->animation();
	_missile->update();
}

void enemy4::render()
{
	//�÷��̾� ����
	//_rocket->render(getMemDC(), _rocket->getX(), _rocket->getY());
	//_rocket->render(getMemDC(), _rcPlayer.left, _rcPlayer.top);

	for (int i = 0; i < 3; i++)
	{
		if (_life[i] == true)
		{
			IMAGEMANAGER->frameRender("Ȱ����", getMemDC(), _Enemy[i].x - 85, _Enemy[i].y - 90);
		}
	}
	//if (_power)
	//{
	//	IMAGEMANAGER->frameRender("�Ŀ�", getMemDC(), _rcPower.left - 20, _rcPower.top - 20);
	//}
	//�̻��� Ŭ���� ����
	_missile->render();
}

void enemy4::animation()
{
	_motion++;
	_enemy->setFrameY(0);

	if (_state == MOVE)
	{
		_enemy->setFrameX(0);
	}
	if (_state == STOP)
	{
		if (_motion % 10 == 0)
		{
			_enemy->setFrameX(_index);
			_index++;
			if (_index > 4)
			{
				_index = 4;
			}
		}
	}
}

void enemy4::Move()
{
	for (int i = 0; i < 5; i++)
	{
		_Enemy[i].x += cosf(_Enemy[i].angle) * _Enemy[i].speed;
		_Enemy[i].y += -sinf(_Enemy[i].angle) * _Enemy[i].speed;
		if (i == 0)//�Ӹ���?
		{
			////����
			//if (_Enemy[i].x - _Enemy[i].radius < 0)
			//{
			//	_Enemy[i].x++;
			//	_Enemy[i].angle = PI - _Enemy[i].angle;
			//}
			////������
			//if (_Enemy[i].x + _Enemy[i].radius > WINSIZEX)
			//{
			//	_Enemy[i].x--;
			//	_Enemy[i].angle = PI - _Enemy[i].angle;
			//}
			////��
			//if (_Enemy[i].y - _Enemy[i].radius < 0)
			//{
			//	_Enemy[i].y++;
			//	_Enemy[i].angle = 2 * PI - _Enemy[i].angle;
			//}
			////�Ʒ�
			//if (_Enemy[i].y + _Enemy[i].radius > WINSIZEY)
			//{
			//	_Enemy[i].y--;
			//	_Enemy[i].angle = 2 * PI - _Enemy[i].angle;
			//}
		}
		else//�����̳�?
		{
			float distance = getDistance(_Enemy[i].x, _Enemy[i].y, _Enemy[i - 1].x, _Enemy[i - 1].y);
			//�Ÿ��� �������ٴ� �ǹ̴�
			//������ �޶����ٴ� ��
			//������ �޶������� ���� ������ ����������

			if (_Enemy[i].radius * 2 < distance)
			{
				_Enemy[i].angle = getAngle(_Enemy[i].x, _Enemy[i].y, _Enemy[i - 1].x, _Enemy[i - 1].y);
				//��ġ�� ��¦ �������ֱ�
				_Enemy[i].x = _Enemy[i - 1].x - cosf(_Enemy[i].angle) * (_Enemy[i].radius * 2);
				_Enemy[i].y = _Enemy[i - 1].y - (-sinf(_Enemy[i].angle)) * (_Enemy[i].radius * 2);
			}
		}
	}
}

float enemy4::getDistance(float startX, float startY, float endX, float endY)
{
	float x = endX - startX;
	float y = endY - startY;

	return sqrtf(x * x + y * y);
}

float enemy4::getAngle(float startX, float startY, float endX, float endY)
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
