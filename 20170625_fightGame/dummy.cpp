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
	KEYANIMANAGER->addArrayFrameAnimation("���̿�������", "����", dummyLeftStop, 6, 10, true);

	int dummyLeftHit[] = { 7, 8, 9 };
	KEYANIMANAGER->addArrayFrameAnimation("���̿��ʸ���", "����", dummyLeftHit, 3, 10, false, leftHit, this);

	ani = KEYANIMANAGER->findAnimation("���̿��ʸ���");
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
		ani = KEYANIMANAGER->findAnimation("���̿�������");
		img->aniRender(getMemDC(), rc.left, rc.top, ani);
		break;
	case DUMMYSTATE_LEFT_HIT:
		ani = KEYANIMANAGER->findAnimation("���̿��ʸ���");
		img->aniRender(getMemDC(), rc.left, rc.top, ani);
		break;
	case DUMMYSTATE_RIGHT_STOP:
		ani = KEYANIMANAGER->findAnimation("���̿�������");
		img->aniRender(getMemDC(), rc.left, rc.top, ani);
		break;
	case DUMMYSTATE_RIGHT_HIT:
		ani = KEYANIMANAGER->findAnimation("���̿�������");
		img->aniRender(getMemDC(), rc.left, rc.top, ani);
		break;
	}
}

void dummy::leftHit(void* obj)
{
	dummy* d = (dummy*)obj;
	d->setDummyState(DUMMYSTATE_LEFT_STOP);
	d->setDummyAni(KEYANIMANAGER->findAnimation("���̿�������"));
	d->getAni()->start();
}

void dummy::rightHit(void* obj)
{
	dummy* d = (dummy*)obj;
	d->setDummyState(DUMMYSTATE_RIGHT_STOP);
	d->setDummyAni(KEYANIMANAGER->findAnimation("���̿�������"));
	d->getAni()->start();
}