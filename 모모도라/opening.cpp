#include "stdafx.h"
#include "opening.h"


opening::opening()
{
}


opening::~opening()
{
}


HRESULT opening::init()
{
	IMAGEMANAGER->addFrameImage("������1", "image/opennig_1.bmp", 27840, 717, 29, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������2", "image/opennig_2.bmp", 27840, 717, 29, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������3", "image/opennig_3.bmp", 27840, 717, 29, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������4", "image/opennig_4.bmp", 27840, 717, 29, 1, true, RGB(255, 0, 255));

	_screen = IMAGEMANAGER->findImage("������1");

	_count = 0;
	_currentX = _currentY = 0;

	return S_OK;
}
void opening::release()
{

}
void opening::update()
{
	_count++;
	if (_count % 5 == 0)
	{
		_currentX++;
		_screen->setFrameX(_currentX);
		if (_screen->getMaxFrameX() == _currentX)
		{
			if (_screen == IMAGEMANAGER->findImage("������1"))
			{
				_screen = IMAGEMANAGER->findImage("������2");
				_currentX = 0;
			}
			else if (_screen == IMAGEMANAGER->findImage("������2"))
			{
				_screen = IMAGEMANAGER->findImage("������3");
				_currentX = 0;
			}
			else if (_screen == IMAGEMANAGER->findImage("������3"))
			{
				_screen = IMAGEMANAGER->findImage("������4");
				_currentX = 0;
			}
			else
			{
				_screen = IMAGEMANAGER->findImage("������3");
				_currentX = 0;
			}
		}
		_count = 0;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) || KEYMANAGER->isOnceKeyDown('A') || KEYMANAGER->isOnceKeyDown('S')
		|| KEYMANAGER->isOnceKeyDown('D'))
	{
		SCENEMANAGER->changeScene("�ε���");
	}
}
void opening::render()
{
	_screen->frameRender(getMemDC(), 0, 0, _currentX, _currentY);
}