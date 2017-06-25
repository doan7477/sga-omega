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
	//배경 이미지
	IMAGEMANAGER->addImage("백그라운드", "image/한도안/background.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("픽셀라인", "image/한도안/pixelLine,bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	//씬을 등록해둔다

	SCENEMANAGER->addScene("인게임씬", new gameScene);
	SCENEMANAGER->addScene("선택씬", new selectScene);
	
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
	SetTextColor(getMemDC(), RGB(255, 0, 255));
	
	SCENEMANAGER->render();
	
	TIMEMANAGER->render(getMemDC());
	//================================================================================
	//건들지마라 이거도
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
