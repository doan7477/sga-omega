// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
#pragma once
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <tchar.h>
#include <commdlg.h>	//OPENFILENAME

#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "imageManager.h"
#include "timeManager.h"
#include "effectManager.h"
#include "soundManager.h"
#include "sceneManager.h"
#include "keyAniManager.h"
#include "iniDataManager.h"
#include "pixelCollisionManager.h"
#include "utils.h"
#include "collision.h"
#include "txtData.h"
#include "database.h"

using namespace std;
using namespace OMEGA_UTIL;


//==================================
// ## 2017.04.05 ## �����ι� ##
//==================================

#define WINNAME (LPTSTR)(TEXT("Momodora : Reverie Under the Moonlight"))
#define WINSTARTX 400			//������ â �������� X��ǥ
#define WINSTARTY 200			//������ â �������� Y��ǥ
#define WINSIZEX  962			//������ â ����ũ��
#define WINSIZEY  722			//������ â ����ũ��
#define WINSTYLE WS_CAPTION | WS_SYSMENU

//�����Լ� ������
#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define EFFECTMANAGER effectManager::getSingleton()
#define SOUNDMANAGER soundManager::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define KEYANIMANAGER keyAniManager::getSingleton()
#define PIXELMANAGER pixelCollisionManager::getSingleton()
#define TXTDATA txtData::getSingleton()
#define INIDATA iniDataManager::getSingleton()
#define DATABASE database::getSingleton()

//==================================
// ## 2017.04.05 ## ��ũ�� �Լ� ##
//==================================

#define SAFE_DELETE(p)	{if(p) {delete(p); (p) = NULL;}}
#define SAFE_RELEASE(p) {if(p) {(p)->release(); (p) = NULL;}}

//==================================
// ## 2017.04.10 ## ���� ���� ##
//==================================

extern HWND _hWnd;
extern HINSTANCE _hInstance;
extern POINT _ptMouse;