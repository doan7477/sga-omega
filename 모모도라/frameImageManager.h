#pragma once
#include "frameImage.h"
#include "singletonBase.h"
#include <map>

class frameImageManager : public singletonBase<frameImageManager>
{
private:
	typedef map<string, frameImage*> arrFrameImage;
	typedef map<string, frameImage*> iterFrameImage;

private:
	arrFrameImage _vTotalFrameAnimation;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void addFrameAnimation(string keyName, char* imageName, int fps, void* cbFunction);
	void addFrameAnimation(string keyName, char* imageName, int fps, void* cbFunction, void* obj);

	void start(string keyName);
	frameImage* findFrameAnimation(string keyName);

	void deleteAll();

	frameImageManager();
	~frameImageManager();
};

