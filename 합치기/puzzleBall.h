#pragma once
#include "structure.h"
class puzzleBall : public structure
{
protected:
	animation* ani;
	image* _image;
	image* _image2;
	image* _rock;
	RECT _rc;
	RECT _rk[5];

	float _x, _y;
	bool _isTurnOn;
	int _time;
	int _count;
	int _currentFrameX, _currentFrameY;
public:
	HRESULT init(const char* imageName, int x, int y);
	void release();
	void update();
	void render(float x, float y);

	void frameWork(void);
	void rockMove(void);

	RECT getRock(void) { return _rk[0]; }
	bool getTurnOn(void) { return _isTurnOn; }

	puzzleBall();
	~puzzleBall();
};

