#pragma once
#include "gameNode.h"
#include "animation.h"

//==================================
// ## 2017.08.22 ## image Class ##
//==================================

class image : public gameNode
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE,		//리소스로부터
		LOAD_FILE,			//파일로부터
		LOAD_EMPTY,			//빈 비트맵 파일
		LOAD_END
	};

	typedef struct tagImageInfo
	{
		DWORD resID;		//리소스로부터 정보를 가져올땐 등록된 아이디로부터 가져오는데 그때 쓰임
		HDC hMemDC;			//메모리 DC (DC영역의 메모리(픽셀값등이 있음))
		HBITMAP hBit;		//비트맵
		HBITMAP hOBit;		//올드 비트맵(SelectObject)
		float	x;				//시작좌표 X
		float	y;				//시작좌표 Y
		int		width;			//가로 사이즈
		int		height;			//세로 사이즈
		int		currentFrameX;	//현재 프레임 번호 X
		int		currentFrameY;	//현재 프레임 번호 Y
		int		maxFrameX;		//맥스 프레임 X
		int		maxFrameY;		//맥스 프레임 Y
		int		frameWidth;		//프레임 한장 가로크기
		int		frameHeight;	//프레임 한장 세로크기
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
	
	BOOL			_useBlend;	//알파블랜드 사용할지 유무
	BLENDFUNCTION	_blendFunc;
	LPIMAGE_INFO	_blendImage;

public:
	image();
	~image();

	//빈 비트맵 이미지 초기화
	HRESULT init(int width, int height, BOOL blend = FALSE);
	//파일로부터 이미지 초기화
	HRESULT init(const TCHAR* fileName, int width, int height, BOOL trans = FALSE, COLORREF transColor = FALSE, BOOL blend = FALSE);

	HRESULT init(const TCHAR* fileName, float x, float y, int width, int height, BOOL trans = FALSE, COLORREF transColor = FALSE, BOOL blend = FALSE);

	HRESULT init(const TCHAR* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor, BOOL blend = FALSE);

	HRESULT init(const TCHAR* fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor, BOOL blend = FALSE);

	void release(void);

	void setTransColor(BOOL trans, COLORREF transColor);


	//이미지 렌더, DC영역, 뿌릴좌표X, 뿌릴좌표Y
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

	//센터기준 랜더링
	void frameRenderCT(HDC hdc, int cenX, int cenY, int currentFrameX, int currentFrameY);


	//메모리 디씨 접근자
	inline HDC getMemDC() { return _imageInfo->hMemDC; }

	//====================================================================
	// 이미지 조작을 쉽게하기 위한 getter, setter
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

