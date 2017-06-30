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

	return S_OK;
}

void gameScene::release()
{

}

void gameScene::update() 
{
	_player->update();
}

void gameScene::render() 
{
	IMAGEMANAGER->findImage("¹è°æ")->render(getMemDC(), 0, 0);
	_player->render();
	IMAGEMANAGER->findImage("¸Ê1-1")->render(getMemDC(), 0, 0);
	//IMAGEMANAGER->findImage("¸Ê1-1ÇÈ¼¿")->render(getMemDC(), 0, 0);
}
