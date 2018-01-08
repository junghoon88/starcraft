#include "stdafx.h"
#include "nrGas.h"
#include "tileNode.h"

nrGas::nrGas(int tilex, int tiley)
	: _img(NULL)
{
	_rcTile = RectMake(tilex, tiley, OBJ_GAS_WIDTH, OBJ_GAS_HEIGHT);
	_rcBody = RectMultiply(_rcTile, TILESIZE);

	_img = IMAGEMANAGER->findImage(L"NeutralResource-Gas");
}


nrGas::~nrGas() {}

HRESULT nrGas::init(UINT amount)
{ 
	_stprintf(_baseStatus.name, L"Vespene Geyser");
	_baseStatus.imgStat1 = IMAGEMANAGER->findImage(L"NeutralResource-Gas-Stat1");

	_isNrGas = true;

	_amountGas = amount;

	return S_OK; 
}
void nrGas::release(void) {}
void nrGas::update(void) {}
void nrGas::render(void) {}
void nrGas::getChar(WPARAM wParam) {}
void nrGas::updateBattleStatus(void) {}
void nrGas::updatePosition(void) {}
void nrGas::updateImageFrame(void) {}
