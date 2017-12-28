#include "stdafx.h"
#include "nrMineral.h"
#include "tileNode.h"


nrMineral::nrMineral(int tilex, int tiley, UINT amount, int type)
	: _img(NULL)
{
	_rcTile = RectMake(tilex, tiley, OBJ_MINERAL_WIDTH, OBJ_MINERAL_HEIGHT);
	_rcBody = RectMultiply(_rcTile, TILESIZE);

	_amount = amount;

	switch (type)
	{
	case 1: _img = IMAGEMANAGER->findImage(L"NeutralResource-Mineral1"); break;
	case 2: _img = IMAGEMANAGER->findImage(L"NeutralResource-Mineral2"); break;
	case 3: _img = IMAGEMANAGER->findImage(L"NeutralResource-Mineral3"); break;
	}
}


nrMineral::~nrMineral()
{
}
