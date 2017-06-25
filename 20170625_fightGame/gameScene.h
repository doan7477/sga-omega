#pragma once
#include "gameNode.h"
#include "playerManager.h"
#include "lee.h"
#include "sasuke.h"
#include "naruto.h"
#include "sakura.h"
#include "dummy.h"


class gameScene : public gameNode
{
private:
	vector<string> vStr;
	int _selectedChar;

	playerManager* _player;
	dummy* _dummy;

	int _camX, _camY;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void collision();
	void dummyState();

	gameScene();
	~gameScene();
};

