#pragma once
#include "gameNode.h"
#include "player.h"



class map1_3 : public gameNode
{
private:
	player* _player;
	float _camX;
	float _camX2;
	float _camX3;
	float _camY;
	ESCAPE _state;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void mapMove();

	map1_3();
	~map1_3();
};

