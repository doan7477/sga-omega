#include "stdafx.h"
#include "fontTest.h"


fontTest::fontTest()
{
}


fontTest::~fontTest()
{
}

HRESULT fontTest::init()
{

	return S_OK;
}

void fontTest::release()
{

}

void fontTest::update()
{

}

void fontTest::render()
{
	//TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY / 2, "������ �ϼ��ض�", strlen("������ �ϼ��ض�"));
	
	//CreateFont�� ���� ����ϱ�
	char str[128];
	HFONT oldFont, font1;
	
	/*
	CreateFont(40,				//������
		0,						//���� ����
		40,						//���� ����(����)
		0,						//���� ����
		600,					//���� ����
		0,						//bool ���� ���� true, false
		0,						//bool ���� ����ĥ�� true, false
		0,						//bool ���� ��Ҽ� true, false
		HANGUL_CHARSET,			//���� ����
		0,						//��� ��Ȯ��
		0,						//Ŭ���� ��Ȯ��
		0,						//����� ����Ƽ
		0,						//�ڰ�
		TEXT("�ü�ü"));
	*/

	font1 = CreateFont(80, 0, 0, 0, 300, true, 1, false, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("����ü"));
	oldFont = (HFONT)SelectObject(getMemDC(), font1);
	sprintf(str, "ġŲ������");
	TextOut(getMemDC(), 10, 100, str, strlen(str));
	DeleteObject(font1);

	RECT rcText = RectMake(10, 300, 400, 100);

	HFONT font2 = CreateFont(80, 0, 0, 0, 300, false, false, false, 
		DEFAULT_CHARSET, OUT_STROKE_PRECIS, CLIP_CHARACTER_PRECIS,
		PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Import"));

	HFONT oldfont2 = (HFONT)SelectObject(getMemDC(), font2);
	DrawText(getMemDC(), TEXT("SUCCESS"), 8, &rcText, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	DeleteObject(oldfont2);
	DeleteObject(font2);


}
