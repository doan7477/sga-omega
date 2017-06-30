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
	_camX = _camY = 0;

	return S_OK;
}

void gameScene::release()
{

}

void gameScene::update() 
{
	_player->update();

	if (_player->getPlayerCenter().x - _camX > WINSIZEX / 2) _camX += _player->getPlayerSpeed();
	if (_player->getPlayerCenter().x - _camX < WINSIZEX / 2) _camX -= _player->getPlayerSpeed();
	if (_player->getPlayerCenter().y - _camY < WINSIZEY / 2) _camY -= 3.0f;
	if (_player->getPlayerCenter().y - _camY > WINSIZEY / 2) _camY += 3.0f;
}

void gameScene::render() 
{
	IMAGEMANAGER->findImage("¹è°æ")->render(getMemDC(), 0, 0);
	_player->render(_camX,_camY);
	IMAGEMANAGER->findImage("¸Ê1-1")->render(getMemDC(), -_camX, -_camY);
	IMAGEMANAGER->findImage("¸Ê1-1ÇÈ¼¿")->render(getMemDC(), -_camX, -_camY);
}
