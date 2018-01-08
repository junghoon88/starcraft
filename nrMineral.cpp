#include "stdafx.h"
#include "nrMineral.h"
#include "tileNode.h"

nrMineral::nrMineral(int tilex, int tiley, int type)
	: _img(NULL)
{
	_rcTile = RectMake(tilex, tiley, OBJ_MINERAL_WIDTH, OBJ_MINERAL_HEIGHT);
	_rcBody = RectMultiply(_rcTile, TILESIZE);

	switch (type)
	{
	case 1: _img = IMAGEMANAGER->findImage(L"NeutralResource-Mineral1"); break;
	case 2: _img = IMAGEMANAGER->findImage(L"NeutralResource-Mineral2"); break;
	case 3: _img = IMAGEMANAGER->findImage(L"NeutralResource-Mineral3"); break;
	}
}

nrMineral::~nrMineral() {}

HRESULT nrMineral::init(UINT amount) 
{
	_stprintf(_baseStatus.name, L"Mineral Field");
	_baseStatus.imgStat1 = IMAGEMANAGER->findImage(L"NeutralResource-Mineral-Stat1");

	_battleStatus.rcBody = _rcBody;
	_battleStatus.rcTile = _rcTile;
	_battleStatus.pt.x = (_rcBody.left + _rcBody.right) / 2;
	_battleStatus.pt.y = (_rcBody.top + _rcBody.bottom) / 2;

	_battleStatus.ptTile.x = (int)_battleStatus.pt.x / TILESIZE;
	_battleStatus.ptTile.y = (int)_battleStatus.pt.y / TILESIZE;


	_isNrMineral = true;

	_amountMineral = amount;

	return S_OK; 
}
void nrMineral::release(void) {}	
void nrMineral::update(void) {}	
void nrMineral::render(void) {}	
void nrMineral::getChar(WPARAM wParam) {}
void nrMineral::updateBattleStatus(void) {}
void nrMineral::updatePosition(void) {}
void nrMineral::updateImageFrame(void) {}
