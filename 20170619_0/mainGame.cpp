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
	IMAGEMANAGER->addImage("선택씬뒷배경", "selectSceneBGI.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bullet", "bullet.bmp", 21, 21, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("selectBox", "selectBox.bmp", 436, 89, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("selectBox2", "selectBox2.bmp", 408, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("확인박스", "okBox.bmp", 380, 251, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("battle", "battle.bmp", 0, 0, 1536, 79, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("missilePF", "missilePF.bmp", 0, 0, 576, 44, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("circle", "circleBox.bmp", 1480, 60, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("저그", "zerg.bmp", 1960, 220, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("프로토스", "protoss.bmp", 1800, 212, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("테란", "terran.bmp", 2320, 208, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("가디언", "guardian.bmp", 1248, 71, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("캐리어", "carrier.bmp", 7800, 136, 50, 1, true, RGB(255, 0, 255));


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
