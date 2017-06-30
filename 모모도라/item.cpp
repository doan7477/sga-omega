#include "stdafx.h"
#include "item.h"


item::item()
{
}


item::~item()
{
}

HRESULT item::init()
{
	//아이템 목록에 아이템들 추가


	//화폐 아이템
	tagItem item1;
	ZeroMemory(&item1, sizeof(tagItem));	//메모리를 꺠끗하게 비운다
	item1.img = IMAGEMANAGER->addImage("돈", "image/돈.bmp", 21, 21, true, RGB(255, 0, 255));
	item1.name = "무니";
	item1.effect = "화폐로 취급됩니다.";
	item1.desct = "상점에서 물건을 살 수 있습니다.";
	item1.x = 10;	//임시위치;돈은 enemy가 죽은 곳에서 생성된다
	item1.y = 10;
	item1.type = 1;	//돈
	item1.price = 1;
	item1.ability = 1;	//화폐는 1개씩 늘어난다 

	//생성하면 벡터행
	_vItem.push_back(item1);


	//활성 슬롯
	tagItem item2;
	ZeroMemory(&item2, sizeof(tagItem));	//메모리를 꺠끗하게 비운다
	item2.img = IMAGEMANAGER->addImage("초롱꽃", "image/초롱꽃.bmp", 72, 72, true, RGB(255, 0, 255));
	item2.name = "초롱꽃";
	item2.effect = "쓸 때마다 HP를 소량 회복합니다.";
	item2.desct = "회복력이 있는 꽃이 썩었습니다.";
	item2.x = 52;
	item2.y = 121;
	item2.type = 2;	//active item
	item2.price = 200;
	item2.ability = 3;	//HP를 3만큼씩 회복

	//생성하면 벡터행
	_vItem.push_back(item2);


	//지속 슬롯
	tagItem item3;
	ZeroMemory(&item3, sizeof(tagItem));	//메모리를 꺠끗하게 비운다
	item3.img = IMAGEMANAGER->addImage("등가의훈장", "image/등가의훈장.bmp", 72, 72, true, RGB(255,0,255));
	item3.name = "등가의 훈장";
	item3.effect = "천천히 HP를 회복합니다.";
	item3.desct = "크로미니아 지방에서 온 훈장.\n사슴을 타고 평생을 먼 지방까지\n돌아다닌 전령들이 달고 다녔습니다.";
	item3.x = 52;
	item3.y = 286;
	item3.type = 3;	//passive item
	item3.price = 200;
	item3.ability = 3;	//HP를 3만큼씩 회복

	//생성하면 벡터행
	_vItem.push_back(item3);

	tagItem item4;
	ZeroMemory(&item4, sizeof(tagItem));	//메모리를 꺠끗하게 비운다
	item4.img = IMAGEMANAGER->addImage("아스트랄부적", "image/아스트랄부적.bmp", 72, 72, true, RGB(255, 0, 255));
	item4.name = "아스트랄 부적";
	item4.effect = "적이 떨어뜨리는 무니가 두 배가 됩니다.";
	item4.desct = "오래되어 닳은 부적.\n행운을 크게 늘려줍니다.";
	item4.x = 52;
	item4.y = 286;
	item4.type = 3;
	item4.price = 300;
	item4.ability = 2;	//무니를 2배로 불림
	
	//생성하면 벡터행
	_vItem.push_back(item4);

	return S_OK;
}