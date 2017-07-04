#pragma once
#include "gameNode.h"
#include "player.h"

enum EMENYSTATE
{
	ENEMYSTATE_STAND,
	ENEMYSTATE_HIT,
	ENEMYSTATE_ATTACK,
	ENEMYSTATE_LEFT_JUMP,
	ENEMYSTATE_RIGHT_JUMP,
	ENEMYSTATE_LEFT_MOVE,
	ENEMYSTATE_RIGHT_MOVE
};

struct tagEnemy
{
	EMENYSTATE state;
	RECT rc;
	image* img;
	float x, y;
	float speed;
	float jumpPower;
	float gravity;
	int	fps;
	char* imgName;
	bool attack;
	float currentHP;
	float maxHP;
};

class enemy : public gameNode
{
private:
	player* _player;

	tagEnemy _enemy;
	image* _img;

	RECT _rc;

	int _fireCount;
public:
	HRESULT init(const char* imageName, POINT position);
	void release(void);
	void update(void);
	void render(float x, float y);

	void imageSet(char* imgName, bool direction); //direction은 플레이어 위치에 따라 받아오자 (아직 미구현)
	bool leftright(void);

	inline float getCenterX() { return _enemy.rc.left + (_enemy.rc.right - _enemy.rc.left) / 2; }

	inline RECT getRect(void) { return _enemy.rc; }
	inline float getX(void) { return _enemy.x; }
	inline float getY(void) { return _enemy.y; }

	bool bulletCountFire(void);

	enemy();
	~enemy();
};
