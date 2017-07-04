#pragma once
#include "gameNode.h"
#include "item.h"
#include <vector>

class player;

class inventory : public gameNode
{
private:
	//�κ��丮���� ���� ���� �����۵�
	vector<tagItem> _vItem;
	vector<tagItem>::iterator _viItem;

	image* _background;		//�κ��丮 ���
	bool _appear;			//ǥ�� ����
	int _alpha;				//���İ� ����

	player* _pl;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	
	//�÷��̾�� ����
	void setPlayerMemoryAddressLink(player* pl) { _pl = pl; }

	//�κ� ������ �� ���� 
	void openInven(void) { _appear = true; }
	void hideInven(void) { _appear = false; }

	void handleInventory(void);

	inventory();
	~inventory();
};

