#include "stdafx.h"
#include "mainGame.h"


mainGame::mainGame()
{
}


mainGame::~mainGame()
{
}

//초기화 해주는 함수
HRESULT mainGame::init(void)
{
	gameNode::init(true);

	SCENEMANAGER->addScene("로딩씬", new loadingScene);
	SCENEMANAGER->addScene("맵1", new map1_1);
	SCENEMANAGER->addScene("맵2", new map1_2);
	SCENEMANAGER->addScene("맵3", new map1_3);
	SCENEMANAGER->addScene("보스룸", new map1_boss);
	SCENEMANAGER->addScene("오프닝", new opening);

	SCENEMANAGER->changeScene("오프닝");

	return S_OK;
}

//메모리 해제 함수
void mainGame::release(void)
{
	gameNode::release();


}

//연산해주는 곳
void mainGame::update(void)
{
	gameNode::update();

	if (KEYMANAGER->isOnceKeyDown('H')) this->init();

	SCENEMANAGER->update();
}

//여기가 그려주는 곳
void mainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============================================================================
	
	SCENEMANAGER->render();
	
	//================================================================================
	//건들지마라 이거도
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
