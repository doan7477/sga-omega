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
	vStr = TXTDATA->txtLoad("캐릭터선택.txt");
	_selectedChar = (atoi(vStr[0].c_str()));

	if (_selectedChar == 1)
	{
		_player = new lee;
		_player->init();
	}
	if (_selectedChar == 2)
	{
		_player = new lee;
		_player->init();
	}
	if (_selectedChar == 3)
	{
		_player = new lee;
		_player->init();
	}
	if (_selectedChar == 4)
	{
		_player = new lee;
		_player->init();
	}

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
	IMAGEMANAGER->render("픽셀라인", getMemDC(), 0, 0);
	IMAGEMANAGER->render("백그라운드", getMemDC(), 0, 0);

	_player->render();
	_dummy->render();
}