#include "stdafx.h"
#include "zbLair.h"

#include "zergDefine.h"
#include "player.h"

zbLair::zbLair(PLAYER playerNum)
{
	_valid = true;

	//플레이어 정보
	_playerNum = playerNum;

	//종족
	_race = RACES_ZERG;

	//유닛인지 건물인지
	_isBuilding = true;

	//유닛 고유 번호
	_buildingNumZ = BUILDINGNUM_ZERG_LAIR;
}


zbLair::~zbLair()
{
}

HRESULT zbLair::init(POINT ptTile)
{
	initBaseStatus();
	initBattleStatus(ptTile);

	return S_OK;
}

void zbLair::initBaseStatus(void)
{
	//Properties
	_stprintf(_baseStatus.name, L"Zerg Lair");

	TCHAR strKey[100];
	_stprintf(strKey, L"ZB-lair-Body%d", _playerNum);
	_baseStatus.imgBody = IMAGEMANAGER->findImage(strKey);
	_baseStatus.imgFace = IMAGEMANAGER->findImage(L"ZB-Face");
	_baseStatus.imgStat1 = IMAGEMANAGER->findImage(L"ZB-lair-Stat1");
	_baseStatus.imgStat2 = NULL;

	_baseStatus.publicControl = 1.0f;

	_baseStatus.maxHP = 1800.0f;

	_baseStatus.useSH = FALSE;
	_baseStatus.maxSH = 0.0f;

	_baseStatus.useMP = FALSE;
	_baseStatus.maxMP = 0.0f;

	_baseStatus.sight = 7.0f;
	_baseStatus.detector = FALSE;

	_baseStatus.isAir = FALSE;

	_baseStatus.unitSize = UNITSIZE_LARGE;
	_baseStatus.transportslots = 0;
	_baseStatus.armor = 1;
	//_baseStatus.armorPlus = 1;				

	//combat
	_baseStatus.sameGWAW = FALSE;
	_baseStatus.GWable = FALSE;
	_baseStatus.AWable = FALSE;


}
void zbLair::initBattleStatus(POINT ptTile)
{
	//BattleStatus
	_battleStatus.curCommand = COMMAND_NONE;
	_battleStatus.clicked = false;
	_battleStatus.curHP = _baseStatus.maxHP;			//현재 HP
	_battleStatus.maxHP = _baseStatus.maxHP;			//최대 HP

	POINT buildTileSize = BUILDSIZE_LAIR;

	_battleStatus.ptTile = ptTile;
	_battleStatus.rcBody = RectMake(ptTile.x * TILESIZE, ptTile.y * TILESIZE, buildTileSize.x * TILESIZE, buildTileSize.y * TILESIZE);
	_battleStatus.pt.set((_battleStatus.rcBody.left + _battleStatus.rcBody.right) * 0.5f, (_battleStatus.rcBody.top + _battleStatus.rcBody.bottom) * 0.5f);
	_battleStatus.rcTile = RectMake(ptTile.x, ptTile.y, buildTileSize.x, buildTileSize.y);
	_battleStatus.rcEllipse = _battleStatus.rcBody;
}


void zbLair::release(void)
{

}

void zbLair::update(void)
{
	Building::update();

}

void zbLair::render(int imgOffsetX, int imgOffsetY)
{
	POINT imgOffset = BUILDIMAGEOFFSET_LAIR;
	Building::render(imgOffset.x * TILESIZE, imgOffset.y * TILESIZE);

}


void zbLair::updateBattleStatus(void)
{

}
void zbLair::updatePosition(void)
{

}
void zbLair::updateImageFrame(void)
{

}

void zbLair::updateProcessing(void)
{
	Building::updateProcessing();

}

void zbLair::updateCommandSet(void)
{
	_baseStatus.commands[0] = COMMAND_SELECT_LARVA;
	_baseStatus.commands[1] = COMMAND_SETRALLYPOINT;

	if (_processing.type == PROCESSING_EVOLVING)
	{
		_baseStatus.commands[2] = COMMAND_NONE;
		_baseStatus.commands[3] = COMMAND_NONE;
		_baseStatus.commands[4] = COMMAND_NONE;
		_baseStatus.commands[5] = COMMAND_NONE;
		_baseStatus.commands[6] = COMMAND_NONE;
		_baseStatus.commands[8] = COMMAND_ESC;
	}
	else
	{
		tagEvolution evoBurrow = _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_BURROW];
		tagEvolution evoVectral = _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_VECTRAL_SACS];
		tagEvolution evoAntennae = _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_ANTENNAE];
		tagEvolution evoPneumati = _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_PNEUMATIZED_CARAPACE];

		if (evoBurrow.complete || evoBurrow.isProcessing)
		{
			_baseStatus.commands[2] = COMMAND_NONE;
		}
		else
		{
			_baseStatus.commands[2] = COMMAND_EVOLUTION_ZERG_BURROW;
		}

		if (evoVectral.complete || evoVectral.isProcessing)
		{
			_baseStatus.commands[3] = COMMAND_NONE;
		}
		else
		{
			_baseStatus.commands[3] = COMMAND_EVOLUTION_ZERG_VECTRAL_SACS;
		}

		if (evoAntennae.complete || evoAntennae.isProcessing)
		{
			_baseStatus.commands[4] = COMMAND_NONE;
		}
		else
		{
			_baseStatus.commands[4] = COMMAND_EVOLUTION_ZERG_ANTENNAE;
		}

		if (evoPneumati.complete || evoPneumati.isProcessing)
		{
			_baseStatus.commands[5] = COMMAND_NONE;
		}
		else
		{
			_baseStatus.commands[5] = COMMAND_EVOLUTION_ZERG_PNEUMATIZED_CARAPACE;
		}

		_baseStatus.commands[6] = COMMAND_BUILD_HIVE;
		_baseStatus.commands[8] = COMMAND_NONE;
	}
}

void zbLair::procCommands(void)
{
	switch (_battleStatus.curCommand)
	{
		case COMMAND_SETRALLYPOINT:
		break;

		case COMMAND_EVOLUTION_ZERG_BURROW:
		{
			tagEvolution evolution = _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_BURROW];

			if (_player->useResource(evolution.cost.mineral, evolution.cost.gas))
			{
				//성공
				_processing.type = PROCESSING_EVOLVING;
				_processing.command = _battleStatus.curCommand;
				_processing.img = IMAGEMANAGER->findImage(L"command-evolution_zerg_evolve_burrow");
				_processing.curTime = 0.0f;
				_processing.maxTime = evolution.cost.duration;
				_processing.complete = false;

				evolution.isProcessing = true;
			}
			else
			{
				//실패
			}
			_battleStatus.curCommand = COMMAND_NONE;
		}
		break;

		case COMMAND_EVOLUTION_ZERG_VECTRAL_SACS:
		{
			tagEvolution evolution = _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_VECTRAL_SACS];

			if (_player->useResource(evolution.cost.mineral, evolution.cost.gas))
			{
				//성공
				_processing.type = PROCESSING_EVOLVING;
				_processing.command = _battleStatus.curCommand;
				_processing.img = IMAGEMANAGER->findImage(L"command-evolution_zerg_vectral_sacs");
				_processing.curTime = 0.0f;
				_processing.maxTime = evolution.cost.duration;
				_processing.complete = false;

				evolution.isProcessing = true;
			}
			else
			{
				//실패
			}
			_battleStatus.curCommand = COMMAND_NONE;
		}
		break;

		case COMMAND_EVOLUTION_ZERG_ANTENNAE:
		{
			tagEvolution evolution = _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_ANTENNAE];

			if (_player->useResource(evolution.cost.mineral, evolution.cost.gas))
			{
				//성공
				_processing.type = PROCESSING_EVOLVING;
				_processing.command = _battleStatus.curCommand;
				_processing.img = IMAGEMANAGER->findImage(L"command-evolution_zerg_antennae");
				_processing.curTime = 0.0f;
				_processing.maxTime = evolution.cost.duration;
				_processing.complete = false;

				evolution.isProcessing = true;
			}
			else
			{
				//실패
			}
			_battleStatus.curCommand = COMMAND_NONE;
		}
		break;

		case COMMAND_EVOLUTION_ZERG_PNEUMATIZED_CARAPACE:
		{
			tagEvolution evolution = _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_PNEUMATIZED_CARAPACE];

			if (_player->useResource(evolution.cost.mineral, evolution.cost.gas))
			{
				//성공
				_processing.type = PROCESSING_EVOLVING;
				_processing.command = _battleStatus.curCommand;
				_processing.img = IMAGEMANAGER->findImage(L"command-evolution_zerg_pneumatized_carapace");
				_processing.curTime = 0.0f;
				_processing.maxTime = evolution.cost.duration;
				_processing.complete = false;

				evolution.isProcessing = true;
			}
			else
			{
				//실패
			}
			_battleStatus.curCommand = COMMAND_NONE;
		}
		break;

		case COMMAND_BUILD_HIVE:
		{
			tagProduction buildCost = _player->getZergProductionInfo()->getZBProductionInfo(BUILDINGNUM_ZERG_HIVE);

			if (_player->useResource(buildCost.costMinerals, buildCost.costGas))
			{
				//성공
				zbMutating* nextBuilding = new zbMutating(_playerNum, BUILDINGNUM_ZERG_HIVE, this);
				nextBuilding->setLinkAdressZergUpgrade(_zergUpgrade);
				nextBuilding->setLinkAdressAstar(_aStar);
				nextBuilding->setLinkAdressPlayer(_player);
				nextBuilding->init(_battleStatus.ptTile);

				//HP 업데이트

				_player->addBuilding(nextBuilding);

				_nextObject = nextBuilding;
				_valid = false;
			}
			else
			{
				//실패
				_battleStatus.curCommand = COMMAND_NONE;
			}

		}
		break;

		case COMMAND_ESC:
		{
			if (_processing.command == COMMAND_EVOLUTION_ZERG_BURROW)
			{
				tagEvolution evolution = _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_BURROW];

				_player->addResource((UINT)(evolution.cost.mineral * CANCLE_RESOURCE), (UINT)(evolution.cost.gas * CANCLE_RESOURCE));
				evolution.isProcessing = false;
				evolution.complete = false;
			}
			else if (_processing.command == COMMAND_EVOLUTION_ZERG_VECTRAL_SACS)
			{
				tagEvolution evolution = _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_VECTRAL_SACS];

				_player->addResource((UINT)(evolution.cost.mineral * CANCLE_RESOURCE), (UINT)(evolution.cost.gas * CANCLE_RESOURCE));
				evolution.isProcessing = false;
				evolution.complete = false;
			}
			else if (_processing.command == COMMAND_EVOLUTION_ZERG_ANTENNAE)
			{
				tagEvolution evolution = _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_ANTENNAE];

				_player->addResource((UINT)(evolution.cost.mineral * CANCLE_RESOURCE), (UINT)(evolution.cost.gas * CANCLE_RESOURCE));
				evolution.isProcessing = false;
				evolution.complete = false;
			}
			else if (_processing.command == COMMAND_EVOLUTION_ZERG_PNEUMATIZED_CARAPACE)
			{
				tagEvolution evolution = _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_PNEUMATIZED_CARAPACE];

				_player->addResource((UINT)(evolution.cost.mineral * CANCLE_RESOURCE), (UINT)(evolution.cost.gas * CANCLE_RESOURCE));
				evolution.isProcessing = false;
				evolution.complete = false;
			}

			ZeroMemory(&_processing, sizeof(tagProcessing));

			_battleStatus.curCommand = COMMAND_NONE;
		}
		break;
	}

}
