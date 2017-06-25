#pragma once
#include "gameNode.h"

enum DUMMYSTATE
{
	DUMMYSTATE_LEFT_STOP,
	DUMMYSTATE_RIGHT_STOP,
	DUMMYSTATE_LEFT_HIT,
	DUMMYSTATE_RIGHT_HIT
};

class dummy : public gameNode
{
private:
	RECT rc;
	float x, y;
	image* img;
	animation* ani;
	DUMMYSTATE dummystate;

public:
	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render();

	dummy();
	~dummy();
};

