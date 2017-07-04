#include "stdafx.h"
#include "map1_3.h"
#include "saveBell.h"

map1_3::map1_3()
{
}


map1_3::~map1_3()
{
}

HRESULT map1_3::init()
{
	_player = new player;
	_player->init();

	_saveBell = new saveBell;
	_saveBell->init("세이브종", WINSIZEX + 800, 530);

	_puzzleBall = new puzzleBall;
	_puzzleBall->init("퍼즐구슬", WINSIZEX / 2 + 740, WINSIZEY / 2 + 150);

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

	_messageImage = IMAGEMANAGER->findImage("기도하기");
	_messageBox = RectMakeCenter(WINSIZEX + 800, 422, _messageImage->getWidth(), _messageImage->getHeight());

	//_camX = 0;
	_camX2 = _camX3 = 0;
	_camY = 10;
	_collision = false;
	_state = NOT_ESCAPE;
	_alpha = 0;

	_count = 0;

	return S_OK;
}
void map1_3::release()
{

}
void map1_3::update()
{
	_player->update();
	//4중으로 가자
	//플레이어 위치는 맵의 중심보다 조금 뒤에 있게
	if (_player->getPlayerCenter().x - 350 > _camX)
		if (_camX < 980)
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
	//플레이어가 맵을 넘어가면 다음 씬으로 이동
	if (_player->getPlayerCenter().x < 0)
	{
		_state = LEFT_ESCAPE;
	}
	else if (_player->getPlayerCenter().x > 2000)
	{
		_state = RIGHT_ESCAPE;
	}
	//플레이어와 종 충돌
	RECT temp;
	if (IntersectRect(&temp, 
		&RectMakeCenter(_player->getPlayerCenter().x, _player->getPlayerCenter().y, _player->getPlayerImage()->getFrameWidth(), _player->getPlayerImage()->getFrameHeight()),
		&_saveBell->getRC()))
	{
		if (_player->getPlayerState() == PLAYERSTATE_LEFT_ATTACK1 || _player->getPlayerState() == PLAYERSTATE_RIGHT_ATTACK1)
		{
			_collision = true;
		}
		else _collision = false;
		if (_alpha < 255) _alpha += 5;

	}
	else _alpha = 0;

	_saveBell->update(_collision,_player->getPlayerCenter().x);
	_puzzleBall->update();

	mapVibration();
	mapMove();
}
void map1_3::render()
{
	IMAGEMANAGER->findImage("배경2")->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _camX2, 0);
	IMAGEMANAGER->findImage("배경1")->loopRender(getMemDC(), &RectMake(0, 100, WINSIZEX, WINSIZEY), _camX3, 0);
	_saveBell->render(_camX, _camY);
	
	_player->render(_camX, _camY);
	IMAGEMANAGER->findImage("맵1-3")->render(getMemDC(), -_camX, -_camY);
	_puzzleBall->render(_camX, _camY);
	if (_player->getPlayerIsJump()) TextOut(getMemDC(), 0, 0, "트루", strlen("트루"));
	if (!_player->getPlayerIsJump()) TextOut(getMemDC(), 0, 0, "폴스", strlen("폴스"));
	_messageImage->alphaRender(getMemDC(), _messageBox.left - _camX, _messageBox.top - _camY, _alpha);
}

void map1_3::mapMove()
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

		SCENEMANAGER->changeScene("맵4");

		break;
	case LEFT_ESCAPE:

		vStr.push_back(itoa(1950, temp, 10));
		vStr.push_back(itoa(600, temp, 10));
		vStr.push_back(itoa(1049, temp, 10));
		vStr.push_back(itoa(0, temp, 10));
		vStr.push_back(itoa(_player->getPlayerState(), temp, 10));
		vStr.push_back(itoa(_player->getPlayerSpeed(), temp, 10));
		vStr.push_back(itoa((int)_player->getPlayerImageName(), temp, 10));
		vStr.push_back(itoa(_player->getPlayerImage()->getFrameX(), temp, 10));


		TXTDATA->txtSave("PlayerPosition.txt", vStr);

		SCENEMANAGER->changeScene("맵2");

		break;
	}
}

void map1_3::mapVibration()
{
	if (_puzzleBall->getRock().top >= WINSIZEY / 2 + 125 && _puzzleBall->getTurnOn())
	{
		_count++;
		if (_count % 6 == 0)
		{
			_camX += 5;
			_camY += 3;
		}
		if (_count % 6 == 1)
		{
			_camX -= 5;
			_camY -= 3;
		}
		if (_count % 6 == 2)
		{
			_camX -= 5;
			_camY += 3;
		}
		if (_count % 6 == 3)
		{
			_camX += 5;
			_camY -= 3;
		}
		if (_count % 6 == 4)
		{
			_camX -= 5;
			_camY += 3;
		}
		if (_count % 6 == 5)
		{
			_camX += 5;
			_camY -= 3;
		}
	}
}