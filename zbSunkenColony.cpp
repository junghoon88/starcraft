#include "stdafx.h"
#include "zbSunkenColony.h"

#include "zergDefine.h"
#include "player.h"


zbSunkenColony::zbSunkenColony(PLAYER playerNum)
{
	_valid = true;

	//플레이어 정보
	_playerNum = playerNum;

	//종족
	_race = RACES_ZERG;

	//유닛인지 건물인지
	_isBuilding = true;

	//유닛 고유 번호
	_buildingNumZ = BUILDINGNUM_ZERG_SUNKENCOLONY;

}


zbSunkenColony::~zbSunkenColony()
{
}

HRESULT zbSunkenColony::init(POINT ptTile)
{
	initBaseStatus();
	initBattleStatus(ptTile);


	return S_OK;
}


void zbSunkenColony::initBaseStatus(void)
{
	//Properties
	_stprintf(_baseStatus.name, L"Zerg SunkenColony");

	TCHAR strKey[100];
	_stprintf(strKey, L"ZB-sunkenColonyBody%d", _playerNum);
	_baseStatus.imgBody = IMAGEMANAGER->findImage(strKey);
	_baseStatus.imgFace = NULL;
	_baseStatus.imgStat1 = IMAGEMANAGER->findImage(L"ZB-sunkenColonyStat1");
	_baseStatus.imgStat2 = NULL;

	_baseStatus.maxHP = 300.0f;

	_baseStatus.useSH = FALSE;
	_baseStatus.maxSH = 0.0f;

	_baseStatus.useMP = FALSE;
	_baseStatus.maxMP = 0.0f;

	_baseStatus.sight = 10.0f;
	_baseStatus.detector = FALSE;

	_baseStatus.isAir = FALSE;

	_baseStatus.unitSize = UNITSIZE_LARGE;
	_baseStatus.transportslots = 0;
	_baseStatus.armor = 2;
	//_baseStatus.armorPlus = 1;				

	//combat
	_baseStatus.sameGWAW = FALSE;

	_baseStatus.GWable = TRUE;
	_baseStatus.GWAttackType = ATTACKTYPE_ZERG_WORKER;	
	_stprintf(_baseStatus.GWname, L"Subterranean Tentacle");
	_baseStatus.GWdamage = 40;							
	_baseStatus.GWdamagePlus = 0;						
	_baseStatus.GWmaxHit = 1;							
	_baseStatus.GWdamageType = DAMAGETYPE_EXPLOSIVE;		
	_baseStatus.GWcooldown = 32.0f;						
	_baseStatus.GWattackRange = 7.0f;					

	_baseStatus.AWable = FALSE;

	_baseStatus.commands[0] = COMMAND_NONE;
	_baseStatus.commands[1] = COMMAND_STOP;
	_baseStatus.commands[2] = COMMAND_ATTACK;
	_baseStatus.commands[3] = COMMAND_NONE;
	_baseStatus.commands[4] = COMMAND_NONE;
	_baseStatus.commands[5] = COMMAND_NONE;
	_baseStatus.commands[6] = COMMAND_NONE;
	_baseStatus.commands[7] = COMMAND_NONE;
	_baseStatus.commands[8] = COMMAND_NONE;

}
void zbSunkenColony::initBattleStatus(POINT ptTile)
{
	//BattleStatus
	_battleStatus.curCommand = COMMAND_NONE;
	_battleStatus.clicked = false;
	_battleStatus.curHP = _baseStatus.maxHP;			//현재 HP
	_battleStatus.maxHP = _baseStatus.maxHP;			//최대 HP

	POINT buildTileSize = BUILDSIZE_SUNKENCOLONY;

	_battleStatus.ptTile = ptTile;
	_battleStatus.rcBody = RectMake(ptTile.x * TILESIZE, ptTile.y * TILESIZE, buildTileSize.x * TILESIZE, buildTileSize.y * TILESIZE);
	_battleStatus.pt.set((_battleStatus.rcBody.left + _battleStatus.rcBody.right) * 0.5f, (_battleStatus.rcBody.top + _battleStatus.rcBody.bottom) * 0.5f);
	_battleStatus.rcTile = RectMake(ptTile.x, ptTile.y, buildTileSize.x, buildTileSize.y);
	_battleStatus.rcEllipse = _battleStatus.rcBody;
}

void zbSunkenColony::release(void)
{

}

void zbSunkenColony::update(void)
{
	Building::update();

}

void zbSunkenColony::render(int imgOffsetX, int imgOffsetY)
{
	Building::render();

}

