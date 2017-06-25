#include "stdafx.h"
#include "naruto.h"


naruto::naruto()
{
}


naruto::~naruto()
{
}

HRESULT naruto::init()
{
	_player.img = IMAGEMANAGER->addFrameImage("������", "image/�輺��/naruto.bmp", 0, 0, 3721, 112, 61, 2, true, RGB(255, 0, 255));
	_iToad = IMAGEMANAGER->addImage("���β���", "image/�輺��/toad.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	//����
	int rightStop[] = { 0,1,2,3,4,5 };
	KEYANIMANAGER->addArrayFrameAnimation("����������", "������", rightStop, 6, 6, true);
	int leftStop[] = { 61,62,63,64,65,66 };
	KEYANIMANAGER->addArrayFrameAnimation("��������", "������", leftStop, 6, 6, true);

	//�̵�
	int rightMove[] = { 6,7,8,9,10,11 };
	KEYANIMANAGER->addArrayFrameAnimation("�������̵�", "������", rightMove, 6, 6, true);
	int leftMove[] = { 67,68,69,70,71,72 };
	KEYANIMANAGER->addArrayFrameAnimation("�����̵�", "������", leftMove, 6, 6, true);

	//�ٱ�
	int rightRun[] = { 12,13,14,15,16,17 };
	KEYANIMANAGER->addArrayFrameAnimation("�����ʶٱ�", "������", rightRun, 6, 6, true);
	int leftRun[] = { 73,74,75,76,77,78 };
	KEYANIMANAGER->addArrayFrameAnimation("���ʶٱ�", "������", leftRun, 6, 6, true);

	//���
	int rightSoftPunch[] = { 18,19,20 };
	KEYANIMANAGER->addArrayFrameAnimation("�����ʾ��", "������", rightSoftPunch, 3, 10, false, rightAttack, this);
	int leftSoftPunch[] = { 79,80,81 };
	KEYANIMANAGER->addArrayFrameAnimation("���ʾ��", "������", leftSoftPunch, 3, 10, false, leftAttack, this);

	//����
	int rightHardPunch[] = { 21,22,23,24 };
	KEYANIMANAGER->addArrayFrameAnimation("�����ʰ���", "������", rightHardPunch, 4, 10, false, rightAttack, this);
	int leftHardPunch[] = { 82,83,84,85 };
	KEYANIMANAGER->addArrayFrameAnimation("���ʰ���", "������", leftHardPunch, 4, 10, false, leftAttack, this);

	//Ŀ�ǵ� 1 ��ġ��
	int rightHeadButt[] = { 25,26,27 };
	KEYANIMANAGER->addArrayFrameAnimation("�����ʹ�ġ��", "������", rightHeadButt, 3, 10, false, rightAttack, this);
	int leftHeadButt[] = { 86,87,88 };
	KEYANIMANAGER->addArrayFrameAnimation("���ʹ�ġ��", "������", leftHeadButt, 3, 10, false, leftAttack, this);

	//����
	int rightJump[] = { 28,29 };
	KEYANIMANAGER->addArrayFrameAnimation("����������", "������", rightJump, 2, 10, false);
	int leftJump[] = { 89,90 };
	KEYANIMANAGER->addArrayFrameAnimation("��������", "������", leftJump, 2, 10, false);

	//�߶�
	int rightFall[] = { 30,31 };
	KEYANIMANAGER->addArrayFrameAnimation("�������߶�", "������", rightFall, 2, 10, false);
	int leftFall[] = { 91,92 };
	KEYANIMANAGER->addArrayFrameAnimation("�����߶�", "������", leftFall, 2, 10, false);

	//Ŀ�ǵ� 2 ������ ��ô
	int rightThrow[] = { 32,33,34 };
	KEYANIMANAGER->addArrayFrameAnimation("��������ô", "������", rightThrow, 3, 5, false, rightAttack, this);
	int leftThrow[] = { 93,94,95 };
	KEYANIMANAGER->addArrayFrameAnimation("������ô", "������", leftThrow, 3, 5, false, leftAttack, this);

	//Ŀ�ǵ� 3 ���β��� ��ȯ
	int rightToad[] = { 35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50 };
	KEYANIMANAGER->addArrayFrameAnimation("�����ʼ�ȯ", "������", rightToad, 16, 5, false, rightAttack, this);
	int leftToad[] = { 96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111 };
	KEYANIMANAGER->addArrayFrameAnimation("���ʼ�ȯ", "������", leftToad, 16, 5, false, leftAttack, this);

	//���̱�
	int rightDuck[] = { 51,52 };
	KEYANIMANAGER->addArrayFrameAnimation("�����ʼ��̱�", "������", rightDuck, 2, 10, false);
	int leftDuck[] = { 112,113 };
	KEYANIMANAGER->addArrayFrameAnimation("���ʼ��̱�", "������", leftDuck, 2, 10, false);

	//���
	int rightSoftKick[] = { 53,54,55,56 };
	KEYANIMANAGER->addArrayFrameAnimation("�����ʾ��", "������", rightSoftKick, 4, 15, false, rightAttack, this);
	int leftSoftKick[] = { 114,115,116,117 };
	KEYANIMANAGER->addArrayFrameAnimation("���ʾ��", "������", leftSoftKick, 4, 15, false, leftAttack, this);

	//����
	int rightHardKick[] = { 57,58,59,60 };
	KEYANIMANAGER->addArrayFrameAnimation("�����ʰ���", "������", rightHardKick, 4, 5, false, rightAttack, this);
	int leftHardKick[] = { 118,119,120,121 };
	KEYANIMANAGER->addArrayFrameAnimation("���ʰ���", "������", leftHardKick, 4, 5, false, leftAttack, this);

	_player.currentHp = _player.maxHp = 100.0f;
	_player.gravity = 4.0f;
	_player.speed = 3.0f;
	_player.playerState = PLAYERSTATE_RIGHT_STOP;
	_player.x = 200;
	_player.y = WINSIZEY - 60;
	_player.rc = RectMakeCenter(_player.x, _player.y, 50, 50);
	_player.ani = KEYANIMANAGER->findAnimation("����������");
	_player.ani->start();
	_player.command = 0;
	_commandTime = 0;
	_toadTime = 0;
	_toad = false;

	_throwKnife = new throwKnife;
	_throwKnife->init(1, WINSIZEX);

	return S_OK;
}

void naruto::release()
{

}

void naruto::update()
{
	KEYANIMANAGER->update();
	move();
	inputKey();
	command();
	_throwKnife->update();
}

void naruto::render()
{
	//�̹��� �׷��ֱ�
	_player.img->aniRender(getMemDC(), _player.rc.left, _player.rc.top, _player.ani);
	if (_toad)_iToad->render(getMemDC(), 0, 0);
	_throwKnife->render();
}

void naruto::move()
{
	_player.rc = RectMakeCenter(_player.x, _player.y, 50, 50);
	//�����̱�
	switch (_player.playerState)
	{
	case PLAYERSTATE_RIGHT_MOVE:
		_player.x += _player.speed;
		break;
	case PLAYERSTATE_LEFT_MOVE:
		_player.x -= _player.speed;
		break;
	case PLAYERSTATE_RIGHT_RUN:
		_player.x += _player.speed * 1.5;
		break;
	case PLAYERSTATE_LEFT_RUN:
		_player.x -= _player.speed * 1.5;
		break;
	}
}

void naruto::attack()
{

}

void naruto::inputKey()
{
	///////////////////////////////////////////////////�������̵�
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_player.command += 1;
		if (_player.command == 2)
		{
			_player.playerState = PLAYERSTATE_RIGHT_RUN;
			_player.ani = KEYANIMANAGER->findAnimation("�����ʶٱ�");
			_player.ani->start();
		}
		else
		{
			_player.playerState = PLAYERSTATE_RIGHT_MOVE;
			_player.ani = KEYANIMANAGER->findAnimation("�������̵�");
			_player.ani->start();
		}
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_player.playerState = PLAYERSTATE_RIGHT_STOP;
		_player.ani = KEYANIMANAGER->findAnimation("����������");
		_player.ani->start();
		if (_player.playerState == PLAYERSTATE_RIGHT_RUN)
		{
			_player.command = 0;
			_player.timer = 0;
		}
	}
	/////////////////////////////////////////////////�����̵�
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_player.command += 2;
		if (_player.command == 4)
		{
			_player.playerState = PLAYERSTATE_LEFT_RUN;
			_player.ani = KEYANIMANAGER->findAnimation("���ʶٱ�");
			_player.ani->start();
		}
		else
		{
			_player.playerState = PLAYERSTATE_LEFT_MOVE;
			_player.ani = KEYANIMANAGER->findAnimation("�����̵�");
			_player.ani->start();
		}
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_player.playerState = PLAYERSTATE_LEFT_STOP;
		_player.ani = KEYANIMANAGER->findAnimation("��������");
		_player.ani->start();
		if (_player.playerState == PLAYERSTATE_RIGHT_RUN)
		{
			_player.command = 0;
			_player.timer = 0;
		}
	}
	////////////////////////////////////////////////////��հ���
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		playerManager::attack();
		_commandTime = 0;
		_player.command += 4;
		if (_player.playerState == PLAYERSTATE_RIGHT_STOP || _player.playerState == PLAYERSTATE_RIGHT_MOVE || _player.playerState == PLAYERSTATE_RIGHT_RUN)
		{
			if (_player.command == 16)
			{
				_player.playerState = PLAYERSTATE_RIGHT_SOFT_PUNCH;
				_player.ani = KEYANIMANAGER->findAnimation("�����ʹ�ġ��");
				_player.ani->start();
				_player.command = 0;
			}
			else
			{
				_player.playerState = PLAYERSTATE_RIGHT_SOFT_PUNCH;
				_player.ani = KEYANIMANAGER->findAnimation("�����ʾ��");
				_player.ani->start();
			}
		}
		else if (_player.playerState == PLAYERSTATE_LEFT_STOP || _player.playerState == PLAYERSTATE_LEFT_MOVE || _player.playerState == PLAYERSTATE_LEFT_RUN)
		{
			if (_player.command == 16)
			{
				_player.playerState = PLAYERSTATE_RIGHT_SOFT_PUNCH;
				_player.ani = KEYANIMANAGER->findAnimation("���ʹ�ġ��");
				_player.ani->start();
				_player.command = 0;
			}
			else
			{
				_player.playerState = PLAYERSTATE_LEFT_SOFT_PUNCH;
				_player.ani = KEYANIMANAGER->findAnimation("���ʾ��");
				_player.ani->start();
			}
		}
	}
	////////////////////////////////////////////////���հ���
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		playerManager::attack();
		_commandTime = 0;
		_player.command += 8;

		if (_player.playerState == PLAYERSTATE_RIGHT_STOP || _player.playerState == PLAYERSTATE_RIGHT_MOVE || _player.playerState == PLAYERSTATE_RIGHT_RUN)
		{
			if (_player.command == 25)
			{
				_commandTime = 0;
				_player.command = 0;
				_player.playerState = PLAYERSTATE_RIGHT_SKILL1;
				_player.ani = KEYANIMANAGER->findAnimation("��������ô");
				_player.ani->start();
				_throwKnife->fire(_player.x, _player.y, (int)_player.playerState);
			}
			else if (_player.command == 40)
			{
				_player.playerState = PLAYERSTATE_RIGHT_SKILL2;
				_player.ani = KEYANIMANAGER->findAnimation("�����ʼ�ȯ");
				_player.ani->start();
				_commandTime = 0;
				_player.command = 0;
			}
			else
			{
				_player.playerState = PLAYERSTATE_RIGHT_HARD_PUNCH;
				_player.ani = KEYANIMANAGER->findAnimation("�����ʰ���");
				_player.ani->start();
			}
		}
		else if (_player.playerState == PLAYERSTATE_LEFT_STOP || _player.playerState == PLAYERSTATE_LEFT_MOVE || _player.playerState == PLAYERSTATE_LEFT_RUN)
		{
			if (_player.command == 26)
			{
				_commandTime = 0;
				_player.command = 0;
				_player.playerState = PLAYERSTATE_LEFT_SKILL1;
				_player.ani = KEYANIMANAGER->findAnimation("������ô");
				_player.ani->start();
				_throwKnife->fire(_player.x, _player.y, (int)_player.playerState);
			}
			else if (_player.command == 40)
			{
				_commandTime = 0;
				_player.command = 0;
				_player.playerState = PLAYERSTATE_LEFT_SKILL2;
				_player.ani = KEYANIMANAGER->findAnimation("���ʼ�ȯ");
				_player.ani->start();
			}
			else
			{
				_player.playerState = PLAYERSTATE_LEFT_HARD_PUNCH;
				_player.ani = KEYANIMANAGER->findAnimation("���ʰ���");
				_player.ani->start();
			}
		}
	}
	////////////////////////////////////////////////////////////////////////��߰���
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		playerManager::attack();
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
	////////////////////////////////////////////////////////////////////////���߰���
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		playerManager::attack();
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
	/////////////////////////////////////////////////////////////////���̱�
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		_commandTime = 0;
		_player.command += 16;
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
			_player.ani = KEYANIMANAGER->findAnimation("��������");
			_player.ani->start();
		}
	}
}
void naruto::setPlayerAni()
{

}

void naruto::command()
{
	if (_player.command != 0)_commandTime++;
	if (_commandTime % 20 == 0)
	{
		_player.command = 0;
		_commandTime = 0;
	}
	if (_toad) _toadTime++;
	if (_toadTime % 50 == 0)
	{
		_toadTime = 0;
		_toad = false;
	}
}

void naruto::rightAttack(void* obj)
{
	naruto* n = (naruto*)obj;
	if (n->getPlayerMotion() == KEYANIMANAGER->findAnimation("�����ʼ�ȯ"))n->setToad(true);
	n->setPlayerState(PLAYERSTATE_RIGHT_STOP);
	n->_player.attackRange = RectMake(0, 0, 0, 0);
	n->setPlayerMotion(KEYANIMANAGER->findAnimation("����������"));
	n->getPlayerMotion()->start();
}

void naruto::leftAttack(void* obj)
{
	naruto* n = (naruto*)obj;
	if (n->getPlayerMotion() == KEYANIMANAGER->findAnimation("���ʼ�ȯ"))n->setToad(true);
	n->setPlayerState(PLAYERSTATE_LEFT_STOP);
	n->_player.attackRange = RectMake(0, 0, 0, 0);
	n->setPlayerMotion(KEYANIMANAGER->findAnimation("��������"));
	n->getPlayerMotion()->start();
}
