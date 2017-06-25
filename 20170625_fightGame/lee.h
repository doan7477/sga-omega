#pragma once
#include "playerManager.h"


class lee : public playerManager
{
private:
	bool _commandStart;
	int	_commandCount;
	int _commandTimer;

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

	static void rightFinish(void* obj);
	static void leftFinish(void* obj);

	PLAYERSTATE getPlayerState(void) { return _player.playerState; }
	void setPlayerState(PLAYERSTATE playerState) { _player.playerState = playerState; }

	animation* getPlayerMotion(void) { return _player.ani; }
	void setPlayerMotion(animation* ani) { _player.ani = ani; }

	lee();
	~lee();
};

