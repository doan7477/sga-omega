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

	//미니언 셋팅 함수
	void setMinion(void);
	//미니언 발사 함수
	void minionBulletFire(void);
	//플레이어 위치파악해서 좌우값 주기
	bool leftright(void);
	//맵에 충돌하면 지워주기
	void bombrelease(void);

	//상호작용시키자
	void setPlayerMemoryAddressLink(player* player) { _player = player; }

	//벡터 접근자
	inline vector<enemy*> getVImp(void) { return _vImp; }
	inline vector<enemy*>::iterator  getVIImp(void) { return _viImp; }
	inline vector<Boss*> getVImpBoss(void) { return _vImpBoss; }
	inline vector<Boss*>::iterator  getVIImpBoss(void) { return _viImpBoss; }

	enemyManager();
	~enemyManager();
};

