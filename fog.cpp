#include "stdafx.h"
#include "fog.h"


fog::fog()
	: _imgFog(NULL)
{
	ZeroMemory(&_fogs, sizeof(tagFog)*TILEX*TILEY);

}


fog::~fog()
{
}


HRESULT fog::init(void)
{
	_imgFog = IMAGEMANAGER->findImage(L"gamemap-fog");

	for (int y = 0; y < TILEY; y++)
	{
		for (int x = 0; x < TILEX; x++)
		{
			_fogs[x][y].rcFog = RectMake(x*TILESIZE, y*TILESIZE, TILESIZE, TILESIZE);
		}
	}

	return S_OK;
}

void fog::release(void)
{
}

void fog::update(void)
{
}

void fog::render(void)
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
			
			if (_imgFog == NULL) continue;

			_imgFog->render(getMemDC(), idX*TILESIZE - cameraX, idY*TILESIZE - cameraY);
		}
	}
}