#pragma once
#include "structure.h"
class tree : public structure
{
private:
	image* _image;
	RECT _rc;
	float _x, _y;
	int _currentFrameX;
	int _currentFrameY;
	bool getBerry;
public:
	HRESULT init(const char* imageName, int x, int y);
	void release();
	void update(bool _isCollision, float x);
	void render(float x, float y);

	RECT getRC() { return _rc; }

	tree();
	~tree();
};

