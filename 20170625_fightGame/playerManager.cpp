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

	*/

	_player.currentHp = _player.maxHp = 100.0f;
	_player.gravity = 5.0f;
	_player.speed = 4.0f;
	_player.playerState = PLAYERSTATE_RIGHT_STOP;
	_player.x = 200;
	_player.y = WINSIZEY - 50;
	_player.rc = RectMakeCenter(_player.x, _player.y, 50, 50);
	_player.ani = KEYANIMANAGER->findAnimation("����������");
	_player.isJump = false;


	//�÷��̾� �ִϸ��̼� �Լ��� �ִϸ��̼� �߰� �� �̴ֿ� �ҷ�����

	return S_OK;
}

void playerManager::release()
{

}

void playerManager::update()
{
	pixelCollision();
	/*KEYANIMANAGER->update();
	inputKey();
	move();*/
}

void playerManager::render()
{
	//_player.img->aniRender(getMemDC(), _player.rc.left, _player.rc.top, _player.ani);
	//_player.hpBar->render();
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

void playerManager::attack()
{
	if (_player.playerState == PLAYERSTATE_LEFT_STOP || _player.playerState == PLAYERSTATE_LEFT_MOVE)
	{
		_player.attackRange = RectMake(_player.x - 20, _player.y - 10, 20, 20);
	}
	if (_player.playerState == PLAYERSTATE_RIGHT_STOP || _player.playerState == PLAYERSTATE_RIGHT_MOVE)
	{
		_player.attackRange = RectMake(_player.x + 40, _player.y - 10, 20, 20);
	}
}

void playerManager::setPlayerAni()
{
}

void playerManager::command()
{

}

void playerManager::pixelCollision()
{
	if (!PIXELMANAGER->playerLWall(_player.img, _player.x, _player.y, IMAGEMANAGER->findImage("�ȼ�����")))
	{

	}
	if (PIXELMANAGER->getPixelCollisionY(_player.img, _player.x, _player.y, IMAGEMANAGER->findImage("�ȼ�����")))
	{
		_player.isJump = false;
	}
}

void playerManager::rightAttack(void* obj)
{

}

void playerManager::leftAttack(void* obj)
{

}