#include "stdafx.h"
#include "zuGuadian.h"
#include "zergDefine.h"
#include "player.h"


zuGuadian::zuGuadian(PLAYER playerNum)
{
	_valid = true;

	//플레이어 정보
	_playerNum = playerNum;

	//종족
	_race = RACES_ZERG;

	//유닛인지 건물인지
	_isBuilding = false;

	//유닛 고유 번호
	_unitNumZ = UNITNUM_ZERG_GUADIAN;

	_zergProductionInfo = new zergProductionInfo;

}


zuGuadian::~zuGuadian()
{
}

HRESULT zuGuadian::init(POINT pt)
{
	initBaseStatus();
	initBattleStatus(pt);



	updatePosition();

	updateBattleStatus();

	return S_OK;
}

void zuGuadian::initBaseStatus(void)
{
	_stprintf(_baseStatus.name, L"Zerg Guadian");

	TCHAR strKey[100];
	_stprintf(strKey, L"ZU-guadianBody%d", _playerNum);
	_baseStatus.imgBody = IMAGEMANAGER->findImage(strKey);
	_baseStatus.imgFace = NULL;
	_baseStatus.imgStat1 = IMAGEMANAGER->findImage(L"ZU-guadianStat1");
	_baseStatus.imgStat2 = IMAGEMANAGER->findImage(L"ZU-guadianStat2");

	_baseStatus.unitControl = 2.0f;

	_baseStatus.maxHP = 25.0f;

	_baseStatus.useSH = FALSE;
	_baseStatus.maxSH = 0.0f;

	_baseStatus.useMP = FALSE;
	_baseStatus.maxMP = 0.0f;

	_baseStatus.sight = 11.0f;
	_baseStatus.detector = FALSE;

	_baseStatus.isAir = TRUE;
	_baseStatus.moveSpeed = 2.5f;

	_baseStatus.unitSize = UNITSIZE_LARGE;
	_baseStatus.transportslots = 0;
	_baseStatus.armor = 2;
	_baseStatus.armorPlus = 1;


	_baseStatus.sameGWAW = FALSE;

	_baseStatus.GWable = TRUE;
	_baseStatus.AWAttackType = ATTACKTYPE_ZERG_FLYING;
	_stprintf(_baseStatus.AWname, L"Acid Spore");
	_baseStatus.AWdamage = 20;
	_baseStatus.AWdamagePlus = 2;
	_baseStatus.AWmaxHit = 1;
	_baseStatus.AWdamageType = DAMAGETYPE_NORMAL;
	_baseStatus.AWcooldown = 30.0;
	_baseStatus.AWattackRange = 8.0f;

	_baseStatus.AWable = FALSE;

	_baseStatus.commands[0] = COMMAND_MOVE;
	_baseStatus.commands[1] = COMMAND_STOP;
	_baseStatus.commands[2] = COMMAND_ATTACK;
	_baseStatus.commands[3] = COMMAND_PATROL;
	_baseStatus.commands[4] = COMMAND_HOLD;
	_baseStatus.commands[5] = COMMAND_NONE;
	_baseStatus.commands[6] = COMMAND_NONE;
	_baseStatus.commands[7] = COMMAND_NONE;
	_baseStatus.commands[8] = COMMAND_NONE;
}
void zuGuadian::initBattleStatus(POINT pt)
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


void zuGuadian::release(void)
{
	SAFE_DELETE(_zergProductionInfo);
}

void zuGuadian::update(void)
{
	Unit::update();
}

void zuGuadian::render(void)
{
	Unit::render();
}

void zuGuadian::updatePosition(void)
{
	POINT pt = _battleStatus.pt.toPoint();
	_battleStatus.ptTile = { pt.x / TILESIZE, pt.y / TILESIZE };			//현재위치한 타일

	POINT unitsize = UNITSIZE_ZERG_GUADIAN;

	_battleStatus.rcBody = RectMakeCenter(pt.x, pt.y, unitsize.x, unitsize.y);			//유닛 몸체
	_battleStatus.rcEllipse = _battleStatus.rcBody;		//클릭했을때 보여주는 타원
	_battleStatus.rcEllipse.top += unitsize.y / 2;
}

void zuGuadian::updateBattleStatus(void)
{
	Unit::updateBattleStatus();


}

void zuGuadian::updateImageFrame(void)
{
	Unit::setImageFrameForAngle();
}

void zuGuadian::procCommands(void)
{
	Unit::procCommands();

}
