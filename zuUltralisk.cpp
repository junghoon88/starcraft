#include "stdafx.h"
#include "zuUltralisk.h"
#include "zergDefine.h"
#include "player.h"


zuUltralisk::zuUltralisk(PLAYER playerNum)
{
	_valid = true;

	//플레이어 정보
	_playerNum = playerNum;

	//종족
	_race = RACES_ZERG;

	//유닛인지 건물인지
	_isBuilding = false;

	//유닛 고유 번호
	_unitNumZ = UNITNUM_ZERG_ULTRALISK;

	_zergProductionInfo = new zergProductionInfo;
}


zuUltralisk::~zuUltralisk()
{
}

HRESULT zuUltralisk::init(POINT pt)
{
	initBaseStatus();
	initBattleStatus(pt);



	updatePosition();

	updateBattleStatus();


	return S_OK;
}


void zuUltralisk::initBaseStatus(void)
{
	_stprintf(_baseStatus.name, L"Zerg Ultralisk");

	TCHAR strKey[100];
	_stprintf(strKey, L"ZU-ultralisk-Body%d", _playerNum);
	_baseStatus.imgBody = IMAGEMANAGER->findImage(strKey);
	_baseStatus.imgFace = NULL;
	_baseStatus.imgStat1 = IMAGEMANAGER->findImage(L"ZU-ultralisk-Stat1");
	_baseStatus.imgStat2 = IMAGEMANAGER->findImage(L"ZU-ultralisk-Stat2");

	_baseStatus.unitControl = 4.0f;

	_baseStatus.maxHP = 400.0f;

	_baseStatus.useSH = FALSE;
	_baseStatus.maxSH = 0.0f;

	_baseStatus.useMP = FALSE;
	_baseStatus.maxMP = 0.0f;

	_baseStatus.sight = 7.0f;
	_baseStatus.detector = FALSE;

	_baseStatus.isAir = FALSE;
	_baseStatus.moveSpeed = 5.4f; //업글시 8.1

	_baseStatus.unitSize = UNITSIZE_LARGE;
	_baseStatus.transportslots = 4;
	_baseStatus.armor = 1;		//업글시 +2
	_baseStatus.armorPlus = 1;


	_baseStatus.sameGWAW = FALSE;

	_baseStatus.GWable = TRUE;
	_baseStatus.GWAttackType = ATTACKTYPE_ZERG_MELEE;
	_stprintf(_baseStatus.GWname, L"Kaiser Baldes");
	_baseStatus.GWdamage = 20;
	_baseStatus.GWdamagePlus = 3;
	_baseStatus.GWmaxHit = 1;
	_baseStatus.GWdamageType = DAMAGETYPE_NORMAL;
	_baseStatus.GWcooldown = 15.0;
	_baseStatus.GWattackRange = 1.0f;

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
void zuUltralisk::initBattleStatus(POINT pt)
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

void zuUltralisk::release(void)
{
	SAFE_DELETE(_zergProductionInfo);

}

void zuUltralisk::update(void)
{
	Unit::update();

}

void zuUltralisk::render(void)
{
	Unit::render();

}

void zuUltralisk::updatePosition(void)
{
	POINT pt = _battleStatus.pt.toPoint();
	_battleStatus.ptTile = { pt.x / TILESIZE, pt.y / TILESIZE };			//현재위치한 타일

	POINT unitsize = UNITSIZE_ZERG_ULTRALISK;

	_battleStatus.rcBody = RectMakeCenter(pt.x, pt.y, unitsize.x, unitsize.y);			//유닛 몸체
	_battleStatus.rcEllipse = _battleStatus.rcBody;		//클릭했을때 보여주는 타원
	_battleStatus.rcEllipse.top += unitsize.y / 2;
}

void zuUltralisk::updateBattleStatus(void)
{
	Unit::updateBattleStatus();


}

void zuUltralisk::updateImageFrame(void)
{
	Unit::setImageFrameForAngle();
}

void zuUltralisk::procCommands(void)
{
	Unit::procCommands();

}
