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

	_img->render(getMemDC(), _rc.left, _rc.top);


	int width = WINSIZEX / GAMEMAP_TILESIZE;
	int height = WINSIZEY / GAMEMAP_TILESIZE;

	image* _backBuffer3 = IMAGEMANAGER->addImage(L"backBuffer3", TILEX, TILEY);
	HDC hDCtemp = _backBuffer3->getMemDC();
	PatBlt(hDCtemp, 0, 0, TILEX, TILEY, BLACKNESS);

	HPEN oldPen = (HPEN)SelectObject(hDCtemp, _gPen[PENVERSION_MINIMAP]);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDCtemp, _gBrush[BRUSHVERSION_BLACK]);
	RectangleMake(hDCtemp, 0, 0, width, height);
	SelectObject(hDCtemp, oldPen);
	SelectObject(hDCtemp, oldBrush);


	GdiTransparentBlt(getMemDC(),		//복사될 DC영역
		_rc.left + MAINCAMERA->getCameraX() / GAMEMAP_TILESIZE,
		_rc.top + MAINCAMERA->getCameraY() / GAMEMAP_TILESIZE,
		width, height,												//복사될 가로 세로 크기

		hDCtemp,			//복사할 DC
		0, 0,				//복사할 좌표
		width, height,		//복사할 가로 세로 크기
		RGB(0, 0, 0));			//제외할 칼라


}