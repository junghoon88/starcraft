#include "stdafx.h"
#include "image.h"

#pragma comment(lib, "msimg32.lib")

image::image()
	: _imageInfo(NULL),
	_fileName(NULL),
	_trans(false),
	_transColor(RGB(0, 0, 0)),
	_useBlend(false)
{
}


image::~image()
{

}

//빈 비트맵 이미지 초기화
HRESULT image::init(int width, int height, BOOL blend)
{
	//이미지 정보가 널이 아니라면(이미지가 들어있다면) 해제해라
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	//빈 DC영역을 생성
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = NULL;

	_trans = FALSE;
	_transColor = RGB(0, 0, 0);

	//알파블렌드 셋팅
	_useBlend = blend;
	if (_useBlend)
	{
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER;

		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = WINSIZEX;
		_blendImage->height = WINSIZEY;
	}


	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

//파일로부터 이미지 초기화
HRESULT image::init(const TCHAR* fileName, int width, int height, BOOL trans, COLORREF transColor, BOOL blend)
{
	if (fileName == NULL) return E_FAIL;

	//이미지 정보가 널이 아니라면(이미지가 들어있다면) 해제해라
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	//빈 DC영역을 생성
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	int len = _tcslen(fileName);

	_fileName = new TCHAR[len + 1];
	_tcscpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	//알파블렌드 셋팅
	_useBlend = blend;
	if (_useBlend)
	{
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER;

		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = WINSIZEX;
		_blendImage->height = WINSIZEY;
	}

	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}


HRESULT image::init(const TCHAR* fileName, float x, float y, int width, int height, BOOL trans, COLORREF transColor, BOOL blend)
{
	if (fileName == NULL) return E_FAIL;

	//이미지 정보가 널이 아니라면(이미지가 들어있다면) 해제해라
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	//빈 DC영역을 생성
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;

	int len = _tcslen(fileName);

	_fileName = new TCHAR[len + 1];
	_tcscpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	//알파블렌드 셋팅
	_useBlend = blend;
	if (_useBlend)
	{
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER;

		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = WINSIZEX;
		_blendImage->height = WINSIZEY;
	}

	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const TCHAR* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor, BOOL blend)
{
	if (fileName == NULL) return E_FAIL;

	//이미지 정보가 널이 아니라면(이미지가 들어있다면) 해제해라
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	//빈 DC영역을 생성
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x - (width / 2);
	_imageInfo->y = y - (height / 2);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	

	int len = _tcslen(fileName);

	_fileName = new TCHAR[len + 1];
	_tcscpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	//알파블렌드 셋팅
	_useBlend = blend;
	if (_useBlend)
	{
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER;

		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = WINSIZEX;
		_blendImage->height = WINSIZEY;
	}

	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const TCHAR* fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor, BOOL blend)
{
	if (fileName == NULL) return E_FAIL;

	//이미지 정보가 널이 아니라면(이미지가 들어있다면) 해제해라
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	//빈 DC영역을 생성
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;


	int len = _tcslen(fileName);

	_fileName = new TCHAR[len + 1];
	_tcscpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	//알파블렌드 셋팅
	_useBlend = blend;
	if (_useBlend)
	{
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER;

		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = WINSIZEX;
		_blendImage->height = WINSIZEY;
	}

	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}



void image::release(void)
{
	if (_imageInfo)
	{
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);

		if (_useBlend)
		{
			SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
			DeleteObject(_blendImage->hBit);
			DeleteDC(_blendImage->hMemDC);

			SAFE_DELETE(_blendImage);
		}

		_trans = false;
		_transColor = RGB(0, 0, 0);
	}
}


void image::setTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;
	_transColor = transColor;

}

void image::render(HDC hdc)
{
	if (!_imageInfo)
		return;

	if (_trans)
	{
		//특정색상을 DC영역에서 제외해주는 함수
		GdiTransparentBlt(hdc,		//복사될 DC영역
			_imageInfo->x,			//복사될 DC영역에 뿌려줄 좌표
			_imageInfo->y,
			_imageInfo->width,		//복사될 가로 크기
			_imageInfo->height,		//복사될 세로 크기
			_imageInfo->hMemDC,		//복사할 DC
			0, 0,					//복사할 좌표
			_imageInfo->width,		//복사할 가로 크기
			_imageInfo->height,		//복사할 세로 크기
			_transColor);			//제외할 칼라
	}
	else
	{
		//백버퍼에 있는 걸 앞으로 고속복사해주는 함수
		BitBlt(hdc, _imageInfo->x, _imageInfo->y,
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}


//이미지 렌더, DC영역, 뿌릴좌표X, 뿌릴좌표Y
void image::render(HDC hdc, int destX, int destY)
{
	if (!_imageInfo)
		return;

	////카메라 영역 밖이면 랜더링하지 않는다.
	//RECT rcImg = RectMake(destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight);
	//RECT rcCamera = MAINCAMERA->getRectCamera();
	//RECT rcTemp;
	//if (IntersectRect(&rcTemp, &rcImg, &rcCamera) == FALSE)
	//{
	//	return;
	//}

	if (_trans)
	{
		//특정색상을 DC영역에서 제외해주는 함수
		GdiTransparentBlt(hdc,		//복사될 DC영역
			destX,					//복사될 DC영역에 뿌려줄 좌표
			destY,
			_imageInfo->width,		//복사될 가로 크기
			_imageInfo->height,		//복사될 세로 크기
			_imageInfo->hMemDC,		//복사할 DC
			0, 0,					//복사할 좌표
			_imageInfo->width,		//복사할 가로 크기
			_imageInfo->height,		//복사할 세로 크기
			_transColor);			//제외할 칼라
	}
	else
	{
		//백버퍼에 있는 걸 앞으로 고속복사해주는 함수
		BitBlt(hdc, destX, destY,
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

//dest 뿌릴 좌표 left, top  
//sour 뿌려올 좌표(left, top, width, height)
void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (!_imageInfo)
		return;

	if (_trans)
	{
		//특정색상을 DC영역에서 제외해주는 함수
		GdiTransparentBlt(hdc,		//복사될 DC영역
			destX,					//복사될 DC영역에 뿌려줄 좌표
			destY,
			sourWidth,				//복사될 가로 크기
			sourHeight,				//복사될 세로 크기
			_imageInfo->hMemDC,		//복사할 DC
			sourX, sourY,			//복사할 좌표
			sourWidth,				//복사할 가로 크기
			sourHeight,				//복사할 세로 크기
			_transColor);			//제외할 칼라
	}
	else
	{
		//백버퍼에 있는 걸 앞으로 고속복사해주는 함수
		BitBlt(hdc, destX, destY,
			sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY)
{
	if (!_imageInfo)
		return;

	if (_trans)
	{
		GdiTransparentBlt(hdc,
			destX,
			destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor);
	}
	else
	{
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	if (!_imageInfo)
		return;

	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (_trans)
	{
		GdiTransparentBlt(hdc,
			destX,
			destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor);
	}
	else
	{
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}

void image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	if (!_imageInfo)
		return;

	//정밀보정
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	//그려지는(복사되어오는) 이미지의 영역
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	RECT rcDest;

	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	for (int y = 0; y < drawAreaH; y+= sourHeight)
	{
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		if (y + sourHeight > drawAreaH)
		{
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			render(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top,
				rcSour.right - rcSour.left,
				rcSour.bottom - rcSour.top);
		}
	}
}

void image::alphaRender(HDC hdc, BYTE alpha)
{
	if (!_imageInfo)
		return;

	if (!_useBlend)
	{
		render(hdc);
		return;
	}


	//0 ~ 255
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, _imageInfo->x, _imageInfo->y, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);

		AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);

	}
	else
	{
		AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);

	}
}

void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	if (!_imageInfo)
		return;

	if (!_useBlend)
	{
		render(hdc, destX, destY);
		return;
	}

	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);

		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);

	}
	else
	{
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);

	}
}

void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	if (!_imageInfo)
		return;

	if (!_useBlend)
	{
		render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
		return;
	}

	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _transColor);

		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
			_blendImage->hMemDC, 0, 0, sourWidth, sourHeight, _blendFunc);

	}
	else
	{
		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _blendFunc);

	}
}

void image::alphaFrameRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	if (!_imageInfo)
		return;

	if (!_useBlend)
	{
		frameRender(hdc, destX, destY);
		return;
	}

	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight,
			hdc, destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC,
						0,
						0,
						_imageInfo->frameWidth,
						_imageInfo->frameHeight,
						_imageInfo->hMemDC,
						_imageInfo->currentFrameX * _imageInfo->frameWidth,
						_imageInfo->currentFrameY * _imageInfo->frameHeight,
						_imageInfo->frameWidth,
						_imageInfo->frameHeight,
						_transColor);

		AlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY, 
					_imageInfo->frameWidth,
					_imageInfo->frameHeight,
					_imageInfo->hMemDC,
					_imageInfo->currentFrameX * _imageInfo->frameWidth,
					_imageInfo->currentFrameY * _imageInfo->frameHeight,
					_imageInfo->frameWidth,
					_imageInfo->frameHeight,
					_blendFunc);
	}
}

void image::alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	if (!_imageInfo)
		return;

	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (!_useBlend)
	{
		frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
		return;
	}


	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight,
			hdc, destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC,
			0,
			0,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor);

		AlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_blendFunc);
	}
}

void image::aniRender(HDC hdc, int destX, int destY, animation* ani)
{
	render(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());
}

void image::aniAlphaRender(HDC hdc, int destX, int destY, animation* ani, BYTE alpha)
{
	alphaRender(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight(), alpha);
}