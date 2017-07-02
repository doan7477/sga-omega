#pragma once
#include "gameNode.h"
#include "loadingScene.h"
#include "map1_1.h"
#include "map1_2.h"
#include "map1_3.h"
#include "map1_boss.h"
#include "opening.h"



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

