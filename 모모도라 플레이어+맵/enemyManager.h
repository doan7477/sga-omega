#pragma once
#include "gameNode.h"
#include "bullets.h"
#include "Idle.h"
#include <vector>

class enemyManager
{
private:
	typedef vector<enemy*> vEnemy;
	typedef vector<enemy*>::iterator viEnemy;

	vEnemy _vIdle;
	viEnemy _viIdle;

	knife* _knife;
	grenade* _grenade;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//�̴Ͼ� ���� �Լ�
	void setMinion(void);

	//�̴Ͼ� �߻� �Լ�
	void minionBulletFire(void);

	enemyManager();
	~enemyManager();
};

