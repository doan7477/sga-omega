#include "stdafx.h"
#include "effectTest.h"


effectTest::effectTest()
{
}


effectTest::~effectTest()
{
}

HRESULT effectTest::init()
{
	IMAGEMANAGER->addImage("����", "explosion.bmp", 0, 0, 832, 62, true, RGB(255, 0, 255));

	_effect = new effect;
	_effect->init(IMAGEMANAGER->findImage("����"), 32, 62, 1, 1.0f);

	//					����Ʈ Ű��   �����̸�     �̹�������, ����, ������ ����, ����, FPS, ����Ʈ �ִϸ��̼� �ӵ�, ���۷�
	EFFECTMANAGER->addEffect("����", "explosion.bmp", 832, 62, 32, 62, 1, 1.0f, 300);

	_count = 0;

	return S_OK;
}

void effectTest::release()
{

}

void effectTest::update()
{

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_effect->startEffect(_ptMouse.x, _ptMouse.y);
	}

	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		EFFECTMANAGER->play("����", _ptMouse.x, _ptMouse.y);
	}


	//_count++;
	//
	//if (_count % 10 == 0)
	//{
	//	EFFECTMANAGER->play("����", RND->getFromIntTo(100, 300),RND->getFromIntTo(100, 300));
	//}

	EFFECTMANAGER->update();
	_effect->update();
}

void effectTest::render()
{
	EFFECTMANAGER->render();
	_effect->render();
}
