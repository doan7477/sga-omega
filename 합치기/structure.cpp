#include "stdafx.h"
#include "structure.h"


structure::structure()
{
}


structure::~structure()
{
}

HRESULT structure::init(const char* imageName, int x, int y)
{
	_x = x;
	_y = y;
	_image = IMAGEMANAGER->findImage(imageName);
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

	return S_OK;
}
void structure::release()
{

}
void structure::update(bool _isCollision, float x)
{

}
void structure::render(float x, float y)
{
	_image->frameRender(getMemDC(), _rc.left - x, _rc.top - y);
}

