#pragma once
#include "gameNode.h"
#include "bullets.h"
#include "progressBar.h"

//��ȣ�����ϰԵǾ��� �� ���ѷ����� ���������� ���� ���漱��
class enemyManager;

class spaceShip : public gameNode
{
private:
	image* _ship;

	missile* _missile;
	thaadMissile* _thaad;

	enemyManager* _em;

	progressBar* _hpBar;
	float _maxHP, _currentHP;

	int _alphaValue;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void collision();

	void removeMissile(int arrNum);

	void hitDamage(float damage);

	image* getShipImage() { return _ship; }

	void setEnemyManagerMemoryAddressLink(enemyManager* em) { _em = em; }

	thaadMissile* getThaadMissile() { return _thaad; }

	spaceShip();
	~spaceShip();
};

