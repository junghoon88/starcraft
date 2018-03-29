#include "stdafx.h"
#include "zuCocoon.h"
#include "zergDefine.h"

#include "player.h"

#include "zuGuadian.h"
#include "zuDevourer.h"

#include <assert.h>

zuCocoon::zuCocoon(PLAYER playerNum, UNITNUM_ZERG nextUnitNum)
{
	_valid = true;

	//플레이어 정보
	_playerNum = playerNum;

	//종족
	_race = RACES_ZERG;

	//유닛인지 건물인지
	_isBuilding = false;

	//유닛 고유 번호
	_unitNumZ = UNITNUM_ZERG_COCOON;

	_nextUnitNum = nextUnitNum;

	_nextUnit = NULL;

}


zuCocoon::~zuCocoon()
{
}

HRESULT zuCocoon::init(POINT pt)
{
	initNextUnit(pt);
	initBaseStatus();
	initBattleStatus(pt);
	initProcessing();



	updatePosition();

	updateBattleStatus();

	return S_OK;
}

void zuCocoon::initNextUnit(POINT pt)
{
	switch (_nextUnitNum)
	{
	case UNITNUM_ZERG_GUADIAN:
		_nextUnit = new zuGuadian(_playerNum);
		break;
	case UNITNUM_ZERG_DEVOURER:
		_nextUnit = new zuDevourer(_playerNum);
		break;
	}

	if (_nextUnit == NULL)
	{
		assert(L"cocoon->nextUnit 에러");
		return;
	}

	_nextUnit->setLinkAdressZergUpgrade(_zergUpgrade);
	_nextUnit->setLinkAdressAstar(_aStar);
	_nextUnit->setLinkAdressPlayer(_player);
	_nextUnit->init(pt);

}

void zuCocoon::initBaseStatus(void)
{
	_stprintf(_baseStatus.name, L"Zerg Cocoon");

	TCHAR strKey[100];
	_stprintf(strKey, L"ZU-cocoon-Body%d", _playerNum);
	_baseStatus.imgBody = IMAGEMANAGER->findImage(strKey);
	_baseStatus.imgFace = IMAGEMANAGER->findImage(L"ZU-cocoon-Face");
	_baseStatus.imgStat1 = IMAGEMANAGER->findImage(L"ZU-cocoon-Stat1");
	_baseStatus.imgStat2 = IMAGEMANAGER->findImage(L"ZU-cocoon-Stat2");

	_baseStatus.unitControl = 2.0f;

	_baseStatus.maxHP = 200.0f;

	_baseStatus.useSH = FALSE;
	_baseStatus.maxSH = 0.0f;

	_baseStatus.useMP = FALSE;
	_baseStatus.maxMP = 0.0f;

	_baseStatus.sight = 5.0f;
	_baseStatus.detector = FALSE;

	_baseStatus.isAir = TRUE;
	_baseStatus.moveSpeed = 0.0f;

	_baseStatus.unitSize = UNITSIZE_LARGE;
	_baseStatus.transportslots = 0;
	_baseStatus.armor = 0;
	_baseStatus.armorPlus = 1;


	_baseStatus.sameGWAW = FALSE;

	_baseStatus.GWable = FALSE;

	_baseStatus.AWable = FALSE;

	_baseStatus.commands[0] = COMMAND_NONE;
	_baseStatus.commands[1] = COMMAND_NONE;
	_baseStatus.commands[2] = COMMAND_NONE;
	_baseStatus.commands[3] = COMMAND_NONE;
	_baseStatus.commands[4] = COMMAND_NONE;
	_baseStatus.commands[5] = COMMAND_NONE;
	_baseStatus.commands[6] = COMMAND_NONE;
	_baseStatus.commands[7] = COMMAND_NONE;
	_baseStatus.commands[8] = COMMAND_ESC;
}
void zuCocoon::initBattleStatus(POINT pt)
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

void zuCocoon::initProcessing(void)
{
	_processing.type = PROCESSING_MORPHING;

	switch (_nextUnitNum)
	{
	case UNITNUM_ZERG_GUADIAN:				_processing.command = COMMAND_UNIT_GUADIAN;				_processing.img = IMAGEMANAGER->findImage(L"command-unit_guadian");			break;
	case UNITNUM_ZERG_DEVOURER:				_processing.command = COMMAND_UNIT_DEVOURER;			_processing.img = IMAGEMANAGER->findImage(L"command-unit_devourer");		break;
	}

	_processing.curTime = 0.0f;
	_processing.maxTime = _player->getZergProductionInfo()->getZUProductionInfo(_nextUnitNum).buildTime;
	_processing.complete = false;
}



void zuCocoon::release(void)
{
}

void zuCocoon::update(void)
{
	Unit::update();

	updateProgressBar();
}

void zuCocoon::render(void)
{
	Unit::render();
}

void zuCocoon::updatePosition(void)
{
	POINT pt = _battleStatus.pt.toPoint();
	_battleStatus.ptTile = { pt.x / TILESIZE, pt.y / TILESIZE };			//현재위치한 타일

	POINT unitsize = UNITSIZE_ZERG_COCOON;

	_battleStatus.rcBody = RectMakeCenter(pt.x, pt.y, unitsize.x, unitsize.y);			//유닛 몸체
	_battleStatus.rcEllipse = _battleStatus.rcBody;		//클릭했을때 보여주는 타원
	_battleStatus.rcEllipse.top += unitsize.y / 2;
}

void zuCocoon::updateBattleStatus(void)
{
	Unit::updateBattleStatus();


}

void zuCocoon::updateImageFrame(void)
{
	Unit::setImageFrameForAngle();

	if (_processing.complete)
	{
		_nextUnit->init(_battleStatus.pt.toPoint());
		_player->addUnit(_nextUnit);
		_nextObject = _nextUnit;

		_valid = false;
	}
}

void zuCocoon::updateProgressBar(void)
{
	float tick = TIMEMANAGER->getElapsedTime() * BUILDSPEEDMULTIPLY;

	if (_processing.complete == false)
	{
		_processing.curTime += tick;

		if (_processing.curTime >= _processing.maxTime)
		{
			_processing.curTime = _processing.maxTime;

			_processing.complete = true;
		}
	}
}

void zuCocoon::procCommands(void)
{
	if (_battleStatus.curCommand == COMMAND_ESC)
	{
		//SAFE_RELEASEDELETE(_nextUnit);

	}
	else
	{
		_battleStatus.curCommand = COMMAND_NONE;
	}

}
