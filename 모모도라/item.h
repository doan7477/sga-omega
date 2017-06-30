#pragma once
#include "gameNode.h"
#include <vector>


struct tagItem
{
	image* img;				//������ �̹���
	const char* name;		//������ ��
	const char* effect;		//������ ȿ��
	const char* desct;		//descript;������ ����
	int x, y;				//������ �̹����� �ѷ��� ��ǥ
	int type;				//������ Ÿ��
	int price;				//������ ����
	int ability;			//������ �ɷ�ġ
};


class item:public gameNode
{
private:
	//������ ������ ���� ����
	vector<tagItem> _vItem;
	vector<tagItem>::iterator _viItem;

	//enemy�� ȭ�� �������� ���� ����
	vector<tagItem> _vMoneyItem;
	vector<tagItem> _viMoneyIem;

public:
	virtual HRESULT init(void);

	//������ ����, ������ ��ȯ
	vector<tagItem> getVItem(void) { return _vItem; }
	vector<tagItem>::iterator getVIItem(void) { return _viItem; }

	item();
	~item();
};

