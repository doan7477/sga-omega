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
	IMAGEMANAGER->findImage("���")->render(getMemDC(), 0, 0);
	_player->render();
	IMAGEMANAGER->findImage("��1-1")->render(getMemDC(), 0, 0);
	//IMAGEMANAGER->findImage("��1-1�ȼ�")->render(getMemDC(), 0, 0);
}
