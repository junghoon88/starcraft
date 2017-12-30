#include "stdafx.h"
#include "zuZergEgg.h"

#include "player.h"

#include "zuDrone.h"
#include "zuZergling.h"
#include "zuOverlord.h"
#include "zuHydralisk.h"
#include "zuMutalisk.h"
#include "zuScourge.h"
#include "zuQueen.h"
#include "zuUltralisk.h"
#include "zuDefiler.h"

#include <assert.h>

zuZergEgg::zuZergEgg(PLAYER playerNum, UNITNUM_ZERG nextUnitNum)
{
	_valid = true;

	//플레이어 정보
	_playerNum = playerNum;

	//종족
	_race = RACES_ZERG;

	//유닛인지 건물인지
	_isBuilding = false;

	//유닛 고유 번호
	_unitNumZ = UNITNUM_ZERG_ZERGEGG;

	_nextUnitNum = nextUnitNum;


	_buildTime = _buildTimeMax = 0.0f;

	_complete = false;

	_zergProductionInfo = new zergProductionInfo;

	_nextUnit = NULL;

	_progressBar = NULL;
}


zuZergEgg::~zuZergEgg()
{
}

HRESULT zuZergEgg::init(POINT pt)
{
	initNextUnit(pt);
	initBaseStatus();
	initBattleStatus(pt);



	updatePosition();

	updateBattleStatus();


	_buildTimeMax = _zergProductionInfo->getZUProductionInfo(_nextUnitNum).buildTime;



	_progressBar = new progressBar;
	_progressBar->init(L"Mutating");
	_progressBar->setPointLT(263, 427);



	return S_OK;
}

void zuZergEgg::initNextUnit(POINT pt)
{
	switch (_nextUnitNum)
	{
	case UNITNUM_ZERG_DRONE:
		_nextUnit = new zuDrone(_playerNum);
		break;
	case UNITNUM_ZERG_ZERGLING:
		_nextUnit = new zuZergling(_playerNum);
		break;
	case UNITNUM_ZERG_OVERLORD:
		_nextUnit = new zuOverlord(_playerNum);
		break;
	case UNITNUM_ZERG_HYDRALISK:
		_nextUnit = new zuHydralisk(_playerNum);
		break;
	case UNITNUM_ZERG_MUTALISK:
		_nextUnit = new zuMutalisk(_playerNum);
		break;
	case UNITNUM_ZERG_SCOURGE:
		_nextUnit = new zuScourge(_playerNum);
		break;
	case UNITNUM_ZERG_QUEEN:
		_nextUnit = new zuQueen(_playerNum);
		break;
	case UNITNUM_ZERG_ULTRALISK:
		_nextUnit = new zuUltralisk(_playerNum);
		break;
	case UNITNUM_ZERG_DEFILER:
		_nextUnit = new zuDefiler(_playerNum);
		break;
	}

	if (_nextUnit == NULL)
	{
		assert(L"egg->nextUnit 에러");
		return;
	}

	_nextUnit->setLinkAdressZergUpgrade(_zergUpgrade);
	_nextUnit->setLinkAdressAstar(_aStar);
	_nextUnit->setLinkAdressPlayer(_player);
	_nextUnit->init(pt);

}


void zuZergEgg::initBaseStatus(void)
{
	_stprintf(_baseStatus.name, L"Zerg Egg");	
												
	TCHAR strKey[100];
	_stprintf(strKey, L"ZU-zergeggBody%d", _playerNum);
	_baseStatus.imgBody = IMAGEMANAGER->findImage(strKey);				
	_baseStatus.imgFace = NULL;											
	_baseStatus.imgStat1 = IMAGEMANAGER->findImage(L"ZU-zergeggStat1");	
	_baseStatus.imgStat2 = IMAGEMANAGER->findImage(L"ZU-zergeggStat2");	
	
	_baseStatus.unitControl = _nextUnit->getBaseStatus().unitControl;

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
void zuZergEgg::initBattleStatus(POINT pt)
{
	//BattleStatus
	_battleStatus.unitState = UNITSTATE_STOP;
	_battleStatus.curCommand = COMMAND_STOP;
	_battleStatus.clicked = false;
	_battleStatus.curHP = _baseStatus.maxHP;			//현재 HP
	_battleStatus.maxHP = _baseStatus.maxHP;			//최대 HP

	_battleStatus.pt.set((float)pt.x, (float)pt.y);							//현재위치
	_battleStatus.moveSpeed = _baseStatus.moveSpeed;
}


void zuZergEgg::release(void)
{
	SAFE_RELEASEDELETE(_nextUnit);
	SAFE_RELEASEDELETE(_progressBar);
	SAFE_DELETE(_zergProductionInfo);
}

void zuZergEgg::update(void)
{
	Unit::update();

	updateProgressBar();


	if (_battleStatus.bodyFrame.x < 4)
	{
		_battleStatus.bodyFrame.x++;
	}
	else
	{
		if (_complete == false)
		{
			_battleStatus.bodyFrameTime += TIMEMANAGER->getElapsedTime();
			if (_battleStatus.bodyFrameTime >= UNIT_BODY_FPS_TIME)
			{
				_battleStatus.bodyFrameTime -= UNIT_BODY_FPS_TIME;
				_battleStatus.bodyFrame.x = (_battleStatus.bodyFrame.x == 6) ? 4 : _battleStatus.bodyFrame.x + 1;
			}
		}
		else
		{

		}
	}

}

void zuZergEgg::render(void)
{
	Unit::render();

	_progressBar->ZRender(ZORDER_INTERFACE2);

}

void zuZergEgg::updateBattleStatus(void)
{
	POINT pt = _battleStatus.pt.toPoint();
	_battleStatus.ptTile = { pt.x / TILESIZE, pt.y / TILESIZE };			//현재위치한 타일

	POINT unitsize = UNITSIZE_ZERG_ZERGEGG;

	_battleStatus.rcBody = RectMakeCenter(pt.x, pt.y, unitsize.x, unitsize.y);			//유닛 몸체
	_battleStatus.rcEllipse = _battleStatus.rcBody;		//클릭했을때 보여주는 타원
	_battleStatus.rcEllipse.top += unitsize.y / 4;
	_battleStatus.rcEllipse.bottom -= unitsize.y / 4;
}
void zuZergEgg::updatePosition(void)
{
	Unit::updateBattleStatus();

}
void zuZergEgg::updateImageFrame(void)
{
	if (!_complete)
	{
		//처음
		if (_battleStatus.bodyFrame.x < 4)
		{
			_battleStatus.bodyFrame.x++;
		}
		else
		{
			//중간 반복
			_battleStatus.bodyFrameTime += TIMEMANAGER->getElapsedTime();
			if (_battleStatus.bodyFrameTime >= UNIT_BODY_FPS_TIME)
			{
				_battleStatus.bodyFrameTime -= UNIT_BODY_FPS_TIME;
				_battleStatus.bodyFrame.x = (_battleStatus.bodyFrame.x == 6) ? 4 : _battleStatus.bodyFrame.x + 1;
			}
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
			//tagBattleStatus temp = _battleStatus;
			//temp.bodyFrame.x = 0;
			//temp.bodyFrame.y = 0;
			//temp.curCommand = COMMAND_STOP;
			//_nextUnit->setBattleStatus(temp);
			_player->addUnit(_nextUnit);

			_nextObject = _nextUnit;
			_valid = false;
		}
	}

}

void zuZergEgg::updateProgressBar(void)
{
	float tick = TIMEMANAGER->getElapsedTime() * BUILDSPEEDMULTIPLY;

	if (_complete == false)
	{
		_buildTime += tick;

		if (_buildTime >= _buildTimeMax)
		{
			_buildTime = _buildTimeMax;

			_complete = true;
			_battleStatus.bodyFrame.x = 7;
		}
	}

	_progressBar->setGauge(_buildTime, _buildTimeMax);

}

void zuZergEgg::procCommands(void)
{
	if (_battleStatus.curCommand == COMMAND_ESC)
	{

	}
	else
	{
		_battleStatus.curCommand = COMMAND_NONE;
	}
}
