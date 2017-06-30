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
		SCENEMANAGER->changeScene("°ÔÀÓ¾À");
	}
}

void loadingScene::render()
{
	_loading->render();
}


void loadingScene::loadingImage()
{
	_loading->loadImage("¹è°æ", "image/background/background.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 255, 255));
	_loading->loadImage("¸Ê1-1", "image/background/map 1-1.bmp", 1500, 1410, true, RGB(255, 0, 255));
	_loading->loadImage("¸Ê1-1ÇÈ¼¿", "image/background/map1-1_pixel.bmp", 1500, 1410, true, RGB(255, 0, 255));

	_loading->loadFrameImage("Á¤Áö", "image/ºÀ±â³²/idle.bmp", 450, 222, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("´Þ¸®±â", "image/ºÀ±â³²/run.bmp", 900, 222, 10, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("ºê·¹ÀÌÅ©", "image/ºÀ±â³²/brake.bmp", 588, 235, 7, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("ÅÏ", "image/ºÀ±â³²/turn.bmp", 207, 228, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Á¡ÇÁ", "image/ºÀ±â³²/jump.bmp", 207, 222, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Æú", "image/ºÀ±â³²/fall.bmp", 375, 240, 5, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("¾É±â", "image/ºÀ±â³²/crouch.bmp", 216, 168, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("ÀÏ¾î¼­±â", "image/ºÀ±â³²/rise.bmp", 120, 210, 2, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("±¸¸£±â", "image/ºÀ±â³²/roll.bmp", 768, 204, 8, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("°ø°Ý1", "image/ºÀ±â³²/attack1.bmp", 567, 216, 7, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("°ø°Ý2", "image/ºÀ±â³²/attack2.bmp", 609, 222, 7, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("°ø°Ý3", "image/ºÀ±â³²/attack3.bmp", 1155, 222, 11, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Á¡ÇÁ°ø°Ý", "image/ºÀ±â³²/jumpAttack1.bmp", 483, 216, 7, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("ÆòÁöÈ°", "image/ºÀ±â³²/bow.bmp", 486, 270, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Á¡ÇÁÈ°", "image/ºÀ±â³²/jumpBow.bmp", 486, 270, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("¾É±âÈ°", "image/ºÀ±â³²/crouchBow.bmp", 486, 210, 6, 2, true, RGB(255, 0, 255));
}

void loadingScene::loadingSound()
{

}
