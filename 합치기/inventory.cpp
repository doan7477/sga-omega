#include "stdafx.h"
#include "inventory.h"
#include "player.h"


inventory::inventory()
{
}


inventory::~inventory()
{
}

HRESULT inventory::init(void)
{
	_background = IMAGEMANAGER->addImage("인벤토리", "image/이지영/inven.bmp", 962, 722, true, RGB(255, 0, 255));
	_alpha = 0;
	_appear = false;

	return S_OK;
}

void inventory::release(void)
{}

void inventory::update(void)
{}

void inventory::render(void)
{
	if (_appear)
	{
		_alpha += 10;
		if (_alpha >= 255) _alpha = 255;

		_background->alphaRender(getMemDC(), 0, 0, _alpha);
	}
}

void inventory::handleInventory(void)
{
	if (!_appear)
		openInven();
	else if (_appear)
	{
		hideInven();
		_alpha = 0;
	}
}