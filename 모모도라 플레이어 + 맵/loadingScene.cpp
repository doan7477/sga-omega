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
		//�ε��� ������ �÷��̾�� ī�޶� ��ǥ
		char temp[128];
		vector<string> vStr;
		vStr.push_back(itoa(200, temp, 10));			//playerX
		vStr.push_back(itoa(600, temp, 10));			//playerY
		vStr.push_back(itoa(0, temp, 10));				//cameraX
		vStr.push_back(itoa(0, temp, 10));				//cameraY
		vStr.push_back(itoa(1, temp, 10));				//playerState
		vStr.push_back(itoa(0, temp, 10));				//playerSpeed
		vStr.push_back(itoa((int)"����", temp, 10));		//playerimage

		TXTDATA->txtSave("PlayerPosition.txt", vStr);

		SCENEMANAGER->changeScene("��1");
	}
}

void loadingScene::render()
{
	_loading->render();
}


void loadingScene::loadingImage()
{
	//�� �̹��� �ε�
	_loading->loadImage("���1", "image/background/background1.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("���2", "image/background/background2.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("��1-1", "image/background/map 1-1.bmp", 1500, 1410, true, RGB(255, 0, 255));
	_loading->loadImage("��1-1�ȼ�", "image/background/map1-1_pixel.bmp", 1500, 1410, true, RGB(255, 0, 255));
	_loading->loadImage("��1-2", "image/background/map 1-2.bmp", 2959, 734, true, RGB(255, 0, 255));
	_loading->loadImage("��1-2�ȼ�", "image/background/map1-2_pixel.bmp", 2959, 734, true, RGB(255, 0, 255));
	_loading->loadImage("��1-3", "image/background/map 1-3.bmp", 1956, 734, true, RGB(255, 0, 255));
	_loading->loadImage("��1-3�ȼ�", "image/background/map1-3_pixel.bmp", 1956, 734, true, RGB(255, 0, 255));
	_loading->loadImage("��1-boss", "image/background/map 1-boss.bmp", 1947, 734, true, RGB(255, 0, 255));
	_loading->loadImage("��1-boss�ȼ�", "image/background/map1-boss_pixel.bmp", 1947, 734, true, RGB(255, 0, 255));

	//�÷��̾� �̹��� �ε�
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
	_loading->loadFrameImage("��ٸ�����", "image/���Ⳳ/ladderEnter.bmp", 450, 222, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("��ٸ�����", "image/���Ⳳ/ladderLeave.bmp", 360, 228, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("��ٸ���������", "image/���Ⳳ/ladderDown.bmp", 189, 111, 3, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("��ٸ��ö󰡱�", "image/���Ⳳ/ladderUp.bmp", 306, 114, 6, 1, true, RGB(255, 0, 255));

	//�÷��̾� ����Ʈ
	_loading->loadFrameImage("����1����Ʈ������", "image/���Ⳳ/attack1right.bmp", 1218, 90, 7, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����1����Ʈ����", "image/���Ⳳ/attack1left.bmp", 1218, 90, 7, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����2����Ʈ������", "image/���Ⳳ/attack2right.bmp", 1176, 114, 7, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����2����Ʈ����", "image/���Ⳳ/attack2left.bmp", 1176, 114, 7, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����3����Ʈ������", "image/���Ⳳ/attack3right.bmp", 2592, 144, 9, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����3����Ʈ����", "image/���Ⳳ/attack3left.bmp", 2592, 144, 9, 1, true, RGB(255, 0, 255));
	

	//������ �� ���� �̹��� �ε�

	//�� �̹��� �ε�

	//�Ѿ� ���� �̹��� �ε�
	_loading->loadFrameImage("ȭ��", "image/���Ⳳ/arrow.bmp", 66, 18, 1, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("ȭ������������Ʈ", "image/���Ⳳ/arrowRemoveEffect.bmp", 350, 64, 6, 1, true, RGB(255, 0, 255));
}

void loadingScene::loadingSound()
{

}
