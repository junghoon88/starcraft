#include "stdafx.h"
#include "miniMap.h"

#include "gameMap.h"
#include "gameController.h"
#include "player.h"

miniMap::miniMap()
	: _imgBackground(NULL), _img(NULL), _imgTemp(NULL)
{
}


miniMap::~miniMap()
{
}


HRESULT miniMap::init(void)
{
	_imgBackground = IMAGEMANAGER->findImage(L"minimap-background");
	_img = IMAGEMANAGER->addImage(L"miniMap", TILEX, TILEY);
	_imgTemp = IMAGEMANAGER->addImage(L"miniMapTemp", TILEX, TILEY);

	//BitBlt(_img->getMemDC(), 0, 0, TILEX, TILEY,
	//	_imgBackground->getMemDC(), 0, 0, SRCCOPY);
	
	PatBlt(_img->getMemDC(), 0, 0, TILEX, TILEY, BLACKNESS);


	_rcMiniMap = RectMake(6, 348, TILEX, TILEY);


	int width = WINSIZEX / TILESIZE;
	int height = WINSIZEY / TILESIZE;

	_rcMiniMapCamera = RectMake(0, 0, width, height);

	_updated = false;

	return S_OK;
}

void miniMap::release(void)
{
}

void miniMap::update(void)
{
	updateCamera();
	//updateMiniMap();
}

void miniMap::render(void)
{
	if (_img == NULL || _imgTemp == NULL)
		return;

	if (_updated)
	{
		BitBlt(_imgTemp->getMemDC(), 0, 0, TILEX, TILEY, _img->getMemDC(), 0, 0, SRCCOPY);
		_updated = false;
	}

	//_img->render(getMemDC(), _rc.left, _rc.top);
	RENDERMANAGER->insertImg(ZORDER_INTERFACE, _imgTemp, _rcMiniMap.left, _rcMiniMap.top);


	int width  = WINSIZEX / TILESIZE;
	int height = WINSIZEY / TILESIZE;

	image* _backBuffer3 = IMAGEMANAGER->addImage(L"backBuffer3", TILEX, TILEY);
	HDC hDCtemp = _backBuffer3->getMemDC();
	PatBlt(hDCtemp, 0, 0, TILEX, TILEY, BLACKNESS);

	GdiTransparentBlt(getMemDC(),		//복사될 DC영역
		_rcMiniMap.left + MAINCAMERA->getCameraX() / TILESIZE,
		_rcMiniMap.top + MAINCAMERA->getCameraY() / TILESIZE,
		width, height,												//복사될 가로 세로 크기

		hDCtemp,			//복사할 DC
		0, 0,				//복사할 좌표
		width, height,		//복사할 가로 세로 크기
		RGB(0, 0, 0));			//제외할 칼라


	//카메라
	RENDERMANAGER->insertLineRectangle(ZORDER_INTERFACE, _rcMiniMapCamera, PENVERSION_MINIMAP);
}


void miniMap::updateCamera(void)
{
	if (PtInRect(&_rcMiniMap, _ptMouse))
	{
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			float x = _ptMouse.x - _rcMiniMap.left;
			float y = _ptMouse.y - _rcMiniMap.top;

			float halfWidth = (WINSIZEX / TILESIZE) * 0.5f;
			float halfHeight = (WINSIZEY / TILESIZE) * 0.5f;

			if (x <= halfWidth)					x = halfWidth;
			else if (x >= TILEX - halfWidth)	x = TILEX - halfWidth;

			if (y <= halfHeight)				y = halfHeight;
			else if (y >= TILEY - halfHeight)	y = TILEY - halfHeight;

			MAINCAMERA->setCameraPos((x - halfWidth) * TILESIZE, (y - halfHeight) * TILESIZE);
		}
	}

	int x = MAINCAMERA->getCameraX() / TILESIZE;
	int y = MAINCAMERA->getCameraY() / TILESIZE;
	int width = WINSIZEX / TILESIZE;
	int height = WINSIZEY / TILESIZE;

	_rcMiniMapCamera = RectMake(x, y, width, height);

	OffsetRect(&_rcMiniMapCamera, _rcMiniMap.left, _rcMiniMap.top);
}

void miniMap::updateMiniMap(void)
{
	BitBlt(_img->getMemDC(), 0, 0, TILEX, TILEY,
			_imgBackground->getMemDC(), 0, 0, SRCCOPY);

	for (int i = 0; i < TILEX; i++)
	{
		for (int j = 0; j < TILEY; j++)
		{
			COLORREF color = RGB(255, 0, 255);
			BOOL isFog = false;

			if (_gameController->getMyPlayer()->getFog()->getFogs()[i][j].level == FOGLEVEL_BLACK)
			{
				SetPixel(_img->getMemDC(), i, j, RGB(0, 0, 0));
				continue;
			}
			else if (_gameController->getMyPlayer()->getFog()->getFogs()[i][j].level == FOGLEVEL_GRAY)
			{
				isFog = true;
			}

			switch (_gameMap->getTiles()[i][j].obj)
			{
			case OBJECT_MINERAL1_START:	
			case OBJECT_MINERAL1_BODY:	
			case OBJECT_MINERAL2_START:	
			case OBJECT_MINERAL2_BODY:	
			case OBJECT_MINERAL3_START:	
			case OBJECT_MINERAL3_BODY:	
			case OBJECT_GAS_START:		
			case OBJECT_GAS_BODY:		
				color = MINIMAPCOLOR_NEUTRAL;
				break;

			case OBJECT_BUILDING_PLAYER1:			
			case OBJECT_BUILDING_GAS_START_PLAYER1:	
			case OBJECT_BUILDING_GAS_PLAYER1:		
				if (_gameController->getMyPlayer()->getPlayerNum() == PLAYER1)
				{
					color = MINIMAPCOLOR_MYOBJCT;
				}
				else
				{
					color = MINIMAPCOLOR_ENEMY;
				}
				break;

			case OBJECT_BUILDING_PLAYER2:			
			case OBJECT_BUILDING_GAS_START_PLAYER2:	
			case OBJECT_BUILDING_GAS_PLAYER2:		
				//if (_gameController->getMyPlayer()->getPlayerNum() == PLAYER2)
				//{
				//	color = MINIMAPCOLOR_MYOBJCT;
				//}
				//else
				{
					color = MINIMAPCOLOR_ENEMY;
				}
				break;

			default:
				continue;
			}

			if (isFog)
			{
				int r = GetRValue(color);
				int g = GetGValue(color);
				int b = GetBValue(color);
				int avr = (r + g + b) / 3;

				SetPixel(_img->getMemDC(), i, j, RGB(r, g, b));
			}
			else
			{
				SetPixel(_img->getMemDC(), i, j, color);
			}
		}
	}

	for (int i = 0; i < PLAYER_NUM; i++)
	{
		BOOL isMyteam = (_gameController->getMyPlayer()->getPlayerNum() == (PLAYER)i);

		for (int j = 0; j < _player[i]->getUnits().size(); j++)
		{
			Unit* unit = _player[i]->getUnits()[j];

			if (unit->getValid() == FALSE) continue;

			unit->addIsBusy(0x04);

			POINT id = unit->getBattleStatus().ptTile;

			if (isMyteam)
			{
				SetPixel(_img->getMemDC(), id.x, id.y, MINIMAPCOLOR_MYOBJCT);
			}
			else
			{
				SetPixel(_img->getMemDC(), id.x, id.y, MINIMAPCOLOR_ENEMY);
			}

			unit->deleteIsBusy(0x04);
		} 
	}

	_updated = true;
}
