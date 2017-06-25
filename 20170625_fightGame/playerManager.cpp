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

	//상속받고 init에 이런식으로 초기화 해주기

	/*_player.img = IMAGEMANAGER->addFrameImage("이동", "move.bmp", 0, 0, 288, 44, 6, 1, true, RGB(255, 0, 255));

	int rightMove[] = { 0,1,2,3,4,5 };
	KEYANIMANAGER->addArrayFrameAnimation("오른쪽이동", "이동", rightMove, 6, 10, true);

	int rightStop[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("오른쪽정지", "이동", rightStop, 1, 10, true);

	_player.currentHp = _player.maxHp = 100.0f;
	_player.gravity = 5.0f;
	_player.speed = 4.0f;
	_player.playerState = PLAYERSTATE_RIGHT_STOP;
	_player.x = 200;
	_player.y = WINSIZEY - 50;
	_player.rc = RectMakeCenter(_player.x, _player.y, 50, 50);
	_player.ani = KEYANIMANAGER->findAnimation("오른쪽정지");*/


	//플레이어 애니메이션 함수에 애니메이션 추가 후 이닛에 불러오기

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
	////플레이어 상태에 따라 움직임 설정하기
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
	//키 입력
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