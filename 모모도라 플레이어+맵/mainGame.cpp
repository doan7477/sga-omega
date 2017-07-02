#include "stdafx.h"
#include "mainGame.h"


mainGame::mainGame()
{
}


mainGame::~mainGame()
{
}

//ÃÊ±âÈ­ ÇØÁÖ´Â ÇÔ¼ö
HRESULT mainGame::init(void)
{
	gameNode::init(true);

	SCENEMANAGER->addScene("·Îµù¾À", new loadingScene);
<<<<<<< HEAD:ëª¨ëª¨ë„ë¼ í”Œë ˆì´ì–´+ë§µ/mainGame.cpp
	SCENEMANAGER->addScene("¸Ê1", new map1_1);
	SCENEMANAGER->addScene("¸Ê2", new map1_2);
	SCENEMANAGER->addScene("¸Ê3", new map1_3);
	SCENEMANAGER->addScene("º¸½º·ë", new map1_boss);
=======
	SCENEMANAGER->addScene("°ÔÀÓ¾À", new gameScene);
>>>>>>> 26e3ede34cfd9cf7d2ca3e51f64978aac01852d3:ëª¨ëª¨ë„ë¼/mainGame.cpp
	SCENEMANAGER->addScene("¿ÀÇÁ´×", new opening);

	SCENEMANAGER->changeScene("¿ÀÇÁ´×");

	return S_OK;
}

//¸Þ¸ð¸® ÇØÁ¦ ÇÔ¼ö
void mainGame::release(void)
{
	gameNode::release();


}

//¿¬»êÇØÁÖ´Â °÷
void mainGame::update(void)
{
	gameNode::update();

	if (KEYMANAGER->isOnceKeyDown('H')) this->init();

	SCENEMANAGER->update();
}

//¿©±â°¡ ±×·ÁÁÖ´Â °÷
void mainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============================================================================
	
	SCENEMANAGER->render();
	
	//================================================================================
	//°ÇµéÁö¸¶¶ó ÀÌ°Åµµ
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
