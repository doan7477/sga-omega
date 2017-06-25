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
	IMAGEMANAGER->addImage("���ù��", "image/���þ�/background.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�׵θ�", "image/���þ�/�׵θ�.bmp", 179, 185, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI", "image/���þ�/vs.bmp", 180, 234, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("�����伱��", "image/���þ�/������.bmp", 310, 486, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ϸ�����", "image/���þ�/�ϸ�.bmp", 310, 486, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�罺�ɼ���", "image/���þ�/�罺��.bmp", 310, 486, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�������", "image/���þ�/�����.bmp", 310, 486, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("������ҹ��", "image/���þ�/����ҹ��.bmp", 179, 185, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ϸ��ҹ��", "image/���þ�/�ϸ� ���.bmp", 179, 185, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�罺�ɶҹ��", "image/���þ�/�罺�ҹ��.bmp", 179, 185, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����ҹ��", "image/���þ�/����� �Ϲ��.bmp", 179, 185, true, RGB(255, 0, 255));

	SOUNDMANAGER->play("����", 0.1f);

	_characterName[0] = "������ҹ��";
	_characterName[1] = "�ϸ��ҹ��";
	_characterName[2] = "�罺�ɶҹ��";
	_characterName[3] = "�����ҹ��";

	_showName[0] = "�����伱��";
	_showName[1] = "�ϸ�����";
	_showName[2] = "�罺�ɼ���";
	_showName[3] = "�������";

	_nowCharacter = 0;
	_alpha = 255;
	_isSelect = false;

	for (int i = 0;i < 4;i++)
	{
		_selectRc[i] = RectMake(10 + i * 200, WINSIZEY / 2 + 100, 179, 185);
	}

	for (int i = 0;i < 2;i++)
	{
		_showRc[i] = RectMake(50 + i * 350, 50, 310, 486);
	}

	return S_OK;
}

void selectScene::release()
{

}

void selectScene::update() 
{
	SOUNDMANAGER->update();
	inputKey();
	if (_isSelect) _alpha -= 10;
	if (_alpha < 10)
	{
		SOUNDMANAGER->stop("����");
		SOUNDMANAGER->play("���Ӿ�", 0.1f);
		SCENEMANAGER->changeScene("�ΰ��Ӿ�");
	}
}

void selectScene::render() 
{
	IMAGEMANAGER->findImage("���ù��")->alphaRender(getMemDC(), 0, 0, _alpha);
	IMAGEMANAGER->findImage("UI")->alphaRender(getMemDC(), WINSIZEX / 2 - 100, 200, _alpha);
	for (int j = 0;j < 4;j++)
	{
		IMAGEMANAGER->findImage(_showName[_nowCharacter])->alphaRender(getMemDC(), _showRc[0].left, _showRc[0].top, _alpha);
	}
	for (int i = 0;i < 4;i++)
	{
		//Rectangle(getMemDC(), _selectRc[i].left, _selectRc[i].top, _selectRc[i].right, _selectRc[i].bottom);
		IMAGEMANAGER->findImage(_characterName[i])->alphaRender(getMemDC(), _selectRc[i].left, _selectRc[i].top, _alpha);
		IMAGEMANAGER->findImage("�׵θ�")->alphaRender(getMemDC(), _selectRc[_nowCharacter].left, _selectRc[_nowCharacter].top, _alpha);
	}
}

void selectScene::inputKey()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_nowCharacter++;
		if (_nowCharacter > 3) _nowCharacter = 0;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_nowCharacter--;
		if (_nowCharacter < 0) _nowCharacter = 3;
	}
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		_isSelect = true;
		char temp[128];
		vector<string> vStr;

		if (_nowCharacter == 0) vStr.push_back(itoa(1, temp, 10));
		if (_nowCharacter == 1) vStr.push_back(itoa(2, temp, 10));
		if (_nowCharacter == 2) vStr.push_back(itoa(3, temp, 10));
		if (_nowCharacter == 3) vStr.push_back(itoa(4, temp, 10));

		TXTDATA->txtSave("ĳ���ͼ���.txt", vStr);

	}
}