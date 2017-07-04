#include "stdafx.h"
#include "tree.h"


tree::tree()
{
}


tree::~tree()
{
}

HRESULT tree::init(const char* imageName, int x, int y)
{
	_x = x;
	_y = y;

	_image = IMAGEMANAGER->findImage(imageName);
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

	_currentFrameX = _currentFrameY = 0;

	getBerry = false;

	return S_OK;
}
void tree::release()
{

}
void tree::update(bool _isCollision, float x)
{
	if (_isCollision == true)
	{
		_currentFrameX = 1;
	}
	else _currentFrameX = 0;
}
void tree::render(float x, float y)
{
	//Rectangle(getMemDC(), _rc.left - x, _rc.top - y, _rc.right - x, _rc.bottom - y);
	_image->frameRender(getMemDC(), _rc.left - x, _rc.top - y, _currentFrameX, _currentFrameY);
}