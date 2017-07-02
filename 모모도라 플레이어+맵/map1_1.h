#pragma once
#include "gameNode.h"
#include "player.h"
class map1_1 : public gameNode
{
private:
	player* _player;
	ESCAPE _state;
	float _camX;
	float _camX2;
	float _camX3;
	float _camY;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//맵이동을 위한 데이타를 넣기위한 함수
	void mapMove();

	map1_1();
	~map1_1();
};

