#include "stdafx.h"
#include "zbExtractor.h"

#include "zergDefine.h"
#include "player.h"

#include "nrGas.h"

zbExtractor::zbExtractor(PLAYER playerNum)
	: _nrGas(NULL)
{
	_valid = true;

	//플레이어 정보
	_playerNum = playerNum;

	//종족
	_race = RACES_ZERG;

	//유닛인지 건물인지
	_isBuilding = true;

	//유닛 고유 번호
	_buildingNumZ = BUILDINGNUM_ZERG_EXTRACTOR;
}


zbExtractor::~zbExtractor()
{
}

HRESULT zbExtractor::init(POINT ptTile)
{
	initBaseStatus();
	initBattleStatus(ptTile);

	return S_OK;
}

void zbExtractor::initBaseStatus(void)
{
	//Properties
	_stprintf(_baseStatus.name, L"Zerg Extractor");

	TCHAR strKey[100];
	_stprintf(strKey, L"ZB-extractor-Body%d", _playerNum);
	_baseStatus.imgBody = IMAGEMANAGER->findImage(strKey);
	_baseStatus.imgFace = IMAGEMANAGER->findImage(L"ZB-Face");
	_baseStatus.imgStat1 = IMAGEMANAGER->findImage(L"ZB-extractor-Stat1");
	_baseStatus.imgStat2 = NULL;

	_baseStatus.maxHP = 750.0f;

	_baseStatus.useSH = FALSE;
	_baseStatus.maxSH = 0.0f;

	_baseStatus.useMP = FALSE;
	_baseStatus.maxMP = 0.0f;

	_baseStatus.sight = 7.0f;
	_baseStatus.detector = FALSE;

	_baseStatus.isAir = FALSE;

	_baseStatus.unitSize = UNITSIZE_LARGE;
	_baseStatus.transportslots = 0;
	_baseStatus.armor = 1;
	//_baseStatus.armorPlus = 1;				

	//combat
	_baseStatus.sameGWAW = FALSE;
	_baseStatus.GWable = FALSE;
	_baseStatus.AWable = FALSE;

}
void zbExtractor::initBattleStatus(POINT ptTile)
{
	//BattleStatus
	_battleStatus.curCommand = COMMAND_NONE;
	_battleStatus.clicked = false;
	_battleStatus.curHP = _baseStatus.maxHP;			//현재 HP
	_battleStatus.maxHP = _baseStatus.maxHP;			//최대 HP

	POINT buildTileSize = BUILDSIZE_EXTRACTOR;

	_battleStatus.ptTile = ptTile;
	_battleStatus.rcBody = RectMake(ptTile.x * TILESIZE, ptTile.y * TILESIZE, buildTileSize.x * TILESIZE, buildTileSize.y * TILESIZE);
	_battleStatus.pt.set((_battleStatus.rcBody.left + _battleStatus.rcBody.right) * 0.5f, (_battleStatus.rcBody.top + _battleStatus.rcBody.bottom) * 0.5f);
	_battleStatus.rcTile = RectMake(ptTile.x, ptTile.y, buildTileSize.x, buildTileSize.y);
	_battleStatus.rcEllipse = _battleStatus.rcBody;
}

void zbExtractor::release(void)
{
	if (_nrGas)
	{
		_nrGas->setAmountGas(_amountGas);
	}
}

void zbExtractor::update(void)
{
	Building::update();

}

void zbExtractor::render(int imgOffsetX, int imgOffsetY)
{
	POINT imgOffset = BUILDIMAGEOFFSET_EXTRACTOR;
	Building::render(imgOffset.x * TILESIZE, imgOffset.y * TILESIZE);

}

void zbExtractor::updateBattleStatus(void)
{

}
void zbExtractor::updatePosition(void)
{

}

void zbExtractor::updateImageFrame(void)
{

}

void zbExtractor::updateProcessing(void)
{
	Building::updateProcessing();

}

void zbExtractor::updateCommandSet(void)
{

}


void zbExtractor::procCommands(void)
{

}


void zbExtractor::findNrGas(void)
{
	_nrGas = _player->getGamemap()->findGas(_battleStatus.ptTile);

	_isNrGas = true;
	_amountGas = _nrGas->getAmountGas();
}
