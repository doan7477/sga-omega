#pragma once
#include "playerManager.h"


class lee : public playerManager
{
public:
	HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void attack();
	virtual void move();
	virtual void inputKey();
	virtual void setPlayerAni();
	virtual void command();
	virtual void pixelCollision();

	static void rightFire(void* obj);
	static void leftFire(void* obj);

	PLAYERSTATE getPlayerState(void) { return _player.playerState; }
	void setPlayerState(PLAYERSTATE playerState) { _player.playerState = playerState; }

	animation* getPlayerMotion(void) { return _player.ani; }
	void setPlayerMotion(animation* ani) { _player.ani = ani; }

	lee();
	~lee();
};

