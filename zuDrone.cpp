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



	//private:
	//_workState = WORKSTATE_IDLE;
	//_hangingMineral = 0;	//0이면 안들고 있는 것.
	//_hangingGas = 0;		//0이면 안들고 있는 것.


	_zergProductionInfo = new zergProductionInfo;


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
	_stprintf(strKey, L"ZU-droneBody%d", _playerNum);
	_baseStatus.imgBody = IMAGEMANAGER->findImage(strKey);				//이미지-몸체
	_baseStatus.imgFace = NULL;											//이미지-얼굴(우측하단)
	_baseStatus.imgStat1 = IMAGEMANAGER->findImage(L"ZU-droneStat1");	//이미지-스탯상태(1마리클릭했을때)
	_baseStatus.imgStat2 = IMAGEMANAGER->findImage(L"ZU-droneStat2");	//이미지-스탯상태(복수클릭했을때)

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
	_baseStatus.GWAttackType = ATTACKTYPE_ZERG_WORKER;	//공격타입(업그레이드에 사용)
	_stprintf(_baseStatus.GWname, L"가시뼈");			//공격이름
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
	_baseStatus.commands[5] = COMMAND_NONE;// COMMAND_RETURNCARGO;
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
	SAFE_DELETE(_zergProductionInfo);
}

void zuDrone::update(void)
{
	Unit::update();

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_battleStatus.bodyFrame.x++;
		if (_battleStatus.bodyFrame.x > _baseStatus.imgBody->getMaxFrameX())
		{
			_battleStatus.bodyFrame.x = 0;
		}
	}
}

void zuDrone::render(void)
{
	Unit::render();

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
	Unit::updateImageFrame();
}

void zuDrone::procCommands(void)
{
	Unit::procCommands();

	POINT buildsize = { 0, 0 };
	POINT ptBuildTile = { 0, 0 };


	switch (_battleStatus.curCommand)
	{
		//BUILD1
	case COMMAND_BUILD_HATCHERY:
	{
		if (fabs(_battleStatus.pt.x - _battleStatus.ptTarget.x) <= 0.1f
			&& fabs(_battleStatus.pt.y - _battleStatus.ptTarget.y) <= 0.1f)
		{
			buildsize = BUILDSIZE_HATCHERY;
			ptBuildTile = _battleStatus.ptTileTarget;



			tagProduction buildCost = _zergProductionInfo->getZBProductionInfo(BUILDINGNUM_ZERG_HATCHERY);

			if (_player->useResource(buildCost.costMinerals, buildCost.costGas))
			{
				//성공
				zbMutating* hatchery = new zbMutating(_playerNum, BUILDINGNUM_ZERG_HATCHERY);
				hatchery->setLinkAdressZergUpgrade(_zergUpgrade);
				hatchery->setLinkAdressAstar(_aStar);
				hatchery->setLinkAdressPlayer(_player);
				hatchery->init(_battleStatus.ptTileTarget);
				if (_battleStatus.clicked)	hatchery->setClicked(true);

				_player->addBuilding(hatchery);

				_nextObject = hatchery;
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
	break;
	//case COMMAND_BUILD_LAIR:
	//case COMMAND_BUILD_HIVE:
	case COMMAND_BUILD_CREEPCOLONY:
	//case COMMAND_BUILD_SUNKENCOLONY:
	//case COMMAND_BUILD_SPORECOLONY:
	case COMMAND_BUILD_EXTRACTOR:
	case COMMAND_BUILD_SPAWNINGPOOL:
	case COMMAND_BUILD_EVOLUTIONCHAMBER:
	case COMMAND_BUILD_HYDRALISKDEN:
		//BUILD2
	case COMMAND_BUILD_SPIRE:
	//case COMMAND_BUILD_GREATERSPIRE:
	case COMMAND_BUILD_QUEENSNEST:
	case COMMAND_BUILD_NYDUSCANAL:
	case COMMAND_BUILD_ULTRALISKCAVERN:
	case COMMAND_BUILD_DEFILERMOUND:
		break;
	}
}
