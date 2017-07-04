#include "stdafx.h"
#include "enemyManager.h"
#include "player.h"

enemyManager::enemyManager()
{
}


enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init()
{
	_knife = new knife;
	_knife->init("Į", 0, 500);

	_grenade = new grenade;
	_grenade->init("��ź", 0);

	_poisionCount = 0;

	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()	
{
	for (_viImp = _vImp.begin(); _viImp != _vImp.end(); ++_viImp)
	{
		(*_viImp)->update();
	}

	for (_viImpBoss = _vImpBoss.begin(); _viImpBoss != _vImpBoss.end(); ++_viImpBoss)
	{
		(*_viImpBoss)->update();
	}

	minionBulletFire();
	bombrelease();

	_knife->update();
	_grenade->update();
}

void enemyManager::render(float x, float y)
{
	for (_viImp = _vImp.begin(); _viImp != _vImp.end(); ++_viImp)
	{
		(*_viImp)->render(x,y);
	}

	for (_viImpBoss = _vImpBoss.begin(); _viImpBoss != _vImpBoss.end(); ++_viImpBoss)
	{
		(*_viImpBoss)->render(x, y);
	}

	_knife->render();
	_grenade->render(x, y);
}

//�̴Ͼ� ���� �Լ�
void enemyManager::setMinion(void)
{
	enemy* bomber;
	bomber = new enemy;
	bomber->init("��ź�����ĵ�",PointMake(200,600));

	Boss* impboss;
	impboss = new Boss;
	impboss->init("�����Ӹ�", PointMake(100, 100));

	_vImp.push_back(bomber);
	_vImpBoss.push_back(impboss);
}

//�̴Ͼ� �߻� �Լ�
void enemyManager::minionBulletFire(void)
{
	for (_viImp = _vImp.begin(); _viImp != _vImp.end(); ++_viImp)
	{
		if ((*_viImp)->bulletCountFire())
		{
			RECT rc = (*_viImp)->getRect();

			if (!leftright()) _grenade->fire((rc.right + rc.left) / 2 , (rc.top + rc.bottom) / 2, 3 * PI / 4, 6.0f);
			else _grenade->fire((rc.right + rc.left) / 2, (rc.top + rc.bottom) / 2, PI / 4, 6.0f);
		}
	}
	for (_viImpBoss = _vImpBoss.begin(); _viImpBoss != _vImpBoss.end(); ++_viImpBoss)
	{
		if ((*_viImpBoss)->bulletCountFire())
		{
			RECT rc = (*_viImpBoss)->getRect();

			if (!leftright()) _grenade->fire((rc.right + rc.left) / 2, (rc.top + rc.bottom) / 2, 3 * PI / 4, 6.0f);
			else _grenade->fire((rc.right + rc.left) / 2, (rc.top + rc.bottom) / 2, PI / 4, 6.0f);
		}
	}
}

//�÷��̾� ��ġ�ľ��ؼ� �¿찪 �ֱ�
bool enemyManager::leftright(void)
{
	for (_viImp = _vImp.begin(); _viImp != _vImp.end(); ++_viImp)
	{
		float center = (*_viImp)->getCenterX();

		//�������� Ʈ��...���Ʈ?
		if (_player->getPlayerCenter().x >= center) return true;
		else return false;
	}
}

void enemyManager::bombrelease()
{
	for (int i = 0; i < _grenade->getVGrenade().size(); i++)
	{
		if (PIXELMANAGER->isPixelCollisionBombLeftX(_grenade->getVGrenade()[i].bulletImage, _grenade->getVGrenade()[i].x, _grenade->getVGrenade()[i].y, IMAGEMANAGER->findImage("��1-1�ȼ�")) ||
			PIXELMANAGER->isPixelCollisionBombRightX(_grenade->getVGrenade()[i].bulletImage, _grenade->getVGrenade()[i].x, _grenade->getVGrenade()[i].y, IMAGEMANAGER->findImage("��1-1�ȼ�")) ||
			PIXELMANAGER->isPixelCollisionBottomY(_grenade->getVGrenade()[i].bulletImage, _grenade->getVGrenade()[i].x, _grenade->getVGrenade()[i].y, IMAGEMANAGER->findImage("��1-1�ȼ�")))
		{
			_grenade->removeBullet(i);
			/*if (0 < _poisionCount && _poisionCount <= 60)
			{
				_grenade->poision();
			}*/
		}
		break;
	}
}
