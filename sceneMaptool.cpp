#include "stdafx.h"
#include "sceneMaptool.h"

#include <assert.h>


sceneMaptool::sceneMaptool()
	: _imgMiniMap(NULL), _editboxNrAmount(NULL), _imgObject(NULL)
{
	for (int i = 0; i < BTNCTRL_MAX; i++)
	{
		_btnCtrl[i] = NULL;
	}
	ZeroMemory(&_tiles, sizeof(tagTile) * TILEX * TILEY);
	ZeroMemory(&_imgTiles, sizeof(INT32) * TILEX * TILEY);
	ZeroMemory(&_isChangedTile, sizeof(BOOL) * TILEX * TILEY);
	
	_cursorPt = { 0, 0 };
	_cursorTile = { 0, 0 };
	_isoCursor = { 0, 0 };


	_startIso = _endIso = { 0, 0 };

	_isClicked = false;
	_endDrag = false;

	ZeroMemory(&_imgSelectTerrain, sizeof(SAMPLETERRAIN_MAX));
	ZeroMemory(&_imgSelectObject, sizeof(SAMPLEOBJECT_MAX));
}


sceneMaptool::~sceneMaptool()
{

}

HRESULT sceneMaptool::init(void)
{
	initButtons();


	initTiles();

	//setTileImageAll();

	initMiniMap();
	initSampleTerrainObject();



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
	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
	{
		_curTerrain = SAMPLETERRAIN_NONE;
		_curObject = SAMPLEOBJECT_NONE;
	}

	//카메라 이동, 미니맵 클릭 이동
	updateCamera();

	//맵에서 마우스가 위치한 실제 위치값 계산
	calcMouseRealPosition();

	//터레인 선택
	selectTerrainObject();

	if (_curTerrain != SAMPLETERRAIN_NONE)
	{
		//마우스가 위치한 ISO 계산
		calcIsoTile();

		//마우스가 클릭했을 때
		//Dirt 는 그냥 클릭하는대로 입력하도록 하고
		//HighDirt, Water는 드래그로 입력하도록 한다.
		switch (_curTerrain)
		{
		case SAMPLETERRAIN_DIRT:
			clickIsoTile();
			break;
		case SAMPLETERRAIN_HIGTDIRT:
			dragIsoTile();
			break;
		case SAMPLETERRAIN_WATER:
			dragIsoTile();
			break;
		}
	}

	if (_curObject != SAMPLEOBJECT_NONE)
	{
		//오브젝트 위치를 마우스 위치로 이동시키고, 위치시킬 수 있는지 여부 판단
		if (calcObjectTile() == true)
		{
			//마우스 클릭했을때
			clickObjectTile();
		}
	}


	//타일 이미지 갱신
	updateTileImage();
	updateMiniMap();

	_editboxNrAmount->update();

	for (int i = 0; i < BTNCTRL_MAX; i++)
	{
		_btnCtrl[i]->update();
	}
}

void sceneMaptool::render(void)
{
	renderTiles();

	if (_curTerrain != SAMPLETERRAIN_NONE)
	{
		//드래그 상태일 때 파란색으로 영역 표시해주기
		renderDragingIsoTiles();

		//현재 커서의 ISO 보여주기
		renderCurIsoTile();
	}

	renderObject();

	renderSideWindow();
}

void sceneMaptool::getChar(WPARAM wParam)
{
	_editboxNrAmount->getChar(wParam);
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

	ZeroMemory(&_colorMiniMap, sizeof(COLORREF)*TILEX*TILEY);
}

void sceneMaptool::initSampleTerrainObject(void)
{
	_curTerrain = SAMPLETERRAIN_DIRT;

	_rcSelectTerrain[SAMPLETERRAIN_DIRT]     = RectMake(SIDEWINDOW_STARTX + 10, _rcMiniMap.bottom + 30, MAPTOOL_TILESIZE, MAPTOOL_TILESIZE);
	_rcSelectTerrain[SAMPLETERRAIN_HIGTDIRT] = RectMake(_rcSelectTerrain[SAMPLETERRAIN_DIRT].right + 5, _rcMiniMap.bottom + 30, MAPTOOL_TILESIZE, MAPTOOL_TILESIZE);
	_rcSelectTerrain[SAMPLETERRAIN_WATER]    = RectMake(_rcSelectTerrain[SAMPLETERRAIN_HIGTDIRT].right + 5, _rcMiniMap.bottom + 30, MAPTOOL_TILESIZE, MAPTOOL_TILESIZE);

	_imgSelectTerrain[SAMPLETERRAIN_DIRT]     = IMAGEMANAGER->findImage(L"maptool-terrain-Dirt");
	_imgSelectTerrain[SAMPLETERRAIN_HIGTDIRT] = IMAGEMANAGER->findImage(L"maptool-terrain-HighDirt");
	_imgSelectTerrain[SAMPLETERRAIN_WATER]    = IMAGEMANAGER->findImage(L"maptool-terrain-Water-00");

	

	_curObject = SAMPLEOBJECT_NONE;
	_rcSelectObject[SAMPLEOBJECT_MINERAL] = RectMake(SIDEWINDOW_STARTX + 10, _rcSelectTerrain[SAMPLETERRAIN_DIRT].bottom + 30, MAPTOOL_TILESIZE, MAPTOOL_TILESIZE);
	_rcSelectObject[SAMPLEOBJECT_GAS]     = RectMake(_rcSelectObject[SAMPLEOBJECT_MINERAL].right + 5, _rcSelectTerrain[SAMPLETERRAIN_DIRT].bottom + 30, MAPTOOL_TILESIZE, MAPTOOL_TILESIZE);
	_rcSelectObject[SAMPLEOBJECT_PLAYER1] = RectMake(_rcSelectObject[SAMPLEOBJECT_GAS].right + 5, _rcSelectTerrain[SAMPLETERRAIN_DIRT].bottom + 30, MAPTOOL_TILESIZE, MAPTOOL_TILESIZE);
	_rcSelectObject[SAMPLEOBJECT_PLAYER2] = RectMake(_rcSelectObject[SAMPLEOBJECT_PLAYER1].right + 5, _rcSelectTerrain[SAMPLETERRAIN_DIRT].bottom + 30, MAPTOOL_TILESIZE, MAPTOOL_TILESIZE);
	_rcSelectObject[SAMPLEOBJECT_ERASER]  = RectMake(_rcSelectObject[SAMPLEOBJECT_PLAYER2].left, _rcSelectObject[SAMPLEOBJECT_PLAYER2].bottom + 10, MAPTOOL_TILESIZE, MAPTOOL_TILESIZE);

	_imgSelectObject[SAMPLEOBJECT_MINERAL] = IMAGEMANAGER->findImage(L"maptool-icon-Mineral");
	_imgSelectObject[SAMPLEOBJECT_GAS]     = IMAGEMANAGER->findImage(L"maptool-icon-Gas");
	_imgSelectObject[SAMPLEOBJECT_PLAYER1] = IMAGEMANAGER->findImage(L"maptool-icon-LocationP1");
	_imgSelectObject[SAMPLEOBJECT_PLAYER2] = IMAGEMANAGER->findImage(L"maptool-icon-LocationP2");
	_imgSelectObject[SAMPLEOBJECT_ERASER]  = IMAGEMANAGER->findImage(L"maptool-icon-iconEraser");


	_editboxNrAmount = new editbox;
	_editboxNrAmount->init();
	_editboxNrAmount->setOnlyNum(true);
	_editboxNrAmount->setMinMax(0, 50000);
	_editboxNrAmount->setStrNum(1500);
	_editboxNrAmount->setRect(RectMake(SIDEWINDOW_STARTX + 10, _rcSelectObject[SAMPLEOBJECT_MINERAL].bottom + 10, 100, 30));

	_imgObject = NULL;

	ZeroMemory(&_objState, sizeof(OBJSTATE) * OBJECTSIZE_MAX_X * OBJECTSIZE_MAX_Y);

	_isLocatedP1 = false;
	_isLocatedP2 = false;
}



void sceneMaptool::initTiles(void)
{
	for (int y = 0; y < TILEY; y++)
	{
		for (int x = 0; x < TILEX; x++)
		{
			_tiles[x][y].terrain = TERRAIN_DIRT;
			_tiles[x][y].terrainNum.x = RND->getInt(24);
			_tiles[x][y].terrainNum.y = RND->getInt(20);
			_tiles[x][y].obj = 0;
			_tiles[x][y].nrAmount = 0;
			_tiles[x][y].attribute = 0;
			_tiles[x][y].rc = RectMake(x * MAPTOOL_TILESIZE, y * MAPTOOL_TILESIZE, MAPTOOL_TILESIZE, MAPTOOL_TILESIZE);
		}
	}
	memset(&_isChangedTile, 1, sizeof(BOOL) * TILEX * TILEY);
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

void sceneMaptool::calcMouseRealPosition(void)
{
	_cursorPt.x = _ptMouse.x + MAINCAMERA->getCameraX();
	_cursorPt.y = _ptMouse.y + MAINCAMERA->getCameraY();
	_cursorTile.x = (LONG)(_cursorPt.x / MAPTOOL_TILESIZE);
	_cursorTile.y = (LONG)(_cursorPt.y / MAPTOOL_TILESIZE);
}


void sceneMaptool::selectTerrainObject(void)
{
	for (int i = 0; i < SAMPLETERRAIN_MAX; i++)
	{
		if (PtInRect(&_rcSelectTerrain[i], _ptMouse))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_curTerrain = (SAMPLETERRAIN)i;
				_curObject = SAMPLEOBJECT_NONE;
				_imgObject = NULL;
				return;
			}
		}
	}

	for (int i = 0; i < SAMPLEOBJECT_MAX; i++)
	{
		if (PtInRect(&_rcSelectObject[i], _ptMouse))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_curTerrain = SAMPLETERRAIN_NONE;
				_curObject = (SAMPLEOBJECT)i;

				switch (_curObject)
				{
				case SAMPLEOBJECT_MINERAL:
					_imgObject = IMAGEMANAGER->findImage(L"NeutralResource-Mineral1");
					break;
				case SAMPLEOBJECT_GAS:
					_imgObject = IMAGEMANAGER->findImage(L"NeutralResource-Gas");
					break;
				case SAMPLEOBJECT_PLAYER1:
					_imgObject = IMAGEMANAGER->findImage(L"maptool-object-LocationP1");
					break;
				case SAMPLEOBJECT_PLAYER2:
					_imgObject = IMAGEMANAGER->findImage(L"maptool-object-LocationP2");
					break;
				case SAMPLEOBJECT_ERASER:
					//_imgObject = IMAGEMANAGER->findImage(L"maptool-icon-iconEraser");
					break;
				}

				return;
			}
		}
	}
}

void sceneMaptool::calcIsoTile(void)
{
	if (_ptMouse.x >= SIDEWINDOW_STARTX)
		return;


	// 가로 4칸, 세로 2칸 영역별로 나눠서 계산
	POINT tempIndex = { _cursorTile.x % 4, _cursorTile.y % 2 }; 

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
			startRef.x = _tiles[_cursorTile.x][_cursorTile.y].rc.left;
			startRef.y = _tiles[_cursorTile.x][_cursorTile.y].rc.bottom;
			endRef.x = _tiles[_cursorTile.x + 1][_cursorTile.y].rc.right;
			endRef.y = _tiles[_cursorTile.x + 1][_cursorTile.y].rc.top;
			angleRef = getAngle(startRef.x, startRef.y, endRef.x, endRef.y);
			angle = getAngle(startRef.x, startRef.y, _cursorPt.x, _cursorPt.y);

			if (angle <= angleRef)
			{
				//영역 안에 있을경우
				_isoCursor.x = _tiles[_cursorTile.x + 1][_cursorTile.y].rc.right;
				_isoCursor.y = _tiles[_cursorTile.x][_cursorTile.y].rc.bottom;
			}
			else
			{
				//영역 밖일 경우
				_isoCursor.x = _tiles[_cursorTile.x][_cursorTile.y].rc.left;
				_isoCursor.y = _tiles[_cursorTile.x][_cursorTile.y].rc.top;
			}

			break;
		case 1:
			startRef.x = _tiles[_cursorTile.x - 1][_cursorTile.y].rc.left;
			startRef.y = _tiles[_cursorTile.x - 1][_cursorTile.y].rc.bottom;
			endRef.x = _tiles[_cursorTile.x][_cursorTile.y].rc.right;
			endRef.y = _tiles[_cursorTile.x][_cursorTile.y].rc.top;
			angleRef = getAngle(startRef.x, startRef.y, endRef.x, endRef.y);
			angle = getAngle(startRef.x, startRef.y, _cursorPt.x, _cursorPt.y);

			if (angle <= angleRef)
			{
				//영역 안에 있을경우
				_isoCursor.x = _tiles[_cursorTile.x][_cursorTile.y].rc.right;
				_isoCursor.y = _tiles[_cursorTile.x][_cursorTile.y].rc.bottom;
			}
			else
			{
				//영역 밖일 경우
				_isoCursor.x = _tiles[_cursorTile.x - 1][_cursorTile.y].rc.left;
				_isoCursor.y = _tiles[_cursorTile.x][_cursorTile.y].rc.top;
			}
			break;
		case 2:
			startRef.x = _tiles[_cursorTile.x + 1][_cursorTile.y].rc.right;
			startRef.y = _tiles[_cursorTile.x + 1][_cursorTile.y].rc.bottom;
			endRef.x = _tiles[_cursorTile.x][_cursorTile.y].rc.left;
			endRef.y = _tiles[_cursorTile.x][_cursorTile.y].rc.top;
			angleRef = getAngle(startRef.x, startRef.y, endRef.x, endRef.y);
			angle = getAngle(startRef.x, startRef.y, _cursorPt.x, _cursorPt.y);

			if (angle >= angleRef)
			{
				//영역 안에 있을경우
				_isoCursor.x = _tiles[_cursorTile.x][_cursorTile.y].rc.left;
				_isoCursor.y = _tiles[_cursorTile.x][_cursorTile.y].rc.bottom;
			}
			else
			{
				//영역 밖일 경우
				_isoCursor.x = _tiles[_cursorTile.x + 1][_cursorTile.y].rc.right;
				_isoCursor.y = _tiles[_cursorTile.x][_cursorTile.y].rc.top;
			}
			break;
		case 3:
			startRef.x = _tiles[_cursorTile.x][_cursorTile.y].rc.right;
			startRef.y = _tiles[_cursorTile.x][_cursorTile.y].rc.bottom;
			endRef.x = _tiles[_cursorTile.x - 1][_cursorTile.y].rc.left;
			endRef.y = _tiles[_cursorTile.x - 1][_cursorTile.y].rc.top;
			angleRef = getAngle(startRef.x, startRef.y, endRef.x, endRef.y);
			angle = getAngle(startRef.x, startRef.y, _cursorPt.x, _cursorPt.y);

			if (angle >= angleRef)
			{
				//영역 안에 있을경우
				_isoCursor.x = _tiles[_cursorTile.x - 1][_cursorTile.y].rc.left;
				_isoCursor.y = _tiles[_cursorTile.x][_cursorTile.y].rc.bottom;
			}
			else
			{
				//영역 밖일 경우
				_isoCursor.x = _tiles[_cursorTile.x][_cursorTile.y].rc.right;
				_isoCursor.y = _tiles[_cursorTile.x][_cursorTile.y].rc.top;
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
			startRef.x = _tiles[_cursorTile.x + 1][_cursorTile.y].rc.right;
			startRef.y = _tiles[_cursorTile.x + 1][_cursorTile.y].rc.bottom;
			endRef.x = _tiles[_cursorTile.x][_cursorTile.y].rc.left;
			endRef.y = _tiles[_cursorTile.x][_cursorTile.y].rc.top;
			angleRef = getAngle(startRef.x, startRef.y, endRef.x, endRef.y);
			angle = getAngle(startRef.x, startRef.y, _cursorPt.x, _cursorPt.y);

			if (angle <= angleRef)
			{
				//영역 안에 있을경우
				_isoCursor.x = _tiles[_cursorTile.x + 1][_cursorTile.y].rc.right;
				_isoCursor.y = _tiles[_cursorTile.x][_cursorTile.y].rc.top;
			}
			else
			{
				//영역 밖일 경우
				_isoCursor.x = _tiles[_cursorTile.x][_cursorTile.y].rc.left;
				_isoCursor.y = _tiles[_cursorTile.x][_cursorTile.y].rc.bottom;
			}
			break;
		case 1:
			startRef.x = _tiles[_cursorTile.x][_cursorTile.y].rc.right;
			startRef.y = _tiles[_cursorTile.x][_cursorTile.y].rc.bottom;
			endRef.x = _tiles[_cursorTile.x - 1][_cursorTile.y].rc.left;
			endRef.y = _tiles[_cursorTile.x - 1][_cursorTile.y].rc.top;
			angleRef = getAngle(startRef.x, startRef.y, endRef.x, endRef.y);
			angle = getAngle(startRef.x, startRef.y, _cursorPt.x, _cursorPt.y);

			if (angle <= angleRef)
			{
				//영역 안에 있을경우
				_isoCursor.x = _tiles[_cursorTile.x][_cursorTile.y].rc.right;
				_isoCursor.y = _tiles[_cursorTile.x][_cursorTile.y].rc.top;
			}
			else
			{
				//영역 밖일 경우
				_isoCursor.x = _tiles[_cursorTile.x - 1][_cursorTile.y].rc.left;
				_isoCursor.y = _tiles[_cursorTile.x][_cursorTile.y].rc.bottom;
			}
			break;
		case 2:
			startRef.x = _tiles[_cursorTile.x][_cursorTile.y].rc.left;
			startRef.y = _tiles[_cursorTile.x][_cursorTile.y].rc.bottom;
			endRef.x = _tiles[_cursorTile.x + 1][_cursorTile.y].rc.right;
			endRef.y = _tiles[_cursorTile.x + 1][_cursorTile.y].rc.top;
			angleRef = getAngle(startRef.x, startRef.y, endRef.x, endRef.y);
			angle = getAngle(startRef.x, startRef.y, _cursorPt.x, _cursorPt.y);

			if (angle >= angleRef)
			{
				//영역 안에 있을경우
				_isoCursor.x = _tiles[_cursorTile.x][_cursorTile.y].rc.left;
				_isoCursor.y = _tiles[_cursorTile.x][_cursorTile.y].rc.top;
			}
			else
			{
				//영역 밖일 경우
				_isoCursor.x = _tiles[_cursorTile.x + 1][_cursorTile.y].rc.right;
				_isoCursor.y = _tiles[_cursorTile.x + 1][_cursorTile.y].rc.bottom;
			}
			break;
		case 3:
			startRef.x = _tiles[_cursorTile.x - 1][_cursorTile.y].rc.left;
			startRef.y = _tiles[_cursorTile.x - 1][_cursorTile.y].rc.bottom;
			endRef.x = _tiles[_cursorTile.x][_cursorTile.y].rc.right;
			endRef.y = _tiles[_cursorTile.x][_cursorTile.y].rc.top;
			angleRef = getAngle(startRef.x, startRef.y, endRef.x, endRef.y);
			angle = getAngle(startRef.x, startRef.y, _cursorPt.x, _cursorPt.y);

			if (angle >= angleRef)
			{
				//영역 안에 있을경우
				_isoCursor.x = _tiles[_cursorTile.x - 1][_cursorTile.y].rc.left;
				_isoCursor.y = _tiles[_cursorTile.x][_cursorTile.y].rc.top;
			}
			else
			{
				//영역 밖일 경우
				_isoCursor.x = _tiles[_cursorTile.x][_cursorTile.y].rc.right;
				_isoCursor.y = _tiles[_cursorTile.x][_cursorTile.y].rc.bottom;
			}
			break;
		}
	}
}

void sceneMaptool::clickIsoTile(void)
{
	if (_ptMouse.x >= SIDEWINDOW_STARTX)
		return;

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) == false)
		return;

	int cx = _isoCursor.x / MAPTOOL_TILESIZE;
	int cy = _isoCursor.y / MAPTOOL_TILESIZE;

	setDirt(cx, cy);
}

void sceneMaptool::dragIsoTile(void)
{
	if (_ptMouse.x >= SIDEWINDOW_STARTX)
		return;

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

	switch (_curTerrain)
	{
	case SAMPLETERRAIN_HIGTDIRT:
		setHighDirt();
		break;
	case SAMPLETERRAIN_WATER:
		setWater();
		break;
	}


	_endDrag = false;
	_vDragInfo.clear();
}

bool sceneMaptool::calcObjectTile(void)
{
	if (_ptMouse.x >= SIDEWINDOW_STARTX)
		return false;


	ZeroMemory(&_objState, sizeof(OBJSTATE) * OBJECTSIZE_MAX_X * OBJECTSIZE_MAX_Y);

	bool isOverWindowSize = false;

	int width = 0;
	int height = 0;

	switch (_curObject)
	{
	case SAMPLEOBJECT_MINERAL:
		width  = OBJ_MINERAL_WIDTH;
		height = OBJ_MINERAL_HEIGHT;
		break;
	case SAMPLEOBJECT_GAS:
		width  = OBJ_GAS_WIDTH;
		height = OBJ_GAS_HEIGHT;
		break;
	case SAMPLEOBJECT_PLAYER1:
		width = OBJ_LOCATION_PLAYER_WIDTH;
		height = OBJ_LOCATION_PLAYER_HEIGHT;
		//이미 위치를 지정했으면
		if (_isLocatedP1)
		{
			for (int i = 0; i < width; i++)
			{
				for (int j = 0; j < height; j++)
				{
					_objState[i][j] = OBJSTATE_OVERLAP;
				}
			}
			return false;
		}
		break;
	case SAMPLEOBJECT_PLAYER2:
		width  = OBJ_LOCATION_PLAYER_WIDTH;
		height = OBJ_LOCATION_PLAYER_HEIGHT;
		//이미 위치를 지정했으면
		if (_isLocatedP2)
		{
			for (int i = 0; i < width; i++)
			{
				for (int j = 0; j < height; j++)
				{
					_objState[i][j] = OBJSTATE_OVERLAP;
				}
			}
			return false;
		}
		break;
	case SAMPLEOBJECT_ERASER:
		_objState[0][0] = OBJSTATE_PLACEABLE;
		return true;
		break;
	}

	//해당 타일에 이미 오브젝트가 깔려있는지 체크
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (_cursorTile.x + i < 0) { isOverWindowSize = true; continue; }
			if (_cursorTile.y + j < 0) { isOverWindowSize = true; continue; }
			if (_cursorTile.x + i >= TILEX) { isOverWindowSize = true; continue; }
			if (_cursorTile.y + j >= TILEY) { isOverWindowSize = true; continue; }

			if (_tiles[_cursorTile.x + i][_cursorTile.y + j].obj == OBJECT_NONE
				&& (_tiles[_cursorTile.x + i][_cursorTile.y + j].attribute & ATTR_UNBUILD) == 0)
			{
				_objState[i][j] = OBJSTATE_PLACEABLE;
			}
			else
			{
				_objState[i][j] = OBJSTATE_OVERLAP;
			}
		}
	}

	//설치하려는 오브젝트가 최대 맵을 벗어났을 경우
	if (isOverWindowSize)
		return false;

	//오브젝트가 겹쳤을 경우
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (_objState[i][j] == OBJSTATE_OVERLAP) 
				return false;
		}
	}




	return true;
}

void sceneMaptool::clickObjectTile(void)
{
	if (_ptMouse.x >= SIDEWINDOW_STARTX)
		return;

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) == false)
	{
		return;
	}


	switch (_curObject)
	{
		case SAMPLEOBJECT_MINERAL:
		{
			int mineralNum = RND->getFromIntTo(1, 3);
			for (int i = 0; i < OBJ_MINERAL_WIDTH; i++)
			{
				for (int j = 0; j < OBJ_MINERAL_HEIGHT; j++)
				{
					if (i == 0 && j == 0)
					{
						switch (mineralNum)
						{
						case 1: _tiles[_cursorTile.x + i][_cursorTile.y + j].obj = OBJECT_MINERAL1_START; break;
						case 2: _tiles[_cursorTile.x + i][_cursorTile.y + j].obj = OBJECT_MINERAL2_START; break;
						case 3: _tiles[_cursorTile.x + i][_cursorTile.y + j].obj = OBJECT_MINERAL3_START; break;
						}
						_tiles[_cursorTile.x + i][_cursorTile.y + j].nrAmount = _editboxNrAmount->getStrNum();
					}
					else
					{
						switch (mineralNum)
						{
						case 1:	_tiles[_cursorTile.x + i][_cursorTile.y + j].obj = OBJECT_MINERAL1_BODY; break;
						case 2: _tiles[_cursorTile.x + i][_cursorTile.y + j].obj = OBJECT_MINERAL2_BODY; break;
						case 3: _tiles[_cursorTile.x + i][_cursorTile.y + j].obj = OBJECT_MINERAL3_BODY; break;
						}
					}
				}
			}
		}
		break;
		case SAMPLEOBJECT_GAS:
		{
			for (int i = 0; i < OBJ_GAS_WIDTH; i++)
			{
				for (int j = 0; j < OBJ_GAS_HEIGHT; j++)
				{
					if (i == 0 && j == 0)
					{
						_tiles[_cursorTile.x + i][_cursorTile.y + j].obj = OBJECT_GAS_START;
						_tiles[_cursorTile.x + i][_cursorTile.y + j].nrAmount = _editboxNrAmount->getStrNum();
					}
					else
					{
						_tiles[_cursorTile.x + i][_cursorTile.y + j].obj = OBJECT_GAS_BODY;
					}
				}
			}
		}
		break;
		case SAMPLEOBJECT_PLAYER1:
		{
			for (int i = 0; i < OBJ_LOCATION_PLAYER_WIDTH; i++)
			{
				for (int j = 0; j < OBJ_LOCATION_PLAYER_HEIGHT; j++)
				{
					if (i == 0 && j == 0)
					{
						_tiles[_cursorTile.x + i][_cursorTile.y + j].obj = OBJECT_LOCATION_P1_START;
					}
					else
					{
						_tiles[_cursorTile.x + i][_cursorTile.y + j].obj = OBJECT_LOCATION_P1_BODY;
					}
				}
			}
			_isLocatedP1 = true;
		}
		break;
		case SAMPLEOBJECT_PLAYER2:
		{
			for (int i = 0; i < OBJ_LOCATION_PLAYER_WIDTH; i++)
			{
				for (int j = 0; j < OBJ_LOCATION_PLAYER_HEIGHT; j++)
				{
					if (i == 0 && j == 0)
					{
						_tiles[_cursorTile.x + i][_cursorTile.y + j].obj = OBJECT_LOCATION_P2_START;
					}
					else
					{
						_tiles[_cursorTile.x + i][_cursorTile.y + j].obj = OBJECT_LOCATION_P2_BODY;
					}
				}
			}
			_isLocatedP2 = true;
		}
		break;
		case SAMPLEOBJECT_ERASER:
		{
			eraseObject(_cursorTile.x, _cursorTile.y);
		}
		break;
	}
}

void sceneMaptool::eraseObject(int tilex, int tiley)
{
	POINT startTile = { 0, 0 };
	int width = 0;
	int height = 0;

	switch (_tiles[tilex][tiley].obj)
	{
		case OBJECT_NONE:
			return;
		break;

		//자원(미네랄, 가스)
		case OBJECT_MINERAL1_START:	
		case OBJECT_MINERAL2_START:
		case OBJECT_MINERAL3_START:
			startTile = { tilex, tiley };
			width  = OBJ_MINERAL_WIDTH;
			height = OBJ_MINERAL_HEIGHT;
		break;
		case OBJECT_MINERAL1_BODY:
		case OBJECT_MINERAL2_BODY:
		case OBJECT_MINERAL3_BODY:
			startTile = findObjectStartPoint(tilex, tiley);
			width  = OBJ_MINERAL_WIDTH;
			height = OBJ_MINERAL_HEIGHT;
		break;
		case OBJECT_GAS_START:
			startTile = { tilex, tiley };
			width  = OBJ_GAS_WIDTH;
			height = OBJ_GAS_HEIGHT;
			break;
		case OBJECT_GAS_BODY:
			startTile = findObjectStartPoint(tilex, tiley);
			width  = OBJ_GAS_WIDTH;
			height = OBJ_GAS_HEIGHT;
			break;

		//플레이어 시작위치
		case OBJECT_LOCATION_P1_START:		
			startTile = { tilex, tiley };
			width  = OBJ_LOCATION_PLAYER_WIDTH;
			height = OBJ_LOCATION_PLAYER_HEIGHT;
			_isLocatedP1 = false;
			break;
		case OBJECT_LOCATION_P1_BODY:
			startTile = findObjectStartPoint(tilex, tiley);
			width  = OBJ_LOCATION_PLAYER_WIDTH;
			height = OBJ_LOCATION_PLAYER_HEIGHT;
			_isLocatedP1 = false;
			break;
		case OBJECT_LOCATION_P2_START:
			startTile = { tilex, tiley };
			width  = OBJ_LOCATION_PLAYER_WIDTH;
			height = OBJ_LOCATION_PLAYER_HEIGHT;
			_isLocatedP2 = false;
			break;
		case OBJECT_LOCATION_P2_BODY:
			startTile = findObjectStartPoint(tilex, tiley);
			width  = OBJ_LOCATION_PLAYER_WIDTH;
			height = OBJ_LOCATION_PLAYER_HEIGHT;
			_isLocatedP2 = false;
			break;
	}

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (startTile.x + i < 0)		continue;
			if (startTile.y + j < 0)		continue;
			if (startTile.x + i >= TILEX)	continue;
			if (startTile.y + j >= TILEY)	continue;

			_tiles[startTile.x + i][startTile.y + j].obj = OBJECT_NONE;
			_tiles[startTile.x + i][startTile.y + j].nrAmount = 0;
		}
	}

}

POINT sceneMaptool::findObjectStartPoint(int tilex, int tiley)
{
	int width = 0;
	int height = 0;
	DWORD targetObj = OBJECT_NONE;

	switch (_tiles[tilex][tiley].obj)
	{
		//자원(미네랄, 가스)
	case OBJECT_MINERAL1_BODY:
		width  = OBJ_MINERAL_WIDTH;
		height = OBJ_MINERAL_HEIGHT;
		targetObj = OBJECT_MINERAL1_START;
		break;
	case OBJECT_MINERAL2_BODY:
		width  = OBJ_MINERAL_WIDTH;
		height = OBJ_MINERAL_HEIGHT;
		targetObj = OBJECT_MINERAL2_START;
		break;
	case OBJECT_MINERAL3_BODY:
		width  = OBJ_MINERAL_WIDTH;
		height = OBJ_MINERAL_HEIGHT;
		targetObj = OBJECT_MINERAL3_START;
		break;
	case OBJECT_GAS_BODY:
		width  = OBJ_GAS_WIDTH;
		height = OBJ_GAS_HEIGHT;
		targetObj = OBJECT_GAS_START;
		break;

		//플레이어 시작위치
	case OBJECT_LOCATION_P1_BODY:
		width  = OBJ_LOCATION_PLAYER_WIDTH;
		height = OBJ_LOCATION_PLAYER_HEIGHT;
		targetObj = OBJECT_LOCATION_P1_START;
		break;
	case OBJECT_LOCATION_P2_BODY:
		width  = OBJ_LOCATION_PLAYER_WIDTH;
		height = OBJ_LOCATION_PLAYER_HEIGHT;
		targetObj = OBJECT_LOCATION_P2_START;
		break;
	}

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (_tiles[tilex - i][tiley - j].obj == targetObj)
			{
				return { tilex - i , tiley - j };
			}
		}
	}

	assert(L"맵툴지우개 로직 에러");
	return { 0, 0 };
}

void sceneMaptool::setDirt(int cx, int cy)
{
	for (int i = -2; i <= 1; i++)
	{
		for (int j = -1; j <= 0; j++)
		{
			int idx = cx + i;
			int idy = cy + j;

			if (idx < 0) continue;
			if (idy < 0) continue;
			if (idx >= TILEX) continue;
			if (idy >= TILEY) continue;

			_tiles[idx][idy].terrain = TERRAIN_DIRT;
			_tiles[idx][idy].terrainNum.x = RND->getInt(24);
			_tiles[idx][idy].terrainNum.y = RND->getInt(20);
			_tiles[idx][idy].attribute = 0;
			_isChangedTile[idx][idy] = true;
		}
	}
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
					_tiles[i][j].terrainNum.x = RND->getInt(3);
					_tiles[i][j].terrainNum.y = RND->getInt(2);
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
						eraseObject(i, j);
						_tiles[i][j].attribute |= ATTR_UNMOVE;
						_tiles[i][j].attribute |= ATTR_UNBUILD;

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
						eraseObject(i, j);
						_tiles[i][j].attribute |= ATTR_UNMOVE;
						_tiles[i][j].attribute |= ATTR_UNBUILD;

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
						eraseObject(i, j);
						_tiles[i][j].attribute |= ATTR_UNMOVE;
						_tiles[i][j].attribute |= ATTR_UNBUILD;

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
						eraseObject(i, j);
						_tiles[i][j].attribute |= ATTR_UNMOVE;
						_tiles[i][j].attribute |= ATTR_UNBUILD;

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
						eraseObject(i, j);
						_tiles[i][j].attribute |= ATTR_UNMOVE;
						_tiles[i][j].attribute |= ATTR_UNBUILD;

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
						eraseObject(i, j);
						_tiles[i][j].attribute |= ATTR_UNMOVE;
						_tiles[i][j].attribute |= ATTR_UNBUILD;

						_isChangedTile[i][j] = true;
					}
				}
				break;
			}
		}
	}
}

void sceneMaptool::setWater(void)
{

}



void sceneMaptool::updateTileImage(void)
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

			if (_isChangedTile[idX][idY] == FALSE) continue;

			switch (_tiles[idX][idY].terrain)
			{
			case TERRAIN_DIRT:
				_imgTiles[idX][idY] = IMAGEMANAGER->findImage(L"maptool-terrain-Dirt");
				break;

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
			_imgTiles[x][y] = IMAGEMANAGER->findImage(L"maptool-terrain-Dirt");
		}
	}
}

void sceneMaptool::updateMiniMap(void)
{
	for (int y = 0; y < TILEY; y++)
	{
		for (int x = 0; x < TILEX; x++)
		{
			if (_tiles[x][y].obj != OBJECT_NONE)
			{
				switch (_tiles[x][y].obj)
				{
				case OBJECT_MINERAL1_START:	
				case OBJECT_MINERAL1_BODY:
				case OBJECT_MINERAL2_START:
				case OBJECT_MINERAL2_BODY:
				case OBJECT_MINERAL3_START:
				case OBJECT_MINERAL3_BODY:
				case OBJECT_GAS_START:
				case OBJECT_GAS_BODY:
					_colorMiniMap[x][y] = RGB(0, 228, 252);
					break;

											
				case OBJECT_LOCATION_P1_START:
				case OBJECT_LOCATION_P1_BODY:
					_colorMiniMap[x][y] = RGB(255, 0, 0);
					break;
				case OBJECT_LOCATION_P2_START:
				case OBJECT_LOCATION_P2_BODY:
					_colorMiniMap[x][y] = RGB(0, 0, 255);
					break;
				}
				continue;
			}

			switch (_tiles[x][y].terrain)
			{
			case TERRAIN_DIRT:
				_colorMiniMap[x][y] = RGB(49, 40, 25);
				break;

			case TERRAIN_HIGHTDIRT:
			case TERRAIN_HIGHTDIRT_LF:
			case TERRAIN_HIGHTDIRT_LU:
			case TERRAIN_HIGHTDIRT_LD:
			case TERRAIN_HIGHTDIRT_RG:
			case TERRAIN_HIGHTDIRT_RU:
			case TERRAIN_HIGHTDIRT_RD:
				_colorMiniMap[x][y] = RGB(69, 57, 39);
				break;
			}
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
				_imgTiles[idX][idY]->frameRender(getMemDC(), idX*MAPTOOL_TILESIZE - cameraX, idY*MAPTOOL_TILESIZE - cameraY, _tiles[idX][idY].terrainNum.x, _tiles[idX][idY].terrainNum.y);
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
			temp.x = (_vDragInfo[i].x) * MAPTOOL_TILESIZE - MAINCAMERA->getCameraX();
			temp.y = (_vDragInfo[i].y) * MAPTOOL_TILESIZE - MAINCAMERA->getCameraY();

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

void sceneMaptool::renderObject(void)
{
	int cameraX = MAINCAMERA->getCameraX();
	int cameraY = MAINCAMERA->getCameraY();

	int cameraIdX = cameraX / MAPTOOL_TILESIZE - 1;
	int cameraIdY = cameraY / MAPTOOL_TILESIZE - 1;

	//깔려 있는 오브젝트
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

			if (_tiles[idX][idY].obj == OBJECT_NONE) continue;

			int mineralFrameY = 0;

			switch (_tiles[idX][idY].obj)
			{
			//자원(미네랄, 가스)
			case OBJECT_MINERAL1_START:
				if (_tiles[idX][idY].nrAmount >= 1500)	mineralFrameY = 0;
				else									mineralFrameY = 3 - _tiles[idX][idY].nrAmount / 500;

				IMAGEMANAGER->frameRender(L"NeutralResource-Mineral1", getMemDC(), _tiles[idX][idY].rc.left - cameraX, _tiles[idX][idY].rc.top - MAPTOOL_TILESIZE - cameraY, 0, mineralFrameY);
				break;
			case OBJECT_MINERAL2_START:
				if (_tiles[idX][idY].nrAmount >= 1500)	mineralFrameY = 0;
				else									mineralFrameY = 3 - _tiles[idX][idY].nrAmount / 500;

				IMAGEMANAGER->frameRender(L"NeutralResource-Mineral2", getMemDC(), _tiles[idX][idY].rc.left - cameraX, _tiles[idX][idY].rc.top - MAPTOOL_TILESIZE - cameraY, 0, mineralFrameY);
				break;
			case OBJECT_MINERAL3_START:
				if (_tiles[idX][idY].nrAmount >= 1500)	mineralFrameY = 0;
				else									mineralFrameY = 3 - _tiles[idX][idY].nrAmount / 500;

				IMAGEMANAGER->frameRender(L"NeutralResource-Mineral3", getMemDC(), _tiles[idX][idY].rc.left - cameraX, _tiles[idX][idY].rc.top - MAPTOOL_TILESIZE - cameraY, 0, mineralFrameY);
				break;
			case OBJECT_GAS_START:
				IMAGEMANAGER->render(L"NeutralResource-Gas", getMemDC(), _tiles[idX][idY].rc.left - cameraX, _tiles[idX][idY].rc.top - cameraY);
				break;

			//플레이어 시작위치
			case OBJECT_LOCATION_P1_START:
				IMAGEMANAGER->render(L"maptool-object-LocationP1", getMemDC(), _tiles[idX][idY].rc.left - cameraX, _tiles[idX][idY].rc.top - cameraY);
				break;
			case OBJECT_LOCATION_P2_START:
				IMAGEMANAGER->render(L"maptool-object-LocationP2", getMemDC(), _tiles[idX][idY].rc.left - cameraX, _tiles[idX][idY].rc.top - cameraY);
				break;
			}
		}
	}

	int width = 0;
	int height = 0;

	//설치할 오브젝트(마우스 따라다니는)
	switch (_curObject)
	{
	case SAMPLEOBJECT_MINERAL:
		_imgObject->frameRender(getMemDC(), _tiles[_cursorTile.x][_cursorTile.y].rc.left - cameraX, _tiles[_cursorTile.x][_cursorTile.y].rc.top - MAPTOOL_TILESIZE - cameraY, 0, 0);
		width  = OBJ_MINERAL_WIDTH;
		height = OBJ_MINERAL_HEIGHT;
		break;
	case SAMPLEOBJECT_GAS:
		_imgObject->render(getMemDC(), _tiles[_cursorTile.x][_cursorTile.y].rc.left - cameraX, _tiles[_cursorTile.x][_cursorTile.y].rc.top - cameraY);
		width  = OBJ_GAS_WIDTH;
		height = OBJ_GAS_HEIGHT;
		break;
	case SAMPLEOBJECT_PLAYER1:
	case SAMPLEOBJECT_PLAYER2:
		_imgObject->render(getMemDC(), _tiles[_cursorTile.x][_cursorTile.y].rc.left - cameraX, _tiles[_cursorTile.x][_cursorTile.y].rc.top - cameraY);
		width  = OBJ_LOCATION_PLAYER_WIDTH;
		height = OBJ_LOCATION_PLAYER_HEIGHT;
		break;
	case SAMPLEOBJECT_ERASER:
		//_imgObject->render(getMemDC(), _tiles[_cursorTile.x][_cursorTile.y].rc.left, _tiles[_cursorTile.x][_cursorTile.y].rc.top);
		width  = OBJ_ERASER_WIDTH;
		height = OBJ_ERASER_HEIGHT;

		break;
	}

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (_cursorTile.x + i < 0)		continue;
			if (_cursorTile.y + j < 0)		continue;
			if (_cursorTile.x + i >= TILEX) continue;
			if (_cursorTile.y + j >= TILEY) continue;

			if (_objState[i][j] == OBJSTATE_NONE) continue;
			else if (_objState[i][j] == OBJSTATE_PLACEABLE)
			{
				IMAGEMANAGER->alphaRender(L"maptool-object-enableTile", getMemDC(),
					_tiles[_cursorTile.x + i][_cursorTile.y + j].rc.left - cameraX, _tiles[_cursorTile.x + i][_cursorTile.y + j].rc.top - cameraY, 128);
			}
			else if (_objState[i][j] == OBJSTATE_OVERLAP)
			{
				IMAGEMANAGER->alphaRender(L"maptool-object-disableTile", getMemDC(),
					_tiles[_cursorTile.x + i][_cursorTile.y + j].rc.left - cameraX, _tiles[_cursorTile.x + i][_cursorTile.y + j].rc.top - cameraY, 128);
			}
		}
	}

}



void sceneMaptool::renderSideWindow(void)
{
	RectangleMake(getMemDC(), SIDEWINDOW_STARTX, 0, WINSIZEX - SIDEWINDOW_STARTX, WINSIZEY);

	renderMiniMap();

	for (int i = 0; i < SAMPLETERRAIN_MAX; i++)
	{
		_imgSelectTerrain[i]->frameRender(getMemDC(), _rcSelectTerrain[i].left, _rcSelectTerrain[i].top, 0, 0);

		LineToRect(getMemDC(), _rcSelectTerrain[i]);

		if (_curTerrain == (SAMPLETERRAIN)i)
		{
			RECT rcTemp = _rcSelectTerrain[i];
			HPEN oldPen = (HPEN)SelectObject(getMemDC(), _gPen[PENVERSION_BLUE]);
			LineToRect(getMemDC(), _rcSelectTerrain[i], 2);
			SelectObject(getMemDC(), oldPen);
		}
	}

	for (int i = 0; i < SAMPLEOBJECT_MAX; i++)
	{
		_imgSelectObject[i]->render(getMemDC(), _rcSelectObject[i].left, _rcSelectObject[i].top);

		LineToRect(getMemDC(), _rcSelectObject[i]);

		if (_curObject == (SAMPLEOBJECT)i)
		{
			HPEN oldPen = (HPEN)SelectObject(getMemDC(), _gPen[PENVERSION_BLUE]);
			LineToRect(getMemDC(), _rcSelectObject[i], 2);
			SelectObject(getMemDC(), oldPen);
		}
	}

	_editboxNrAmount->render();


	for (int i = 0; i < BTNCTRL_MAX; i++)
	{
		_btnCtrl[i]->render();
	}
}


void sceneMaptool::renderMiniMap(void)
{
	HDC hDCtemp = _imgMiniMap->getMemDC();
	PatBlt(hDCtemp, 0, 0, TILEX, TILEY, BLACKNESS);

	for (int y = 0; y < TILEY; y++)
	{
		for (int x = 0; x < TILEX; x++)
		{
			SetPixel(hDCtemp, x, y, _colorMiniMap[x][y]);
		}
	}
	


	HPEN oldPen = (HPEN)SelectObject(hDCtemp, _gPen[PENVERSION_MINIMAP]);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDCtemp, _gBrush[BRUSHVERSION_BLACK]);
	LineToRect(hDCtemp, _rcMiniMapCamera);
	SelectObject(hDCtemp, oldPen);
	SelectObject(hDCtemp, oldBrush);

	//BitBlt(getMemDC(), SIDEWINDOW_STARTX + 16, 16, TILEX, TILEY, hDCtemp, 0, 0, SRCCOPY);

	GdiTransparentBlt(getMemDC(),		//복사될 DC영역
		SIDEWINDOW_STARTX + 16,
		0 + 16,
		TILEX, TILEY,												//복사될 가로 세로 크기

		hDCtemp,			//복사할 DC
		0, 0,				//복사할 좌표
		TILEX, TILEY,		//복사할 가로 세로 크기
		RGB(0, 0, 0));			//제외할 칼라

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

