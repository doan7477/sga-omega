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

bool pixelCollisionManager::isPixelCollisionTopY(image* destImage, float destX, float destY, image* sourImage)
{
	_probeY = destY;

	for (int i = _probeY - destImage->getFrameHeight() / 2; i < _probeY; ++i)
	{
		_color = GetPixel(sourImage->getMemDC(), destX, i);

		_r = GetRValue(_color);
		_g = GetGValue(_color);
		_b = GetBValue(_color);

		if ((_r == 0 && _g == 255 && _b == 255))
		{
			return true;
			break;
		}
	}
	return false;
}

bool pixelCollisionManager::isPixelCollisionBottomY(image* destImage, float destX, float destY, image* sourImage)
{
	_probeY = destY + destImage->getFrameHeight() / 2;

	for (float i = _probeY; i < _probeY + 3; i += 0.1f)
	{
		_color = GetPixel(sourImage->getMemDC(), destX, i);

		_r = GetRValue(_color);
		_g = GetGValue(_color);
		_b = GetBValue(_color);

		if ((_r == 255 && _g == 0 && _b == 0))
		{
			return true;
			break;
		}
		else return false;
	}

}

bool pixelCollisionManager::isPixelCollisionLeftX(image* destImage, float destX, float destY, image* sourImage)	
{
	_probeX = destX;

	for (int i = _probeX - 10; i < _probeX; ++i)
	{
		_color = GetPixel(sourImage->getMemDC(), i, destY);

		_r = GetRValue(_color);
		_g = GetGValue(_color);
		_b = GetBValue(_color);

		if ((_r == 0 && _g == 0 && _b == 255))
		{
			return true;
			break;
		}
	}
	return false;
}

bool pixelCollisionManager::isPixelCollisionRightX(image* destImage, float destX, float destY, image* sourImage)
{
	_probeX = destX;

	for (int i = _probeX; i < _probeX + 10; ++i)
	{
		_color = GetPixel(sourImage->getMemDC(), i, destY);

		_r = GetRValue(_color);
		_g = GetGValue(_color);
		_b = GetBValue(_color);

		if ((_r == 0 && _g == 0 && _b == 255))
		{
			return true;
			break;
		}
	}
	return false;
}

bool pixelCollisionManager::isDownJump(image* destImg, float destX, float destY, image* sourImg)
{
	_probeY = destY + destImg->getFrameHeight() / 2;

	for (int i = _probeY; i < _probeY + 3; ++i)
	{
		_color = GetPixel(sourImg->getMemDC(), destX, i);

		_r = GetRValue(_color);
		_g = GetGValue(_color);
		_b = GetBValue(_color);

		if ((_r == 255 && _g == 255 && _b == 0))
		{
			return true;
			break;
		}
		else return false;
	}
}

bool pixelCollisionManager::isLadderEnter(image* destImg, float destX, float destY, image* sourImg)
{
	_probeY = destY + destImg->getFrameHeight() / 2;
	_probeX = destX;

	for (int i = _probeY - 20; i < _probeY; ++i)
	{
		_color = GetPixel(sourImg->getMemDC(), destX, i);

		_r = GetRValue(_color);
		_g = GetGValue(_color);
		_b = GetBValue(_color);

		if (_r == 0 && _g == 255 && _b == 0)
		{
			return true;
			break;
		}
		else return false;
	}
}

bool pixelCollisionManager::isLadderLeave(image* destImg, float destX, float destY, image* sourImg)
{
	_probeY = destY;
	_probeX = destX;

	for (int i = _probeY; i < _probeY + destImg->getFrameHeight() / 2; ++i)
	{
		_color = GetPixel(sourImg->getMemDC(), destX, i);

		_r = GetRValue(_color);
		_g = GetGValue(_color);
		_b = GetBValue(_color);

		if ((_r == 0 && _g == 254 && _b == 0))
		{
			return true;
			break;
		}
		else return false;
	}
}

bool pixelCollisionManager::isLadder(image* destImg, float destX, float destY, image* sourImg)
{
	_probeY = destY;
	_probeX = destX;

	for (int i = _probeY - destImg->getFrameHeight() / 2; i < _probeY + destImg->getFrameHeight() / 2; ++i)
	{
		_color = GetPixel(sourImg->getMemDC(), destX, i);

		_r = GetRValue(_color);
		_g = GetGValue(_color);
		_b = GetBValue(_color);

		if ((_r == 0 && _g == 253 && _b == 0))
		{
			return true;
			break;
		}
		else return false;
	}
}

float pixelCollisionManager::getPixelCollisionY(image* destImage, float destX, float destY, image* sourImage)
{
	_probeY = destY + destImage->getFrameHeight() / 2;

	for (int i = _probeY;
		i < _probeY + 2; ++i)
	{
		_color = GetPixel(sourImage->getMemDC(), destX, i);

		_r = GetRValue(_color);
		_g = GetGValue(_color);
		_b = GetBValue(_color);

		if ((_r == 255 && _g == 0 && _b == 0))
		{
			return destY = (float)i - destImage->getFrameHeight() / 2;
			break;
		}
	}

	return WINSIZEY - 10;
}

float pixelCollisionManager::getPixelCollisionLeftX(char* imgName, char* sourImg, float destX, float destY)
{
	_probeX = destX + IMAGEMANAGER->findImage(imgName)->getFrameWidth() / 2;

	for (int i = _probeX - IMAGEMANAGER->findImage(imgName)->getFrameWidth() / 2; i < _probeX; ++i)
	{
		_color = GetPixel(IMAGEMANAGER->findImage(sourImg)->getMemDC(), i, destY);

		_r = GetRValue(_color);
		_g = GetGValue(_color);
		_b = GetBValue(_color);

		if (!(_r == 255 && _g == 0 && _b == 255))
		{
			return destY = i - IMAGEMANAGER->findImage(imgName)->getFrameWidth() / 2;
			break;
		}
	}

	return WINSIZEY - 10;
}

bool pixelCollisionManager::testPixelCollision(image* destImg, float destX, float destY, image* sourImg, int range, int r, int g, int b, HDC hdc)
{
	_probeY = destY + destImg->getFrameHeight() / 2;

	for (int i = _probeY; i < _probeY + range; ++i)
	{
		_color = GetPixel(sourImg->getMemDC(), destX, i);

		_r = GetRValue(_color);
		_g = GetGValue(_color);
		_b = GetBValue(_color);
		
		TextOut(hdc, destX, _probeY, ".", strlen("."));

		if ((_r == r && _g == g && _b == b))
		{
			return true;
			break;
		}
		else return false;
	}
}