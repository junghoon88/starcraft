#include "stdafx.h"
#include "gameMap.h"

#include "nrMineral.h"
#include "nrGas.h"


gameMap::gameMap()
{
	ZeroMemory(&_tiles, sizeof(tagTile) * TILEX * TILEY);
	ZeroMemory(&_imgTiles, sizeof(image*) * TILEX * TILEY);

	_locationP1 = { 0, 0 };
	_locationP2 = { 0, 0 };

	_miniMapBackground = NULL;
}

gameMap::~gameMap()
{
}

HRESULT gameMap::init(void)
{
	//맵로드
	loadData();

	//불러온 타일 정보를 가지고 타일이미지를 넣어준다.
	setTileImage();
	createNeutralResource();

	return S_OK;
}

void gameMap::release(void)
{
	IMAGEMANAGER->deleteImage(L"minimap-background");
}

void gameMap::update(void)
{
	//미네랄을 다 팠으면 제거
	for (int i = 0; i < _vMineral.size(); i++)
	{
		if (_vMineral[i]->getAmountMineral() == 0)
		{
			RECT rcMineral = _vMineral[i]->getRectTile();

			for (int x = 0; x < OBJ_MINERAL_WIDTH; x++)
			{
				for (int y = 0; y < OBJ_MINERAL_HEIGHT; y++)
				{
					int idx = rcMineral.left + x;
					int idy = rcMineral.top + y;
					_tiles[idx][idy].obj = OBJECT_NONE;
				}
			}

			SAFE_RELEASEDELETE(_vMineral[i]);
			_vMineral.erase(_vMineral.begin() + i);
		}
	}
}

void gameMap::render(void)
{
	renderTiles();
	renderObject();
}

void gameMap::loadData(void)
{
	HANDLE file;
	DWORD read;

	//실제 맵 데이터를 불러온다.
	TCHAR strMapName[100];
	_tcscpy(strMapName, DATABASE->getMapFile());
	//_stprintf(strMapName, L"MapData/test3.map");

	file = CreateFile(strMapName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);


	CloseHandle(file);


	//미니맵 불러오기
	//1. path 에서 확장자만 bmp 로 변경
	char szDrv[_MAX_DRIVE], szDir[_MAX_DIR], szFname[_MAX_FNAME], szExt[_MAX_EXT];
	_splitpath(convert_mb(strMapName), szDrv, szDir, szFname, szExt);
	sprintf(szExt, ".bmp");
	//2. bmp로 바꾼걸 다시 합체
	char newpath[MAXCHAR];
	_makepath_s(newpath, szDrv, szDir, szFname, szExt);

	_miniMapBackground = IMAGEMANAGER->addImage(L"minimap-background", convert_wc(newpath), TILEX, TILEY);
}

void gameMap::setTileImage(void)
{
	TCHAR strKey[128] = L"";

	for (int y = 0; y < TILEY; y++)
	{
		for (int x = 0; x < TILEX; x++)
		{
			switch (_tiles[x][y].terrain)
			{
			case TERRAIN_DIRT:			_imgTiles[x][y] = IMAGEMANAGER->findImage(L"maptool-terrain-Dirt");			break;

			case TERRAIN_HIGHTDIRT:		_imgTiles[x][y] = IMAGEMANAGER->findImage(L"maptool-terrain-HighDirt");		break;
			case TERRAIN_HIGHTDIRT_LF:	_imgTiles[x][y] = IMAGEMANAGER->findImage(L"maptool-terrain-HighDirt-LF");	break;
			case TERRAIN_HIGHTDIRT_LU:	_imgTiles[x][y] = IMAGEMANAGER->findImage(L"maptool-terrain-HighDirt-LU");	break;
			case TERRAIN_HIGHTDIRT_LD:	_imgTiles[x][y] = IMAGEMANAGER->findImage(L"maptool-terrain-HighDirt-LD");	break;
			case TERRAIN_HIGHTDIRT_RG:	_imgTiles[x][y] = IMAGEMANAGER->findImage(L"maptool-terrain-HighDirt-RG");	break;
			case TERRAIN_HIGHTDIRT_RU:	_imgTiles[x][y] = IMAGEMANAGER->findImage(L"maptool-terrain-HighDirt-RU");	break;
			case TERRAIN_HIGHTDIRT_RD:	_imgTiles[x][y] = IMAGEMANAGER->findImage(L"maptool-terrain-HighDirt-RD");	break;

			case TERRAIN_WATER:
				break;
			}
		}
	}
}

void gameMap::createNeutralResource(void)
{
	for (int y = 0; y < TILEY; y++)
	{
		for (int x = 0; x < TILEX; x++)
		{
			switch (_tiles[x][y].obj)
			{
			case OBJECT_MINERAL1_START:
			{
				nrMineral* mineral = new nrMineral(x, y, 1);
				mineral->init(_tiles[x][y].nrAmount);
				_vMineral.push_back(mineral);
			}
			break;
			case OBJECT_MINERAL2_START:
			{
				nrMineral* mineral = new nrMineral(x, y, 2);
				mineral->init(_tiles[x][y].nrAmount);
				_vMineral.push_back(mineral);
			}
			break;
			case OBJECT_MINERAL3_START:
			{
				nrMineral* mineral = new nrMineral(x, y, 3);
				mineral->init(_tiles[x][y].nrAmount);
				_vMineral.push_back(mineral);
			}
			break;
			case OBJECT_GAS_START:
			{
				nrGas* gas = new nrGas(x, y);
				gas->init(_tiles[x][y].nrAmount);
				_vGas.push_back(gas);
			}
			break;

				//플레이어 시작위치
			case OBJECT_LOCATION_P1_START:
				_locationP1 = { x, y };
				_tiles[x][y].obj = OBJECT_NONE;
			break;
			case OBJECT_LOCATION_P1_BODY:
				_tiles[x][y].obj = OBJECT_NONE;
			break;

			case OBJECT_LOCATION_P2_START:
				_locationP2 = { x, y };
				_tiles[x][y].obj = OBJECT_NONE;
			break;
			case OBJECT_LOCATION_P2_BODY:
				_tiles[x][y].obj = OBJECT_NONE;
			break;
			}
		}
	}
}


void gameMap::renderTiles(void)
{
	int cameraX = MAINCAMERA->getCameraX();
	int cameraY = MAINCAMERA->getCameraY();

	int cameraIdX = cameraX / TILESIZE - 1;
	int cameraIdY = cameraY / TILESIZE - 1;

	for (int y = 0; y < GAMEMAP_TILEVIEWY + 2; y++)
	{
		for (int x = 0; x < GAMEMAP_TILEVIEWX + 2; x++)
		{
			int idX = cameraIdX + x;
			int idY = cameraIdY + y;

			if (idX < 0) continue;
			if (idY < 0) continue;
			if (idX >= TILEX) continue;
			if (idY >= TILEY) continue;
			if (_imgTiles[idX][idY] == NULL) continue;

			if (_tiles[idX][idY].attribute & ATTR_CREEP)
			{
				RENDERMANAGER->insertImgFrame(ZORDER_TILES, IMAGEMANAGER->findImage(L"gamemap-creep"), idX*TILESIZE - cameraX, idY*TILESIZE - cameraY, _tiles[idX][idY].terrainNum.x, _tiles[idX][idY].terrainNum.y);
			}
			else
			{
				RENDERMANAGER->insertImgFrame(ZORDER_TILES, _imgTiles[idX][idY], idX*TILESIZE - cameraX, idY*TILESIZE - cameraY, _tiles[idX][idY].terrainNum.x, _tiles[idX][idY].terrainNum.y);
			}
		}
	}
}

void gameMap::renderObject(void)
{
	int cameraX = MAINCAMERA->getCameraX();
	int cameraY = MAINCAMERA->getCameraY();

	RECT rcCamera = MAINCAMERA->getRectCamera();
	rcCamera.bottom = rcCamera.top + GAMEMAP_TILEVIEWY * TILESIZE;

	RECT temp;

	for (int i = 0; i < _vMineral.size(); i++)
	{
		if(IntersectRect(&temp, &rcCamera, &_vMineral[i]->getRectBody()))
		{
			int mineralFrameY = 0;
			int nrAmount = _vMineral[i]->getAmountMineral();
			if (nrAmount >= 1500)	mineralFrameY = 0;
			else					mineralFrameY = 3 - nrAmount / 500;

			RECT rcBodyOffset = _vMineral[i]->getRectBody();
			OffsetRect(&rcBodyOffset, -cameraX, -cameraY);

			RENDERMANAGER->insertImgFrame(ZORDER_GAMEOBJECT, _vMineral[i]->getImage(), rcBodyOffset.left, rcBodyOffset.top - TILESIZE, 0, mineralFrameY, rcBodyOffset);

			if (_vMineral[i]->getBattleStatus().clicked)
			{
				//rcBodyOffset.top = (rcBodyOffset.top + rcBodyOffset.bottom) / 2;
				RENDERMANAGER->insertEllipse(ZORDER_GAMEOBJECT, rcBodyOffset, PENVERSION_RESOURCECLICK);
			}
		}
	}

	for (int i = 0; i < _vGas.size(); i++)
	{
		if (IntersectRect(&temp, &rcCamera, &_vGas[i]->getRectBody()))
		{
			RECT rcBodyOffset = _vGas[i]->getRectBody();
			OffsetRect(&rcBodyOffset, -cameraX, -cameraY);

			RENDERMANAGER->insertImg(ZORDER_GAMEOBJECT, _vGas[i]->getImage(), rcBodyOffset.left, rcBodyOffset.top);

			if (_vGas[i]->getBattleStatus().clicked)
			{
				//rcBodyOffset.top = (rcBodyOffset.top + rcBodyOffset.bottom) / 2;
				RENDERMANAGER->insertEllipse(ZORDER_GAMEOBJECT, rcBodyOffset, PENVERSION_RESOURCECLICK);
			}
		}
	}
}

nrGas* gameMap::findGas(POINT ptTile)
{
	for (int i = 0; i < _vGas.size(); i++)
	{
		RECT rcTile = _vGas[i]->getRectTile();

		if (ptTile.x == rcTile.left && ptTile.y == rcTile.top)
		{
			return _vGas[i];
		}
	}

	return NULL;
}
