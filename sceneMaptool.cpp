#include "stdafx.h"
#include "sceneMaptool.h"


sceneMaptool::sceneMaptool()
{
	for (int i = 0; i < BTNCTRL_MAX; i++)
	{
		_btnCtrl[i] = NULL;
	}
	for (int y = 0; y < TILEY; y++)
	{
		for (int x = 0; x < TILEX; x++)
		{
			_imgTiles[x][y] = NULL;
		}
	}
}


sceneMaptool::~sceneMaptool()
{

}

HRESULT sceneMaptool::init(void)
{
	initButtons();

	for (int y = 0; y < TILEY; y++)
	{
		for (int x = 0; x < TILEX; x++)
		{
			ZeroMemory(&_tiles[x][y], sizeof(tagTile));
		}
	}

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


	updateTileImage();
	for (int i = 0; i < BTNCTRL_MAX; i++)
	{
		_btnCtrl[i]->update();
	}

}

void sceneMaptool::render(void)
{
	int cameraX = MAINCAMERA->getCameraX();
	int cameraY = MAINCAMERA->getCameraY();

	int cameraIdX = cameraX / TILESIZE - 1;
	int cameraIdY = cameraY / TILESIZE - 1;

	for (int y = 0; y < TILEVIEWX + 2; y++)
	{
		for (int x = 0; x < TILEVIEWX + 2; x++)
		{
			int idX = cameraIdX + x;
			int idY = cameraIdY + y;

			if (idX < 0) continue;
			if (idY < 0) continue;
			if (idX >= TILEX) continue;
			if (idY >= TILEY) continue;
			if (_imgTiles[idX][idY] == NULL) continue;

			_imgTiles[idX][idY]->render(getMemDC(), idX*TILESIZE - cameraX, idY*TILESIZE - cameraY);
		}
	}



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

void sceneMaptool::updateTileImage(void)
{
	DWORD tick1 = GetTickCount();
	TCHAR strKey[128] = L"";


	int cameraX = MAINCAMERA->getCameraX();
	int cameraY = MAINCAMERA->getCameraY();

	int cameraIdX = cameraX / TILESIZE - 1;
	int cameraIdY = cameraY / TILESIZE - 1;

	for (int y = 0; y < TILEVIEWX + 2; y++)
	{
		for (int x = 0; x < TILEVIEWX + 2; x++)
		{
			int idX = cameraIdX + x;
			int idY = cameraIdY + y;

			if (idX < 0) continue;
			if (idY < 0) continue;
			if (idX >= TILEX) continue;
			if (idY >= TILEY) continue;

			switch (_tiles[idX][idY].terrain)
			{
			case TERRAIN_DIRT:
				_stprintf(strKey, L"terrain-Dirt-%02d", _tiles[idX][idY].terrainNum);
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
	printf("");
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




void sceneMaptool::cbButtonSave(void * obj)
{
	sceneMaptool* sm = (sceneMaptool*)obj;
	sm->saveData();
}

void sceneMaptool::cbButtonLoad(void * obj)
{
	sceneMaptool* sm = (sceneMaptool*)obj;
	sm->loadData();
}

