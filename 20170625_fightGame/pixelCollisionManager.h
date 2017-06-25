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
	float getPixelCollisionY(image* destImage, float destX, float destY, image* sourImage);		// �ȼ��浹 ���� ��, �浹�� ���� Y���� �������ִ� �Լ�
	float getPixelCollisionX(image* destImage, float destX, float destY, image* sourImage);		// �ȼ��浹 ���� ��, �浹�� ���� X���� �������ִ� �Լ�

	pixelCollisionManager();
	~pixelCollisionManager();
};

