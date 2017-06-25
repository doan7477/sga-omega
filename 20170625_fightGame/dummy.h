#pragma once
#include "gameNode.h"
#include "progressBar.h"

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
	RECT hitRc;
	float x, y;
	image* img;
	animation* ani;
	DUMMYSTATE dummystate;
	progressBar* hpBar;
	float currentHp, maxHp;

public:
	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render();

	void hitDamage(float dam);

	static void leftHit(void* obj);
	static void rightHit(void* obj);

	RECT getRect() { return hitRc; }
	animation* getAni() { return ani; }
	DUMMYSTATE getState() { return dummystate; }
	POINT getCenter() { return PointMake(x, y); }

	void setDummyState(DUMMYSTATE ds) { dummystate = ds; ani->start(); }
	void setDummyAni(animation* an) { ani = an; }

	dummy();
	~dummy();
};

