#pragma once
#include "gameNode.h"

class structure : public gameNode
{
protected:
	image* _image;
	RECT _rc;
	float _x, _y;
	int _count;
public:
	virtual HRESULT init(const char* imageName, int x, int y);
	virtual void release();
	virtual void update(bool _isCollision, float x);
	virtual void render(float x, float y);

	virtual RECT getRC() { return _rc; }

	structure();
	~structure();
};

