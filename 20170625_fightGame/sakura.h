#pragma once
#include "playerManager.h"

class sakura : public playerManager
{
public:
	HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void move();
	virtual void inputKey();
	virtual void setPlayerAni();
	virtual void attack();
	virtual void command();

	static void rightFire(void* obj);
	static void leftFire(void* obj);

	PLAYERSTATE getPlayerState(void) { return _player.playerState; }
	void setPlayerState(PLAYERSTATE playerState) { _player.playerState = playerState; }

	animation* getPlayerMotion(void) { return _player.ani; }
	void setPlayerMotion(animation* ani) { _player.ani = ani; }

	sakura();
	~sakura();
};