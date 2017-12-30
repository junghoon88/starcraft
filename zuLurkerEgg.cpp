#include "stdafx.h"
#include "zuLurkerEgg.h"
#include "zergDefine.h"
#include "player.h"


zuLurkerEgg::zuLurkerEgg(PLAYER playerNum)
{
	_valid = true;

	//플레이어 정보
	_playerNum = playerNum;

	//종족
	_race = RACES_ZERG;

	//유닛인지 건물인지
	_isBuilding = false;

	//유닛 고유 번호
	_unitNumZ = UNITNUM_ZERG_LURKEREGG;

	_zergProductionInfo = new zergProductionInfo;
}


zuLurkerEgg::~zuLurkerEgg()
{
}

HRESULT zuLurkerEgg::init(POINT pt)
{
	initBaseStatus();
	initBattleStatus(pt);



	updatePosition();

	updateBattleStatus();


	return S_OK;
}


void zuLurkerEgg::initBaseStatus(void)
{
	_stprintf(_baseStatus.name, L"Zerg LerkerEgg");

	TCHAR strKey[100];
	_stprintf(strKey, L"ZU-lerkereggBody%d", _playerNum);
	_baseStatus.imgBody = IMAGEMANAGER->findImage(strKey);
	_baseStatus.imgFace = NULL;
	_baseStatus.imgStat1 = IMAGEMANAGER->findImage(L"ZU-lerkereggStat1");
	_baseStatus.imgStat2 = IMAGEMANAGER->findImage(L"ZU-lerkereggStat2");

	_baseStatus.unitControl = 2.0f;

	_baseStatus.maxHP = 200.0f;

	_baseStatus.useSH = FALSE;
	_baseStatus.maxSH = 0.0f;

	_baseStatus.useMP = FALSE;
	_baseStatus.maxMP = 0.0f;

	_baseStatus.sight = 5.0f;
	_baseStatus.detector = FALSE;

	_baseStatus.isAir = FALSE;
	_baseStatus.moveSpeed = 0.0f;

	_baseStatus.unitSize = UNITSIZE_SMALL;
	_baseStatus.transportslots = 0;
	_baseStatus.armor = 10;
	_baseStatus.armorPlus = 1;


	_baseStatus.sameGWAW = FALSE;
	_baseStatus.GWable = FALSE;
	_baseStatus.AWable = FALSE;

	_baseStatus.commands[0] = COMMAND_MOVE;
	_baseStatus.commands[1] = COMMAND_NONE;
	_baseStatus.commands[2] = COMMAND_NONE;
	_baseStatus.commands[3] = COMMAND_NONE;
	_baseStatus.commands[4] = COMMAND_NONE;
	_baseStatus.commands[5] = COMMAND_NONE;
	_baseStatus.commands[6] = COMMAND_NONE;
	_baseStatus.commands[7] = COMMAND_NONE;
	_baseStatus.commands[8] = COMMAND_ESC;
}
void zuLurkerEgg::initBattleStatus(POINT pt)
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


void zuLurkerEgg::release(void)
{
	SAFE_DELETE(_zergProductionInfo);
}

void zuLurkerEgg::update(void)
{
	Unit::update();
}

void zuLurkerEgg::render(void)
{
	Unit::render();
}

void zuLurkerEgg::updatePosition(void)
{
	POINT pt = _battleStatus.pt.toPoint();
	_battleStatus.ptTile = { pt.x / TILESIZE, pt.y / TILESIZE };			//현재위치한 타일

	POINT unitsize = UNITSIZE_ZERG_LURKEREGG;

	_battleStatus.rcBody = RectMakeCenter(pt.x, pt.y, unitsize.x, unitsize.y);			//유닛 몸체
	_battleStatus.rcEllipse = _battleStatus.rcBody;		//클릭했을때 보여주는 타원
	_battleStatus.rcEllipse.top += unitsize.y / 2;
}

void zuLurkerEgg::updateBattleStatus(void)
{
	Unit::updateBattleStatus();


}

void zuLurkerEgg::updateImageFrame(void)
{
	Unit::setImageFrameForAngle();
}

void zuLurkerEgg::procCommands(void)
{
	Unit::procCommands();

}
