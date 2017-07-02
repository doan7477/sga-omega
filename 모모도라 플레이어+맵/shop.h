#pragma once
#include "gameNode.h"
#include "item.h"
#include <vector>

class shop: public gameNode
{
private:
	//shopNpc
	image* _npcImg;			//기본 npc 이미지
	image* _npcFrameImg;	//3분 마다 나타나는 npc 이미지
	RECT _npcRc;			//충돌 처리용

	//shop창
	image* _shopBackground;	//shop 배경
	image* _shopSelect;		//아이템 선택
	int _selectX, _selectY;	//선택된 아이템

	//상점에서 팔 물건 벡터
	vector<tagItem> _vShop;
	vector<tagItem>::iterator _viShop;

	int _count;
	int _count2;
	int _index;

	bool _showFrameNPC;
	bool _showList;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	
	//리스트를 보여줄지/말지 
	void showList(void) { _showList = true; }
	void hideList(void) { _showList = false; }

	//상점 npc 위치 조정
	void setNPC(int x, int y);

	shop();
	~shop();
};

