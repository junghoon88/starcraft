#include "stdafx.h"
#include "zuLurker.h"
#include "zergDefine.h"
#include "player.h"


zuLurker::zuLurker(PLAYER playerNum)
{
	_valid = true;

	//플레이어 정보
	_playerNum = playerNum;

	//종족
	_race = RACES_ZERG;

	//유닛인지 건물인지
	_isBuilding = false;

	//유닛 고유 번호
	_unitNumZ = UNITNUM_ZERG_LURKER;

	_zergProductionInfo = new zergProductionInfo;

}


zuLurker::~zuLurker()
{
}

HRESULT zuLurker::init(POINT pt)
{
	initBaseStatus();
	initBattleStatus(pt);



	updatePosition();

	updateBattleStatus();

	return S_OK;
}

void zuLurker::initBaseStatus(void)
{
	_stprintf(_baseStatus.name, L"Zerg Lurker");

	TCHAR strKey[100];
	_stprintf(strKey, L"ZU-lurkerBody%d", _playerNum);
	_baseStatus.imgBody = IMAGEMANAGER->findImage(strKey);
	_baseStatus.imgFace = NULL;
	_baseStatus.imgStat1 = IMAGEMANAGER->findImage(L"ZU-lurkerStat1");
	_baseStatus.imgStat2 = IMAGEMANAGER->findImage(L"ZU-lurkerStat2");

	_baseStatus.unitControl = 2.0f;

	_baseStatus.maxHP = 125.0f;

	_baseStatus.useSH = FALSE;
	_baseStatus.maxSH = 0.0f;

	_baseStatus.useMP = FALSE;
	_baseStatus.maxMP = 0.0f;

	_baseStatus.sight = 8.0f;
	_baseStatus.detector = FALSE;

	_baseStatus.isAir = FALSE;
	_baseStatus.moveSpeed = 6.0f; //업글시 8.36

	_baseStatus.unitSize = UNITSIZE_LARGE;
	_baseStatus.transportslots = 4;
	_baseStatus.armor = 1;
	_baseStatus.armorPlus = 1;


	_baseStatus.sameGWAW = FALSE;

	_baseStatus.GWable = FALSE;
	_baseStatus.GWAttackType = ATTACKTYPE_ZERG_MELEE;
	_stprintf(_baseStatus.GWname, L"Subterranean Spines");
	_baseStatus.GWdamage = 20;
	_baseStatus.GWdamagePlus = 2;
	_baseStatus.GWmaxHit = 1;
	_baseStatus.GWdamageType = DAMAGETYPE_NORMAL;
	_baseStatus.GWcooldown = 37.0;
	_baseStatus.GWattackRange = 6.0f;

	_baseStatus.AWable = FALSE;

	_baseStatus.commands[0] = COMMAND_MOVE;
	_baseStatus.commands[1] = COMMAND_STOP;
	_baseStatus.commands[2] = COMMAND_NONE;
	_baseStatus.commands[3] = COMMAND_PATROL;
	_baseStatus.commands[4] = COMMAND_HOLD;
	_baseStatus.commands[5] = COMMAND_NONE;
	_baseStatus.commands[6] = COMMAND_NONE;
	_baseStatus.commands[7] = COMMAND_NONE;
	_baseStatus.commands[8] = COMMAND_BURROW;
}
void zuLurker::initBattleStatus(POINT pt)
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

void zuLurker::release(void)
{
	SAFE_DELETE(_zergProductionInfo);

}

void zuLurker::update(void)
{
	Unit::update();

}

void zuLurker::render(void)
{
	Unit::render();

}

void zuLurker::updatePosition(void)
{
	POINT pt = _battleStatus.pt.toPoint();
	_battleStatus.ptTile = { pt.x / TILESIZE, pt.y / TILESIZE };			//현재위치한 타일

	POINT unitsize = UNITSIZE_ZERG_LURKER;

	_battleStatus.rcBody = RectMakeCenter(pt.x, pt.y, unitsize.x, unitsize.y);			//유닛 몸체
	_battleStatus.rcEllipse = _battleStatus.rcBody;		//클릭했을때 보여주는 타원
	_battleStatus.rcEllipse.top += unitsize.y / 2;
}

void zuLurker::updateBattleStatus(void)
{
	Unit::updateBattleStatus();


}

void zuLurker::updateImageFrame(void)
{
	Unit::setImageFrameForAngle();
}

void zuLurker::procCommands(void)
{
	Unit::procCommands();

}
