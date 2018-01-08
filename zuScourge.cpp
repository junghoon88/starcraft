#include "stdafx.h"
#include "zuScourge.h"
#include "zergDefine.h"
#include "player.h"


zuScourge::zuScourge(PLAYER playerNum)
{
	_valid = true;

	//플레이어 정보
	_playerNum = playerNum;

	//종족
	_race = RACES_ZERG;

	//유닛인지 건물인지
	_isBuilding = false;

	//유닛 고유 번호
	_unitNumZ = UNITNUM_ZERG_SCOURGE;

}


zuScourge::~zuScourge()
{
}

HRESULT zuScourge::init(POINT pt)
{
	initBaseStatus();
	initBattleStatus(pt);



	updatePosition();

	updateBattleStatus();

	return S_OK;
}


void zuScourge::initBaseStatus(void)
{
	_stprintf(_baseStatus.name, L"Zerg Scourge");

	TCHAR strKey[100];
	_stprintf(strKey, L"ZU-scourge-Body%d", _playerNum);
	_baseStatus.imgBody = IMAGEMANAGER->findImage(strKey);
	_baseStatus.imgFace = IMAGEMANAGER->findImage(L"ZU-scourge-Face");
	_baseStatus.imgStat1 = IMAGEMANAGER->findImage(L"ZU-scourge-Stat1");
	_baseStatus.imgStat2 = IMAGEMANAGER->findImage(L"ZU-scourge-Stat2");

	_baseStatus.unitControl = 0.5f;

	_baseStatus.maxHP = 25.0f;

	_baseStatus.useSH = FALSE;
	_baseStatus.maxSH = 0.0f;

	_baseStatus.useMP = FALSE;
	_baseStatus.maxMP = 0.0f;

	_baseStatus.sight = 5.0f;
	_baseStatus.detector = FALSE;

	_baseStatus.isAir = TRUE;
	_baseStatus.moveSpeed = 6.67;

	_baseStatus.unitSize = UNITSIZE_SMALL;
	_baseStatus.transportslots = 0;
	_baseStatus.armor = 0;
	_baseStatus.armorPlus = 1;


	_baseStatus.sameGWAW = FALSE;

	_baseStatus.GWable = FALSE;

	_baseStatus.AWable = TRUE;
	_baseStatus.AWAttackType = ATTACKTYPE_ZERG_FLYING;
	_stprintf(_baseStatus.AWname, L"Suicide");
	_baseStatus.AWdamage = 110;
	_baseStatus.AWdamagePlus = 0;
	_baseStatus.AWmaxHit = 1;
	_baseStatus.AWdamageType = DAMAGETYPE_NORMAL;
	_baseStatus.AWcooldown = 0.0;
	_baseStatus.AWattackRange = 1.0f;

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
void zuScourge::initBattleStatus(POINT pt)
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


void zuScourge::release(void)
{
}

void zuScourge::update(void)
{
	Unit::update();
}

void zuScourge::render(void)
{
	Unit::render();
}

void zuScourge::updatePosition(void)
{
	POINT pt = _battleStatus.pt.toPoint();
	_battleStatus.ptTile = { pt.x / TILESIZE, pt.y / TILESIZE };			//현재위치한 타일

	POINT unitsize = UNITSIZE_ZERG_SCOURGE;

	_battleStatus.rcBody = RectMakeCenter(pt.x, pt.y, unitsize.x, unitsize.y);			//유닛 몸체
	_battleStatus.rcEllipse = _battleStatus.rcBody;		//클릭했을때 보여주는 타원
	_battleStatus.rcEllipse.top += unitsize.y / 2;
}

void zuScourge::updateBattleStatus(void)
{
	Unit::updateBattleStatus();


}

void zuScourge::updateImageFrame(void)
{
	Unit::setImageFrameForAngle();

	float tick = TIMEMANAGER->getElapsedTime();

	_battleStatus.bodyFrameTime += tick;
	if (_battleStatus.bodyFrameTime >= UNIT_BODY_FPS_TIME)
	{
		_battleStatus.bodyFrameTime -= UNIT_BODY_FPS_TIME;

		_battleStatus.bodyFrame.y++;
		if (_battleStatus.bodyFrame.y > _baseStatus.imgBody->getMaxFrameY())
		{
			_battleStatus.bodyFrame.y = 0;
		}
	}
}

void zuScourge::procCommands(void)
{
	Unit::procCommands();

}
