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
	_player = new lee;
	_player->init();

	_dummy = new dummy;
	_dummy->init();

	return S_OK;
}
void gameScene::release()
{

}
void gameScene::update()
{
	_player->update();
	_dummy->update();
}
void gameScene::render()
{
	IMAGEMANAGER->render("�ȼ�����", getMemDC(), 0, 0);
	IMAGEMANAGER->render("��׶���", getMemDC(), 0, 0);

	_player->render();
	_dummy->render();
}