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
	IMAGEMANAGER->addImage("선택배경", "image/선택씬/background.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("테두리", "image/선택씬/테두리.bmp", 179, 185, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI", "image/선택씬/vs.bmp", 180, 234, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("나루토선택", "image/선택씬/나루토.bmp", 310, 486, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("록리선택", "image/선택씬/록리.bmp", 310, 486, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("사스케선택", "image/선택씬/사스케.bmp", 310, 486, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("사쿠라선택", "image/선택씬/사쿠라.bmp", 310, 486, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("나루토뚝배기", "image/선택씬/나루뚝배기.bmp", 179, 185, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("록리뚝배기", "image/선택씬/록리 배기.bmp", 179, 185, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("사스케뚝배기", "image/선택씬/사스뚝배기.bmp", 179, 185, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("사쿠라뚝배기", "image/선택씬/사쿠라 둑배기.bmp", 179, 185, true, RGB(255, 0, 255));

	SOUNDMANAGER->play("선택", 0.1f);

	_characterName[0] = "나루토뚝배기";
	_characterName[1] = "록리뚝배기";
	_characterName[2] = "사스케뚝배기";
	_characterName[3] = "사쿠라뚝배기";

	_showName[0] = "나루토선택";
	_showName[1] = "록리선택";
	_showName[2] = "사스케선택";
	_showName[3] = "사쿠라선택";

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
		SOUNDMANAGER->stop("선택");
		SOUNDMANAGER->play("게임씬", 0.1f);
		SCENEMANAGER->changeScene("인게임씬");
	}
}

void selectScene::render() 
{
	IMAGEMANAGER->findImage("선택배경")->alphaRender(getMemDC(), 0, 0, _alpha);
	IMAGEMANAGER->findImage("UI")->alphaRender(getMemDC(), WINSIZEX / 2 - 100, 200, _alpha);
	for (int j = 0;j < 4;j++)
	{
		IMAGEMANAGER->findImage(_showName[_nowCharacter])->alphaRender(getMemDC(), _showRc[0].left, _showRc[0].top, _alpha);
	}
	for (int i = 0;i < 4;i++)
	{
		//Rectangle(getMemDC(), _selectRc[i].left, _selectRc[i].top, _selectRc[i].right, _selectRc[i].bottom);
		IMAGEMANAGER->findImage(_characterName[i])->alphaRender(getMemDC(), _selectRc[i].left, _selectRc[i].top, _alpha);
		IMAGEMANAGER->findImage("테두리")->alphaRender(getMemDC(), _selectRc[_nowCharacter].left, _selectRc[_nowCharacter].top, _alpha);
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

		TXTDATA->txtSave("캐릭터선택.txt", vStr);

	}
}