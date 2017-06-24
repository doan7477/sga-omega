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

	//씬을 등록해둔다

	SCENEMANAGER->addScene("변태영감씬", new playerManager);
	
	SCENEMANAGER->changeScene("변태영감씬");
	
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



	SCENEMANAGER->update();

}

//여기가 그려주는 곳
void mainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============================================================================
	SetTextColor(getMemDC(), RGB(255, 0, 255));
	
	SCENEMANAGER->render();
	
	TIMEMANAGER->render(getMemDC());
	//================================================================================
	//건들지마라 이거도
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
