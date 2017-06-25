#include "stdafx.h"
#include "dummy.h"


dummy::dummy()
{
}


dummy::~dummy()
{
}

HRESULT dummy::init()
{
	x = WINSIZEX - 200;
	y = WINSIZEY - 50;

	rc = RectMakeCenter(x, y, 50, 50);
	dummystate = DUMMYSTATE_LEFT_STOP;
	img = IMAGEMANAGER->addFrameImage("더미", "image/한도안/dummy.bmp", 0, 0, 704, 106, 11, 2, true, RGB(255, 0, 255));

	int dummyLeftStop[] = { 0, 1, 2, 3, 4, 5 };
	KEYANIMANAGER->addArrayFrameAnimation("더미왼쪽정지", "더미", dummyLeftStop, 6, 6, true);
	ani = KEYANIMANAGER->findAnimation("더미왼쪽정지");
	ani->start();

	return S_OK;
}

void dummy::update() 
{
	KEYANIMANAGER->update();

	
}

void dummy::release()
{

}

void dummy::render()
{
	img->aniRender(getMemDC(), rc.left, rc.top, ani);
}

