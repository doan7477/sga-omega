#pragma once
#include "gameNode.h"
#include "loadingScene.h"
<<<<<<< HEAD:모모도라 플레이어+맵/mainGame.h
#include "map1_1.h"
#include "map1_2.h"
#include "map1_3.h"
#include "map1_boss.h"
#include "opening.h"

=======
#include "gameScene.h"
#include "opening.h"
>>>>>>> 26e3ede34cfd9cf7d2ca3e51f64978aac01852d3:모모도라/mainGame.h


class mainGame : public gameNode
{
private:
	
	

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	

	mainGame();
	~mainGame();
};

