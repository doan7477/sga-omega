#pragma once
#include "gameNode.h"
#include "bullets.h"

class ship : public gameNode
{
protected:
	bullet* _bullet;

	image* _image;
	RECT _rc;
	float _x, _y;
	float _angle;
	float _speed;
	float _radius;

public:
	virtual HRESULT init(const char* imageName, int x, int y);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void draw();
	virtual void keyControl();
	virtual void move();

	virtual void bulletFire(void);
	virtual void bulletMove(void);
	virtual void bulletDraw(void);

	ship();
	virtual ~ship();
};

