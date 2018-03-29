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
	_buildingNumZ = BUILDINGNUM_ZERG_MUTATING;
	_beforeBuildingNum = BUILDINGNUM_ZERG_NONE;
	_nextBuildingNum = buildingNum;

	_beforeBuilding = NULL;
	_nextBuilding = NULL;

	
	
	_buildHP = 0.0f;
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
	_buildingNumZ = beforeBuilding->getBuildingNumZerg();
	_beforeBuildingNum = beforeBuilding->getBuildingNumZerg();
	_nextBuildingNum = buildingNum;

	_beforeBuilding = beforeBuilding;
	_nextBuilding = NULL;

	

	_buildHP = 0.0f;
}

zbMutating::~zbMutating()
{
}

HRESULT zbMutating::init(POINT ptTile)
{
	initNextBuilding(ptTile);
	initBaseStatus();
	initBattleStatus(ptTile);
	initProcessing();




	return S_OK;
}

void zbMutating::initNextBuilding(POINT ptTile)
{
	switch (_nextBuildingNum)
	{
	case BUILDINGNUM_ZERG_HATCHERY:					_nextBuilding = new zbHatchery(_playerNum);				break;
	case BUILDINGNUM_ZERG_LAIR:						_nextBuilding = new zbLair(_playerNum);					break;
	case BUILDINGNUM_ZERG_HIVE:						_nextBuilding = new zbHive(_playerNum);					break;
	case BUILDINGNUM_ZERG_CREEPCOLONY:				_nextBuilding = new zbCreepColony(_playerNum);			break;
	case BUILDINGNUM_ZERG_SUNKENCOLONY:				_nextBuilding = new zbSunkenColony(_playerNum);			break;
	case BUILDINGNUM_ZERG_SPORECOLONY:				_nextBuilding = new zbSporeColony(_playerNum);			break;
	case BUILDINGNUM_ZERG_EXTRACTOR:				_nextBuilding = new zbExtractor(_playerNum);			break;
	case BUILDINGNUM_ZERG_SPAWNINGPOOL:				_nextBuilding = new zbSpawningPool(_playerNum);			break;
	case BUILDINGNUM_ZERG_EVOLUTIONCHAMBER:			_nextBuilding = new zbEvolutionChamber(_playerNum);		break;
	case BUILDINGNUM_ZERG_HYDRALISKDEN:				_nextBuilding = new zbHydraliskDen(_playerNum);			break;
	case BUILDINGNUM_ZERG_SPIRE:					_nextBuilding = new zbSpire(_playerNum);				break;
	case BUILDINGNUM_ZERG_GREATERSPIRE:				_nextBuilding = new zbGreaterSpire(_playerNum);			break;
	case BUILDINGNUM_ZERG_QUEENSNEST:				_nextBuilding = new zbQueensNest(_playerNum);			break;
	case BUILDINGNUM_ZERG_NYDUSCANAL:				_nextBuilding = new zbNydusCanal(_playerNum);			break;
	case BUILDINGNUM_ZERG_ULTRALISKCAVERN:			_nextBuilding = new zbUltraliskCavern(_playerNum);		break;
	case BUILDINGNUM_ZERG_DEFILERMOUND:				_nextBuilding = new zbDefilerMound(_playerNum);			break;
	}

	_nextBuilding->setLinkAdressZergUpgrade(_zergUpgrade);
	_nextBuilding->setLinkAdressAstar(_aStar);
	_nextBuilding->setLinkAdressPlayer(_player);
	_nextBuilding->init(ptTile);

	_nextObject = _nextBuilding;
}


void zbMutating::initBaseStatus(void)
{
	//드론에서 새로 만드는 건물일 경우 HP를 그대로 받아오지만 
	//건물자체가 업그레이드 하는 경우 현재 HP를 그대로 가져간다. 
	//(예->Spire 피가 600 이었다가 완성되면 1000으로 됨. 하지만 이름은 그레이트 스파이어임)

	tagBaseStatus nextStatus = _nextBuilding->getBaseStatus();


	switch (_nextBuildingNum)
	{
	case BUILDINGNUM_ZERG_HATCHERY:				_baseStatus.imgBody = IMAGEMANAGER->findImage(L"ZB-MutatingBody2");		break;
	case BUILDINGNUM_ZERG_LAIR:					_baseStatus.imgBody = IMAGEMANAGER->findImage(L"ZB-MutatingBody2");		break;
	case BUILDINGNUM_ZERG_HIVE:					_baseStatus.imgBody = IMAGEMANAGER->findImage(L"ZB-MutatingBody2");		break;
	case BUILDINGNUM_ZERG_CREEPCOLONY:			_baseStatus.imgBody = IMAGEMANAGER->findImage(L"ZB-MutatingBody1");		break;
	case BUILDINGNUM_ZERG_SUNKENCOLONY:			_baseStatus.imgBody = IMAGEMANAGER->findImage(L"ZB-MutatingBody1");		break;
	case BUILDINGNUM_ZERG_SPORECOLONY:			_baseStatus.imgBody = IMAGEMANAGER->findImage(L"ZB-MutatingBody1");		break;
	case BUILDINGNUM_ZERG_EXTRACTOR:			_baseStatus.imgBody = IMAGEMANAGER->findImage(L"ZB-MutatingBody3");		break;
	case BUILDINGNUM_ZERG_SPAWNINGPOOL:			_baseStatus.imgBody = IMAGEMANAGER->findImage(L"ZB-MutatingBody2");		break;
	case BUILDINGNUM_ZERG_EVOLUTIONCHAMBER:		_baseStatus.imgBody = IMAGEMANAGER->findImage(L"ZB-MutatingBody2");		break;
	case BUILDINGNUM_ZERG_HYDRALISKDEN:			_baseStatus.imgBody = IMAGEMANAGER->findImage(L"ZB-MutatingBody2");		break;
	case BUILDINGNUM_ZERG_SPIRE:				_baseStatus.imgBody = IMAGEMANAGER->findImage(L"ZB-MutatingBody1");		break;
	case BUILDINGNUM_ZERG_GREATERSPIRE:			_baseStatus.imgBody = IMAGEMANAGER->findImage(L"ZB-MutatingBody1");		break;
	case BUILDINGNUM_ZERG_QUEENSNEST:			_baseStatus.imgBody = IMAGEMANAGER->findImage(L"ZB-MutatingBody2");		break;
	case BUILDINGNUM_ZERG_NYDUSCANAL:			_baseStatus.imgBody = IMAGEMANAGER->findImage(L"ZB-MutatingBody2");		break;
	case BUILDINGNUM_ZERG_ULTRALISKCAVERN:		_baseStatus.imgBody = IMAGEMANAGER->findImage(L"ZB-MutatingBody2");		break;
	case BUILDINGNUM_ZERG_DEFILERMOUND:			_baseStatus.imgBody = IMAGEMANAGER->findImage(L"ZB-MutatingBody2");		break;
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

		_baseStatus.publicControl = beforeStatus.publicControl;

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
			_baseStatus.commands[0] = COMMAND_SELECT_LARVA; //라바
			_baseStatus.commands[1] = COMMAND_SETRALLYPOINT; //렐리포인트
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

	if (_beforeBuilding == NULL)
	{
		_battleStatus.curHP = 0.0f;					
		_battleStatus.maxHP = _baseStatus.maxHP;	
	}
	else
	{
		_battleStatus.curHP = _beforeBuilding->getBattleStatus().curHP;
		_battleStatus.maxHP = _baseStatus.maxHP;
	}



	tagBattleStatus nextStatus = _nextBuilding->getBattleStatus();

	_battleStatus.ptTile = nextStatus.ptTile;
	_battleStatus.rcBody = nextStatus.rcBody;
	_battleStatus.pt = nextStatus.pt;
	_battleStatus.rcTile = nextStatus.rcTile;
	_battleStatus.rcEllipse = nextStatus.rcEllipse;
}

void zbMutating::initProcessing(void)
{
	_processing.type = PROCESSING_MUTATING;

	switch (_nextBuildingNum)
	{
	case BUILDINGNUM_ZERG_HATCHERY:					_processing.command = COMMAND_BUILD_HATCHERY;			break;
	case BUILDINGNUM_ZERG_LAIR:						_processing.command = COMMAND_BUILD_LAIR;				break;
	case BUILDINGNUM_ZERG_HIVE:						_processing.command = COMMAND_BUILD_HIVE;				break;
	case BUILDINGNUM_ZERG_CREEPCOLONY:				_processing.command = COMMAND_BUILD_CREEPCOLONY;		break;
	case BUILDINGNUM_ZERG_SUNKENCOLONY:				_processing.command = COMMAND_BUILD_SUNKENCOLONY;		break;
	case BUILDINGNUM_ZERG_SPORECOLONY:				_processing.command = COMMAND_BUILD_SPORECOLONY;		break;
	case BUILDINGNUM_ZERG_EXTRACTOR:				_processing.command = COMMAND_BUILD_EXTRACTOR;			break;
	case BUILDINGNUM_ZERG_SPAWNINGPOOL:				_processing.command = COMMAND_BUILD_SPAWNINGPOOL;		break;
	case BUILDINGNUM_ZERG_EVOLUTIONCHAMBER:			_processing.command = COMMAND_BUILD_EVOLUTIONCHAMBER;	break;
	case BUILDINGNUM_ZERG_HYDRALISKDEN:				_processing.command = COMMAND_BUILD_HYDRALISKDEN;		break;
	case BUILDINGNUM_ZERG_SPIRE:					_processing.command = COMMAND_BUILD_SPIRE;				break;
	case BUILDINGNUM_ZERG_GREATERSPIRE:				_processing.command = COMMAND_BUILD_GREATERSPIRE;		break;
	case BUILDINGNUM_ZERG_QUEENSNEST:				_processing.command = COMMAND_BUILD_QUEENSNEST;			break;
	case BUILDINGNUM_ZERG_NYDUSCANAL:				_processing.command = COMMAND_BUILD_NYDUSCANAL;			break;
	case BUILDINGNUM_ZERG_ULTRALISKCAVERN:			_processing.command = COMMAND_BUILD_ULTRALISKCAVERN;	break;
	case BUILDINGNUM_ZERG_DEFILERMOUND:				_processing.command = COMMAND_BUILD_DEFILERMOUND;		break;
	}

	_processing.img = NULL;
	_processing.curTime = 0.0f;
	_processing.maxTime = _player->getZergProductionInfo()->getZBProductionInfo(_nextBuildingNum).buildTime;
}

void zbMutating::release(void)
{
}

void zbMutating::update(void)
{
	Building::update();

	updateProcessing();

	if (_buildingNumZ == BUILDINGNUM_ZERG_HATCHERY || _buildingNumZ == BUILDINGNUM_ZERG_HATCHERY)
	{
		larvaValidCheck();
		responeLarva();
	}
}

void zbMutating::render(int imgOffsetX, int imgOffsetY)
{
	switch (_nextBuildingNum)
	{
	case BUILDINGNUM_ZERG_HATCHERY:					Building::render(16, 48);		break;
	case BUILDINGNUM_ZERG_LAIR:						Building::render(16, 48);		break;
	case BUILDINGNUM_ZERG_HIVE:						Building::render(16, 48);		break;
	case BUILDINGNUM_ZERG_CREEPCOLONY:				Building::render(48, 64);		break;
	case BUILDINGNUM_ZERG_SUNKENCOLONY:				Building::render(48, 64);		break;
	case BUILDINGNUM_ZERG_SPORECOLONY:				Building::render(48, 64);		break;
	case BUILDINGNUM_ZERG_EXTRACTOR:				Building::render(24, 64);		break;
	case BUILDINGNUM_ZERG_SPAWNINGPOOL:				Building::render(32, 64);		break;
	case BUILDINGNUM_ZERG_EVOLUTIONCHAMBER:			Building::render(32, 64);		break;
	case BUILDINGNUM_ZERG_HYDRALISKDEN:				Building::render(32, 64);		break;
	case BUILDINGNUM_ZERG_SPIRE:					Building::render(48, 64);		break;
	case BUILDINGNUM_ZERG_GREATERSPIRE:				Building::render(48, 64);		break;
	case BUILDINGNUM_ZERG_QUEENSNEST:				Building::render(32, 64);		break;
	case BUILDINGNUM_ZERG_NYDUSCANAL:				Building::render(32, 64);		break;
	case BUILDINGNUM_ZERG_ULTRALISKCAVERN:			Building::render(32, 64);		break;
	case BUILDINGNUM_ZERG_DEFILERMOUND:				Building::render(16, 64);		break;
	}
	

}

void zbMutating::larvaValidCheck(void)
{
	for (int i = 0; i < _vLarva.size();)
	{
		if (_vLarva[i]->getValid() == false)
		{
			//여기서 delete는 하지 않는다.
			_vLarva.erase(_vLarva.begin() + i);
		}
		else ++i;
	}
}

void zbMutating::responeLarva(void)
{
	if (_vLarva.size() >= LARVA_MAX)
	{
		if (_vLarva.size() > LARVA_MAX)
		{
			printf("");
		}
		_larvaResponeTime = 0.0f;
		return;
	}

	_larvaResponeTime += TIMEMANAGER->getElapsedTime() * BUILDSPEEDMULTIPLY * 0.1f;

	float time = _player->getZergProductionInfo()->getZUProductionInfo(UNITNUM_ZERG_LARVA).buildTime;

	if (_larvaResponeTime >= time)
	{
		_larvaResponeTime -= time;

		if (_vLarva.size() == 0)
		{
			POINT larvaSize = UNITSIZE_ZERG_LARVA;
			POINT pt;
			pt.x = _battleStatus.rcBody.left + larvaSize.x * 0.5f;
			pt.y = _battleStatus.rcBody.bottom + larvaSize.y * 0.5f;

			createLarva(pt);
			return;
		}
		else
		{
			for (int i = 0; i < LARVA_MAX; i++)
			{
				POINT larvaSize = UNITSIZE_ZERG_LARVA;
				POINT pt;
				pt.x = _battleStatus.rcBody.left + larvaSize.x * (i + 0.5f);
				pt.y = _battleStatus.rcBody.bottom + larvaSize.y * 0.5f;

				//겹치는지 확인하고 
				bool overlap = false;
				for (int j = 0; j < _vLarva.size(); j++)
				{
					RECT rcBody = _vLarva[j]->getBattleStatus().rcBody;
					if (PtInRect(&rcBody, pt))
					{
						overlap = true;
						break;
					}
				}
				//겹치지 않았으면 생성
				if (overlap == false)
				{
					createLarva(pt);
					return;
				}
			}
		}
	}
}

void zbMutating::createLarva(POINT pt)
{
	zuLarva* larva = new zuLarva(_playerNum);
	larva->setLinkAdressZergUpgrade(_zergUpgrade);
	larva->setLinkAdressAstar(_aStar);
	larva->setLinkAdressPlayer(_player);
	larva->init(pt);

	_player->addUnit(larva);
	_vLarva.push_back(larva);
}


void zbMutating::updateBattleStatus(void)
{

}
void zbMutating::updatePosition(void)
{

}
void zbMutating::updateImageFrame(void)
{
	if (!_processing.complete)
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
			else if (_nextBuilding->getBuildingNumZerg() == BUILDINGNUM_ZERG_LAIR)
			{
				zbLair* lair = (zbLair*)_nextBuilding;
				lair->setLarvas(_vLarva);
				lair->setLarvaResponeTime(_larvaResponeTime);
			}
			else if (_nextBuilding->getBuildingNumZerg() == BUILDINGNUM_ZERG_HIVE)
			{
				zbHive* hive = (zbHive*)_nextBuilding;
				hive->setLarvas(_vLarva);
				hive->setLarvaResponeTime(_larvaResponeTime);
			}
			else if (_nextBuilding->getBuildingNumZerg() == BUILDINGNUM_ZERG_EXTRACTOR)
			{
				zbExtractor* ext = (zbExtractor*)_nextBuilding;
				ext->findNrGas();
			}

			//다음건물 HP가 낮을 경우(성큰콜로니)
			if (_beforeBuildingNum != BUILDINGNUM_ZERG_NONE)
			{
				if (_nextBuilding->getBattleStatus().maxHP < _battleStatus.maxHP)
				{
					float ratio = _nextBuilding->getBattleStatus().maxHP / _battleStatus.maxHP;
					temp.curHP = temp.curHP * ratio;
				}
				else if (_nextBuilding->getBattleStatus().maxHP > _battleStatus.maxHP)
				{
					FLOAT gapHP = _nextBuilding->getBattleStatus().maxHP - _battleStatus.maxHP;
					temp.curHP += gapHP;
				}
			}
			temp.maxHP = _nextBuilding->getBaseStatus().maxHP;

			_nextBuilding->setBattleStatus(temp);
			_player->addBuilding(_nextBuilding);

			//_nextObject = _nextBuilding;
			_valid = false;
		}
	}

}

void zbMutating::updateProcessing(void)
{
	if (_processing.type == PROCESSING_NONE)
		return;

	float tick = TIMEMANAGER->getElapsedTime() * BUILDSPEEDMULTIPLY;

	if (_processing.complete == false)
	{
		if (_processing.curTime + tick >= _processing.maxTime)
		{
			_processing.curTime = _processing.maxTime;

			if (_beforeBuildingNum == BUILDINGNUM_ZERG_NONE)
			{
				_battleStatus.curHP += _battleStatus.maxHP - _buildHP;
			}
		
			_processing.complete = true;
			_battleStatus.bodyFrame.x = 8;
		}
		else
		{
			_processing.curTime += tick;

			_buildHP += _battleStatus.maxHP * tick / _processing.maxTime;

			if (_beforeBuildingNum == BUILDINGNUM_ZERG_NONE)
			{
				_battleStatus.curHP += _battleStatus.maxHP * tick / _processing.maxTime;
			}
		}
	}
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
