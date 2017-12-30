#include "stdafx.h"
#include "zuDefiler.h"
#include "zergDefine.h"
#include "player.h"


zuDefiler::zuDefiler(PLAYER playerNum)
{
	_valid = true;

	//플레이어 정보
	_playerNum = playerNum;

	//종족
	_race = RACES_ZERG;

	//유닛인지 건물인지
	_isBuilding = false;

	//유닛 고유 번호
	_unitNumZ = UNITNUM_ZERG_DEFILER;

	_zergProductionInfo = new zergProductionInfo;
}


zuDefiler::~zuDefiler()
{
}

HRESULT zuDefiler::init(POINT pt)
{
	initBaseStatus();
	initBattleStatus(pt);



	updatePosition();

	updateBattleStatus();


	return S_OK;
}

void zuDefiler::initBaseStatus(void)
{
	_stprintf(_baseStatus.name, L"Zerg Defiler");

	TCHAR strKey[100];
	_stprintf(strKey, L"ZU-defilerBody%d", _playerNum);
	_baseStatus.imgBody = IMAGEMANAGER->findImage(strKey);
	_baseStatus.imgFace = NULL;
	_baseStatus.imgStat1 = IMAGEMANAGER->findImage(L"ZU-defilerStat1");
	_baseStatus.imgStat2 = IMAGEMANAGER->findImage(L"ZU-defilerStat2");

	_baseStatus.unitControl = 2.0f;

	_baseStatus.maxHP = 80.0f;

	_baseStatus.useSH = FALSE;
	_baseStatus.maxSH = 0.0f;

	_baseStatus.useMP = TRUE;
	_baseStatus.maxMP = 200.0f; //업글시 250

	_baseStatus.sight = 10.0f;
	_baseStatus.detector = FALSE;

	_baseStatus.isAir = FALSE;
	_baseStatus.moveSpeed = 4.0f;

	_baseStatus.unitSize = UNITSIZE_MEDIUM;
	_baseStatus.transportslots = 2;
	_baseStatus.armor = 1;
	_baseStatus.armorPlus = 1;


	_baseStatus.sameGWAW = FALSE;

	_baseStatus.GWable = FALSE;

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
void zuDefiler::initBattleStatus(POINT pt)
{
	//BattleStatus
	_battleStatus.unitState = UNITSTATE_STOP;
	_battleStatus.curCommand = COMMAND_STOP;
	_battleStatus.clicked = false;
	_battleStatus.curHP = _baseStatus.maxHP;
	_battleStatus.maxHP = _baseStatus.maxHP;
	_battleStatus.curMP = 50.0f; //업글시 62.5
	_battleStatus.maxMP = _baseStatus.maxHP;

	_battleStatus.pt.set((float)pt.x, (float)pt.y);
	_battleStatus.moveSpeed = _baseStatus.moveSpeed;
	_battleStatus.angleDeg = 315.0f;
	_battleStatus.direction;
}


void zuDefiler::release(void)
{
	SAFE_DELETE(_zergProductionInfo);
}

void zuDefiler::update(void)
{
	Unit::update();
}

void zuDefiler::render(void)
{
	Unit::render();
}

void zuDefiler::updatePosition(void)
{
	POINT pt = _battleStatus.pt.toPoint();
	_battleStatus.ptTile = { pt.x / TILESIZE, pt.y / TILESIZE };			//현재위치한 타일

	POINT unitsize = UNITSIZE_ZERG_DEFILER;

	_battleStatus.rcBody = RectMakeCenter(pt.x, pt.y, unitsize.x, unitsize.y);			//유닛 몸체
	_battleStatus.rcEllipse = _battleStatus.rcBody;		//클릭했을때 보여주는 타원
	_battleStatus.rcEllipse.top += unitsize.y / 2;
}

void zuDefiler::updateBattleStatus(void)
{
	Unit::updateBattleStatus();


}

void zuDefiler::updateImageFrame(void)
{
	Unit::setImageFrameForAngle();
}

void zuDefiler::procCommands(void)
{
	Unit::procCommands();

}
