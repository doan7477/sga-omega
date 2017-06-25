#include "stdafx.h"
#include "lee.h"


lee::lee()
{
}


lee::~lee()
{
}

HRESULT lee::init()
{
	//��ӹް� init�� �̷������� �ʱ�ȭ ���ֱ�

	_player.img = IMAGEMANAGER->addFrameImage("�ϸ�", "image/�ѵ���/lee.bmp", 0, 0, 4050, 132, 50, 2, true, RGB(255, 0, 255));
	//�̵�
	int rightMove[] = { 33,34,35,36,37,38 };
	KEYANIMANAGER->addArrayFrameAnimation("�������̵�", "�ϸ�", rightMove, 6, 6, true);
	int leftMove[] = { 83,84,85,86,87,88 };
	KEYANIMANAGER->addArrayFrameAnimation("�����̵�", "�ϸ�", leftMove, 6, 6, true);
	//�ٱ�
	int rightRun[] = { 6,7,8,9,10,11 };
	KEYANIMANAGER->addArrayFrameAnimation("�����ʶٱ�", "�ϸ�", rightRun, 6, 6, true);
	int leftRun[] = { 56,57,58,59,60,61 };
	KEYANIMANAGER->addArrayFrameAnimation("���ʶٱ�", "�ϸ�", leftRun, 6, 6, true);
	//����
	int rightStop[] = { 0,1,2,3,4,5 };
	KEYANIMANAGER->addArrayFrameAnimation("����������", "�ϸ�", rightStop, 6, 6, true);
	int leftStop[] = { 50,51,52,53,54,55 };
	KEYANIMANAGER->addArrayFrameAnimation("��������", "�ϸ�", leftStop, 6, 6, true);
	//���̱�
	int rightDuck[] = { 12,13,14,15,16 };
	KEYANIMANAGER->addArrayFrameAnimation("�����ʼ��̱�", "�ϸ�", rightDuck, 5, 10, false);
	int leftDuck[] = { 62,63,64,65,66 };
	KEYANIMANAGER->addArrayFrameAnimation("���ʼ��̱�", "�ϸ�", leftDuck, 5, 10, false);
	//����
	int rightJump[] = { 17,18,19 };
	KEYANIMANAGER->addArrayFrameAnimation("����������", "�ϸ�", rightJump, 3, 10, false);
	int leftJump[] = { 67,68,69 };
	KEYANIMANAGER->addArrayFrameAnimation("��������", "�ϸ�", leftJump, 3, 10, false);
	//���
	int rightSoftPuch[] = { 20,21,22 };
	KEYANIMANAGER->addArrayFrameAnimation("�����ʾ��", "�ϸ�", rightSoftPuch, 3, 6, false, rightFire, this);
	int leftSoftPuch[] = { 70,71,72 };
	KEYANIMANAGER->addArrayFrameAnimation("���ʾ��", "�ϸ�", leftSoftPuch, 3, 6, false, leftFire, this);
	//����
	int rightHardPuch[] = { 23,24,25,26 };
	KEYANIMANAGER->addArrayFrameAnimation("�����ʰ���", "�ϸ�", rightHardPuch, 4, 6, false, rightFire, this);
	int leftHardPuch[] = { 73,74,75,76 };
	KEYANIMANAGER->addArrayFrameAnimation("���ʰ���", "�ϸ�", leftHardPuch, 4, 6, false, leftFire, this);
	//���
	int rightSoftKick[] = { 27,28,29,30,31,32 };
	KEYANIMANAGER->addArrayFrameAnimation("�����ʾ��", "�ϸ�", rightSoftKick, 6, 6, false, rightFire, this);
	int leftSoftKick[] = { 77,78,79,80,81,82 };
	KEYANIMANAGER->addArrayFrameAnimation("���ʾ��", "�ϸ�", leftSoftKick, 6, 6, false, leftFire, this);
	//����
	int rightHardKick[] = { 42,43,44,45,46,47,48,49 };
	KEYANIMANAGER->addArrayFrameAnimation("�����ʰ���", "�ϸ�", rightHardKick, 8, 6, false, rightFire, this);
	int leftHardKick[] = { 92,93,94,95,96,97,98,99 };
	KEYANIMANAGER->addArrayFrameAnimation("���ʰ���", "�ϸ�", leftHardKick, 8, 6, false, leftFire, this);


	_player.currentHp = _player.maxHp = 100.0f;
	_player.gravity = 5.0f;
	_player.speed = 3.0f;
	_player.playerState = PLAYERSTATE_RIGHT_STOP;
	_player.x = 200;
	_player.y = WINSIZEY - 60;
	_player.rc = RectMakeCenter(_player.x, _player.y, 50, 50);
	_player.ani = KEYANIMANAGER->findAnimation("����������");


	return S_OK;
}
void lee::release()
{

}
void lee::update()
{
	KEYANIMANAGER->update();
	inputKey();
	move();
}
void lee::render()
{
	_player.img->aniRender(getMemDC(), _player.rc.left, _player.rc.top, _player.ani);
}

void lee::attack()
{

}
void lee::move()
{
	_player.rc = RectMakeCenter(_player.x, _player.y, 50, 50);
	//�÷��̾� ���¿� ���� ������ �����ϱ�
	switch (_player.playerState)
	{
	case PLAYERSTATE_RIGHT_MOVE:
		_player.x += _player.speed;
		break;
	case PLAYERSTATE_LEFT_MOVE:
		_player.x -= _player.speed;
		break;
	case PLAYERSTATE_RIGHT_RUN:
		_player.x += 4.0f;
		break;
	case PLAYERSTATE_LEFT_RUN:
		_player.x -= 4.0f;
		break;
	case PLAYERSTATE_RIGHT_HARD_KICK:
		_player.x += 0.2f;
		break;
	case PLAYERSTATE_LEFT_HARD_KICK:
		_player.x -= 0.2f;
		break;
	case PLAYERSTATE_RIGHT_HARD_PUNCH:
		_player.x += 0.2f;
		break;
	case PLAYERSTATE_LEFT_HARD_PUNCH:
		_player.x -= 0.2f;
		break;

	}
}
void lee::inputKey()
{
	//Ű �Է�
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_player.playerState = PLAYERSTATE_RIGHT_MOVE;
		_player.ani = KEYANIMANAGER->findAnimation("�������̵�");
		_player.ani->start();
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_player.playerState = PLAYERSTATE_RIGHT_STOP;
		_player.ani = KEYANIMANAGER->findAnimation("����������");
		_player.ani->start();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_player.playerState = PLAYERSTATE_LEFT_MOVE;
		_player.ani = KEYANIMANAGER->findAnimation("�����̵�");
		_player.ani->start();
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_player.playerState = PLAYERSTATE_LEFT_STOP;
		_player.ani = KEYANIMANAGER->findAnimation("��������");
		_player.ani->start();
	}
	//����
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (_player.playerState == PLAYERSTATE_RIGHT_STOP || _player.playerState == PLAYERSTATE_RIGHT_RUN || _player.playerState == PLAYERSTATE_RIGHT_MOVE)
		{
			_player.playerState = PLAYERSTATE_RIGHT_JUMP;
			_player.ani = KEYANIMANAGER->findAnimation("����������");
			_player.ani->start();
		}
		else if (_player.playerState == PLAYERSTATE_LEFT_STOP || _player.playerState == PLAYERSTATE_LEFT_RUN || _player.playerState == PLAYERSTATE_LEFT_MOVE)
		{
			_player.playerState = PLAYERSTATE_LEFT_JUMP;
			_player.ani = KEYANIMANAGER->findAnimation("��������");
			_player.ani->start();
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		if (_player.playerState == PLAYERSTATE_RIGHT_JUMP)
		{
			_player.playerState = PLAYERSTATE_RIGHT_STOP;
			_player.ani = KEYANIMANAGER->findAnimation("����������");
			_player.ani->start();
		}
		if (_player.playerState == PLAYERSTATE_LEFT_JUMP)
		{
			_player.playerState = PLAYERSTATE_LEFT_STOP;
			_player.ani = KEYANIMANAGER->findAnimation("����������");
			_player.ani->start();
		}
	}
	//���̱�
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		if (_player.playerState == PLAYERSTATE_RIGHT_STOP || _player.playerState == PLAYERSTATE_RIGHT_RUN || _player.playerState == PLAYERSTATE_RIGHT_MOVE)
		{
			_player.playerState = PLAYERSTATE_RIGHT_DUCK;
			_player.ani = KEYANIMANAGER->findAnimation("�����ʼ��̱�");
			_player.ani->start();
		}
		else if (_player.playerState == PLAYERSTATE_LEFT_STOP || _player.playerState == PLAYERSTATE_LEFT_RUN || _player.playerState == PLAYERSTATE_LEFT_MOVE)
		{
			_player.playerState = PLAYERSTATE_LEFT_DUCK;
			_player.ani = KEYANIMANAGER->findAnimation("���ʼ��̱�");
			_player.ani->start();
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		if (_player.playerState == PLAYERSTATE_RIGHT_DUCK)
		{
			_player.playerState = PLAYERSTATE_RIGHT_STOP;
			_player.ani = KEYANIMANAGER->findAnimation("����������");
			_player.ani->start();
		}
		if (_player.playerState == PLAYERSTATE_LEFT_DUCK)
		{
			_player.playerState = PLAYERSTATE_LEFT_STOP;
			_player.ani = KEYANIMANAGER->findAnimation("����������");
			_player.ani->start();
		}
	}
	//���
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		if (_player.playerState == PLAYERSTATE_RIGHT_STOP || _player.playerState == PLAYERSTATE_RIGHT_RUN || _player.playerState == PLAYERSTATE_RIGHT_MOVE)
		{
			_player.playerState = PLAYERSTATE_RIGHT_SOFT_PUNCH;
			_player.ani = KEYANIMANAGER->findAnimation("�����ʾ��");
			_player.ani->start();
		}
		else if (_player.playerState == PLAYERSTATE_LEFT_STOP || _player.playerState == PLAYERSTATE_LEFT_RUN || _player.playerState == PLAYERSTATE_LEFT_MOVE)
		{
			_player.playerState = PLAYERSTATE_LEFT_SOFT_PUNCH;
			_player.ani = KEYANIMANAGER->findAnimation("���ʾ��");
			_player.ani->start();
		}
	}
	//����
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		if (_player.playerState == PLAYERSTATE_RIGHT_STOP || _player.playerState == PLAYERSTATE_RIGHT_RUN || _player.playerState == PLAYERSTATE_RIGHT_MOVE)
		{
			_player.playerState = PLAYERSTATE_RIGHT_HARD_PUNCH;
			_player.ani = KEYANIMANAGER->findAnimation("�����ʰ���");
			_player.ani->start();
		}
		else if (_player.playerState == PLAYERSTATE_LEFT_STOP || _player.playerState == PLAYERSTATE_LEFT_RUN || _player.playerState == PLAYERSTATE_LEFT_MOVE)
		{
			_player.playerState = PLAYERSTATE_LEFT_HARD_PUNCH;
			_player.ani = KEYANIMANAGER->findAnimation("���ʰ���");
			_player.ani->start();
		}
	}
	//���
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		if (_player.playerState == PLAYERSTATE_RIGHT_STOP || _player.playerState == PLAYERSTATE_RIGHT_RUN || _player.playerState == PLAYERSTATE_RIGHT_MOVE)
		{
			_player.playerState = PLAYERSTATE_RIGHT_SOFT_KICK;
			_player.ani = KEYANIMANAGER->findAnimation("�����ʾ��");
			_player.ani->start();
		}
		else if (_player.playerState == PLAYERSTATE_LEFT_STOP || _player.playerState == PLAYERSTATE_LEFT_RUN || _player.playerState == PLAYERSTATE_LEFT_MOVE)
		{
			_player.playerState = PLAYERSTATE_LEFT_SOFT_KICK;
			_player.ani = KEYANIMANAGER->findAnimation("���ʾ��");
			_player.ani->start();
		}
	}
	//����
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		if (_player.playerState == PLAYERSTATE_RIGHT_STOP || _player.playerState == PLAYERSTATE_RIGHT_RUN || _player.playerState == PLAYERSTATE_RIGHT_MOVE)
		{
			_player.playerState = PLAYERSTATE_RIGHT_HARD_KICK;
			_player.ani = KEYANIMANAGER->findAnimation("�����ʰ���");
			_player.ani->start();
		}
		else if (_player.playerState == PLAYERSTATE_LEFT_STOP || _player.playerState == PLAYERSTATE_LEFT_RUN || _player.playerState == PLAYERSTATE_LEFT_MOVE)
		{
			_player.playerState = PLAYERSTATE_LEFT_HARD_KICK;
			_player.ani = KEYANIMANAGER->findAnimation("���ʰ���");
			_player.ani->start();
		}
	}

}
void lee::setPlayerAni()
{

}
void lee::command()
{

}

void lee::rightFire(void* obj)
{
	lee* l = (lee*)obj;
	l->setPlayerState(PLAYERSTATE_RIGHT_STOP);
	l->setPlayerMotion(KEYANIMANAGER->findAnimation("����������"));
	l->getPlayerMotion()->start();
}

void lee::leftFire(void* obj)
{
	lee* l = (lee*)obj;
	l->setPlayerState(PLAYERSTATE_LEFT_STOP);
	l->setPlayerMotion(KEYANIMANAGER->findAnimation("��������"));
	l->getPlayerMotion()->start();
}