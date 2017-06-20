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
	selectRC = RectMake(WINSIZEX - 300, 600 - 75, 180, 41);
	selectRC2 = RectMake(WINSIZEX - 410, 600 - 75 -70 , 150, 41);
	selectRC3 = RectMake(WINSIZEX - 180, 600 - 75 - 70, 150, 41);

	_zerg.circle = RectMake(118, WINSIZEY/2 + 100, 148, 60);
	_zerg.select = false;
	_zerg.choice = false;
	_zerg.num = 1;
	_zerg.kind = RectMake(98, 200, 196, 220);
	_zerg.i_kind = IMAGEMANAGER->findImage("Àú±×");
	_protoss.circle = RectMake(_zerg.circle.right + 70, WINSIZEY / 2 + 100, 148, 60);
	_protoss.select = false;
	_protoss.choice = false;
	_protoss.num = 2;
	_protoss.kind = RectMake(_zerg.circle.right + 55, 215, 180, 212);
	_protoss.i_kind = IMAGEMANAGER->findImage("ÇÁ·ÎÅä½º");
	_terran.circle = RectMake(_protoss.circle.right + 70, WINSIZEY / 2 + 100, 148, 60);
	_terran.select = false;
	_terran.choice = false;
	_terran.num = 3;
	_terran.kind = RectMake(_protoss.circle.right - 10, 230, 232, 208);
	_terran.i_kind = IMAGEMANAGER->findImage("Å×¶õ");

	alpha = 255;

	_currentFrameX = _currentFrameY = 0;
	_count = 0;

	return S_OK;
}

void selectScene::release()
{

}

void  selectScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->changeScene("°ÔÀÓ¾À");
	}
	if (PtInRect(&_zerg.kind, _ptMouse))
	{
		_zerg.select = true;
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_zerg.choice = true;

			char temp[128];
			vector<string> vStr;

			vStr.push_back(itoa(_zerg.num, temp, 10));
			TXTDATA->txtSave("OmegaShooting.txt", vStr);

			SCENEMANAGER->changeScene("°ÔÀÓ¾À");
		}
	}
	else _zerg.select = false;
	if (PtInRect(&_protoss.kind, _ptMouse))
	{
		_protoss.select = true;
	}
	else _protoss.select = false;
	if (PtInRect(&_terran.kind, _ptMouse))
	{
		_terran.select = true;
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_terran.choice = true;

			char temp[128];
			vector<string> vStr;

			vStr.push_back(itoa(_terran.num, temp, 10));
			TXTDATA->txtSave("OmegaShooting.txt", vStr);

			SCENEMANAGER->changeScene("°ÔÀÓ¾À");
		}
	}
	else _terran.select = false;

	imageFrame();
}

void  selectScene::render()
{
	IMAGEMANAGER->render("¼±ÅÃ¾ÀµÞ¹è°æ", getMemDC(), 0, 0);
	//Rectangle(getMemDC(), selectRC.left, selectRC.top, selectRC.right, selectRC.bottom);
	//Rectangle(getMemDC(), selectRC2.left, selectRC2.top, selectRC2.right, selectRC2.bottom);
	//Rectangle(getMemDC(), selectRC3.left, selectRC3.top, selectRC3.right, selectRC3.bottom);
	
	IMAGEMANAGER->findImage("circle")->frameRender(getMemDC(), _zerg.circle.left, _zerg.circle.top, _currentFrameX, _currentFrameY);
	IMAGEMANAGER->findImage("circle")->frameRender(getMemDC(), _protoss.circle.left, _protoss.circle.top, _currentFrameX, _currentFrameY);
	IMAGEMANAGER->findImage("circle")->frameRender(getMemDC(), _terran.circle.left, _terran.circle.top, _currentFrameX, _currentFrameY);
	if(!_zerg.select)_zerg.i_kind->frameRender(getMemDC(), _zerg.kind.left, _zerg.kind.top, _currentFrameX, _currentFrameY);
	if(!_protoss.select)_protoss.i_kind->frameRender(getMemDC(), _protoss.kind.left, _protoss.kind.top, _currentFrameX, _currentFrameY);
	if(!_terran.select)_terran.i_kind->frameRender(getMemDC(), _terran.kind.left, _terran.kind.top, _currentFrameX, _currentFrameY);
	if (_zerg.select)IMAGEMANAGER->findImage("°¡µð¾ð")->frameRender(getMemDC(), _zerg.kind.left + 50, _zerg.kind.top + 50, _currentFrameX, _currentFrameY);
	if (_protoss.select)IMAGEMANAGER->findImage("Ä³¸®¾î")->frameRender(getMemDC(), _protoss.kind.left, _protoss.kind.top, _currentFrameX, _currentFrameY);
	if (_terran.select)IMAGEMANAGER->findImage("battle")->frameRender(getMemDC(), _terran.kind.left + 100, _terran.kind.top, _currentFrameX, _currentFrameY);

	IMAGEMANAGER->render("selectBox", getMemDC(), selectRC.left, selectRC.top);
	IMAGEMANAGER->render("selectBox2", getMemDC(), selectRC2.left, selectRC2.top);
	//char str[128];
	//
	//sprintf(str, "¿©±ä ¼¿·ºÆ® ¾À");
	//TextOut(getMemDC(), WINSIZEX / 2 - 200, WINSIZEY / 2, str, strlen(str));
}

void selectScene::imageFrame()
{
	_count++;
	if (_count % 10 == 0)
	{
		IMAGEMANAGER->findImage("circle")->setFrameX(IMAGEMANAGER->findImage("circle")->getFrameX() + 1);
		_currentFrameX++;
		if (_currentFrameX > IMAGEMANAGER->findImage("circle")->getMaxFrameX())
		{
			_currentFrameX = 0;
			_count = 0;
		}
	}

}