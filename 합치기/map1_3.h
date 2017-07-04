#pragma once
#include "gameNode.h"
#include "player.h"
#include "structure.h"
#include "puzzleBall.h"


class map1_3 : public gameNode
{
private:
	player* _player;
	structure* _saveBell;
	puzzleBall* _puzzleBall;

	int _count;
	float _camX;
	float _camX2;
	float _camX3;
	float _camY;
	ESCAPE _state;
	int _alpha;
	float _num;
	RECT _messageBox;
	image* _messageImage;

	bool _collision;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void mapMove();
	void mapVibration();

	map1_3();
	~map1_3();
};

