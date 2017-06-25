#pragma once
#include "gameNode.h"
#include "progressBar.h"

enum PLAYERSTATE
{
	PLAYERSTATE_LEFT_STOP,
	PLAYERSTATE_RIGHT_STOP,
	PLAYERSTATE_LEFT_MOVE,
	PLAYERSTATE_RIGHT_MOVE,
	PLAYERSTATE_LEFT_RUN,
	PLAYERSTATE_RIGHT_RUN,
	PLAYERSTATE_LEFT_SOFT_PUNCH,
	PLAYERSTATE_RIGHT_SOFT_PUNCH,
	PLAYERSTATE_LEFT_HARD_PUNCH,
	PLAYERSTATE_RIGHT_HARD_PUNCH,
	PLAYERSTATE_LEFT_SOFT_KICK,
	PLAYERSTATE_RIGHT_SOFT_KICK,
	PLAYERSTATE_LEFT_HARD_KICK,
	PLAYERSTATE_RIGHT_HARD_KICK,
	PLAYERSTATE_LEFT_JUMP,
	PLAYERSTATE_RIGHT_JUMP,
	PLAYERSTATE_LEFT_DUCK,
	PLAYERSTATE_RIGHT_DUCK
};

struct tagPlayer
{
	RECT rc;
	RECT attackRange;
	PLAYERSTATE playerState;
	image* img;
	progressBar* hpBar;
	animation* ani;
	float currentHp, maxHp;
	float x, y;
	float speed;
	float gravity;
	float timer;
	int command;
	bool isJump;
};

class playerManager : public gameNode
{
private:

protected:
	tagPlayer _player;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	
	virtual void move();
	virtual void inputKey();
	virtual void setPlayerAni();
	virtual void command();
	virtual void pixelCollision();
	virtual void attack();

	virtual void rightAttack(void* obj);
	virtual void leftAttack(void* obj);

	tagPlayer getPlayerStruct() { return _player; }
	RECT getPlayerAttackRange() { return _player.attackRange; }

	playerManager();
	~playerManager();
};

