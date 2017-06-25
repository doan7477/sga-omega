#include "stdafx.h"
#include "sasuke.h"

sasuke::sasuke()
{
}

sasuke::~sasuke()
{
}

HRESULT sasuke::init()
{
	_chidoriCount = 0;
	_commandFinal = 0;
	_commandCount = 0;
	_commandTimer = 0;
	//��ӹް� init�� �̷������� �ʱ�ȭ ���ֱ�
	_player.img = IMAGEMANAGER->addFrameImage("�罺��", "image/�����/Sasuke.bmp", 0, 0, 1090, 728, 10, 14, true, RGB(255, 0, 255));

	int rightStop[] = { 0,1,2,3 };
	KEYANIMANAGER->addArrayFrameAnimation("����������", "�罺��", rightStop, 4, 10, true);
	int rightMove[] = { 4,5,6,7,8,9 };
	KEYANIMANAGER->addArrayFrameAnimation("�������̵�", "�罺��", rightMove, 6, 10, true);
	int rightDuck[] = { 20,21 };
	KEYANIMANAGER->addArrayFrameAnimation("�����ʼ��̱�", "�罺��", rightDuck, 2, 10, true);
	int leftStop[] = { 10,11,12,13 };
	KEYANIMANAGER->addArrayFrameAnimation("��������", "�罺��", leftStop, 4, 10, true);
	int leftMove[] = { 14,15,16,17,18,19 };
	KEYANIMANAGER->addArrayFrameAnimation("�����̵�", "�罺��", leftMove, 6, 10, true);
	int leftDuck[] = { 30,31 };
	KEYANIMANAGER->addArrayFrameAnimation("���ʼ��̱�", "�罺��", leftDuck, 2, 10, true);
	int rightRunning[] = { 24,25,26,27,28,29 };
	KEYANIMANAGER->addArrayFrameAnimation("�����ʴ޸���", "�罺��", rightRunning, 6, 10, true);
	int leftRunning[] = { 34,35,36,37,38,39 };
	KEYANIMANAGER->addArrayFrameAnimation("���ʴ޸���", "�罺��", leftRunning, 4, 10, true);
	int rightJumping[] = { 40,41,42,43,44 };
	KEYANIMANAGER->addArrayFrameAnimation("����������", "�罺��", rightJumping, 5, 10, true);
	int leftJumping[] = { 50,51,52,53,54 };
	KEYANIMANAGER->addArrayFrameAnimation("��������", "�罺��", leftJumping, 5, 10, true);
	//���ݸ��
	int rightSoftpunch[] = { 64,65,66 };
	KEYANIMANAGER->addArrayFrameAnimation("�����ʾ��", "�罺��", rightSoftpunch, 3, 10, false, rightattack, this);
	int leftSoftpunch[] = { 74,75,76 };
	KEYANIMANAGER->addArrayFrameAnimation("���ʾ��", "�罺��", leftSoftpunch, 3, 10, false, leftattack, this);
	int rightHardpunch[] = { 80,81,82,83,84 };
	KEYANIMANAGER->addArrayFrameAnimation("�����ʰ���", "�罺��", rightHardpunch, 5, 10, false, rightattack, this);
	int leftHardpunch[] = { 90,91,92,93,94 };
	KEYANIMANAGER->addArrayFrameAnimation("���ʰ���", "�罺��", leftHardpunch, 5, 10, false, leftattack, this);
	int rightSoftkick[] = { 60,61,62,63 };
	KEYANIMANAGER->addArrayFrameAnimation("�����ʾ��", "�罺��", rightSoftkick, 4, 10, false, rightattack, this);
	int leftSoftkick[] = { 70,71,72,73 };
	KEYANIMANAGER->addArrayFrameAnimation("���ʾ��", "�罺��", leftSoftkick, 4, 10, false, leftattack, this);
	int rightHardkick[] = { 67,68,69 };
	KEYANIMANAGER->addArrayFrameAnimation("�����ʰ���", "�罺��", rightHardkick, 3, 10, false, rightattack, this);
	int leftHardkick[] = { 77,78,79 };
	KEYANIMANAGER->addArrayFrameAnimation("���ʰ���", "�罺��", leftHardkick, 3, 10, false, leftattack, this);

	//��ų���
	int rightCharging[] = { 100,101,102,103,104,105,106,107,108,109 };
	KEYANIMANAGER->addArrayFrameAnimation("�����ʱ������", "�罺��", rightCharging, 10, 10, false, rightattack, this);
	int leftCharging[] = { 110,111,112,113,114,115,116,117,118,119 };
	KEYANIMANAGER->addArrayFrameAnimation("���ʱ������", "�罺��", leftCharging, 10, 10, false, leftattack, this);
	int rightChidori[] = { 120,121,122,123,124,125,126,127,128,129 };
	KEYANIMANAGER->addArrayFrameAnimation("������ġ����", "�罺��", rightChidori, 10, 10, false, rightattack, this);
	int leftChidori[] = { 130,131,132,133,134,135,136,137,138,139 };
	KEYANIMANAGER->addArrayFrameAnimation("����ġ����", "�罺��", leftChidori, 10, 10, false, leftattack, this);

	_player.currentHp = _player.maxHp = 100.0f;
	_player.gravity = 5.0f;
	_player.speed = 4.0f;
	_player.playerState = PLAYERSTATE_RIGHT_STOP;
	_player.x = 200;
	_player.y = WINSIZEY - 60;
	_player.rc = RectMakeCenter(_player.x, _player.y, 50, 50);
	_player.attackRange= RectMakeCenter(_hitzoneX, _hitzoneY, 10, 10);
	_player.ani = KEYANIMANAGER->findAnimation("����������");
	_player.jumping = false;

	_hitzoneX = 0;
	_hitzoneY = 0;

	return S_OK;
}

void sasuke::release()
{
}

void sasuke::update()
{
	if (_player.jumping) _player.gravity += 0.1f;
	KEYANIMANAGER->update();
	inputKey();
	command();
	move();
}

void sasuke::render()
{
	_player.img->aniRender(getMemDC(), _player.rc.left, _player.rc.top, _player.ani);
	char str[128];
	sprintf(str, "%d, %d, %d", _commandCount, _commandTimer, _commandFinal);
	TextOut(getMemDC(), 200, 200, str, strlen(str));
}

void sasuke::attack()
{
	_player.attackRange = RectMakeCenter(_hitzoneX, _hitzoneY, 10, 10);

	switch (_player.playerState)
	{
		case PLAYERSTATE_RIGHT_SOFT_PUNCH:
			_hitzoneX = _player.x + 23;
			_hitzoneY = _player.y - 8;
		break;
	}
}

void sasuke::move()
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
			_player.x += 1.5 * _player.speed;
		break;
		case PLAYERSTATE_LEFT_RUN:
			_player.x -= 1.5 * _player.speed;
		break;
		case PLAYERSTATE_RIGHT_STAYJUMP:
			_player.x += 2.0f;
			_player.y -= sin(PI / 2) * _player.speed + _player.gravity;
		break;
		case PLAYERSTATE_LEFT_STAYJUMP:
			_player.x -= 2.0f;
			_player.y -= sin(PI / 2) * _player.speed + _player.gravity;
		break;
		case PLAYERSTATE_RIGHT_SKILL3:
			_player.x += 2 * _player.speed;
		break;
		case PLAYERSTATE_LEFT_SKILL3:
			_player.x -= 2 * _player.speed;
		break;
	}
}

void sasuke::inputKey()
{
	//Ű �Է� (����)
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_commandClick = true;
		_commandCount += 1;
		_commandFinal = 1;
		_player.playerState = PLAYERSTATE_RIGHT_MOVE;
		_player.ani = KEYANIMANAGER->findAnimation("�������̵�");
		_player.ani->start();

		//�뽬 (Ŀ�ǵ�ī��Ʈ�� ��� ���� ���̰�, Ű�Է�����)
		if (_commandTimer >= 2)
		{
			_player.playerState = PLAYERSTATE_RIGHT_RUN;
			_player.ani = KEYANIMANAGER->findAnimation("�����ʴ޸���");
			_player.ani->start();
		}
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_player.playerState = PLAYERSTATE_RIGHT_STOP;
		_player.ani = KEYANIMANAGER->findAnimation("����������");
		_player.ani->start();

		//�޸��� �ִ� ���̰� Ű�� ������
		if (_player.playerState == PLAYERSTATE_RIGHT_RUN) _commandTimer = 0;
	}

	//Ű �Է� (�ϴ�)
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		_commandClick = true;
		_commandCount += 4;
		_commandFinal = 4;
		if (_player.playerState == PLAYERSTATE_RIGHT_STOP)
		{
			_player.playerState = PLAYERSTATE_RIGHT_DUCK;
			_player.ani = KEYANIMANAGER->findAnimation("�����ʼ��̱�");
			_player.ani->start();
		}
		else if (_player.playerState == PLAYERSTATE_LEFT_STOP)
		{
			_player.playerState = PLAYERSTATE_LEFT_DUCK;
			_player.ani = KEYANIMANAGER->findAnimation("���ʼ��̱�");
			_player.ani->start();
		}
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
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
			_player.ani = KEYANIMANAGER->findAnimation("��������");
			_player.ani->start();
		}
	}

	//Ű �Է� (���� �ϴ�)
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN) && KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_commandClick = true;
		_commandCount += 8;
	}

	//Ű �Է� (����)
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_commandClick = true;
		_commandCount += 16;
		_commandFinal = 16;
		_player.playerState = PLAYERSTATE_LEFT_MOVE;
		_player.ani = KEYANIMANAGER->findAnimation("�����̵�");
		_player.ani->start();

		//�뽬 (Ŀ�ǵ�ī��Ʈ�� ��� ���� ���̰�, Ű�Է�����)
		if (_commandTimer >= 2)
		{
			_player.playerState = PLAYERSTATE_LEFT_RUN;
			_player.ani = KEYANIMANAGER->findAnimation("���ʴ޸���");
			_player.ani->start();
		}
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_player.playerState = PLAYERSTATE_LEFT_STOP;
		_player.ani = KEYANIMANAGER->findAnimation("��������");
		_player.ani->start();

		//�޸��� �ִ� ���̰� Ű�� ������
		if (_player.playerState == PLAYERSTATE_LEFT_RUN) _commandTimer = 0;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		_player.gravity = 4.0f;
		_player.jumping = true;
		if (_player.playerState == PLAYERSTATE_RIGHT_STOP)
		{
			_player.playerState = PLAYERSTATE_RIGHT_STAYJUMP;
			_player.ani = KEYANIMANAGER->findAnimation("����������");
			_player.ani->start();
		}
		else if (_player.playerState == PLAYERSTATE_LEFT_STOP)
		{
			_player.playerState = PLAYERSTATE_LEFT_STAYJUMP;
			_player.ani = KEYANIMANAGER->findAnimation("��������");
			_player.ani->start();
		}
	}

	//���� Ŀ�ǵ� ����
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		_commandCount += 32;
		if (_player.playerState == PLAYERSTATE_RIGHT_STOP || _player.playerState == PLAYERSTATE_RIGHT_MOVE || _player.playerState == PLAYERSTATE_RIGHT_RUN)
		{
			_player.playerState = PLAYERSTATE_RIGHT_SOFT_PUNCH;
			_player.ani = KEYANIMANAGER->findAnimation("�����ʾ��");
			_player.ani->start();
		}
		else if (_player.playerState == PLAYERSTATE_LEFT_STOP || _player.playerState == PLAYERSTATE_LEFT_MOVE || _player.playerState == PLAYERSTATE_LEFT_RUN)
		{
			_player.playerState = PLAYERSTATE_LEFT_SOFT_PUNCH;
			_player.ani = KEYANIMANAGER->findAnimation("���ʾ��");
			_player.ani->start();
		}
	}
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		_commandCount += 64;
		if (_player.playerState == PLAYERSTATE_RIGHT_STOP || _player.playerState == PLAYERSTATE_RIGHT_MOVE || _player.playerState == PLAYERSTATE_RIGHT_RUN)
		{
			_player.playerState = PLAYERSTATE_RIGHT_HARD_PUNCH;
			_player.ani = KEYANIMANAGER->findAnimation("�����ʰ���");
			_player.ani->start();
		}
		else if (_player.playerState == PLAYERSTATE_LEFT_STOP || _player.playerState == PLAYERSTATE_LEFT_MOVE || _player.playerState == PLAYERSTATE_LEFT_RUN)
		{
			_player.playerState = PLAYERSTATE_LEFT_HARD_PUNCH;
			_player.ani = KEYANIMANAGER->findAnimation("���ʰ���");
			_player.ani->start();
		}
	}
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		_commandCount += 128;
		if (_player.playerState == PLAYERSTATE_RIGHT_STOP || _player.playerState == PLAYERSTATE_RIGHT_MOVE || _player.playerState == PLAYERSTATE_RIGHT_RUN)
		{
			_player.playerState = PLAYERSTATE_RIGHT_SOFT_KICK;
			_player.ani = KEYANIMANAGER->findAnimation("�����ʾ��");
			_player.ani->start();
		}
		else if (_player.playerState == PLAYERSTATE_LEFT_STOP || _player.playerState == PLAYERSTATE_LEFT_MOVE || _player.playerState == PLAYERSTATE_LEFT_RUN)
		{
			_player.playerState = PLAYERSTATE_LEFT_SOFT_KICK;
			_player.ani = KEYANIMANAGER->findAnimation("���ʾ��");
			_player.ani->start();
		}
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		_commandCount += 256;
		if (_player.playerState == PLAYERSTATE_RIGHT_STOP || _player.playerState == PLAYERSTATE_RIGHT_MOVE || _player.playerState == PLAYERSTATE_RIGHT_RUN)
		{
			_player.playerState = PLAYERSTATE_RIGHT_HARD_KICK;
			_player.ani = KEYANIMANAGER->findAnimation("�����ʰ���");
			_player.ani->start();
		}
		else if (_player.playerState == PLAYERSTATE_LEFT_STOP || _player.playerState == PLAYERSTATE_LEFT_MOVE || _player.playerState == PLAYERSTATE_LEFT_RUN)
		{
			_player.playerState = PLAYERSTATE_LEFT_HARD_KICK;
			_player.ani = KEYANIMANAGER->findAnimation("���ʰ���");
			_player.ani->start();
		}
	}

	//Ŀ�ǵ� ����
	if (_commandClick) _commandTimer++;

	if (_commandTimer == 30)
	{
		_commandClick = false;
		_commandFinal = 0;
		_commandCount = 0;
		_commandTimer = 0;
	}
}

void sasuke::setPlayerAni()
{
}

void sasuke::command()
{
	//������ ����������
	if (_commandFinal == 1 && _commandCount == 37 && (0 < _commandTimer && _commandTimer < 30))
	{
		_player.playerState = PLAYERSTATE_RIGHT_SKILL1;
		_player.ani = KEYANIMANAGER->findAnimation("�����ʱ������");
		_player.ani->start();
	}
	if (_commandFinal == 1 && _commandCount == 49 && (0 < _commandTimer && _commandTimer < 30))
	{
		_player.playerState = PLAYERSTATE_RIGHT_SKILL2;
		_player.ani = KEYANIMANAGER->findAnimation("�����ʾ��");
		_player.ani->start();
	}
	if (_commandFinal == 1 && _commandCount == 85 && (0 < _commandTimer && _commandTimer < 30))
	{
		_player.playerState = PLAYERSTATE_RIGHT_SKILL3;
		_player.ani = KEYANIMANAGER->findAnimation("������ġ����");
		_player.ani->start();
	}
	//������ ����������
	if (_commandFinal == 16 && _commandCount == 52 && (0 < _commandTimer && _commandTimer < 30))
	{
		_player.playerState = PLAYERSTATE_LEFT_SKILL1;
		_player.ani = KEYANIMANAGER->findAnimation("���ʱ������");
		_player.ani->start();
	}
	if (_commandFinal == 16 && _commandCount == 49 && (0 < _commandTimer && _commandTimer < 30))
	{
		_player.playerState = PLAYERSTATE_LEFT_SKILL2;
		_player.ani = KEYANIMANAGER->findAnimation("���ʾ��");
		_player.ani->start();
	}
	if (_commandFinal == 16 && _commandCount == 85 && (0 < _commandTimer && _commandTimer < 30))
	{
		_player.playerState = PLAYERSTATE_LEFT_SKILL3;
		_player.ani = KEYANIMANAGER->findAnimation("����ġ����");
		_player.ani->start();
	}
}

void sasuke::rightattack(void* obj)
{
	sasuke* s = (sasuke*)obj;

	s->setPlayerState(PLAYERSTATE_RIGHT_STOP);
	s->setPlayerMotion(KEYANIMANAGER->findAnimation("����������"));
	s->getPlayerMotion()->start();
}

void sasuke::leftattack(void* obj)
{
	sasuke* s = (sasuke*)obj;

	s->setPlayerState(PLAYERSTATE_LEFT_STOP);
	s->setPlayerMotion(KEYANIMANAGER->findAnimation("��������"));
	s->getPlayerMotion()->start();
}