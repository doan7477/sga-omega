#pragma once
#include "playerManager.h"
class naruto :
	public playerManager
{
public:
	HRESULT init();
	void release();
	void update();
	void render();

	void attack();
	void move();
	void inputKey();
	void setPlayerAni();
	void command();

	static void rightAttack(void* obj);
	static void leftAttack(void* obj);

	PLAYERSTATE getPlayerState(void) { return _player.playerState; }
	void setPlayerState(PLAYERSTATE playerState) { _player.playerState = playerState; }

	animation* getPlayerMotion(void) { return _player.ani; }
	void setPlayerMotion(animation* ani) { _player.ani = ani; }

	naruto();
	~naruto();
};

