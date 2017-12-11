#include "stdafx.h"
#include "sceneMaptool.h"


sceneMaptool::sceneMaptool()
{
	for (int i = 0; i < BTNCTRL_MAX; i++)
	{
		_btnCtrl[i] = NULL;
	}
	ZeroMemory(&_tiles, sizeof(tagTile) * TILEX * TILEY);
	ZeroMemory(&_imgTiles, sizeof(INT32) * TILEX * TILEY);
	ZeroMemory(&_isChangedTile, sizeof(BOOL) * TILEX * TILEY);
	
	_isoCursor = { 0, 0 };
}


sceneMaptool::~sceneMaptool()
{

}

HRESULT sceneMaptool::init(void)
{
	initButtons();

	initTiles();

	setTileImageAll();

	initIsoTiles();

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


	//updateTileImage();
	for (int i = 0; i < BTNCTRL_MAX; i++)
	{
		_btnCtrl[i]->update();
	}

	clickIsoTile();


}

void sceneMaptool::render(void)
{
	renderTiles();

	HPEN oldPen = (HPEN)SelectObject(getMemDC(), _gPen[PENVERSION_BLUE]);
#if 0
	for (int i = 0; i < ISOTILEY; i++)
	{
		for (int j = 0; j < ISOTILEX; j++)
		{
			if (_isoTile[j][i].clicked == FALSE) continue;

			RECT rcIso = _isoTile[j][i].rc;
			POINT ptIso = _isoTile[j][i].pt;
			ptIso.x		 -= MAINCAMERA->getCameraX();
			ptIso.y		 -= MAINCAMERA->getCameraY();
			rcIso.left   -= MAINCAMERA->getCameraX();
			rcIso.right  -= MAINCAMERA->getCameraX();
			rcIso.top    -= MAINCAMERA->getCameraY();
			rcIso.bottom -= MAINCAMERA->getCameraY();

			//Rectangle(getMemDC(), _isoTile[j][i].rc.left, _isoTile[j][i].rc.top, _isoTile[j][i].rc.right, _isoTile[j][i].rc.bottom);
			LineMake(getMemDC(), rcIso.left,  ptIso.y, ptIso.x, rcIso.top);
			LineMake(getMemDC(), rcIso.left,  ptIso.y, ptIso.x, rcIso.bottom);
			LineMake(getMemDC(), rcIso.right, ptIso.y, ptIso.x, rcIso.top);
			LineMake(getMemDC(), rcIso.right, ptIso.y, ptIso.x, rcIso.bottom);
		}
	}
#endif
	_isoCursor.x -= MAINCAMERA->getCameraX();
	_isoCursor.y -= MAINCAMERA->getCameraY();
	LineMake(getMemDC(), _isoCursor.x - ISOTILE_HALF_WIDTH, _isoCursor.y, _isoCursor.x, _isoCursor.y - ISOTILE_HALF_HEIGHT);
	LineMake(getMemDC(), _isoCursor.x - ISOTILE_HALF_WIDTH, _isoCursor.y, _isoCursor.x, _isoCursor.y + ISOTILE_HALF_HEIGHT);
	LineMake(getMemDC(), _isoCursor.x + ISOTILE_HALF_WIDTH, _isoCursor.y, _isoCursor.x, _isoCursor.y - ISOTILE_HALF_HEIGHT);
	LineMake(getMemDC(), _isoCursor.x + ISOTILE_HALF_WIDTH, _isoCursor.y, _isoCursor.x, _isoCursor.y + ISOTILE_HALF_HEIGHT);
	SelectObject(getMemDC(), oldPen);
	DeleteObject(oldPen);


	for (int i = 0; i < BTNCTRL_MAX; i++)
	{
		_btnCtrl[i]->render();
	}

}

void sceneMaptool::getChar(WPARAM wParam)
{

}

void sceneMaptool::initButtons(void)
{
	_btnCtrl[BTNCTRL_SAVE] = new button;
	_btnCtrl[BTNCTRL_SAVE]->init(L"버튼1", L"SAVE", 200, 200, { 0,0 }, { 0,1 }, cbButtonSave, this);
	_btnCtrl[BTNCTRL_LOAD] = new button;
	_btnCtrl[BTNCTRL_LOAD]->init(L"버튼1", L"LOAD", 200, 300, { 0,0 }, { 0,1 }, cbButtonLoad, this);
}

void sceneMaptool::initTiles(void)
{
	for (int y = 0; y < TILEY; y++)
	{
		for (int x = 0; x < TILEX; x++)
		{
			_tiles[x][y].terrain = TERRAIN_DIRT;
			_tiles[x][y].terrainNum = 0;
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

void sceneMaptool::clickIsoTile(void)
{
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
				_isoCursor.y = _tiles[cursorTile.x][cursorTile.y].rc.top;
			}
			break;
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
				_stprintf(strKey, L"maptool-terrain-Dirt-%02d", _tiles[idX][idY].terrainNum);
				_imgTiles[idX][idY] = IMAGEMANAGER->findImage(strKey);
				break;
			case TERRAIN_MUD:
				break;
			case TERRAIN_DIRTWALL:
				break;
			case TERRAIN_WATER:
				break;
			case TERRAIN_GRASS:
				break;
			case TERRAIN_GRASSWALL:
				break;
			case TERRAIN_STRUCTURE:
				break;
			case TERRAIN_STRUCTUREWALL:
				break;
			case TERRAIN_ASPHALT:
				break;
			case TERRAIN_ROCKYGROUND:
				break;
			}
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
			_stprintf(strKey, L"maptool-terrain-Dirt-%02d", _tiles[x][y].terrainNum);
			_imgTiles[x][y] = IMAGEMANAGER->findImage(strKey);
		}
	}
}

void sceneMaptool::saveData(void)
{
	HANDLE file;
	DWORD write;

	TCHAR strFile[100];
	_stprintf(strFile, L"MapData/test.map");

	file = CreateFile(strFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL);

	CloseHandle(file);
}

void sceneMaptool::loadData(void)
{
	HANDLE file;
	DWORD read;

	TCHAR strFile[100];
	_stprintf(strFile, L"MapData/test.map");

	file = CreateFile(strFile, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);


	CloseHandle(file);
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

			_imgTiles[idX][idY]->render(getMemDC(), idX*MAPTOOL_TILESIZE - cameraX, idY*MAPTOOL_TILESIZE - cameraY);
		}
	}

	DWORD tick2 = GetTickCount();
	DWORD tick = tick2 - tick1;

	printf("");

}

//callback Function
void sceneMaptool::cbButtonSave(void * obj)
{
	sceneMaptool* sm = (sceneMaptool*)obj;
	sm->saveData();
}

void sceneMaptool::cbButtonLoad(void * obj)
{
	sceneMaptool* sm = (sceneMaptool*)obj;
	sm->loadData();
	sm->setTileImageAll();
}

