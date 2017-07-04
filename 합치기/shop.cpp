#include "stdafx.h"
#include "shop.h"
#include "player.h"

shop::shop()
{
}


shop::~shop()
{
}

HRESULT shop::init(void)
{	
	//�̹��� �ѷ��� ��ǥ ����
	_absolX = _x = WINSIZEX / 2;
	_absolY = _y = WINSIZEY / 2;

	//npc �̹��� �ҷ�����
	setImg("shopNPC�⺻", "image/������/shopNPC.bmp", _x, _y, 54, 108, true);							//0
	setImg("shopNPC���", "image/������/shopNPCF.bmp", _x, _y, 756, 108, 14, 1, false);				//1
	
	//�÷��̾���� �浹 ���� ����
	_rc = RectMake(_x, _y, 162, 108);
	
	//shop ���� �̹��� �ҷ�����
	setImg("shop��ũ", "image/������/shopMark.bmp", _x - 60, _y - 66, 198, 48, false);					//2
	setImg("shop�ϻ��Ʈ", "image/������/�ϻ��Ʈ.bmp", _x - 95, _y - 96, 246, 78, false);				//3	
	setImg("shopó����Ʈ1", "image/������/ó����Ʈ1.bmp", _x - 152, _y - 138, 384, 120, false);		//4	
	setImg("shopó����Ʈ2", "image/������/ó����Ʈ2.bmp", _x - 72, _y - 138, 192, 120, false);			//5	
	setImg("�����۸��", "image/������/itemList.bmp", _x - 200, _y - 228, 498, 210, false);			//6
	setImg("���þ�����", "image/������/itemSelect.bmp", _x-193, _y-165, 192, 27, 8, 1, false);			//7
	setImg("��Ƽ�걸��Ȯ��", "image/������/��Ƽ�걸��Ȯ��.bmp", _x - 200, _y - 228, 600, 204, false);	//8
	setImg("�нú걸��Ȯ��", "image/������/�нú걸��Ȯ��.bmp", _x - 200, _y - 228, 600, 204, false);	//9

	_time = _selectTime = _npcIdx = _itemSelectIdx = _talkCount = _selectedItem = 0;
	_firstTalk = _isTalk = _isShowList = _isShowConfirm = false;

	return S_OK;
}

void shop::release(void)
{} 

void shop::update(void)
{
	changeNPC();	//npc �̹��� ��ȯ
	changeScript();

	for (int i = 0; i < _vImg.size(); i++)
	{
		if (_vImg[i].appear && i >= 2)//npc �̹����� �����ϰ� ���ĺ���
		{
			_vImg[i].alpha += 10;
			if (_vImg[i].alpha >= 255) _vImg[i].alpha = 255;
		}
	}

	_rc = RectMake(_x - 54, _y, 162, 108);

}

void shop::render(void)
{
	//Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);

	//�̹��� ���
	for (int i=0; i<_vImg.size(); i++)
	{
		if (_vImg[i].appear)
		{
			if (!_vImg[i].isFrame)//������ �̹����� �ƴ� ��
			{
				if (i >= 2)//npc �̹��� ����� ���ĺ���
						_vImg[i].img->alphaRender(getMemDC(), _vImg[i].x, _vImg[i].y, _vImg[i].alpha);	
				else
					_vImg[i].img->render(getMemDC(), _vImg[i].x, _vImg[i].y);
			}
			else//������ �̹����� ��
			{
				_vImg[i].img->frameRender(getMemDC(), _vImg[i].x, _vImg[i].y);
			}

			//������ ���
			if (i == 6)
			{
				for (int i = 0; i < _vShop.size(); i++)
				{
					char str[50], str2[10];

					HFONT oldFont, font;

					font = CreateFont(38, 16, 0, 0, 20, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("���纻��üM"));
					oldFont = (HFONT)SelectObject(getMemDC(), font);
					SetBkMode(getMemDC(), TRANSPARENT);//������ ����� ����Ѵ�
					SetTextColor(getMemDC(), RGB(_vImg[6].alpha, _vImg[6].alpha, _vImg[6].alpha));

					sprintf_s(str, _vShop[i].name);
					sprintf_s(str2, "%d", _vShop[i].price);

					TextOut(getMemDC(), _vImg[6].x + 35, _vImg[6].y + 60 + i * 50, str, strlen(str));
					TextOut(getMemDC(), _vImg[6].x + 370, _vImg[6].y + 60 + i * 50, str2, strlen(str2));

					DeleteObject(oldFont);
					DeleteObject(font);

				}
			}

			//������ ȿ��
			if (i == 8 || i == 9)
			{
				char str[50];

				SetTextColor(getMemDC(), RGB(_vImg[i].alpha, _vImg[i].alpha, _vImg[i].alpha));
				sprintf_s(str, "%s", _vShop[_selectedItem].effect);
				TextOut(getMemDC(), _vImg[i].x + 10, _vImg[i].y + 55, str, strlen(str));
			}
		}
	}
	SetTextColor(getMemDC(), RGB(0,0,0));
	char temp[128];
	sprintf_s(temp, "talkCount: %d _vImg[7].y: %d ���õȾ�����: %d", _talkCount, _vImg[7].y, _selectedItem);
	TextOut(getMemDC(), 400, 50, temp, strlen(temp));
}

//ī�޶� ��ǥ�� ���� ���� NPC ��ġ ����
void shop::setLoc(int cameraX, int cameraY)
{
	for (int i = 0; i < _vImg.size(); i++)
	{
		_vImg[i].img->setX(_absolX - cameraX);
		_vImg[i].img->setY(_absolY - cameraY);
	}

	_rc = RectMake(_x - cameraX, _y - cameraY, 162, 108);
}


//�̹��� ����
void shop::setImg(const char* keyName, const char* imgName, int x, int y, int width, int height, bool appear)
{
	tagShopImg temp;
	temp.img = IMAGEMANAGER->addImage(keyName, imgName, width, height, true, RGB(255, 0, 255));
	temp.x = x;
	temp.y = y;
	temp.alpha = 0;
	temp.isFrame = false;	//�׳� �̹���
	temp.appear = appear;

	_vImg.push_back(temp);
}

//������ �̹��� ����
void shop::setImg(const char* keyName, const char* imgName, int x, int y, int width, int height, int frameX, int frameY, bool appear)
{
	tagShopImg temp;
	temp.img = IMAGEMANAGER->addFrameImage(keyName, imgName, width, height, frameX, frameY, true, RGB(255, 0, 255));
	temp.x = x;
	temp.y = y;
	temp.alpha = 0;
	temp.isFrame = true;	//������ �̹���
	temp.appear = appear;

	_vImg.push_back(temp);
}

//������ �߰�
void shop::addItem(tagItem item)
{
	tagItem temp = item;
	_vShop.push_back(temp);//�������� �����ؼ� ������ ������ ���Ϳ� �ִ´�
}

//������ �Ǹ� �� ����
void shop::removeItem(int num)
{
	//_vItem.erase(_vItem.begin() + num);
}

//npc �̹��� ��ȯ(�⺻->������ Ȥ�� ������->�⺻)
void shop::changeNPC(void)
{
	_time++;

	if (_vImg[0].appear)
	{
		if (_time % 200 == 0)	//���� �ð��� �Ǹ� ������ �̹����� ��ȯ
		{
			_vImg[0].appear = false;	//�⺻ �̹����� ����� 
			_vImg[1].appear = true;
			_time = 0;
		}
	}

	if (_vImg[1].appear)
	{
		if (_time % 5 == 0)
			_npcIdx++;

		if (_npcIdx > _vImg[1].img->getMaxFrameX())
		{
			_npcIdx = _time = 0;
			_vImg[0].appear = true;	//�ٽ� �⺻ �̹�����
			_vImg[1].appear = false;
		}
		_vImg[1].img->setFrameX(_npcIdx);
	}
}

void shop::changeScript(void)
{
	//�÷��̾�� �浹 ���̶��
	if (_isColli)
	{
		if (!_isTalk && !_vImg[2].appear)//��ȭ ���� �ƴ� ��쿡��
			showImg(2);

		if (_isTalk)//��ȭ ���̰�
		{
			if (!_firstTalk)//ù ��ȭ�� ��
			{
				if (_talkCount == 0 && _vImg[4].alpha == 255)//��� �̹����� �����ϰ� �ѷ����� �� ��ȭȽ�� ����
					_talkCount++;

				if (_talkCount == 1 && _vImg[5].alpha == 255)
					_talkCount++;

				if (_talkCount == 2 && _vImg[3].alpha == 255)
					_talkCount++;

				if (_talkCount == 3 && _vImg[6].alpha == 255)
					_talkCount++;
			}
			if (_firstTalk)
			{
				if (_talkCount == 0 && _vImg[3].alpha == 255)
					_talkCount++;

				if (_talkCount == 1 && _vImg[6].alpha == 255)
					_talkCount++;
			}
			if (_isShowList)
			{
				if(_selectTime % 5 ==0)
					_itemSelectIdx++;

				if (_itemSelectIdx > _vImg[7].img->getMaxFrameX())
					_itemSelectIdx = 0;

				_vImg[7].img->setFrameX(_itemSelectIdx);
				_selectTime++;
			}
		}
	}
	if(!_isColli)
	{
		if (!_isTalk)//��ȭ ���� �ƴ϶��
		{
			hideImg(2);
			_vImg[2].alpha = 0;
		}
		else	{ }
	}
}

//�÷��̾� rc�� �浹 ����
void shop::colliPlayer(RECT rc)
{
	RECT temp;

	if (IntersectRect(&temp, &_rc, &rc))
		_isColli = true;
	else
		_isColli = false;
}

//npc�� ��ȭ; �ݵ�� OnceKeyDown���� ȣ���ؾ� �Ѵ� �ȱ׷��� ���۰� �Ⱥ������ â�� ������ �ȵȴ� TT
void shop::talk(void)
{
	if (_firstTalk)//ù ��ȭ�� �ƴ϶��
	{
		if (_talkCount == 0)
		{
			changeImg(3, 2);
			_isTalk = true;
			_pl->setInShop(_isTalk);
		}

		if (_talkCount == 1)
		{
			changeImg(6, 3);
			showImg(7);
			_isShowList = true;
		}

		if (_talkCount == 2)
		{
			for (int i = 0; i < _vImg.size(); i++)
			{
				if (i >= 2)
					hideImg(i);
			}
			_talkCount = 0;
			_isShowList = false;
			_isTalk = false;
			_pl->setInShop(_isTalk);
		}
	}

	if (!_firstTalk)//ù ��ȭ���
	{
		if (_talkCount == 0)
		{
			changeImg(4, 2);
			_isTalk = true;
			_pl->setInShop(_isTalk);
		}

		if (_talkCount == 1)
			changeImg(5, 4);

		if (_talkCount == 2)
			changeImg(3, 5);

		if (_talkCount == 3)
		{
			changeImg(6, 3);
			showImg(7);
			_isShowList = true;
		}

		if (_talkCount == 4)
		{
			for (int i = 0; i < _vImg.size(); i++)
			{
				if (i >= 2)
					hideImg(i);
			}
			_talkCount = 0;
			_isShowList = false;
			_isTalk = false;//��ȭ ���� �ƴϴ�
			_firstTalk = true;//�������� ù ��ȭ�� �ƴϴ� 
			_pl->setInShop(_isTalk);
		}
	}
}

//������ ����
void shop::select(bool isDown)
{
	bool success;

	//������ ����� ǥ�õǾ��ٸ�
	if (_isShowList)
	{
		//�Ʒ� ����Ű�� ������
		if (isDown)
		{
			if (_vImg[7].y >= 196 && _vImg[7].y <= 246)
			{
				_vImg[7].y = _vImg[7].y + 50;
				_selectedItem++;
			}
		}
		//�� ����Ű�� ������
		else if (!isDown)
		{
			if (_vImg[7].y >= 246 && _vImg[7].y <= 296)
			{
				_vImg[7].y = _vImg[7].y - 50;
				_selectedItem--;
			}
		}
	}
}

//������ ���Դϱ�
void shop::purchaseConfirm(void)
{
	//������ Ÿ���� 2: �ߵ�ȿ��(active item)
	//������ Ÿ���� 3: ����ȿ��(passive item)
	if (_vShop[_selectedItem].type == 2)
	{
		changeImg(8, 6);
	}
	else if (_vShop[_selectedItem].type == 3)
	{
		changeImg(9, 6);
	}
}