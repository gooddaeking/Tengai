#include "stdafx.h"
#include "bullet.h"

//=============================================================
//	## bullet ## (�����Ѿ� - ������� ������ ��)
//=============================================================
HRESULT bullet::init()
{
	return S_OK;
}

void bullet::release()
{
}

void bullet::update()
{
}

void bullet::render()
{
}

//=============================================================
//	## missile ## (missile[0] -> �迭ó�� �̸� �����صΰ� �Ѿ˹߻�)
//=============================================================
HRESULT missile::init(int bulletMax, float range)
{
	//�Ѿ� ��Ÿ� �� �Ѿ� ���� �ʱ�ȭ
	_range = range;
	_bulletMax = bulletMax;
	frameX[bulletMax];
	frameY[bulletMax];
	_count = 0;

	//�Ѿ��� ������ŭ ����ü�� �ʱ�ȭ �� �� ���Ϳ� ���
	for (int i = 0; i < bulletMax; i++)
	{
		//�Ѿ� ����ü ����
		tagBullet bullet;
		//�Ѿ˱���ü �ʱ�ȭ
		//���θ޸�, ���
		//����ü�� �������� ���� �ѹ��� 0���� �ʱ�ȭ �����ش�
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new image;
		bullet.bulletImage->init("�׸�����/���� �Ѿ� ������.bmp", 440, 400, 4, 5, true, RGB(255, 0, 255));
		bullet.speed = 30.0f;
		bullet.fire = false;
		frameX[i] = 0;
		frameY[i] = 0;
		//���Ϳ� ���
		_vBullet.push_back(bullet);
	}

	return S_OK;
}

void missile::release()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i].bulletImage->release();
		SAFE_DELETE(_vBullet[i].bulletImage);
	}
}

void missile::update()
{
	

	this->move();
}

void missile::render()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		if (!_vBullet[i].fire) continue;
		//_vBullet[i].bulletImage->render(getMemDC(), _vBullet[i].rc.left, _vBullet[i].rc.top);
		_vBullet[i].bulletImage->frameRender(getMemDC(), _vBullet[i].rc.left, _vBullet[i].rc.top, frameX[i], frameY[i]);
		_count++;
		if (_count % 5 == 0)
		{
			frameX[i]++;
			if (frameX[i] > 3)
			{
				frameX[i] = 0;
			}

			frameY[i] = _power;
		}
	}
}

void missile::fire(float x, float y)
{

	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->fire) continue;
		_viBullet->fire = true;
		_viBullet->x = _viBullet->fireX = x;
		_viBullet->y = _viBullet->fireY = y;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth()/4,
			_viBullet->bulletImage->getHeight()/3);
		break;
	}
}

void missile::move()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;
		_viBullet->x += _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth()/4,
			_viBullet->bulletImage->getHeight()/3);

		//�Ѿ��� ��Ÿ����� Ŀ������
		float distance = getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y);
		for (int i = 0; i < 30; i++)
		{
			if (_range < distance)
			{
				_viBullet->fire = false;
			}			
		}
	}
}

void missile::setBullet(int num, bool fire)
{
	_vBullet[num].fire = fire;	
}

void missile::setRC(int num)
{
	_vBullet[num].rc = RectMakeCenter(-2000, 2000, 0, 0);
}


//���ʹ� �̻���
void missileE::setBullet(int num, bool fire)
{
	_vBullet[num].fire = fire;
}

void missileE::setRC(int num)
{
	_vBullet[num].rc = RectMakeCenter(-2000, 2000, 0, 0);
}

void missileE::fire(float x, float y)
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->fire) continue;
		_viBullet->fire = true;
		_viBullet->x = _viBullet->fireX = x;
		_viBullet->y = _viBullet->fireY = y;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth() / 4,
			_viBullet->bulletImage->getHeight() / 3);
		break;
	}
}

void missileE::move()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;
		_viBullet->x -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth() / 4,
			_viBullet->bulletImage->getHeight() / 3);

		//�Ѿ��� ��Ÿ����� Ŀ������
		float distance = getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y);
		for (int i = 0; i < 30; i++)
		{
			//if (!_vBullet[i].fire)
			//{
			//	distance = 2000;
			//}
			if (_range < distance)
			{
				_viBullet->fire = false;
			}
		}
	}
}

HRESULT missileE::init(int bulletMax, float range)
{
	//�Ѿ� ��Ÿ� �� �Ѿ� ���� �ʱ�ȭ
	_range = range;
	_bulletMax = bulletMax;
	frameX[bulletMax];
	frameY[bulletMax];
	_count = 0;

	//�Ѿ��� ������ŭ ����ü�� �ʱ�ȭ �� �� ���Ϳ� ���
	for (int i = 0; i < bulletMax; i++)
	{
		//�Ѿ� ����ü ����
		tagBullet bullet;
		//�Ѿ˱���ü �ʱ�ȭ
		//���θ޸�, ���
		//����ü�� �������� ���� �ѹ��� 0���� �ʱ�ȭ �����ش�
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new image;
		bullet.bulletImage->init("�׸�����/�����Ѿ� ������.bmp", 120, 30, 4, 1, true, RGB(255, 0, 255));
		bullet.speed = 7.0f;
		bullet.fire = false;
		frameX[i] = 0;
		frameY[i] = 0;
		//���Ϳ� ���
		_vBullet.push_back(bullet);
	}

	return S_OK;
}

void missileE::release()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i].bulletImage->release();
		SAFE_DELETE(_vBullet[i].bulletImage);
	}
}

void missileE::update()
{
	this->move();
}

void missileE::render()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		if (!_vBullet[i].fire) continue;
		//_vBullet[i].bulletImage->render(getMemDC(), _vBullet[i].rc.left, _vBullet[i].rc.top);
		_vBullet[i].bulletImage->frameRender(getMemDC(), _vBullet[i].rc.left, _vBullet[i].rc.top, frameX[i], frameY[i]);
		_count++;
		if (_count % 2 == 0)
		{
			frameX[i]++;
			if (frameX[i] > 4)
			{
				frameX[i] = 0;
			}
			frameY[i] = 0;
		}
	}
}

void missileB::setBullet(int num, bool fire)
{
	_vBullet[num].fire = fire;
}

void missileB::setRC(int num)
{
	_vBullet[num].rc = RectMakeCenter(3000, 2000, 0, 0);
}

void missileB::fire(float x, float y, float angle)
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->fire) continue;
		_viBullet->fire = true;
		_viBullet->angle = angle;
		_viBullet->x = _viBullet->fireX = x;
		_viBullet->y = _viBullet->fireY = y;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth() / 4,
			_viBullet->bulletImage->getHeight() / 3);
		break;
	}
}

void missileB::move()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth() / 4,
			_viBullet->bulletImage->getHeight() / 3);

		//�Ѿ��� ��Ÿ����� Ŀ������
		float distance = getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y);
	
			if (_range < distance)
			{
				_viBullet->fire = false;
				_stop = true;
			}
	}
}

HRESULT missileB::init(int bulletMax, float range)
{
	//�Ѿ� ��Ÿ� �� �Ѿ� ���� �ʱ�ȭ
	_range = range;
	_bulletMax = bulletMax;
	frameX[bulletMax];
	frameY[bulletMax];
	_count = 0;
	_playerX = _playerY = 0;
	

	//�Ѿ��� ������ŭ ����ü�� �ʱ�ȭ �� �� ���Ϳ� ���
	for (int i = 0; i < bulletMax; i++)
	{
		//�Ѿ� ����ü ����
		tagBullet bullet;
		//�Ѿ˱���ü �ʱ�ȭ
		//���θ޸�, ���
		//����ü�� �������� ���� �ѹ��� 0���� �ʱ�ȭ �����ش�
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new image;
		bullet.bulletImage->init("�׸�����/ū�Ѿ� ������.bmp", 150, 50, 3, 1, true, RGB(255, 0, 255));
		bullet.speed = 10.0f;
		bullet.fire = false;
		frameX[i] = 0;
		frameY[i] = 0;
		_stop = false;
		//���Ϳ� ���
		_vBullet.push_back(bullet);
	}

	return S_OK;
}

void missileB::release()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i].bulletImage->release();
		SAFE_DELETE(_vBullet[i].bulletImage);
	}
}

void missileB::update()
{
	this->move();
}

void missileB::render()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		if (!_vBullet[i].fire) continue;
		//_vBullet[i].bulletImage->render(getMemDC(), _vBullet[i].rc.left, _vBullet[i].rc.top);
		_vBullet[i].bulletImage->frameRender(getMemDC(), _vBullet[i].rc.left, _vBullet[i].rc.top, frameX[i], frameY[i]);
		_count++;
		if (_count % 2 == 0)
		{
			frameX[i]++;
			if (frameX[i] > 4)
			{
				frameX[i] = 0;
			}
			frameY[i] = 0;
		}
	}
}

HRESULT missileP::init(int bulletMax, float range)
{
	//�Ѿ� ��Ÿ� �� �Ѿ� ���� �ʱ�ȭ
	_range = range;
	_bulletMax = bulletMax;
	frameX[bulletMax];
	frameY[bulletMax];
	_count = 0;

	//�Ѿ��� ������ŭ ����ü�� �ʱ�ȭ �� �� ���Ϳ� ���
	for (int i = 0; i < bulletMax; i++)
	{
		//�Ѿ� ����ü ����
		tagBullet bullet;
		//�Ѿ˱���ü �ʱ�ȭ
		//���θ޸�, ���
		//����ü�� �������� ���� �ѹ��� 0���� �ʱ�ȭ �����ش�
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new image;
		bullet.bulletImage->init("�׸�����/���Ի� �Ѿ�.bmp", 60, 40, true, RGB(255, 0, 255));
		bullet.speed = 20.0f;
		bullet.speed2 = 0.0f;
		bullet.fire = false;
		//���Ϳ� ���
		_vBullet.push_back(bullet);
	}

	return S_OK;
}

void missileP::release()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i].bulletImage->release();
		SAFE_DELETE(_vBullet[i].bulletImage);
	}
}

void missileP::update()
{
	this->move();
}

void missileP::render()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		if (!_vBullet[i].fire) continue;
		//_vBullet[i].bulletImage->render(getMemDC(), _vBullet[i].rc.left, _vBullet[i].rc.top);
		_vBullet[i].bulletImage->render(getMemDC(), _vBullet[i].rc.left, _vBullet[i].rc.top);
		

	}
}

void missileP::fire(float x, float y)
{

	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->fire) continue;
		_viBullet->fire = true;
		_viBullet->x = _viBullet->fireX = x;
		_viBullet->y = _viBullet->fireY = y;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth() / 4,
			_viBullet->bulletImage->getHeight() / 3);
		break;
	}
}

void missileP::move()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;
		if (_viBullet->speed > 0)
		{
			_viBullet->x += cosf(PI * 1.6) * _viBullet->speed;
			_viBullet->y += -sinf(PI * 1.6) * _viBullet->speed;
			_viBullet->speed -= 2;
		}
		if(_viBullet->speed <= 0)
		{
			_viBullet->x += cosf(PI * 2) * _viBullet->speed2;
			_viBullet->y += -sinf(PI * 2) * _viBullet->speed2;
			_viBullet->speed2 += 2;
		}
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth() / 4,
			_viBullet->bulletImage->getHeight() / 3);

		//�Ѿ��� ��Ÿ����� Ŀ������
		float distance = getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y);
		for (int i = 0; i < 30; i++)
		{
			if (_range < distance)
			{
				_viBullet->fire = false;
				_viBullet->speed = 20;
				_viBullet->speed2 = 0;
			}
		}
	}
}

void missileP::setBullet(int num, bool fire)
{
	_vBullet[num].fire = fire;
}

void missileP::setRC(int num)
{
	_vBullet[num].rc = RectMakeCenter(-2000, 2000, 0, 0);
}

HRESULT missileP2::init(int bulletMax, float range)
{
	//�Ѿ� ��Ÿ� �� �Ѿ� ���� �ʱ�ȭ
	_range = range;
	_bulletMax = bulletMax;
	frameX[bulletMax];
	frameY[bulletMax];
	_count = 0;

	//�Ѿ��� ������ŭ ����ü�� �ʱ�ȭ �� �� ���Ϳ� ���
	for (int i = 0; i < bulletMax; i++)
	{
		//�Ѿ� ����ü ����
		tagBullet bullet;
		//�Ѿ˱���ü �ʱ�ȭ
		//���θ޸�, ���
		//����ü�� �������� ���� �ѹ��� 0���� �ʱ�ȭ �����ش�
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new image;
		bullet.bulletImage->init("�׸�����/���Ի� �Ѿ�.bmp", 60, 40, true, RGB(255, 0, 255));
		bullet.speed = 20.0f;
		bullet.speed2 = 0.0f;
		bullet.fire = false;
		//���Ϳ� ���
		_vBullet.push_back(bullet);
	}

	return S_OK;
}

void missileP2::release()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i].bulletImage->release();
		SAFE_DELETE(_vBullet[i].bulletImage);
	}
}

void missileP2::update()
{
	this->move();
}

void missileP2::render()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		if (!_vBullet[i].fire) continue;
		//_vBullet[i].bulletImage->render(getMemDC(), _vBullet[i].rc.left, _vBullet[i].rc.top);
		_vBullet[i].bulletImage->render(getMemDC(), _vBullet[i].rc.left, _vBullet[i].rc.top);


	}
}

void missileP2::fire(float x, float y)
{

	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->fire) continue;
		_viBullet->fire = true;
		_viBullet->x = _viBullet->fireX = x;
		_viBullet->y = _viBullet->fireY = y;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth() / 4,
			_viBullet->bulletImage->getHeight() / 3);
		break;
	}
}

void missileP2::move()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;
		if (_viBullet->speed > 0)
		{
			_viBullet->x += cosf(PI * 0.4) * _viBullet->speed;
			_viBullet->y += -sinf(PI * 0.4) * _viBullet->speed;
			_viBullet->speed -= 2;
		}
		if (_viBullet->speed <= 0)
		{
			_viBullet->x += cosf(PI * 1.96) * _viBullet->speed2;
			_viBullet->y += -sinf(PI * 1.96) * _viBullet->speed2;
			_viBullet->speed2 += 2;
		}
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth() / 4,
			_viBullet->bulletImage->getHeight() / 3);

		//�Ѿ��� ��Ÿ����� Ŀ������
		float distance = getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y);
		for (int i = 0; i < 30; i++)
		{
			if (_range < distance)
			{
				_viBullet->fire = false;
				_viBullet->speed = 20;
				_viBullet->speed2 = 0;
			}
		}
	}
}

void missileP2::setBullet(int num, bool fire)
{
	_vBullet[num].fire = fire;
}

void missileP2::setRC(int num)
{
	_vBullet[num].rc = RectMakeCenter(-2000, 2000, 0, 0);
}

HRESULT missileZ::init(int bulletMax, float range)
{
	//�Ѿ� ��Ÿ� �� �Ѿ� ���� �ʱ�ȭ
	_range = range;
	_bulletMax = bulletMax;
	frameX[bulletMax];
	frameY[bulletMax];
	_count = 0;
	_speed = 20.0f;

	//�Ѿ��� ������ŭ ����ü�� �ʱ�ȭ �� �� ���Ϳ� ���
	for (int i = 0; i < bulletMax; i++)
	{
		//�Ѿ� ����ü ����
		tagBullet bullet;
		//�Ѿ˱���ü �ʱ�ȭ
		//���θ޸�, ���
		//����ü�� �������� ���� �ѹ��� 0���� �ʱ�ȭ �����ش�
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new image;
		bullet.bulletImage->init("�׸�����/��߻�������.bmp", 2400, 420, 8, 1, true, RGB(255, 0, 255));
		bullet.speed = 20.0f;
		bullet.fire = false;
		frameX[i] = 0;
		frameY[i] = 0;
		//���Ϳ� ���
		_vBullet.push_back(bullet);
	}

	return S_OK;
}

void missileZ::release()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i].bulletImage->release();
		SAFE_DELETE(_vBullet[i].bulletImage);
	}
}

void missileZ::update()
{


	this->move();
}

void missileZ::render()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		if (!_vBullet[i].fire) continue;
		//_vBullet[i].bulletImage->render(getMemDC(), _vBullet[i].rc.left, _vBullet[i].rc.top);
		_vBullet[i].bulletImage->frameRender(getMemDC(), _vBullet[i].rc.left, _vBullet[i].rc.top, frameX[i], frameY[i]);
		_count++;
		if (_count % 5 == 0)
		{
			frameX[i]++;
			if (frameX[i] > 7)
			{
				frameX[i] = 0;
			}

			frameY[i] = 0;
		}
	}
}

void missileZ::fire(float x, float y)
{

	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->fire) continue;
		_speed = 20.0f;
		_viBullet->fire = true;
		_viBullet->x = _viBullet->fireX = x;
		_viBullet->y = _viBullet->fireY = y;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth() / 4,
			_viBullet->bulletImage->getHeight() / 3);
		break;
	}
}

void missileZ::move()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;
		_viBullet->x += _speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth() / 4,
			_viBullet->bulletImage->getHeight() / 3);

		//�Ѿ��� ��Ÿ����� Ŀ������
		float distance = getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y);
		for (int i = 0; i < 30; i++)
		{
			if (_range < distance)
			{
				_viBullet->fire = false;
			}
		}
	}
}

void missileZ::setBullet(int num, bool fire)
{
	_vBullet[num].fire = fire;
}

void missileZ::setRC(int num)
{
	_vBullet[num].rc = RectMakeCenter(-2000, 2000, 0, 0);
}