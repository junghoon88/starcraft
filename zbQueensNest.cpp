#include "stdafx.h"
#include "zbQueensNest.h"

#include "zergDefine.h"
#include "player.h"

zbQueensNest::zbQueensNest(PLAYER playerNum)
{
	_valid = true;

	//플레이어 정보
	_playerNum = playerNum;

	//종족
	_race = RACES_ZERG;

	//유닛인지 건물인지
	_isBuilding = true;

	//유닛 고유 번호
	_buildingNumZ = BUILDINGNUM_ZERG_QUEENSNEST;

}


zbQueensNest::~zbQueensNest()
{
}

HRESULT zbQueensNest::init(POINT ptTile)
{
	initBaseStatus();
	initBattleStatus(ptTile);

	return S_OK;
}

void zbQueensNest::initBaseStatus(void)
{
	//Properties
	_stprintf(_baseStatus.name, L"Zerg Queen's Nest");

	TCHAR strKey[100];
	_stprintf(strKey, L"ZB-queensnest-Body%d", _playerNum);
	_baseStatus.imgBody = IMAGEMANAGER->findImage(strKey);
	_baseStatus.imgFace = IMAGEMANAGER->findImage(L"ZB-Face");
	_baseStatus.imgStat1 = IMAGEMANAGER->findImage(L"ZB-queensnest-Stat1");
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
void zbQueensNest::initBattleStatus(POINT ptTile)
{
	//BattleStatus
	_battleStatus.curCommand = COMMAND_NONE;
	_battleStatus.clicked = false;
	_battleStatus.curHP = _baseStatus.maxHP;			//현재 HP
	_battleStatus.maxHP = _baseStatus.maxHP;			//최대 HP

	POINT buildTileSize = BUILDSIZE_QUEENSNEST;

	_battleStatus.ptTile = ptTile;
	_battleStatus.rcBody = RectMake(ptTile.x * TILESIZE, ptTile.y * TILESIZE, buildTileSize.x * TILESIZE, buildTileSize.y * TILESIZE);
	_battleStatus.pt.set((_battleStatus.rcBody.left + _battleStatus.rcBody.right) * 0.5f, (_battleStatus.rcBody.top + _battleStatus.rcBody.bottom) * 0.5f);
	_battleStatus.rcTile = RectMake(ptTile.x, ptTile.y, buildTileSize.x, buildTileSize.y);
	_battleStatus.rcEllipse = _battleStatus.rcBody;
}

void zbQueensNest::release(void)
{

}

void zbQueensNest::update(void)
{
	Building::update();

}

void zbQueensNest::render(int imgOffsetX, int imgOffsetY)
{
	POINT imgOffset = BUILDIMAGEOFFSET_QUEENSNEST;
	Building::render(imgOffset.x * TILESIZE, imgOffset.y * TILESIZE);

}


void zbQueensNest::updateBattleStatus(void)
{

}
void zbQueensNest::updatePosition(void)
{

}

void zbQueensNest::updateImageFrame(void)
{

}

void zbQueensNest::updateProcessing(void)
{
	Building::updateProcessing();

}

void zbQueensNest::updateCommandSet(void)
{
	if (_processing.type == PROCESSING_EVOLVING)
	{
		_baseStatus.commands[0] = COMMAND_NONE;
		_baseStatus.commands[1] = COMMAND_NONE;
		_baseStatus.commands[2] = COMMAND_NONE;
		_baseStatus.commands[8] = COMMAND_ESC;
	}
	else
	{
		tagEvolution evobroodling = _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_SPAWN_BROODLING];
		tagEvolution evoEnsnare   = _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_ENSNARE];
		tagEvolution evoMeiosis   = _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_GAMETE_MEIOSIS];

		if (evobroodling.complete || evobroodling.isProcessing)
		{
			_baseStatus.commands[0] = COMMAND_NONE;
		}
		else
		{
			_baseStatus.commands[0] = COMMAND_EVOLUTION_ZERG_SPAWN_BROODLING;
		}

		if (evoEnsnare.complete || evoEnsnare.isProcessing)
		{
			_baseStatus.commands[1] = COMMAND_NONE;
		}
		else
		{
			_baseStatus.commands[1] = COMMAND_EVOLUTION_ZERG_ENSNARE;
		}

		if (evoMeiosis.complete || evoMeiosis.isProcessing)
		{
			_baseStatus.commands[2] = COMMAND_NONE;
		}
		else
		{
			_baseStatus.commands[2] = COMMAND_EVOLUTION_ZERG_GAMETE_MEIOSIS;
		}

		_baseStatus.commands[8] = COMMAND_NONE;
	}
}


void zbQueensNest::procCommands(void)
{
	switch (_battleStatus.curCommand)
	{
		case COMMAND_EVOLUTION_ZERG_SPAWN_BROODLING:
		{
			tagEvolution evolution = _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_SPAWN_BROODLING];

			if (_player->useResource(evolution.cost.mineral, evolution.cost.gas))
			{
				//성공
				_processing.type = PROCESSING_EVOLVING;
				_processing.command = _battleStatus.curCommand;
				_processing.img = IMAGEMANAGER->findImage(L"command-evolution_zerg_evolve_spawn_broodling");
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

		case COMMAND_EVOLUTION_ZERG_ENSNARE:
		{
			tagEvolution evolution = _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_ENSNARE];

			if (_player->useResource(evolution.cost.mineral, evolution.cost.gas))
			{
				//성공
				_processing.type = PROCESSING_EVOLVING;
				_processing.command = _battleStatus.curCommand;
				_processing.img = IMAGEMANAGER->findImage(L"command-evolution_zerg_evolve_ensnare");
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

		case COMMAND_EVOLUTION_ZERG_GAMETE_MEIOSIS:
		{
			tagEvolution evolution = _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_GAMETE_MEIOSIS];

			if (_player->useResource(evolution.cost.mineral, evolution.cost.gas))
			{
				//성공
				_processing.type = PROCESSING_EVOLVING;
				_processing.command = _battleStatus.curCommand;
				_processing.img = IMAGEMANAGER->findImage(L"command-evolution_zerg_gamete_meiosis");
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
			if (_processing.command == COMMAND_EVOLUTION_ZERG_SPAWN_BROODLING)
			{
				tagEvolution evolution = _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_SPAWN_BROODLING];

				_player->addResource((UINT)(evolution.cost.mineral * CANCLE_RESOURCE), (UINT)(evolution.cost.gas * CANCLE_RESOURCE));
				evolution.isProcessing = false;
				evolution.complete = false;
			}
			else if (_processing.command == COMMAND_EVOLUTION_ZERG_ENSNARE)
			{
				tagEvolution evolution = _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_ENSNARE];

				_player->addResource((UINT)(evolution.cost.mineral * CANCLE_RESOURCE), (UINT)(evolution.cost.gas * CANCLE_RESOURCE));
				evolution.isProcessing = false;
				evolution.complete = false;
			}
			else if (_processing.command == COMMAND_EVOLUTION_ZERG_GAMETE_MEIOSIS)
			{
				tagEvolution evolution = _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_GAMETE_MEIOSIS];

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