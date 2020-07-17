#include "stdafx.h"
#include "player.h"

HRESULT player::init()
{
	//플레이어 이미지 초기화
	_idle = IMAGEMANAGER->addFrameImage("달마", "그림파일/캐릭터 프레임.bmp", 1080, 120, 9, 1, true, RGB(255, 0, 255));
	_bullet = IMAGEMANAGER->addFrameImage("달마공격", "그림파일/스님 총알 프레임.bmp", 440, 240, 4, 3, true, RGB(255, 0, 255));
	_bird = IMAGEMANAGER->addFrameImage("새", "그림파일/스님새 프레임.bmp", 440, 80, 4, 1, true, RGB(255, 0, 255));
	_bird2 = IMAGEMANAGER->addFrameImage("새2", "그림파일/기폭발프레임.bmp", 880, 80, 8, 1, true, RGB(255, 0, 255));
	_angryBird = IMAGEMANAGER->addFrameImage("화난새", "그림파일/기발사프레임.bmp", 2400, 420, 8, 1, true, RGB(255, 0, 255));
	
	//플레이어 렉트
	_rcPlayer = RectMakeCenter(-200, WINSIZEY / 2, 60, 60);
	_motion = _index = _power = 0;
	_birdCount = _birdIndex = _birdIndex2 = _angryCount = 0;
	_angry = false;
	_state = IDLE;
	_pcLife = 30000;

	//for (int i = 0; i < 30; i++)
	//{
	//	bullet[i] = false;
	//	_Bullet[i] = RectMake(_rcPlayer.right, _rcPlayer.top + 30, 10, 10);
	//}

	//미사일 클래스 초기화
	_missile = new missile;
	_missile->init(29, 1200);
	_missileP = new missileP;
	_missileP->init(20, 1200);
	_missileP2 = new missileP2;
	_missileP2->init(20, 1200);
	_missileZ = new missileZ;
	_missileZ->init(10, 1500);

	return S_OK;
}

void player::release()
{
	//미사일 클래스 해제
	_missile->release();
	SAFE_DELETE(_missile);
	_missileP->release();
	SAFE_DELETE(_missileP);
	_missileP2->release();
	SAFE_DELETE(_missileP2);
	_missileZ->release();
	SAFE_DELETE(_missileZ);
}

void player::update()
{
	//유도탄
	if (_rcPlayer.left - 30 < 0)
	{
		_rcPlayer.left += 2;
		_rcPlayer.right += 2;
	}

	_missile->setPower(_power);
	if (_power >= 4)
	{
		_power = 4;
	}

	//플레이어 움직이기 & 화면밖으로 나가지 못하게 만들기
	_idle->setX(_rcPlayer.left +30);
	_idle->setY(_rcPlayer.top +30);
	_x = _idle->getX() ;
	_y = _idle->getY() ;
	if (INPUT->GetKey(VK_LEFT) && _rcPlayer.left -30 > 0)
	{
		_rcPlayer.left -= 5.0f;
		_rcPlayer.right -= 5.0f;
		_state = BACK;
	}
	if (INPUT->GetKeyUp(VK_LEFT))
	{
		_state = IDLE;
	}
	if (INPUT->GetKey(VK_UP) && _rcPlayer.top -20 > 0)
	{
		_rcPlayer.top -= 5.0f;
		_rcPlayer.bottom -= 5.0f;
		_state = BACK;
	}
	if (INPUT->GetKeyUp(VK_UP))
	{
		_state = IDLE;
	}
	if (INPUT->GetKey(VK_RIGHT) && _rcPlayer.right +20 < WINSIZEX)
	{
		_rcPlayer.left += 5.0f;
		_rcPlayer.right += 5.0f;
		_state = IDLE;
	}
	
	if (INPUT->GetKey(VK_DOWN) && _rcPlayer.bottom +20 < WINSIZEY)
	{
		_rcPlayer.top += 5.0f;
		_rcPlayer.bottom += 5.0f;
	}
	//총알발사
	if (INPUT->GetKeyDown('Z'))
	{
		_missile->fire(_rcPlayer.right + 40, _rcPlayer.top + 20);
		if (_power == 1)
		{
			_missileP->fire(_rcPlayer.left - 80, _rcPlayer.top - 90);
			_missileP2->fire(_rcPlayer.left - 80, _rcPlayer.top - 90);
		}
		if (_power == 2)
		{
			_missileP->fire(_rcPlayer.left - 80, _rcPlayer.top - 90);
			_missileP2->fire(_rcPlayer.left - 80, _rcPlayer.top - 90);
			_missileP->fire(_rcPlayer.left - 120, _rcPlayer.top - 80);
			_missileP2->fire(_rcPlayer.left - 120, _rcPlayer.top - 80);
		}
		if (_power == 3)
		{
			_missileP->fire(_rcPlayer.left - 80, _rcPlayer.top - 90);
			_missileP2->fire(_rcPlayer.left - 80, _rcPlayer.top - 90);
			_missileP->fire(_rcPlayer.left - 120, _rcPlayer.top - 80);
			_missileP2->fire(_rcPlayer.left - 120, _rcPlayer.top - 80);
			_missileP->fire(_rcPlayer.left - 160, _rcPlayer.top - 100);
			_missileP2->fire(_rcPlayer.left - 160, _rcPlayer.top - 100);
		}
		if (_power >= 4)
		{
			_missileP->fire(_rcPlayer.left - 80, _rcPlayer.top - 90);
			_missileP2->fire(_rcPlayer.left - 80, _rcPlayer.top - 90);
			_missileP->fire(_rcPlayer.left - 120, _rcPlayer.top - 80);
			_missileP2->fire(_rcPlayer.left - 120, _rcPlayer.top - 80);
			_missileP->fire(_rcPlayer.left - 160, _rcPlayer.top - 100);
			_missileP2->fire(_rcPlayer.left - 160, _rcPlayer.top - 100);
			_missileP->fire(_rcPlayer.left - 40, _rcPlayer.top - 70);
			_missileP2->fire(_rcPlayer.left - 40, _rcPlayer.top - 70);
		}
	}
	if (INPUT->GetKey('Z'))
	{
		_angryCount++;
		if (_angryCount > 70 && _power > 0)
		{
			_angry = true;
		}
	}
	if (INPUT->GetKeyUp('Z'))
	{
		if (_angry)
		{
			_missileZ->fire(_rcPlayer.right, _rcPlayer.top - 150);
		}
		_angryCount = 0;
		_angry = false;
	}
	//미사일 클래스 업데이트
	this->animation();

	_missile->update();
	_missileP->update();
	_missileP2->update();
	_missileZ->update();
}

void player::render()
{
	//플레이어 렌더
	//_rocket->render(getMemDC(), _rocket->getX(), _rocket->getY());
	//_rocket->render(getMemDC(), _rcPlayer.left, _rcPlayer.top);
	if (_state == IDLE || _state == BACK)
	{
		IMAGEMANAGER->frameRender("달마", getMemDC(), _rcPlayer.left-30, _rcPlayer.top-30);
	}
	if (_power >= 1 && !_angry)
	{
		IMAGEMANAGER->frameRender("새", getMemDC(), _rcPlayer.left - 90, _rcPlayer.top - 90);
		_bird->setFrameY(0);
		_birdCount++;
		if (_birdCount % 7 == 0)
		{
			_birdIndex++;
			if (_birdIndex > 3)
			{
				_birdIndex = 0;
			}
			_bird->setFrameX(_birdIndex);
		}
	}
	if (_power >= 1 && _angry)
	{
		IMAGEMANAGER->frameRender("새2", getMemDC(), _rcPlayer.right + 20, _rcPlayer.top - 70);
		_bird2->setFrameY(0);
		_birdCount++;
		if (_birdCount % 4 == 0)
		{
			_birdIndex2++;
			if (_birdIndex2 > 7)
			{
				_birdIndex2 = 0;
			}
			_bird2->setFrameX(_birdIndex2);
		}
	}
	//미사일 클래스 렌더
	_missile->render();
	_missileP->render();
	_missileP2->render();
	_missileZ->render();
}

void player::animation()
{
	switch (_state)
	{
	case IDLE:
		_motion++;
		_idle->setFrameY(0);
		if (_motion % 5 == 0)
		{
			_index--; if (_index < 0)
			{
				_index = 2;
			}
			_idle->setFrameX(_index);
		}
		break;
	case BACK:
		_motion++;
		_idle->setFrameY(0);
		if (_motion % 6 == 0)
		{
			_index++;
			//if (_index < 2)
			//{
			//	_index = 3;
			//}
			if (_index > 8)
			{
				_index = 6;
			}
			_idle->setFrameX(_index);
		}
		break;
	case POWER:

		break;
	//case RUN:
	//	//왼쪽프레임 일때 인덱스 변경하기(애니메이션)
	//	break;
	case DEAD:
		break;
	}
}