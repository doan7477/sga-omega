#pragma once
#include <vector>

class frameImage
{
private:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE,			//���ҽ��� ����
		LOAD_FILE,				//���Ϸ� ����
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
		int currentFrameX;	//������ �̹��� ��ȣ(����)
		int currentFrameY;	//������ �̹��� ��ȣ(����)
		int maxFrameX;		//�������� �� ��ȣ(����)
		int maxFrameY;		//�������� �� ��ȣ(����)
		int frameWidth;		//������ �̹��� ����� ����ũ��
		int frameHeight;	//������ �̹��� ����� ����ũ��
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
	LPIMAGE_INFO	_imageInfo;		//�̹��� ����ü
	CHAR*			_fileName;		//�����̸�
	BOOL			_trans;			//Ư�� Į�� ��������?
	COLORREF		_transColor;	//�����ٸ� � Į�� ��������?(�ȼ���)

	BLENDFUNCTION	_blendFunc;
	LPIMAGE_INFO	_blendImage;

public:
	frameImage();
	~frameImage();

	HRESULT init(const char* keyName, const char* fileName, int width, int height, int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = FALSE);

	void release();
};

