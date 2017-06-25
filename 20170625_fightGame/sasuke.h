#pragma once
#include "playerManager.h"

class sasuke : public playerManager
{
private:
	int _hitx, _hity;
	int _commandClick;
	int	_commandCount;
	int _commandTimer;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void attack();
	virtual void move();
	virtual void inputKey();
	virtual void setPlayerAni();
	virtual void command();

	static void rightattack(void* obj);
	static void leftattack(void* obj);

	tagPlayer getPlayerStruct() { return _player; }

	PLAYERSTATE getPlayerState(void) { return _player.playerState; }
	void setPlayerState(PLAYERSTATE state) { _player.playerState = state; }

	animation* getPlayerMotion(void) { return _player.ani; }
	void setPlayerMotion(animation* ani) { _player.ani = ani; }

	sasuke();
	~sasuke();
};