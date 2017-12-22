#include "stdafx.h"
#include "nrGas.h"
#include "tileNode.h"


nrGas::nrGas(int tilex, int tiley, UINT amount)
	: _img(NULL)
{
	_rcTile = RectMake(tilex, tiley, OBJ_MINERAL_WIDTH, OBJ_MINERAL_HEIGHT);
	_rcBody = RectMultiply(_rcTile, GAMEMAP_TILESIZE);

	_amount = amount;

	_img = IMAGEMANAGER->findImage(L"NeutralResource-Gas");
}


nrGas::~nrGas()
{
}
