#include "stdafx.h"
#include "selectScene.h"


selectScene::selectScene()
{
}


selectScene::~selectScene()
{
}

HRESULT selectScene::init()
{

	return S_OK;
}

void selectScene::release()
{

}

void  selectScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->changeScene("∞‘¿”æ¿");
	}
}

void  selectScene::render()
{
	char str[128];

	sprintf(str, "ø©±‰ ºø∑∫∆Æ æ¿");
	TextOut(getMemDC(), WINSIZEX / 2 - 200, WINSIZEY / 2, str, strlen(str));
}
