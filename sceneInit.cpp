#include "stdafx.h"
#include "sceneInit.h"
#include "tileNode.h"


sceneInit::sceneInit()
	: _loading(NULL)
{
}


sceneInit::~sceneInit()
{
}

HRESULT sceneInit::init(void)
{
	_loading = new loading;
	_loading->init();


	initImage();
	initSound();

	return S_OK;
}


void sceneInit::release(void)
{
	_loading->release();
	SAFE_DELETE(_loading);
}

void sceneInit::update(void)
{
	if (_loading->loadingImageDone())
	{
		_loading->update();
		SCENEMANAGER->changeScene(L"¼±ÅÃ¾À");
	}
	else
	{
		_loading->update();
	}
}

void sceneInit::render(void)
{
	_loading->render();
}

void sceneInit::initImage(void)
{
	_loading->loadFrameImage(L"¹öÆ°1", L"image/button1.bmp", 100, 60, 1, 2);

	initImageMaptoolTiles();
	initImageGamemapTiles();

	initImageInterface();

	initImageZergUnits();
}

void sceneInit::initSound(void)
{

}

void sceneInit::initImageMaptoolTiles(void)
{
	TCHAR strKey[128] = L"";
	TCHAR strFile[128] = L"";

	//terrain-Asphlat
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"maptool-terrain-Asphlat-%02d", i);
		_stprintf(strFile, L"image/maptool/tiles/terrain-Asphlat/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, MAPTOOL_TILESIZE, MAPTOOL_TILESIZE);
	}

	//terrain-Dirt
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"maptool-terrain-Dirt-%02d", i);
		_stprintf(strFile, L"image/maptool/tiles/terrain-Dirt/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, MAPTOOL_TILESIZE, MAPTOOL_TILESIZE);
	}

	//terrain-Grass
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"maptool-terrain-Grass-%02d", i);
		_stprintf(strFile, L"image/maptool/tiles/terrain-Grass/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, MAPTOOL_TILESIZE, MAPTOOL_TILESIZE);
	}

	//terrain-HighDirt
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"maptool-terrain-HighDirt-%02d", i);
		_stprintf(strFile, L"image/maptool/tiles/terrain-HighDirt/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, MAPTOOL_TILESIZE, MAPTOOL_TILESIZE);
	}

	//terrain-HighGrass
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"maptool-terrain-HighGrass-%02d", i);
		_stprintf(strFile, L"image/maptool/tiles/terrain-HighDirt/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, MAPTOOL_TILESIZE, MAPTOOL_TILESIZE);
	}

	//terrain-Mud
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"maptool-terrain-Mud-%02d", i);
		_stprintf(strFile, L"image/maptool/tiles/terrain-Mud/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, MAPTOOL_TILESIZE, MAPTOOL_TILESIZE);
	}

	//terrain-RockyGround
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"maptool-terrain-RockyGround-%02d", i);
		_stprintf(strFile, L"image/maptool/tiles/terrain-RockyGround/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, MAPTOOL_TILESIZE, MAPTOOL_TILESIZE);
	}

	//terrain-Structure
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"maptool-terrain-Structure-%02d", i);
		_stprintf(strFile, L"image/maptool/tiles/terrain-Structure/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, MAPTOOL_TILESIZE, MAPTOOL_TILESIZE);
	}

	//terrain-Water
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"maptool-terrain-Water-%02d", i);
		_stprintf(strFile, L"image/maptool/tiles/terrain-Water/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, MAPTOOL_TILESIZE, MAPTOOL_TILESIZE);
	}
}

void sceneInit::initImageGamemapTiles(void)
{
	TCHAR strKey[128] = L"";
	TCHAR strFile[128] = L"";

	_loading->loadImage(L"gamemap-fog", L"image/gamemap/fog.bmp", GAMEMAP_TILESIZE, GAMEMAP_TILESIZE, false, RGB(0, 0, 0), true);

	//terrain-Asphlat
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"gamemap-terrain-Asphlat-%02d", i);
		_stprintf(strFile, L"image/gamemap/tiles/terrain-Asphlat/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, GAMEMAP_TILESIZE, GAMEMAP_TILESIZE);
	}

	//terrain-Dirt
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"gamemap-terrain-Dirt-%02d", i);
		_stprintf(strFile, L"image/gamemap/tiles/terrain-Dirt/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, GAMEMAP_TILESIZE, GAMEMAP_TILESIZE);
	}

	//terrain-Grass
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"gamemap-terrain-Grass-%02d", i);
		_stprintf(strFile, L"image/gamemap/tiles/terrain-Grass/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, GAMEMAP_TILESIZE, GAMEMAP_TILESIZE);
	}

	//terrain-HighDirt
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"gamemap-terrain-HighDirt-%02d", i);
		_stprintf(strFile, L"image/gamemap/tiles/terrain-HighDirt/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, GAMEMAP_TILESIZE, GAMEMAP_TILESIZE);
	}

	//terrain-HighGrass
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"gamemap-terrain-HighGrass-%02d", i);
		_stprintf(strFile, L"image/gamemap/tiles/terrain-HighDirt/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, GAMEMAP_TILESIZE, GAMEMAP_TILESIZE);
	}

	//terrain-Mud
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"gamemap-terrain-Mud-%02d", i);
		_stprintf(strFile, L"image/gamemap/tiles/terrain-Mud/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, GAMEMAP_TILESIZE, GAMEMAP_TILESIZE);
	}

	//terrain-RockyGround
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"gamemap-terrain-RockyGround-%02d", i);
		_stprintf(strFile, L"image/gamemap/tiles/terrain-RockyGround/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, GAMEMAP_TILESIZE, GAMEMAP_TILESIZE);
	}

	//terrain-Structure
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"gamemap-terrain-Structure-%02d", i);
		_stprintf(strFile, L"image/gamemap/tiles/terrain-Structure/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, GAMEMAP_TILESIZE, GAMEMAP_TILESIZE);
	}

	//terrain-Water
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"gamemap-terrain-Water-%02d", i);
		_stprintf(strFile, L"image/gamemap/tiles/terrain-Water/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, GAMEMAP_TILESIZE, GAMEMAP_TILESIZE);
	}
}

void sceneInit::initImageInterface(void)
{
	//cursor
	_loading->loadFrameImage(L"cursor-Idle", L"image/interface/cursor-Idle.bmp", 100, 21, 5, 1, true, RGB(255, 0, 255));
	_loading->loadImage(L"cursor-Dragging", L"image/interface/cursor-Dragging.bmp", 18, 22, true, RGB(255, 0, 255));
	_loading->loadFrameImage(L"cursor-onme", L"image/interface/cursor-onme.bmp", 574, 41, 14, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage(L"cursor-onneutral", L"image/interface/cursor-onneutral.bmp", 574, 41, 14, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage(L"cursor-onenemy", L"image/interface/cursor-onenemy.bmp", 574, 41, 14, 1, true, RGB(255, 0, 255));

	//interface
	_loading->loadImage(L"interfaceZ", L"image/interface/interface-Z.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage(L"interfaceT", L"image/interface/interface-T.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage(L"interfaceP", L"image/interface/interface-P.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	//commands
	_loading->loadImage(L"command-attack0",		L"image/interface/command/attack0.bmp",		34, 33);
	_loading->loadImage(L"command-attack1",		L"image/interface/command/attack1.bmp",		34, 33);
	_loading->loadImage(L"command-build0",		L"image/interface/command/build0.bmp",		34, 33);
	_loading->loadImage(L"command-build1",		L"image/interface/command/build1.bmp",		34, 33);
	_loading->loadImage(L"command-burrow0",		L"image/interface/command/burrow0.bmp",		34, 33);
	_loading->loadImage(L"command-burrow2",		L"image/interface/command/burrow2.bmp",		34, 33);
	_loading->loadImage(L"command-gather0",		L"image/interface/command/gather0.bmp",		34, 33);
	_loading->loadImage(L"command-gather1",		L"image/interface/command/gather1.bmp",		34, 33);
	_loading->loadImage(L"command-move0",		L"image/interface/command/move0.bmp",		34, 33);
	_loading->loadImage(L"command-move1",		L"image/interface/command/move1.bmp",		34, 33);
	_loading->loadImage(L"command-return0",		L"image/interface/command/return0.bmp",		34, 33);
	_loading->loadImage(L"command-return1",		L"image/interface/command/return1.bmp",		34, 33);
	_loading->loadImage(L"command-stop0",		L"image/interface/command/stop0.bmp",		34, 33);
	_loading->loadImage(L"command-stop1",		L"image/interface/command/stop1.bmp",		34, 33);
	_loading->loadImage(L"command-unburrow0",	L"image/interface/command/unburrow0.bmp",	34, 33);
}

void sceneInit::initImageZergUnits(void)
{
	TCHAR strKey[100];
	TCHAR strFile[100];

	//Body---------------------------------------------------------------------------------------------------------------------------------
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		//drone
		_stprintf(strKey, L"ZU-droneBody%d", i);
		_stprintf(strFile, L"image/zerg/unit/drone/droneBody%d.bmp", i);
		_loading->loadFrameImage(strKey, strFile, 576, 1008, 8, 14, true, RGB(255, 0, 255));


	}

	//Stat---------------------------------------------------------------------------------------------------------------------------------
	//drone
	_loading->loadFrameImage(L"ZU-droneStat1", L"image/zerg/unit/drone/droneStat1.bmp", 59, 51, 1, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage(L"ZU-droneStat2", L"image/zerg/unit/drone/droneStat2.bmp", 33, 34, 1, 1);

}

