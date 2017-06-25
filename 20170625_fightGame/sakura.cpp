#include "stdafx.h"
#include "sakura.h"


sakura::sakura()
{
}


sakura::~sakura()
{
}

HRESULT sakura::init()
{
	//�̹��� �ʱ�ȭ
	_player.img = IMAGEMANAGER->addFrameImage("�����", "image/������/sakura.bmp", 0, 0, 1656, 672, 18, 7, true, RGB(255, 0, 255));
	
	//�̵�
	int leftMove[] = { 0,1,2,3 };
	KEYANIMANAGER->addArrayFrameAnimation("���̵�", "�����", leftMove, 4, 10, true);
	int rightMove[] = { 6,7,8,9 };
	KEYANIMANAGER->addArrayFrameAnimation("���̵�", "�����", rightMove, 4, 10, true);

	//���̱�
	int leftDuck[] = { 12,13,14 };
	KEYANIMANAGER->addArrayFrameAnimation("�¼��̱�", "�����", leftDuck, 3, 10, true);
	int rightDuck[] = { 15,16,17 };
	KEYANIMANAGER->addArrayFrameAnimation("����̱�", "�����", rightDuck, 3, 10, true);

	//�ٱ�
	int leftDash[] = { 18,19,20,21,22 };
	KEYANIMANAGER->addArrayFrameAnimation("�¶ٱ�", "�����", leftDash, 5, 10, true);
	int rightDash[] = { 23,24,25,26,27 };
	KEYANIMANAGER->addArrayFrameAnimation("��ٱ�", "�����", rightDash, 5, 10, true);

	//���
	int leftSoftPunch[] = { 28,29,30 };
	KEYANIMANAGER->addArrayFrameAnimation("�¾��", "�����", leftSoftPunch, 3, 10, true, leftFire, this);
	int rightSoftPunch[] = { 31,32,33 };
	KEYANIMANAGER->addArrayFrameAnimation("����", "�����", rightSoftPunch, 3, 10, true, rightFire, this);

	//����
	int leftStop[] = { 36,37,38,39,40,41 };
	KEYANIMANAGER->addArrayFrameAnimation("������", "�����", leftStop, 6, 10, true);
	int rightStop[] = { 42,43,44,45,46,47 };
	KEYANIMANAGER->addArrayFrameAnimation("������", "�����", rightStop, 6, 10, true);

	//����
	int leftJump[] = { 54,55,56,57,58,59,60,61,62 };
	KEYANIMANAGER->addArrayFrameAnimation("������", "�����", leftStop, 9, 10, true);
	int rightJump[] = { 63,64,65,66,67,68,69,70,71 };
	KEYANIMANAGER->addArrayFrameAnimation("������", "�����", rightStop, 9, 10, true);

	//����
	int leftStrongPunch[] = { 72,73,74,75,76,77,78 };
	KEYANIMANAGER->addArrayFrameAnimation("�°���", "�����", leftStrongPunch, 7, 10, true, leftFire, this);
	int rightStrongPunch[] = { 79,80,81,82,83,84,85 };
	KEYANIMANAGER->addArrayFrameAnimation("�찭��", "�����", rightStrongPunch, 7, 10, true, rightFire, this);

	//������
	int leftKick[] = { 90,91,92,93,94 };
	KEYANIMANAGER->addArrayFrameAnimation("�¹�", "�����", leftKick, 5, 10, true, leftFire, this);
	int rightKick[] = { 95,96,97,98,99 };
	KEYANIMANAGER->addArrayFrameAnimation("���", "�����", rightKick, 5, 10, true, rightFire, this);

	//�������
	int leftSkill1[] = { 100,101,102,103 };
	KEYANIMANAGER->addArrayFrameAnimation("�±������", "�����", leftSkill1, 4, 10, true);
	int rightSkill1[] = { 104,105,106,107 };
	KEYANIMANAGER->addArrayFrameAnimation("��������", "�����", rightSkill1, 4, 10, true);

	//ǥâ������
	int leftSkill2[] = { 108,109,110 };
	KEYANIMANAGER->addArrayFrameAnimation("��ǥâ������", "�����", leftSkill2, 3, 10, true);
	int rightSkill2[] = { 111,112,113 };
	KEYANIMANAGER->addArrayFrameAnimation("��ǥâ������", "�����", rightSkill2, 3, 10, true);

	//64��Ÿ
	int leftSkill3[] = { 114,115,116,117,118,119 };
	KEYANIMANAGER->addArrayFrameAnimation("�¿�Ÿ", "�����", leftSkill3, 6, 10, true);
	int rightSkill3[] = { 120,121,122,123,124,125 };
	KEYANIMANAGER->addArrayFrameAnimation("�쿬Ÿ", "�����", rightSkill3, 6, 10, true);

	_player.currentHp = _player.maxHp = 100.0f;
	_player.gravity = 5.0f;
	_player.speed = 3.0f;
	_player.playerState = PLAYERSTATE_RIGHT_STOP;
	_player.x = 200;
	_player.y = WINSIZEY - 50;
	_player.rc = RectMakeCenter(_player.x, _player.y, 50, 50);
	_player.ani = KEYANIMANAGER->findAnimation("������");

	return S_OK;
}

void sakura::release()
{}

void sakura::update()
{
	KEYANIMANAGER->update();
	inputKey();
	move();
}

void sakura::render()
{
	Rectangle(getMemDC(), _player.attackRange.left, _player.attackRange.top, _player.attackRange.right, _player.attackRange.bottom);
	Rectangle(getMemDC(), _player.rc.left, _player.rc.top, _player.rc.right, _player.rc.bottom);
	_player.img->aniRender(getMemDC(), _player.rc.left - 25, _player.rc.top - 50, _player.ani);
}

void sakura::move()
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
	case PLAYERSTATE_RIGHT_HARD_PUNCH:
		_player.x += 0.2f;
		break;
	case PLAYERSTATE_LEFT_HARD_PUNCH:
		_player.x -= 0.2f;
		break;
	}
}

void sakura::inputKey()
{
	//�̵�
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_player.playerState = PLAYERSTATE_LEFT_MOVE;
		_player.ani = KEYANIMANAGER->findAnimation("���̵�");
		_player.ani->start();
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_player.playerState = PLAYERSTATE_LEFT_STOP;
		_player.ani = KEYANIMANAGER->findAnimation("������");
		_player.ani->start();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_player.playerState = PLAYERSTATE_RIGHT_MOVE;
		_player.ani = KEYANIMANAGER->findAnimation("���̵�");
		_player.ani->start();
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_player.playerState = PLAYERSTATE_RIGHT_STOP;
		_player.ani = KEYANIMANAGER->findAnimation("������");
		_player.ani->start();
	}

	//����
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (_player.playerState == PLAYERSTATE_RIGHT_STOP || _player.playerState == PLAYERSTATE_RIGHT_RUN || _player.playerState == PLAYERSTATE_RIGHT_MOVE)
		{
			_player.playerState = PLAYERSTATE_RIGHT_JUMP;
			_player.ani = KEYANIMANAGER->findAnimation("������");
			_player.ani->start();
		}
		else if (_player.playerState == PLAYERSTATE_LEFT_STOP || _player.playerState == PLAYERSTATE_LEFT_RUN || _player.playerState == PLAYERSTATE_LEFT_MOVE)
		{
			_player.playerState = PLAYERSTATE_LEFT_JUMP;
			_player.ani = KEYANIMANAGER->findAnimation("������");
			_player.ani->start();
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		if (_player.playerState == PLAYERSTATE_RIGHT_JUMP)
		{
			_player.playerState = PLAYERSTATE_RIGHT_STOP;
			_player.ani = KEYANIMANAGER->findAnimation("������");
			_player.ani->start();
		}
		if (_player.playerState == PLAYERSTATE_LEFT_JUMP)
		{
			_player.playerState = PLAYERSTATE_LEFT_STOP;
			_player.ani = KEYANIMANAGER->findAnimation("������");
			_player.ani->start();
		}
	}
	//���̱�
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		if (_player.playerState == PLAYERSTATE_RIGHT_STOP || _player.playerState == PLAYERSTATE_RIGHT_RUN || _player.playerState == PLAYERSTATE_RIGHT_MOVE)
		{
			_player.playerState = PLAYERSTATE_RIGHT_DUCK;
			_player.ani = KEYANIMANAGER->findAnimation("����̱�");
			_player.ani->start();
		}
		else if (_player.playerState == PLAYERSTATE_LEFT_STOP || _player.playerState == PLAYERSTATE_LEFT_RUN || _player.playerState == PLAYERSTATE_LEFT_MOVE)
		{
			_player.playerState = PLAYERSTATE_LEFT_DUCK;
			_player.ani = KEYANIMANAGER->findAnimation("�¼��̱�");
			_player.ani->start();
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		if (_player.playerState == PLAYERSTATE_RIGHT_DUCK)
		{
			_player.playerState = PLAYERSTATE_RIGHT_STOP;
			_player.ani = KEYANIMANAGER->findAnimation("������");
			_player.ani->start();
		}
		if (_player.playerState == PLAYERSTATE_LEFT_DUCK)
		{
			_player.playerState = PLAYERSTATE_LEFT_STOP;
			_player.ani = KEYANIMANAGER->findAnimation("������");
			_player.ani->start();
		}
	}
	//���
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		playerManager::attack();
		if (_player.playerState == PLAYERSTATE_RIGHT_STOP || _player.playerState == PLAYERSTATE_RIGHT_RUN || _player.playerState == PLAYERSTATE_RIGHT_MOVE)
		{
			_player.playerState = PLAYERSTATE_RIGHT_SOFT_PUNCH;
			_player.ani = KEYANIMANAGER->findAnimation("����");
			_player.ani->start();
		}
		else if (_player.playerState == PLAYERSTATE_LEFT_STOP || _player.playerState == PLAYERSTATE_LEFT_RUN || _player.playerState == PLAYERSTATE_LEFT_MOVE)
		{
			_player.playerState = PLAYERSTATE_LEFT_SOFT_PUNCH;
			_player.ani = KEYANIMANAGER->findAnimation("�¾��");
			_player.ani->start();
		}
	}
	//����
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		playerManager::attack();
		if (_player.playerState == PLAYERSTATE_RIGHT_STOP || _player.playerState == PLAYERSTATE_RIGHT_RUN || _player.playerState == PLAYERSTATE_RIGHT_MOVE)
		{
			_player.playerState = PLAYERSTATE_RIGHT_HARD_PUNCH;
			_player.ani = KEYANIMANAGER->findAnimation("�찭��");
			_player.ani->start();
		}
		else if (_player.playerState == PLAYERSTATE_LEFT_STOP || _player.playerState == PLAYERSTATE_LEFT_RUN || _player.playerState == PLAYERSTATE_LEFT_MOVE)
		{
			_player.playerState = PLAYERSTATE_LEFT_HARD_PUNCH;
			_player.ani = KEYANIMANAGER->findAnimation("�°���");
			_player.ani->start();
		}
	}
	//���
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		playerManager::attack();
		if (_player.playerState == PLAYERSTATE_RIGHT_STOP || _player.playerState == PLAYERSTATE_RIGHT_RUN || _player.playerState == PLAYERSTATE_RIGHT_MOVE)
		{
			_player.playerState = PLAYERSTATE_RIGHT_SOFT_KICK;
			_player.ani = KEYANIMANAGER->findAnimation("���");
			_player.ani->start();
		}
		else if (_player.playerState == PLAYERSTATE_LEFT_STOP || _player.playerState == PLAYERSTATE_LEFT_RUN || _player.playerState == PLAYERSTATE_LEFT_MOVE)
		{
			_player.playerState = PLAYERSTATE_LEFT_SOFT_KICK;
			_player.ani = KEYANIMANAGER->findAnimation("�¹�");
			_player.ani->start();
		}
	}
	//������ ���ߵ����� ����.
}

void sakura::setPlayerAni()
{}

void sakura::attack()
{}

void sakura::command()
{}

void sakura::rightFire(void* obj)
{
	sakura* s = (sakura*)obj;
	s->setPlayerState(PLAYERSTATE_RIGHT_STOP);
	s->setPlayerMotion(KEYANIMANAGER->findAnimation("������"));
	s->getPlayerAttackRange() = RectMake(0, 0, 0, 0);
	s->getPlayerMotion()->start();
}

void sakura::leftFire(void* obj)
{
	sakura* s = (sakura*)obj;
	s->setPlayerState(PLAYERSTATE_LEFT_STOP);
	s->setPlayerMotion(KEYANIMANAGER->findAnimation("������"));
	s->getPlayerAttackRange() = RectMake(0, 0, 0, 0);
	s->getPlayerMotion()->start();
}