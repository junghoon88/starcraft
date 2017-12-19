#include "stdafx.h"
#include "sceneMaptool.h"


sceneMaptool::sceneMaptool()
	: _imgMiniMap(NULL)
{
	for (int i = 0; i < BTNCTRL_MAX; i++)
	{
		_btnCtrl[i] = NULL;
	}
	ZeroMemory(&_tiles, sizeof(tagTile) * TILEX * TILEY);
	ZeroMemory(&_imgTiles, sizeof(INT32) * TILEX * TILEY);
	ZeroMemory(&_isChangedTile, sizeof(BOOL) * TILEX * TILEY);
	
	_isoCursor = { 0, 0 };


	_startIso = _endIso = { 0, 0 };

	_isClicked = false;
	_endDrag = false;

}


sceneMaptool::~sceneMaptool()
{

}

HRESULT sceneMaptool::init(void)
{
	initButtons();

	initMiniMap();

	initTiles();

	setTileImageAll();

	//initIsoTiles();

	_curTerrain = SAMPLETERRAIN_DIRT;
	_rcSelectTerrain[SAMPLETERRAIN_DIRT] = RectMake(SIDEWINDOW_STARTX + 10, _rcMiniMap.bottom + 30, MAPTOOL_TILESIZE, MAPTOOL_TILESIZE);
	_rcSelectTerrain[SAMPLETERRAIN_HIGTDIRT] = RectMake(_rcSelectTerrain[SAMPLETERRAIN_DIRT].right + 5, _rcSelectTerrain[SAMPLETERRAIN_DIRT].top, MAPTOOL_TILESIZE, MAPTOOL_TILESIZE);
	_rcSelectTerrain[SAMPLETERRAIN_WATER] = RectMake(_rcSelectTerrain[SAMPLETERRAIN_HIGTDIRT].right + 5, _rcSelectTerrain[SAMPLETERRAIN_HIGTDIRT].top, MAPTOOL_TILESIZE, MAPTOOL_TILESIZE);



	return S_OK;
}

void sceneMaptool::release(void)
{
	for (int i = 0; i < BTNCTRL_MAX; i++)
	{
		SAFE_DELETE(_btnCtrl[i]);
	}

}

void sceneMaptool::update(void)
{
	//카메라 이동, 미니맵 클릭 이동
	updateCamera();

	//터레인 선택
	selectTerrain();

	//마우스가 위치한 ISO 계산
	calcIsoTile();

	//마우스가 클릭했을 때
	clickIsoTile();

	//타일 이미지 갱신
	updateTileImage();


	for (int i = 0; i < BTNCTRL_MAX; i++)
	{
		_btnCtrl[i]->update();
	}
}

void sceneMaptool::render(void)
{
	renderTiles();

	//드래그 상태일 때 파란색으로 영역 표시해주기
	renderDragingIsoTiles();

	//현재 커서의 ISO 보여주기
	renderCurIsoTile();

	renderSideWindow();


}

void sceneMaptool::getChar(WPARAM wParam)
{

}

void sceneMaptool::initButtons(void)
{
	_btnCtrl[BTNCTRL_SAVE] = new button;
	_btnCtrl[BTNCTRL_SAVE]->init(L"버튼2", L"SAVE", (SIDEWINDOW_STARTX + WINSIZEX) / 2, WINSIZEY - 110, { 0,0 }, { 0,0 }, cbButtonSave, this);
	_btnCtrl[BTNCTRL_SAVE]->setColor(RGB(92, 237, 48));

	_btnCtrl[BTNCTRL_LOAD] = new button;
	_btnCtrl[BTNCTRL_LOAD]->init(L"버튼2", L"LOAD", (SIDEWINDOW_STARTX + WINSIZEX) / 2, WINSIZEY - 70, { 0,0 }, { 0,0 }, cbButtonLoad, this);
	_btnCtrl[BTNCTRL_LOAD]->setColor(RGB(92, 237, 48));

	_btnCtrl[BTNCTRL_EXIT] = new button;
	_btnCtrl[BTNCTRL_EXIT]->init(L"버튼2", L"EXIT", (SIDEWINDOW_STARTX + WINSIZEX) / 2, WINSIZEY - 30, { 0,0 }, { 0,0 }, cbButtonExit, this);
	_btnCtrl[BTNCTRL_EXIT]->setColor(RGB(92, 237, 48));

}

void sceneMaptool::initMiniMap(void)
{
	_imgMiniMap = IMAGEMANAGER->addImage(L"맵툴미니맵", TILEX, TILEY);
	PatBlt(_imgMiniMap->getMemDC(), 0, 0, TILEX, TILEY, BLACKNESS);

	int x = MAINCAMERA->getCameraX() / MAPTOOL_TILESIZE;
	int y = MAINCAMERA->getCameraY() / MAPTOOL_TILESIZE;
	int width  = WINSIZEX / MAPTOOL_TILESIZE;
	int height = WINSIZEY / MAPTOOL_TILESIZE;

	_rcMiniMap = RectMake(SIDEWINDOW_STARTX + 16, 16, TILEX, TILEY);
	_rcMiniMapCamera = RectMake(x, y, width, height);
}


void sceneMaptool::initTiles(void)
{
	for (int y = 0; y < TILEY; y++)
	{
		for (int x = 0; x < TILEX; x++)
		{
			_tiles[x][y].terrain = TERRAIN_DIRT;
			_tiles[x][y].terrainNum = { 0, 0 };
			_tiles[x][y].obj = 0;
			_tiles[x][y].rc = RectMake(x * MAPTOOL_TILESIZE, y * MAPTOOL_TILESIZE, MAPTOOL_TILESIZE, MAPTOOL_TILESIZE);
			_tiles[x][y].isClick = false;
		}
	}
}


void sceneMaptool::initIsoTiles(void)
{
#if 0
	int firstCenterX = MAPTOOL_TILESIZE * MAPTOOL_TILEVIEWX * 0.5f;
	int firstCenterY = -(MAPTOOL_TILESIZE * MAPTOOL_TILEVIEWX * 0.5f);

	for (int i = 0; i < ISOTILEY; i++)
	{
		for (int j = 0; j < ISOTILEX; j++)
		{
			_isoTile[j][i].pt.x = firstCenterX + ISOTILE_HALF_WIDTH  * (i - j);
			_isoTile[j][i].pt.y = firstCenterY + ISOTILE_HALF_HEIGHT * (i + j);
			_isoTile[j][i].rc = RectMakeCenter(_isoTile[j][i].pt.x, _isoTile[j][i].pt.y, ISOTILE_WIDTH, ISOTILE_HEIGHT);
			_isoTile[j][i].clicked = false;
		}
	}
#endif
}

void sceneMaptool::updateCamera(void)
{
	if (PtInRect(&_rcMiniMap, _ptMouse))
	{
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			float x = _ptMouse.x - _rcMiniMap.left;
			float y = _ptMouse.y - _rcMiniMap.top;

			float halfWidth  = (WINSIZEX / MAPTOOL_TILESIZE) * 0.5f;
			float halfHeight = (WINSIZEY / MAPTOOL_TILESIZE) * 0.5f;

			if (x <= halfWidth)					x = halfWidth;
			else if (x >= TILEX - halfWidth)	x = TILEX - halfWidth;

			if (y <= halfHeight)				y = halfHeight;
			else if (y >= TILEY - halfHeight)	y = TILEY - halfHeight;


			MAINCAMERA->setCameraPos((x - halfWidth) * MAPTOOL_TILESIZE, (y - halfHeight) * MAPTOOL_TILESIZE);
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		MAINCAMERA->moveCamera(DIRECTION_RG);
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		MAINCAMERA->moveCamera(DIRECTION_LF);
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		MAINCAMERA->moveCamera(DIRECTION_UP);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		MAINCAMERA->moveCamera(DIRECTION_DN);
	}

	int x = MAINCAMERA->getCameraX() / MAPTOOL_TILESIZE;
	int y = MAINCAMERA->getCameraY() / MAPTOOL_TILESIZE;
	int width  = WINSIZEX / MAPTOOL_TILESIZE;
	int height = WINSIZEY / MAPTOOL_TILESIZE;

	_rcMiniMapCamera = RectMake(x, y, width, height);
}

void sceneMaptool::selectTerrain(void)
{
	for (int i = 0; i < SAMPLETERRAIN_MAX; i++)
	{
		if (PtInRect(&_rcSelectTerrain[i], _ptMouse))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_curTerrain = (SAMPLETERRAIN)i;
				return;
			}
		}
	}
}

void sceneMaptool::calcIsoTile(void)
{
	if (_ptMouse.x >= SIDEWINDOW_STARTX)
		return;


#if 0
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < ISOTILEY; i++)
		{
			for (int j = 0; j < ISOTILEX; j++)
			{
				if (PtInRect(&_isoTile[j][i].rc, _ptMouse))
				{
					//1사분면
					if (_ptMouse.y <= _isoTile[j][i].pt.y && _ptMouse.x >= _isoTile[j][i].pt.x)
					{
						float angleDeg = Rad2Deg(getAngle(_isoTile[j][i].rc.right, _isoTile[j][i].pt.y, _ptMouse.x, _ptMouse.y));
						float angleDegRef = Rad2Deg(getAngle(_isoTile[j][i].rc.right, _isoTile[j][i].pt.y, _isoTile[j][i].pt.x, _isoTile[j][i].rc.top));
						if (angleDeg >= angleDegRef)
						{
							_isoTile[j][i].clicked ^= 1;
							break;
						}
						else continue;
					}
					//2사분면
					if (_ptMouse.y <= _isoTile[j][i].pt.y && _ptMouse.x < _isoTile[j][i].pt.x)
					{
						float angleDeg = Rad2Deg(getAngle(_isoTile[j][i].rc.left, _isoTile[j][i].pt.y, _ptMouse.x, _ptMouse.y));
						float angleDegRef = Rad2Deg(getAngle(_isoTile[j][i].rc.left, _isoTile[j][i].pt.y, _isoTile[j][i].pt.x, _isoTile[j][i].rc.top));
						if (angleDeg <= angleDegRef)
						{
							_isoTile[j][i].clicked ^= 1;
							break;
						}
						else continue;
					}
					//3사분면
					if (_ptMouse.y > _isoTile[j][i].pt.y && _ptMouse.x < _isoTile[j][i].pt.x)
					{
						float angleDeg = Rad2Deg(getAngle(_isoTile[j][i].rc.left, _isoTile[j][i].pt.y, _ptMouse.x, _ptMouse.y));
						float angleDegRef = Rad2Deg(getAngle(_isoTile[j][i].rc.left, _isoTile[j][i].pt.y, _isoTile[j][i].pt.x, _isoTile[j][i].rc.bottom));
						if (angleDeg >= angleDegRef)
						{
							_isoTile[j][i].clicked ^= 1;
							break;
						}
						else continue;
					}
					//4사분면
					if (_ptMouse.y > _isoTile[j][i].pt.y && _ptMouse.x >= _isoTile[j][i].pt.x)
					{
						float angleDeg = Rad2Deg(getAngle(_isoTile[j][i].rc.right, _isoTile[j][i].pt.y, _ptMouse.x, _ptMouse.y));
						float angleDegRef = Rad2Deg(getAngle(_isoTile[j][i].rc.right, _isoTile[j][i].pt.y, _isoTile[j][i].pt.x, _isoTile[j][i].rc.bottom));
						if (angleDeg <= angleDegRef)
						{
							_isoTile[j][i].clicked ^= 1;
							break;
						}
						else continue;
					}
				}
				else _isoTile[j][i].clicked = 0;
			}
		}
	}
#endif

	POINT cursorPt = { _ptMouse.x + MAINCAMERA->getCameraX() , _ptMouse.y + MAINCAMERA->getCameraY() };
	POINT cursorTile;
	cursorTile.x = (LONG)(cursorPt.x / MAPTOOL_TILESIZE);
	cursorTile.y = (LONG)(cursorPt.y / MAPTOOL_TILESIZE);

	// 가로 4칸, 세로 2칸 영역별로 나눠서 계산
	POINT tempIndex = { cursorTile.x % 4, cursorTile.y % 2 }; 

	//     0 1 2 3
	//  0 
	//  1

	float angle = 0.0f;		//마우스가 위치한 각도
	float angleRef = 0.0f;	//iso 기준 각도
	
	POINT startRef = { 0,0 };
	POINT endRef = { 0,0 };

	//상단
	if (tempIndex.y == 0)
	{
		switch (tempIndex.x)
		{
		case 0:
			startRef.x = _tiles[cursorTile.x][cursorTile.y].rc.left;
			startRef.y = _tiles[cursorTile.x][cursorTile.y].rc.bottom;
			endRef.x = _tiles[cursorTile.x + 1][cursorTile.y].rc.right;
			endRef.y = _tiles[cursorTile.x + 1][cursorTile.y].rc.top;
			angleRef = getAngle(startRef.x, startRef.y, endRef.x, endRef.y);
			angle = getAngle(startRef.x, startRef.y, cursorPt.x, cursorPt.y);

			if (angle <= angleRef)
			{
				//영역 안에 있을경우
				_isoCursor.x = _tiles[cursorTile.x + 1][cursorTile.y].rc.right;
				_isoCursor.y = _tiles[cursorTile.x][cursorTile.y].rc.bottom;
			}
			else
			{
				//영역 밖일 경우
				_isoCursor.x = _tiles[cursorTile.x][cursorTile.y].rc.left;
				_isoCursor.y = _tiles[cursorTile.x][cursorTile.y].rc.top;
			}

			break;
		case 1:
			startRef.x = _tiles[cursorTile.x - 1][cursorTile.y].rc.left;
			startRef.y = _tiles[cursorTile.x - 1][cursorTile.y].rc.bottom;
			endRef.x = _tiles[cursorTile.x][cursorTile.y].rc.right;
			endRef.y = _tiles[cursorTile.x][cursorTile.y].rc.top;
			angleRef = getAngle(startRef.x, startRef.y, endRef.x, endRef.y);
			angle = getAngle(startRef.x, startRef.y, cursorPt.x, cursorPt.y);

			if (angle <= angleRef)
			{
				//영역 안에 있을경우
				_isoCursor.x = _tiles[cursorTile.x][cursorTile.y].rc.right;
				_isoCursor.y = _tiles[cursorTile.x][cursorTile.y].rc.bottom;
			}
			else
			{
				//영역 밖일 경우
				_isoCursor.x = _tiles[cursorTile.x - 1][cursorTile.y].rc.left;
				_isoCursor.y = _tiles[cursorTile.x][cursorTile.y].rc.top;
			}
			break;
		case 2:
			startRef.x = _tiles[cursorTile.x + 1][cursorTile.y].rc.right;
			startRef.y = _tiles[cursorTile.x + 1][cursorTile.y].rc.bottom;
			endRef.x = _tiles[cursorTile.x][cursorTile.y].rc.left;
			endRef.y = _tiles[cursorTile.x][cursorTile.y].rc.top;
			angleRef = getAngle(startRef.x, startRef.y, endRef.x, endRef.y);
			angle = getAngle(startRef.x, startRef.y, cursorPt.x, cursorPt.y);

			if (angle >= angleRef)
			{
				//영역 안에 있을경우
				_isoCursor.x = _tiles[cursorTile.x][cursorTile.y].rc.left;
				_isoCursor.y = _tiles[cursorTile.x][cursorTile.y].rc.bottom;
			}
			else
			{
				//영역 밖일 경우
				_isoCursor.x = _tiles[cursorTile.x + 1][cursorTile.y].rc.right;
				_isoCursor.y = _tiles[cursorTile.x][cursorTile.y].rc.top;
			}
			break;
		case 3:
			startRef.x = _tiles[cursorTile.x][cursorTile.y].rc.right;
			startRef.y = _tiles[cursorTile.x][cursorTile.y].rc.bottom;
			endRef.x = _tiles[cursorTile.x - 1][cursorTile.y].rc.left;
			endRef.y = _tiles[cursorTile.x - 1][cursorTile.y].rc.top;
			angleRef = getAngle(startRef.x, startRef.y, endRef.x, endRef.y);
			angle = getAngle(startRef.x, startRef.y, cursorPt.x, cursorPt.y);

			if (angle >= angleRef)
			{
				//영역 안에 있을경우
				_isoCursor.x = _tiles[cursorTile.x - 1][cursorTile.y].rc.left;
				_isoCursor.y = _tiles[cursorTile.x][cursorTile.y].rc.bottom;
			}
			else
			{
				//영역 밖일 경우
				_isoCursor.x = _tiles[cursorTile.x][cursorTile.y].rc.right;
				_isoCursor.y = _tiles[cursorTile.x][cursorTile.y].rc.top;
			}
			break;
		}
	}
	//하단
	else
	{
		switch (tempIndex.x)
		{
		case 0:
			startRef.x = _tiles[cursorTile.x + 1][cursorTile.y].rc.right;
			startRef.y = _tiles[cursorTile.x + 1][cursorTile.y].rc.bottom;
			endRef.x = _tiles[cursorTile.x][cursorTile.y].rc.left;
			endRef.y = _tiles[cursorTile.x][cursorTile.y].rc.top;
			angleRef = getAngle(startRef.x, startRef.y, endRef.x, endRef.y);
			angle = getAngle(startRef.x, startRef.y, cursorPt.x, cursorPt.y);

			if (angle <= angleRef)
			{
				//영역 안에 있을경우
				_isoCursor.x = _tiles[cursorTile.x + 1][cursorTile.y].rc.right;
				_isoCursor.y = _tiles[cursorTile.x][cursorTile.y].rc.top;
			}
			else
			{
				//영역 밖일 경우
				_isoCursor.x = _tiles[cursorTile.x][cursorTile.y].rc.left;
				_isoCursor.y = _tiles[cursorTile.x][cursorTile.y].rc.bottom;
			}
			break;
		case 1:
			startRef.x = _tiles[cursorTile.x][cursorTile.y].rc.right;
			startRef.y = _tiles[cursorTile.x][cursorTile.y].rc.bottom;
			endRef.x = _tiles[cursorTile.x - 1][cursorTile.y].rc.left;
			endRef.y = _tiles[cursorTile.x - 1][cursorTile.y].rc.top;
			angleRef = getAngle(startRef.x, startRef.y, endRef.x, endRef.y);
			angle = getAngle(startRef.x, startRef.y, cursorPt.x, cursorPt.y);

			if (angle <= angleRef)
			{
				//영역 안에 있을경우
				_isoCursor.x = _tiles[cursorTile.x][cursorTile.y].rc.right;
				_isoCursor.y = _tiles[cursorTile.x][cursorTile.y].rc.top;
			}
			else
			{
				//영역 밖일 경우
				_isoCursor.x = _tiles[cursorTile.x - 1][cursorTile.y].rc.left;
				_isoCursor.y = _tiles[cursorTile.x][cursorTile.y].rc.bottom;
			}
			break;
		case 2:
			startRef.x = _tiles[cursorTile.x][cursorTile.y].rc.left;
			startRef.y = _tiles[cursorTile.x][cursorTile.y].rc.bottom;
			endRef.x = _tiles[cursorTile.x + 1][cursorTile.y].rc.right;
			endRef.y = _tiles[cursorTile.x + 1][cursorTile.y].rc.top;
			angleRef = getAngle(startRef.x, startRef.y, endRef.x, endRef.y);
			angle = getAngle(startRef.x, startRef.y, cursorPt.x, cursorPt.y);

			if (angle >= angleRef)
			{
				//영역 안에 있을경우
				_isoCursor.x = _tiles[cursorTile.x][cursorTile.y].rc.left;
				_isoCursor.y = _tiles[cursorTile.x][cursorTile.y].rc.top;
			}
			else
			{
				//영역 밖일 경우
				_isoCursor.x = _tiles[cursorTile.x + 1][cursorTile.y].rc.right;
				_isoCursor.y = _tiles[cursorTile.x + 1][cursorTile.y].rc.bottom;
			}
			break;
		case 3:
			startRef.x = _tiles[cursorTile.x - 1][cursorTile.y].rc.left;
			startRef.y = _tiles[cursorTile.x - 1][cursorTile.y].rc.bottom;
			endRef.x = _tiles[cursorTile.x][cursorTile.y].rc.right;
			endRef.y = _tiles[cursorTile.x][cursorTile.y].rc.top;
			angleRef = getAngle(startRef.x, startRef.y, endRef.x, endRef.y);
			angle = getAngle(startRef.x, startRef.y, cursorPt.x, cursorPt.y);

			if (angle >= angleRef)
			{
				//영역 안에 있을경우
				_isoCursor.x = _tiles[cursorTile.x - 1][cursorTile.y].rc.left;
				_isoCursor.y = _tiles[cursorTile.x][cursorTile.y].rc.top;
			}
			else
			{
				//영역 밖일 경우
				_isoCursor.x = _tiles[cursorTile.x][cursorTile.y].rc.right;
				_isoCursor.y = _tiles[cursorTile.x][cursorTile.y].rc.bottom;
			}
			break;
		}
	}
}

void sceneMaptool::clickIsoTile(void)
{
#if 0
	if (_ptMouse.x >= SIDEWINDOW_STARTX)
	{
		return;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) == false)
	{
		return;
	}

	int cx = _isoCursor.x / MAPTOOL_TILESIZE;
	int cy = _isoCursor.y / MAPTOOL_TILESIZE;


	for (int i = cx - 4; i < cx + 4; i++)
	{
		for (int j = cy - 2; j < cy + 3; j++)
		{
			//예외처리
			if (i == cx - 4 && j == cy - 2) continue;
			if (i == cx - 3 && j == cy - 2) continue;
			if (i == cx + 3 && j == cy - 2) continue;
			if (i == cx + 4 && j == cy - 2) continue;
			if (i == cx - 4 && j == cy + 2) continue;
			if (i == cx - 3 && j == cy + 2) continue;
			if (i == cx + 3 && j == cy + 2) continue;
			if (i == cx + 4 && j == cy + 2) continue;

			if (i < 0) continue;
			if (j < 0) continue;
			if (i >= TILEX) continue;
			if (j >= TILEY) continue;

			//왼쪽위
			if (i >= cx - 2 && i < cx && j >= cy - 2 && j < cy)
			{
				if ((_tiles[i][j].terrain & TERRAIN_HIGHTDIRT) != TERRAIN_HIGHTDIRT)
				{
					_tiles[i][j].terrain = TERRAIN_HIGHTDIRT;
					_tiles[i][j].terrain |= HIGHTDIRT_LF;
					_tiles[i][j].terrain |= HIGHTDIRT_UP;
					_tiles[i][j].terrainNum.x = i - (cx - 2);
					_tiles[i][j].terrainNum.y = j - (cy - 2);
					_isChangedTile[i][j] = true;
				}
			}
			//오른쪽 위
			else if (i >= cx && i < cx + 2 && j >= cy - 2 && j < cy)
			{
				if ((_tiles[i][j].terrain & TERRAIN_HIGHTDIRT) != TERRAIN_HIGHTDIRT)
				{
					_tiles[i][j].terrain = TERRAIN_HIGHTDIRT;
					_tiles[i][j].terrain |= HIGHTDIRT_RG;
					_tiles[i][j].terrain |= HIGHTDIRT_UP;
					_tiles[i][j].terrainNum.x = i - (cx);
					_tiles[i][j].terrainNum.y = j - (cy - 2);
					_isChangedTile[i][j] = true;
				}

			}
			//왼쪽
			else if (i >= cx - 4 && i < cx - 2 && j >= cy - 1 && j < cy + 2)
			{
				if ((_tiles[i][j].terrain & TERRAIN_HIGHTDIRT) != TERRAIN_HIGHTDIRT)
				{
					_tiles[i][j].terrain = TERRAIN_HIGHTDIRT;
					_tiles[i][j].terrain |= HIGHTDIRT_LF;
					_tiles[i][j].terrainNum.x = i - (cx - 4);
					_tiles[i][j].terrainNum.y = j - (cy - 1);
					_isChangedTile[i][j] = true;
				}
			}
			//오른쪽
			else if (i >= cx + 2 && i < cx + 4 && j >= cy - 1 && j < cy + 2)
			{
				if ((_tiles[i][j].terrain & TERRAIN_HIGHTDIRT) != TERRAIN_HIGHTDIRT)
				{
					_tiles[i][j].terrain = TERRAIN_HIGHTDIRT;
					_tiles[i][j].terrain |= HIGHTDIRT_RG;
					_tiles[i][j].terrainNum.x = i - (cx + 2);
					_tiles[i][j].terrainNum.y = j - (cy - 1);
					_isChangedTile[i][j] = true;
				}
			}
			//왼쪽아래
			else if (i >= cx - 2 && i < cx && j >= cy && j < cy + 3)
			{
				if ((_tiles[i][j].terrain & TERRAIN_HIGHTDIRT) != TERRAIN_HIGHTDIRT)
				{
					_tiles[i][j].terrain = TERRAIN_HIGHTDIRT;
					_tiles[i][j].terrain |= HIGHTDIRT_LF;
					_tiles[i][j].terrain |= HIGHTDIRT_DN;
					_tiles[i][j].terrainNum.x = i - (cx - 2);
					_tiles[i][j].terrainNum.y = j - (cy);
					_isChangedTile[i][j] = true;
				}
			}
			//오른쪽아래
			else if (i >= cx && i < cx + 2 && j >= cy && j < cy + 3)
			{
				if ((_tiles[i][j].terrain & TERRAIN_HIGHTDIRT) != TERRAIN_HIGHTDIRT)
				{
					_tiles[i][j].terrain = TERRAIN_HIGHTDIRT;
					_tiles[i][j].terrain |= HIGHTDIRT_RG;
					_tiles[i][j].terrain |= HIGHTDIRT_DN;
					_tiles[i][j].terrainNum.x = i - (cx);
					_tiles[i][j].terrainNum.y = j - (cy);
					_isChangedTile[i][j] = true;
				}
			}


		}
	}
#else
	int cx = _isoCursor.x / MAPTOOL_TILESIZE;
	int cy = _isoCursor.y / MAPTOOL_TILESIZE;

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_isClicked = true;
		_endDrag = false;
		_startIso = { cx, cy };
		_endIso = { cx, cy };
		_vDragInfo.clear();
	}
	else if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		_vDragInfo.clear();
	}
	else 
	{
		if (_isClicked)
		{
			_isClicked = false;
			_endDrag = true;
			_vDragInfo.clear();
		}
		else
		{
			//아무것도 아닐때
			return;
		}
	}

	_endIso = { cx, cy };


	int dx = (_endIso.x - _startIso.x);
	int dy = (_endIso.y - _startIso.y);

	int stx = _startIso.x - MAINCAMERA->getCameraX();
	int sty = _startIso.y - MAINCAMERA->getCameraY();
	int edx = _endIso.x - MAINCAMERA->getCameraX();
	int edy = _endIso.y - MAINCAMERA->getCameraY();

	int sta = 0;
	int stb = 0;

	int eda = (-dx + 2 * dy) / 4;
	int edb = ( dx + 2 * dy) / 4;

	if (eda >= 0 && edb >= 0)
	{
		for (int i = 0; i <= eda; i++)
		{
			for (int j = 0; j <= edb; j++)
			{
				tagDragInfo temp;
				temp.x = (j - i) * 2 + _startIso.x;
				temp.y = (j + i)     + _startIso.y;
				temp.a = i;
				temp.b = j;

				_vDragInfo.push_back(temp);
			}
		}
	}
	else if (eda >= 0 && edb < 0)
	{
		for (int i = 0; i <= eda; i++)
		{
			for (int j = 0; j >= edb; j--)
			{
				tagDragInfo temp;
				temp.x = (j - i) * 2 + _startIso.x;
				temp.y = (j + i)     + _startIso.y;
				temp.a = i;
				temp.b = j;

				_vDragInfo.push_back(temp);
			}
		}
	}
	else if (eda < 0 && edb >= 0)
	{
		for (int i = 0; i >= eda; i--)
		{
			for (int j = 0; j <= edb; j++)
			{
				tagDragInfo temp;
				temp.x = (j - i) * 2 + _startIso.x;
				temp.y = (j + i)     + _startIso.y;
				temp.a = i;
				temp.b = j;

				_vDragInfo.push_back(temp);
			}
		}
	}
	else if (eda < 0 && edb < 0)
	{
		for (int i = 0; i >= eda; i--)
		{
			for (int j = 0; j >= edb; j--)
			{
				tagDragInfo temp;
				temp.x = (j - i) * 2 + _startIso.x;
				temp.y = (j + i)     + _startIso.y;
				temp.a = i;
				temp.b = j;

				_vDragInfo.push_back(temp);
			}
		}
	}

	if (_endDrag == false)
	return;

	setHighDirt();


	_endDrag = false;
	_vDragInfo.clear();
#endif

}

void sceneMaptool::setHighDirt(void)
{
	int mina = 10000;
	int minb = 10000;
	int maxa = -10000;
	int maxb = -10000;

	//min, max (a, b) 를 계산한다.
	for (int i = 0; i < _vDragInfo.size(); i++)
	{
		if (_vDragInfo[i].a > maxa)		maxa = _vDragInfo[i].a;
		if (_vDragInfo[i].a < mina)		mina = _vDragInfo[i].a;

		if (_vDragInfo[i].b > maxb)		maxb = _vDragInfo[i].b;
		if (_vDragInfo[i].b < minb)		minb = _vDragInfo[i].b;
	}

	//가장자리를 먼저 채워주고
	for (int i = 0; i < _vDragInfo.size(); i++)
	{
		//왼쪽 끝
		if (_vDragInfo[i].a == maxa && _vDragInfo[i].b == minb)
		{
			setHighDirtEdge(_vDragInfo[i].x, _vDragInfo[i].y, TERRAINNUM_HIGHDIRT_LF);
			setHighDirtEdge(_vDragInfo[i].x, _vDragInfo[i].y, TERRAINNUM_HIGHDIRT_LF + TERRAINNUM_HIGHDIRT_UP);
			setHighDirtEdge(_vDragInfo[i].x, _vDragInfo[i].y, TERRAINNUM_HIGHDIRT_LF + TERRAINNUM_HIGHDIRT_DN);
		}
		//오른쪽 끝
		if (_vDragInfo[i].a == mina && _vDragInfo[i].b == maxb)
		{
			setHighDirtEdge(_vDragInfo[i].x, _vDragInfo[i].y, TERRAINNUM_HIGHDIRT_RG);
			setHighDirtEdge(_vDragInfo[i].x, _vDragInfo[i].y, TERRAINNUM_HIGHDIRT_RG + TERRAINNUM_HIGHDIRT_UP);
			setHighDirtEdge(_vDragInfo[i].x, _vDragInfo[i].y, TERRAINNUM_HIGHDIRT_RG + TERRAINNUM_HIGHDIRT_DN);
		}
		//왼쪽 위
		if (_vDragInfo[i].b == minb)
		{
			setHighDirtEdge(_vDragInfo[i].x, _vDragInfo[i].y, TERRAINNUM_HIGHDIRT_LF + TERRAINNUM_HIGHDIRT_UP);
		}
		//오른쪽 위
		if (_vDragInfo[i].a == mina)
		{
			setHighDirtEdge(_vDragInfo[i].x, _vDragInfo[i].y, TERRAINNUM_HIGHDIRT_RG + TERRAINNUM_HIGHDIRT_UP);
		}
		//왼쪽 밑
		if (_vDragInfo[i].a == maxa)
		{
			setHighDirtEdge(_vDragInfo[i].x, _vDragInfo[i].y, TERRAINNUM_HIGHDIRT_LF + TERRAINNUM_HIGHDIRT_DN);
		}
		//오른쪽 밑
		if (_vDragInfo[i].b == maxb)
		{
			setHighDirtEdge(_vDragInfo[i].x, _vDragInfo[i].y, TERRAINNUM_HIGHDIRT_RG + TERRAINNUM_HIGHDIRT_DN);
		}
	}

	//나머지를 언덕 idle 로 채워준다.
	for (int i = 0; i < _vDragInfo.size(); i++)
	{
		setHighDirtEdge(_vDragInfo[i].x, _vDragInfo[i].y, 0);
	}



	

}

void sceneMaptool::setHighDirtEdge(int cx, int cy, DWORD edge)
{
	for (int i = cx - 4; i < cx + 4; i++)
	{
		for (int j = cy - 2; j < cy + 3; j++)
		{
			//예외처리
			if (i == cx - 4 && j == cy - 2) continue;
			if (i == cx - 3 && j == cy - 2) continue;
			if (i == cx + 2 && j == cy - 2) continue;
			if (i == cx + 3 && j == cy - 2) continue;
			if (i == cx - 4 && j == cy + 2) continue;
			if (i == cx - 3 && j == cy + 2) continue;
			if (i == cx + 2 && j == cy + 2) continue;
			if (i == cx + 3 && j == cy + 2) continue;

			if (i < 0) continue;
			if (j < 0) continue;
			if (i >= TILEX) continue;
			if (j >= TILEY) continue;

			switch (edge)
			{
				//IDLE
			case 0:
				if ((_tiles[i][j].terrain & TERRAIN_HIGHTDIRT) != TERRAIN_HIGHTDIRT)
				{
					_tiles[i][j].terrain = TERRAIN_HIGHTDIRT;
					_tiles[i][j].terrainNum.x = 0;
					_tiles[i][j].terrainNum.y = 0;
					_isChangedTile[i][j] = true;
				}
				break;
				//왼쪽 끝
			case TERRAINNUM_HIGHDIRT_LF:
				if (i >= cx - 4 && i < cx - 2 && j >= cy - 1 && j < cy + 2)
				{
					if ((_tiles[i][j].terrain & TERRAIN_HIGHTDIRT) != TERRAIN_HIGHTDIRT)
					{
						_tiles[i][j].terrain = TERRAIN_HIGHTDIRT;
						_tiles[i][j].terrain |= HIGHTDIRT_LF;
						_tiles[i][j].terrainNum.x = i - (cx - 4);
						_tiles[i][j].terrainNum.y = j - (cy - 1);
						_isChangedTile[i][j] = true;
					}
				}
				break;
				//오른쪽 끝
			case TERRAINNUM_HIGHDIRT_RG:
				if (i >= cx + 2 && i < cx + 4 && j >= cy - 1 && j < cy + 2)
				{
					if ((_tiles[i][j].terrain & TERRAIN_HIGHTDIRT) != TERRAIN_HIGHTDIRT)
					{
						_tiles[i][j].terrain = TERRAIN_HIGHTDIRT;
						_tiles[i][j].terrain |= HIGHTDIRT_RG;
						_tiles[i][j].terrainNum.x = i - (cx + 2);
						_tiles[i][j].terrainNum.y = j - (cy - 1);
						_isChangedTile[i][j] = true;
					}
				}
				break;
				//왼쪽 위
			case (TERRAINNUM_HIGHDIRT_LF + TERRAINNUM_HIGHDIRT_UP):
				if (i >= cx - 2 && i < cx && j >= cy - 2 && j < cy)
				{
					if ((_tiles[i][j].terrain & TERRAIN_HIGHTDIRT) != TERRAIN_HIGHTDIRT)
					{
						_tiles[i][j].terrain = TERRAIN_HIGHTDIRT;
						_tiles[i][j].terrain |= HIGHTDIRT_LF;
						_tiles[i][j].terrain |= HIGHTDIRT_UP;
						_tiles[i][j].terrainNum.x = i - (cx - 2);
						_tiles[i][j].terrainNum.y = j - (cy - 2);
						_isChangedTile[i][j] = true;
					}
				}
				break;
				//오른쪽 위
			case (TERRAINNUM_HIGHDIRT_RG + TERRAINNUM_HIGHDIRT_UP):
				if (i >= cx && i < cx + 2 && j >= cy - 2 && j < cy)
				{
					if ((_tiles[i][j].terrain & TERRAIN_HIGHTDIRT) != TERRAIN_HIGHTDIRT)
					{
						_tiles[i][j].terrain = TERRAIN_HIGHTDIRT;
						_tiles[i][j].terrain |= HIGHTDIRT_RG;
						_tiles[i][j].terrain |= HIGHTDIRT_UP;
						_tiles[i][j].terrainNum.x = i - (cx);
						_tiles[i][j].terrainNum.y = j - (cy - 2);
						_isChangedTile[i][j] = true;
					}

				}
				break;
				//왼쪽 아래
			case (TERRAINNUM_HIGHDIRT_LF + TERRAINNUM_HIGHDIRT_DN):
				if (i >= cx - 2 && i < cx && j >= cy && j < cy + 3)
				{
					if ((_tiles[i][j].terrain & TERRAIN_HIGHTDIRT) != TERRAIN_HIGHTDIRT)
					{
						_tiles[i][j].terrain = TERRAIN_HIGHTDIRT;
						_tiles[i][j].terrain |= HIGHTDIRT_LF;
						_tiles[i][j].terrain |= HIGHTDIRT_DN;
						_tiles[i][j].terrainNum.x = i - (cx - 2);
						_tiles[i][j].terrainNum.y = j - (cy);
						_isChangedTile[i][j] = true;
					}
				}
				break;
				//오른쪽 아래
			case (TERRAINNUM_HIGHDIRT_RG + TERRAINNUM_HIGHDIRT_DN):
				if (i >= cx && i < cx + 2 && j >= cy && j < cy + 3)
				{
					if ((_tiles[i][j].terrain & TERRAIN_HIGHTDIRT) != TERRAIN_HIGHTDIRT)
					{
						_tiles[i][j].terrain = TERRAIN_HIGHTDIRT;
						_tiles[i][j].terrain |= HIGHTDIRT_RG;
						_tiles[i][j].terrain |= HIGHTDIRT_DN;
						_tiles[i][j].terrainNum.x = i - (cx);
						_tiles[i][j].terrainNum.y = j - (cy);
						_isChangedTile[i][j] = true;
					}
				}
				break;
			}
		}
	}
}


void sceneMaptool::updateTileImage(void)
{
	DWORD tick1 = GetTickCount();
	TCHAR strKey[128] = L"";

	int cameraX = MAINCAMERA->getCameraX();
	int cameraY = MAINCAMERA->getCameraY();

	int cameraIdX = cameraX / MAPTOOL_TILESIZE - 1;
	int cameraIdY = cameraY / MAPTOOL_TILESIZE - 1;

	for (int y = 0; y < MAPTOOL_TILEVIEWY + 2; y++)
	{
		for (int x = 0; x < MAPTOOL_TILEVIEWX + 2; x++)
		{
			int idX = cameraIdX + x;
			int idY = cameraIdY + y;

			if (idX < 0) continue;
			if (idY < 0) continue;
			if (idX >= TILEX) continue;
			if (idY >= TILEY) continue;

			if (_isChangedTile[idX][idY] == FALSE) continue;

			switch (_tiles[idX][idY].terrain)
			{
			case TERRAIN_DIRT:
				_stprintf(strKey, L"maptool-terrain-Dirt-00");// , _tiles[idX][idY].terrainNum);
				_imgTiles[idX][idY] = IMAGEMANAGER->findImage(strKey);
				break;
			//case TERRAIN_DIRTWALL:
			//	break;

			case TERRAIN_HIGHTDIRT:		_imgTiles[idX][idY] = IMAGEMANAGER->findImage(L"maptool-terrain-HighDirt");		break;
			case TERRAIN_HIGHTDIRT_LF:	_imgTiles[idX][idY] = IMAGEMANAGER->findImage(L"maptool-terrain-HighDirt-LF");	break;
			case TERRAIN_HIGHTDIRT_LU:	_imgTiles[idX][idY] = IMAGEMANAGER->findImage(L"maptool-terrain-HighDirt-LU");	break;
			case TERRAIN_HIGHTDIRT_LD:	_imgTiles[idX][idY] = IMAGEMANAGER->findImage(L"maptool-terrain-HighDirt-LD");	break;
			case TERRAIN_HIGHTDIRT_RG:	_imgTiles[idX][idY] = IMAGEMANAGER->findImage(L"maptool-terrain-HighDirt-RG");	break;
			case TERRAIN_HIGHTDIRT_RU:	_imgTiles[idX][idY] = IMAGEMANAGER->findImage(L"maptool-terrain-HighDirt-RU");	break;
			case TERRAIN_HIGHTDIRT_RD:	_imgTiles[idX][idY] = IMAGEMANAGER->findImage(L"maptool-terrain-HighDirt-RD");	break;
			
			case TERRAIN_WATER:
				break;
			}

			_isChangedTile[idX][idY] = false;
		}
	}

	DWORD tick2 = GetTickCount();
	DWORD tick = tick2 - tick1;

	printf("");

}

void sceneMaptool::setTileImageAll(void)
{
	for (int y = 0; y < TILEY; y++)
	{
		for (int x = 0; x < TILEX; x++)
		{
			TCHAR strKey[128] = L"";
			_stprintf(strKey, L"maptool-terrain-Dirt-00");// , _tiles[x][y].terrainNum);
			_imgTiles[x][y] = IMAGEMANAGER->findImage(strKey);
		}
	}
}

void sceneMaptool::saveData(const TCHAR* fileName)
{
	HANDLE file;
	DWORD write;

	file = CreateFile(fileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL);

	CloseHandle(file);
}

void sceneMaptool::loadData(const TCHAR* fileName)
{
	HANDLE file;
	DWORD read;

	file = CreateFile(fileName, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);


	CloseHandle(file);
}

void sceneMaptool::saveFile(void)
{
	OPENFILENAME ofn;
	TCHAR filePathSize[1028] = L"";

	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = filePathSize;
	ofn.nMaxFile = sizeof(filePathSize);
	ofn.nFilterIndex = true;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = NULL;
	ofn.lpstrInitialDir = L"./MapData";
	ofn.lpstrFilter = (L"map만볼꺼얌(*.map)\0*.map;");
	ofn.Flags = OFN_NOCHANGEDIR | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (GetSaveFileName(&ofn) == FALSE) return;

	TCHAR fileName[1028];
	_tcsncpy_s(fileName, _tcslen(ofn.lpstrFile) + 1, ofn.lpstrFile, _tcslen(ofn.lpstrFile));

	saveData(fileName);
}

void sceneMaptool::loadFile(void)
{
	OPENFILENAME ofn;
	TCHAR filePathSize[1028] = L"";
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = filePathSize;
	ofn.nMaxFile = sizeof(filePathSize);
	ofn.nFilterIndex = true;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = NULL;
	ofn.lpstrInitialDir = L"./MapData";
	ofn.lpstrFilter = (L"map만볼꺼얌(*.map)\0*.map;");
	ofn.Flags = OFN_NOCHANGEDIR | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (GetOpenFileName(&ofn) == FALSE) return;

	TCHAR fileName[1028];
	_tcsncpy_s(fileName, _tcslen(ofn.lpstrFile) + 1, ofn.lpstrFile, _tcslen(ofn.lpstrFile));

	loadData(fileName);
}

void sceneMaptool::renderTiles(void)
{
	DWORD tick1 = GetTickCount();

	int cameraX = MAINCAMERA->getCameraX();
	int cameraY = MAINCAMERA->getCameraY();

	int cameraIdX = cameraX / MAPTOOL_TILESIZE - 1;
	int cameraIdY = cameraY / MAPTOOL_TILESIZE - 1;

	for (int y = 0; y < MAPTOOL_TILEVIEWY + 2; y++)
	{
		for (int x = 0; x < MAPTOOL_TILEVIEWX + 2; x++)
		{
			int idX = cameraIdX + x;
			int idY = cameraIdY + y;

			if (idX < 0) continue;
			if (idY < 0) continue;
			if (idX >= TILEX) continue;
			if (idY >= TILEY) continue;
			if (_imgTiles[idX][idY] == NULL) continue;

			if (_tiles[idX][idY].terrain == TERRAIN_DIRT)
			{
				_imgTiles[idX][idY]->render(getMemDC(), idX*MAPTOOL_TILESIZE - cameraX, idY*MAPTOOL_TILESIZE - cameraY);
			}
			else
			{
				_imgTiles[idX][idY]->frameRender(getMemDC(), idX*MAPTOOL_TILESIZE - cameraX, idY*MAPTOOL_TILESIZE - cameraY, _tiles[idX][idY].terrainNum.x, _tiles[idX][idY].terrainNum.y);
			}

		}
	}


	DWORD tick2 = GetTickCount();
	DWORD tick = tick2 - tick1;

	printf("");

}

void sceneMaptool::renderDragingIsoTiles(void)
{
	if (_isClicked == true && _endDrag == false)
	{
		HPEN oldPen = (HPEN)SelectObject(getMemDC(), _gPen[PENVERSION_BLUE]);

		for (int i = 0; i < _vDragInfo.size(); i++)
		{
			POINT temp;
			temp.x = (_vDragInfo[i].x/* + _startIso.x*/) * MAPTOOL_TILESIZE - MAINCAMERA->getCameraX();
			temp.y = (_vDragInfo[i].y/* + _startIso.y*/) * MAPTOOL_TILESIZE - MAINCAMERA->getCameraY();

			LineMake(getMemDC(), temp.x - ISOTILE_HALF_WIDTH, temp.y, temp.x, temp.y - ISOTILE_HALF_HEIGHT);
			LineMake(getMemDC(), temp.x - ISOTILE_HALF_WIDTH, temp.y, temp.x, temp.y + ISOTILE_HALF_HEIGHT);
			LineMake(getMemDC(), temp.x + ISOTILE_HALF_WIDTH, temp.y, temp.x, temp.y - ISOTILE_HALF_HEIGHT);
			LineMake(getMemDC(), temp.x + ISOTILE_HALF_WIDTH, temp.y, temp.x, temp.y + ISOTILE_HALF_HEIGHT);
		}
		SelectObject(getMemDC(), oldPen);
	}
}

void sceneMaptool::renderCurIsoTile(void)
{
	HPEN oldPen = (HPEN)SelectObject(getMemDC(), _gPen[PENVERSION_MOUSEDRAG]);
	_isoCursor.x -= MAINCAMERA->getCameraX();
	_isoCursor.y -= MAINCAMERA->getCameraY();
	LineMake(getMemDC(), _isoCursor.x - ISOTILE_HALF_WIDTH, _isoCursor.y, _isoCursor.x, _isoCursor.y - ISOTILE_HALF_HEIGHT);
	LineMake(getMemDC(), _isoCursor.x - ISOTILE_HALF_WIDTH, _isoCursor.y, _isoCursor.x, _isoCursor.y + ISOTILE_HALF_HEIGHT);
	LineMake(getMemDC(), _isoCursor.x + ISOTILE_HALF_WIDTH, _isoCursor.y, _isoCursor.x, _isoCursor.y - ISOTILE_HALF_HEIGHT);
	LineMake(getMemDC(), _isoCursor.x + ISOTILE_HALF_WIDTH, _isoCursor.y, _isoCursor.x, _isoCursor.y + ISOTILE_HALF_HEIGHT);
	SelectObject(getMemDC(), oldPen);
	DeleteObject(oldPen);
}



void sceneMaptool::renderSideWindow(void)
{
	RectangleMake(getMemDC(), SIDEWINDOW_STARTX, 0, WINSIZEX - SIDEWINDOW_STARTX, WINSIZEY);

	renderMiniMap();

	for (int i = 0; i < SAMPLETERRAIN_MAX; i++)
	{
		RectangleMake(getMemDC(), _rcSelectTerrain[i]);
	}

	for (int i = 0; i < BTNCTRL_MAX; i++)
	{
		_btnCtrl[i]->render();
	}
}


void sceneMaptool::renderMiniMap(void)
{
	HDC hDCtemp = _imgMiniMap->getMemDC();
	PatBlt(hDCtemp, 0, 0, TILEX, TILEY, BLACKNESS);

	HPEN oldPen = (HPEN)SelectObject(hDCtemp, _gPen[PENVERSION_MINIMAP]);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDCtemp, _gBrush[BRUSHVERSION_BLACK]);
	RectangleMake(hDCtemp, _rcMiniMapCamera);
	SelectObject(hDCtemp, oldPen);
	SelectObject(hDCtemp, oldBrush);

	BitBlt(getMemDC(), SIDEWINDOW_STARTX + 16, 16, TILEX, TILEY, hDCtemp, 0, 0, SRCCOPY);

	//GdiTransparentBlt(getMemDC(),		//복사될 DC영역
	//	SIDEWINDOW_STARTX + 16,
	//	0 + 16,
	//	TILEX, TILEY,												//복사될 가로 세로 크기

	//	hDCtemp,			//복사할 DC
	//	0, 0,				//복사할 좌표
	//	TILEX, TILEY,		//복사할 가로 세로 크기
	//	RGB(0, 0, 0));			//제외할 칼라

}


//callback Function
void sceneMaptool::cbButtonSave(void * obj)
{
	sceneMaptool* sm = (sceneMaptool*)obj;
	sm->saveFile();
}

void sceneMaptool::cbButtonLoad(void * obj)
{
	sceneMaptool* sm = (sceneMaptool*)obj;
	sm->loadFile();
	sm->updateTileImage();
}

void sceneMaptool::cbButtonExit(void* obj)
{
	sceneMaptool* sm = (sceneMaptool*)obj;
	sm->setChangeScene(true, L"선택씬");
}

