#include "stdafx.h"
#include "saveLoadTest.h"


saveLoadTest::saveLoadTest()
{
}


saveLoadTest::~saveLoadTest()
{
}

void saveLoadTest::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) save();
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) load();
}

void saveLoadTest::save(void)
{
	//���� �����
	//C - FILE*
	//C++ - ifstream, ofstream
	//WIN32 - CreateFile

	//���ð��ӿ� �� ������ ���
	//HPBar, Save & Load, 

	HANDLE file;

	char str[128] = "�Ⳳ�� �ָ��� ����ߴ�";
	DWORD write;

	file = CreateFile("�����̲������.txt", GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, str, strlen(str), &write, NULL);

	CloseHandle(file);
}

void saveLoadTest::load(void)
{
	HANDLE file;

	char str[128];
	DWORD read;

	file = CreateFile("�����̲������.txt", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, strlen(str), &read, NULL);

	CloseHandle(file);

	MessageBox(_hWnd, str, "��~��", MB_OK);
}