#include "stdafx.h"
#include "zbHydraliskDen.h"

#include "zergDefine.h"
#include "player.h"


zbHydraliskDen::zbHydraliskDen(PLAYER playerNum)
{
	_valid = true;

	//플레이어 정보
	_playerNum = playerNum;

	//종족
	_race = RACES_ZERG;

	//유닛인지 건물인지
	_isBuilding = true;

	//유닛 고유 번호
	_buildingNumZ = BUILDINGNUM_ZERG_HYDRALISKDEN;

}


zbHydraliskDen::~zbHydraliskDen()
{
}

HRESULT zbHydraliskDen::init(POINT ptTile)
{
	initBaseStatus();
	initBattleStatus(ptTile);

	return S_OK;
}

void zbHydraliskDen::initBaseStatus(void)
{
	//Properties
	_stprintf(_baseStatus.name, L"Zerg Hydralisk Den");

	TCHAR strKey[100];
	_stprintf(strKey, L"ZB-hydraliskden-Body%d", _playerNum);
	_baseStatus.imgBody = IMAGEMANAGER->findImage(strKey);
	_baseStatus.imgFace = IMAGEMANAGER->findImage(L"ZB-Face");
	_baseStatus.imgStat1 = IMAGEMANAGER->findImage(L"ZB-hydraliskden-Stat1");
	_baseStatus.imgStat2 = NULL;

	_baseStatus.maxHP = 850.0f;

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
void zbHydraliskDen::initBattleStatus(POINT ptTile)
{
	//BattleStatus
	_battleStatus.curCommand = COMMAND_NONE;
	_battleStatus.clicked = false;
	_battleStatus.curHP = _baseStatus.maxHP;			//현재 HP
	_battleStatus.maxHP = _baseStatus.maxHP;			//최대 HP

	POINT buildTileSize = BUILDSIZE_HYDRALISKDEN;

	_battleStatus.ptTile = ptTile;
	_battleStatus.rcBody = RectMake(ptTile.x * TILESIZE, ptTile.y * TILESIZE, buildTileSize.x * TILESIZE, buildTileSize.y * TILESIZE);
	_battleStatus.pt.set((_battleStatus.rcBody.left + _battleStatus.rcBody.right) * 0.5f, (_battleStatus.rcBody.top + _battleStatus.rcBody.bottom) * 0.5f);
	_battleStatus.rcTile = RectMake(ptTile.x, ptTile.y, buildTileSize.x, buildTileSize.y);
	_battleStatus.rcEllipse = _battleStatus.rcBody;
}

void zbHydraliskDen::release(void)
{

}

void zbHydraliskDen::update(void)
{
	Building::update();

}

void zbHydraliskDen::render(int imgOffsetX, int imgOffsetY)
{
	POINT imgOffset = BUILDIMAGEOFFSET_HYDRALISKDEN;
	Building::render(imgOffset.x * TILESIZE, imgOffset.y * TILESIZE);

}

void zbHydraliskDen::updateBattleStatus(void)
{

}
void zbHydraliskDen::updatePosition(void)
{

}

void zbHydraliskDen::updateImageFrame(void)
{

}

void zbHydraliskDen::updateProcessing(void)
{
	Building::updateProcessing();

}

void zbHydraliskDen::updateCommandSet(void)
{
	if (_processing.type == PROCESSING_EVOLVING)
	{
		_baseStatus.commands[0] = COMMAND_NONE;
		_baseStatus.commands[1] = COMMAND_NONE;
		_baseStatus.commands[3] = COMMAND_NONE;
		_baseStatus.commands[8] = COMMAND_ESC;
	}
	else
	{
		tagEvolution evoMuscular = _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_MUSCULAR_AUGMENTS];
		tagEvolution evoGrooved  = _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_GROOVED_SPINES];
		tagEvolution evoLurker   = _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_LURKER_ASPECT];

		if (evoMuscular.complete || evoMuscular.isProcessing)
		{
			_baseStatus.commands[0] = COMMAND_NONE;
		}
		else
		{
			_baseStatus.commands[0] = COMMAND_EVOLUTION_ZERG_MUSCULAR_AUGMENTS;
		}

		if (evoGrooved.complete || evoGrooved.isProcessing)
		{
			_baseStatus.commands[1] = COMMAND_NONE;
		}
		else
		{
			_baseStatus.commands[1] = COMMAND_EVOLUTION_ZERG_GROOVED_SPINES;
		}

		if (evoLurker.complete || evoLurker.isProcessing)
		{
			_baseStatus.commands[3] = COMMAND_NONE;
		}
		else
		{
			_baseStatus.commands[3] = COMMAND_EVOLUTION_ZERG_LURKER_ASPECT;
		}

		_baseStatus.commands[8] = COMMAND_NONE;
	}


}


void zbHydraliskDen::procCommands(void)
{
	switch (_battleStatus.curCommand)
	{
		case COMMAND_EVOLUTION_ZERG_MUSCULAR_AUGMENTS:
		{
			tagEvolution evolution = _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_MUSCULAR_AUGMENTS];

			if (_player->useResource(evolution.cost.mineral, evolution.cost.gas))
			{
				//성공
				_processing.type = PROCESSING_EVOLVING;
				_processing.command = _battleStatus.curCommand;
				_processing.img = IMAGEMANAGER->findImage(L"command-evolution_zerg_muscular_augments");
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

		case COMMAND_EVOLUTION_ZERG_GROOVED_SPINES:
		{
			tagEvolution evolution = _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_GROOVED_SPINES];

			if (_player->useResource(evolution.cost.mineral, evolution.cost.gas))
			{
				//성공
				_processing.type = PROCESSING_EVOLVING;
				_processing.command = _battleStatus.curCommand;
				_processing.img = IMAGEMANAGER->findImage(L"command-evolution_zerg_grooved_spines");
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

		case COMMAND_EVOLUTION_ZERG_LURKER_ASPECT:
		{
			tagEvolution evolution = _player->getZergUpgrade()->getEvolution()[COMMAND_EVOLUTION_ZERG_LURKER_ASPECT];

			if (_player->useResource(evolution.cost.mineral, evolution.cost.gas))
			{
				//성공
				_processing.type = PROCESSING_EVOLVING;
				_processing.command = _battleStatus.curCommand;
				_processing.img = IMAGEMANAGER->findImage(L"command-evolution_zerg_evolve_lurker_aspect");
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


		case COMMAND_ESC:
		{
			if (_processing.command == COMMAND_EVOLUTION_ZERG_MUSCULAR_AUGMENTS)
			{
				tagEvolution evolution = _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_MUSCULAR_AUGMENTS];

				_player->addResource((UINT)(evolution.cost.mineral * CANCLE_RESOURCE), (UINT)(evolution.cost.gas * CANCLE_RESOURCE));
				evolution.isProcessing = false;
				evolution.complete = false;
			}
			else if (_processing.command == COMMAND_EVOLUTION_ZERG_GROOVED_SPINES)
			{
				tagEvolution evolution = _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_GROOVED_SPINES];

				_player->addResource((UINT)(evolution.cost.mineral * CANCLE_RESOURCE), (UINT)(evolution.cost.gas * CANCLE_RESOURCE));
				evolution.isProcessing = false;
				evolution.complete = false;
			}
			else if (_processing.command == COMMAND_EVOLUTION_ZERG_LURKER_ASPECT)
			{
				tagEvolution evolution = _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_LURKER_ASPECT];

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
