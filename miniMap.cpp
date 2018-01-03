#include "stdafx.h"
#include "miniMap.h"


miniMap::miniMap()
	: _img(NULL)
{
}


miniMap::~miniMap()
{
}


HRESULT miniMap::init(void)
{
	_img = IMAGEMANAGER->addImage(L"miniMap", TILEX, TILEY);
	PatBlt(_img->getMemDC(), 0, 0, TILEX, TILEY, BLACKNESS);

	memset(&_color, RGB(0, 0, 0), sizeof(COLORREF) * TILEX * TILEY);


	for (int x = 0; x < TILEX; x++)
	{
		for (int y = 0; y < TILEY; y++)
		{
			SetPixel(_img->getMemDC(), x, y, RGB(100, 100, 100));
		}
	}

	_rc = RectMake(6, 348, TILEX, TILEY);


	int width = WINSIZEX / TILESIZE;
	int height = WINSIZEY / TILESIZE;

	_rcMiniMapCamera = RectMake(0, 0, width, height);


	return S_OK;
}

void miniMap::release(void)
{
}

void miniMap::update(void)
{
}

void miniMap::render(void)
{
	if (_img == NULL)
		return;

	//_img->render(getMemDC(), _rc.left, _rc.top);
	RENDERMANAGER->insertImg(ZORDER_INTERFACE, _img, _rc.left, _rc.top);


	int width  = WINSIZEX / TILESIZE;
	int height = WINSIZEY / TILESIZE;

	image* _backBuffer3 = IMAGEMANAGER->addImage(L"backBuffer3", TILEX, TILEY);
	HDC hDCtemp = _backBuffer3->getMemDC();
	PatBlt(hDCtemp, 0, 0, TILEX, TILEY, BLACKNESS);

	HPEN oldPen = (HPEN)SelectObject(hDCtemp, _gPen[PENVERSION_MINIMAP]);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDCtemp, _gBrush[BRUSHVERSION_BLACK]);
	RectangleMake(hDCtemp, 0, 0, width, height);
	SelectObject(hDCtemp, oldPen);
	SelectObject(hDCtemp, oldBrush);


	GdiTransparentBlt(getMemDC(),		//복사될 DC영역
		_rc.left + MAINCAMERA->getCameraX() / TILESIZE,
		_rc.top + MAINCAMERA->getCameraY() / TILESIZE,
		width, height,												//복사될 가로 세로 크기

		hDCtemp,			//복사할 DC
		0, 0,				//복사할 좌표
		width, height,		//복사할 가로 세로 크기
		RGB(0, 0, 0));			//제외할 칼라


	//카메라
	{
		int x = MAINCAMERA->getCameraX() / TILESIZE;
		int y = MAINCAMERA->getCameraY() / TILESIZE;
		int width = WINSIZEX / TILESIZE;
		int height = WINSIZEY / TILESIZE;

		_rcMiniMapCamera = RectMake(x, y, width, height);



		RENDERMANAGER->insertLineRectangle(ZORDER_INTERFACE, _rcMiniMapCamera, PENVERSION_MINIMAP);
	}

}