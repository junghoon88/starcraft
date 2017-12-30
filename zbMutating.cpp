#include "stdafx.h"
#include "zbMutating.h"

#include "player.h"

#include "zbCreepColony.h"
#include "zbDefilerMound.h"
#include "zbEvolutionChamber.h"
#include "zbExtractor.h"
#include "zbGreaterSpire.h"
#include "zbHatchery.h"
#include "zbHive.h"
#include "zbHydraliskDen.h"
#include "zbLair.h"
#include "zbNydusCanal.h"
#include "zbQueensNest.h"
#include "zbSpawningPool.h"
#include "zbSpire.h"
#include "zbSporeColony.h"
#include "zbSunkenColony.h"
#include "zbUltraliskCavern.h"


zbMutating::zbMutating(PLAYER playerNum, BUILDINGNUM_ZERG buildingNum)
{
	_valid = true;

	//플레이어 정보
	_playerNum = playerNum;

	//종족
	_race = RACES_ZERG;

	//유닛인지 건물인지
	_isBuilding = true;

	//유닛 고유 번호
	_buildingNumZ = buildingNum;

	_beforeBuilding = NULL;
	_nextBuilding = NULL;

	_zergProductionInfo = new zergProductionInfo;
	
	_buildTime = _buildTimeMax = _buildHP = 0.0f;

	_progressBar = NULL;

	_complete = false;
}

zbMutating::zbMutating(PLAYER playerNum, BUILDINGNUM_ZERG buildingNum, Building* beforeBuilding)
{
	_valid = true;

	//플레이어 정보
	_playerNum = playerNum;

	//종족
	_race = RACES_ZERG;

	//유닛인지 건물인지
	_isBuilding = true;

	//유닛 고유 번호
	_buildingNumZ = buildingNum;

	_beforeBuilding = beforeBuilding;
	_nextBuilding = NULL;

	_zergProductionInfo = new zergProductionInfo;

	_buildTime = _buildTimeMax = _buildHP = 0.0f;

	_progressBar = NULL;

	_complete = false;
}

zbMutating::~zbMutating()
{
}

HRESULT zbMutating::init(POINT ptTile)
{
	initNextBuilding(ptTile);
	initBaseStatus();
	initBattleStatus(ptTile);

	_buildTimeMax = _zergProductionInfo->getZBProductionInfo(_buildingNumZ).buildTime;

	_progressBar = new progressBar;
	_progressBar->init(L"Mutating");
	_progressBar->setPointLT(263, 427);



	return S_OK;
}

void zbMutating::initNextBuilding(POINT ptTile)
{
	switch (_buildingNumZ)
	{
	case BUILDINGNUM_ZERG_HATCHERY:					_nextBuilding = new zbHatchery(_playerNum);				break;
	//case BUILDINGNUM_ZERG_LAIR:					_nextBuilding = new zbLair(_playerNum);					break;
	//case BUILDINGNUM_ZERG_HIVE:					_nextBuilding = new zbHive(_playerNum);					break;
	//case BUILDINGNUM_ZERG_CREEPCOLONY:			_nextBuilding = new zbCreepColony(_playerNum);			break;
	//case BUILDINGNUM_ZERG_SUNKENCOLONY:			_nextBuilding = new zbSunkenColony(_playerNum);			break;
	//case BUILDINGNUM_ZERG_SPORECOLONY:			_nextBuilding = new zbSporeColony(_playerNum);			break;
	//case BUILDINGNUM_ZERG_EXTRACTOR:				_nextBuilding = new zbExtractor(_playerNum);			break;
	//case BUILDINGNUM_ZERG_SPAWNINGPOOL:			_nextBuilding = new zbSpawningPool(_playerNum);			break;
	//case BUILDINGNUM_ZERG_EVOLUTIONCHAMBER:		_nextBuilding = new zbEvolutionChamber(_playerNum);		break;
	//case BUILDINGNUM_ZERG_HYDRALISKDEN:			_nextBuilding = new zbHydraliskDen(_playerNum);			break;
	//case BUILDINGNUM_ZERG_SPIRE:					_nextBuilding = new zbSpire(_playerNum);				break;
	//case BUILDINGNUM_ZERG_GREATERSPIRE:			_nextBuilding = new zbGreaterSpire(_playerNum);			break;
	//case BUILDINGNUM_ZERG_QUEENSNEST:				_nextBuilding = new zbQueensNest(_playerNum);			break;
	//case BUILDINGNUM_ZERG_NYDUSCANAL:				_nextBuilding = new zbNydusCanal(_playerNum);			break;
	//case BUILDINGNUM_ZERG_ULTRALISKCAVERN:		_nextBuilding = new zbUltraliskCavern(_playerNum);		break;
	//case BUILDINGNUM_ZERG_DEFILERMOUND:			_nextBuilding = new zbEvolutionChamber(_playerNum);		break;
	}

	_nextBuilding->setLinkAdressZergUpgrade(_zergUpgrade);
	_nextBuilding->setLinkAdressAstar(_aStar);
	_nextBuilding->setLinkAdressPlayer(_player);
	_nextBuilding->init(ptTile);
}


void zbMutating::initBaseStatus(void)
{
	//드론에서 새로 만드는 건물일 경우 HP를 그대로 받아오지만 
	//건물자체가 업그레이드 하는 경우 현재 HP를 그대로 가져간다. 
	//(예->Spire 피가 600 이었다가 완성되면 1000으로 됨. 하지만 이름은 그레이트 스파이어임)

	tagBaseStatus nextStatus = _nextBuilding->getBaseStatus();


	switch (_buildingNumZ)
	{
	case BUILDINGNUM_ZERG_HATCHERY:				_baseStatus.imgBody = IMAGEMANAGER->findImage(L"ZB-MutatingBody2");	break;
	case BUILDINGNUM_ZERG_LAIR:					_baseStatus.imgBody = IMAGEMANAGER->findImage(L"ZB-MutatingBody2");	break;
	case BUILDINGNUM_ZERG_HIVE:					_baseStatus.imgBody = IMAGEMANAGER->findImage(L"ZB-MutatingBody2");	break;
	case BUILDINGNUM_ZERG_CREEPCOLONY:			_baseStatus.imgBody = IMAGEMANAGER->findImage(L"ZB-MutatingBody1");	break;
	case BUILDINGNUM_ZERG_SUNKENCOLONY:			_baseStatus.imgBody = IMAGEMANAGER->findImage(L"ZB-MutatingBody1");	break;
	case BUILDINGNUM_ZERG_SPORECOLONY:			_baseStatus.imgBody = IMAGEMANAGER->findImage(L"ZB-MutatingBody1");	break;
	case BUILDINGNUM_ZERG_EXTRACTOR:			_baseStatus.imgBody = IMAGEMANAGER->findImage(L"ZB-MutatingBody3");	break;
	case BUILDINGNUM_ZERG_SPAWNINGPOOL:			_baseStatus.imgBody = IMAGEMANAGER->findImage(L"ZB-MutatingBody2");	break;
	case BUILDINGNUM_ZERG_EVOLUTIONCHAMBER:		_baseStatus.imgBody = IMAGEMANAGER->findImage(L"ZB-MutatingBody2");	break;
	case BUILDINGNUM_ZERG_HYDRALISKDEN:			_baseStatus.imgBody = IMAGEMANAGER->findImage(L"ZB-MutatingBody2");	break;
	case BUILDINGNUM_ZERG_SPIRE:				_baseStatus.imgBody = IMAGEMANAGER->findImage(L"ZB-MutatingBody2");	break;
	case BUILDINGNUM_ZERG_GREATERSPIRE:			_baseStatus.imgBody = IMAGEMANAGER->findImage(L"ZB-MutatingBody2");	break;
	case BUILDINGNUM_ZERG_QUEENSNEST:			_baseStatus.imgBody = IMAGEMANAGER->findImage(L"ZB-MutatingBody2");	break;
	case BUILDINGNUM_ZERG_NYDUSCANAL:			_baseStatus.imgBody = IMAGEMANAGER->findImage(L"ZB-MutatingBody2");	break;
	case BUILDINGNUM_ZERG_ULTRALISKCAVERN:		_baseStatus.imgBody = IMAGEMANAGER->findImage(L"ZB-MutatingBody2");	break;
	case BUILDINGNUM_ZERG_DEFILERMOUND:			_baseStatus.imgBody = IMAGEMANAGER->findImage(L"ZB-MutatingBody2");	break;
	}



	//이전상태가 드론일경우
	if (_beforeBuilding == NULL)
	{
		_tcscpy(_baseStatus.name, nextStatus.name);
		//_baseStatus.imgBody		= IMAGEMANAGER->findImage(L"ZB-MutatingBody1");
		_baseStatus.imgFace		= nextStatus.imgFace;
		_baseStatus.imgStat1	= nextStatus.imgStat1;
		_baseStatus.imgStat2	= nextStatus.imgStat2;

		_baseStatus.maxHP		= nextStatus.maxHP;
		_baseStatus.useSH		= nextStatus.useSH;
		_baseStatus.maxSH		= nextStatus.maxSH;
		_baseStatus.useMP		= nextStatus.useMP;
		_baseStatus.maxMP		= nextStatus.maxMP;
		_baseStatus.sight		= 5.0f;
		_baseStatus.detector	= FALSE;

		_baseStatus.isAir		= FALSE;
		_baseStatus.armor		= nextStatus.armor;

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
	//이전 건물이 있을 경우
	else
	{
		tagBaseStatus beforeStatus = _beforeBuilding->getBaseStatus();

		_tcscpy(_baseStatus.name, nextStatus.name);
		//_baseStatus.imgBody		= IMAGEMANAGER->findImage(L"ZB-MutatingBody1");
		_baseStatus.imgFace		= nextStatus.imgFace;
		_baseStatus.imgStat1	= nextStatus.imgStat1;
		_baseStatus.imgStat2	= nextStatus.imgStat2;

		_baseStatus.maxHP = beforeStatus.maxHP;
		_baseStatus.useSH = beforeStatus.useSH;
		_baseStatus.maxSH = beforeStatus.maxSH;
		_baseStatus.useMP = beforeStatus.useMP;
		_baseStatus.maxMP = beforeStatus.maxMP;
		_baseStatus.sight = 5.0f;
		_baseStatus.detector = FALSE;

		_baseStatus.isAir = FALSE;
		_baseStatus.armor = beforeStatus.armor;

		_baseStatus.sameGWAW = FALSE;
		_baseStatus.GWable = FALSE;
		_baseStatus.AWable = FALSE;

		switch (_beforeBuilding->getBuildingNumZerg())
		{
		case BUILDINGNUM_ZERG_HATCHERY:
		case BUILDINGNUM_ZERG_LAIR:
			_baseStatus.commands[0] = COMMAND_NONE; //라바
			_baseStatus.commands[1] = COMMAND_NONE; //렐리포인트
			_baseStatus.commands[2] = COMMAND_NONE;
			_baseStatus.commands[3] = COMMAND_NONE;
			_baseStatus.commands[4] = COMMAND_NONE;
			_baseStatus.commands[5] = COMMAND_NONE;
			_baseStatus.commands[6] = COMMAND_NONE;
			_baseStatus.commands[7] = COMMAND_NONE;
			_baseStatus.commands[8] = COMMAND_ESC;
			break;
		default:
			_baseStatus.commands[0] = COMMAND_NONE;
			_baseStatus.commands[1] = COMMAND_NONE;
			_baseStatus.commands[2] = COMMAND_NONE;
			_baseStatus.commands[3] = COMMAND_NONE;
			_baseStatus.commands[4] = COMMAND_NONE;
			_baseStatus.commands[5] = COMMAND_NONE;
			_baseStatus.commands[6] = COMMAND_NONE;
			_baseStatus.commands[7] = COMMAND_NONE;
			_baseStatus.commands[8] = COMMAND_ESC;
			break;
		}
	}
}
void zbMutating::initBattleStatus(POINT ptTile)
{
	//BattleStatus
	_battleStatus.curCommand = COMMAND_NONE;
	_battleStatus.clicked = false;
	_battleStatus.curHP = 0.0f;			//현재 HP
	_battleStatus.maxHP = _baseStatus.maxHP;			//최대 HP


	tagBattleStatus nextStatus = _nextBuilding->getBattleStatus();

	_battleStatus.ptTile = nextStatus.ptTile;
	_battleStatus.rcBody = nextStatus.rcBody;
	_battleStatus.pt = nextStatus.pt;
	_battleStatus.rcTile = nextStatus.rcTile;
	_battleStatus.rcEllipse = nextStatus.rcEllipse;
}

void zbMutating::release(void)
{
	SAFE_RELEASEDELETE(_progressBar);
	SAFE_DELETE(_zergProductionInfo);
}

void zbMutating::update(void)
{
	Building::update();

	updateProgressBar();

}

void zbMutating::render(int imgOffsetX, int imgOffsetY)
{
	switch (_buildingNumZ)
	{
	case BUILDINGNUM_ZERG_HATCHERY:						   Building::render(-16, -48);		break;
		//case BUILDINGNUM_ZERG_LAIR:					   Building::render(0, 0);		break;
		//case BUILDINGNUM_ZERG_HIVE:					   Building::render(0, 0);		break;
		//case BUILDINGNUM_ZERG_CREEPCOLONY:			   Building::render(0, 0);		break;
		//case BUILDINGNUM_ZERG_SUNKENCOLONY:			   Building::render(0, 0);		break;
		//case BUILDINGNUM_ZERG_SPORECOLONY:			   Building::render(0, 0);		break;
		//case BUILDINGNUM_ZERG_EXTRACTOR:				   Building::render(0, 0);		break;
		//case BUILDINGNUM_ZERG_SPAWNINGPOOL:			   Building::render(0, 0);		break;
		//case BUILDINGNUM_ZERG_EVOLUTIONCHAMBER:		   Building::render(0, 0);		break;
		//case BUILDINGNUM_ZERG_HYDRALISKDEN:			   Building::render(0, 0);		break;
		//case BUILDINGNUM_ZERG_SPIRE:					   Building::render(0, 0);		break;
		//case BUILDINGNUM_ZERG_GREATERSPIRE:			   Building::render(0, 0);		break;
		//case BUILDINGNUM_ZERG_QUEENSNEST:				   Building::render(0, 0);		break;
		//case BUILDINGNUM_ZERG_NYDUSCANAL:				   Building::render(0, 0);		break;
		//case BUILDINGNUM_ZERG_ULTRALISKCAVERN:		   Building::render(0, 0);		break;
		//case BUILDINGNUM_ZERG_DEFILERMOUND:			   Building::render(0, 0);		break;
	}
	

	_progressBar->ZRender(ZORDER_INTERFACE2);

#if 0
	if (_battleStatus.clicked)
	{
		RENDERMANAGER->insertEllipse(ZORDER_GAMEOBJECT, _battleStatus.rcEllipse, PENVERSION_UNITCLICK);
	}

	//_baseStatus.imgBody->frameRender(getMemDC(), 
	//	_battleStatus.ptTile.x * TILESIZE - MAINCAMERA->getCameraX(), 
	//	_battleStatus.ptTile.y * TILESIZE - MAINCAMERA->getCameraY(), 
	//	_battleStatus.bodyFrame.x, _battleStatus.bodyFrame.y);

	RENDERMANAGER->insertImgFrame(ZORDER_GAMEOBJECT, _baseStatus.imgBody,
		_battleStatus.ptTile.x * TILESIZE - MAINCAMERA->getCameraX(),
		_battleStatus.ptTile.y * TILESIZE - MAINCAMERA->getCameraY(),
		1, 1);//_battleStatus.bodyFrame.x, _battleStatus.bodyFrame.y);
#endif
}

void zbMutating::updateBattleStatus(void)
{

}
void zbMutating::updatePosition(void)
{

}
void zbMutating::updateImageFrame(void)
{
	if (!_complete)
	{
		//처음
		if (_battleStatus.bodyFrame.x < 2)
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
				_battleStatus.bodyFrame.x = (_battleStatus.bodyFrame.x == 7) ? 2 : _battleStatus.bodyFrame.x + 1;
			}
		}
	}
	else
	{
		//마지막
		if (_battleStatus.bodyFrame.x < 10)
		{
			_battleStatus.bodyFrame.x++;
		}
		else
		{
			tagBattleStatus temp = _battleStatus;
			temp.bodyFrame.x = 0;
			temp.bodyFrame.y = 0;


			if (_nextBuilding->getBuildingNumZerg() == BUILDINGNUM_ZERG_HATCHERY)
			{
				_nextBuilding->init(_battleStatus.ptTile, 1);
			}


			_nextBuilding->setBattleStatus(temp);
			_player->addBuilding(_nextBuilding);

			_nextObject = _nextBuilding;
			_valid = false;
		}
	}

}

void zbMutating::updateProgressBar(void)
{
	float tick = TIMEMANAGER->getElapsedTime() * BUILDSPEEDMULTIPLY;

	if (_complete == false)
	{
		if (_buildTime + tick >= _buildTimeMax)
		{
			_buildTime = _buildTimeMax;
			_battleStatus.curHP += _battleStatus.maxHP - _buildHP;
		
			_complete = true;
			_battleStatus.bodyFrame.x = 8;
		}
		else
		{
			_buildTime += tick;

			_buildHP += _battleStatus.maxHP * tick / _buildTimeMax;
			_battleStatus.curHP += _battleStatus.maxHP * tick / _buildTimeMax;
		}
	}

	_progressBar->setGauge(_buildTime, _buildTimeMax);
}

void zbMutating::procCommands(void)
{
	if (_battleStatus.curCommand == COMMAND_ESC)
	{
		//SAFE_RELEASEDELETE(_nextBuilding);
	}
	else
	{
		_battleStatus.curCommand = COMMAND_NONE;
	}
}
