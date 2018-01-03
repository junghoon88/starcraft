#include "stdafx.h"
#include "zuHydralisk.h"
#include "zergDefine.h"
#include "player.h"


zuHydralisk::zuHydralisk(PLAYER playerNum)
{
	_valid = true;

	//플레이어 정보
	_playerNum = playerNum;

	//종족
	_race = RACES_ZERG;

	//유닛인지 건물인지
	_isBuilding = false;

	//유닛 고유 번호
	_unitNumZ = UNITNUM_ZERG_HYDRALISK;

}


zuHydralisk::~zuHydralisk()
{
}

HRESULT zuHydralisk::init(POINT pt)
{
	initBaseStatus();
	initBattleStatus(pt);



	updatePosition();

	updateBattleStatus();


	return S_OK;
}

void zuHydralisk::initBaseStatus(void)
{
	_stprintf(_baseStatus.name, L"Zerg Hydralisk");

	TCHAR strKey[100];
	_stprintf(strKey, L"ZU-hydralisk-Body%d", _playerNum);
	_baseStatus.imgBody = IMAGEMANAGER->findImage(strKey);
	_baseStatus.imgFace = IMAGEMANAGER->findImage(L"ZU-hydralisk-Face");
	_baseStatus.imgStat1 = IMAGEMANAGER->findImage(L"ZU-hydralisk-Stat1");
	_baseStatus.imgStat2 = IMAGEMANAGER->findImage(L"ZU-hydralisk-Stat2");

	_baseStatus.unitControl = 1.0f;

	_baseStatus.maxHP = 80.0f;

	_baseStatus.useSH = FALSE;
	_baseStatus.maxSH = 0.0f;

	_baseStatus.useMP = FALSE;
	_baseStatus.maxMP = 0.0f;

	_baseStatus.sight = 6.0f;
	_baseStatus.detector = FALSE;

	_baseStatus.isAir = FALSE;
	_baseStatus.moveSpeed = 3.71f; //업글시 5.57

	_baseStatus.unitSize = UNITSIZE_MEDIUM;
	_baseStatus.transportslots = 2;
	_baseStatus.armor = 0;
	_baseStatus.armorPlus = 1;


	_baseStatus.sameGWAW = TRUE;

	_baseStatus.GWable = TRUE;
	_baseStatus.GWAttackType = ATTACKTYPE_ZERG_MISSILE;
	_stprintf(_baseStatus.GWname, L"Needle Spines");
	_baseStatus.GWdamage = 10;
	_baseStatus.GWdamagePlus = 1;
	_baseStatus.GWmaxHit = 1;
	_baseStatus.GWdamageType = DAMAGETYPE_EXPLOSIVE;
	_baseStatus.GWcooldown = 15.0;
	_baseStatus.GWattackRange = 4.0f; //업글시 5

	_baseStatus.AWable = TRUE;
	_baseStatus.AWAttackType = ATTACKTYPE_ZERG_MISSILE;
	_stprintf(_baseStatus.AWname, L"Needle Spines");
	_baseStatus.AWdamage = 10;
	_baseStatus.AWdamagePlus = 1;
	_baseStatus.AWmaxHit = 1;
	_baseStatus.AWdamageType = DAMAGETYPE_EXPLOSIVE;
	_baseStatus.AWcooldown = 15.0;
	_baseStatus.AWattackRange = 4.0f; //업글시 5

	_baseStatus.commands[0] = COMMAND_MOVE;
	_baseStatus.commands[1] = COMMAND_STOP;
	_baseStatus.commands[2] = COMMAND_ATTACK;
	_baseStatus.commands[3] = COMMAND_PATROL;
	_baseStatus.commands[4] = COMMAND_HOLD;
	_baseStatus.commands[5] = COMMAND_NONE;
	_baseStatus.commands[6] = COMMAND_NONE;
	_baseStatus.commands[7] = COMMAND_NONE;
	_baseStatus.commands[8] = COMMAND_BURROW;
}
void zuHydralisk::initBattleStatus(POINT pt)
{
	//BattleStatus
	_battleStatus.unitState = UNITSTATE_STOP;
	_battleStatus.curCommand = COMMAND_STOP;
	_battleStatus.clicked = false;
	_battleStatus.curHP = _baseStatus.maxHP;
	_battleStatus.maxHP = _baseStatus.maxHP;

	_battleStatus.pt.set((float)pt.x, (float)pt.y);
	_battleStatus.moveSpeed = _baseStatus.moveSpeed;
	_battleStatus.angleDeg = 315.0f;
	_battleStatus.direction;
}


void zuHydralisk::release(void)
{

}

void zuHydralisk::update(void)
{
	Unit::update();
}

void zuHydralisk::render(void)
{
	Unit::render();
}

void zuHydralisk::updatePosition(void)
{
	POINT pt = _battleStatus.pt.toPoint();
	_battleStatus.ptTile = { pt.x / TILESIZE, pt.y / TILESIZE };			//현재위치한 타일

	POINT unitsize = UNITSIZE_ZERG_HYDRALISK;

	_battleStatus.rcBody = RectMakeCenter(pt.x, pt.y, unitsize.x, unitsize.y);			//유닛 몸체
	_battleStatus.rcEllipse = _battleStatus.rcBody;		//클릭했을때 보여주는 타원
	_battleStatus.rcEllipse.top += unitsize.y / 2;
}

void zuHydralisk::updateBattleStatus(void)
{
	Unit::updateBattleStatus();


}

void zuHydralisk::updateImageFrame(void)
{
	Unit::setImageFrameForAngle();
}

void zuHydralisk::procCommands(void)
{
	Unit::procCommands();

}
