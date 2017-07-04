#include "stdafx.h"
#include "puzzleBall.h"


puzzleBall::puzzleBall()
{
}


puzzleBall::~puzzleBall()
{
}

HRESULT puzzleBall::init(const char* imageName, int x, int y)
{
	_image = IMAGEMANAGER->findImage(imageName);
	_rock = IMAGEMANAGER->findImage("바위");
	_x = x;
	_y = y;

	_isTurnOn = false;

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

	_rk[0] = RectMake(WINSIZEX / 2 + 548,
		WINSIZEY + 10, _rock->getWidth(), _rock->getHeight());

	_rk[1] = RectMake(WINSIZEX / 2 + 548,
		WINSIZEY + 10 + (_rock->getHeight() * 1),
		_rock->getWidth(), _rock->getHeight());

	_rk[2] = RectMake(WINSIZEX / 2 + 548 - (_rock->getWidth() * 1),
		WINSIZEY + 10,
		_rock->getWidth(), _rock->getHeight());

	_rk[3] = RectMake(WINSIZEX / 2 + 548 - (_rock->getWidth() * 1),
		WINSIZEY + 10 + (_rock->getHeight() * 1),
		_rock->getWidth(), _rock->getHeight());

	_rk[4] = RectMake(WINSIZEX / 2 + 548 - (_rock->getWidth() * 2),
		WINSIZEY + 10,
		_rock->getWidth(), _rock->getHeight());

	_currentFrameX = _currentFrameY = 0;
	_time = 0;

	return S_OK;
}

void puzzleBall::release()
{

}

void puzzleBall::update()
{
	rockMove();
	frameWork();
	KEYANIMANAGER->update();
	//확인용
	if (KEYMANAGER->isOnceKeyDown(VK_F6))
	{
		if (_isTurnOn)_isTurnOn = false;
		else _isTurnOn = true;
	}
}

void puzzleBall::render(float x, float y)
{
	_image->frameRender(getMemDC(), _rc.left - x, _rc.top - y, _currentFrameX, _currentFrameY);
	for (int i = 0; i < 5; i++)
	{
		_rock->render(getMemDC(), _rk[i].left - x, _rk[i].top - y);
	}
}

void puzzleBall::frameWork(void)
{
	if (_isTurnOn)_currentFrameY = 1;
	else _currentFrameY = 0;

	_count++;
	if (_count % 10 == 0)
	{
		_image->setFrameX(_currentFrameX);
		_currentFrameX++;
		if (_currentFrameX > _image->getMaxFrameX())_currentFrameX = 0;
	}
}

void puzzleBall::rockMove(void)
{
	if (_isTurnOn)
	{
		_time++;
		if (_time > 50)
		{
			if (_rk[4].top >= WINSIZEY / 2 + 227)
			{
				_rk[4].top--;
				_rk[4].bottom--;
			}
		}
		if (_time > 100)
		{
			if (_rk[2].top >= WINSIZEY / 2 + 176)
			{
				_rk[2].top--;
				_rk[2].bottom--;
			}
		}
		if (_time > 150)
		{
			if (_rk[0].top >= WINSIZEY / 2 + 125)
			{
				_rk[0].top--;
				_rk[0].bottom--;
			}
		}
	}
	_rk[3].top = _rk[2].top + _rock->getWidth();
	_rk[3].bottom = _rk[2].bottom + _rock->getWidth();
	_rk[1].top = _rk[0].top + _rock->getWidth();
	_rk[1].bottom = _rk[0].bottom + _rock->getWidth();
}
