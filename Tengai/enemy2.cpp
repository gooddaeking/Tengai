#include "stdafx.h"
#include "enemy2.h"

HRESULT enemy2::init()
{
	//�÷��̾� �̹��� �ʱ�ȭ
	_enemy = IMAGEMANAGER->addFrameImage("��1", "�׸�����/��1������.bmp", 440, 110, 4, 1, true, RGB(255, 0, 255));
	_enemy2 = IMAGEMANAGER->addFrameImage("��2", "�׸�����/��2������.bmp", 440, 110, 4, 1, true, RGB(255, 0, 255));
	_bullet = IMAGEMANAGER->addFrameImage("�Ѿ�", "�׸�����/�����Ѿ� ������.bmp", 120, 30, 4, 1, true, RGB(255, 0, 255));
	_powers = IMAGEMANAGER->addFrameImage("�Ŀ�", "�׸�����/�Ŀ� ������.bmp", 600, 120, 5, 1, true, RGB(255, 0, 255));

	

	for (int i = 0; i < 5; i++)
	{
		_Enemy[i].speed = 5.0f;
		_Enemy[i].radius = 65;
		_Enemy[i].angle = (i == 0) ? PI : _Enemy[i - 1].angle;
		_Enemy[i].x = (i == 0) ? WINSIZEX + 550 :
			_Enemy[i - 1].x - cosf(_Enemy[i].angle) * 150;
		_Enemy[i].y = (i == 0) ? 0 :
			_Enemy[i - 1].y - (-sinf(_Enemy[i].angle)) * 150;
		_life[i] = true;
	}
	_motion = _index = _indexP = 0;
	_power = false;
	random = RANDOM->Range(2 * PI);
	_anglePower = random;
	

	//for (int i = 0; i < 30; i++)
	//{
	//	bullet[i] = false;
	//	_Bullet[i] = RectMake(_rcPlayer.right, _rcPlayer.top + 30, 10, 10);
	//}

	//�̻��� Ŭ���� �ʱ�ȭ
	_missile = new missile;
	_missile->init(30, 1500);

	return S_OK;
}

void enemy2::release()
{
	//�̻��� Ŭ���� ����
	_missile->release();
	SAFE_DELETE(_missile);
}

void enemy2::update()
{
	for (int i = 0; i < 4; i++)
	{
		_rcEnemy1[i] = RectMakeCenter(_Enemy[i].x, _Enemy[i].y, 50, 50);
	}
	_rcEnemy2 = RectMakeCenter(_Enemy[4].x, _Enemy[4].y, 50, 50);

	_Enemy[0].angle += 0.004f;


	//�̻��� Ŭ���� ������Ʈ
	if (_Enemy[4].y > WINSIZEY + 55)
	{
		for (int i = 0; i < 5; i++)
		{
			_life[i] = true;

		}
	}

	if (_life[4])
	{
		power.x = _rcEnemy2.left;
		power.y = _rcEnemy2.bottom;
	}
	if (_life[4] == false)
	{
		_power = true;
		_rcPower = RectMakeCenter(power.x, power.y, 80, 80);
	}
	if (_power == true)
	{
		this->powerMove();
	}

	this->Move();

	this->animation();
	_missile->update();
}

void enemy2::render()
{
	for (int i = 0; i < 4; i++)
	{
		if (_life[i] == true)
		{
			IMAGEMANAGER->frameRender("��1", getMemDC(), _Enemy[i].x - 55, _Enemy[i].y - 55);
		}
	}
	if (_life[4] == true)
	{
		IMAGEMANAGER->frameRender("��2", getMemDC(), _Enemy[4].x - 55, _Enemy[4].y - 55);
	}
	if (_power)
	{
		IMAGEMANAGER->frameRender("�Ŀ�", getMemDC(), _rcPower.left - 20, _rcPower.top - 20);
	}
	//�̻��� Ŭ���� ����
	_missile->render();
}

void enemy2::animation()
{
	_motion++;
	_enemy->setFrameY(0);
	_enemy2->setFrameY(0);
	_powers->setFrameY(0);
	if (_motion % 10 == 0)
	{
		_enemy->setFrameX(_index);
		_enemy2->setFrameX(_index);
		_powers->setFrameX(_index);
		_index++;
		_indexP++;
		if (_index > 3)
		{
			_index = 0;
		}
		if (_index > 5)
		{
			_indexP = 0;
		}
	}
}

void enemy2::Move()
{
	for (int i = 0; i < 5; i++)
	{
		_Enemy[i].x += cosf(_Enemy[i].angle) * _Enemy[i].speed;
		_Enemy[i].y += -sinf(_Enemy[i].angle) * _Enemy[i].speed;
		if (i == 0)
		{
		}
		else//�����̳�?
		{
			float distance = getDistance(_Enemy[i].x, _Enemy[i].y, _Enemy[i - 1].x, _Enemy[i - 1].y);
			//�Ÿ��� �������ٴ� �ǹ̴�
			//������ �޶����ٴ� ��

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

float enemy2::getDistance(float startX, float startY, float endX, float endY)
{
	float x = endX - startX;
	float y = endY - startY;

	return sqrtf(x * x + y * y);
}

float enemy2::getAngle(float startX, float startY, float endX, float endY)
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

void enemy2::powerMove()
{

	_rcPower.left += cosf(random) * 3;
	_rcPower.right = _rcPower.left + 60;
	_rcPower.top += -sinf(random) * 3;
	_rcPower.bottom = _rcPower.top + 60;
	{
		//����
		if (_rcPower.left - 30 < 100)
		{
			_rcPower.left += 3;
			random = RANDOM->Range(PI * 2);
		}
		//������
		if (_rcPower.right + 30 > WINSIZEX)
		{
			_rcPower.left -= 3;
			random = RANDOM->Range(PI * 2);
		}
		//��
		if (_rcPower.top - 30 < 0)
		{
			_rcPower.top += 3;
			random = RANDOM->Range(PI * 2);
		}
		//�Ʒ�
		if (_rcPower.bottom + 30 > WINSIZEY)
		{
			_rcPower.top -= 3;
			random = RANDOM->Range(PI * 2);
		}
	}
}