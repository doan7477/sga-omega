#include "stdafx.h"
#include "loadingScene.h"


loadingScene::loadingScene()
{
}


loadingScene::~loadingScene()
{

}

HRESULT loadingScene::init()
{
	_loading = new loading;
	_loading->init();

	this->loadingImage();

	return S_OK;
}

void loadingScene::release()
{
	SAFE_DELETE(_loading);
}

void loadingScene::update()
{
	_loading->update();

	if (_loading->loadingDone())
	{
		SCENEMANAGER->changeScene("게임씬");
	}
}

void loadingScene::render()
{
	_loading->render();
}


void loadingScene::loadingImage()
{
	_loading->loadImage("배경", "image/background/background.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 255, 255));
	_loading->loadImage("맵1-1", "image/background/map 1-1.bmp", 1800, 1350, true, RGB(255, 0, 255));
	_loading->loadImage("맵1-1픽셀", "image/background/map1-1_pixel.bmp", 1800, 1350, true, RGB(255, 0, 255));

	_loading->loadFrameImage("정지", "image/봉기남/idle.bmp", 450, 222, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("달리기", "image/봉기남/run.bmp", 900, 222, 10, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("브레이크", "image/봉기남/brake.bmp", 588, 235, 7, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("턴", "image/봉기남/turn.bmp", 207, 228, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("점프", "image/봉기남/jump.bmp", 207, 222, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("폴", "image/봉기남/fall.bmp", 375, 240, 5, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("앉기", "image/봉기남/crouch.bmp", 216, 168, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("일어서기", "image/봉기남/rise.bmp", 120, 210, 2, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("구르기", "image/봉기남/roll.bmp", 768, 204, 8, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("공격1", "image/봉기남/attack1.bmp", 567, 216, 7, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("공격2", "image/봉기남/attack2.bmp", 609, 222, 7, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("공격3", "image/봉기남/attack3.bmp", 1155, 222, 11, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("평지활", "image/봉기남/bow.bmp", 486, 270, 6, 2, true, RGB(255, 0, 255));
}

void loadingScene::loadingSound()
{

}
