#pragma once
#include "gameNode.h"
#include "player.h"

enum BOSSSTATE
{
	BOSSSTATE_SHOWUP,
	BOSSSTATE_STAND,
	BOSSSTATE_ATTACK1,
	BOSSSTATE_ATTACK2,
	BOSSSTATE_ATTACK3,
	BOSSSTATE_ATTACK4,
	BOSSSTATE_ATTACK1_END,
	BOSSSTATE_ATTACK2_END,
	BOSSSTATE_ATTACK3_END,
	BOSSSTATE_ATTACK4_END,
	BOSSSTATE_LEFT_MOVE,
	BOSSSTATE_RIGHT_MOVE
};

struct tagBoss
{
	BOSSSTATE state;
	RECT headrc;
	RECT body1rc[3];
	RECT body2rc[4];
	RECT tailrc;
	char* HeadimgName;
	image* Headimg;
	char* Body1imgName;
	image* Body1img;
	char* Body2imgName;
	image* Body2img;
	char* TailimgName;
	image* Tailimg;
	float headx, heady;
	float body1x[3], body1y[3], body2x[4], body2y[4], tailx, taily;
	float speed;
	float jumpPower;
	float gravity;
	int	fps;
	bool attack;
	float currentHP;
	float maxHP;
};

class Boss : public gameNode
{
private:
	player* _player;

	tagBoss _boss;
	image* _img;

	RECT _rc;

	int _fireCount;
	int _rndAttack;

public:
	HRESULT init(const char* imageName, POINT position);
	void release(void);
	void update(void);
	void render(float x, float y);

	void move(void);

	void imageSet(char* imgName);

	///inline float getCenterX() { return _boss.rc.left + (_boss.rc.right - _boss.rc.left) / 2; }
	inline RECT getRect(void) { return _boss.headrc; }
	//inline float getX(void) { return _boss.x; }
	//inline float getY(void) { return _boss.y; }

	bool bulletCountFire(void);

	Boss();
	~Boss();
};

