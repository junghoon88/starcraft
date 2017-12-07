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

	initImageTiles();
}

void sceneInit::initSound(void)
{

}

void sceneInit::initImageTiles(void)
{
	TCHAR strKey[128] = L"";
	TCHAR strFile[128] = L"";

	//terrain-Asphlat
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"terrain-Asphlat-%02d", i);
		_stprintf(strFile, L"image/tiles/terrain-Asphlat/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, TILESIZE, TILESIZE);
	}

	//terrain-Dirt
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"terrain-Dirt-%02d", i);
		_stprintf(strFile, L"image/tiles/terrain-Dirt/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, TILESIZE, TILESIZE);
	}

	//terrain-Grass
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"terrain-Grass-%02d", i);
		_stprintf(strFile, L"image/tiles/terrain-Grass/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, TILESIZE, TILESIZE);
	}

	//terrain-HighDirt
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"terrain-HighDirt-%02d", i);
		_stprintf(strFile, L"image/tiles/terrain-HighDirt/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, TILESIZE, TILESIZE);
	}

	//terrain-HighGrass
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"terrain-HighGrass-%02d", i);
		_stprintf(strFile, L"image/tiles/terrain-HighDirt/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, TILESIZE, TILESIZE);
	}

	//terrain-Mud
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"terrain-Mud-%02d", i);
		_stprintf(strFile, L"image/tiles/terrain-Mud/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, TILESIZE, TILESIZE);
	}

	//terrain-RockyGround
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"terrain-RockyGround-%02d", i);
		_stprintf(strFile, L"image/tiles/terrain-RockyGround/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, TILESIZE, TILESIZE);
	}

	//terrain-Structure
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"terrain-Structure-%02d", i);
		_stprintf(strFile, L"image/tiles/terrain-Structure/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, TILESIZE, TILESIZE);
	}

	//terrain-Water
	for (int i = 0; i < 1; i++)
	{
		_stprintf(strKey, L"terrain-Water-%02d", i);
		_stprintf(strFile, L"image/tiles/terrain-Water/%02d.bmp", i);
		_loading->loadImage(strKey, strFile, TILESIZE, TILESIZE);
	}
}

