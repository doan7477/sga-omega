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

	/*_player.img = IMAGEMANAGER->addFrameImage("�̵�", "move.bmp", 0, 0, 288, 44, 6, 1, true, RGB(255, 0, 255));

	int rightMove[] = { 0,1,2,3,4,5 };
	KEYANIMANAGER->addArrayFrameAnimation("�������̵�", "�̵�", rightMove, 6, 10, true);

	int rightStop[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("����������", "�̵�", rightStop, 1, 10, true);

	_player.currentHp = _player.maxHp = 100.0f;
	_player.gravity = 5.0f;
	_player.speed = 4.0f;
	_player.playerState = PLAYERSTATE_RIGHT_STOP;
	_player.x = 200;
	_player.y = WINSIZEY - 50;
	_player.rc = RectMakeCenter(_player.x, _player.y, 50, 50);
	_player.ani = KEYANIMANAGER->findAnimation("����������");*/


	//�÷��̾� �ִϸ��̼� �Լ��� �ִϸ��̼� �߰� �� �̴ֿ� �ҷ�����

	return S_OK;
}

void playerManager::release()
{

}

void playerManager::update()
{

	/*KEYANIMANAGER->update();
	inputKey();
	move();*/
}

void playerManager::render()
{
	//_player.img->aniRender(getMemDC(), _player.rc.left, _player.rc.top, _player.ani);
	//_player.hpBar->render();
}

void playerManager::attack()  
{

}

void playerManager::move()	  
{
	//_player.rc = RectMakeCenter(_player.x, _player.y, 50, 50);
	////�÷��̾� ���¿� ���� ������ �����ϱ�
	//switch (_player.playerState)
	//{
	//case PLAYERSTATE_RIGHT_MOVE:
	//	_player.x += _player.speed;
	//	break;
	//case PLAYERSTATE_LEFT_MOVE:
	//	_player.x -= _player.speed;
	//	break;
	//}
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
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_player.playerState = PLAYERSTATE_LEFT_STOP;
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