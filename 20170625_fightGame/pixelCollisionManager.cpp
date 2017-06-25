#include "stdafx.h"
#include "pixelCollisionManager.h"


pixelCollisionManager::pixelCollisionManager()
{
}


pixelCollisionManager::~pixelCollisionManager()
{
}

HRESULT pixelCollisionManager::init(void)
{
	_color = NULL;
	_r = _g = _b = 0;
	_probeX = _probeY = 0;


	return S_OK;
}

void pixelCollisionManager::release(void)
{
}

bool pixelCollisionManager::pixelCollision(image* destImage, float destX, float destY, image* sourImage)
{
	_probeY = destY;

	for (int i = _probeY - destImage->getHeight() / 2;
		i < _probeY + destImage->getHeight() / 2; ++i)
	{
		_color = GetPixel(sourImage->getMemDC(), destX, i);

		_r = GetRValue(_color);
		_g = GetGValue(_color);
		_b = GetBValue(_color);

		if (!(_r == 255 && _g == 0 && _b == 255))
		{
			return true;
		}
	}
	return false;
}

bool pixelCollisionManager::playerLWall(image* destImage, float destX, float destY, image* sourImage)
{
	_probeX = destX;

	for (int i = _probeX - 10;
		i < _probeX; ++i)
	{
		_color = GetPixel(sourImage->getMemDC(), i, destY);

		_r = GetRValue(_color);
		_g = GetGValue(_color);
		_b = GetBValue(_color);
		if ((_r == 0 && _g == 0 && _b == 255))
		{
			return true;
		}
	}
	return false;
}

bool pixelCollisionManager::playerRWall(image* destImage, float destX, float destY, image* sourImage)
{
	_probeX = destX;

	for (int i = _probeX;
		i < _probeX + destImage->getFrameWidth() / 4; ++i)
	{
		_color = GetPixel(sourImage->getMemDC(), i, destY);

		_r = GetRValue(_color);
		_g = GetGValue(_color);
		_b = GetBValue(_color);
		if ((_r == 0 && _g == 0 && _b == 255))
		{
			return true;
		}
	}
	return false;
}

float pixelCollisionManager::getPixelCollisionY(image* destImage, float destX, float destY, image* sourImage)
{
	_probeY = destY + destImage->getFrameHeight() / 2;

	for (int i = _probeY - destImage->getFrameHeight() / 2;
		i < _probeY + destImage->getFrameHeight() / 2; ++i)
	{
		_color = GetPixel(sourImage->getMemDC(), destX, i);

		_r = GetRValue(_color);
		_g = GetGValue(_color);
		_b = GetBValue(_color);

		if (_r == 255 && _g == 0 && _b == 0)
		{
			return destY = i - destImage->getFrameHeight() / 2;
		}
	}

	return WINSIZEY - 20;
}
float pixelCollisionManager::getPixelCollisionX(image* destImage, float destX, float destY, image* sourImage)
{
	_probeX = destX;

	for (int i = _probeX - destImage->getFrameWidth() / 2;
		i < _probeX + destImage->getFrameWidth() / 2; ++i)
	{
		_color = GetPixel(sourImage->getMemDC(), i, destY);

		_r = GetRValue(_color);
		_g = GetGValue(_color);
		_b = GetBValue(_color);

		if (_r == 0 && _g == 0 && _b == 255)
		{
			return destX = i - destImage->getFrameWidth() / 2;
		}
	}

	return destX;
}