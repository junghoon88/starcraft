#include "stdafx.h"
#include "fog.h"

#include "player.h"
#include "gameMap.h"


fog::fog()
	: _imgFog(NULL)
{
	ZeroMemory(&_fogs, sizeof(tagFog)*TILEX*TILEY);

	_alpha = 96;
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
	for (int i = 0; i < TILEX; i++)
	{
		for (int j = 0; j < TILEY; j++)
		{
			if (_fogs[i][j].level != FOGLEVEL_BLACK)
			{
				_fogs[i][j].level = FOGLEVEL_GRAY;
			}
		}
	}

	for (int i = 0; i < _myPlayer->getUnits().size(); i++)
	{
		addSightArea(_myPlayer->getUnits()[i]->getBattleStatus().pt.toPoint(), _myPlayer->getUnits()[i]->getBaseStatus().sight, _myPlayer->getUnits()[i]->getBaseStatus().detector);
	}

	for (int i = 0; i < _myPlayer->getBuildings().size(); i++)
	{
		addSightArea(_myPlayer->getBuildings()[i]->getBattleStatus().pt.toPoint(), _myPlayer->getBuildings()[i]->getBaseStatus().sight, _myPlayer->getUnits()[i]->getBaseStatus().detector);
	}



	for (int i = 0; i < _vObjectDetectRect.size(); i++)
	{
		RECT rc = _vObjectDetectRect[i];
		for (int x = rc.left; x <= rc.right; x++)
		{
			for (int y = rc.top; y <= rc.bottom; y++)
			{
				if (x < 0) continue;
				if (x >= TILEX) continue;
				if (y < 0) continue;
				if (y >= TILEY) continue;

				if (_fogs[x][y].level >= FOGLEVEL_DETECT) continue;

				_fogs[x][y].level = FOGLEVEL_DETECT;
			}
		}
	}
	_vObjectDetectRect.clear();


	for (int i = 0; i < _vObjectViewRect.size(); i++)
	{
		RECT rc = _vObjectViewRect[i];
		for (int x = rc.left; x <= rc.right; x++)
		{
			for (int y = rc.top; y <= rc.bottom; y++)
			{
				if (x < 0) continue;
				if (x >= TILEX) continue;
				if (y < 0) continue;
				if (y >= TILEY) continue;

				if (_fogs[x][y].level >= FOGLEVEL_VIEW) continue;

				_fogs[x][y].level = FOGLEVEL_VIEW;
			}
		}
	}
	_vObjectViewRect.clear();

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

			if (_fogs[idX][idY].level == FOGLEVEL_BLACK)
			{
				RENDERMANAGER->insertImg(ZORDER_FOG, _imgFog, idX*TILESIZE - cameraX, idY*TILESIZE - cameraY);
				//_imgFog->render(getMemDC(), idX*TILESIZE - cameraX, idY*TILESIZE - cameraY);
			}
			else if (_fogs[idX][idY].level == FOGLEVEL_GRAY)
			{
				RENDERMANAGER->insertImgAlpha(ZORDER_FOG, _imgFog, idX*TILESIZE - cameraX, idY*TILESIZE - cameraY, _alpha);
				//_imgFog->alphaRender(getMemDC(), idX*TILESIZE - cameraX, idY*TILESIZE - cameraY, _alpha);
			}

		}
	}


}

void fog::addSightArea(POINT pt, FLOAT sight, BOOL detect)
{
	POINT ptTIle;

	ptTIle.x = pt.x / TILESIZE;
	ptTIle.y = pt.y / TILESIZE;

	if (detect)
	{
		RECT rc = RectMakeCenter(ptTIle.x, ptTIle.y, sight * 2, sight * 2);
		_vObjectDetectRect.push_back(rc);
	}
	else
	{
		RECT rc = RectMakeCenter(ptTIle.x, ptTIle.y, sight * 2, sight * 2);
		_vObjectViewRect.push_back(rc);
	}
}
