#pragma once
#include <vector>

class frameImage
{
private:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE,			//리소스로 부터
		LOAD_FILE,				//파일로 부터
		LOAD_EMPTY,
		LOAD_END
	};

	typedef struct tagImageInfo
	{
		DWORD resID;
		HDC hMemDC;
		HBITMAP hBit;
		HBITMAP hOBit;
		float x;
		float y;
		int width;
		int height;
		int currentFrameX;	//프레임 이미지 번호(가로)
		int currentFrameY;	//프레임 이미지 번호(세로)
		int maxFrameX;		//프레임의 끝 번호(가로)
		int maxFrameY;		//프레임의 끝 번호(세로)
		int frameWidth;		//프레임 이미지 한장당 가로크기
		int frameHeight;	//프레임 이미지 한장당 세로크기
		BYTE loadType;

		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
		}

	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;		//이미지 구조체
	CHAR*			_fileName;		//파일이름
	BOOL			_trans;			//특정 칼라 날릴꺼니?
	COLORREF		_transColor;	//날린다면 어떤 칼라를 날릴꺼니?(픽셀값)

	BLENDFUNCTION	_blendFunc;
	LPIMAGE_INFO	_blendImage;

public:
	frameImage();
	~frameImage();

	HRESULT init(const char* keyName, const char* fileName, int width, int height, int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = FALSE);

	void release();
};

