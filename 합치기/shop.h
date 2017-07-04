#pragma once
#include "gameNode.h"
#include "item.h"
#include <vector>

class player;

struct tagShopImg
{
	image* img;		//이미지
	bool appear;	//표시 여부
	bool isFrame;	//기본 이미지 or 프레임 이미지
	int x, y;		//이미지 뿌릴 좌표
	int alpha;		//알파값 조절
};

class shop: public gameNode
{
private:
	//관련 이미지 벡터, 접근자
	vector<tagShopImg> _vImg;

	//상점에서 팔 물건 벡터, 접근자
	vector<tagItem> _vShop;
	vector<tagItem>::iterator _viShop;

	RECT _rc;					//npc의 플레이어 인식범위

	int _absolX, _absolY;		//절대좌표
	int _x, _y;					//상대좌표
	int _scriptX, _scriptY;		//대사 뿌릴 좌표

	int _time, _selectTime;		//npc이미지 전환 타이밍, 아이템 선택 이미지 타이밍
	int _npcIdx, _itemSelectIdx;//npc, 아이템 선택 프레임 이미지
	int _talkCount;				//대화횟수
	int _selectedItem;			//선택된 아이템

	bool _firstTalk;			//처음 말 거는지 여부
	bool _isTalk;				//대화중인지 여부
	bool _isColli;				//플레이어와 충돌 중인지 여부
	bool _isShowList;			//아이템 리스트를 펼쳤는지 여부
	bool _isShowConfirm;		//구매확인창 표시 여부

	player* _pl;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render();
	
	//player와 서로 연결
	void setPlayerMemoryAddressLink(player* pl) { _pl = pl; }

	//맵에서 상점 NPC의 절대적 위치 셋팅
	void setAbsolLoc(int absolX, int absolY) { _absolX = absolX, _absolY = absolY; }

	//카메라 좌표에 따른 이미지들 위치 조정
	void setLoc(int cameraX, int cameraY);

	//이미지 셋팅
	void setImg(const char* keyName, const char* imgName, int x, int y, int width, int height, bool appear);
	//프레임 이미지 셋팅
	void setImg(const char* keyName, const char* imgName, int x, int y, int width, int height, int frameX, int frameY, bool appear);

	//상점에 아이템 추가
	void addItem(tagItem item);
	//상점에 아이템 제거
	void removeItem(int num);

	//이미지 표시 여부
	void showImg(int num) { _vImg[num].appear = true; }
	void hideImg(int num) { _vImg[num].appear = false, _vImg[num].alpha = 0; }
	void changeImg(int num1, int num2) { showImg(num1), hideImg(num2); }

	//npc 이미지 전환(기본->프레임 혹은 프레임->기본)
	void changeNPC(void);

	//그 외 이미지 전환
	void changeScript(void);

	//플레이어 rc와 충돌 여부
	void colliPlayer(RECT rc);

	//npc와 대화
	void talk(void);

	//아이템 선택
	void select(bool isDown);
	//선택된 아이템
	void setSelectItem(int num) { _selectedItem = num; }

	//구매할 것입니까
	void purchaseConfirm(void);

	//아이템 목록이 떴읍니까
	bool isShowList(void) { return _isShowList; }

	shop();
	~shop();
};
