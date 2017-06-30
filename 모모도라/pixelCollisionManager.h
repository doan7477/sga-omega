#pragma once
#include "singletonBase.h"

class pixelCollisionManager : public singletonBase <pixelCollisionManager>
{
private:
	
	COLORREF _color;
	int _r, _g, _b;
	float _probeX, _probeY;

public:
	HRESULT init(void);
	void release(void);

	bool isPixelCollisionTopY(image* destImage, float destX, float destY, image* sourImage);
	bool isPixelCollisionBottomY(image* destImage, float destX, float destY, image* sourImage);
	bool isPixelCollisionLeftX(image* destImage, float destX, float destY, image* sourImage);
	bool isPixelCollisionRightX(image* destImage, float destX, float destY, image* sourImage);

	float getPixelCollisionY(image* destImage, float destX, float destY, image* sourImage);		
	float getPixelCollisionLeftX(char* imgName, char* sourImg, float destX, float destY);


	pixelCollisionManager();
	~pixelCollisionManager();
};

