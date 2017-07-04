#pragma once
#include "gameNode.h"
#include "arrow.h"
#include "inventory.h"

class shop;

#define MAXSPEED 5.0f
#define ROLLSPEED 7.5f
#define MINSPEED 2.5f
#define JUMPPOWER 17.0f
#define GRAVITY 0.3f
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
	PLAYERSTATE_JUMP_ATTACK,
	PLAYERSTATE_FALL,
	PLAYERSTATE_LEFT_ATTACK1,
	PLAYERSTATE_RIGHT_ATTACK1,
	PLAYERSTATE_LEFT_ATTACK2,
	PLAYERSTATE_RIGHT_ATTACK2,
	PLAYERSTATE_LEFT_ATTACK3,
	PLAYERSTATE_RIGHT_ATTACK3,
	PLAYERSTATE_LEFT_BOW,
	PLAYERSTATE_RIGHT_BOW,
	PLAYERSTATE_LEFT_JUMPBOW,
	PLAYERSTATE_RIGHT_JUMPBOW,
	PLAYERSTATE_LEFT_CROUCHBOW,
	PLAYERSTATE_RIGHT_CROUCHBOW,
	PLAYERSTATE_LEFT_LADDER_ENTER,
	PLAYERSTATE_RIGHT_LADDER_ENTER,
	PLAYERSTATE_LADDER_UP,
	PLAYERSTATE_LADDER_DOWN,
	PLAYERSTATE_LEFT_LADDER_LEAVE,
	PLAYERSTATE_RIGHT_LADDER_LEAVE
};

struct tagPlayer
{
	PLAYERSTATE			state;
	RECT				rc;
	image*				img;
	arrow*				arrow;
	inventory*			inven;
	shop*				shop;
	char*				imgName;
	float				x, y;
	float				speed;
	float				jumpPower;
	float				gravity;
	int					fps;
	int					key;
	bool				isJump;
	bool				isJump2;
	bool				isAirAttack;
	bool				isGround;
	bool				isLadder;
	bool				isRight;
	bool				inShop;
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
	void showInven();

	POINT getPlayerCenter() { return PointMake(_player.x, _player.y); }
	BOOL getPlayerIsJump() { return _player.isJump; }
	BOOL getPlayerIsLadder() { return _player.isLadder; }
	BOOL getPlayerIsGround() { return _player.isGround; }
	BOOL getPlayerDirection() { return _player.isRight; }
	PLAYERSTATE getPlayerState() { return _player.state; }
	arrow* getPlayerArrow() { return _player.arrow; }
	shop* getPlayerShop() { return _player.shop; }
	float getPlayerSpeed() { return _player.speed; }
	float getPlayerJumpPower() { return _player.jumpPower; }
	char* getPlayerImageName() { return _player.imgName; }
	RECT getPlayerRect(void) { return _player.rc; }
	image* getPlayerImage() { return _player.img; }

	void setPlayerCenterX(float x) { _player.x = x; }
	void setPlayerCenterY(float y) { _player.y = y; }
	void setPlayerState(PLAYERSTATE state) { _player.state = state; }
	void setPlayerSpeed(float speed) { _player.speed = speed; }
	void setPlayerImageName(char* NAME) { _player.imgName = NAME; }
	void setPlayerImage(image* NAME) { _player.img = NAME; }
	void setPlayerImageFrameX(int num) { _player.img->setFrameX(num); }

	//인벤토리와 연결
	void setInventoryMemoryAddressLink(inventory* inven) { _player.inven = inven; }
	//샵과 연결
	void setShopMemoryAddressLink(shop* shop) { _player.shop = shop; }

	void setInShop(bool inShop) { _player.inShop = inShop; }



	player();
	~player();
};

