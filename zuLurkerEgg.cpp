#include "stdafx.h"
#include "zuLurkerEgg.h"
#include "zergDefine.h"
#include "player.h"

#include <assert.h>

#include "zuLurker.h"


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

	_nextUnitNum = UNITNUM_ZERG_LURKER;

	_nextUnit = NULL;

}


zuLurkerEgg::~zuLurkerEgg()
{
}

HRESULT zuLurkerEgg::init(POINT pt)
{
	initNextUnit(pt);
	initBaseStatus();
	initBattleStatus(pt);
	initProcessing();

	updatePosition();

	updateBattleStatus();


	return S_OK;
}

void zuLurkerEgg::initNextUnit(POINT pt)
{
	_nextUnit = new zuLurker(_playerNum);

	if (_nextUnit == NULL)
	{
		assert(L"lurkeregg->nextUnit 에러");
		return;
	}

	_nextUnit->setLinkAdressZergUpgrade(_zergUpgrade);
	_nextUnit->setLinkAdressAstar(_aStar);
	_nextUnit->setLinkAdressPlayer(_player);
	_nextUnit->init(pt);
}


void zuLurkerEgg::initBaseStatus(void)
{
	_stprintf(_baseStatus.name, L"Zerg LerkerEgg");

	TCHAR strKey[100];
	_stprintf(strKey, L"ZU-lurkeregg-Body%d", _playerNum);
	_baseStatus.imgBody = IMAGEMANAGER->findImage(strKey);
	_baseStatus.imgFace = IMAGEMANAGER->findImage(L"ZU-lerkeregg-Face");
	_baseStatus.imgStat1 = IMAGEMANAGER->findImage(L"ZU-lerkeregg-Stat1");
	_baseStatus.imgStat2 = IMAGEMANAGER->findImage(L"ZU-lerkeregg-Stat2");

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

void zuLurkerEgg::initProcessing(void)
{
	_processing.type = PROCESSING_MORPHING;

	_processing.command = COMMAND_UNIT_LURKER;
	_processing.img = IMAGEMANAGER->findImage(L"command-unit_lurker");

	_processing.curTime = 0.0f;
	_processing.maxTime = _player->getZergProductionInfo()->getZUProductionInfo(UNITNUM_ZERG_LURKER).buildTime;
	_processing.complete = false;

}

void zuLurkerEgg::release(void)
{
}

void zuLurkerEgg::update(void)
{
	Unit::update();

	updateProgressBar();

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
	//중간 반복
	_battleStatus.bodyFrameTime += TIMEMANAGER->getElapsedTime();
	if (_battleStatus.bodyFrameTime >= UNIT_BODY_FPS_TIME)
	{
		_battleStatus.bodyFrameTime -= UNIT_BODY_FPS_TIME;

		if (!_processing.complete)
		{
			//처음
			if (_battleStatus.bodyFrame.x < 4)
			{
				_battleStatus.bodyFrame.x++;
			}
			else
			{
				_battleStatus.bodyFrame.x = (_battleStatus.bodyFrame.x == 6) ? 4 : _battleStatus.bodyFrame.x + 1;
			}
		}
		else
		{
			//마지막
			if (_battleStatus.bodyFrame.x < 9)
			{
				_battleStatus.bodyFrame.x++;
			}
			else
			{
				_nextUnit->init(_battleStatus.pt.toPoint());
				_player->addUnit(_nextUnit);
				_nextObject = _nextUnit;
				
				_valid = false;
			}
		}
	}
}

void zuLurkerEgg::updateProgressBar(void)
{
	float tick = TIMEMANAGER->getElapsedTime() * BUILDSPEEDMULTIPLY;

	if (_processing.complete == false)
	{
		_processing.curTime += tick;

		if (_processing.curTime >= _processing.maxTime)
		{
			_processing.curTime = _processing.maxTime;

			_processing.complete = true;
			_battleStatus.bodyFrame.x = 7;
		}
	}
}

void zuLurkerEgg::procCommands(void)
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
