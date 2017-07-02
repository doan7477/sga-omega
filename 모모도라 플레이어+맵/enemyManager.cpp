#include "stdafx.h"
#include "enemyManager.h"


enemyManager::enemyManager()
{
}


enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init()
{
	_knife = new knife;
	_knife->init("knife", 1, 500);

	_grenade = new grenade;
	_grenade->init("grenade", 1);

	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()	
{
	for (_viIdle = _vIdle.begin(); _viIdle != _vIdle.end(); ++_viIdle)
	{
		(*_viIdle)->update();
	}

	minionBulletFire();

	_knife->update();
	_grenade->update();
}

void enemyManager::render()	
{
	for (_viIdle = _vIdle.begin(); _viIdle != _vIdle.end(); ++_viIdle)
	{
		(*_viIdle)->render();
	}

	_knife->render();
	_grenade->render();
}

//미니언 셋팅 함수
void enemyManager::setMinion(void)
{
	enemy* bomber;
	bomber = new Idle;
	bomber->init("bomber", PointMake(10, 10));

	_vIdle.push_back(bomber);
}

//미니언 발사 함수
void enemyManager::minionBulletFire(void)
{
}
