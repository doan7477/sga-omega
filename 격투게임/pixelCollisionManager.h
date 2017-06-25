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

	bool pixelCollision(image* destImage, float destX, float destY, image* sourImage);		
	bool playerLWall(image* destImage, float destX, float destY, image* sourImage);
	bool playerRWall(image* destImage, float destX, float destY, image* sourImage);
	float getPixelCollisionY(image* destImage, float destX, float destY, image* sourImage);		// 픽셀충돌 했을 때, 충돌한 곳의 Y값을 가져와주는 함수
	float getPixelCollisionX(image* destImage, float destX, float destY, image* sourImage);		// 픽셀충돌 했을 때, 충돌한 곳의 X값을 가져와주는 함수

	pixelCollisionManager();
	~pixelCollisionManager();
};

