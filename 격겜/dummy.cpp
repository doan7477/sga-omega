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
	y = WINSIZEY - 100;

	rc = RectMakeCenter(x, y, 50, 50);
	dummystate = DUMMYSTATE_LEFT_STOP;
	img = IMAGEMANAGER->addFrameImage("����", "move.bmp", 0, 0, 288, 44, 6, 1, true, RGB(255, 0, 255));

	int dummyLeftStop[] = { 0, 1, 2 };
	KEYANIMANAGER->addArrayFrameAnimation("���̿�������", "����", dummyLeftStop, 3, 10, true);
	ani = KEYANIMANAGER->findAnimation("���̿�������");
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

