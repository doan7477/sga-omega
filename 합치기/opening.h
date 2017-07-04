#pragma once
#include "gameNode.h"

class opening : public gameNode
{
private:
	image* _screen;
	int _count;
	int _currentX;
	int _currentY;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	opening();
	~opening();
};

