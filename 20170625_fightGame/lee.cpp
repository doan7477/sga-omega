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
	//상속받고 init에 이런식으로 초기화 해주기

	_commandCount = 0;
	_commandTimer = 0;
	_commandStart = false;

	_player.img = IMAGEMANAGER->addFrameImage("록리", "image/한도안/lee.bmp", 0, 0, 4050, 132, 50, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("스페셜기술시전", "image/한도안/special2-1.bmp", 1364, 130, 22, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("스페셜기술발동", "image/한도안/special2-2.bmp", 1470, 96, 10, 2, true, RGB(255, 0, 255));

	//이동
	int rightMove[] = { 33,34,35,36,37,38 };
	KEYANIMANAGER->addArrayFrameAnimation("오른쪽이동", "록리", rightMove, 6, 6, true);
	int leftMove[] = { 83,84,85,86,87,88 };
	KEYANIMANAGER->addArrayFrameAnimation("왼쪽이동", "록리", leftMove, 6, 6, true);

	//뛰기
	int rightRun[] = { 6,7,8,9,10,11 };
	KEYANIMANAGER->addArrayFrameAnimation("오른쪽뛰기", "록리", rightRun, 6, 6, true);
	int leftRun[] = { 56,57,58,59,60,61 };
	KEYANIMANAGER->addArrayFrameAnimation("왼쪽뛰기", "록리", leftRun, 6, 6, true);

	//스톱
	int rightStop[] = { 0,1,2,3,4,5 };
	KEYANIMANAGER->addArrayFrameAnimation("오른쪽정지", "록리", rightStop, 6, 6, true);
	int leftStop[] = { 50,51,52,53,54,55 };
	KEYANIMANAGER->addArrayFrameAnimation("왼쪽정지", "록리", leftStop, 6, 6, true);

	//숙이기
	int rightDuck[] = { 12,13,14,15,16 };
	KEYANIMANAGER->addArrayFrameAnimation("오른쪽숙이기", "록리", rightDuck, 5, 10, false);
	int leftDuck[] = { 62,63,64,65,66 };
	KEYANIMANAGER->addArrayFrameAnimation("왼쪽숙이기", "록리", leftDuck, 5, 10, false);

	//점프
	int rightJump[] = { 17,18,19 };
	KEYANIMANAGER->addArrayFrameAnimation("오른쪽점프", "록리", rightJump, 3, 10, false);
	int leftJump[] = { 67,68,69 };
	KEYANIMANAGER->addArrayFrameAnimation("왼쪽점프", "록리", leftJump, 3, 10, false);

	//약손
	int rightSoftPuch[] = { 20,21,22 };
	KEYANIMANAGER->addArrayFrameAnimation("오른쪽약손", "록리", rightSoftPuch, 3, 10, false, rightFire, this);
	int leftSoftPuch[] = { 70,71,72 };
	KEYANIMANAGER->addArrayFrameAnimation("왼쪽약손", "록리", leftSoftPuch, 3, 10, false, leftFire, this);

	//강손
	int rightHardPuch[] = { 23,24,25,26 };
	KEYANIMANAGER->addArrayFrameAnimation("오른쪽강손", "록리", rightHardPuch, 4, 10, false, rightFire, this);
	int leftHardPuch[] = { 73,74,75,76 };
	KEYANIMANAGER->addArrayFrameAnimation("왼쪽강손", "록리", leftHardPuch, 4, 10, false, leftFire, this);

	//약발
	int rightSoftKick[] = { 27,28,29,30,31,32 };
	KEYANIMANAGER->addArrayFrameAnimation("오른쪽약발", "록리", rightSoftKick, 6, 10, false, rightFire, this);
	int leftSoftKick[] = { 77,78,79,80,81,82 };
	KEYANIMANAGER->addArrayFrameAnimation("왼쪽약발", "록리", leftSoftKick, 6, 10, false, leftFire, this);

	//강발
	int rightHardKick[] = { 42,43,44,45,46,47,48,49 };
	KEYANIMANAGER->addArrayFrameAnimation("오른쪽강발", "록리", rightHardKick, 8, 10, false, rightFire, this);
	int leftHardKick[] = { 92,93,94,95,96,97,98,99 };
	KEYANIMANAGER->addArrayFrameAnimation("왼쪽강발", "록리", leftHardKick, 8, 10, false, leftFire, this);

	//커맨드1
	int rightCommand1[] = { 39,40,41 };
	KEYANIMANAGER->addArrayFrameAnimation("오른쪽커맨드1", "록리", rightCommand1, 3, 5, false, rightFire, this);
	int leftCommand1[] = { 89,90,91 };
	KEYANIMANAGER->addArrayFrameAnimation("왼쪽커맨드1", "록리", leftCommand1, 3, 5, false, leftFire, this);

	//커맨드2
	int rightCommand2[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21 };
	KEYANIMANAGER->addArrayFrameAnimation("오른쪽커맨드2", "스페셜기술시전", rightCommand2, 22, 3, false, rightFinish, this);
	int leftCommand2[] = { 22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43 };
	KEYANIMANAGER->addArrayFrameAnimation("왼쪽커맨드2", "스페셜기술시전", leftCommand2, 22, 3, false, leftFinish, this);

	//커맨드3
	int rightCommand3[] = { 0,1,2,3,4,5,6,7,8,9 };
	KEYANIMANAGER->addArrayFrameAnimation("오른쪽커맨드3", "스페셜기술발동", rightCommand3, 10, 5, false, rightFire, this);
	int leftCommand3[] = { 10,11,12,13,14,15,16,17,18,19 };
	KEYANIMANAGER->addArrayFrameAnimation("왼쪽커맨드3", "스페셜기술발동", leftCommand3, 10, 5, false, leftFire, this);


	_player.currentHp = _player.maxHp = 100.0f;
	_player.gravity = 4.0f;
	_player.speed = 4.0f;
	_player.playerState = PLAYERSTATE_RIGHT_STOP;
	_player.x = 200;
	_player.y = WINSIZEY - 60;
	_player.rc = RectMakeCenter(_player.x, _player.y, 50, 50);
	_player.ani = KEYANIMANAGER->findAnimation("오른쪽정지");
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
		_player.img = IMAGEMANAGER->findImage("스페셜기술시전");
	}
	else if (_player.playerState == PLAYERSTATE_LEFT_COMMAND3 || _player.playerState == PLAYERSTATE_RIGHT_COMMAND3)
	{
		_player.img = IMAGEMANAGER->findImage("스페셜기술발동");
	}
	else _player.img = IMAGEMANAGER->findImage("록리");

	KEYANIMANAGER->update();
	inputKey();
	move();
	if (_player.isJump)
	{
		_player.gravity -= 0.1f;
	}
	_player.hpBar->update();
	command();
	playerManager::pixelCollision();
}
void lee::render()
{
	_player.hpBar->render();
	//Rectangle(getMemDC(), _player.rc.left, _player.rc.top, _player.rc.right, _player.rc.bottom);
	if (_player.img == IMAGEMANAGER->findImage("스페셜기술발동"))
	{
		_player.img->aniRender(getMemDC(), _player.rc.left, _player.rc.top + 13, _player.ani);
	}
	else _player.img->aniRender(getMemDC(), _player.rc.left, _player.rc.top, _player.ani);
	Rectangle(getMemDC(), _player.attackRange.left, _player.attackRange.top, _player.attackRange.right, _player.attackRange.bottom);

	char str[256];
	string frameRate;
	SetBkMode(getMemDC(), TRANSPARENT);
	sprintf_s(str, "커맨드카운트 : %d", _commandCount);
	TextOut(getMemDC(), 0, 60, str, strlen(str));

}

void lee::attack()
{
	
}

void lee::move()
{
	_player.rc = RectMakeCenter(_player.x, _player.y, 50, 50);
	//플레이어 상태에 따라 움직임 설정하기
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
	//키 입력
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_player.playerState = PLAYERSTATE_RIGHT_MOVE;
		_player.ani = KEYANIMANAGER->findAnimation("오른쪽이동");
		_player.ani->start();
		_commandStart = true;
		_commandCount += 1;
		if (_commandTimer >= 2)
		{
			_player.playerState = PLAYERSTATE_RIGHT_RUN;
			_player.ani = KEYANIMANAGER->findAnimation("오른쪽뛰기");
			_player.ani->start();
		}
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_player.playerState = PLAYERSTATE_RIGHT_STOP;
		_player.ani = KEYANIMANAGER->findAnimation("오른쪽정지");
		_player.ani->start();
		//달리고 있는 중이고 키를 땠을때
		if (_player.playerState == PLAYERSTATE_RIGHT_RUN)
		{
			_commandTimer = 0;
			_commandStart = false;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_player.playerState = PLAYERSTATE_LEFT_MOVE;
		_player.ani = KEYANIMANAGER->findAnimation("왼쪽이동");
		_player.ani->start();
		_commandStart = true;
		_commandCount += 11;
		if (_commandTimer >= 2)
		{
			_player.playerState = PLAYERSTATE_LEFT_RUN;
			_player.ani = KEYANIMANAGER->findAnimation("왼쪽뛰기");
			_player.ani->start();
		}
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_player.playerState = PLAYERSTATE_LEFT_STOP;
		_player.ani = KEYANIMANAGER->findAnimation("왼쪽정지");
		_player.ani->start();
		//달리고 있는 중이고 키를 땠을때
		if (_player.playerState == PLAYERSTATE_LEFT_RUN)
		{
			_commandStart = false;
			_commandTimer = 0;
		}
	}
	//점프
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		_player.gravity = 4.0f;
		_player.isJump = true;
		_commandStart = true;
		_commandCount += 21;
		if (_player.playerState == PLAYERSTATE_RIGHT_STOP || _player.playerState == PLAYERSTATE_RIGHT_RUN || _player.playerState == PLAYERSTATE_RIGHT_MOVE)
		{
			_player.playerState = PLAYERSTATE_RIGHT_JUMP;
			_player.ani = KEYANIMANAGER->findAnimation("오른쪽점프");
			_player.ani->start();
		}
		else if (_player.playerState == PLAYERSTATE_LEFT_STOP || _player.playerState == PLAYERSTATE_LEFT_RUN || _player.playerState == PLAYERSTATE_LEFT_MOVE)
		{
			_player.playerState = PLAYERSTATE_LEFT_JUMP;
			_player.ani = KEYANIMANAGER->findAnimation("왼쪽점프");
			_player.ani->start();
		}
	}
	/*if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		if (_player.playerState == PLAYERSTATE_RIGHT_JUMP)
		{
			_player.playerState = PLAYERSTATE_RIGHT_STOP;
			_player.ani = KEYANIMANAGER->findAnimation("오른쪽정지");
			_player.ani->start();
		}
		if (_player.playerState == PLAYERSTATE_LEFT_JUMP)
		{
			_player.playerState = PLAYERSTATE_LEFT_STOP;
			_player.ani = KEYANIMANAGER->findAnimation("오른쪽정지");
			_player.ani->start();
		}
	}*/
	//숙이기
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		if (_player.playerState == PLAYERSTATE_RIGHT_STOP || _player.playerState == PLAYERSTATE_RIGHT_RUN || _player.playerState == PLAYERSTATE_RIGHT_MOVE)
		{
			_player.playerState = PLAYERSTATE_RIGHT_DUCK;
			_player.ani = KEYANIMANAGER->findAnimation("오른쪽숙이기");
			_player.ani->start();
			_commandStart = true;
			_commandCount += 31;
		}
		else if (_player.playerState == PLAYERSTATE_LEFT_STOP || _player.playerState == PLAYERSTATE_LEFT_RUN || _player.playerState == PLAYERSTATE_LEFT_MOVE)
		{
			_player.playerState = PLAYERSTATE_LEFT_DUCK;
			_player.ani = KEYANIMANAGER->findAnimation("왼쪽숙이기");
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
			_player.ani = KEYANIMANAGER->findAnimation("오른쪽정지");
			_player.ani->start();
		}
		else if (_player.playerState == PLAYERSTATE_LEFT_DUCK)
		{
			_player.playerState = PLAYERSTATE_LEFT_STOP;
			_player.ani = KEYANIMANAGER->findAnimation("왼쪽정지");
			_player.ani->start();
		}
		else;
	}
	//약손
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		playerManager::attack();
		if (_player.playerState == PLAYERSTATE_RIGHT_STOP || _player.playerState == PLAYERSTATE_RIGHT_RUN || _player.playerState == PLAYERSTATE_RIGHT_MOVE)
		{
			if (_commandCount >= 63)
			{
				_player.playerState = PLAYERSTATE_RIGHT_COMMAND1;
				_player.ani = KEYANIMANAGER->findAnimation("오른쪽커맨드1");
				_player.ani->start();
			}
			else
			{
				_player.playerState = PLAYERSTATE_RIGHT_SOFT_PUNCH;
				_player.ani = KEYANIMANAGER->findAnimation("오른쪽약손");
				_player.ani->start();
			}
		}
		else if (_player.playerState == PLAYERSTATE_LEFT_STOP || _player.playerState == PLAYERSTATE_LEFT_RUN || _player.playerState == PLAYERSTATE_LEFT_MOVE)
		{
			if (_commandCount >= 73)
			{
				_player.playerState = PLAYERSTATE_LEFT_COMMAND1;
				_player.ani = KEYANIMANAGER->findAnimation("왼쪽커맨드1");
				_player.ani->start();
			}
			else
			{
				_player.playerState = PLAYERSTATE_LEFT_SOFT_PUNCH;
				_player.ani = KEYANIMANAGER->findAnimation("왼쪽약손");
				_player.ani->start();
			}
		}
	}
	//강손
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		playerManager::attack();
		if (_player.playerState == PLAYERSTATE_RIGHT_STOP || _player.playerState == PLAYERSTATE_RIGHT_RUN || _player.playerState == PLAYERSTATE_RIGHT_MOVE)
		{
			_player.playerState = PLAYERSTATE_RIGHT_HARD_PUNCH;
			_player.ani = KEYANIMANAGER->findAnimation("오른쪽강손");
			_player.ani->start();
		}
		else if (_player.playerState == PLAYERSTATE_LEFT_STOP || _player.playerState == PLAYERSTATE_LEFT_RUN || _player.playerState == PLAYERSTATE_LEFT_MOVE)
		{
			_player.playerState = PLAYERSTATE_LEFT_HARD_PUNCH;
			_player.ani = KEYANIMANAGER->findAnimation("왼쪽강손");
			_player.ani->start();
		}
	}
	//약발
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		playerManager::attack();
		if (_player.playerState == PLAYERSTATE_RIGHT_STOP || _player.playerState == PLAYERSTATE_RIGHT_RUN || _player.playerState == PLAYERSTATE_RIGHT_MOVE)
		{
			_player.playerState = PLAYERSTATE_RIGHT_SOFT_KICK;
			_player.ani = KEYANIMANAGER->findAnimation("오른쪽약발");
			_player.ani->start();
		}
		else if (_player.playerState == PLAYERSTATE_LEFT_STOP || _player.playerState == PLAYERSTATE_LEFT_RUN || _player.playerState == PLAYERSTATE_LEFT_MOVE)
		{
			_player.playerState = PLAYERSTATE_LEFT_SOFT_KICK;
			_player.ani = KEYANIMANAGER->findAnimation("왼쪽약발");
			_player.ani->start();
		}
	}
	//강발
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		playerManager::attack();
		if (_player.playerState == PLAYERSTATE_RIGHT_STOP || _player.playerState == PLAYERSTATE_RIGHT_RUN || _player.playerState == PLAYERSTATE_RIGHT_MOVE)
		{
			if (_commandCount >= 74)
			{
				_player.playerState = PLAYERSTATE_RIGHT_COMMAND2;
				_player.ani = KEYANIMANAGER->findAnimation("오른쪽커맨드2");
				_player.ani->start();
			}
			else
			{
				_player.playerState = PLAYERSTATE_RIGHT_HARD_KICK;
				_player.ani = KEYANIMANAGER->findAnimation("오른쪽강발");
				_player.ani->start();
			}
		}
		else if (_player.playerState == PLAYERSTATE_LEFT_STOP || _player.playerState == PLAYERSTATE_LEFT_RUN || _player.playerState == PLAYERSTATE_LEFT_MOVE)
		{
			if (_commandCount >= 74)
			{
				_player.playerState = PLAYERSTATE_LEFT_COMMAND2;
				_player.ani = KEYANIMANAGER->findAnimation("왼쪽커맨드2");
				_player.ani->start();
			}
			else
			{
				_player.playerState = PLAYERSTATE_LEFT_HARD_KICK;
				_player.ani = KEYANIMANAGER->findAnimation("왼쪽강발");
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
	//커맨드 불값 켜지면 
	if (_commandStart)
	{
		//커맨트 타이머 돌고
		_commandTimer++;
	}
	//캐맨드 타이머 일정치 지나면 불값 초기화
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
	l->setPlayerMotion(KEYANIMANAGER->findAnimation("오른쪽정지"));
	l->_player.attackRange = RectMake(0, 0, 0, 0);
	l->getPlayerMotion()->start();
}

void lee::leftFire(void* obj)
{
	lee* l = (lee*)obj;
	l->setPlayerState(PLAYERSTATE_LEFT_STOP);
	l->setPlayerMotion(KEYANIMANAGER->findAnimation("왼쪽정지"));
	l->_player.attackRange = RectMake(0, 0, 0, 0);
	l->getPlayerMotion()->start();
}

void lee::rightFinish(void* obj)
{
	lee* l = (lee*)obj;
	l->setPlayerState(PLAYERSTATE_RIGHT_COMMAND3);
	l->setPlayerMotion(KEYANIMANAGER->findAnimation("오른쪽커맨드3"));
	l->_player.attackRange = RectMake(0, 0, 0, 0);
	l->getPlayerMotion()->start();
}
void lee::leftFinish(void* obj)
{
	lee* l = (lee*)obj;
	l->setPlayerState(PLAYERSTATE_LEFT_COMMAND3);
	l->setPlayerMotion(KEYANIMANAGER->findAnimation("왼쪽커맨드3"));
	l->_player.attackRange = RectMake(0, 0, 0, 0);
	l->getPlayerMotion()->start();
}

void lee::pixelCollision()
{
	if (!PIXELMANAGER->playerLWall(_player.img, _player.x, _player.y, IMAGEMANAGER->findImage("픽셀라인")))
	{

	}
	if (PIXELMANAGER->getPixelCollisionY(_player.img, _player.x, _player.y, IMAGEMANAGER->findImage("픽셀라인")))
	{
		_player.isJump = false;
	}
}