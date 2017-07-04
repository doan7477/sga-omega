#pragma once
#include "gameNode.h"
#include <vector>

struct tagArrow
{
	image* img;
	RECT rc;
	float x, y;
	float angle;
	float speed;
	float radius;
	bool fire;
	bool isRight;
	int count;
};

class arrow : public gameNode
{
private:
	typedef vector<tagArrow> arrArrow;
	typedef vector<tagArrow>::iterator iterArrow;

private:
	arrArrow _vArrow;
	const char* _imgName;

public:
	HRESULT init(const char* imgName);
	void release();
	void update();
	void render(float x, float y);

	void move();
	void fire(float x, float y, float speed, float angle, bool isRight = TRUE);
	void removeArrow(int arrNum);

	arrow();
	~arrow();
};

