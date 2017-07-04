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
	_camY = 100;

	return S_OK;
}

void gameScene::release()
{

}

void gameScene::update() 
{
	_player->update();

	//if (_player->getPlayerCenter().x - _camX > WINSIZEX / 2) _camX += _player->getPlayerSpeed();
	//if (_player->getPlayerCenter().x - _camX < WINSIZEX / 2) _camX -= _player->getPlayerSpeed();
	//if (_player->getPlayerCenter().y - _camY < WINSIZEY / 2) _camY -= 3.0f;
	//if (_player->getPlayerCenter().y - _camY > WINSIZEY / 2) _camY += 3.0f;

	if (_player->getPlayerCenter().x - 350 > _camX)
		if (_camX < 510)
		{
			if (_player->getPlayerState() == PLAYERSTATE_LEFT_ROLL ||
				_player->getPlayerState() == PLAYERSTATE_RIGHT_ROLL)
			{
				_camX += ROLLSPEED;
			}
			else _camX += _player->getPlayerSpeed();
		}

	if (_player->getPlayerCenter().x - 350 < _camX)
		if (_camX > 0)
		{
			if (_player->getPlayerState() == PLAYERSTATE_LEFT_ROLL ||
				_player->getPlayerState() == PLAYERSTATE_RIGHT_ROLL)
			{
				_camX -= ROLLSPEED;
			}
			else _camX -= _player->getPlayerSpeed();
		}
}

void gameScene::render() 
{
	IMAGEMANAGER->findImage("¹è°æ")->render(getMemDC(), 0, 0);
	_player->render(_camX, _camY);
	//IMAGEMANAGER->findImage("¸Ê1-1")->render(getMemDC(), -_camX, -_camY);
	IMAGEMANAGER->findImage("¸Ê1-1ÇÈ¼¿")->render(getMemDC(), -_camX, -_camY);
}
