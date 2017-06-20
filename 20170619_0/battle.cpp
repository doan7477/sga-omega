#include "stdafx.h"
#include "battle.h"


battle::battle()
{
}


battle::~battle()
{
}

HRESULT battle::init(const char* imageName, int x, int y)
{
	ship::init(imageName, x, y);

	_missile = new missilePF;
	_missile->init("missilePF", 30, 600);

	return S_OK;
}

void battle::release(void)
{
	ship::release();
}

void battle::update(void)
{
	ship::update();

	missileMove();
	keyControl();
}

void battle::render(void)
{
	ship::render();
	missileDraw();
}

void battle::keyControl(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_angle -= 0.06f;
		if (_angle <= 0) _angle += PI2;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_angle += 0.06f;
		if (_angle >= PI2) _angle -= PI2;
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_speed += 0.02f;
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_speed -= 0.02f;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		bulletFire();
	}

	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		missileFire();
	}
}

void battle::missileFire()
{
	float x = _x + cosf(_angle) * 50;
	float y = _y + -sinf(_angle) * 50;

	_missile->fire(x, y, _angle, 400);
}

void battle::missileMove()
{
	_missile->update();
}

void battle::missileDraw()
{
	_missile->render();
}