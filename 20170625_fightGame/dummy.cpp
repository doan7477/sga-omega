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
	currentHp = maxHp = 1000.0f;

	x = WINSIZEX - 200;
	y = WINSIZEY - 50;

	rc = RectMakeCenter(x, y, 50, 50);
	hitRc = RectMakeCenter(x, y, 25, 50);
	dummystate = DUMMYSTATE_LEFT_STOP;
	img = IMAGEMANAGER->addFrameImage("더미", "image/한도안/dummy.bmp", 0, 0, 704, 106, 11, 2, true, RGB(255, 0, 255));

	int dummyLeftStop[] = { 0, 1, 2, 3, 4, 5 };
	KEYANIMANAGER->addArrayFrameAnimation("더미왼쪽정지", "더미", dummyLeftStop, 6, 10, true);

	int dummyLeftHit[] = { 6, 7, 8, 9 };
	KEYANIMANAGER->addArrayFrameAnimation("더미왼쪽맞음", "더미", dummyLeftHit, 3, 6, false, leftHit, this);

	int dummyRightStop[] = { 11,12,13,14,15,16 };
	KEYANIMANAGER->addArrayFrameAnimation("더미오른쪽정지", "더미", dummyRightStop, 6, 10, true);

	int dummyRightHit[] = { 17,18,19,20 };
	KEYANIMANAGER->addArrayFrameAnimation("더미오른쪽맞음", "더미", dummyRightHit, 4, 6, false, rightHit, this);

	ani = KEYANIMANAGER->findAnimation("더미왼쪽정지");
	ani->start();

	hpBar = new progressBar;
	hpBar->init(WINSIZEX / 2 + 50, 50, 300, 20);
	hpBar->setGauge(currentHp, maxHp);


	return S_OK;
}

void dummy::update() 
{
	KEYANIMANAGER->update();
	hitRc = RectMakeCenter(x, y, 25, 50);
	hpBar->update();
	hpBar->setGauge(currentHp, maxHp);
}

void dummy::release()
{

}

void dummy::render()
{
	hpBar->render();
	//Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
	//Rectangle(getMemDC(), hitRc.left, hitRc.top, hitRc.right, hitRc.bottom);

	img->aniRender(getMemDC(), rc.left, rc.top, ani);
	
}

void dummy::leftHit(void* obj)
{
	dummy* d = (dummy*)obj;
	d->setDummyState(DUMMYSTATE_LEFT_STOP);
	d->setDummyAni(KEYANIMANAGER->findAnimation("더미왼쪽정지"));
}

void dummy::rightHit(void* obj)
{
	dummy* d = (dummy*)obj;
	d->setDummyState(DUMMYSTATE_RIGHT_STOP);
	d->setDummyAni(KEYANIMANAGER->findAnimation("더미왼쪽정지"));
}

void dummy::hitDamage(float dam)
{
	currentHp -= dam;
}