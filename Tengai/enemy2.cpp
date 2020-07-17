#include "stdafx.h"
#include "enemy2.h"

HRESULT enemy2::init()
{
	//플레이어 이미지 초기화
	_enemy = IMAGEMANAGER->addFrameImage("적1", "그림파일/적1프레임.bmp", 440, 110, 4, 1, true, RGB(255, 0, 255));
	_enemy2 = IMAGEMANAGER->addFrameImage("적2", "그림파일/적2프레임.bmp", 440, 110, 4, 1, true, RGB(255, 0, 255));
	_bullet = IMAGEMANAGER->addFrameImage("총알", "그림파일/작은총알 프레임.bmp", 120, 30, 4, 1, true, RGB(255, 0, 255));
	_powers = IMAGEMANAGER->addFrameImage("파워", "그림파일/파워 프레임.bmp", 600, 120, 5, 1, true, RGB(255, 0, 255));

	

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

	//미사일 클래스 초기화
	_missile = new missile;
	_missile->init(30, 1500);

	return S_OK;
}

void enemy2::release()
{
	//미사일 클래스 해제
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


	//미사일 클래스 업데이트
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
			IMAGEMANAGER->frameRender("적1", getMemDC(), _Enemy[i].x - 55, _Enemy[i].y - 55);
		}
	}
	if (_life[4] == true)
	{
		IMAGEMANAGER->frameRender("적2", getMemDC(), _Enemy[4].x - 55, _Enemy[4].y - 55);
	}
	if (_power)
	{
		IMAGEMANAGER->frameRender("파워", getMemDC(), _rcPower.left - 20, _rcPower.top - 20);
	}
	//미사일 클래스 렌더
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
		else//몸통이냐?
		{
			float distance = getDistance(_Enemy[i].x, _Enemy[i].y, _Enemy[i - 1].x, _Enemy[i - 1].y);
			//거리가 벌어졌다는 의미는
			//각도가 달라졌다는 말

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

void enemy2::powerMove()
{

	_rcPower.left += cosf(random) * 3;
	_rcPower.right = _rcPower.left + 60;
	_rcPower.top += -sinf(random) * 3;
	_rcPower.bottom = _rcPower.top + 60;
	{
		//왼쪽
		if (_rcPower.left - 30 < 100)
		{
			_rcPower.left += 3;
			random = RANDOM->Range(PI * 2);
		}
		//오른쪽
		if (_rcPower.right + 30 > WINSIZEX)
		{
			_rcPower.left -= 3;
			random = RANDOM->Range(PI * 2);
		}
		//위
		if (_rcPower.top - 30 < 0)
		{
			_rcPower.top += 3;
			random = RANDOM->Range(PI * 2);
		}
		//아래
		if (_rcPower.bottom + 30 > WINSIZEY)
		{
			_rcPower.top -= 3;
			random = RANDOM->Range(PI * 2);
		}
	}
}