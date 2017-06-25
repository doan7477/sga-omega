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
	_player.img = IMAGEMANAGER->addFrameImage("나루토", "image/김성진/naruto.bmp", 0, 0, 3233, 112, 53, 2, true, RGB(255, 0, 255));

	//스톱
	int rightStop[] = { 0,1,2,3,4,5 };
	KEYANIMANAGER->addArrayFrameAnimation("오른쪽정지", "나루토", rightStop, 6, 6, true);
	int leftStop[] = { 53,54,55,56,57,58 };
	KEYANIMANAGER->addArrayFrameAnimation("왼쪽정지", "나루토", leftStop, 6, 6, true);

	//이동
	int rightMove[] = { 6,7,8,9,10,11 };
	KEYANIMANAGER->addArrayFrameAnimation("오른쪽이동", "나루토", rightMove, 6, 6, true);
	int leftMove[] = { 59,60,61,62,63,64 };
	KEYANIMANAGER->addArrayFrameAnimation("왼쪽이동", "나루토", leftMove, 6, 6, true);

	//뛰기
	int rightRun[] = { 12,13,14,15,16,17 };
	KEYANIMANAGER->addArrayFrameAnimation("오른쪽뛰기", "나루토", rightRun, 6, 6, true);
	int leftRun[] = { 65,66,67,68,69,70 };
	KEYANIMANAGER->addArrayFrameAnimation("왼쪽뛰기", "나루토", leftRun, 6, 6, true);

	//약손
	int rightSoftPunch[] = { 18,19,20 };
	KEYANIMANAGER->addArrayFrameAnimation("오른쪽약손", "나루토", rightSoftPunch, 3, 10, false, rightAttack, this);
	int leftSoftPunch[] = { 71,72,73 };
	KEYANIMANAGER->addArrayFrameAnimation("왼쪽약손", "나루토", leftSoftPunch, 3, 10, false, leftAttack, this);

	//강손
	int rightHardPunch[] = { 21,22,23,24 };
	KEYANIMANAGER->addArrayFrameAnimation("오른쪽강손", "나루토", rightHardPunch, 4, 10, false, rightAttack, this);
	int leftHardPunch[] = { 74,75,76,77 };
	KEYANIMANAGER->addArrayFrameAnimation("왼쪽강손", "나루토", leftHardPunch, 4, 10, false, leftAttack, this);

	//커맨드 1 박치기
	int rightHeadButt[] = { 25,26,27 };
	KEYANIMANAGER->addArrayFrameAnimation("오른쪽박치기", "나루토", rightHeadButt, 3, 10, false, rightAttack, this);
	int leftHeadButt[] = { 78,79,80 };
	KEYANIMANAGER->addArrayFrameAnimation("왼쪽박치키", "나루토", leftHeadButt, 3, 10, false, leftAttack, this);

	//점프
	int rightJump[] = { 28,29 };
	KEYANIMANAGER->addArrayFrameAnimation("오른쪽점프", "나루토", rightJump, 2, 10, false);
	int leftJump[] = { 81,82 };
	KEYANIMANAGER->addArrayFrameAnimation("왼쪽점프", "나루토", leftJump, 2, 10, false);

	//추락
	int rightFall[] = { 30,31 };
	KEYANIMANAGER->addArrayFrameAnimation("오른쪽추락", "나루토", rightFall, 2, 10, false);
	int leftFall[] = { 83,84 };
	KEYANIMANAGER->addArrayFrameAnimation("왼쪽추락", "나루토", leftFall, 2, 10, false);

	//커맨드 2 수리검 투척
	int rightThrow[] = { 32,33 };
	KEYANIMANAGER->addArrayFrameAnimation("오른쪽투척", "나루토", rightThrow, 3, 10, false);
	int leftThrow[] = { 85,86 };
	KEYANIMANAGER->addArrayFrameAnimation("왼쪽투척", "나루토", leftThrow, 3, 10, false);

	//커맨드 3 독두꺼비 소환
	int rightToad[] = { 34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49 };
	KEYANIMANAGER->addArrayFrameAnimation("오른쪽소환", "나루토", rightToad, 16, 10, false);
	int leftToad[] = { 87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102 };
	KEYANIMANAGER->addArrayFrameAnimation("왼쪽소환", "나루토", leftToad, 16, 10, false);

	//숙이기
	int rightDuck[] = { 50,51 };
	KEYANIMANAGER->addArrayFrameAnimation("오른쪽소환", "나루토", rightDuck, 2, 10, false);
	int leftDuck[] = { 103,104 };
	KEYANIMANAGER->addArrayFrameAnimation("왼쪽소환", "나루토", leftDuck, 2, 10, false);

	_player.currentHp = _player.maxHp = 100.0f;
	_player.gravity = 4.0f;
	_player.speed = 3.0f;
	_player.playerState = PLAYERSTATE_RIGHT_STOP;
	_player.x = 200;
	_player.y = WINSIZEY - 60;
	_player.rc = RectMakeCenter(_player.x, _player.y, 50, 50);
	_player.ani = KEYANIMANAGER->findAnimation("오른쪽정지");

	return S_OK;
}

void naruto::release()
{

}

void naruto::update()
{
	KEYANIMANAGER->update();
	move();
}

void naruto::render()
{
	//이미지 그려주기
	_player.img->aniRender(getMemDC(), _player.rc.left, _player.rc.top, _player.ani);
}

void naruto::move()
{
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
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_player.playerState = PLAYERSTATE_RIGHT_MOVE;
		_player.ani = KEYANIMANAGER->findAnimation("오른쪽이동");
		_player.ani->start();
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_player.playerState = PLAYERSTATE_RIGHT_STOP;
		_player.ani = KEYANIMANAGER->findAnimation("오른쪽정지");
		_player.ani->start();
	}
}

void naruto::inputKey()
{

}
void naruto::setPlayerAni()
{

}
void naruto::command()
{

}

void naruto::rightAttack(void* obj)
{
	naruto* n = (naruto*)obj;

	n->setPlayerState(PLAYERSTATE_RIGHT_STOP);
	n->setPlayerMotion(KEYANIMANAGER->findAnimation("오른쪽정지"));
	n->getPlayerMotion()->start();
}

void naruto::leftAttack(void* obj)
{
	naruto* n = (naruto*)obj;

	n->setPlayerState(PLAYERSTATE_LEFT_STOP);
	n->setPlayerMotion(KEYANIMANAGER->findAnimation("왼쪽정지"));
	n->getPlayerMotion()->start();
}