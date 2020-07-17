#include "stdafx.h"
#include "enemy3.h"

HRESULT enemy3::init()
{
	//플레이어 이미지 초기화
	_enemy = IMAGEMANAGER->addFrameImage("적3", "그림파일/해골 프레임.bmp", 960, 110, 8, 1, true, RGB(255, 0, 255));
	_bullet = IMAGEMANAGER->addFrameImage("총알", "그림파일/작은총알 프레임.bmp", 120, 30, 4, 1, true, RGB(255, 0, 255));
	


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

	//미사일 클래스 초기화
	_missile = new missileE;
	_missile->init(10, 1500);

	return S_OK;
}

void enemy3::release()
{
	//미사일 클래스 해제
	_missile->release();
	SAFE_DELETE(_missile);
}

void enemy3::update()
{
	//플레이어 움직이기 & 화면밖으로 나가지 못하게 만들기
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


	//미사일 클래스 업데이트


	//this->Move();

	this->animation();
	_missile->update();
}

void enemy3::render()
{
	//플레이어 렌더
	//_rocket->render(getMemDC(), _rocket->getX(), _rocket->getY());
	//_rocket->render(getMemDC(), _rcPlayer.left, _rcPlayer.top);

	for (int i = 0; i < 10; i++)
	{
		if (_life[i] == true)
		{
			IMAGEMANAGER->frameRender("적3", getMemDC(), _Enemy[i].x - 60, _Enemy[i].y - 55);
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
		if (i == 0)//머리냐?
		{
			////왼쪽
			//if (_Enemy[i].x - _Enemy[i].radius < 0)
			//{
			//	_Enemy[i].x++;
			//	_Enemy[i].angle = PI - _Enemy[i].angle;
			//}
			////오른쪽
			//if (_Enemy[i].x + _Enemy[i].radius > WINSIZEX)
			//{
			//	_Enemy[i].x--;
			//	_Enemy[i].angle = PI - _Enemy[i].angle;
			//}
			////위
			//if (_Enemy[i].y - _Enemy[i].radius < 0)
			//{
			//	_Enemy[i].y++;
			//	_Enemy[i].angle = 2 * PI - _Enemy[i].angle;
			//}
			////아래
			//if (_Enemy[i].y + _Enemy[i].radius > WINSIZEY)
			//{
			//	_Enemy[i].y--;
			//	_Enemy[i].angle = 2 * PI - _Enemy[i].angle;
			//}
		}
		else//몸통이냐?
		{
			float distance = getDistance(_Enemy[i].x, _Enemy[i].y, _Enemy[i - 1].x, _Enemy[i - 1].y);
			//거리가 벌어졌다는 의미는
			//각도가 달라졌다는 말
			//각도가 달라졌으니 앞의 각도를 전달해주자

			if (_Enemy[i].radius * 2 < distance)
			{
				_Enemy[i].angle = getAngle(_Enemy[i].x, _Enemy[i].y, _Enemy[i - 1].x, _Enemy[i - 1].y);
				//위치를 살짝 보정해주기
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
	//두점 사이의 거리(빗변)
	float distance = sqrtf(x * x + y * y);
	//두점 사이의 각도 구하는 공식(역함수 사용)
	//빗변과 X의 길이를 알고 있으면 각도를 알수있다
	float angle = acosf(x / distance);
	//예외처리
	//윈도우 API에서 acosf는 0 ~ 180도 까지의
	//라디안값(0.0f ~ 3.14f) 리턴시킨다
	//180도 이상의 값에대한 예외처리를 해줘야 한다
	if (endY > startY)
	{
		angle = (PI * 2) - angle;
	}
	return angle;
}

