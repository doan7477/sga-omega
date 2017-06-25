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
	KEYANIMANAGER->addArrayFrameAnimation("더미왼쪽정지", "더미", dummyLeftStop, 6, 10, true);

	int dummyLeftHit[] = { 7, 8, 9 };
	KEYANIMANAGER->addArrayFrameAnimation("더미왼쪽맞음", "더미", dummyLeftHit, 3, 10, false, leftHit, this);

	ani = KEYANIMANAGER->findAnimation("더미왼쪽맞음");
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
	Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
	switch (dummystate)
	{
	case DUMMYSTATE_LEFT_STOP:
		ani = KEYANIMANAGER->findAnimation("더미왼쪽정지");
		img->aniRender(getMemDC(), rc.left, rc.top, ani);
		break;
	case DUMMYSTATE_LEFT_HIT:
		ani = KEYANIMANAGER->findAnimation("더미왼쪽맞음");
		img->aniRender(getMemDC(), rc.left, rc.top, ani);
		break;
	case DUMMYSTATE_RIGHT_STOP:
		ani = KEYANIMANAGER->findAnimation("더미왼쪽정지");
		img->aniRender(getMemDC(), rc.left, rc.top, ani);
		break;
	case DUMMYSTATE_RIGHT_HIT:
		ani = KEYANIMANAGER->findAnimation("더미왼쪽정지");
		img->aniRender(getMemDC(), rc.left, rc.top, ani);
		break;
	}
}

void dummy::leftHit(void* obj)
{
	dummy* d = (dummy*)obj;
	d->setDummyState(DUMMYSTATE_LEFT_STOP);
	d->setDummyAni(KEYANIMANAGER->findAnimation("더미왼쪽정지"));
	d->getAni()->start();
}

void dummy::rightHit(void* obj)
{
	dummy* d = (dummy*)obj;
	d->setDummyState(DUMMYSTATE_RIGHT_STOP);
	d->setDummyAni(KEYANIMANAGER->findAnimation("더미왼쪽정지"));
	d->getAni()->start();
}