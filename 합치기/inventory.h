#pragma once
#include "gameNode.h"
#include "item.h"
#include <vector>

class player;

class inventory : public gameNode
{
private:
	//인벤토리에서 보관 중인 아이템들
	vector<tagItem> _vItem;
	vector<tagItem>::iterator _viItem;

	image* _background;		//인벤토리 배경
	bool _appear;			//표시 여부
	int _alpha;				//알파값 조절

	player* _pl;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	
	//플레이어와 연결
	void setPlayerMemoryAddressLink(player* pl) { _pl = pl; }

	//인벤 보여줄 지 말지 
	void openInven(void) { _appear = true; }
	void hideInven(void) { _appear = false; }

	void handleInventory(void);

	inventory();
	~inventory();
};

