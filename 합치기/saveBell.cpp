#include "stdafx.h"
#include "saveBell.h"


saveBell::saveBell()
{
}


saveBell::~saveBell()
{
}

HRESULT saveBell::init(const char* imageName, int x, int y)
{
	_x = x; 
	_y = y;

	_count = 0;
	_swingCount = 0;

	_rc = RectMakeCenter(_x, _y, 82, 96);
	_image = IMAGEMANAGER->findImage(imageName); 
	_currentFrameX = _currentFrameY = 0;


	return S_OK;
}

void saveBell::release()
{

}

void saveBell::update(bool _isCollision, float x)
{
	if (isCollision(_isCollision))
	{
		if (isLeft(x))
		{
			_currentFrameY = 1;
		}
		else
		{
			_currentFrameY = 2;
		}
	}
	else
	{
		_currentFrameY = 0;
	}
	//이미지 프레임 돌리기
	
	_count++;
	if (_count % 3 == 0)
	{
		_currentFrameX++;
		if (_currentFrameX >= _image->getMaxFrameX())
		{
			if (_swingCount == 3)
			{
				_swingCount = 0;
				_currentFrameY = 0;
			}
			else
			{
				_swingCount += 1;
			}
			_currentFrameX = 0;
		}
		_count = 0;
	}
	

}

void saveBell::render(float x, float y)
{
	_image->frameRender(getMemDC(), _rc.left - x, _rc.top - y, _currentFrameX, _currentFrameY);
}

BOOL saveBell::isCollision(bool _isCollision)
{
	if (_isCollision) return true;
	else return false;

	return false;
}

BOOL saveBell::isLeft(float x)
{
	if (x > (_rc.right - _rc.left) + _rc.left)
	{
		return false;
	}
	else if (x < (_rc.right - _rc.left) + _rc.left)
	{
		return true;
	}

	return false;
}