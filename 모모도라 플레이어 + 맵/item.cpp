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
	//������ ��Ͽ� �����۵� �߰�


	//ȭ�� ������
	tagItem item1;
	ZeroMemory(&item1, sizeof(tagItem));	//�޸𸮸� �Ʋ��ϰ� ����
	item1.img = IMAGEMANAGER->addImage("��", "image/��.bmp", 21, 21, true, RGB(255, 0, 255));
	item1.name = "����";
	item1.effect = "ȭ��� ��޵˴ϴ�.";
	item1.desct = "�������� ������ �� �� �ֽ��ϴ�.";
	item1.x = 10;	//�ӽ���ġ;���� enemy�� ���� ������ �����ȴ�
	item1.y = 10;
	item1.type = 1;	//��
	item1.price = 1;
	item1.ability = 1;	//ȭ��� 1���� �þ�� 

	//�����ϸ� ������
	_vItem.push_back(item1);


	//Ȱ�� ����
	tagItem item2;
	ZeroMemory(&item2, sizeof(tagItem));	//�޸𸮸� �Ʋ��ϰ� ����
	item2.img = IMAGEMANAGER->addImage("�ʷղ�", "image/�ʷղ�.bmp", 72, 72, true, RGB(255, 0, 255));
	item2.name = "�ʷղ�";
	item2.effect = "�� ������ HP�� �ҷ� ȸ���մϴ�.";
	item2.desct = "ȸ������ �ִ� ���� ������ϴ�.";
	item2.x = 52;
	item2.y = 121;
	item2.type = 2;	//active item
	item2.price = 200;
	item2.ability = 3;	//HP�� 3��ŭ�� ȸ��

	//�����ϸ� ������
	_vItem.push_back(item2);


	//���� ����
	tagItem item3;
	ZeroMemory(&item3, sizeof(tagItem));	//�޸𸮸� �Ʋ��ϰ� ����
	item3.img = IMAGEMANAGER->addImage("�������", "image/�������.bmp", 72, 72, true, RGB(255,0,255));
	item3.name = "��� ����";
	item3.effect = "õõ�� HP�� ȸ���մϴ�.";
	item3.desct = "ũ�ι̴Ͼ� ���濡�� �� ����.\n�罿�� Ÿ�� ����� �� �������\n���ƴٴ� ���ɵ��� �ް� �ٳ���ϴ�.";
	item3.x = 52;
	item3.y = 286;
	item3.type = 3;	//passive item
	item3.price = 200;
	item3.ability = 3;	//HP�� 3��ŭ�� ȸ��

	//�����ϸ� ������
	_vItem.push_back(item3);

	tagItem item4;
	ZeroMemory(&item4, sizeof(tagItem));	//�޸𸮸� �Ʋ��ϰ� ����
	item4.img = IMAGEMANAGER->addImage("�ƽ�Ʈ������", "image/�ƽ�Ʈ������.bmp", 72, 72, true, RGB(255, 0, 255));
	item4.name = "�ƽ�Ʈ�� ����";
	item4.effect = "���� ����߸��� ���ϰ� �� �谡 �˴ϴ�.";
	item4.desct = "�����Ǿ� ���� ����.\n����� ũ�� �÷��ݴϴ�.";
	item4.x = 52;
	item4.y = 286;
	item4.type = 3;
	item4.price = 300;
	item4.ability = 2;	//���ϸ� 2��� �Ҹ�
	
	//�����ϸ� ������
	_vItem.push_back(item4);

	return S_OK;
}