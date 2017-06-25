#pragma once
#include "gameNode.h"
#include "gameScene.h"

class selectScene : public gameNode
{
private:
	RECT _selectRc[4];
	RECT _showRc[4];
	char* _characterName[4];
	char* _showName[4];
	int _nowCharacter;
	int _alpha;
	bool _isSelect;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void inputKey();

	selectScene();
	~selectScene();
};

