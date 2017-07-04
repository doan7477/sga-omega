#pragma once
#include "gameNode.h"
#include "player.h"
#include "structure.h"

class map1_2 : public gameNode
{
private:
	player* _player;
	structure* _tree;
	float _camX;
	float _camX2;
	float _camX3;
	float _camY;
	ESCAPE _state;
	bool _getBerry;
	int _alpha;
	float _num;
	RECT _messageBox;
	image* _messageImage;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void mapMove();

	map1_2();
	~map1_2();
};

