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
	img = IMAGEMANAGER->addFrameImage("����", "image/�ѵ���/dummy.bmp", 0, 0, 704, 106, 11, 2, true, RGB(255, 0, 255));

	int dummyLeftStop[] = { 0, 1, 2, 3, 4, 5 };
	KEYANIMANAGER->addArrayFrameAnimation("���̿�������", "����", dummyLeftStop, 6, 6, true);
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

