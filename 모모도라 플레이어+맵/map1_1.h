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

	//���̵��� ���� ����Ÿ�� �ֱ����� �Լ�
	void mapMove();

	map1_1();
	~map1_1();
};

