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

	//���� ����صд�

	SCENEMANAGER->addScene("���¿�����", new playerManager);
	
	SCENEMANAGER->changeScene("���¿�����");
	
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



	SCENEMANAGER->update();

}

//���Ⱑ �׷��ִ� ��
void mainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============================================================================
	SetTextColor(getMemDC(), RGB(255, 0, 255));
	
	SCENEMANAGER->render();
	
	TIMEMANAGER->render(getMemDC());
	//================================================================================
	//�ǵ������� �̰ŵ�
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
