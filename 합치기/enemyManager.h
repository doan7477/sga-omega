#pragma once
#include "gameNode.h"
#include "bullets.h"
#include "Imp.h"
#include "ImpBoss.h"
#include <vector>

class player;

class enemyManager
{
private:
	typedef vector<enemy*> vEnemy;
	typedef vector<enemy*>::iterator viEnemy;
	typedef vector<Boss*> vBoss;
	typedef vector<Boss*>::iterator viBoss;

private:
	vEnemy _vImp;
	viEnemy _viImp;
	vBoss _vImpBoss;
	viBoss _viImpBoss;

	knife* _knife;
	grenade* _grenade;
	bossgrenade* _bossgrenade;
	
	player* _player;

	int _poisionCount;

public:
	HRESULT init();
	void release();
	void update();
	void render(float x, float y);

	//�̴Ͼ� ���� �Լ�
	void setMinion(void);
	//�̴Ͼ� �߻� �Լ�
	void minionBulletFire(void);
	//�÷��̾� ��ġ�ľ��ؼ� �¿찪 �ֱ�
	bool leftright(void);
	//�ʿ� �浹�ϸ� �����ֱ�
	void bombrelease(void);

	//��ȣ�ۿ��Ű��
	void setPlayerMemoryAddressLink(player* player) { _player = player; }

	//���� ������
	inline vector<enemy*> getVImp(void) { return _vImp; }
	inline vector<enemy*>::iterator  getVIImp(void) { return _viImp; }
	inline vector<Boss*> getVImpBoss(void) { return _vImpBoss; }
	inline vector<Boss*>::iterator  getVIImpBoss(void) { return _viImpBoss; }

	enemyManager();
	~enemyManager();
};

