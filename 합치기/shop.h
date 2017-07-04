#pragma once
#include "gameNode.h"
#include "item.h"
#include <vector>

class player;

struct tagShopImg
{
	image* img;		//�̹���
	bool appear;	//ǥ�� ����
	bool isFrame;	//�⺻ �̹��� or ������ �̹���
	int x, y;		//�̹��� �Ѹ� ��ǥ
	int alpha;		//���İ� ����
};

class shop: public gameNode
{
private:
	//���� �̹��� ����, ������
	vector<tagShopImg> _vImg;

	//�������� �� ���� ����, ������
	vector<tagItem> _vShop;
	vector<tagItem>::iterator _viShop;

	RECT _rc;					//npc�� �÷��̾� �νĹ���

	int _absolX, _absolY;		//������ǥ
	int _x, _y;					//�����ǥ
	int _scriptX, _scriptY;		//��� �Ѹ� ��ǥ

	int _time, _selectTime;		//npc�̹��� ��ȯ Ÿ�̹�, ������ ���� �̹��� Ÿ�̹�
	int _npcIdx, _itemSelectIdx;//npc, ������ ���� ������ �̹���
	int _talkCount;				//��ȭȽ��
	int _selectedItem;			//���õ� ������

	bool _firstTalk;			//ó�� �� �Ŵ��� ����
	bool _isTalk;				//��ȭ������ ����
	bool _isColli;				//�÷��̾�� �浹 ������ ����
	bool _isShowList;			//������ ����Ʈ�� ���ƴ��� ����
	bool _isShowConfirm;		//����Ȯ��â ǥ�� ����

	player* _pl;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render();
	
	//player�� ���� ����
	void setPlayerMemoryAddressLink(player* pl) { _pl = pl; }

	//�ʿ��� ���� NPC�� ������ ��ġ ����
	void setAbsolLoc(int absolX, int absolY) { _absolX = absolX, _absolY = absolY; }

	//ī�޶� ��ǥ�� ���� �̹����� ��ġ ����
	void setLoc(int cameraX, int cameraY);

	//�̹��� ����
	void setImg(const char* keyName, const char* imgName, int x, int y, int width, int height, bool appear);
	//������ �̹��� ����
	void setImg(const char* keyName, const char* imgName, int x, int y, int width, int height, int frameX, int frameY, bool appear);

	//������ ������ �߰�
	void addItem(tagItem item);
	//������ ������ ����
	void removeItem(int num);

	//�̹��� ǥ�� ����
	void showImg(int num) { _vImg[num].appear = true; }
	void hideImg(int num) { _vImg[num].appear = false, _vImg[num].alpha = 0; }
	void changeImg(int num1, int num2) { showImg(num1), hideImg(num2); }

	//npc �̹��� ��ȯ(�⺻->������ Ȥ�� ������->�⺻)
	void changeNPC(void);

	//�� �� �̹��� ��ȯ
	void changeScript(void);

	//�÷��̾� rc�� �浹 ����
	void colliPlayer(RECT rc);

	//npc�� ��ȭ
	void talk(void);

	//������ ����
	void select(bool isDown);
	//���õ� ������
	void setSelectItem(int num) { _selectedItem = num; }

	//������ ���Դϱ�
	void purchaseConfirm(void);

	//������ ����� �����ϱ�
	bool isShowList(void) { return _isShowList; }

	shop();
	~shop();
};
