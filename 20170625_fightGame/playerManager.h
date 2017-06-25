#pragma once
#include "gameNode.h"
#include "progressBar.h"
#include "bullets.h"

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
	PLAYERSTATE_RIGHT_DUCK,
	PLAYERSTATE_LEFT_STAYJUMP,
	PLAYERSTATE_RIGHT_STAYJUMP,
	PLAYERSTATE_LEFT_WALKJUMP,
	PLAYERSTATE_RIGHT_WALKJUMP,
	PLAYERSTATE_LEFT_RUNJUMP,
	PLAYERSTATE_RIGHT_RUNJUMP,
	PLAYERSTATE_LEFT_COMMAND1,
	PLAYERSTATE_RIGHT_COMMAND1,
	PLAYERSTATE_LEFT_COMMAND2,
	PLAYERSTATE_RIGHT_COMMAND2,
	PLAYERSTATE_LEFT_COMMAND3,
	PLAYERSTATE_RIGHT_COMMAND3,
	PLAYERSTATE_LEFT_SKILL1,
	PLAYERSTATE_RIGHT_SKILL1,
	PLAYERSTATE_LEFT_SKILL2,
	PLAYERSTATE_RIGHT_SKILL2,
	PLAYERSTATE_LEFT_SKILL3,
	PLAYERSTATE_RIGHT_SKILL3
};

struct tagPlayer
{
	RECT rc;
	RECT attackRange;
	RECT hitZone;
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
	bool jumping;
};

class playerManager : public gameNode
{
private:

protected:
	throwKnife* _throwKnife;
	tagPlayer _player;
	//커맨드입력 관련 변수
	int _commandCount;
	int _commandTimer;
	//마지막 받은 키값으로 예외조건 걸기
	int _commandFinal;
	bool _commandClick;

	//히트존관련 변수
	int _hitzoneX;
	int _hitzoneY;

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

	throwKnife* getKnife() { return _throwKnife; }
	tagPlayer getPlayerStruct() { return _player; }
	RECT getPlayerAttackRange() { return _player.attackRange; }

	playerManager();
	~playerManager();
};

