#include "stdafx.h"
#include "spaceShip.h"
#include "enemyManager.h"

//���漱���� �ߴٸ� �� cpp�� ��������� �ɾ����� ������������


spaceShip::spaceShip()
{
}


spaceShip::~spaceShip()
{
}

HRESULT spaceShip::init(void)
{
	_ship = IMAGEMANAGER->addImage("�÷��̾�", "rocket.bmp", 52, 64, true, RGB(255, 0, 255));
	_ship->setX(WINSIZEX / 2);
	_ship->setY(WINSIZEY / 2 + 200);

	_missile = new missile;
	_missile->init(30, 400);

	_thaad = new thaadMissile;
	_thaad->init(5000, 500);

	_currentHP = _maxHP = 100.0f;

	_hpBar = new progressBar;
	_hpBar->init(_ship->getX(), _ship->getY() - 10, 53, 5);
	_hpBar->setGauge(_currentHP, _maxHP);

	_alphaValue = 120;

	return S_OK;
}

void spaceShip::release(void)
{

}

void spaceShip::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _ship->getX() > 0)
	{
		_ship->setX(_ship->getX() - 5);
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _ship->getX() + _ship->getWidth() < WINSIZEX)
	{
		_ship->setX(_ship->getX() + 5);
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP) && _ship->getY() > 0)
	{
		_ship->setY(_ship->getY() - 5);
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _ship->getY() + _ship->getHeight() < WINSIZEY)
	{
		_ship->setY(_ship->getY() + 5);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_missile->fire(_ship->getX() + _ship->getWidth() / 2, _ship->getY() - 30);
	}
	if (KEYMANAGER->isStayKeyDown('X'))
	{
		_thaad->fire(_ship->getX() + _ship->getWidth() / 2, _ship->getY() - 30);
	}


	_hpBar->setX(_ship->getX());
	_hpBar->setY(_ship->getY() - 10);
	_hpBar->setGauge(_currentHP, _maxHP);

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		char temp[128];
		vector<string> vStr;

		vStr.push_back(itoa(_currentHP, temp, 10));
		vStr.push_back(itoa(_maxHP, temp, 10));
		vStr.push_back(itoa(_ship->getX(), temp, 10));
		vStr.push_back(itoa(_ship->getY(), temp, 10));

		TXTDATA->txtSave("OmegaShooting.txt", vStr);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		vector<string> vStr;

		vStr = TXTDATA->txtLoad("OmegaShooting.txt");

		_currentHP = (atoi(vStr[0].c_str()));
		_ship->setX(atoi(vStr[2].c_str()));
		_ship->setY(atoi(vStr[3].c_str()));
	}


	//�갡 2���Դϴ� 2��
	collision();

	_missile->update();
	_thaad->update();
	_hpBar->update();

	//_alphaValue--;
	//
	//if (_alphaValue <= 0) _alphaValue = 255;

}

void spaceShip::render(void)
{
	IMAGEMANAGER->findImage("�÷��̾�")->alphaRender(getMemDC(), _alphaValue);

	_missile->render();
	_thaad->render();
	_hpBar->render();

}

void spaceShip::collision()
{
	for (int i = 0; i < _thaad->getVBullet().size(); i++)
	{
		for (int j = 0; j < _em->getVMinion().size(); j++)
		{
			RECT temp;
			if (IntersectRect(&temp, &_thaad->getVBullet()[i].rc,
				&_em->getVMinion()[j]->getRect()))
			{
				_thaad->removeMissile(i);
				_em->removeMinion(j);
				break;
			}
		}

	}

}

void spaceShip::hitDamage(float damage)
{
	_currentHP -= damage;
}

void spaceShip::removeMissile(int arrNum)
{
	_thaad->removeMissile(arrNum);
}