#include "stdafx.h"
#include "gameScene.h"


gameScene::gameScene()
{
}


gameScene::~gameScene()
{
}

HRESULT gameScene::init()
{
	_player = new player;
	_player->init();
	_camX = 0;
	_camX2 = _camX3 = 0;
	_camY = 100;

	return S_OK;
}

void gameScene::release()
{

}

void gameScene::update() 
{
	_player->update();
	//4������ ����
	//�÷��̾� ��ġ�� ���� �߽ɺ��� ���� �ڿ� �ְ�
	if (_player->getPlayerCenter().x - 350 > _camX)
		if (_camX < 510)
		{
			//������ ī�޶� ������
			if (_player->getPlayerState() == PLAYERSTATE_LEFT_ROLL ||
				_player->getPlayerState() == PLAYERSTATE_RIGHT_ROLL)
			{
				_camX += ROLLSPEED;
				_camX2 += ROLLSPEED - 1.0f;
				_camX3 += ROLLSPEED - 0.5f;
			}
			// �Ϲ� ī�޶� �ӵ�
			else
			{
				_camX += _player->getPlayerSpeed();
				_camX2 += _player->getPlayerSpeed() - 1.0f;
				_camX3 += _player->getPlayerSpeed() - 0.5f;
			}
		}

	if (_player->getPlayerCenter().x - 350 < _camX)
		if (_camX > 0)
		{
			if (_player->getPlayerState() == PLAYERSTATE_LEFT_ROLL ||
				_player->getPlayerState() == PLAYERSTATE_RIGHT_ROLL)
			{
				_camX -= ROLLSPEED;
				_camX2 -= ROLLSPEED - 1.0f;
				_camX3 -= ROLLSPEED - 0.5f;
			}
			else
			{
				_camX -= _player->getPlayerSpeed();
				_camX2 -= _player->getPlayerSpeed() - 1.0f;
				_camX3 -= _player->getPlayerSpeed() - 0.5f;
			}
		}
}

void gameScene::render() 
{
	//IMAGEMANAGER->findImage("���")->render(getMemDC(), 0, 0);
	IMAGEMANAGER->findImage("���2")->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _camX2, 0);
	IMAGEMANAGER->findImage("���1")->loopRender(getMemDC(), &RectMake(0, 100, WINSIZEX, WINSIZEY), _camX3, 0);
	_player->render(_camX,_camY);
	IMAGEMANAGER->findImage("��1-1")->render(getMemDC(), -_camX, -_camY);
	if (_player->getPlayerIsJump()) TextOut(getMemDC(), 0, 0, "Ʈ��", strlen("Ʈ��"));
	if (!_player->getPlayerIsJump()) TextOut(getMemDC(), 0, 0, "����", strlen("����"));
	//IMAGEMANAGER->findImage("��1-1�ȼ�")->render(getMemDC(), -_camX, -_camY);
}
