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
		SCENEMANAGER->changeScene("���Ӿ�");
	}
}

void loadingScene::render()
{
	_loading->render();
}


void loadingScene::loadingImage()
{
	_loading->loadImage("���", "image/background/background.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 255, 255));
	_loading->loadImage("��1-1", "image/background/map 1-1.bmp", 1500, 1410, true, RGB(255, 0, 255));
	_loading->loadImage("��1-1�ȼ�", "image/background/map1-1_pixel.bmp", 1500, 1410, true, RGB(255, 0, 255));

	_loading->loadFrameImage("����", "image/���Ⳳ/idle.bmp", 450, 222, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�޸���", "image/���Ⳳ/run.bmp", 900, 222, 10, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�극��ũ", "image/���Ⳳ/brake.bmp", 588, 235, 7, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("��", "image/���Ⳳ/turn.bmp", 207, 228, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����", "image/���Ⳳ/jump.bmp", 207, 222, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("��", "image/���Ⳳ/fall.bmp", 375, 240, 5, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�ɱ�", "image/���Ⳳ/crouch.bmp", 216, 168, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�Ͼ��", "image/���Ⳳ/rise.bmp", 120, 210, 2, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("������", "image/���Ⳳ/roll.bmp", 768, 204, 8, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����1", "image/���Ⳳ/attack1.bmp", 567, 216, 7, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����2", "image/���Ⳳ/attack2.bmp", 609, 222, 7, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����3", "image/���Ⳳ/attack3.bmp", 1155, 222, 11, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("��������", "image/���Ⳳ/jumpAttack1.bmp", 483, 216, 7, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����Ȱ", "image/���Ⳳ/bow.bmp", 486, 270, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����Ȱ", "image/���Ⳳ/jumpBow.bmp", 486, 270, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�ɱ�Ȱ", "image/���Ⳳ/crouchBow.bmp", 486, 210, 6, 2, true, RGB(255, 0, 255));
}

void loadingScene::loadingSound()
{

}
