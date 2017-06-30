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
	_player.imgName = "����";
	_player.img = IMAGEMANAGER->findImage(_player.imgName);
	_player.x = 200;
	_player.y = 600;
	_player.speed = 1.5f;
	_player.fps = 0;
	_player.jumpPower = JUMPPOWER;
	_player.gravity = GRAVITY;
	_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
	_player.state = PLAYERSTATE_RIGHT_IDLE;
	_player.isAirAttack = _player.isJump = _player.isJump2 = false;


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
	if (_player.isJump)
	{
		_player.jumpPower -= GRAVITY;
	}

}

void player::render(float x, float y) 
{
	//Rectangle(getMemDC(), _player.rc.left, _player.rc.top, _player.rc.right, _player.rc.bottom);
	_player.img->frameRender(getMemDC(), _player.rc.left - x, _player.rc.top - y);
	if (_player.imgName == "����")
	{
		if (_player.fps % 8 == 0)
		{
			_player.img->setFrameX(_player.img->getFrameX() + 1);
		}
	}
	else if (_player.imgName == "����Ȱ")
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
	case PLAYERSTATE_LEFT_BOW: case PLAYERSTATE_RIGHT_BOW:
		if (_player.img->getFrameX() >= _player.img->getMaxFrameX())
		{
			if (_player.state == PLAYERSTATE_LEFT_BOW) _player.state = PLAYERSTATE_LEFT_IDLE;
			if (_player.state == PLAYERSTATE_RIGHT_BOW) _player.state = PLAYERSTATE_RIGHT_IDLE;
		}
		break;
	case PLAYERSTATE_LEFT_JUMPBOW: case PLAYERSTATE_RIGHT_JUMPBOW:
		if (_player.img->getFrameX() >= _player.img->getMaxFrameX())
		{
			if (_player.state == PLAYERSTATE_LEFT_JUMPBOW) _player.state = PLAYERSTATE_LEFT_IDLE;
			if (_player.state == PLAYERSTATE_RIGHT_JUMPBOW) _player.state = PLAYERSTATE_RIGHT_IDLE;
		}
		break;
	case PLAYERSTATE_LEFT_CROUCHBOW: case PLAYERSTATE_RIGHT_CROUCHBOW:
		if (_player.img->getFrameX() >= _player.img->getMaxFrameX())
		{
			if (_player.state == PLAYERSTATE_LEFT_CROUCHBOW) _player.state = PLAYERSTATE_LEFT_IDLE;
			if (_player.state == PLAYERSTATE_RIGHT_CROUCHBOW) _player.state = PLAYERSTATE_RIGHT_IDLE;
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
				_player.imgName = "��";
				imageSet(_player.imgName, true);
			}
			else
			{
				_player.imgName = "�޸���";
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
				_player.imgName = "��";
				imageSet(_player.imgName, false);
			}
			else
			{
				_player.imgName = "�޸���";
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
			_player.imgName = "�극��ũ";
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
			_player.imgName = "�극��ũ";
			imageSet(_player.imgName, false);
			_player.img->setFrameY(1);
		}
	}



	//����
	if (KEYMANAGER->isOnceKeyDown('A') && !_player.isJump2)
	{
		_player.isAirAttack = false;
		if (_player.state == PLAYERSTATE_LEFT_IDLE || _player.state == PLAYERSTATE_LEFT_BRAKE || _player.state == PLAYERSTATE_LEFT_RUN)
		{
			imageSet("����", false);
		}
		else if (_player.state == PLAYERSTATE_RIGHT_IDLE || _player.state == PLAYERSTATE_RIGHT_BRAKE || _player.state == PLAYERSTATE_RIGHT_RUN)
		{
			imageSet("����", true);
		}
		else if (_player.state == PLAYERSTATE_JUMP)
		{
			_player.isJump2 = true;
			_player.jumpPower = JUMPPOWER;
			_player.gravity = GRAVITY;
		}
		else return;
		_player.state = PLAYERSTATE_JUMP;
		_player.isJump = true;
		_player.jumpPower = JUMPPOWER;
		_player.gravity = GRAVITY;
	}

	//�ɱ�
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		if (_player.state == PLAYERSTATE_LEFT_IDLE || _player.state == PLAYERSTATE_LEFT_BRAKE)
		{
			_player.state = PLAYERSTATE_LEFT_CROUCH;
			imageSet("�ɱ�", false);
		}
		else if (_player.state == PLAYERSTATE_RIGHT_IDLE || _player.state == PLAYERSTATE_RIGHT_BRAKE)
		{
			_player.state = PLAYERSTATE_RIGHT_CROUCH;
			imageSet("�ɱ�", true);
		}
	}

	//�Ͼ��
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		if (_player.state == PLAYERSTATE_LEFT_CROUCH)
		{
			_player.state = PLAYERSTATE_LEFT_RISE;
			imageSet("�Ͼ��", false);
		}
		else if (_player.state == PLAYERSTATE_RIGHT_CROUCH)
		{
			_player.state = PLAYERSTATE_RIGHT_RISE;
			imageSet("�Ͼ��", true);
		}
	}

	//������
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		if (_player.state == PLAYERSTATE_LEFT_IDLE || _player.state == PLAYERSTATE_LEFT_BRAKE || _player.state == PLAYERSTATE_LEFT_RUN)
		{
			_player.state = PLAYERSTATE_LEFT_ROLL;
			imageSet("������", false);
		}
		else if (_player.state == PLAYERSTATE_RIGHT_IDLE || _player.state == PLAYERSTATE_RIGHT_BRAKE || _player.state == PLAYERSTATE_RIGHT_RUN)
		{
			_player.state = PLAYERSTATE_RIGHT_ROLL;
			imageSet("������", true);
		}
	}

	//���� ����Ű
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		if (_player.state == PLAYERSTATE_LEFT_IDLE || _player.state == PLAYERSTATE_LEFT_RUN || _player.state == PLAYERSTATE_LEFT_BRAKE)
		{
			_player.state = PLAYERSTATE_LEFT_ATTACK1;
			if (_player.imgName == "����1") return;
			imageSet("����1", false);
		}
		else if (_player.state == PLAYERSTATE_RIGHT_IDLE || _player.state == PLAYERSTATE_RIGHT_RUN || _player.state == PLAYERSTATE_RIGHT_BRAKE)
		{
			_player.state = PLAYERSTATE_RIGHT_ATTACK1;
			if (_player.imgName == "����1") return;
			imageSet("����1", true);
		}
		else if (_player.state == PLAYERSTATE_LEFT_ATTACK1 && _player.img->getFrameX() == _player.img->getMaxFrameX() - 1)
		{
			_player.state = PLAYERSTATE_LEFT_ATTACK2;
			if (_player.imgName == "����2") return;
			imageSet("����2", false);
		}
		else if (_player.state == PLAYERSTATE_RIGHT_ATTACK1 && _player.img->getFrameX() == _player.img->getMaxFrameX() - 1)
		{
			_player.state = PLAYERSTATE_RIGHT_ATTACK2;
			if (_player.imgName == "����2") return;
			imageSet("����2", true);
		}
		else if (_player.state == PLAYERSTATE_LEFT_ATTACK2 && _player.img->getFrameX() == _player.img->getMaxFrameX() - 1)
		{
			_player.state = PLAYERSTATE_LEFT_ATTACK3;
			if (_player.imgName == "����3") return;
			imageSet("����3", false);
		}
		else if (_player.state == PLAYERSTATE_RIGHT_ATTACK2 && _player.img->getFrameX() == _player.img->getMaxFrameX() - 1)
		{
			_player.state = PLAYERSTATE_RIGHT_ATTACK3;
			if (_player.imgName == "����3") return;
			imageSet("����3", true);
		}
		else if ((_player.isJump || _player.isJump2) && !_player.isAirAttack)
		{
			_player.isAirAttack = true;
			if (_player.img->getFrameY() == 0) imageSet("��������", true);
			if (_player.img->getFrameY() == 1) imageSet("��������", false);
		}
	}

	//Ȱ ����
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		if (_player.state == PLAYERSTATE_LEFT_IDLE || _player.state == PLAYERSTATE_LEFT_RUN || _player.state == PLAYERSTATE_LEFT_BRAKE)
		{
			_player.state = PLAYERSTATE_LEFT_BOW;
			imageSet("����Ȱ", false);
		}
		else if (_player.state == PLAYERSTATE_RIGHT_IDLE || _player.state == PLAYERSTATE_RIGHT_RUN || _player.state == PLAYERSTATE_RIGHT_BRAKE)
		{
			_player.state = PLAYERSTATE_RIGHT_BOW;
			imageSet("����Ȱ", true);
		}
		else if (_player.state == PLAYERSTATE_LEFT_CROUCH)
		{
			_player.state = PLAYERSTATE_LEFT_CROUCHBOW;
			imageSet("�ɱ�Ȱ", false);
		}
		else if (_player.state == PLAYERSTATE_RIGHT_CROUCH)
		{
			_player.state = PLAYERSTATE_RIGHT_CROUCHBOW;
			imageSet("�ɱ�Ȱ", true);
		}
		else if ((_player.state == PLAYERSTATE_JUMP || _player.state == PLAYERSTATE_FALL) && !_player.isAirAttack)
		{
			_player.isAirAttack = true;
			if (_player.img->getFrameY() == 0)
			{
				imageSet("����Ȱ", true);
			}
			else if (_player.img->getFrameY() == 1)
			{
				imageSet("����Ȱ", false);
			}
		}
	}
}



void player::move()
{
	switch (_player.state)
	{
	case PLAYERSTATE_LEFT_IDLE:
		_player.isJump = false;
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
		_player.imgName = "����";
		_player.img = IMAGEMANAGER->findImage(_player.imgName);
		_player.img->setFrameY(1);
		break;
	case PLAYERSTATE_RIGHT_IDLE:
		_player.isJump = false;
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
		_player.imgName = "����";
		_player.img = IMAGEMANAGER->findImage(_player.imgName);
		_player.img->setFrameY(0);
		break;
	case PLAYERSTATE_LEFT_RUN:
		if (!PIXELMANAGER->isPixelCollisionLeftX(_player.img, _player.x, _player.y, IMAGEMANAGER->findImage("��1-1�ȼ�")))
		{
			_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
			_player.x -= _player.speed;
		}
		break;
	case PLAYERSTATE_RIGHT_RUN:
		if (!PIXELMANAGER->isPixelCollisionRightX(_player.img, _player.x, _player.y, IMAGEMANAGER->findImage("��1-1�ȼ�")))
		{
			_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
			_player.x += _player.speed;
		}
		break;
	case PLAYERSTATE_LEFT_BRAKE:
		if (!PIXELMANAGER->isPixelCollisionLeftX(_player.img, _player.x, _player.y, IMAGEMANAGER->findImage("��1-1�ȼ�")))
		{
			_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
			_player.x -= _player.speed / 5;
		}
		break;
	case PLAYERSTATE_RIGHT_BRAKE:
		if (!PIXELMANAGER->isPixelCollisionRightX(_player.img, _player.x, _player.y, IMAGEMANAGER->findImage("��1-1�ȼ�")))
		{
			_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
			_player.x += _player.speed / 5;
		}
		break;
	case PLAYERSTATE_JUMP:
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
		_player.y -= _player.jumpPower;
		_player.jumpPower -= _player.gravity;
		if (KEYMANAGER->isStayKeyDown(VK_LEFT) && !PIXELMANAGER->isPixelCollisionLeftX(_player.img, _player.x, _player.y, IMAGEMANAGER->findImage("��1-1�ȼ�")))
		{
			_player.x -= MAXSPEED;
			//imageSet("����", false);
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && !PIXELMANAGER->isPixelCollisionRightX(_player.img, _player.x, _player.y, IMAGEMANAGER->findImage("��1-1�ȼ�")))
		{
			_player.x += MAXSPEED;
			//imageSet("����", true);
		}
		if (_player.jumpPower < 0 && _player.imgName != "��������" && _player.imgName != "����Ȱ" && _player.imgName != "�ɱ�Ȱ")
		{
			_player.state = PLAYERSTATE_FALL;
			if (_player.img->getFrameY() == 1)
			{
				imageSet("��", false);
			}
			else if (_player.img->getFrameY() == 0)
			{
				imageSet("��", true);
			}
		}
		if ((_player.imgName == "��������" || _player.imgName == "����Ȱ" || _player.imgName == "�ɱ�Ȱ") && _player.img->getFrameX() == _player.img->getMaxFrameX())
		{
			_player.state = PLAYERSTATE_FALL;
			if (_player.img->getFrameY() == 1)
			{
				imageSet("��", false);
			}
			else if (_player.img->getFrameY() == 0)
			{
				imageSet("��", true);
			}
		}
		else return;
		break;
	case PLAYERSTATE_DOWN_JUMP:
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
		_player.y -= _player.gravity;
		break;
	case PLAYERSTATE_LEFT_ROLL:
		if (!PIXELMANAGER->isPixelCollisionLeftX(_player.img, _player.x, _player.y, IMAGEMANAGER->findImage("��1-1�ȼ�")))
		{
			_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
			_player.x -= ROLLSPEED;
		}
		break;
	case PLAYERSTATE_RIGHT_ROLL:
		if (!PIXELMANAGER->isPixelCollisionRightX(_player.img, _player.x, _player.y, IMAGEMANAGER->findImage("��1-1�ȼ�")))
		{
			_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
			_player.x += ROLLSPEED;
		}
		break;
	case PLAYERSTATE_FALL:
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
		if (_player.isJump) _player.y -= _player.jumpPower;
		if (KEYMANAGER->isStayKeyDown(VK_LEFT) && !PIXELMANAGER->isPixelCollisionLeftX(_player.img, _player.x, _player.y, IMAGEMANAGER->findImage("��1-1�ȼ�")))
		{
			_player.x -= MAXSPEED;
			imageSet("��", false);
		}
		else if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && !PIXELMANAGER->isPixelCollisionRightX(_player.img, _player.x, _player.y, IMAGEMANAGER->findImage("��1-1�ȼ�")))
		{
			_player.x += MAXSPEED;
			imageSet("��", true);
		}
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
	case PLAYERSTATE_LEFT_BOW: case PLAYERSTATE_RIGHT_BOW:
		_player.rc = RectMakeCenter(_player.x, _player.y - 13, _player.img->getFrameWidth(), _player.img->getFrameHeight());
		break;
	case PLAYERSTATE_LEFT_JUMPBOW: case PLAYERSTATE_RIGHT_JUMPBOW:
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
		break;
	case PLAYERSTATE_LEFT_CROUCHBOW: case PLAYERSTATE_RIGHT_CROUCHBOW:
		_player.rc = RectMakeCenter(_player.x, _player.y + 14, _player.img->getFrameWidth(), _player.img->getFrameHeight());
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
		if (PIXELMANAGER->isPixelCollisionTopY(_player.img, _player.x, _player.y, IMAGEMANAGER->findImage("��1-1�ȼ�")))
		{
			_player.state = PLAYERSTATE_FALL;
			_player.jumpPower = 0;
			if (_player.img->getFrameY() == 0) imageSet("��", true);
			if (_player.img->getFrameY() == 1) imageSet("��", false);
		}
		break;
	case PLAYERSTATE_FALL:
		if (PIXELMANAGER->isPixelCollisionBottomY(_player.img, _player.x, _player.y, IMAGEMANAGER->findImage("��1-1�ȼ�")))
		{
			_player.isJump = false;
			_player.isJump2 = false;
			if (_player.img->getFrameY() == 0)
			{
				imageSet("����", false);
				_player.state = PLAYERSTATE_RIGHT_IDLE;
			}
			else if (_player.img->getFrameY() == 1)
			{
				imageSet("����", true);
				_player.state = PLAYERSTATE_LEFT_IDLE;
			}
		}
		break;
	case PLAYERSTATE_RIGHT_IDLE: case PLAYERSTATE_LEFT_IDLE: case PLAYERSTATE_LEFT_RUN: case PLAYERSTATE_RIGHT_RUN:
	case PLAYERSTATE_RIGHT_ROLL: case PLAYERSTATE_LEFT_ROLL: case PLAYERSTATE_LEFT_ATTACK1: case PLAYERSTATE_LEFT_ATTACK2:
	case PLAYERSTATE_LEFT_ATTACK3: case PLAYERSTATE_RIGHT_ATTACK1: case PLAYERSTATE_RIGHT_ATTACK2:
	case PLAYERSTATE_RIGHT_ATTACK3:
		_player.y = PIXELMANAGER->getPixelCollisionY(_player.img, _player.x, _player.y, IMAGEMANAGER->findImage("��1-1�ȼ�"));
		break;
	case PLAYERSTATE_DOWN_JUMP:
		if (PIXELMANAGER->isDownJump(_player.img, _player.x, _player.y, IMAGEMANAGER->findImage("��1-1�ȼ�")))
		{
			_player.jumpPower = 0;
			if (_player.img->getFrameY() == 0) imageSet("��", true);
			if (_player.img->getFrameY() == 1) imageSet("��", false);
		}
	}
}
