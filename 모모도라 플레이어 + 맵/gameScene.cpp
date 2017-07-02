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
	_camY = 100;

	return S_OK;
}

void gameScene::release()
{

}

void gameScene::update() 
{
	_player->update();

	//if (_player->getPlayerCenter().x - _camX > WINSIZEX / 2) _camX += _player->getPlayerSpeed();
	//if (_player->getPlayerCenter().x - _camX < WINSIZEX / 2) _camX -= _player->getPlayerSpeed();
	//if (_player->getPlayerCenter().y - _camY < WINSIZEY / 2) _camY -= 3.0f;
	//if (_player->getPlayerCenter().y - _camY > WINSIZEY / 2) _camY += 3.0f;

	if (_player->getPlayerCenter().x - 350 > _camX)
		if (_camX < 510)
		{
			if (_player->getPlayerState() == PLAYERSTATE_LEFT_ROLL ||
				_player->getPlayerState() == PLAYERSTATE_RIGHT_ROLL)
			{
				_camX += ROLLSPEED;
			}
			else _camX += _player->getPlayerSpeed();
		}

	if (_player->getPlayerCenter().x - 350 < _camX)
		if (_camX > 0)
		{
			if (_player->getPlayerState() == PLAYERSTATE_LEFT_ROLL ||
				_player->getPlayerState() == PLAYERSTATE_RIGHT_ROLL)
			{
				_camX -= ROLLSPEED;
			}
			else _camX -= _player->getPlayerSpeed();
		}
}

void gameScene::render() 
{
	IMAGEMANAGER->findImage("배경")->render(getMemDC(), 0, 0);
	_player->render(_camX, _camY);
	//IMAGEMANAGER->findImage("맵1-1")->render(getMemDC(), -_camX, -_camY);
	IMAGEMANAGER->findImage("맵1-1픽셀")->render(getMemDC(), -_camX, -_camY);
	char str[128];
	sprintf(str, "%.1f %.1f", (float)_player->getPlayerCenter().x, (float)_player->getPlayerCenter().y);
	TextOut(getMemDC(), 0, 30, str, strlen(str));
	char str2[128];
	sprintf(str2, "%.1f", (float)_player->getPlayerJumpPower());
	TextOut(getMemDC(), 0, 60, str2, strlen(str2));
	if (_player->getPlayerIsLadder()) TextOut(getMemDC(), 0, 0, "사다리트루", strlen("사다리트루"));
	if (!_player->getPlayerIsLadder()) TextOut(getMemDC(), 0, 0, "사다리폴스", strlen("사다리폴스"));
	if (_player->getPlayerIsGround()) TextOut(getMemDC(), 100, 0, "땅트루", strlen("땅트루"));
	if (!_player->getPlayerIsGround()) TextOut(getMemDC(), 100, 0, "땅폴스", strlen("땅폴스"));
	if (_player->getPlayerIsJump()) TextOut(getMemDC(), 200, 0, "점프트루", strlen("점프트루"));
	if (!_player->getPlayerIsJump()) TextOut(getMemDC(), 200, 0, "점프폴스", strlen("점프폴스"));
}
