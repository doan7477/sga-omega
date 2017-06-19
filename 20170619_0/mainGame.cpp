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

	IMAGEMANAGER->addImage("뒷배경", "background.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bullet", "bullet.bmp", 21, 21, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("battle", "battle.bmp", 0, 0, 1536, 79, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("missilePF", "missilePF.bmp", 0, 0, 576, 44, 16, 1, true, RGB(255, 0, 255));

	//씬을 등록해둔다
	SCENEMANAGER->addScene("선택씬", new selectScene);
	SCENEMANAGER->addScene("게임씬", new starcraftScene);
	
	SCENEMANAGER->changeScene("선택씬");
	
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

	IMAGEMANAGER->findImage("뒷배경")->render(getMemDC(),0,0);
	
	SCENEMANAGER->render();
	
	TIMEMANAGER->render(getMemDC());
	//================================================================================
	//건들지마라 이거도
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
