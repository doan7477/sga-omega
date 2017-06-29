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
	int count;
};

class arrow : public gameNode
{
private:

public:
	arrow();
	~arrow();
};

