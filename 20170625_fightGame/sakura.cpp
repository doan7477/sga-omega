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
	//ÀÌ¹ÌÁö ÃÊ±âÈ­
	_player.img = IMAGEMANAGER->addFrameImage("»çÄí¶ó", "image/ÀÌÁö¿µ/sakura.bmp", 0, 0, 1656, 672, 18, 7, true, RGB(255, 0, 255));
	
	//ÀÌµ¿
	int leftMove[] = { 0,1,2,3 };
	KEYANIMANAGER->addArrayFrameAnimation("ÁÂÀÌµ¿", "»çÄí¶ó", leftMove, 4, 10, true);
	int rightMove[] = { 6,7,8,9 };
	KEYANIMANAGER->addArrayFrameAnimation("¿ìÀÌµ¿", "»çÄí¶ó", rightMove, 4, 10, true);

	//¼÷ÀÌ±â
	int leftDuck[] = { 12,13,14 };
	KEYANIMANAGER->addArrayFrameAnimation("ÁÂ¼÷ÀÌ±â", "»çÄí¶ó", leftDuck, 3, 10, true);
	int rightDuck[] = { 15,16,17 };
	KEYANIMANAGER->addArrayFrameAnimation("¿ì¼÷ÀÌ±â", "»çÄí¶ó", rightDuck, 3, 10, true);

	//¶Ù±â
	int leftDash[] = { 18,19,20,21,22 };
	KEYANIMANAGER->addArrayFrameAnimation("ÁÂ¶Ù±â", "»çÄí¶ó", leftDash, 5, 10, true);
	int rightDash[] = { 23,24,25,26,27 };
	KEYANIMANAGER->addArrayFrameAnimation("¿ì¶Ù±â", "»çÄí¶ó", rightDash, 5, 10, true);

	//¾à¼Õ
	int leftSoftPunch[] = { 28,29,30 };
	KEYANIMANAGER->addArrayFrameAnimation("ÁÂ¾à¼Õ", "»çÄí¶ó", leftSoftPunch, 3, 10, true, leftFire, this);
	int rightSoftPunch[] = { 31,32,33 };
	KEYANIMANAGER->addArrayFrameAnimation("¿ì¾à¼Õ", "»çÄí¶ó", rightSoftPunch, 3, 10, true, rightFire, this);

	//Á¤Áö
	int leftStop[] = { 36,37,38,39,40,41 };
	KEYANIMANAGER->addArrayFrameAnimation("ÁÂÁ¤Áö", "»çÄí¶ó", leftStop, 6, 10, true);
	int rightStop[] = { 42,43,44,45,46,47 };
	KEYANIMANAGER->addArrayFrameAnimation("¿ìÁ¤Áö", "»çÄí¶ó", rightStop, 6, 10, true);

	//Á¡ÇÁ
	int leftJump[] = { 54,55,56,57,58,59,60,61,62 };
	KEYANIMANAGER->addArrayFrameAnimation("ÁÂÁ¡ÇÁ", "»çÄí¶ó", leftStop, 9, 10, true);
	int rightJump[] = { 63,64,65,66,67,68,69,70,71 };
	KEYANIMANAGER->addArrayFrameAnimation("¿ìÁ¡ÇÁ", "»çÄí¶ó", rightStop, 9, 10, true);

	//°­¼Õ
	int leftStrongPunch[] = { 72,73,74,75,76,77,78 };
	KEYANIMANAGER->addArrayFrameAnimation("ÁÂ°­¼Õ", "»çÄí¶ó", leftStrongPunch, 7, 10, true, leftFire, this);
	int rightStrongPunch[] = { 79,80,81,82,83,84,85 };
	KEYANIMANAGER->addArrayFrameAnimation("¿ì°­¼Õ", "»çÄí¶ó", rightStrongPunch, 7, 10, true, rightFire, this);

	//¹ßÂ÷±â
	int leftKick[] = { 90,91,92,93,94 };
	KEYANIMANAGER->addArrayFrameAnimation("ÁÂ¹ß", "»çÄí¶ó", leftKick, 5, 10, true, leftFire, this);
	int rightKick[] = { 95,96,97,98,99 };
	KEYANIMANAGER->addArrayFrameAnimation("¿ì¹ß", "»çÄí¶ó", rightKick, 5, 10, true, rightFire, this);

	//±â¸ğÀ¸±â
	int leftSkill1[] = { 100,101,102,103 };
	KEYANIMANAGER->addArrayFrameAnimation("ÁÂ±â¸ğÀ¸±â", "»çÄí¶ó", leftSkill1, 4, 10, true);
	int rightSkill1[] = { 104,105,106,107 };
	KEYANIMANAGER->addArrayFrameAnimation("¿ì±â¸ğÀ¸±â", "»çÄí¶ó", rightSkill1, 4, 10, true);

	//Ç¥Ã¢´øÁö±â
	int leftSkill2[] = { 108,109,110 };
	KEYANIMANAGER->addArrayFrameAnimation("ÁÂÇ¥Ã¢´øÁö±â", "»çÄí¶ó", leftSkill2, 3, 10, true);
	int rightSkill2[] = { 111,112,113 };
	KEYANIMANAGER->addArrayFrameAnimation("¿ìÇ¥Ã¢´øÁö±â", "»çÄí¶ó", rightSkill2, 3, 10, true);

	//64¿¬Å¸
	int leftSkill3[] = { 114,115,116,117,118,119 };
	KEYANIMANAGER->addArrayFrameAnimation("ÁÂ¿¬Å¸", "»çÄí¶ó", leftSkill3, 6, 10, true);
	int rightSkill3[] = { 120,121,122,123,124,125 };
	KEYANIMANAGER->addArrayFrameAnimation("¿ì¿¬Å¸", "»çÄí¶ó", rightSkill3, 6, 10, true);

	_player.currentHp = _player.maxHp = 100.0f;
	_player.gravity = 5.0f;
	_player.speed = 3.0f;
	_player.playerState = PLAYERSTATE_RIGHT_STOP;
	_player.x = 200;
	_player.y = WINSIZEY - 50;
	_player.rc = RectMakeCenter(_player.x, _player.y, 50, 50);
	_player.ani = KEYANIMANAGER->findAnimation("¿ìÁ¤Áö");

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
	//ÇÃ·¹ÀÌ¾î »óÅÂ¿¡ µû¶ó ¿òÁ÷ÀÓ ¼³Á¤ÇÏ±â
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
	//ÀÌµ¿
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_player.playerState = PLAYERSTATE_LEFT_MOVE;
		_player.ani = KEYANIMANAGER->findAnimation("ÁÂÀÌµ¿");
		_player.ani->start();
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_player.playerState = PLAYERSTATE_LEFT_STOP;
		_player.ani = KEYANIMANAGER->findAnimation("ÁÂÁ¤Áö");
		_player.ani->start();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_player.playerState = PLAYERSTATE_RIGHT_MOVE;
		_player.ani = KEYANIMANAGER->findAnimation("¿ìÀÌµ¿");
		_player.ani->start();
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_player.playerState = PLAYERSTATE_RIGHT_STOP;
		_player.ani = KEYANIMANAGER->findAnimation("¿ìÁ¤Áö");
		_player.ani->start();
	}

	//Á¡ÇÁ
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (_player.playerState == PLAYERSTATE_RIGHT_STOP || _player.playerState == PLAYERSTATE_RIGHT_RUN || _player.playerState == PLAYERSTATE_RIGHT_MOVE)
		{
			_player.playerState = PLAYERSTATE_RIGHT_JUMP;
			_player.ani = KEYANIMANAGER->findAnimation("¿ìÁ¡ÇÁ");
			_player.ani->start();
		}
		else if (_player.playerState == PLAYERSTATE_LEFT_STOP || _player.playerState == PLAYERSTATE_LEFT_RUN || _player.playerState == PLAYERSTATE_LEFT_MOVE)
		{
			_player.playerState = PLAYERSTATE_LEFT_JUMP;
			_player.ani = KEYANIMANAGER->findAnimation("¿ŞÁ¡ÇÁ");
			_player.ani->start();
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		if (_player.playerState == PLAYERSTATE_RIGHT_JUMP)
		{
			_player.playerState = PLAYERSTATE_RIGHT_STOP;
			_player.ani = KEYANIMANAGER->findAnimation("¿ìÁ¤Áö");
			_player.ani->start();
		}
		if (_player.playerState == PLAYERSTATE_LEFT_JUMP)
		{
			_player.playerState = PLAYERSTATE_LEFT_STOP;
			_player.ani = KEYANIMANAGER->findAnimation("¿ŞÁ¤Áö");
			_player.ani->start();
		}
	}
	//¼÷ÀÌ±â
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		if (_player.playerState == PLAYERSTATE_RIGHT_STOP || _player.playerState == PLAYERSTATE_RIGHT_RUN || _player.playerState == PLAYERSTATE_RIGHT_MOVE)
		{
			_player.playerState = PLAYERSTATE_RIGHT_DUCK;
			_player.ani = KEYANIMANAGER->findAnimation("¿ì¼÷ÀÌ±â");
			_player.ani->start();
		}
		else if (_player.playerState == PLAYERSTATE_LEFT_STOP || _player.playerState == PLAYERSTATE_LEFT_RUN || _player.playerState == PLAYERSTATE_LEFT_MOVE)
		{
			_player.playerState = PLAYERSTATE_LEFT_DUCK;
			_player.ani = KEYANIMANAGER->findAnimation("ÁÂ¼÷ÀÌ±â");
			_player.ani->start();
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		if (_player.playerState == PLAYERSTATE_RIGHT_DUCK)
		{
			_player.playerState = PLAYERSTATE_RIGHT_STOP;
			_player.ani = KEYANIMANAGER->findAnimation("¿ìÁ¤Áö");
			_player.ani->start();
		}
		if (_player.playerState == PLAYERSTATE_LEFT_DUCK)
		{
			_player.playerState = PLAYERSTATE_LEFT_STOP;
			_player.ani = KEYANIMANAGER->findAnimation("¿ŞÁ¤Áö");
			_player.ani->start();
		}
	}
	//¾à¼Õ
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		playerManager::attack();
		if (_player.playerState == PLAYERSTATE_RIGHT_STOP || _player.playerState == PLAYERSTATE_RIGHT_RUN || _player.playerState == PLAYERSTATE_RIGHT_MOVE)
		{
			_player.playerState = PLAYERSTATE_RIGHT_SOFT_PUNCH;
			_player.ani = KEYANIMANAGER->findAnimation("¿ì¾à¼Õ");
			_player.ani->start();
		}
		else if (_player.playerState == PLAYERSTATE_LEFT_STOP || _player.playerState == PLAYERSTATE_LEFT_RUN || _player.playerState == PLAYERSTATE_LEFT_MOVE)
		{
			_player.playerState = PLAYERSTATE_LEFT_SOFT_PUNCH;
			_player.ani = KEYANIMANAGER->findAnimation("ÁÂ¾à¼Õ");
			_player.ani->start();
		}
	}
	//°­¼Õ
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		playerManager::attack();
		if (_player.playerState == PLAYERSTATE_RIGHT_STOP || _player.playerState == PLAYERSTATE_RIGHT_RUN || _player.playerState == PLAYERSTATE_RIGHT_MOVE)
		{
			_player.playerState = PLAYERSTATE_RIGHT_HARD_PUNCH;
			_player.ani = KEYANIMANAGER->findAnimation("¿ì°­¼Õ");
			_player.ani->start();
		}
		else if (_player.playerState == PLAYERSTATE_LEFT_STOP || _player.playerState == PLAYERSTATE_LEFT_RUN || _player.playerState == PLAYERSTATE_LEFT_MOVE)
		{
			_player.playerState = PLAYERSTATE_LEFT_HARD_PUNCH;
			_player.ani = KEYANIMANAGER->findAnimation("ÁÂ°­¼Õ");
			_player.ani->start();
		}
	}
	//¾à¹ß
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		playerManager::attack();
		if (_player.playerState == PLAYERSTATE_RIGHT_STOP || _player.playerState == PLAYERSTATE_RIGHT_RUN || _player.playerState == PLAYERSTATE_RIGHT_MOVE)
		{
			_player.playerState = PLAYERSTATE_RIGHT_SOFT_KICK;
			_player.ani = KEYANIMANAGER->findAnimation("¿ì¹ß");
			_player.ani->start();
		}
		else if (_player.playerState == PLAYERSTATE_LEFT_STOP || _player.playerState == PLAYERSTATE_LEFT_RUN || _player.playerState == PLAYERSTATE_LEFT_MOVE)
		{
			_player.playerState = PLAYERSTATE_LEFT_SOFT_KICK;
			_player.ani = KEYANIMANAGER->findAnimation("ÁÂ¹ß");
			_player.ani->start();
		}
	}
	//»çÄí¶ó´Â °­¹ßµûÀ§´Â ¾ø´Ù.
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
	s->setPlayerMotion(KEYANIMANAGER->findAnimation("¿ìÁ¤Áö"));
	s->getPlayerAttackRange() = RectMake(0, 0, 0, 0);
	s->getPlayerMotion()->start();
}

void sakura::leftFire(void* obj)
{
	sakura* s = (sakura*)obj;
	s->setPlayerState(PLAYERSTATE_LEFT_STOP);
	s->setPlayerMotion(KEYANIMANAGER->findAnimation("¿ŞÁ¤Áö"));
	s->getPlayerAttackRange() = RectMake(0, 0, 0, 0);
	s->getPlayerMotion()->start();
}