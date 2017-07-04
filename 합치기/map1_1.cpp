#include "stdafx.h"
#include "map1_1.h"


map1_1::map1_1()
{
}


map1_1::~map1_1()
{
}

HRESULT map1_1::init()
{
	_player = new player;
	_player->init();

	_em = new enemyManager;
	_em->init();
	_em->setMinion();
	_em->setPlayerMemoryAddressLink(_player);

	_shop = new shop;
	_shop->init();
	_player->setShopMemoryAddressLink(_shop);
	_shop->setPlayerMemoryAddressLink(_player);

	//��ǥ ��������
	vector<string> vStr;
	vStr = TXTDATA->txtLoad("PlayerPosition.txt");
	_player->setPlayerCenterX(atoi(vStr[0].c_str()));
	_player->setPlayerCenterY(atoi(vStr[1].c_str()));
	_camX = atoi(vStr[2].c_str());
	_player->setPlayerState((PLAYERSTATE)atoi(vStr[4].c_str()));
	_player->setPlayerSpeed(atoi(vStr[5].c_str()));
	_player->imageSet((char*)atoi(vStr[6].c_str()), (atoi(vStr[4].c_str())) % 2);
	_player->setPlayerImageFrameX(atoi(vStr[7].c_str()));

	_camX2 = _camX3 = 0;
	_camY = 100;

	_state = NOT_ESCAPE;

	return S_OK;
}
void map1_1::release()
{

}
void map1_1::update()
{
	_player->update();
	_shop->update();
	_em->update();
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

	if (_player->getPlayerCenter().x > IMAGEMANAGER->findImage("��1-1")->getWidth())
	{
		_state = RIGHT_ESCAPE;
	}

	mapMove();
}
void map1_1::render()
{
	//IMAGEMANAGER->findImage("���")->render(getMemDC(), 0, 0);
	IMAGEMANAGER->findImage("���2")->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _camX2, 0);
	IMAGEMANAGER->findImage("���1")->loopRender(getMemDC(), &RectMake(0, 100, WINSIZEX, WINSIZEY), _camX3, 0);
	_player->render(_camX, _camY);
	IMAGEMANAGER->findImage("��1-1")->render(getMemDC(), -_camX, -_camY);
	//IMAGEMANAGER->findImage("��1-1�ȼ�")->render(getMemDC(), -_camX, -_camY);
	_em->render(_camX,_camY);
	_shop->render();
	_shop->setLoc(_camX, _camY);
	_player->showInven();
	char str[128];
	sprintf(str, "%.1f %.1f", (float)_player->getPlayerCenter().x, (float)_player->getPlayerCenter().y);
	TextOut(getMemDC(), 0, 30, str, strlen(str));
	char str2[128];
	sprintf(str2, "%s", _player->getPlayerImageName());
	TextOut(getMemDC(), 0, 60, str2, strlen(str2));
	if (_player->getPlayerIsGround()) TextOut(getMemDC(), 100, 0, "��Ʈ��", strlen("��Ʈ��"));
	if (!_player->getPlayerIsGround()) TextOut(getMemDC(), 100, 0, "������", strlen("������"));
	if (_player->getPlayerIsJump()) TextOut(getMemDC(), 200, 0, "����Ʈ��", strlen("����Ʈ��"));
	if (!_player->getPlayerIsJump()) TextOut(getMemDC(), 200, 0, "��������", strlen("��������"));
	

	//IMAGEMANAGER->findImage("��1-1�ȼ�")->render(getMemDC(), -_camX, -_camY);
}

void map1_1::mapMove()
{
	char temp[128];
	vector<string> vStr;

	//�ʳѾ�� ���� �ʿ� ��ǥ�� �̸� �����ݽô�
	switch (_state)
	{
	case RIGHT_ESCAPE:
		vStr.push_back(itoa(10, temp, 10));
		vStr.push_back(itoa(600, temp, 10));
		vStr.push_back(itoa(0, temp, 10));
		vStr.push_back(itoa(0, temp, 10));
		vStr.push_back(itoa(_player->getPlayerState(), temp, 10));
		vStr.push_back(itoa(_player->getPlayerSpeed(), temp, 10));
		vStr.push_back(itoa((int)_player->getPlayerImageName(), temp, 10));
		vStr.push_back(itoa(_player->getPlayerImage()->getFrameX(), temp, 10));

		TXTDATA->txtSave("PlayerPosition.txt", vStr);

		SCENEMANAGER->changeScene("��2");

		break;
	}
}
