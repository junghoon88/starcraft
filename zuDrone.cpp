#include "stdafx.h"
#include "zuDrone.h"
#include "tileNode.h"
#include "zergDefine.h"
#include "player.h"


//저그 건물들
#include "zbMutating.h"
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

#include "nrMineral.h"


zuDrone::zuDrone(PLAYER playerNum)
{
	_valid = true;

	//플레이어 정보
	_playerNum = playerNum;

	//종족
	_race = RACES_ZERG;

	//유닛인지 건물인지
	_isBuilding = false;

	//유닛 고유 번호
	_unitNumZ = UNITNUM_ZERG_DRONE;



	_workState = WORKSTATE_IDLE;
	_hangingMineral = 0;	//0이면 안들고 있는 것.
	_hangingGas = 0;		//0이면 안들고 있는 것.

	_targetMineral = NULL;
	_targetGas = NULL;

	_mineralGatheringTime = 0.0f;
	_mineralGatheringTimeMax = 3.0f;
	_gasGatheringTime = 0.0f;
	_gasGatheringTimeMax = 1.0f;
}


zuDrone::~zuDrone()
{
}

HRESULT zuDrone::init(POINT pt)
{
	initBaseStatus();
	initBattleStatus(pt);



	updatePosition();

	updateBattleStatus();

	return S_OK;
}

void zuDrone::initBaseStatus(void)
{
	//Properties
	_stprintf(_baseStatus.name, L"Zerg Drone");	//이름
												//BaseStatus
	TCHAR strKey[100];
	_stprintf(strKey, L"ZU-drone-Body%d", _playerNum);
	_baseStatus.imgBody = IMAGEMANAGER->findImage(strKey);				//이미지-몸체
	_baseStatus.imgFace = IMAGEMANAGER->findImage(L"ZU-drone-Face");	//이미지-얼굴(우측하단)
	_baseStatus.imgStat1 = IMAGEMANAGER->findImage(L"ZU-drone-Stat1");	//이미지-스탯상태(1마리클릭했을때)
	_baseStatus.imgStat2 = IMAGEMANAGER->findImage(L"ZU-drone-Stat2");	//이미지-스탯상태(복수클릭했을때)

	_baseStatus.unitControl = 1.0f;

	_baseStatus.maxHP = 40.0f;					//HP

	_baseStatus.useSH = FALSE;					//실드여부
	_baseStatus.maxSH = 0.0f;					//실드

	_baseStatus.useMP = FALSE;					//에너지여부
	_baseStatus.maxMP = 0.0f;					//에너지

	_baseStatus.sight = 7.0f;					//시야
	_baseStatus.detector = FALSE;				//디텍터(오버로드, 스포어콜로니)

	_baseStatus.isAir = FALSE;					//공중유닛인지
	_baseStatus.moveSpeed = 5.0f;				//이동속도

	_baseStatus.unitSize = UNITSIZE_SMALL;		//유닛사이즈
	_baseStatus.transportslots = 1;				//수송 슬롯칸 수
	_baseStatus.armor = 0;						//방어력
	_baseStatus.armorPlus = 1;					//추가 방어력

	//combat
	_baseStatus.sameGWAW = FALSE;						//지상공격, 공중공격이 같은지

	_baseStatus.GWable = TRUE;							//지상공격 가능여부
	_baseStatus.GWAttackType = ATTACKTYPE_ZERG_FIXED;	//공격타입(업그레이드에 사용)
	_stprintf(_baseStatus.GWname, L"Spines");			//공격이름
	_baseStatus.GWdamage = 5;							//공격데미지
	_baseStatus.GWdamagePlus = 0;						//공격보너스데미지
	_baseStatus.GWmaxHit = 1;							//공격최대횟수(프레임당) 
	_baseStatus.GWdamageType = DAMAGETYPE_NORMAL;		//공격타입
	_baseStatus.GWcooldown = 22.0f;						//공격쿨타임
	_baseStatus.GWattackRange = 1.0f;					//공격범위

	_baseStatus.AWable = FALSE;							//공중공격 가능여부

	_baseStatus.commands[0] = COMMAND_MOVE;
	_baseStatus.commands[1] = COMMAND_STOP;
	_baseStatus.commands[2] = COMMAND_ATTACK;
	_baseStatus.commands[3] = COMMAND_NONE;
	_baseStatus.commands[4] = COMMAND_GATHER;
	_baseStatus.commands[5] = COMMAND_NONE;
	_baseStatus.commands[6] = COMMAND_BUILD1;
	_baseStatus.commands[7] = COMMAND_BUILD2;
	_baseStatus.commands[8] = COMMAND_BURROW;
}
void zuDrone::initBattleStatus(POINT pt)
{
	//BattleStatus
	_battleStatus.unitState = UNITSTATE_STOP;
	_battleStatus.curCommand = COMMAND_STOP;
	_battleStatus.clicked = false;
	_battleStatus.curHP = _baseStatus.maxHP;			//현재 HP
	_battleStatus.maxHP = _baseStatus.maxHP;			//최대 HP

	_battleStatus.pt.set((float)pt.x, (float)pt.y);							//현재위치
	_battleStatus.moveSpeed = _baseStatus.moveSpeed;
	_battleStatus.angleDeg = 315.0f;			//바라보는 각도
	_battleStatus.direction;		//움직일때 이동방향
}


void zuDrone::release(void)
{
}

void zuDrone::update(void)
{
	Unit::update();

}

void zuDrone::render(void)
{
	if (_workState != WORKSTATE_GATHERING_GAS)
	{
		Unit::render();
	}

}


void zuDrone::updatePosition(void)
{
	POINT pt = _battleStatus.pt.toPoint();
	_battleStatus.ptTile = { pt.x / TILESIZE, pt.y / TILESIZE };			//현재위치한 타일

	POINT unitsize = UNITSIZE_ZERG_DRONE;

	_battleStatus.rcBody = RectMakeCenter(pt.x, pt.y, unitsize.x, unitsize.y);			//유닛 몸체
	_battleStatus.rcEllipse = _battleStatus.rcBody;		//클릭했을때 보여주는 타원
	_battleStatus.rcEllipse.top += unitsize.y / 2;
}

void zuDrone::updateBattleStatus(void)
{
	Unit::updateBattleStatus();

}

void zuDrone::updateImageFrame(void)
{

	float tick = TIMEMANAGER->getElapsedTime();
	
	if (_isBurrowing)
	{
		_battleStatus.unitState = UNITSTATE_STOP;
		_workState = WORKSTATE_IDLE;

		if (_battleStatus.bodyFrame.y != 12)
		{
			_battleStatus.bodyFrame.x = 0;
			_battleStatus.bodyFrame.y = 12;
			_battleStatus.bodyFrameTime = 0.0f;
		}

		_battleStatus.bodyFrameTime += tick;
		if (_battleStatus.bodyFrameTime >= UNIT_BODY_FPS_TIME)
		{
			_battleStatus.bodyFrameTime -= UNIT_BODY_FPS_TIME;
			_battleStatus.bodyFrame.x++;
			if (_battleStatus.bodyFrame.x > 7)
			{
				_battleStatus.bodyFrame.x = 7;
				_isBurrowing = false;
				_battleStatus.isBurrow = true;
				_battleStatus.angleDeg = 315.0f;
			}
		}
	}
	else if (_isUnburrowing)
	{
		_battleStatus.bodyFrameTime += tick;
		if (_battleStatus.bodyFrameTime >= UNIT_BODY_FPS_TIME / 4)
		{
			_battleStatus.bodyFrameTime -= UNIT_BODY_FPS_TIME / 4;
			_battleStatus.bodyFrame.x--;
			if (_battleStatus.bodyFrame.x < 0)
			{
				_battleStatus.bodyFrame.x = 3;
				_isUnburrowing = false;
				_battleStatus.isBurrow = false;
				_battleStatus.curCommand = COMMAND_STOP;
				_battleStatus.oldCommand = COMMAND_STOP;

				if (_hangingMineral > 0)
				{
					_battleStatus.bodyFrame.y = 10;
				}
				else if (_hangingGas > 0)
				{
					_battleStatus.bodyFrame.y = 11;
				}
				else
				{
					_battleStatus.bodyFrame.y = 0;
				}
			}
		}
	}
	else
	{
		if (_battleStatus.isBurrow)
			return;

		Unit::setImageFrameForAngle();

		if (_battleStatus.unitState == UNITSTATE_ATTACK)
		{
			_workState = WORKSTATE_IDLE;

			if (_battleStatus.targetObject == NULL)
			{
				_battleStatus.bodyFrameTime = 0.0f;
				return;
			}

			float attackTime = (_battleStatus.targetObject->getBaseStatus().isAir) ? _baseStatus.AWcooldown : _baseStatus.GWcooldown;
			attackTime = attackTime * UNIT_ATTACK_FPS_TIME; //공격이 1프레임이니까

			_battleStatus.bodyFrameTime += tick;
			if (_battleStatus.bodyFrameTime >= attackTime)
			{
				_battleStatus.bodyFrameTime -= attackTime;
				_battleStatus.targetObject->hitDamage(this);
			}
		}
	}
}

void zuDrone::updateCommandSet(void)
{
	if (_battleStatus.isBurrow)
	{
		_baseStatus.commands[0] = COMMAND_NONE;
		_baseStatus.commands[1] = COMMAND_NONE;
		_baseStatus.commands[2] = COMMAND_NONE;
		_baseStatus.commands[3] = COMMAND_NONE;
		_baseStatus.commands[4] = COMMAND_NONE;
		_baseStatus.commands[5] = COMMAND_NONE;
		_baseStatus.commands[6] = COMMAND_NONE;
		_baseStatus.commands[7] = COMMAND_NONE;
		_baseStatus.commands[8] = COMMAND_UNBURROW;
	}
	else
	{
		_baseStatus.commands[0] = COMMAND_MOVE;
		_baseStatus.commands[1] = COMMAND_STOP;
		_baseStatus.commands[2] = COMMAND_ATTACK;
		_baseStatus.commands[3] = COMMAND_NONE;

		if (_hangingMineral == 0 && _hangingGas == 0)
		{
			_baseStatus.commands[4] = COMMAND_GATHER;
			_baseStatus.commands[5] = COMMAND_NONE;
		}
		else
		{
			_baseStatus.commands[4] = COMMAND_NONE;
			_baseStatus.commands[5] = COMMAND_RETURNCARGO;
		}

		_baseStatus.commands[6] = COMMAND_BUILD1;
		_baseStatus.commands[7] = COMMAND_BUILD2;
		_baseStatus.commands[8] = COMMAND_BURROW;
	}
}


void zuDrone::procCommands(void)
{
	Unit::procCommands();

	BUILDINGNUM_ZERG buildingNum = BUILDINGNUM_ZERG_NONE;

	switch (_battleStatus.curCommand)
	{
	case COMMAND_GATHER:
		if (_battleStatus.targetObject == NULL)
		{
			_battleStatus.curCommand = _battleStatus.oldCommand;
			break;
		}

		if (_targetMineral == _battleStatus.targetObject)
		{
			gatheringMineral();
		}
		else if(_targetGas == _battleStatus.targetObject)
		{
			gatheringGas();
		}
		else
		{
			if (_battleStatus.targetObject->getIsNrMineral() == FALSE
				//&& _battleStatus.targetObject->getIsNrGas() == FALSE
				&& _battleStatus.targetObject->getBuildingNumZerg() != BUILDINGNUM_ZERG_EXTRACTOR)
			{
				//자원이 아니면 무효처리
				_battleStatus.curCommand = _battleStatus.oldCommand;
			}
			else if (_battleStatus.targetObject->getIsNrMineral() == TRUE)
			{
				_targetMineral = _battleStatus.targetObject;
				gatheringMineral();
			}
			else if (_battleStatus.targetObject->getBuildingNumZerg() == BUILDINGNUM_ZERG_EXTRACTOR)
			{
				_targetGas = _battleStatus.targetObject;
				gatheringGas();
			}
		}
		break;
	case COMMAND_RETURNCARGO:
		returnCargo();
		break;

		//BUILD1
	case COMMAND_BUILD_HATCHERY:					buildingNum = BUILDINGNUM_ZERG_HATCHERY;			break;
	case COMMAND_BUILD_CREEPCOLONY:					buildingNum = BUILDINGNUM_ZERG_CREEPCOLONY;			break;
	case COMMAND_BUILD_EXTRACTOR:					buildingNum = BUILDINGNUM_ZERG_EXTRACTOR;			break;
	case COMMAND_BUILD_SPAWNINGPOOL:				buildingNum = BUILDINGNUM_ZERG_SPAWNINGPOOL;		break;
	case COMMAND_BUILD_EVOLUTIONCHAMBER:			buildingNum = BUILDINGNUM_ZERG_EVOLUTIONCHAMBER;	break;
	case COMMAND_BUILD_HYDRALISKDEN:				buildingNum = BUILDINGNUM_ZERG_HYDRALISKDEN;		break;
		//BUILD2
	case COMMAND_BUILD_SPIRE:						buildingNum = BUILDINGNUM_ZERG_SPIRE;				break;
	case COMMAND_BUILD_QUEENSNEST:					buildingNum = BUILDINGNUM_ZERG_QUEENSNEST;			break;
	case COMMAND_BUILD_NYDUSCANAL:					buildingNum = BUILDINGNUM_ZERG_NYDUSCANAL;			break;
	case COMMAND_BUILD_ULTRALISKCAVERN:				buildingNum = BUILDINGNUM_ZERG_ULTRALISKCAVERN;		break;
	case COMMAND_BUILD_DEFILERMOUND:				buildingNum = BUILDINGNUM_ZERG_DEFILERMOUND;		break;
	}

	if (_battleStatus.curCommand != COMMAND_GATHER
		&& _battleStatus.curCommand != COMMAND_RETURNCARGO)
	{
		if (_targetMineral)
		{
			_targetMineral->deleteIsBusy(0x10);
			_targetMineral = NULL;
		}

		if (_targetGas)
		{
			_targetGas->deleteIsBusy(0x10);
			_targetGas = NULL;
		}


		_workState = WORKSTATE_IDLE;
	}

	if (buildingNum != BUILDINGNUM_ZERG_NONE)
	{
		if (buildingNum == BUILDINGNUM_ZERG_EXTRACTOR)
		{
			if (Unit::isInTargetPoint())
			{
				tagProduction buildCost = _player->getZergProductionInfo()->getZBProductionInfo(buildingNum);

				if (_player->useResource(buildCost.costMinerals, buildCost.costGas))
				{
					//성공
					zbMutating* nextBuilding = new zbMutating(_playerNum, buildingNum);
					nextBuilding->setLinkAdressZergUpgrade(_zergUpgrade);
					nextBuilding->setLinkAdressAstar(_aStar);
					nextBuilding->setLinkAdressPlayer(_player);
					nextBuilding->init(_battleStatus.ptTileTarget);

					_player->addBuilding(nextBuilding);

					_nextObject = nextBuilding;
					_valid = false;
				}
				else
				{
					//실패
					_battleStatus.curCommand = COMMAND_STOP;
					_battleStatus.unitState = UNITSTATE_STOP;
				}
			}
			else
			{
				Unit::moveGround();
			}
		}
		else
		{
			if (Unit::isInTargetPoint())
			{
				tagProduction buildCost = _player->getZergProductionInfo()->getZBProductionInfo(buildingNum);

				if (_player->useResource(buildCost.costMinerals, buildCost.costGas))
				{
					//성공
					zbMutating* nextBuilding = new zbMutating(_playerNum, buildingNum);
					nextBuilding->setLinkAdressZergUpgrade(_zergUpgrade);
					nextBuilding->setLinkAdressAstar(_aStar);
					nextBuilding->setLinkAdressPlayer(_player);
					nextBuilding->init(_battleStatus.ptTileTarget);

					_player->addBuilding(nextBuilding);

					_nextObject = nextBuilding;
					_valid = false;
				}
				else
				{
					//실패
					_battleStatus.curCommand = COMMAND_STOP;
					_battleStatus.unitState = UNITSTATE_STOP;
				}
			}
			else
			{
				Unit::moveGround();
			}
		}
	
	}

}



void zuDrone::gatheringMineral(void)
{
	switch (_workState)
	{
	case WORKSTATE_IDLE:
		_workState = WORKSTATE_MOVETO_MINERAL;
		break;
	case WORKSTATE_MOVETO_MINERAL:
		Unit::moveGround();
		if (Unit::isInTargetPoint())
		{
			//미네랄을 향해 바라본다.
			rotateToTarget(_targetMineral);

			//미네랄의 busy 상태를 체크한다.
			if (_targetMineral->getIsBusy() == 0)
			{
				_targetMineral->addIsBusy(0x10);
				_workState = WORKSTATE_GATHERING_MINERAL;
			}
			else
			{
				//10%확률로 다른 미네랄을 찾는다.
				if (RND->getInt(10) < 5)
				{
					gameObject* otherMineral = findOtherMineral();
					if (otherMineral == NULL)
					{
						//못찾았으면 기다린다.
						_workState = WORKSTATE_WAITING_MINERAL;
					}
					else
					{
						_workState = WORKSTATE_IDLE;
						receiveCommand(COMMAND_GATHER, otherMineral);
					}
				}
				else
				{
					_workState = WORKSTATE_WAITING_MINERAL;
				}
			}
		}
		break;
	case WORKSTATE_WAITING_MINERAL:
		if (_targetMineral->getIsBusy() == 0)
		{
			_targetMineral->addIsBusy(0x10);
			_workState = WORKSTATE_GATHERING_MINERAL;
			_battleStatus.bodyFrame.y = 4;
			_mineralGatheringTime = 0.0f;
		}
		break;
	case WORKSTATE_GATHERING_MINERAL:
		updateWorkState();
		if (_hangingMineral > 0)
		{
			_targetMineral->deleteIsBusy(0x10);
			_workState = WORKSTATE_RETURN_MINERAL;
		}
		break;
	case WORKSTATE_RETURN_MINERAL:
		gameObject* cargo = findCargo();
		if (cargo == NULL)
		{
			_battleStatus.curCommand = COMMAND_STOP;
		}
		else
		{
			receiveCommand(COMMAND_RETURNCARGO, cargo);
		}
		break;
	}
}

void zuDrone::gatheringGas(void)
{
	switch (_workState)
	{
	case WORKSTATE_IDLE:
		_workState = WORKSTATE_MOVETO_GAS;
		break;
	case WORKSTATE_MOVETO_GAS:
		Unit::moveGround();
		if (Unit::isInTargetPoint())
		{
			//가스를 향해 바라본다.
			rotateToTarget(_targetGas);

			if (_targetGas->getIsBusy() == 0)
			{
				_targetGas->addIsBusy(0x10);
				_workState = WORKSTATE_GATHERING_GAS;
			}
			else
			{
				_workState = WORKSTATE_WAITING_GAS;
			}
		}
		break;
	case WORKSTATE_WAITING_GAS:
		if (_targetGas->getIsBusy() == 0)
		{
			_targetGas->addIsBusy(0x10);
			_workState = WORKSTATE_GATHERING_GAS;
		}
		break;
	case WORKSTATE_GATHERING_GAS:
		updateWorkState();
		if (_hangingGas > 0)
		{
			_targetGas->deleteIsBusy(0x10);
			_workState = WORKSTATE_RETURN_GAS;
			_gasGatheringTime = 0.0f;
		}
		break;
	case WORKSTATE_RETURN_GAS:
		gameObject* cargo = findCargo();
		if (cargo == NULL)
		{
			_battleStatus.curCommand = COMMAND_STOP;
		}
		else
		{
			receiveCommand(COMMAND_RETURNCARGO, cargo);
		}
		break;
	}
}

void zuDrone::returnCargo(void)
{
	if (_battleStatus.targetObject == NULL)
	{
		gameObject* cargo = findCargo();
		if (cargo == NULL)
		{
			_battleStatus.curCommand = COMMAND_STOP;
		}
		else
		{
			receiveCommand(COMMAND_RETURNCARGO, cargo);
		}
	}
	else
	{
		Unit::moveGround();
		if (Unit::isInTargetPoint())
		{
			_player->addResource(_hangingMineral, _hangingGas);
			_hangingMineral = 0;
			_hangingGas = 0;
			_battleStatus.bodyFrame.y = 0;

			if (_targetMineral)
			{
				_workState = WORKSTATE_IDLE;

				if (_targetMineral)
				{
					receiveCommand(COMMAND_GATHER, _targetMineral);
				}
				else
				{
					receiveCommand(COMMAND_STOP);
				}
			}
			else if(_targetGas)
			{
				_workState = WORKSTATE_IDLE;
				if (_targetGas)
				{
					receiveCommand(COMMAND_GATHER, _targetGas);
				}
				else
				{
					_battleStatus.curCommand = COMMAND_STOP;
				}
			}
			else
			{
				_battleStatus.curCommand = COMMAND_STOP;
			}
		}
	}
}

gameObject* zuDrone::findOtherMineral(void)
{
	int index = -1;
	float distMin = 300;

	for (int i = 0; i < _player->getGamemap()->getVMineral().size(); i++)
	{
		nrMineral* mn = _player->getGamemap()->getVMineral()[i];

		if (mn->getIsBusy() != 0) continue;

		float dist = getDistance(_battleStatus.pt.x, _battleStatus.pt.y,
						mn->getBattleStatus().pt.x, mn->getBattleStatus().pt.y);

		if (distMin > dist)
		{
			distMin = dist;
			index = i;
		}
	}

	if (index >= 0)
	{
		return _player->getGamemap()->getVMineral()[index];
	}


	return NULL;
}
gameObject* zuDrone::findCargo(void)
{
	int index = -1;
	float distMin = TILEX * TILEY * TILESIZE;

	for (int i = 0; i < _player->getBuildings().size(); i++)
	{
		Building* bd = _player->getBuildings()[i];
		if (bd->getBuildingNumZerg() != BUILDINGNUM_ZERG_HATCHERY
			&& bd->getBuildingNumZerg() != BUILDINGNUM_ZERG_LAIR
			&& bd->getBuildingNumZerg() != BUILDINGNUM_ZERG_HIVE)
		{
			continue;
		}

		float dist = getDistance(_battleStatus.pt.x, _battleStatus.pt.y,
								bd->getBattleStatus().pt.x, bd->getBattleStatus().pt.y);

		if (distMin > dist)
		{
			distMin = dist;
			index = i;
		}
	}

	if (index >= 0)
	{
		return _player->getBuildings()[index];
	}

	return NULL;
}

void zuDrone::updateWorkState(void)
{
	if (_workState == WORKSTATE_GATHERING_MINERAL)
	{
		_mineralGatheringTime += TIMEMANAGER->getElapsedTime();

		if (_mineralGatheringTime >= _mineralGatheringTimeMax)
		{
			_mineralGatheringTime = 0.0f;
			_hangingMineral = _targetMineral->gatherMineral();
			_battleStatus.bodyFrame.y = 10;

			if (_targetMineral->getAmountMineral() == 0)
			{
				_targetMineral = findOtherMineral();
				if (_targetMineral == NULL)
				{
					_battleStatus.targetObject = NULL;
				}
			}
			return;
		}

		_battleStatus.bodyFrameTime += TIMEMANAGER->getElapsedTime();
		if (_battleStatus.bodyFrameTime >= UNIT_BODY_FPS_TIME)
		{
			_battleStatus.bodyFrameTime -= UNIT_BODY_FPS_TIME;
			_battleStatus.bodyFrame.y++;
			if (_battleStatus.bodyFrame.y > 9)
				_battleStatus.bodyFrame.y = 4;
		}
	}
	else if (_workState == WORKSTATE_GATHERING_GAS)
	{
		_gasGatheringTime += TIMEMANAGER->getElapsedTime();

		if (_gasGatheringTime >= _gasGatheringTimeMax)
		{
			_gasGatheringTime = 0.0f;
			_hangingGas = _targetGas->gatherGas();
			_battleStatus.bodyFrame.y = 11;
		}
	}
}

void zuDrone::rotateToTarget(gameObject* obj)
{
	_battleStatus.angleDeg = getAngleDeg(_battleStatus.pt.x, _battleStatus.pt.y,
		obj->getBattleStatus().pt.x, obj->getBattleStatus().pt.y);

	Unit::setImageFrameForAngle();
}
