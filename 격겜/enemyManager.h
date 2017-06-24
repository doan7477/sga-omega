#pragma once
#include "gameNode.h"
#include "minion.h"
#include "bullets.h"
#include <vector>

class spaceShip;

class enemyManager : public gameNode
{
private:
	typedef vector<enemy*> vEnemy;
	typedef vector<enemy*>::iterator viEnemy;

private:
	vEnemy _vMinion;
	viEnemy _viMinion;

	bullet* _bullet;

	spaceShip* _ship;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//�̴Ͼ� ���� �Լ�
	void setMinion(void);

	//�̴Ͼ� �߻� �Լ�
	void minionBulletFire(void);

	void removeMinion(int arrNum);

	void collision();


	void setSpaceShipMemoryAddressLink(spaceShip* ship) { _ship = ship; }

	inline vector<enemy*> getVMinion(void) { return _vMinion; }
	inline vector<enemy*>::iterator  getVIMinion(void) { return _viMinion; }

	enemyManager();
	~enemyManager();
};

