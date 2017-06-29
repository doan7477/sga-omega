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
		SCENEMANAGER->changeScene("ĳ�����þ�");
	}
}

void loadingScene::render()	
{
	_loading->render();
}


void loadingScene::loadingImage()
{
	//�̹����� �������� �ƴϴϱ� ���� ������
	//�̹��� 1���� 300�� �ø��ڴٴ� ����
	for (int i = 0; i < 1000; i++)
	{
		_loading->loadImage("ĳ������", WINSIZEX, WINSIZEY);
	}
}

void loadingScene::loadingSound()
{

}
