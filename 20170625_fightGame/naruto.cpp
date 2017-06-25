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
	_player.img = IMAGEMANAGER->addFrameImage("������", "image/�輺��/naruto.bmp", 0, 0, 3233, 112, 53, 2, true, RGB(255, 0, 255));

	//����
	int rightStop[] = { 0,1,2,3,4,5 };
	KEYANIMANAGER->addArrayFrameAnimation("����������", "������", rightStop, 6, 6, true);
	int leftStop[] = { 53,54,55,56,57,58 };
	KEYANIMANAGER->addArrayFrameAnimation("��������", "������", leftStop, 6, 6, true);

	//�̵�
	int rightMove[] = { 6,7,8,9,10,11 };
	KEYANIMANAGER->addArrayFrameAnimation("�������̵�", "������", rightMove, 6, 6, true);
	int leftMove[] = { 59,60,61,62,63,64 };
	KEYANIMANAGER->addArrayFrameAnimation("�����̵�", "������", leftMove, 6, 6, true);

	//�ٱ�
	int rightRun[] = { 12,13,14,15,16,17 };
	KEYANIMANAGER->addArrayFrameAnimation("�����ʶٱ�", "������", rightRun, 6, 6, true);
	int leftRun[] = { 65,66,67,68,69,70 };
	KEYANIMANAGER->addArrayFrameAnimation("���ʶٱ�", "������", leftRun, 6, 6, true);

	//���
	int rightSoftPunch[] = { 18,19,20 };
	KEYANIMANAGER->addArrayFrameAnimation("�����ʾ��", "������", rightSoftPunch, 3, 10, false, rightAttack, this);
	int leftSoftPunch[] = { 71,72,73 };
	KEYANIMANAGER->addArrayFrameAnimation("���ʾ��", "������", leftSoftPunch, 3, 10, false, leftAttack, this);

	//����
	int rightHardPunch[] = { 21,22,23,24 };
	KEYANIMANAGER->addArrayFrameAnimation("�����ʰ���", "������", rightHardPunch, 4, 10, false, rightAttack, this);
	int leftHardPunch[] = { 74,75,76,77 };
	KEYANIMANAGER->addArrayFrameAnimation("���ʰ���", "������", leftHardPunch, 4, 10, false, leftAttack, this);

	//Ŀ�ǵ� 1 ��ġ��
	int rightHeadButt[] = { 25,26,27 };
	KEYANIMANAGER->addArrayFrameAnimation("�����ʹ�ġ��", "������", rightHeadButt, 3, 10, false, rightAttack, this);
	int leftHeadButt[] = { 78,79,80 };
	KEYANIMANAGER->addArrayFrameAnimation("���ʹ�ġŰ", "������", leftHeadButt, 3, 10, false, leftAttack, this);

	//����
	int rightJump[] = { 28,29 };
	KEYANIMANAGER->addArrayFrameAnimation("����������", "������", rightJump, 2, 10, false);
	int leftJump[] = { 81,82 };
	KEYANIMANAGER->addArrayFrameAnimation("��������", "������", leftJump, 2, 10, false);

	//�߶�
	int rightFall[] = { 30,31 };
	KEYANIMANAGER->addArrayFrameAnimation("�������߶�", "������", rightFall, 2, 10, false);
	int leftFall[] = { 83,84 };
	KEYANIMANAGER->addArrayFrameAnimation("�����߶�", "������", leftFall, 2, 10, false);

	//Ŀ�ǵ� 2 ������ ��ô
	int rightThrow[] = { 32,33 };
	KEYANIMANAGER->addArrayFrameAnimation("��������ô", "������", rightThrow, 3, 10, false);
	int leftThrow[] = { 85,86 };
	KEYANIMANAGER->addArrayFrameAnimation("������ô", "������", leftThrow, 3, 10, false);

	//Ŀ�ǵ� 3 ���β��� ��ȯ
	int rightToad[] = { 34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49 };
	KEYANIMANAGER->addArrayFrameAnimation("�����ʼ�ȯ", "������", rightToad, 16, 10, false);
	int leftToad[] = { 87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102 };
	KEYANIMANAGER->addArrayFrameAnimation("���ʼ�ȯ", "������", leftToad, 16, 10, false);

	//���̱�
	int rightDuck[] = { 50,51 };
	KEYANIMANAGER->addArrayFrameAnimation("�����ʼ�ȯ", "������", rightDuck, 2, 10, false);
	int leftDuck[] = { 103,104 };
	KEYANIMANAGER->addArrayFrameAnimation("���ʼ�ȯ", "������", leftDuck, 2, 10, false);

	_player.currentHp = _player.maxHp = 100.0f;
	_player.gravity = 4.0f;
	_player.speed = 3.0f;
	_player.playerState = PLAYERSTATE_RIGHT_STOP;
	_player.x = 200;
	_player.y = WINSIZEY - 60;
	_player.rc = RectMakeCenter(_player.x, _player.y, 50, 50);
	_player.ani = KEYANIMANAGER->findAnimation("����������");

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
	//�̹��� �׷��ֱ�
	_player.img->aniRender(getMemDC(), _player.rc.left, _player.rc.top, _player.ani);
}

void naruto::move()
{
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
	n->setPlayerMotion(KEYANIMANAGER->findAnimation("����������"));
	n->getPlayerMotion()->start();
}

void naruto::leftAttack(void* obj)
{
	naruto* n = (naruto*)obj;

	n->setPlayerState(PLAYERSTATE_LEFT_STOP);
	n->setPlayerMotion(KEYANIMANAGER->findAnimation("��������"));
	n->getPlayerMotion()->start();
}