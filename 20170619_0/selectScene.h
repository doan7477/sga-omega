#pragma once
#include "gameNode.h"

class selectScene : public gameNode
{
public:
	HRESULT init();
	void release();
	void update();
	void render();

	selectScene();
	~selectScene();
};

