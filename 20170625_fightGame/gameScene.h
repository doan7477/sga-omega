#pragma once
#include "gameNode.h"
#include "playerManager.h"
#include "lee.h"
#include "dummy.h"

class gameScene : public gameNode
{
private:
	lee* _player;
	dummy* _dummy;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	gameScene();
	~gameScene();
};

