#pragma once
#include "gameNode.h"

#define MAXSPEED 5.0f
#define ROLLSPEED 7.5f
#define MINSPEED 1.5f
#define JUMPPOWER 6.0f
#define GRAVITY 0.1f
#define FRAMEUPDATE TIMEMANAGER->getElapsedTime() * 5;

enum PLAYERSTATE
{
	PLAYERSTATE_LEFT_IDLE,
	PLAYERSTATE_RIGHT_IDLE,
	PLAYERSTATE_LEFT_RUN,
	PLAYERSTATE_RIGHT_RUN,
	PLAYERSTATE_LEFT_BRAKE,
	PLAYERSTATE_RIGHT_BRAKE,
	PLAYERSTATE_LEFT_TURN,
	PLAYERSTATE_RIGHT_TURN,
	PLAYERSTATE_LEFT_ROLL,
	PLAYERSTATE_RIGHT_ROLL,
	PLAYERSTATE_LEFT_HIT,
	PLAYERSTATE_RIGHT_HIT,
	PLAYERSTATE_LEFT_CROUCH,
	PLAYERSTATE_RIGHT_CROUCH,
	PLAYERSTATE_LEFT_RISE,
	PLAYERSTATE_RIGHT_RISE,
	PLAYERSTATE_JUMP,
	PLAYERSTATE_DOWN_JUMP,
	PLAYERSTATE_FALL,
	PLAYERSTATE_LEFT_ATTACK1,
	PLAYERSTATE_LEFT_ATTACK2,
	PLAYERSTATE_LEFT_ATTACK3,
	PLAYERSTATE_LEFT_BOW,
	PLAYERSTATE_LEFT_JUMPBOW,
	PLAYERSTATE_LEFT_CROUCHBOW,
	PLAYERSTATE_RIGHT_ATTACK1,
	PLAYERSTATE_RIGHT_ATTACK2,
	PLAYERSTATE_RIGHT_ATTACK3,
	PLAYERSTATE_RIGHT_BOW,
	PLAYERSTATE_RIGHT_JUMPBOW,
	PLAYERSTATE_RIGHT_CROUCHBOW
};

struct tagPlayer
{
	PLAYERSTATE			state;
	RECT				rc;
	image*				img;
	float				x, y;
	float				speed;
	float				jumpPower;
	float				gravity;
	int					fps;
	char*				imgName;
	bool				isMove;
	bool				isJump;
	bool				isJump2;
};

typedef void(*CALLBACK_FUNCTION_PARAMETER)(void*);

class player : public gameNode
{
private:
	tagPlayer					_player;
	CALLBACK_FUNCTION_PARAMETER _callbackFunctionParameter;
	void*						_obj;

public:
	HRESULT init();
	void release();
	void update();
	void render(float x, float y);

	void inputKey();
	void move();
	void imageSet(char* imgName, bool direction);
	void pixelCollision();

	POINT getPlayerCenter() { return PointMake(_player.x, _player.y); }
	float getPlayerSpeed() { return _player.speed; }
	float getPlayerJumpPower() { return _player.jumpPower; }

	player();
	~player();
};

