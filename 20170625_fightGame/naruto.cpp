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
	_player.img = IMAGEMANAGER->addFrameImage("나루토", "image/김성진/naruto.bmp", 0, 0, 3721, 112, 61, 2, true, RGB(255, 0, 255));
	_iToad = IMAGEMANAGER->addImage("독두꺼비", "image/김성진/toad.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	//스톱
	int rightStop[] = { 0,1,2,3,4,5 };
	KEYANIMANAGER->addArrayFrameAnimation("오른쪽정지", "나루토", rightStop, 6, 6, true);
	int leftStop[] = { 61,62,63,64,65,66 };
	KEYANIMANAGER->addArrayFrameAnimation("왼쪽정지", "나루토", leftStop, 6, 6, true);

	//이동
	int rightMove[] = { 6,7,8,9,10,11 };
	KEYANIMANAGER->addArrayFrameAnimation("오른쪽이동", "나루토", rightMove, 6, 6, true);
	int leftMove[] = { 67,68,69,70,71,72 };
	KEYANIMANAGER->addArrayFrameAnimation("왼쪽이동", "나루토", leftMove, 6, 6, true);

	//뛰기
	int rightRun[] = { 12,13,14,15,16,17 };
	KEYANIMANAGER->addArrayFrameAnimation("오른쪽뛰기", "나루토", rightRun, 6, 6, true);
	int leftRun[] = { 73,74,75,76,77,78 };
	KEYANIMANAGER->addArrayFrameAnimation("왼쪽뛰기", "나루토", leftRun, 6, 6, true);

	//약손
	int rightSoftPunch[] = { 18,19,20 };
	KEYANIMANAGER->addArrayFrameAnimation("오른쪽약손", "나루토", rightSoftPunch, 3, 10, false, rightAttack, this);
	int leftSoftPunch[] = { 79,80,81 };
	KEYANIMANAGER->addArrayFrameAnimation("왼쪽약손", "나루토", leftSoftPunch, 3, 10, false, leftAttack, this);

	//강손
	int rightHardPunch[] = { 21,22,23,24 };
	KEYANIMANAGER->addArrayFrameAnimation("오른쪽강손", "나루토", rightHardPunch, 4, 10, false, rightAttack, this);
	int leftHardPunch[] = { 82,83,84,85 };
	KEYANIMANAGER->addArrayFrameAnimation("왼쪽강손", "나루토", leftHardPunch, 4, 10, false, leftAttack, this);

	//커맨드 1 박치기
	int rightHeadButt[] = { 25,26,27 };
	KEYANIMANAGER->addArrayFrameAnimation("오른쪽박치기", "나루토", rightHeadButt, 3, 10, false, rightAttack, this);
	int leftHeadButt[] = { 86,87,88 };
	KEYANIMANAGER->addArrayFrameAnimation("왼쪽박치기", "나루토", leftHeadButt, 3, 10, false, leftAttack, this);

	//점프
	int rightJump[] = { 28,29 };
	KEYANIMANAGER->addArrayFrameAnimation("오른쪽점프", "나루토", rightJump, 2, 10, false);
	int leftJump[] = { 89,90 };
	KEYANIMANAGER->addArrayFrameAnimation("왼쪽점프", "나루토", leftJump, 2, 10, false);

	//추락
	int rightFall[] = { 30,31 };
	KEYANIMANAGER->addArrayFrameAnimation("오른쪽추락", "나루토", rightFall, 2, 10, false);
	int leftFall[] = { 91,92 };
	KEYANIMANAGER->addArrayFrameAnimation("왼쪽추락", "나루토", leftFall, 2, 10, false);

	//커맨드 2 수리검 투척
	int rightThrow[] = { 32,33,34 };
	KEYANIMANAGER->addArrayFrameAnimation("오른쪽투척", "나루토", rightThrow, 3, 5, false, rightAttack, this);
	int leftThrow[] = { 93,94,95 };
	KEYANIMANAGER->addArrayFrameAnimation("왼쪽투척", "나루토", leftThrow, 3, 5, false, leftAttack, this);

	//커맨드 3 독두꺼비 소환
	int rightToad[] = { 35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50 };
	KEYANIMANAGER->addArrayFrameAnimation("오른쪽소환", "나루토", rightToad, 16, 5, false, rightAttack, this);
	int leftToad[] = { 96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111 };
	KEYANIMANAGER->addArrayFrameAnimation("왼쪽소환", "나루토", leftToad, 16, 5, false, leftAttack, this);

	//숙이기
	int rightDuck[] = { 51,52 };
	KEYANIMANAGER->addArrayFrameAnimation("오른쪽숙이기", "나루토", rightDuck, 2, 10, false);
	int leftDuck[] = { 112,113 };
	KEYANIMANAGER->addArrayFrameAnimation("왼쪽숙이기", "나루토", leftDuck, 2, 10, false);

	//약발
	int rightSoftKick[] = { 53,54,55,56 };
	KEYANIMANAGER->addArrayFrameAnimation("오른쪽약발", "나루토", rightSoftKick, 4, 15, false, rightAttack, this);
	int leftSoftKick[] = { 114,115,116,117 };
	KEYANIMANAGER->addArrayFrameAnimation("왼쪽약발", "나루토", leftSoftKick, 4, 15, false, leftAttack, this);

	//강발
	int rightHardKick[] = { 57,58,59,60 };
	KEYANIMANAGER->addArrayFrameAnimation("오른쪽강발", "나루토", rightHardKick, 4, 5, false, rightAttack, this);
	int leftHardKick[] = { 118,119,120,121 };
	KEYANIMANAGER->addArrayFrameAnimation("왼쪽강발", "나루토", leftHardKick, 4, 5, false, leftAttack, this);

	_player.currentHp = _player.maxHp = 100.0f;
	_player.gravity = 4.0f;
	_player.speed = 3.0f;
	_player.playerState = PLAYERSTATE_RIGHT_STOP;
	_player.x = 200;
	_player.y = WINSIZEY - 60;
	_player.rc = RectMakeCenter(_player.x, _player.y, 50, 50);
	_player.ani = KEYANIMANAGER->findAnimation("오른쪽정지");
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
	//이미지 그려주기
	_player.img->aniRender(getMemDC(), _player.rc.left, _player.rc.top, _player.ani);
	if (_toad)_iToad->render(getMemDC(), 0, 0);
	_throwKnife->render();
}

void naruto::move()
{
	_player.rc = RectMakeCenter(_player.x, _player.y, 50, 50);
	//움직이기
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
	///////////////////////////////////////////////////오른쪽이동
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_player.command += 1;
		if (_player.command == 2)
		{
			_player.playerState = PLAYERSTATE_RIGHT_RUN;
			_player.ani = KEYANIMANAGER->findAnimation("오른쪽뛰기");
			_player.ani->start();
		}
		else
		{
			_player.playerState = PLAYERSTATE_RIGHT_MOVE;
			_player.ani = KEYANIMANAGER->findAnimation("오른쪽이동");
			_player.ani->start();
		}
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_player.playerState = PLAYERSTATE_RIGHT_STOP;
		_player.ani = KEYANIMANAGER->findAnimation("오른쪽정지");
		_player.ani->start();
		if (_player.playerState == PLAYERSTATE_RIGHT_RUN)
		{
			_player.command = 0;
			_player.timer = 0;
		}
	}
	/////////////////////////////////////////////////왼쪽이동
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_player.command += 2;
		if (_player.command == 4)
		{
			_player.playerState = PLAYERSTATE_LEFT_RUN;
			_player.ani = KEYANIMANAGER->findAnimation("왼쪽뛰기");
			_player.ani->start();
		}
		else
		{
			_player.playerState = PLAYERSTATE_LEFT_MOVE;
			_player.ani = KEYANIMANAGER->findAnimation("왼쪽이동");
			_player.ani->start();
		}
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_player.playerState = PLAYERSTATE_LEFT_STOP;
		_player.ani = KEYANIMANAGER->findAnimation("왼쪽정지");
		_player.ani->start();
		if (_player.playerState == PLAYERSTATE_RIGHT_RUN)
		{
			_player.command = 0;
			_player.timer = 0;
		}
	}
	////////////////////////////////////////////////////약손공격
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
				_player.ani = KEYANIMANAGER->findAnimation("오른쪽박치기");
				_player.ani->start();
				_player.command = 0;
			}
			else
			{
				_player.playerState = PLAYERSTATE_RIGHT_SOFT_PUNCH;
				_player.ani = KEYANIMANAGER->findAnimation("오른쪽약손");
				_player.ani->start();
			}
		}
		else if (_player.playerState == PLAYERSTATE_LEFT_STOP || _player.playerState == PLAYERSTATE_LEFT_MOVE || _player.playerState == PLAYERSTATE_LEFT_RUN)
		{
			if (_player.command == 16)
			{
				_player.playerState = PLAYERSTATE_RIGHT_SOFT_PUNCH;
				_player.ani = KEYANIMANAGER->findAnimation("왼쪽박치기");
				_player.ani->start();
				_player.command = 0;
			}
			else
			{
				_player.playerState = PLAYERSTATE_LEFT_SOFT_PUNCH;
				_player.ani = KEYANIMANAGER->findAnimation("왼쪽약손");
				_player.ani->start();
			}
		}
	}
	////////////////////////////////////////////////강손공격
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
				_player.ani = KEYANIMANAGER->findAnimation("오른쪽투척");
				_player.ani->start();
				_throwKnife->fire(_player.x, _player.y, (int)_player.playerState);
			}
			else if (_player.command == 40)
			{
				_player.playerState = PLAYERSTATE_RIGHT_SKILL2;
				_player.ani = KEYANIMANAGER->findAnimation("오른쪽소환");
				_player.ani->start();
				_commandTime = 0;
				_player.command = 0;
			}
			else
			{
				_player.playerState = PLAYERSTATE_RIGHT_HARD_PUNCH;
				_player.ani = KEYANIMANAGER->findAnimation("오른쪽강손");
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
				_player.ani = KEYANIMANAGER->findAnimation("왼쪽투척");
				_player.ani->start();
				_throwKnife->fire(_player.x, _player.y, (int)_player.playerState);
			}
			else if (_player.command == 40)
			{
				_commandTime = 0;
				_player.command = 0;
				_player.playerState = PLAYERSTATE_LEFT_SKILL2;
				_player.ani = KEYANIMANAGER->findAnimation("왼쪽소환");
				_player.ani->start();
			}
			else
			{
				_player.playerState = PLAYERSTATE_LEFT_HARD_PUNCH;
				_player.ani = KEYANIMANAGER->findAnimation("왼쪽강손");
				_player.ani->start();
			}
		}
	}
	////////////////////////////////////////////////////////////////////////약발공격
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		playerManager::attack();
		if (_player.playerState == PLAYERSTATE_RIGHT_STOP || _player.playerState == PLAYERSTATE_RIGHT_MOVE || _player.playerState == PLAYERSTATE_RIGHT_RUN)
		{
			_player.playerState = PLAYERSTATE_RIGHT_SOFT_KICK;
			_player.ani = KEYANIMANAGER->findAnimation("오른쪽약발");
			_player.ani->start();
		}
		else if (_player.playerState == PLAYERSTATE_LEFT_STOP || _player.playerState == PLAYERSTATE_LEFT_MOVE || _player.playerState == PLAYERSTATE_LEFT_RUN)
		{
			_player.playerState = PLAYERSTATE_LEFT_SOFT_KICK;
			_player.ani = KEYANIMANAGER->findAnimation("왼쪽약발");
			_player.ani->start();
		}
	}
	////////////////////////////////////////////////////////////////////////강발공격
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		playerManager::attack();
		if (_player.playerState == PLAYERSTATE_RIGHT_STOP || _player.playerState == PLAYERSTATE_RIGHT_MOVE || _player.playerState == PLAYERSTATE_RIGHT_RUN)
		{
			_player.playerState = PLAYERSTATE_RIGHT_HARD_KICK;
			_player.ani = KEYANIMANAGER->findAnimation("오른쪽강발");
			_player.ani->start();
		}
		else if (_player.playerState == PLAYERSTATE_LEFT_STOP || _player.playerState == PLAYERSTATE_LEFT_MOVE || _player.playerState == PLAYERSTATE_LEFT_RUN)
		{
			_player.playerState = PLAYERSTATE_LEFT_HARD_KICK;
			_player.ani = KEYANIMANAGER->findAnimation("왼쪽강발");
			_player.ani->start();
		}
	}
	/////////////////////////////////////////////////////////////////숙이기
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		_commandTime = 0;
		_player.command += 16;
		if (_player.playerState == PLAYERSTATE_RIGHT_STOP || _player.playerState == PLAYERSTATE_RIGHT_RUN || _player.playerState == PLAYERSTATE_RIGHT_MOVE)
		{
			_player.playerState = PLAYERSTATE_RIGHT_DUCK;
			_player.ani = KEYANIMANAGER->findAnimation("오른쪽숙이기");
			_player.ani->start();
		}
		else if (_player.playerState == PLAYERSTATE_LEFT_STOP || _player.playerState == PLAYERSTATE_LEFT_RUN || _player.playerState == PLAYERSTATE_LEFT_MOVE)
		{
			_player.playerState = PLAYERSTATE_LEFT_DUCK;
			_player.ani = KEYANIMANAGER->findAnimation("왼쪽숙이기");
			_player.ani->start();
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
		if (_player.playerState == PLAYERSTATE_LEFT_DUCK)
		{
			_player.playerState = PLAYERSTATE_LEFT_STOP;
			_player.ani = KEYANIMANAGER->findAnimation("왼쪽정지");
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
	if (n->getPlayerMotion() == KEYANIMANAGER->findAnimation("오른쪽소환"))n->setToad(true);
	n->setPlayerState(PLAYERSTATE_RIGHT_STOP);
	n->_player.attackRange = RectMake(0, 0, 0, 0);
	n->setPlayerMotion(KEYANIMANAGER->findAnimation("오른쪽정지"));
	n->getPlayerMotion()->start();
}

void naruto::leftAttack(void* obj)
{
	naruto* n = (naruto*)obj;
	if (n->getPlayerMotion() == KEYANIMANAGER->findAnimation("왼쪽소환"))n->setToad(true);
	n->setPlayerState(PLAYERSTATE_LEFT_STOP);
	n->_player.attackRange = RectMake(0, 0, 0, 0);
	n->setPlayerMotion(KEYANIMANAGER->findAnimation("왼쪽정지"));
	n->getPlayerMotion()->start();
}
