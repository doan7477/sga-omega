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
	//이미지 뿌려줄 좌표 셋팅
	_absolX = _x = WINSIZEX / 2;
	_absolY = _y = WINSIZEY / 2;

	//npc 이미지 불러오기
	setImg("shopNPC기본", "image/이지영/shopNPC.bmp", _x, _y, 54, 108, true);							//0
	setImg("shopNPC삼분", "image/이지영/shopNPCF.bmp", _x, _y, 756, 108, 14, 1, false);				//1
	
	//플레이어와의 충돌 판정 범위
	_rc = RectMake(_x, _y, 162, 108);
	
	//shop 관련 이미지 불러오기
	setImg("shop마크", "image/이지영/shopMark.bmp", _x - 60, _y - 66, 198, 48, false);					//2
	setImg("shop일상멘트", "image/이지영/일상멘트.bmp", _x - 95, _y - 96, 246, 78, false);				//3	
	setImg("shop처음멘트1", "image/이지영/처음멘트1.bmp", _x - 152, _y - 138, 384, 120, false);		//4	
	setImg("shop처음멘트2", "image/이지영/처음멘트2.bmp", _x - 72, _y - 138, 192, 120, false);			//5	
	setImg("아이템목록", "image/이지영/itemList.bmp", _x - 200, _y - 228, 498, 210, false);			//6
	setImg("선택아이콘", "image/이지영/itemSelect.bmp", _x-193, _y-165, 192, 27, 8, 1, false);			//7
	setImg("액티브구매확인", "image/이지영/액티브구매확인.bmp", _x - 200, _y - 228, 600, 204, false);	//8
	setImg("패시브구매확인", "image/이지영/패시브구매확인.bmp", _x - 200, _y - 228, 600, 204, false);	//9

	_time = _selectTime = _npcIdx = _itemSelectIdx = _talkCount = _selectedItem = 0;
	_firstTalk = _isTalk = _isShowList = _isShowConfirm = false;

	return S_OK;
}

void shop::release(void)
{} 

void shop::update(void)
{
	changeNPC();	//npc 이미지 전환
	changeScript();

	for (int i = 0; i < _vImg.size(); i++)
	{
		if (_vImg[i].appear && i >= 2)//npc 이미지를 제외하고 알파블렌딩
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

	//이미지 출력
	for (int i=0; i<_vImg.size(); i++)
	{
		if (_vImg[i].appear)
		{
			if (!_vImg[i].isFrame)//프레임 이미지가 아닐 때
			{
				if (i >= 2)//npc 이미지 빼고는 알파블렌딩
						_vImg[i].img->alphaRender(getMemDC(), _vImg[i].x, _vImg[i].y, _vImg[i].alpha);	
				else
					_vImg[i].img->render(getMemDC(), _vImg[i].x, _vImg[i].y);
			}
			else//프레임 이미지일 때
			{
				_vImg[i].img->frameRender(getMemDC(), _vImg[i].x, _vImg[i].y);
			}

			//아이템 목록
			if (i == 6)
			{
				for (int i = 0; i < _vShop.size(); i++)
				{
					char str[50], str2[10];

					HFONT oldFont, font;

					font = CreateFont(38, 16, 0, 0, 20, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("양재본목각체M"));
					oldFont = (HFONT)SelectObject(getMemDC(), font);
					SetBkMode(getMemDC(), TRANSPARENT);//투명한 배경을 사용한다
					SetTextColor(getMemDC(), RGB(_vImg[6].alpha, _vImg[6].alpha, _vImg[6].alpha));

					sprintf_s(str, _vShop[i].name);
					sprintf_s(str2, "%d", _vShop[i].price);

					TextOut(getMemDC(), _vImg[6].x + 35, _vImg[6].y + 60 + i * 50, str, strlen(str));
					TextOut(getMemDC(), _vImg[6].x + 370, _vImg[6].y + 60 + i * 50, str2, strlen(str2));

					DeleteObject(oldFont);
					DeleteObject(font);

				}
			}

			//아이템 효과
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
	sprintf_s(temp, "talkCount: %d _vImg[7].y: %d 선택된아이템: %d", _talkCount, _vImg[7].y, _selectedItem);
	TextOut(getMemDC(), 400, 50, temp, strlen(temp));
}

//카메라 좌표에 따른 상점 NPC 위치 조정
void shop::setLoc(int cameraX, int cameraY)
{
	for (int i = 0; i < _vImg.size(); i++)
	{
		_vImg[i].img->setX(_absolX - cameraX);
		_vImg[i].img->setY(_absolY - cameraY);
	}

	_rc = RectMake(_x - cameraX, _y - cameraY, 162, 108);
}


//이미지 셋팅
void shop::setImg(const char* keyName, const char* imgName, int x, int y, int width, int height, bool appear)
{
	tagShopImg temp;
	temp.img = IMAGEMANAGER->addImage(keyName, imgName, width, height, true, RGB(255, 0, 255));
	temp.x = x;
	temp.y = y;
	temp.alpha = 0;
	temp.isFrame = false;	//그냥 이미지
	temp.appear = appear;

	_vImg.push_back(temp);
}

//프레임 이미지 셋팅
void shop::setImg(const char* keyName, const char* imgName, int x, int y, int width, int height, int frameX, int frameY, bool appear)
{
	tagShopImg temp;
	temp.img = IMAGEMANAGER->addFrameImage(keyName, imgName, width, height, frameX, frameY, true, RGB(255, 0, 255));
	temp.x = x;
	temp.y = y;
	temp.alpha = 0;
	temp.isFrame = true;	//프레임 이미지
	temp.appear = appear;

	_vImg.push_back(temp);
}

//아이템 추가
void shop::addItem(tagItem item)
{
	tagItem temp = item;
	_vShop.push_back(temp);//아이템을 복사해서 상점의 아이템 벡터에 넣는다
}

//아이템 판매 시 제거
void shop::removeItem(int num)
{
	//_vItem.erase(_vItem.begin() + num);
}

//npc 이미지 전환(기본->프레임 혹은 프레임->기본)
void shop::changeNPC(void)
{
	_time++;

	if (_vImg[0].appear)
	{
		if (_time % 200 == 0)	//일정 시간이 되면 프레임 이미지로 전환
		{
			_vImg[0].appear = false;	//기본 이미지는 감춘다 
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
			_vImg[0].appear = true;	//다시 기본 이미지로
			_vImg[1].appear = false;
		}
		_vImg[1].img->setFrameX(_npcIdx);
	}
}

void shop::changeScript(void)
{
	//플레이어와 충돌 중이라면
	if (_isColli)
	{
		if (!_isTalk && !_vImg[2].appear)//대화 중이 아닐 경우에만
			showImg(2);

		if (_isTalk)//대화 중이고
		{
			if (!_firstTalk)//첫 대화일 때
			{
				if (_talkCount == 0 && _vImg[4].alpha == 255)//대사 이미지가 완전하게 뿌려졌을 때 대화횟수 증가
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
		if (!_isTalk)//대화 중이 아니라면
		{
			hideImg(2);
			_vImg[2].alpha = 0;
		}
		else	{ }
	}
}

//플레이어 rc와 충돌 여부
void shop::colliPlayer(RECT rc)
{
	RECT temp;

	if (IntersectRect(&temp, &_rc, &rc))
		_isColli = true;
	else
		_isColli = false;
}

//npc와 대화; 반드시 OnceKeyDown으로 호출해야 한다 안그러면 버퍼가 안비워져서 창이 삭제가 안된다 TT
void shop::talk(void)
{
	if (_firstTalk)//첫 대화가 아니라면
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

	if (!_firstTalk)//첫 대화라면
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
			_isTalk = false;//대화 중이 아니다
			_firstTalk = true;//이제부터 첫 대화가 아니다 
			_pl->setInShop(_isTalk);
		}
	}
}

//아이템 선택
void shop::select(bool isDown)
{
	bool success;

	//아이템 목록이 표시되었다면
	if (_isShowList)
	{
		//아래 방향키를 눌렀다
		if (isDown)
		{
			if (_vImg[7].y >= 196 && _vImg[7].y <= 246)
			{
				_vImg[7].y = _vImg[7].y + 50;
				_selectedItem++;
			}
		}
		//윗 방향키를 눌렀다
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

//구매할 것입니까
void shop::purchaseConfirm(void)
{
	//아이템 타입이 2: 발동효과(active item)
	//아이템 타입이 3: 지속효과(passive item)
	if (_vShop[_selectedItem].type == 2)
	{
		changeImg(8, 6);
	}
	else if (_vShop[_selectedItem].type == 3)
	{
		changeImg(9, 6);
	}
}