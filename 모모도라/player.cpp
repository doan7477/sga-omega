#include "stdafx.h"
#include "player.h"


player::player()
{
}


player::~player()
{
}

HRESULT player::init()
{
	_player.imgName = "정지";
	_player.img = IMAGEMANAGER->findImage(_player.imgName);
	_player.x = 200;
	_player.y = 560;
	_player.speed = 1.5f;
	_player.fps = 0;
	_player.jumpPower = JUMPPOWER;
	_player.gravity = GRAVITY;
	_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
	_player.state = PLAYERSTATE_RIGHT_IDLE;
	_player.isJump = _player.isJump = _player.isJump2 = false;


	return S_OK;
}

void player::release()
{

}

void player::update() 
{
	_player.fps++;
	inputKey();
	move();
	pixelCollision();
	if (_player.isJump) _player.jumpPower -= GRAVITY;
}

void player::render() 
{
	//Rectangle(getMemDC(), _player.rc.left, _player.rc.top, _player.rc.right, _player.rc.bottom);
	_player.img->frameRender(getMemDC(), _player.rc.left, _player.rc.top);
	if (_player.imgName == "정지")
	{
		if (_player.fps % 8 == 0)
		{
			_player.img->setFrameX(_player.img->getFrameX() + 1);
		}
	}
	else
	{
		if (_player.fps % 5 == 0)
		{
			_player.img->setFrameX(_player.img->getFrameX() + 1);
		}
	}
	switch (_player.state)
	{
	case PLAYERSTATE_LEFT_IDLE: case PLAYERSTATE_RIGHT_IDLE:
		if (_player.img->getFrameX() >= _player.img->getMaxFrameX())
			_player.img->setFrameX(0);
		break;
	case PLAYERSTATE_LEFT_BRAKE:
		if (_player.img->getFrameX() >= _player.img->getMaxFrameX())
		{
			_player.state = PLAYERSTATE_LEFT_IDLE;
		}
		break;
	case PLAYERSTATE_RIGHT_BRAKE:
		if (_player.img->getFrameX() >= _player.img->getMaxFrameX())
		{
			_player.state = PLAYERSTATE_RIGHT_IDLE;
		}
		break;
	case PLAYERSTATE_LEFT_RUN: case PLAYERSTATE_RIGHT_RUN:
		if (_player.img->getFrameX() >= _player.img->getMaxFrameX())
		{
			_player.img->setFrameX(2);
		}
		break;
	case PLAYERSTATE_LEFT_TURN: case PLAYERSTATE_RIGHT_TURN:
		if (_player.img->getFrameX() >= _player.img->getMaxFrameX())
		{
			if (_player.state == PLAYERSTATE_LEFT_TURN) _player.state = PLAYERSTATE_LEFT_RUN;
			if (_player.state == PLAYERSTATE_RIGHT_TURN) _player.state = PLAYERSTATE_RIGHT_RUN;
		}
		break;
	case PLAYERSTATE_LEFT_CROUCH: case PLAYERSTATE_RIGHT_CROUCH:
		if (_player.img->getFrameX() >= _player.img->getMaxFrameX())
		{
			_player.img->setFrameX(_player.img->getMaxFrameX());
		}
		break;
	case PLAYERSTATE_LEFT_RISE: case PLAYERSTATE_RIGHT_RISE:
		if (_player.img->getFrameX() >= _player.img->getMaxFrameX())
		{
			if (_player.state == PLAYERSTATE_LEFT_RISE) _player.state = PLAYERSTATE_LEFT_IDLE;
			if (_player.state == PLAYERSTATE_RIGHT_RISE) _player.state = PLAYERSTATE_RIGHT_IDLE;
		}
		break;
	case PLAYERSTATE_LEFT_ATTACK1: case PLAYERSTATE_RIGHT_ATTACK1:
		if (_player.img->getFrameX() >= _player.img->getMaxFrameX())
		{
			if (_player.state == PLAYERSTATE_LEFT_ATTACK1) _player.state = PLAYERSTATE_LEFT_IDLE;
			if (_player.state == PLAYERSTATE_RIGHT_ATTACK1) _player.state = PLAYERSTATE_RIGHT_IDLE;
		}
		break;
	case PLAYERSTATE_LEFT_ATTACK2: case PLAYERSTATE_RIGHT_ATTACK2:
		if (_player.img->getFrameX() >= _player.img->getMaxFrameX())
		{
			if (_player.state == PLAYERSTATE_LEFT_ATTACK2) _player.state = PLAYERSTATE_LEFT_IDLE;
			if (_player.state == PLAYERSTATE_RIGHT_ATTACK2) _player.state = PLAYERSTATE_RIGHT_IDLE;
		}
		break;
	case PLAYERSTATE_LEFT_ATTACK3: case PLAYERSTATE_RIGHT_ATTACK3:
		if (_player.img->getFrameX() >= _player.img->getMaxFrameX())
		{
			if (_player.state == PLAYERSTATE_LEFT_ATTACK3) _player.state = PLAYERSTATE_LEFT_IDLE;
			if (_player.state == PLAYERSTATE_RIGHT_ATTACK3) _player.state = PLAYERSTATE_RIGHT_IDLE;
		}
		break;
	case PLAYERSTATE_LEFT_ROLL: case PLAYERSTATE_RIGHT_ROLL:
		if (_player.img->getFrameX() >= _player.img->getMaxFrameX())
		{
			if (_player.state == PLAYERSTATE_LEFT_ROLL) _player.state = PLAYERSTATE_LEFT_IDLE;
			if (_player.state == PLAYERSTATE_RIGHT_ROLL) _player.state = PLAYERSTATE_RIGHT_IDLE;
		}
		break;
	case PLAYERSTATE_FALL:
		break;
		_player.fps = 0;
	}
}

void player::inputKey()
{
	if (KEYMANAGER->isOnceKeyDown('H')) this->init();
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		if (!_player.isJump)
		{
			if (_player.state == PLAYERSTATE_LEFT_RUN)
			{
				_player.state = PLAYERSTATE_RIGHT_TURN;
				_player.imgName = "턴";
				imageSet(_player.imgName, true);
			}
			else
			{
				_player.imgName = "달리기";
				imageSet(_player.imgName, true);
			}
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && !_player.isJump && (_player.state != PLAYERSTATE_LEFT_ATTACK1 && _player.state != PLAYERSTATE_LEFT_ATTACK2 && 
		_player.state != PLAYERSTATE_LEFT_ATTACK3 && _player.state != PLAYERSTATE_RIGHT_ATTACK1 &&_player.state != PLAYERSTATE_RIGHT_ATTACK2 &&
		_player.state != PLAYERSTATE_RIGHT_ATTACK3))
	{
		_player.state = PLAYERSTATE_RIGHT_RUN;
		_player.speed += 0.05f;
		if (_player.speed >= MAXSPEED) _player.speed = MAXSPEED;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		if (!_player.isJump)
		{
			if (_player.state == PLAYERSTATE_RIGHT_RUN)
			{
				_player.state = PLAYERSTATE_LEFT_TURN;
				_player.imgName = "턴";
				imageSet(_player.imgName, false);
			}
			else
			{
				_player.imgName = "달리기";
				imageSet(_player.imgName, false);
			}
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && !_player.isJump && (_player.state != PLAYERSTATE_LEFT_ATTACK1 && _player.state != PLAYERSTATE_LEFT_ATTACK2 && _player.state != PLAYERSTATE_LEFT_ATTACK3 &&
		_player.state != PLAYERSTATE_RIGHT_ATTACK1 &&_player.state != PLAYERSTATE_RIGHT_ATTACK2 &&_player.state != PLAYERSTATE_RIGHT_ATTACK3))
	{
		_player.state = PLAYERSTATE_LEFT_RUN;
		_player.speed += 0.1f;
		if (_player.speed >= MAXSPEED) _player.speed = MAXSPEED;
	}

	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT) && _player.state != PLAYERSTATE_LEFT_TURN)
	{
		_player.speed = MINSPEED;
		if (_player.state == PLAYERSTATE_RIGHT_RUN && (_player.state != PLAYERSTATE_RIGHT_TURN && _player.state != PLAYERSTATE_RIGHT_ROLL))
		{
			_player.state = PLAYERSTATE_RIGHT_BRAKE;
			_player.imgName = "브레이크";
			imageSet(_player.imgName, true);
			_player.img->setFrameY(0);
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_player.speed = MINSPEED;
		if (_player.state == PLAYERSTATE_LEFT_RUN && (_player.state != PLAYERSTATE_RIGHT_TURN && _player.state != PLAYERSTATE_RIGHT_ROLL))
		{
			_player.state = PLAYERSTATE_LEFT_BRAKE;
			_player.imgName = "브레이크";
			imageSet(_player.imgName, false);
			_player.img->setFrameY(1);
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && !_player.isJump2)
	{
		_player.isJump = true;
		_player.jumpPower = JUMPPOWER;
		_player.gravity = GRAVITY;
		if (_player.state == PLAYERSTATE_LEFT_IDLE || _player.state == PLAYERSTATE_LEFT_BRAKE || _player.state == PLAYERSTATE_LEFT_RUN)
		{
			imageSet("점프", false);
		}
		else if (_player.state == PLAYERSTATE_RIGHT_IDLE || _player.state == PLAYERSTATE_RIGHT_BRAKE || _player.state == PLAYERSTATE_RIGHT_RUN)
		{
			imageSet("점프", true);
		}
		_player.state = PLAYERSTATE_JUMP;
	}
	if (_player.state == PLAYERSTATE_LEFT_CROUCH || _player.state == PLAYERSTATE_RIGHT_CROUCH)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_player.isJump = true;
			_player.gravity = GRAVITY;
			if (_player.state == PLAYERSTATE_LEFT_CROUCH)
			{
				imageSet("폴", false);
			}
			if (_player.state == PLAYERSTATE_RIGHT_CROUCH)
			{
				imageSet("폴", true);
			}
			_player.state = PLAYERSTATE_DOWN_JUMP;
		}
	}

	if (_player.state == PLAYERSTATE_JUMP)
	{
		if (_player.jumpPower < 0)
		{
			_player.state = PLAYERSTATE_FALL;
			if (_player.img->getFrameY() == 1)
			{
				imageSet("폴", false);
			}
			else if (_player.img->getFrameY() == 0)
			{
				imageSet("폴", true);
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_player.state = PLAYERSTATE_JUMP;
			imageSet("점프", true);
			_player.isJump2 = true;
		}
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_player.x -= MAXSPEED;
			imageSet("점프", false);
			_player.img->setFrameX(_player.img->getMaxFrameX() - 1);
		}
		else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_player.x += MAXSPEED;
			imageSet("점프", true);
			_player.img->setFrameX(_player.img->getMaxFrameX() - 1);
		}
	}
	if (_player.state == PLAYERSTATE_FALL)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_player.x -= MAXSPEED;
			imageSet("폴", false);
		}
		else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_player.x += MAXSPEED;
			imageSet("폴", true);
		}
	}

	//앉기
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		if (_player.state == PLAYERSTATE_LEFT_IDLE || _player.state == PLAYERSTATE_LEFT_BRAKE)
		{
			_player.state = PLAYERSTATE_LEFT_CROUCH;
			imageSet("앉기", false);
		}
		else if (_player.state == PLAYERSTATE_RIGHT_IDLE || _player.state == PLAYERSTATE_RIGHT_BRAKE)
		{
			_player.state = PLAYERSTATE_RIGHT_CROUCH;
			imageSet("앉기", true);
		}
	}

	//일어서기
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		if (_player.state == PLAYERSTATE_LEFT_CROUCH)
		{
			_player.state = PLAYERSTATE_LEFT_RISE;
			imageSet("일어서기", false);
		}
		else if (_player.state == PLAYERSTATE_RIGHT_CROUCH)
		{
			_player.state = PLAYERSTATE_RIGHT_RISE;
			imageSet("일어서기", true);
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LSHIFT))
	{
		if (_player.state == PLAYERSTATE_LEFT_IDLE || _player.state == PLAYERSTATE_LEFT_BRAKE || _player.state == PLAYERSTATE_LEFT_RUN)
		{
			_player.state = PLAYERSTATE_LEFT_ROLL;
			imageSet("구르기", false);
		}
		else if (_player.state == PLAYERSTATE_RIGHT_IDLE || _player.state == PLAYERSTATE_RIGHT_BRAKE || _player.state == PLAYERSTATE_RIGHT_RUN)
		{
			_player.state = PLAYERSTATE_RIGHT_ROLL;
			imageSet("구르기", true);
		}
	}

	//근접 공격키
	if (KEYMANAGER->isOnceKeyDown(VK_LCONTROL))
	{
		if (_player.state == PLAYERSTATE_LEFT_IDLE || _player.state == PLAYERSTATE_LEFT_RUN || _player.state == PLAYERSTATE_LEFT_BRAKE)
		{
			_player.state = PLAYERSTATE_LEFT_ATTACK1;
			if (_player.imgName == "공격1") return;
			imageSet("공격1", false);
		}
		else if (_player.state == PLAYERSTATE_RIGHT_IDLE || _player.state == PLAYERSTATE_RIGHT_RUN || _player.state == PLAYERSTATE_RIGHT_BRAKE)
		{
			_player.state = PLAYERSTATE_RIGHT_ATTACK1;
			if (_player.imgName == "공격1") return;
			imageSet("공격1", true);
		}
		else if (_player.state == PLAYERSTATE_LEFT_ATTACK1 && _player.img->getFrameX() == _player.img->getMaxFrameX() - 1)
		{
			_player.state = PLAYERSTATE_LEFT_ATTACK2;
			if (_player.imgName == "공격2") return;
			imageSet("공격2", false);
		}
		else if (_player.state == PLAYERSTATE_RIGHT_ATTACK1 && _player.img->getFrameX() == _player.img->getMaxFrameX() - 1)
		{
			_player.state = PLAYERSTATE_RIGHT_ATTACK2;
			if (_player.imgName == "공격2") return;
			imageSet("공격2", true);
		}
		else if (_player.state == PLAYERSTATE_LEFT_ATTACK2 && _player.img->getFrameX() == _player.img->getMaxFrameX() - 1)
		{
			_player.state = PLAYERSTATE_LEFT_ATTACK3;
			if (_player.imgName == "공격3") return;
			imageSet("공격3", false);
		}
		else if (_player.state == PLAYERSTATE_RIGHT_ATTACK2 && _player.img->getFrameX() == _player.img->getMaxFrameX() - 1)
		{
			_player.state = PLAYERSTATE_RIGHT_ATTACK3;
			if (_player.imgName == "공격3") return;
			imageSet("공격3", true);
		}
	}
}



void player::move()
{
	switch (_player.state)
	{
	case PLAYERSTATE_LEFT_IDLE:
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
		_player.imgName = "정지";
		_player.img = IMAGEMANAGER->findImage(_player.imgName);
		_player.img->setFrameY(1);
		break;
	case PLAYERSTATE_RIGHT_IDLE:
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
		_player.imgName = "정지";
		_player.img = IMAGEMANAGER->findImage(_player.imgName);
		_player.img->setFrameY(0);
		break;
	case PLAYERSTATE_LEFT_RUN:
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
		_player.x -= _player.speed;
		break;
	case PLAYERSTATE_RIGHT_RUN:
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
		_player.x += _player.speed;
		break;
	case PLAYERSTATE_LEFT_BRAKE:
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
		_player.x -= _player.speed / 5;
		break;
	case PLAYERSTATE_RIGHT_BRAKE:
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
		_player.x += _player.speed / 5;
		break;
	case PLAYERSTATE_JUMP:
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
		_player.y -= _player.jumpPower;
		_player.jumpPower -= _player.gravity;
		break;
	case PLAYERSTATE_DOWN_JUMP:
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
		_player.y -= _player.gravity;
		break;
	case PLAYERSTATE_LEFT_ROLL:
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
		_player.x -= MAXSPEED * 2;
		break;
	case PLAYERSTATE_RIGHT_ROLL:
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
		_player.x += MAXSPEED * 2;
		break;
	case PLAYERSTATE_FALL:
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
		if (_player.isJump) _player.y -= _player.jumpPower;
		break;
	case PLAYERSTATE_LEFT_CROUCH: case PLAYERSTATE_RIGHT_CROUCH:
		_player.rc = RectMakeCenter(_player.x, _player.y + 14, _player.img->getFrameWidth(), _player.img->getFrameHeight());
		break;
	case PLAYERSTATE_LEFT_RISE: case PLAYERSTATE_RIGHT_RISE:
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
		break;
	case PLAYERSTATE_LEFT_ATTACK1:
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
		_player.x -= _player.speed / 5;
		break;
	case PLAYERSTATE_LEFT_ATTACK2:
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
		_player.x -= _player.speed / 5;
		break;
	case PLAYERSTATE_LEFT_ATTACK3:
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
		_player.x -= _player.speed / 2.5f;
		break;
	case PLAYERSTATE_RIGHT_ATTACK1:
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
		_player.x += _player.speed / 5;
		break;
	case PLAYERSTATE_RIGHT_ATTACK2:
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
		_player.x += _player.speed / 5;
		break;
	case PLAYERSTATE_RIGHT_ATTACK3:
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
		_player.x += _player.speed / 2.5f;
		break;
	
	}
}

void player::imageSet(char* imgName, bool direction)
{
	_player.fps = 0;
	_player.imgName = imgName;
	_player.img = IMAGEMANAGER->findImage(imgName);
	_player.img->setFrameX(0);
	if (direction) _player.img->setFrameY(0);
	else if (!direction) _player.img->setFrameY(1);
}

void player::pixelCollision()
{
	switch (_player.state)
	{
	case PLAYERSTATE_JUMP:
		break;
	case PLAYERSTATE_FALL:
		if (PIXELMANAGER->isPixelCollisionBottomY(_player.img, _player.x, _player.y, IMAGEMANAGER->findImage("맵1-1픽셀")))
		{
			_player.isJump = false;
			_player.isJump2 = false;
			if (_player.img->getFrameY() == 0)
			{
				imageSet("정지", false);
				_player.state = PLAYERSTATE_RIGHT_IDLE;
			}
			else if (_player.img->getFrameY() == 1)
			{
				imageSet("정지", true);
				_player.state = PLAYERSTATE_LEFT_IDLE;
			}
		}
		break;
	case PLAYERSTATE_RIGHT_IDLE: case PLAYERSTATE_LEFT_IDLE: case PLAYERSTATE_LEFT_RUN: case PLAYERSTATE_RIGHT_RUN:
		_player.y = PIXELMANAGER->getPixelCollisionY(_player.img, _player.x, _player.y, IMAGEMANAGER->findImage("맵1-1픽셀"));
		break;
	}
}
