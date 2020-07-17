#include "stdafx.h"
#include "enemy3.h"

HRESULT enemy3::init()
{
	//�÷��̾� �̹��� �ʱ�ȭ
	_enemy = IMAGEMANAGER->addFrameImage("��3", "�׸�����/�ذ� ������.bmp", 960, 110, 8, 1, true, RGB(255, 0, 255));
	_bullet = IMAGEMANAGER->addFrameImage("�Ѿ�", "�׸�����/�����Ѿ� ������.bmp", 120, 30, 4, 1, true, RGB(255, 0, 255));
	


	for (int i = 0; i < 10; i++)
	{
		_Enemy[i].speed = 4.0f;
		_Enemy[i].radius = 65;
		_Enemy[i].angle =  PI;
		_Enemy[i].x = WINSIZEX + 100 + i * 150;
		_Enemy[i].y = 50 + i * 100;
		_life[i] = true;
	}
	_motion = _index = _count = 0;
	random = RANDOM->Range(2 * PI);

	//�̻��� Ŭ���� �ʱ�ȭ
	_missile = new missileE;
	_missile->init(10, 1500);

	return S_OK;
}

void enemy3::release()
{
	//�̻��� Ŭ���� ����
	_missile->release();
	SAFE_DELETE(_missile);
}

void enemy3::update()
{
	//�÷��̾� �����̱� & ȭ������� ������ ���ϰ� �����
	_count++;
	if (_count % 1000 == 0)
	{
		for (int i = 0; i < 10; i++)
		{
			_Enemy[i].speed = 4.0f;
			_Enemy[i].radius = 65;
			_Enemy[i].angle = PI;
			_Enemy[i].x = WINSIZEX + 100 + i * 150;
			_Enemy[i].y = 50 + i * 100;
			_life[i] = true;
			
		}
	}
	for (int i = 0; i < 10; i++)
	{
		_rcEnemy1[i] = RectMakeCenter(_Enemy[i].x, _Enemy[i].y, 60, 55);
		if (!_life[i])
		{
			_rcEnemy1[i].left = -500;
			_rcEnemy1[i].right = -500;
			_rcEnemy1[i].top = 2000;
			_rcEnemy1[i].bottom = 2000;
		}
	}

	//_Enemy[0].angle += 0f;
	for (int i = 0; i < 10; i++)
	{
		_Enemy[i].x -= 5;
		if (_rcEnemy1[0].left < 600 && _rcEnemy1[0].left > 500)
		{
			_missile->fire(_rcEnemy1[0].left - 30, _rcEnemy1[0].top + 20);
			_missile->fire(_rcEnemy1[1].left - 30, _rcEnemy1[1].top + 20);
			_missile->fire(_rcEnemy1[2].left - 30, _rcEnemy1[2].top + 20);
			_missile->fire(_rcEnemy1[3].left - 30, _rcEnemy1[3].top + 20);
			_missile->fire(_rcEnemy1[4].left - 30, _rcEnemy1[4].top + 20);
			_missile->fire(_rcEnemy1[5].left - 30, _rcEnemy1[5].top + 20);
			_missile->fire(_rcEnemy1[6].left - 30, _rcEnemy1[6].top + 20);
			_missile->fire(_rcEnemy1[7].left - 30, _rcEnemy1[7].top + 20);
			_missile->fire(_rcEnemy1[8].left - 30, _rcEnemy1[8].top + 20);
			_missile->fire(_rcEnemy1[9].left - 30, _rcEnemy1[9].top + 20);
		}
	}


	//�̻��� Ŭ���� ������Ʈ


	//this->Move();

	this->animation();
	_missile->update();
}

void enemy3::render()
{
	//�÷��̾� ����
	//_rocket->render(getMemDC(), _rocket->getX(), _rocket->getY());
	//_rocket->render(getMemDC(), _rcPlayer.left, _rcPlayer.top);

	for (int i = 0; i < 10; i++)
	{
		if (_life[i] == true)
		{
			IMAGEMANAGER->frameRender("��3", getMemDC(), _Enemy[i].x - 60, _Enemy[i].y - 55);
		}
	}
	_missile->render();
}

void enemy3::animation()
{
	_motion++;
	_enemy->setFrameY(0);
	
	if (_motion % 10 == 0)
	{
		_enemy->setFrameX(_index);
		_index++;
		if (_index > 8)
		{
			_index = 0;
		}
	}
}

void enemy3::Move()
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

float enemy3::getDistance(float startX, float startY, float endX, float endY)
{
	float x = endX - startX;
	float y = endY - startY;

	return sqrtf(x * x + y * y);
}

float enemy3::getAngle(float startX, float startY, float endX, float endY)
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

