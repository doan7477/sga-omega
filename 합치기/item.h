#pragma once
#include "gameNode.h"
#include <vector>

class shop;

struct tagItem
{
	image* img;				//아이템 이미지
	const char* name;		//아이템 명
	const char* effect;		//아이템 효과
	const char* desct;		//descript;아이템 설명
	int x, y;				//아이템 이미지를 뿌려줄 좌표
	int type;				//아이템 타입
	int price;				//아이템 가격
	int ability;			//아이템 능력치
	int amount;				//아이템 갯수
	bool inShop;			//상점템인가
};

class item:public gameNode
{
private:
	//아이템 종류를 담을 벡터
	vector<tagItem> _vItem;
	vector<tagItem>::iterator _viItem;

	//enemy용 화폐 아이템을 담을 벡터
	vector<tagItem> _vMoneyItem;
	vector<tagItem> _viMoneyIem;

public:
	virtual HRESULT init(void);

	vector<tagItem> getVItem(void) { return _vItem; }
	vector<tagItem>::iterator getVIItem(void) { return _viItem; }

	item();
	~item();
};

