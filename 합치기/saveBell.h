#pragma once
#include "structure.h"


class saveBell : public structure
{
protected:
	image* _image;
	RECT _rc;
	float _x, _y;
	int _currentFrameX;
	int _currentFrameY;
	int _count;
	int _swingCount;

public:
	HRESULT init(const char* imageName, int x, int y);
	void release();
	void update(bool _isCollision, float x);
	void render(float x, float y);

	BOOL isCollision(bool _isCollision);
	BOOL isLeft(float x);

	virtual RECT getRC() { return _rc; }

	saveBell();
	~saveBell();
};

