#pragma once
#include "gameNode.h"

class enemy : public gameNode
{
private:
	image* _imageName;
	RECT _rc;

	int _currentFrameX;
	int _currentFrameY;

	int _count;

public:
	HRESULT init(void);
	HRESULT init(const char* imageName, POINT position);
	void release(void);
	void update(void);
	void render(void);

	void move(void);
	void draw(void);

	bool bulletCountFire(void);

	enemy();
	~enemy();
};

