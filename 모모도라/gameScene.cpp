#include "stdafx.h"
#include "gameScene.h"


gameScene::gameScene()
{
}


gameScene::~gameScene()
{
}

HRESULT gameScene::init()
{
	_player = new player;
	_player->init();
	_camX = 0;
	_camX2 = _camX3 = 0;
	_camY = 100;

	return S_OK;
}

void gameScene::release()
{

}

void gameScene::update() 
{
	_player->update();
	//4중으로 가자
	//플레이어 위치는 맵의 중심보다 조금 뒤에 있게
	if (_player->getPlayerCenter().x - 350 > _camX)
		if (_camX < 510)
		{
			//구를땐 카메라 빠르게
			if (_player->getPlayerState() == PLAYERSTATE_LEFT_ROLL ||
				_player->getPlayerState() == PLAYERSTATE_RIGHT_ROLL)
			{
				_camX += ROLLSPEED;
				_camX2 += ROLLSPEED - 1.0f;
				_camX3 += ROLLSPEED - 0.5f;
			}
			// 일반 카메라 속도
			else
			{
				_camX += _player->getPlayerSpeed();
				_camX2 += _player->getPlayerSpeed() - 1.0f;
				_camX3 += _player->getPlayerSpeed() - 0.5f;
			}
		}

	if (_player->getPlayerCenter().x - 350 < _camX)
		if (_camX > 0)
		{
			if (_player->getPlayerState() == PLAYERSTATE_LEFT_ROLL ||
				_player->getPlayerState() == PLAYERSTATE_RIGHT_ROLL)
			{
				_camX -= ROLLSPEED;
				_camX2 -= ROLLSPEED - 1.0f;
				_camX3 -= ROLLSPEED - 0.5f;
			}
			else
			{
				_camX -= _player->getPlayerSpeed();
				_camX2 -= _player->getPlayerSpeed() - 1.0f;
				_camX3 -= _player->getPlayerSpeed() - 0.5f;
			}
		}
}

void gameScene::render() 
{
	//IMAGEMANAGER->findImage("배경")->render(getMemDC(), 0, 0);
	IMAGEMANAGER->findImage("배경2")->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _camX2, 0);
	IMAGEMANAGER->findImage("배경1")->loopRender(getMemDC(), &RectMake(0, 100, WINSIZEX, WINSIZEY), _camX3, 0);
	_player->render(_camX,_camY);
	IMAGEMANAGER->findImage("맵1-1")->render(getMemDC(), -_camX, -_camY);
	if (_player->getPlayerIsJump()) TextOut(getMemDC(), 0, 0, "트루", strlen("트루"));
	if (!_player->getPlayerIsJump()) TextOut(getMemDC(), 0, 0, "폴스", strlen("폴스"));
	//IMAGEMANAGER->findImage("맵1-1픽셀")->render(getMemDC(), -_camX, -_camY);
}
