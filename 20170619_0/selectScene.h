#pragma once
#include "gameNode.h"

struct tagKind
{
	RECT circle;
	image* i_circle;
	RECT kind;
	image* i_kind;
	int num;
	bool select;
	bool choice;
};

class selectScene : public gameNode
{
private:
	RECT selectRC;
	RECT selectRC2;
	RECT selectRC3;
	RECT circle1;
	RECT circle2;
	RECT circle3;
	RECT checkRC;
	tagKind _terran;
	tagKind _protoss;
	tagKind _zerg;

	int alpha;
	int _count;
	int _currentFrameX, _currentFrameY;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void imageFrame();

	selectScene();
	~selectScene();
};

