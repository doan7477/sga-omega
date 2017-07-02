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
	_player.arrow = new arrow;
	_player.arrow->init("ȭ��");
	_player.x = 200;
	_player.y = 600;
	_player.speed = 1.5f;
	_player.fps = 0;
	_player.key = 0;
	_player.jumpPower = JUMPPOWER;
	_player.gravity = GRAVITY;
	_player.isRight = true;
	_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
	_player.state = PLAYERSTATE_RIGHT_IDLE;
	_player.isAirAttack = _player.isJump = _player.isJump2 = _player.isLadder = false;
	_player.isGround = true;

	EFFECTMANAGER->addEffect("����1����", "����1����Ʈ����", IMAGEMANAGER->findImage("����1����Ʈ����")->getWidth(), IMAGEMANAGER->findImage("����1����Ʈ����")->getHeight(),
		IMAGEMANAGER->findImage("����1����Ʈ����")->getFrameWidth(), IMAGEMANAGER->findImage("����1����Ʈ����")->getFrameHeight(), 3, 0.1f, 1);

	EFFECTMANAGER->addEffect("����1������", "����1����Ʈ������", IMAGEMANAGER->findImage("����1����Ʈ������")->getWidth(), IMAGEMANAGER->findImage("����1����Ʈ������")->getHeight(),
		IMAGEMANAGER->findImage("����1����Ʈ������")->getFrameWidth(), IMAGEMANAGER->findImage("����1����Ʈ������")->getFrameHeight(), 3, 0.1f, 1);

	EFFECTMANAGER->addEffect("����2����", "����2����Ʈ����", IMAGEMANAGER->findImage("����2����Ʈ����")->getWidth(), IMAGEMANAGER->findImage("����2����Ʈ����")->getHeight(),
		IMAGEMANAGER->findImage("����2����Ʈ����")->getFrameWidth(), IMAGEMANAGER->findImage("����2����Ʈ����")->getFrameHeight(), 3, 0.1f, 1);
	
	EFFECTMANAGER->addEffect("����2������", "����2����Ʈ������", IMAGEMANAGER->findImage("����2����Ʈ������")->getWidth(), IMAGEMANAGER->findImage("����2����Ʈ������")->getHeight(),
		IMAGEMANAGER->findImage("����2����Ʈ������")->getFrameWidth(), IMAGEMANAGER->findImage("����2����Ʈ������")->getFrameHeight(), 3, 0.1f, 1);
	
	EFFECTMANAGER->addEffect("����3����", "����3����Ʈ����", IMAGEMANAGER->findImage("����3����Ʈ����")->getWidth(), IMAGEMANAGER->findImage("����3����Ʈ����")->getHeight(),
		IMAGEMANAGER->findImage("����3����Ʈ����")->getFrameWidth(), IMAGEMANAGER->findImage("����3����Ʈ����")->getFrameHeight(), 3, 0.1f, 1);
	
	EFFECTMANAGER->addEffect("����3������", "����3����Ʈ������", IMAGEMANAGER->findImage("����3����Ʈ������")->getWidth(), IMAGEMANAGER->findImage("����3����Ʈ������")->getHeight(),
		IMAGEMANAGER->findImage("����3����Ʈ������")->getFrameWidth(), IMAGEMANAGER->findImage("����3����Ʈ������")->getFrameHeight(), 3, 0.1f, 1);

	return S_OK;
}

void player::release()
{

}

void player::update()
{
	EFFECTMANAGER->update();
	_player.fps++;
	_player.arrow->update();
	inputKey();
	move();
	pixelCollision();
	if (_player.isJump || !_player.isGround)
	{
		_player.jumpPower -= GRAVITY;
		if (_player.jumpPower < -6.0f) _player.jumpPower = -6.0f;
		_player.y += GRAVITY * 20;
	}
}

void player::render(float x, float y)
{
	EFFECTMANAGER->render(x, y);
	_player.arrow->render(x, y);
	//Rectangle(getMemDC(), _player.rc.left, _player.rc.top, _player.rc.right, _player.rc.bottom);
	_player.img->frameRender(getMemDC(), _player.rc.left - x, _player.rc.top - y);
	if (_player.imgName == "����" || _player.imgName == "��ٸ�����")
	{
		if (_player.fps % 8 == 0)
		{
			_player.img->setFrameX(_player.img->getFrameX() + 1);
		}
	}
	else if (_player.imgName == "����Ȱ" || _player.imgName == "����Ȱ" || _player.imgName == "����Ȱ")
	{
		if (_player.fps % 4 == 0)
		{
			_player.img->setFrameX(_player.img->getFrameX() + 1);
		}
	}
	else if (_player.imgName != "��ٸ��ö󰡱�")
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
	case PLAYERSTATE_JUMP_ATTACK:
		if (_player.img->getFrameX() >= _player.img->getMaxFrameX())
		{
			_player.state = PLAYERSTATE_FALL;
			if (_player.img->getFrameY() == 0)imageSet("��", false);
			if (_player.img->getFrameY() == 1)imageSet("��", true);
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
	case PLAYERSTATE_LEFT_LADDER_ENTER: case PLAYERSTATE_RIGHT_LADDER_ENTER:
		break;
	case PLAYERSTATE_LADDER_UP:
		break;
	case PLAYERSTATE_LADDER_DOWN:
		break;
	case PLAYERSTATE_LEFT_LADDER_LEAVE: case PLAYERSTATE_RIGHT_LADDER_LEAVE:
		break;
		_player.fps = 0;
	}
}

void player::inputKey()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{	
		_player.imgName = "�޸���";
		imageSet(_player.imgName, true);
	}

	//������ �޸���
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (!_player.isJump && _player.state != PLAYERSTATE_LEFT_ATTACK1 && _player.state != PLAYERSTATE_LEFT_ATTACK2 &&
			_player.state != PLAYERSTATE_LEFT_ATTACK3 && _player.state != PLAYERSTATE_RIGHT_ATTACK1 &&_player.state != PLAYERSTATE_RIGHT_ATTACK2 &&
			_player.state != PLAYERSTATE_RIGHT_ATTACK3 && _player.state != PLAYERSTATE_RIGHT_ROLL)
		{
			_player.key = 3;
			_player.state = PLAYERSTATE_RIGHT_RUN;
			_player.speed += 0.1f;
			if (_player.speed >= MAXSPEED) _player.speed = MAXSPEED;
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_player.key = 0;
		if (_player.state == PLAYERSTATE_RIGHT_RUN && _player.state != PLAYERSTATE_RIGHT_ROLL && _player.state != PLAYERSTATE_LEFT_ATTACK1 &&
			_player.state != PLAYERSTATE_LEFT_ATTACK2 && _player.state != PLAYERSTATE_LEFT_ATTACK3 && _player.state != PLAYERSTATE_RIGHT_ATTACK1 &&
			_player.state != PLAYERSTATE_RIGHT_ATTACK2 && _player.state != PLAYERSTATE_RIGHT_ATTACK3)
		{
			_player.speed = MINSPEED;
			_player.state = PLAYERSTATE_RIGHT_BRAKE;
			_player.imgName = "�극��ũ";
			imageSet(_player.imgName, true);
			_player.img->setFrameY(0);
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		if (!_player.isJump)
		{
			_player.imgName = "�޸���";
			imageSet(_player.imgName, false);
		}
	}

	//���� �޸���
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (!_player.isJump && _player.state != PLAYERSTATE_LEFT_ATTACK1 && _player.state != PLAYERSTATE_LEFT_ATTACK2 && _player.state != PLAYERSTATE_LEFT_ATTACK3 &&
			_player.state != PLAYERSTATE_RIGHT_ATTACK1 &&_player.state != PLAYERSTATE_RIGHT_ATTACK2 &&_player.state != PLAYERSTATE_RIGHT_ATTACK3)
		{
			_player.key = 2;
			_player.state = PLAYERSTATE_LEFT_RUN;
			_player.speed += 0.1f;
			if (_player.speed >= MAXSPEED) _player.speed = MAXSPEED;
		}
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_player.key = 0;
		_player.speed = MINSPEED;
		if (_player.state == PLAYERSTATE_LEFT_RUN && _player.state != PLAYERSTATE_RIGHT_ROLL && _player.state != PLAYERSTATE_LEFT_ATTACK1 &&
			_player.state != PLAYERSTATE_LEFT_ATTACK2 && _player.state != PLAYERSTATE_LEFT_ATTACK3 && _player.state != PLAYERSTATE_RIGHT_ATTACK1 &&
			_player.state != PLAYERSTATE_RIGHT_ATTACK2 && _player.state != PLAYERSTATE_RIGHT_ATTACK3)
		{
			_player.state = PLAYERSTATE_LEFT_BRAKE;
			_player.imgName = "�극��ũ";
			imageSet(_player.imgName, false);
			_player.img->setFrameY(1);
		}
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

	//�� ����Ű�� ��������
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{

	}

	//�Ʒ� ����Ű�� ������
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

	//���� Ű
	if (KEYMANAGER->isOnceKeyDown('A') && !_player.isJump2)
	{
		_player.isAirAttack = false;
		if (_player.state == PLAYERSTATE_LEFT_IDLE || _player.state == PLAYERSTATE_LEFT_BRAKE || _player.state == PLAYERSTATE_LEFT_RUN)
		{
			imageSet("����", false);
			_player.state = PLAYERSTATE_JUMP;
			_player.isJump = true;
			_player.isGround = false;
			_player.jumpPower = JUMPPOWER;
			_player.gravity = GRAVITY;
		}
		else if (_player.state == PLAYERSTATE_RIGHT_IDLE || _player.state == PLAYERSTATE_RIGHT_BRAKE || _player.state == PLAYERSTATE_RIGHT_RUN)
		{
			imageSet("����", true);
			_player.state = PLAYERSTATE_JUMP;
			_player.isJump = true;
			_player.isGround = false;
			_player.jumpPower = JUMPPOWER;
			_player.gravity = GRAVITY;
		}
		else if (_player.state == PLAYERSTATE_JUMP || _player.state == PLAYERSTATE_FALL)
		{
			if (_player.img->getFrameY() == 0) imageSet("����", true);
			else if (_player.img->getFrameY() == 1) imageSet("����", false);
			_player.state = PLAYERSTATE_JUMP;
			_player.isJump2 = true;
			_player.isGround = false;
			_player.jumpPower = JUMPPOWER;
			_player.gravity = GRAVITY;
		}
		else return;
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
			EFFECTMANAGER->play("����1����", _player.rc.left, _player.y);
			if (_player.imgName == "����1") return;
			imageSet("����1", false);
		}
		else if (_player.state == PLAYERSTATE_RIGHT_IDLE || _player.state == PLAYERSTATE_RIGHT_RUN || _player.state == PLAYERSTATE_RIGHT_BRAKE)
		{
			_player.state = PLAYERSTATE_RIGHT_ATTACK1;
			EFFECTMANAGER->play("����1������", _player.rc.right, _player.y);
			if (_player.imgName == "����1") return;
			imageSet("����1", true);
		}
		else if (_player.state == PLAYERSTATE_LEFT_ATTACK1 && _player.img->getFrameX() == _player.img->getMaxFrameX() - 1)
		{
			_player.state = PLAYERSTATE_LEFT_ATTACK2;
			EFFECTMANAGER->play("����2����", _player.rc.left, _player.y);
			if (_player.imgName == "����2") return;
			imageSet("����2", false);
		}
		else if (_player.state == PLAYERSTATE_RIGHT_ATTACK1 && _player.img->getFrameX() == _player.img->getMaxFrameX() - 1)
		{
			_player.state = PLAYERSTATE_RIGHT_ATTACK2;
			EFFECTMANAGER->play("����2������", _player.rc.right, _player.y);
			if (_player.imgName == "����2") return;
			imageSet("����2", true);
		}
		else if (_player.state == PLAYERSTATE_LEFT_ATTACK2 && _player.img->getFrameX() == _player.img->getMaxFrameX() - 1)
		{
			_player.state = PLAYERSTATE_LEFT_ATTACK3;
			EFFECTMANAGER->play("����3����", _player.rc.left - 20, _player.y);
			if (_player.imgName == "����3") return;
			imageSet("����3", false);
		}
		else if (_player.state == PLAYERSTATE_RIGHT_ATTACK2 && _player.img->getFrameX() == _player.img->getMaxFrameX() - 1)
		{
			_player.state = PLAYERSTATE_RIGHT_ATTACK3;
			EFFECTMANAGER->play("����3������", _player.rc.right + 20, _player.y);
			if (_player.imgName == "����3") return;
			imageSet("����3", true);
		}
		else if ((_player.isJump || _player.isJump2) && !_player.isAirAttack)
		{
			_player.state = PLAYERSTATE_JUMP_ATTACK;
			_player.isAirAttack = true;
			if (_player.img->getFrameY() == 0) imageSet("��������", true);
			if (_player.img->getFrameY() == 1) imageSet("��������", false);
		}
	}

	//Ȱ ����
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		if (_player.state == PLAYERSTATE_LEFT_IDLE || _player.state == PLAYERSTATE_LEFT_RUN || _player.state == PLAYERSTATE_LEFT_BRAKE)
		{
			_player.state = PLAYERSTATE_LEFT_BOW;
			_player.arrow->fire(_player.rc.left, _player.y - 18, 50.0f, PI, false);
			imageSet("����Ȱ", false);
		}
		else if (_player.state == PLAYERSTATE_RIGHT_IDLE || _player.state == PLAYERSTATE_RIGHT_RUN || _player.state == PLAYERSTATE_RIGHT_BRAKE)
		{
			_player.state = PLAYERSTATE_RIGHT_BOW;
			_player.arrow->fire(_player.rc.right, _player.y - 18, 50.0f, -PI * 2);
			imageSet("����Ȱ", true);
		}
		else if (_player.state == PLAYERSTATE_LEFT_CROUCH)
		{
			_player.state = PLAYERSTATE_LEFT_CROUCHBOW;
			_player.arrow->fire(_player.rc.left, _player.y + 18, 50.0f, PI, false);
			imageSet("�ɱ�Ȱ", false);
		}
		else if (_player.state == PLAYERSTATE_RIGHT_CROUCH)
		{
			_player.state = PLAYERSTATE_RIGHT_CROUCHBOW;
			_player.arrow->fire(_player.rc.right, _player.y + 18, 50.0f, -PI * 2);
			imageSet("�ɱ�Ȱ", true);
		}
		else if ((_player.state == PLAYERSTATE_JUMP || _player.state == PLAYERSTATE_FALL) && !_player.isAirAttack)
		{
			_player.isAirAttack = true;
			if (_player.img->getFrameY() == 0)
			{
				_player.state = PLAYERSTATE_LEFT_JUMPBOW;
				imageSet("����Ȱ", true);
			}
			else if (_player.img->getFrameY() == 1)
			{
				_player.state = PLAYERSTATE_RIGHT_JUMPBOW;
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
		_player.isRight = false;
		_player.isJump = false;
		_player.isLadder = false;
		_player.isGround = true;
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
		_player.imgName = "����";
		_player.img = IMAGEMANAGER->findImage(_player.imgName);
		_player.img->setFrameY(1);
		break;
	case PLAYERSTATE_RIGHT_IDLE:
		_player.isJump = false;
		_player.isLadder = false;
		_player.isGround = true;
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
		_player.imgName = "����";
		_player.img = IMAGEMANAGER->findImage(_player.imgName);
		_player.img->setFrameY(0);
		break;
	case PLAYERSTATE_LEFT_RUN:
		_player.isRight = false;
		_player.isGround = true;
		if (!PIXELMANAGER->isPixelCollisionLeftX(_player.img, _player.x, _player.y, IMAGEMANAGER->findImage("��1-1�ȼ�")))
		{
			_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
			_player.x -= _player.speed;
		}
		break;
	case PLAYERSTATE_RIGHT_RUN:
		_player.isGround = true;
		if (!PIXELMANAGER->isPixelCollisionRightX(_player.img, _player.x, _player.y, IMAGEMANAGER->findImage("��1-1�ȼ�")))
		{
			_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
			_player.x += _player.speed;
		}
		break;
	case PLAYERSTATE_LEFT_BRAKE:
		_player.isRight = false;
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
			_player.isRight = false;
			_player.x -= MAXSPEED;
			imageSet("����", false);
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && !PIXELMANAGER->isPixelCollisionRightX(_player.img, _player.x, _player.y, IMAGEMANAGER->findImage("��1-1�ȼ�")))
		{
			_player.x += MAXSPEED;
			imageSet("����", true);
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
	case PLAYERSTATE_JUMP_ATTACK:
		if (PIXELMANAGER->testPixelCollision(_player.img, _player.x, _player.y, IMAGEMANAGER->findImage("��1-1�ȼ�"), 10, 255, 0, 0, getMemDC()))
		{
			_player.state = PLAYERSTATE_RIGHT_IDLE;
			imageSet("����", true);
		}
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
		if (_player.isJump) _player.y -= _player.jumpPower;
		break;
	case PLAYERSTATE_DOWN_JUMP:
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
		_player.y -= _player.gravity;
		break;
	case PLAYERSTATE_LEFT_ROLL:
		_player.isRight = false;
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
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT)) imageSet("��", true);
		if (KEYMANAGER->isStayKeyDown(VK_LEFT) && !PIXELMANAGER->isPixelCollisionLeftX(_player.img, _player.x, _player.y, IMAGEMANAGER->findImage("��1-1�ȼ�")))
		{
			_player.x -= MAXSPEED;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT)) imageSet("��", false);
		else if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && !PIXELMANAGER->isPixelCollisionRightX(_player.img, _player.x, _player.y, IMAGEMANAGER->findImage("��1-1�ȼ�")))
		{
			_player.x += MAXSPEED;
		}
		break;
	case PLAYERSTATE_LEFT_CROUCH: case PLAYERSTATE_RIGHT_CROUCH:
		_player.isGround = true;
		_player.rc = RectMakeCenter(_player.x, _player.y + 13, _player.img->getFrameWidth(), _player.img->getFrameHeight());
		break;
	case PLAYERSTATE_LEFT_RISE: case PLAYERSTATE_RIGHT_RISE:
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
		break;
	case PLAYERSTATE_LEFT_ATTACK1:
	case PLAYERSTATE_LEFT_ATTACK2:
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
		if (!PIXELMANAGER->isPixelCollisionLeftX(_player.img, _player.x, _player.y, IMAGEMANAGER->findImage("��1-1�ȼ�")))
			_player.x -= _player.speed / 5;
		break;
	case PLAYERSTATE_LEFT_ATTACK3:
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
		if (!PIXELMANAGER->isPixelCollisionLeftX(_player.img, _player.x, _player.y, IMAGEMANAGER->findImage("��1-1�ȼ�")))
			_player.x -= _player.speed / 2.5f;
		break;
	case PLAYERSTATE_RIGHT_ATTACK1:
	case PLAYERSTATE_RIGHT_ATTACK2:
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
		if (!PIXELMANAGER->isPixelCollisionRightX(_player.img, _player.x, _player.y, IMAGEMANAGER->findImage("��1-1�ȼ�")))
			_player.x += _player.speed / 5;
		break;
	case PLAYERSTATE_RIGHT_ATTACK3:
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
		if (!PIXELMANAGER->isPixelCollisionRightX(_player.img, _player.x, _player.y, IMAGEMANAGER->findImage("��1-1�ȼ�")))
			_player.x += _player.speed / 5;
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
	case PLAYERSTATE_LEFT_LADDER_ENTER: case PLAYERSTATE_RIGHT_LADDER_ENTER:
		break;
	case PLAYERSTATE_LADDER_DOWN:
		break;
	case PLAYERSTATE_LADDER_UP:
		break;
	case PLAYERSTATE_LEFT_LADDER_LEAVE: case PLAYERSTATE_RIGHT_LADDER_LEAVE:
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
			_player.isLadder = false;
			if (_player.img->getFrameY() == 0) imageSet("��", true);
			if (_player.img->getFrameY() == 1) imageSet("��", false);
		}
		/*if (PIXELMANAGER->testPixelCollision(_player.img, _player.x, _player.y, IMAGEMANAGER->findImage("��1-1�ȼ�"), 10, 0, 255, 0, getMemDC()))
		{
			_player.isGround = true;
			_player.isLadder = true;
			_player.isJump = false;

			if (_player.key == 3)
			{
				_player.state == PLAYERSTATE_RIGHT_RUN;
				imageSet("�޸���", true);
			}
			if (_player.key == 2)
			{
				_player.state == PLAYERSTATE_LEFT_RUN;
				imageSet("�޸���", false);
			}
		}*/
		
		break;
	case PLAYERSTATE_FALL:
		if (PIXELMANAGER->testPixelCollision(_player.img, _player.x, _player.y, IMAGEMANAGER->findImage("��1-1�ȼ�"), 1.0f, 255, 0, 0, getMemDC()))
		{
			_player.isJump = false;
			_player.isJump2 = false;
			_player.isLadder = false;
			_player.isGround = true;
			if (_player.img->getFrameY() == 0)
			{
				imageSet("����", true);
				_player.state = PLAYERSTATE_RIGHT_IDLE;
			}
			else if (_player.img->getFrameY() == 1)
			{
				imageSet("����", false);
				_player.state = PLAYERSTATE_LEFT_IDLE;
			}
			else if (_player.key == 3)
			{
				_player.state == PLAYERSTATE_RIGHT_RUN;
				imageSet("�޸���", true);
			}
			else if (_player.key == 2)
			{
				_player.state == PLAYERSTATE_LEFT_RUN;
				imageSet("�޸���", false);
			}
		}
		break;
	case PLAYERSTATE_RIGHT_IDLE: case PLAYERSTATE_LEFT_IDLE: case PLAYERSTATE_LEFT_RUN: case PLAYERSTATE_RIGHT_RUN:
	case PLAYERSTATE_RIGHT_ROLL: case PLAYERSTATE_LEFT_ROLL: case PLAYERSTATE_LEFT_BRAKE: case PLAYERSTATE_RIGHT_BRAKE:
	case PLAYERSTATE_JUMP_ATTACK: case PLAYERSTATE_LEFT_JUMPBOW: case PLAYERSTATE_RIGHT_JUMPBOW:
	case PLAYERSTATE_LEFT_BOW: case PLAYERSTATE_RIGHT_BOW:
	case PLAYERSTATE_LEFT_ATTACK1: case PLAYERSTATE_LEFT_ATTACK2: case PLAYERSTATE_LEFT_ATTACK3:
	case PLAYERSTATE_RIGHT_ATTACK1: case PLAYERSTATE_RIGHT_ATTACK2: case PLAYERSTATE_RIGHT_ATTACK3:
		if (PIXELMANAGER->testPixelCollision(_player.img, _player.x, _player.y, IMAGEMANAGER->findImage("��1-1�ȼ�"), 5.0f, 255, 0, 0, getMemDC()))
		{
			_player.isGround = true;
			_player.y = PIXELMANAGER->getPixelCollisionY(_player.img, _player.x, _player.y, IMAGEMANAGER->findImage("��1-1�ȼ�"));
		}
		else if (!PIXELMANAGER->testPixelCollision(_player.img, _player.x, _player.y, IMAGEMANAGER->findImage("��1-1�ȼ�"), 5.0f, 255, 0, 0, getMemDC()))
		{
			_player.state = PLAYERSTATE_FALL;
			if (_player.img->getFrameY() == 0) imageSet("��", true);
			if (_player.img->getFrameY() == 1) imageSet("��", false);
			_player.isGround = false;
		}
		break;
	case PLAYERSTATE_DOWN_JUMP:
		break;
	case PLAYERSTATE_LADDER_DOWN:
		break;
	case PLAYERSTATE_LADDER_UP:
		break;
	case PLAYERSTATE_LEFT_LADDER_LEAVE:
		break;
	}
}
