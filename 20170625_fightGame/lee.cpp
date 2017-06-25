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

	_commandCount = 0;
	_commandTimer = 0;
	_commandStart = false;

	_player.img = IMAGEMANAGER->addFrameImage("�ϸ�", "image/�ѵ���/lee.bmp", 0, 0, 4050, 132, 50, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����ȱ������", "image/�ѵ���/special2-1.bmp", 1364, 130, 22, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����ȱ���ߵ�", "image/�ѵ���/special2-2.bmp", 1470, 96, 10, 2, true, RGB(255, 0, 255));

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
	KEYANIMANAGER->addArrayFrameAnimation("�����ʾ��", "�ϸ�", rightSoftPuch, 3, 10, false, rightFire, this);
	int leftSoftPuch[] = { 70,71,72 };
	KEYANIMANAGER->addArrayFrameAnimation("���ʾ��", "�ϸ�", leftSoftPuch, 3, 10, false, leftFire, this);

	//����
	int rightHardPuch[] = { 23,24,25,26 };
	KEYANIMANAGER->addArrayFrameAnimation("�����ʰ���", "�ϸ�", rightHardPuch, 4, 10, false, rightFire, this);
	int leftHardPuch[] = { 73,74,75,76 };
	KEYANIMANAGER->addArrayFrameAnimation("���ʰ���", "�ϸ�", leftHardPuch, 4, 10, false, leftFire, this);

	//���
	int rightSoftKick[] = { 27,28,29,30,31,32 };
	KEYANIMANAGER->addArrayFrameAnimation("�����ʾ��", "�ϸ�", rightSoftKick, 6, 10, false, rightFire, this);
	int leftSoftKick[] = { 77,78,79,80,81,82 };
	KEYANIMANAGER->addArrayFrameAnimation("���ʾ��", "�ϸ�", leftSoftKick, 6, 10, false, leftFire, this);

	//����
	int rightHardKick[] = { 42,43,44,45,46,47,48,49 };
	KEYANIMANAGER->addArrayFrameAnimation("�����ʰ���", "�ϸ�", rightHardKick, 8, 10, false, rightFire, this);
	int leftHardKick[] = { 92,93,94,95,96,97,98,99 };
	KEYANIMANAGER->addArrayFrameAnimation("���ʰ���", "�ϸ�", leftHardKick, 8, 10, false, leftFire, this);

	//Ŀ�ǵ�1
	int rightCommand1[] = { 39,40,41 };
	KEYANIMANAGER->addArrayFrameAnimation("������Ŀ�ǵ�1", "�ϸ�", rightCommand1, 3, 5, false, rightFire, this);
	int leftCommand1[] = { 89,90,91 };
	KEYANIMANAGER->addArrayFrameAnimation("����Ŀ�ǵ�1", "�ϸ�", leftCommand1, 3, 5, false, leftFire, this);

	//Ŀ�ǵ�2
	int rightCommand2[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21 };
	KEYANIMANAGER->addArrayFrameAnimation("������Ŀ�ǵ�2", "����ȱ������", rightCommand2, 22, 3, false, rightFinish, this);
	int leftCommand2[] = { 22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43 };
	KEYANIMANAGER->addArrayFrameAnimation("����Ŀ�ǵ�2", "����ȱ������", leftCommand2, 22, 3, false, leftFinish, this);

	//Ŀ�ǵ�3
	int rightCommand3[] = { 0,1,2,3,4,5,6,7,8,9 };
	KEYANIMANAGER->addArrayFrameAnimation("������Ŀ�ǵ�3", "����ȱ���ߵ�", rightCommand3, 10, 5, false, rightFire, this);
	int leftCommand3[] = { 10,11,12,13,14,15,16,17,18,19 };
	KEYANIMANAGER->addArrayFrameAnimation("����Ŀ�ǵ�3", "����ȱ���ߵ�", leftCommand3, 10, 5, false, leftFire, this);


	_player.currentHp = _player.maxHp = 100.0f;
	_player.gravity = 4.0f;
	_player.speed = 4.0f;
	_player.playerState = PLAYERSTATE_RIGHT_STOP;
	_player.x = 200;
	_player.y = WINSIZEY - 60;
	_player.rc = RectMakeCenter(_player.x, _player.y, 50, 50);
	_player.ani = KEYANIMANAGER->findAnimation("����������");
	_player.hpBar = new progressBar;
	_player.hpBar->init(50, 50, 300, 30);
	_player.hpBar->setGauge(_player.currentHp, _player.maxHp);


	return S_OK;
}
void lee::release()
{

}
void lee::update()
{
	if (_player.playerState == PLAYERSTATE_LEFT_COMMAND2 || _player.playerState == PLAYERSTATE_RIGHT_COMMAND2)
	{
		_player.img = IMAGEMANAGER->findImage("����ȱ������");
	}
	else if (_player.playerState == PLAYERSTATE_LEFT_COMMAND3 || _player.playerState == PLAYERSTATE_RIGHT_COMMAND3)
	{
		_player.img = IMAGEMANAGER->findImage("����ȱ���ߵ�");
	}
	else _player.img = IMAGEMANAGER->findImage("�ϸ�");

	KEYANIMANAGER->update();
	inputKey();
	move();
	if (_player.isJump)
	{
		_player.gravity -= 0.1f;
	}
	_player.hpBar->update();
	command();
}
void lee::render()
{
	_player.hpBar->render();
	//Rectangle(getMemDC(), _player.rc.left, _player.rc.top, _player.rc.right, _player.rc.bottom);
	if (_player.img == IMAGEMANAGER->findImage("����ȱ���ߵ�"))
	{
		_player.img->aniRender(getMemDC(), _player.rc.left, _player.rc.top + 13, _player.ani);
	}
	else _player.img->aniRender(getMemDC(), _player.rc.left, _player.rc.top, _player.ani);
	Rectangle(getMemDC(), _player.attackRange.left, _player.attackRange.top, _player.attackRange.right, _player.attackRange.bottom);

	char str[256];
	string frameRate;
	SetBkMode(getMemDC(), TRANSPARENT);
	sprintf_s(str, "Ŀ�ǵ�ī��Ʈ : %d", _commandCount);
	TextOut(getMemDC(), 0, 60, str, strlen(str));

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
		_player.x += 1.5 * _player.speed;
		break;
	case PLAYERSTATE_LEFT_RUN:
		_player.x -= 1.5 * _player.speed;
		break;
	case PLAYERSTATE_RIGHT_JUMP:
		_player.x += 2.0f;
		_player.y -= _player.gravity;
		break;
	case PLAYERSTATE_LEFT_JUMP:
		_player.x -= 2.0f;
		_player.y -= _player.gravity;
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
	case PLAYERSTATE_RIGHT_COMMAND3:
		_player.x += 5.2f;
		break;
	case PLAYERSTATE_LEFT_COMMAND3:
		_player.x -= 5.2f;
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
		_commandStart = true;
		_commandCount += 1;
		if (_commandTimer >= 2)
		{
			_player.playerState = PLAYERSTATE_RIGHT_RUN;
			_player.ani = KEYANIMANAGER->findAnimation("�����ʶٱ�");
			_player.ani->start();
		}
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_player.playerState = PLAYERSTATE_RIGHT_STOP;
		_player.ani = KEYANIMANAGER->findAnimation("����������");
		_player.ani->start();
		//�޸��� �ִ� ���̰� Ű�� ������
		if (_player.playerState == PLAYERSTATE_RIGHT_RUN)
		{
			_commandTimer = 0;
			_commandStart = false;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_player.playerState = PLAYERSTATE_LEFT_MOVE;
		_player.ani = KEYANIMANAGER->findAnimation("�����̵�");
		_player.ani->start();
		_commandStart = true;
		_commandCount += 11;
		if (_commandTimer >= 2)
		{
			_player.playerState = PLAYERSTATE_LEFT_RUN;
			_player.ani = KEYANIMANAGER->findAnimation("���ʶٱ�");
			_player.ani->start();
		}
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_player.playerState = PLAYERSTATE_LEFT_STOP;
		_player.ani = KEYANIMANAGER->findAnimation("��������");
		_player.ani->start();
		//�޸��� �ִ� ���̰� Ű�� ������
		if (_player.playerState == PLAYERSTATE_LEFT_RUN)
		{
			_commandStart = false;
			_commandTimer = 0;
		}
	}
	//����
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		_player.gravity = 4.0f;
		_player.isJump = true;
		_commandStart = true;
		_commandCount += 21;
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
	/*if (KEYMANAGER->isOnceKeyUp(VK_UP))
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
	}*/
	//���̱�
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		if (_player.playerState == PLAYERSTATE_RIGHT_STOP || _player.playerState == PLAYERSTATE_RIGHT_RUN || _player.playerState == PLAYERSTATE_RIGHT_MOVE)
		{
			_player.playerState = PLAYERSTATE_RIGHT_DUCK;
			_player.ani = KEYANIMANAGER->findAnimation("�����ʼ��̱�");
			_player.ani->start();
			_commandStart = true;
			_commandCount += 31;
		}
		else if (_player.playerState == PLAYERSTATE_LEFT_STOP || _player.playerState == PLAYERSTATE_LEFT_RUN || _player.playerState == PLAYERSTATE_LEFT_MOVE)
		{
			_player.playerState = PLAYERSTATE_LEFT_DUCK;
			_player.ani = KEYANIMANAGER->findAnimation("���ʼ��̱�");
			_player.ani->start();
			_commandStart = true;
			_commandCount += 31;
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
		else if (_player.playerState == PLAYERSTATE_LEFT_DUCK)
		{
			_player.playerState = PLAYERSTATE_LEFT_STOP;
			_player.ani = KEYANIMANAGER->findAnimation("��������");
			_player.ani->start();
		}
		else;
	}
	//���
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		playerManager::attack();
		if (_player.playerState == PLAYERSTATE_RIGHT_STOP || _player.playerState == PLAYERSTATE_RIGHT_RUN || _player.playerState == PLAYERSTATE_RIGHT_MOVE)
		{
			if (_commandCount >= 63)
			{
				_player.playerState = PLAYERSTATE_RIGHT_COMMAND1;
				_player.ani = KEYANIMANAGER->findAnimation("������Ŀ�ǵ�1");
				_player.ani->start();
			}
			else
			{
				_player.playerState = PLAYERSTATE_RIGHT_SOFT_PUNCH;
				_player.ani = KEYANIMANAGER->findAnimation("�����ʾ��");
				_player.ani->start();
			}
		}
		else if (_player.playerState == PLAYERSTATE_LEFT_STOP || _player.playerState == PLAYERSTATE_LEFT_RUN || _player.playerState == PLAYERSTATE_LEFT_MOVE)
		{
			if (_commandCount >= 73)
			{
				_player.playerState = PLAYERSTATE_LEFT_COMMAND1;
				_player.ani = KEYANIMANAGER->findAnimation("����Ŀ�ǵ�1");
				_player.ani->start();
			}
			else
			{
				_player.playerState = PLAYERSTATE_LEFT_SOFT_PUNCH;
				_player.ani = KEYANIMANAGER->findAnimation("���ʾ��");
				_player.ani->start();
			}
		}
	}
	//����
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		playerManager::attack();
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
		playerManager::attack();
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
		playerManager::attack();
		if (_player.playerState == PLAYERSTATE_RIGHT_STOP || _player.playerState == PLAYERSTATE_RIGHT_RUN || _player.playerState == PLAYERSTATE_RIGHT_MOVE)
		{
			if (_commandCount >= 74)
			{
				_player.playerState = PLAYERSTATE_RIGHT_COMMAND2;
				_player.ani = KEYANIMANAGER->findAnimation("������Ŀ�ǵ�2");
				_player.ani->start();
			}
			else
			{
				_player.playerState = PLAYERSTATE_RIGHT_HARD_KICK;
				_player.ani = KEYANIMANAGER->findAnimation("�����ʰ���");
				_player.ani->start();
			}
		}
		else if (_player.playerState == PLAYERSTATE_LEFT_STOP || _player.playerState == PLAYERSTATE_LEFT_RUN || _player.playerState == PLAYERSTATE_LEFT_MOVE)
		{
			if (_commandCount >= 74)
			{
				_player.playerState = PLAYERSTATE_LEFT_COMMAND2;
				_player.ani = KEYANIMANAGER->findAnimation("����Ŀ�ǵ�2");
				_player.ani->start();
			}
			else
			{
				_player.playerState = PLAYERSTATE_LEFT_HARD_KICK;
				_player.ani = KEYANIMANAGER->findAnimation("���ʰ���");
				_player.ani->start();
			}
		}
	}
}

void lee::setPlayerAni()
{

}

void lee::command()
{
	//Ŀ�ǵ� �Ұ� ������ 
	if (_commandStart)
	{
		//Ŀ��Ʈ Ÿ�̸� ����
		_commandTimer++;
	}
	//ĳ�ǵ� Ÿ�̸� ����ġ ������ �Ұ� �ʱ�ȭ
	if (_commandTimer > 20)
	{
		_commandStart = false;
		_commandCount = 0;
		_commandTimer = 0;
	}
}

void lee::rightFire(void* obj)
{
	lee* l = (lee*)obj;
	l->setPlayerState(PLAYERSTATE_RIGHT_STOP);
	l->setPlayerMotion(KEYANIMANAGER->findAnimation("����������"));
	l->_player.attackRange = RectMake(0, 0, 0, 0);
	l->getPlayerMotion()->start();
}

void lee::leftFire(void* obj)
{
	lee* l = (lee*)obj;
	l->setPlayerState(PLAYERSTATE_LEFT_STOP);
	l->setPlayerMotion(KEYANIMANAGER->findAnimation("��������"));
	l->_player.attackRange = RectMake(0, 0, 0, 0);
	l->getPlayerMotion()->start();
}

void lee::rightFinish(void* obj)
{
	lee* l = (lee*)obj;
	l->setPlayerState(PLAYERSTATE_RIGHT_COMMAND3);
	l->setPlayerMotion(KEYANIMANAGER->findAnimation("������Ŀ�ǵ�3"));
	l->_player.attackRange = RectMake(0, 0, 0, 0);
	l->getPlayerMotion()->start();
}
void lee::leftFinish(void* obj)
{
	lee* l = (lee*)obj;
	l->setPlayerState(PLAYERSTATE_LEFT_COMMAND3);
	l->setPlayerMotion(KEYANIMANAGER->findAnimation("����Ŀ�ǵ�3"));
	l->_player.attackRange = RectMake(0, 0, 0, 0);
	l->getPlayerMotion()->start();
}

void lee::pixelCollision()
{
	if (!PIXELMANAGER->playerLWall(_player.img, _player.x, _player.y, IMAGEMANAGER->findImage("�ȼ�����")))
	{

	}
	if (PIXELMANAGER->getPixelCollisionY(_player.img, _player.x, _player.y, IMAGEMANAGER->findImage("�ȼ�����")))
	{
		_player.isJump = false;
	}
}