#include "stdafx.h"
#include "ship.h"


ship::ship()
{
}


ship::~ship()
{
}

HRESULT ship::init(const char* imageName, int x, int y)
{

	_image = IMAGEMANAGER->findImage(imageName);

	_x = x;
	_y = y;

	_angle = 0.0f;

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

	_speed = 0.0f;
	_radius = _image->getFrameWidth() / 2;

	_bullet = new bullet;
	_bullet->init("bullet", 10, 300);

	return S_OK;
}

void ship::release()
{

}

void ship::update()
{
	bulletMove();
	move();
	keyControl();
}

void ship::render()
{
	draw();
	bulletDraw();
}

void ship::draw()
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top);

	//앵글 및 스피드 출력
	char str[128];
	sprintf(str, "%d도, %3.2f", int(_angle * 180 / PI), _speed);
	TextOut(getMemDC(), _rc.left, _rc.top - 15, str, strlen(str));
}

void ship::keyControl()
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
}

void ship::move()
{
	int frame;
	float angle;

	angle = _angle + PI16;
	if (angle >= PI2) angle -= PI2;

	frame = int(angle / PI8);
	_image->setFrameX(frame);

	float elapsedTime = TIMEMANAGER->getElapsedTime();
	float moveSpeed = elapsedTime * 100;

	_x += cosf(_angle) * _speed * moveSpeed;
	_y += -sinf(_angle) * _speed * moveSpeed;

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}

void ship::bulletFire(void)
{
	float x = _x + cosf(_angle) * 50;
	float y = _y + -sinf(_angle) * 50;

	_bullet->fire(x, y, _angle, 300);
}

void ship::bulletMove(void)
{
	_bullet->update();
}

void ship::bulletDraw(void)
{
	_bullet->render();
}