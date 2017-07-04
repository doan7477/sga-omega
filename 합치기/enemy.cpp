#include "stdafx.h"
#include "enemy.h"

enemy::enemy()
{
}

enemy::~enemy()
{
}

HRESULT enemy::init(const char* imageName, POINT position)
{
	_player = new player;
	_player->init();

	_enemy.imgName = "��ź�����ĵ�";
	_enemy.img = IMAGEMANAGER->findImage(_enemy.imgName);
	_enemy.x = position.x;
	_enemy.y = position.y;
	_enemy.fps = 0;
	_enemy.speed = 1.0;
	_enemy.jumpPower = 5.0f;
	_enemy.gravity = 0.1;
	_enemy.rc = RectMakeCenter(_enemy.x, _enemy.y, _enemy.img->getFrameWidth(), _enemy.img->getFrameHeight());
	_enemy.state = ENEMYSTATE_STAND;
	_enemy.attack = false;
	_enemy.currentHP = 10.0f;
	_enemy.maxHP = 10.0f;

	_fireCount = 0;

	return S_OK;
}

void enemy::release(void)
{

}

void enemy::update(void)
{
	_player->update();

	_enemy.fps++;
	_fireCount++;
	
	if (_enemy.state == ENEMYSTATE_STAND)
	{
		imageSet("��ź�����ĵ�", leftright());
	}
	if (_fireCount % 180 == 0)
	{
		if (_enemy.state == ENEMYSTATE_STAND)
		{
			_enemy.state = ENEMYSTATE_ATTACK;
			imageSet("��ź����ź��ô", leftright());
		}
		_fireCount = 0;
	}
}

void enemy::render(float x, float y)
{
	//���°� �´��� Ȯ��
	char str[123];
	char str1[123];
	char str2[123];
	sprintf(str, "fps : %d", _enemy.fps);
	sprintf(str1, "fire : %d", _fireCount);
	TextOut(getMemDC(), 150, 0, str, strlen(str));
	TextOut(getMemDC(), 220, 0, str1, strlen(str1));
	
	_enemy.img->frameRender(getMemDC(), _enemy.rc.left - x, _enemy.rc.top - y);

	if (_enemy.imgName == "��ź�����ĵ�")
	{
		if (_enemy.fps % 5 == 0) _enemy.img->setFrameX(_enemy.img->getFrameX() + 1);
	}
	else if ((_enemy.imgName == "��ź����Ʈ"))
	{
		if (_enemy.fps % 30 == 0) _enemy.img->setFrameX(_enemy.img->getFrameX() + 1);
	}
	else
	{
		if (_enemy.fps % 8 == 0) _enemy.img->setFrameX(_enemy.img->getFrameX() + 1);
	}

	switch (_enemy.state)
	{
	case ENEMYSTATE_ATTACK:
		if (_enemy.img->getFrameX() >= _enemy.img->getMaxFrameX()) _enemy.state = ENEMYSTATE_STAND;
	break;
	case ENEMYSTATE_HIT:
		if (_enemy.img->getFrameX() >= _enemy.img->getMaxFrameX()) _enemy.state = ENEMYSTATE_STAND;
	break;


	
	}
}

void enemy::imageSet(char* imgName, bool direction)
{
	_enemy.fps = 0;
	_enemy.imgName = imgName;
	_enemy.img = IMAGEMANAGER->findImage(imgName);
	_enemy.img->setFrameX(0);
	if (direction) _enemy.img->setFrameY(0);
	else if (!direction) _enemy.img->setFrameY(1);
}

bool enemy::bulletCountFire(void)
{
	//���� ������ �ѹ����� �޾ƿͼ� �װ�(���)�̶�� ����������
	if (_enemy.state == ENEMYSTATE_ATTACK)
	{
		if (_enemy.img->getFrameX() == 5) return true;
	}
	return false;
}

//�÷��̾� ��ġ�ľ��ؼ� �¿찪 �ֱ�
bool enemy::leftright(void)
{
	//�������� Ʈ��...���Ʈ?
	if (_player->getPlayerCenter().x >= _enemy.x) return true;
	else return false;
}
