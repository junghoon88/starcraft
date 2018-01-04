#include "stdafx.h"
#include "zuDrone.h"
#include "tileNode.h"
#include "zergDefine.h"
#include "player.h"


//���� �ǹ���
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

	//�÷��̾� ����
	_playerNum = playerNum;

	//����
	_race = RACES_ZERG;

	//�������� �ǹ�����
	_isBuilding = false;

	//���� ���� ��ȣ
	_unitNumZ = UNITNUM_ZERG_DRONE;



	//private:
	//_workState = WORKSTATE_IDLE;
	//_hangingMineral = 0;	//0�̸� �ȵ�� �ִ� ��.
	//_hangingGas = 0;		//0�̸� �ȵ�� �ִ� ��.


	


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
	_stprintf(_baseStatus.name, L"Zerg Drone");	//�̸�
												//BaseStatus
	TCHAR strKey[100];
	_stprintf(strKey, L"ZU-drone-Body%d", _playerNum);
	_baseStatus.imgBody = IMAGEMANAGER->findImage(strKey);				//�̹���-��ü
	_baseStatus.imgFace = IMAGEMANAGER->findImage(L"ZU-drone-Face");	//�̹���-��(�����ϴ�)
	_baseStatus.imgStat1 = IMAGEMANAGER->findImage(L"ZU-drone-Stat1");	//�̹���-���Ȼ���(1����Ŭ��������)
	_baseStatus.imgStat2 = IMAGEMANAGER->findImage(L"ZU-drone-Stat2");	//�̹���-���Ȼ���(����Ŭ��������)

	_baseStatus.unitControl = 1.0f;

	_baseStatus.maxHP = 40.0f;					//HP

	_baseStatus.useSH = FALSE;					//�ǵ忩��
	_baseStatus.maxSH = 0.0f;					//�ǵ�

	_baseStatus.useMP = FALSE;					//����������
	_baseStatus.maxMP = 0.0f;					//������

	_baseStatus.sight = 7.0f;					//�þ�
	_baseStatus.detector = FALSE;				//������(�����ε�, �������ݷδ�)

	_baseStatus.isAir = FALSE;					//������������
	_baseStatus.moveSpeed = 5.0f;				//�̵��ӵ�

	_baseStatus.unitSize = UNITSIZE_SMALL;		//���ֻ�����
	_baseStatus.transportslots = 1;				//���� ����ĭ ��
	_baseStatus.armor = 0;						//����
	_baseStatus.armorPlus = 1;					//�߰� ����

	//combat
	_baseStatus.sameGWAW = FALSE;						//�������, ���߰����� ������

	_baseStatus.GWable = TRUE;							//������� ���ɿ���
	_baseStatus.GWAttackType = ATTACKTYPE_ZERG_FIXED;	//����Ÿ��(���׷��̵忡 ���)
	_stprintf(_baseStatus.GWname, L"Spines");			//�����̸�
	_baseStatus.GWdamage = 5;							//���ݵ�����
	_baseStatus.GWdamagePlus = 0;						//���ݺ��ʽ�������
	_baseStatus.GWmaxHit = 1;							//�����ִ�Ƚ��(�����Ӵ�) 
	_baseStatus.GWdamageType = DAMAGETYPE_NORMAL;		//����Ÿ��
	_baseStatus.GWcooldown = 22.0f;						//������Ÿ��
	_baseStatus.GWattackRange = 1.0f;					//���ݹ���

	_baseStatus.AWable = FALSE;							//���߰��� ���ɿ���

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
	_battleStatus.curHP = _baseStatus.maxHP;			//���� HP
	_battleStatus.maxHP = _baseStatus.maxHP;			//�ִ� HP

	_battleStatus.pt.set((float)pt.x, (float)pt.y);							//������ġ
	_battleStatus.moveSpeed = _baseStatus.moveSpeed;
	_battleStatus.angleDeg = 315.0f;			//�ٶ󺸴� ����
	_battleStatus.direction;		//�����϶� �̵�����
}


void zuDrone::release(void)
{
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
	_battleStatus.ptTile = { pt.x / TILESIZE, pt.y / TILESIZE };			//������ġ�� Ÿ��

	POINT unitsize = UNITSIZE_ZERG_DRONE;

	_battleStatus.rcBody = RectMakeCenter(pt.x, pt.y, unitsize.x, unitsize.y);			//���� ��ü
	_battleStatus.rcEllipse = _battleStatus.rcBody;		//Ŭ�������� �����ִ� Ÿ��
	_battleStatus.rcEllipse.top += unitsize.y / 2;
}

void zuDrone::updateBattleStatus(void)
{
	Unit::updateBattleStatus();


}

void zuDrone::updateImageFrame(void)
{
	Unit::setImageFrameForAngle();
}

void zuDrone::procCommands(void)
{
	Unit::procCommands();

	BUILDINGNUM_ZERG buildingNum = BUILDINGNUM_ZERG_NONE;

	switch (_battleStatus.curCommand)
	{
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


	if (buildingNum != BUILDINGNUM_ZERG_NONE)
	{
		if (Unit::isInTargetPoint())
		{
			tagProduction buildCost = _player->getZergProductionInfo()->getZBProductionInfo(buildingNum);

			if (_player->useResource(buildCost.costMinerals, buildCost.costGas))
			{
				//����
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
				//����
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
