#include "stdafx.h"
#include "starcraftScene.h"
#include "battle.h"
#include "guardian.h"


starcraftScene::starcraftScene()
{
}


starcraftScene::~starcraftScene()
{
}

HRESULT starcraftScene::init()
{
	vector<string> vStr;
	vStr = TXTDATA->txtLoad("OmegaShooting.txt");
	num = (atoi(vStr[0].c_str()));

	if (num == 1)
	{
		_guardian = new guardian;
		_guardian->init("가디언", WINSIZEX / 2, WINSIZEY / 2);
	}

	if (num == 3)
	{
		_battle = new battle;
		_battle->init("battle", WINSIZEX / 2, WINSIZEY / 2);
	}

	return S_OK;
}

void starcraftScene::release()
{

}

void starcraftScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		SCENEMANAGER->changeScene("선택씬");
	}
	if (num == 1) _guardian->update();
	if (num == 3) _battle->update();
}

void starcraftScene::render()
{
	//char str[128];
	//
	//sprintf(str, "여긴 스타 씬");
	//TextOut(getMemDC(), WINSIZEX / 2 + 200, WINSIZEY / 2, str, strlen(str));
	if (num == 1) _guardian->render();
	if (num == 3)_battle->render();
}