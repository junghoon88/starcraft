#include "stdafx.h"
#include "gameMap.h"

gameMap::gameMap()
{
	ZeroMemory(&_tiles, sizeof(tagTile) * TILEX * TILEY);
	ZeroMemory(&_imgTiles, sizeof(image*) * TILEX * TILEY);

	_locationP1 = { 0, 0 };
	_locationP2 = { 0, 0 };
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
}

void gameMap::update(void)
{
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
	_stprintf(strMapName, L"MapData/test.map");

	file = CreateFile(strMapName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);


	CloseHandle(file);
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
				nrMineral* mineral = new nrMineral(x, y, _tiles[x][y].nrAmount, 1);
				_vMineral.push_back(mineral);
			}
			break;
			case OBJECT_MINERAL2_START:
			{
				nrMineral* mineral = new nrMineral(x, y, _tiles[x][y].nrAmount, 2);
				_vMineral.push_back(mineral);
			}
			break;
			case OBJECT_MINERAL3_START:
			{
				nrMineral* mineral = new nrMineral(x, y, _tiles[x][y].nrAmount, 3);
				_vMineral.push_back(mineral);
			}
			break;
			case OBJECT_GAS_START:
			{
				nrGas* gas = new nrGas(x, y, _tiles[x][y].nrAmount);
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
			int nrAmount = _vMineral[i]->getAmount();
			if (nrAmount >= 1500)	mineralFrameY = 0;
			else					mineralFrameY = 3 - nrAmount / 500;

			//_vMineral[i]->getImage()->frameRender(getMemDC(), _vMineral[i]->getRectBody().left - cameraX, _vMineral[i]->getRectBody().top - TILESIZE - cameraY, 0, mineralFrameY);
			RENDERMANAGER->insertImgFrame(ZORDER_GAMEOBJECT, _vMineral[i]->getImage(), _vMineral[i]->getRectBody().left - cameraX, _vMineral[i]->getRectBody().top - TILESIZE - cameraY, 0, mineralFrameY, _vMineral[i]->getRectBody());
		}
	}

	for (int i = 0; i < _vGas.size(); i++)
	{
		if (IntersectRect(&temp, &rcCamera, &_vGas[i]->getRectBody()))
		{
			//_vGas[i]->getImage()->render(getMemDC(), _vGas[i]->getRectBody().left - cameraX, _vGas[i]->getRectBody().top - cameraY);
			RENDERMANAGER->insertImg(ZORDER_GAMEOBJECT, _vGas[i]->getImage(), _vGas[i]->getRectBody().left - cameraX, _vGas[i]->getRectBody().top - cameraY);
		}
	}
}
