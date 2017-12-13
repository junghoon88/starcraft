#include "stdafx.h"
#include "gameMap.h"

gameMap::gameMap()
{
}


gameMap::~gameMap()
{
}

HRESULT gameMap::init(void)
{
	//맵로드
	int num = DATABASE->getMapNum();
	loadData(num);

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
}

void gameMap::loadData(int num)
{
	HANDLE file;
	DWORD read;

	//실제 맵 데이터를 불러온다.
	TCHAR strMapName[100];
	_stprintf(strMapName, L"MapData/test.map");

	file = CreateFile(strMapName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);


	CloseHandle(file);

	//불러온 타일 정보를 가지고 타일이미지를 넣어준다.
	setTileImage();
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
			case TERRAIN_DIRT:
				_stprintf(strKey, L"gamemap-terrain-Dirt-%02d", _tiles[x][y].terrainNum);
				_imgTiles[x][y] = IMAGEMANAGER->findImage(strKey);
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
}

void gameMap::renderTiles(void)
{
	int cameraX = MAINCAMERA->getCameraX();
	int cameraY = MAINCAMERA->getCameraY();

	int cameraIdX = cameraX / GAMEMAP_TILESIZE - 1;
	int cameraIdY = cameraY / GAMEMAP_TILESIZE - 1;

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

			_imgTiles[idX][idY]->render(getMemDC(), idX*GAMEMAP_TILESIZE - cameraX, idY*GAMEMAP_TILESIZE - cameraY);
		}
	}
}