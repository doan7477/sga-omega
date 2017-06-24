#include "stdafx.h"
#include "soundTest.h"


soundTest::soundTest()
{
}


soundTest::~soundTest()
{
}

HRESULT soundTest::init()
{
	SOUNDMANAGER->addSound("������ġ", "Kalimba.mp3", true, true);
	SOUNDMANAGER->addSound("������ġ2", "Kalimba.mp3", true, true);
	SOUNDMANAGER->addSound("������ġ3", "Kalimba.mp3", true, true);

	

	return S_OK;
}

void soundTest::release()
{

}

void soundTest::update()
{
	//SOUNDMANAGER->play("������ġ", 0.8f);


	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		SOUNDMANAGER->play("������ġ", 0.8f);
	}

	if (KEYMANAGER->isOnceKeyDown('O'))
	{
		SOUNDMANAGER->stop("������ġ");
	}


	if (KEYMANAGER->isOnceKeyDown('J'))
	{
		SOUNDMANAGER->pause("������ġ");
	}

	if (KEYMANAGER->isOnceKeyDown('K'))
	{
		SOUNDMANAGER->resume("������ġ");
	}

	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		SOUNDMANAGER->play("������ġ2", 1.0f);
	}

	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		SOUNDMANAGER->play("������ġ3", 1.0f);
	}
}