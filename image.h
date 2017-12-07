#pragma once
#include "animation.h"

//==================================
// ## 2017.08.22 ## image Class ##
//==================================

class image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE,		//���ҽ��κ���
		LOAD_FILE,			//���Ϸκ���
		LOAD_EMPTY,			//�� ��Ʈ�� ����
		LOAD_END
	};

	typedef struct tagImageInfo
	{
		DWORD resID;		//���ҽ��κ��� ������ �����ö� ��ϵ� ���̵�κ��� �������µ� �׶� ����
		HDC hMemDC;			//�޸� DC (DC������ �޸�(�ȼ������� ����))
		HBITMAP hBit;		//��Ʈ��
		HBITMAP hOBit;		//�õ� ��Ʈ��(SelectObject)
		float	x;				//������ǥ X
		float	y;				//������ǥ Y
		int		width;			//���� ������
		int		height;			//���� ������
		int		currentFrameX;	//���� ������ ��ȣ X
		int		currentFrameY;	//���� ������ ��ȣ Y
		int		maxFrameX;		//�ƽ� ������ X
		int		maxFrameY;		//�ƽ� ������ Y
		int		frameWidth;		//������ ���� ����ũ��
		int		frameHeight;	//������ ���� ����ũ��
		BYTE	loadType;

		tagImageInfo()
		{
			resID			= 0;
			hMemDC			= NULL;
			hBit			= NULL;
			hOBit			= NULL;
			x				= 0;
			y				= 0;
			width			= 0;
			height			= 0;
			currentFrameX	= 0;
			currentFrameY	= 0;
			maxFrameX		= 0;
			maxFrameY		= 0;
			frameWidth		= 0;
			frameHeight		= 0;
			loadType		= LOAD_RESOURCE;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;
	TCHAR*			_fileName;
	BOOL			_trans;
	COLORREF		_transColor;
	
	BOOL			_useBlend;	//���ĺ����� ������� ����
	BLENDFUNCTION	_blendFunc;
	LPIMAGE_INFO	_blendImage;

public:
	image();
	~image();

	//�� ��Ʈ�� �̹��� �ʱ�ȭ
	HRESULT init(int width, int height, BOOL blend = FALSE);
	//���Ϸκ��� �̹��� �ʱ�ȭ
	HRESULT init(const TCHAR* fileName, int width, int height, BOOL trans = FALSE, COLORREF transColor = FALSE, BOOL blend = FALSE);

	HRESULT init(const TCHAR* fileName, float x, float y, int width, int height, BOOL trans = FALSE, COLORREF transColor = FALSE, BOOL blend = FALSE);

	HRESULT init(const TCHAR* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor, BOOL blend = FALSE);

	HRESULT init(const TCHAR* fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor, BOOL blend = FALSE);

	void release(void);

	void setTransColor(BOOL trans, COLORREF transColor);


	//�̹��� ����, DC����, �Ѹ���ǥX, �Ѹ���ǥY
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);

	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	void alphaFrameRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

	void aniRender(HDC hdc, int destX, int destY, animation* ani);
	void aniAlphaRender(HDC hdc, int destX, int destY, animation* ani, BYTE alpha);

	//�޸� �� ������
	inline HDC getMemDC() { return _imageInfo->hMemDC; }

	//====================================================================
	// �̹��� ������ �����ϱ� ���� getter, setter
	//====================================================================

	inline void setX(float x) { _imageInfo->x = x; }
	inline float getX() { return _imageInfo->x; }

	inline void setY(float y) { _imageInfo->y = y; }
	inline float getY() { return _imageInfo->y; }

	inline float getWidth() { return (float)(_imageInfo->width); }
	inline float getHeight() { return (float)(_imageInfo->height); }

	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	inline float getCenterX()
	{
		return _imageInfo->maxFrameX <= 0 ? _imageInfo->x + (_imageInfo->width / 2) : _imageInfo->x + (_imageInfo->frameWidth / 2);
	}

	inline float getCenterY()
	{
		return _imageInfo->maxFrameY <= 0 ? _imageInfo->y + (_imageInfo->height / 2) : _imageInfo->y + (_imageInfo->frameHeight / 2);
	}

	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (_imageInfo->maxFrameX < frameX) _imageInfo->maxFrameX = frameX;
	}

	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (_imageInfo->maxFrameY < frameY) _imageInfo->maxFrameY = frameY;
	}

	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }

	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }

	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

	inline void setWidth(float width) { _imageInfo->width = width; }

	inline TCHAR* getFileName(void) { return _fileName; }

	inline void nextFrameX(void) { _imageInfo->currentFrameX = _imageInfo->currentFrameX == _imageInfo->maxFrameX ? 0 : _imageInfo->currentFrameX + 1; }
	inline void nextFrameY(void) { _imageInfo->currentFrameY = _imageInfo->currentFrameY == _imageInfo->maxFrameY ? 0 : _imageInfo->currentFrameY + 1; }
};
