#include "stdafx.h"
#include "playerManager.h"


playerManager::playerManager()
{
}


playerManager::~playerManager()
{
}

HRESULT playerManager::init()
{

	//��ӹް� init�� �̷������� �ʱ�ȭ ���ֱ�

	_player.img = IMAGEMANAGER->addFrameImage("�罺��", "Sasuke.bmp", 0, 0, 1090, 728, 10, 14, true, RGB(255, 0, 255));

	int rightStop[] = { 0,1,2,3 };
	KEYANIMANAGER->addArrayFrameAnimation("����������", "�罺��", rightStop, 4, 10, true);

	int rightMove[] = { 4,5,6,7,8,9 };
	KEYANIMANAGER->addArrayFrameAnimation("�������̵�", "�罺��", rightMove, 6, 10, true);

	int leftStop[] = { 10,11,12,13 };
	KEYANIMANAGER->addArrayFrameAnimation("��������", "�罺��", leftStop, 4, 10, true);

	int leftMove[] = { 14,15,16,17,18,19 };
	KEYANIMANAGER->addArrayFrameAnimation("�����̵�", "�罺��", leftMove, 6, 10, true);

	int rightRunning[] = { 24,25,26,27,28,29 };
	KEYANIMANAGER->addArrayFrameAnimation("�����ʴ޸���", "�罺��", rightRunning, 6, 10, true);

	int leftRunning[] = { 34,35,36,37,38,39 };
	KEYANIMANAGER->addArrayFrameAnimation("���ʴ޸���", "�罺��", leftRunning, 4, 10, true);

	_player.currentHp = _player.maxHp = 100.0f;
	_player.gravity = 5.0f;
	_player.speed = 4.0f;
	_player.playerState = PLAYERSTATE_RIGHT_STOP;
	_player.x = 200;
	_player.y = WINSIZEY - 100;
	_player.rc = RectMakeCenter(_player.x, _player.y, 50, 50);
	_player.ani = KEYANIMANAGER->findAnimation("����������");

	_dummy = new dummy;
	_dummy->init();


	//�÷��̾� �ִϸ��̼� �Լ��� �ִϸ��̼� �߰� �� �̴ֿ� �ҷ�����

	return S_OK;
}

void playerManager::release()
{

}

void playerManager::update()
{
	_dummy->update();
	KEYANIMANAGER->update();
	inputKey();
	move();
}

void playerManager::render()
{
	_dummy->render();
	_player.img->aniRender(getMemDC(), _player.rc.left, _player.rc.top, _player.ani);
	//_player.hpBar->render();
}

void playerManager::attack()  
{

}

void playerManager::move()	  
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
	}
}

void playerManager::inputKey()
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

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		
	}
}

void playerManager::setPlayerAni()
{
}

void playerManager::command()
{

}