#include "stdafx.h"
#include "bullets.h"

throwKnife::throwKnife() {}
throwKnife::~throwKnife() {}

HRESULT throwKnife::init(int bulletMax, int range)
{
	_range = range;
	_bulletMax = bulletMax;

	return S_OK;
}
void throwKnife::release(void)
{
	_vBullet.clear();
}
void throwKnife::update(void)
{
	frameWork();
	move();
}
void throwKnife::render(void)
{
	draw();
}

void throwKnife::fire(float x, float y, int num)
{
	if (_bulletMax < _vBullet.size()) return;
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new image;
	bullet.bulletImage->init("image/throw_knife.bmp", 78, 28, 2, 2, true, RGB(255, 0, 255));
	bullet.speed = 15.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet._isLeft = num;
	bullet.count = 0;
	bullet._currentX = 0;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.bulletImage->getFrameWidth(), bullet.bulletImage->getFrameHeight());

	_vBullet.push_back(bullet);

}
void throwKnife::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		if (_viBullet->_isLeft % 2 == 0)_viBullet->x -= _viBullet->speed;
		if (_viBullet->_isLeft % 2 == 1)_viBullet->x += _viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getFrameWidth(),
			_viBullet->bulletImage->getFrameHeight());

		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void throwKnife::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->_isLeft % 2 == 0)_viBullet->bulletImage->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top, _viBullet->_currentX, 1);
		if (_viBullet->_isLeft % 2 == 1)_viBullet->bulletImage->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top, _viBullet->_currentX, 0);
	}
}

void throwKnife::frameWork(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->count++;
		if (_viBullet->count % 5 == 0)
		{
			_viBullet->bulletImage->setFrameX(_viBullet->_currentX);
			_viBullet->_currentX++;

			if (_viBullet->_currentX > _viBullet->bulletImage->getMaxFrameX())_viBullet->_currentX = 0;
		}
	}
}

void throwKnife::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}



