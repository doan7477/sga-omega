#include "stdafx.h"
#include "map1_2.h"
#include "tree.h"


map1_2::map1_2()
{
}


map1_2::~map1_2()
{
}

HRESULT map1_2::init()
{
	_player = new player;
	_player->init();

	_tree = new tree;
	_tree->init("나무", 550, 520);

	//좌표설정
	vector<string> vStr;
	vStr = TXTDATA->txtLoad("PlayerPosition.txt");
	_player->setPlayerCenterX(atoi(vStr[0].c_str()));
	_player->setPlayerCenterY(atoi(vStr[1].c_str()));
	_camX = atoi(vStr[2].c_str());
	_player->setPlayerState((PLAYERSTATE)atoi(vStr[4].c_str()));
	_player->setPlayerSpeed(atoi(vStr[5].c_str()));
	_player->imageSet((char*)atoi(vStr[6].c_str()), (atoi(vStr[4].c_str())) % 2);
	_player->setPlayerImageFrameX(atoi(vStr[7].c_str()));
	
	_state = NOT_ESCAPE;
	//_camX = 0;
	_camX2 = _camX3 = 0;
	_camY = 20;
	_getBerry = false;

	_messageImage = IMAGEMANAGER->findImage("조사하기");
	_messageBox = RectMakeCenter(550, 422, _messageImage->getWidth(), _messageImage->getHeight());
	_alpha = 0;
	_num = 2.0f;

	return S_OK;
}

void map1_2::release()
{

}

void map1_2::update()
{
	_player->update();
	//4중으로 가자
	//플레이어 위치는 맵의 중심보다 조금 뒤에 있게
	if (_player->getPlayerCenter().x - 350 > _camX)
		if (_camX < 1050)
		{
			//구를땐 카메라 빠르게
			if (_player->getPlayerState() == PLAYERSTATE_LEFT_ROLL ||
				_player->getPlayerState() == PLAYERSTATE_RIGHT_ROLL)
			{
				_camX += ROLLSPEED;
				_camX2 += ROLLSPEED - 1.0f;
				_camX3 += ROLLSPEED - 0.5f;
			}
			// 일반 카메라 속도
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

	if (_player->getPlayerCenter().x < 0)
	{
		_state = LEFT_ESCAPE;
	}
	else if (_player->getPlayerCenter().x > 2000)
	{
		_state = RIGHT_ESCAPE;
	}

	//열매를 따봅시다
	RECT temp;
	if (IntersectRect(&temp,
		&RectMakeCenter(_player->getPlayerCenter().x, _player->getPlayerCenter().y, _player->getPlayerImage()->getFrameWidth(), _player->getPlayerImage()->getFrameHeight()), &_tree->getRC()))
	{
		if (KEYMANAGER->isOnceKeyUp(VK_UP))
		{
			_getBerry = true;
			if (_num > 1.0f) _num -= 0.1f;
		}
		if (_alpha < 255) 
		{
			_alpha += 5;
			_num = 2.0f;
		}
	}
	else _alpha = 0;

	_tree->update(_getBerry, _player->getPlayerCenter().x);

	mapMove();
}

void map1_2::render()
{
	//IMAGEMANAGER->findImage("배경")->render(getMemDC(), 0, 0);
	IMAGEMANAGER->findImage("배경2")->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _camX2, 0);
	IMAGEMANAGER->findImage("배경1")->loopRender(getMemDC(), &RectMake(0, 100, WINSIZEX, WINSIZEY), _camX3, 0);
	_tree->render(_camX, _camY);
	_player->render(_camX, _camY);
	IMAGEMANAGER->findImage("맵1-2")->render(getMemDC(), -_camX, -_camY);
	if (_player->getPlayerIsJump()) TextOut(getMemDC(), 0, 0, "트루", strlen("트루"));
	if (!_player->getPlayerIsJump()) TextOut(getMemDC(), 0, 0, "폴스", strlen("폴스"));
	_messageImage->alphaRender(getMemDC(), _messageBox.left - _camX, _messageBox.top - _camY, _alpha);
	//_messageImage->render(getMemDC(), _messageBox.left - _camX, _messageBox.top - _camY);
	//StretchBlt(getMemDC(), _messageBox.left - _camX, _messageBox.top - _camY, _messageImage->getWidth(), _messageImage->getHeight() * _num,
	//	getMemDC(), _messageBox.left - _camX, _messageBox.top - _camY, _messageImage->getWidth(), _messageImage->getHeight(), RGB(255, 0, 255));

	//IMAGEMANAGER->findImage("맵1-1픽셀")->render(getMemDC(), -_camX, -_camY);
	//IMAGEMANAGER->findImage("맵1-2픽셀")->render(getMemDC(), -_camX, -_camY);
}

void map1_2::mapMove()
{
	char temp[128];
	vector<string> vStr;

	//맵넘어갈때 다음 맵에 좌표를 미리 정해줍시다
	switch (_state)
	{
	case RIGHT_ESCAPE:

		vStr.push_back(itoa(10, temp, 10));
		vStr.push_back(itoa(550, temp, 10));
		vStr.push_back(itoa(0, temp, 10));
		vStr.push_back(itoa(0, temp, 10));
		vStr.push_back(itoa(_player->getPlayerState(), temp, 10));
		vStr.push_back(itoa(_player->getPlayerSpeed(), temp, 10));
		vStr.push_back(itoa((int)_player->getPlayerImageName(), temp, 10));
		vStr.push_back(itoa(_player->getPlayerImage()->getFrameX(), temp, 10));


		TXTDATA->txtSave("PlayerPosition.txt", vStr);

		SCENEMANAGER->changeScene("맵3");

		break;
	case LEFT_ESCAPE:

		vStr.push_back(itoa(1470, temp, 10));
		vStr.push_back(itoa(620, temp, 10));
		vStr.push_back(itoa(509, temp, 10));
		vStr.push_back(itoa(0, temp, 10));
		vStr.push_back(itoa(_player->getPlayerState(), temp, 10));
		vStr.push_back(itoa(_player->getPlayerSpeed(), temp, 10));
		vStr.push_back(itoa((int)_player->getPlayerImageName(), temp, 10));
		vStr.push_back(itoa(_player->getPlayerImage()->getFrameX(), temp, 10));


		TXTDATA->txtSave("PlayerPosition.txt", vStr);

		SCENEMANAGER->changeScene("맵1");

		break;
	}
}