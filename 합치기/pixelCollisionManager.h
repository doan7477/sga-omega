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

	bool isPixelCollisionBombTopY(image* destImage, float destX, float destY, image* sourImage);
	bool isPixelCollisionBombBottomY(image* destImage, float destX, float destY, image* sourImage);
	bool isPixelCollisionBombLeftX(image* destImage, float destX, float destY, image* sourImage);
	bool isPixelCollisionBombRightX(image* destImage, float destX, float destY, image* sourImage);

	bool isDownJump(image* destImg, float destX, float destY, image* sourImg);
	bool isLadderEnter(image* destImg, float destX, float destY, image* sourImg);
	bool isLadderLeave(image* destImg, float destX, float destY, image* sourImg);
	bool isLadder(image* destImg, float destX, float destY, image* sourImg);

	float getPixelCollisionY(image* destImage, float destX, float destY, image* sourImage);		
	float getPixelCollisionLeftX(char* imgName, char* sourImg, float destX, float destY);

	bool testPixelCollision(image* destImg, float destX, float destY, image* sourImg, int range, int r, int g, int b);


	pixelCollisionManager();
	~pixelCollisionManager();
};

