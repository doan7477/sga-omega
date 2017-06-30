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
	//npc �̹��� �ҷ�����
	_npcImg = IMAGEMANAGER->addImage("shop�⺻", "image/shopNPC.bmp", 54,108, true, RGB(255,0,255));
	_npcFrameImg = IMAGEMANAGER->addFrameImage("shop���", "image/shopNPC2.bmp", 756, 108, 14, 1, true, RGB(255, 0, 255));
	_npcRc = RectMake(0, 0, 138, 130);

	//shopâ �̹��� �ҷ�����
	_shopBackground = IMAGEMANAGER->addImage("�����۸���Ʈ", "image/itemList.bmp", 498,210, true, RGB(255,0,255));
	_shopSelect = IMAGEMANAGER->addFrameImage("�����ۼ���", "image/itemSelect.bmp", 192, 27, 8, 1, true, RGB(255,0,255));

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

		if (_count % 200 == 0)	//������ �̹����� ���� 
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

		if (_index > IMAGEMANAGER->findImage("shop���")->getMaxFrameX())
		{
			_index = _count2 = 0;
			_showFrameNPC = false;
		}
		IMAGEMANAGER->findImage("shop���")->setFrameX(_index);
	}
}

void shop::render(void)
{
	if (_showFrameNPC)
		IMAGEMANAGER->findImage("shop���")->frameRender(getMemDC(), WINSIZEX / 2, WINSIZEY / 2);

	if (!_showFrameNPC)
		IMAGEMANAGER->findImage("shop�⺻")->render(getMemDC(), WINSIZEX / 2, WINSIZEY / 2);

}