#pragma once
#include "gameNode.h"
#include "item.h"
#include <vector>

class shop: public gameNode
{
private:
	//shopNpc
	image* _npcImg;			//�⺻ npc �̹���
	image* _npcFrameImg;	//3�� ���� ��Ÿ���� npc �̹���
	RECT _npcRc;			//�浹 ó����

	//shopâ
	image* _shopBackground;	//shop ���
	image* _shopSelect;		//������ ����
	int _selectX, _selectY;	//���õ� ������

	//�������� �� ���� ����
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
	
	//����Ʈ�� ��������/���� 
	void showList(void) { _showList = true; }
	void hideList(void) { _showList = false; }

	//���� npc ��ġ ����
	void setNPC(int x, int y);

	shop();
	~shop();
};

