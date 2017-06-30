#include "stdafx.h"
#include "shop.h"


shop::shop()
{
}


shop::~shop()
{
}

HRESULT shop::init(void)
{	
	//npc 이미지 불러오기
	_npcImg = IMAGEMANAGER->addImage("shop기본", "image/shopNPC.bmp", 54,108, true, RGB(255,0,255));
	_npcFrameImg = IMAGEMANAGER->addFrameImage("shop삼분", "image/shopNPC2.bmp", 756, 108, 14, 1, true, RGB(255, 0, 255));
	_npcRc = RectMake(0, 0, 138, 130);

	//shop창 이미지 불러오기
	_shopBackground = IMAGEMANAGER->addImage("아이템리스트", "image/itemList.bmp", 498,210, true, RGB(255,0,255));
	_shopSelect = IMAGEMANAGER->addFrameImage("아이템선택", "image/itemSelect.bmp", 192, 27, 8, 1, true, RGB(255,0,255));

	_count = _count2 = _index = 0;
	_showFrameNPC = _showList = false;

	return S_OK;
}

void shop::release(void)
{} 

void shop::update(void)
{
	if (!_showFrameNPC)
	{
		_count++;

		if (_count % 200 == 0)	//프레임 이미지를 띄운다 
		{
			_showFrameNPC = true;
			_count = 0;
		}
	}
	else if (_showFrameNPC)
	{
		_count2++;

		if(_count2 % 5 == 0)
			_index++;

		if (_index > IMAGEMANAGER->findImage("shop삼분")->getMaxFrameX())
		{
			_index = _count2 = 0;
			_showFrameNPC = false;
		}
		IMAGEMANAGER->findImage("shop삼분")->setFrameX(_index);
	}
}

void shop::render(void)
{
	if (_showFrameNPC)
		IMAGEMANAGER->findImage("shop삼분")->frameRender(getMemDC(), WINSIZEX / 2, WINSIZEY / 2);

	if (!_showFrameNPC)
		IMAGEMANAGER->findImage("shop기본")->render(getMemDC(), WINSIZEX / 2, WINSIZEY / 2);

}