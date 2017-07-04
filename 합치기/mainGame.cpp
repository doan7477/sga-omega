#include "stdafx.h"
#include "mainGame.h"


mainGame::mainGame()
{
}


mainGame::~mainGame()
{
}

//�ʱ�ȭ ���ִ� �Լ�
HRESULT mainGame::init(void)
{
	gameNode::init(true);

	SCENEMANAGER->addScene("�ε���", new loadingScene);
	SCENEMANAGER->addScene("��1", new map1_1);
	SCENEMANAGER->addScene("��2", new map1_2);
	SCENEMANAGER->addScene("��3", new map1_3);
	SCENEMANAGER->addScene("������", new map1_boss);
	SCENEMANAGER->addScene("������", new opening);

	SCENEMANAGER->changeScene("������");

	return S_OK;
}

//�޸� ���� �Լ�
void mainGame::release(void)
{
	gameNode::release();


}

//�������ִ� ��
void mainGame::update(void)
{
	gameNode::update();

	if (KEYMANAGER->isOnceKeyDown('H')) this->init();

	SCENEMANAGER->update();
}

//���Ⱑ �׷��ִ� ��
void mainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============================================================================
	
	SCENEMANAGER->render();
	
	//================================================================================
	//�ǵ������� �̰ŵ�
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
