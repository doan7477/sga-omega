#include "stdafx.h"
#include "frameImageManager.h"


frameImageManager::frameImageManager()
{
}


frameImageManager::~frameImageManager()
{
}

HRESULT frameImageManager::init()
{

	return S_OK;
}

void frameImageManager::release()
{
	deleteAll();
}

void frameImageManager::update()
{
}

void frameImageManager::render()
{

}

void frameImageManager::addFrameAnimation(string keyName, char* imageName, int fps, void* cbFunction)
{

}

void frameImageManager::addFrameAnimation(string keyName, char* imageName, int fps, void* cbFunction, void* obj)
{

}

void frameImageManager::start(string keyName)
{

}

frameImage* frameImageManager::findFrameAnimation(string keyName)
{
	return NULL;
}

void frameImageManager::deleteAll()
{

}