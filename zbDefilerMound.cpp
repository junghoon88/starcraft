#include "stdafx.h"
#include "zbDefilerMound.h"

#include "zergDefine.h"
#include "player.h"

zbDefilerMound::zbDefilerMound(PLAYER playerNum)
{
	_valid = true;

	//플레이어 정보
	_playerNum = playerNum;

	//종족
	_race = RACES_ZERG;

	//유닛인지 건물인지
	_isBuilding = true;

	//유닛 고유 번호
	_buildingNumZ = BUILDINGNUM_ZERG_DEFILERMOUND;

}


zbDefilerMound::~zbDefilerMound()
{
}

HRESULT zbDefilerMound::init(POINT ptTile)
{
	initBaseStatus();
	initBattleStatus(ptTile);

	return S_OK;
}

void zbDefilerMound::initBaseStatus(void)
{
	//Properties
	_stprintf(_baseStatus.name, L"Zerg Defiler Mound");

	TCHAR strKey[100];
	_stprintf(strKey, L"ZB-defilermound-Body%d", _playerNum);
	_baseStatus.imgBody = IMAGEMANAGER->findImage(strKey);
	_baseStatus.imgFace = IMAGEMANAGER->findImage(L"ZB-Face");
	_baseStatus.imgStat1 = IMAGEMANAGER->findImage(L"ZB-defilermound-Stat1");
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

	_baseStatus.commands[0] = COMMAND_EVOLUTION_ZERG_PLAGUE;
	_baseStatus.commands[1] = COMMAND_EVOLUTION_ZERG_CONSUME;
	_baseStatus.commands[2] = COMMAND_EVOLUTION_ZERG_METASYNAPTIC_NODE;
	_baseStatus.commands[3] = COMMAND_NONE;
	_baseStatus.commands[4] = COMMAND_NONE;
	_baseStatus.commands[5] = COMMAND_NONE;
	_baseStatus.commands[6] = COMMAND_NONE;
	_baseStatus.commands[7] = COMMAND_NONE;
	_baseStatus.commands[8] = COMMAND_NONE;

}
void zbDefilerMound::initBattleStatus(POINT ptTile)
{
	//BattleStatus
	_battleStatus.curCommand = COMMAND_NONE;
	_battleStatus.clicked = false;
	_battleStatus.curHP = _baseStatus.maxHP;			//현재 HP
	_battleStatus.maxHP = _baseStatus.maxHP;			//최대 HP

	POINT buildTileSize = BUILDSIZE_DEFILERMOUND;

	_battleStatus.ptTile = ptTile;
	_battleStatus.rcBody = RectMake(ptTile.x * TILESIZE, ptTile.y * TILESIZE, buildTileSize.x * TILESIZE, buildTileSize.y * TILESIZE);
	_battleStatus.pt.set((_battleStatus.rcBody.left + _battleStatus.rcBody.right) * 0.5f, (_battleStatus.rcBody.top + _battleStatus.rcBody.bottom) * 0.5f);
	_battleStatus.rcTile = RectMake(ptTile.x, ptTile.y, buildTileSize.x, buildTileSize.y);
	_battleStatus.rcEllipse = _battleStatus.rcBody;
}

void zbDefilerMound::release(void)
{

}

void zbDefilerMound::update(void)
{
	Building::update();

}

void zbDefilerMound::render(int imgOffsetX, int imgOffsetY)
{
	POINT imgOffset = BUILDIMAGEOFFSET_DEFILERMOUND;
	Building::render(imgOffset.x * TILESIZE, imgOffset.y * TILESIZE);

}

void zbDefilerMound::updateBattleStatus(void)
{

}
void zbDefilerMound::updatePosition(void)
{

}

void zbDefilerMound::updateImageFrame(void)
{

}

void zbDefilerMound::updateProcessing(void)
{
	Building::updateProcessing();

}

void zbDefilerMound::updateCommandSet(void)
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
		tagEvolution evoPlague		= _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_PLAGUE];
		tagEvolution evoConsume		= _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_CONSUME];
		tagEvolution evoMetasy		= _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_METASYNAPTIC_NODE];

		if (evoPlague.complete || evoPlague.isProcessing)
		{
			_baseStatus.commands[0] = COMMAND_NONE;
		}
		else
		{
			_baseStatus.commands[0] = COMMAND_EVOLUTION_ZERG_PLAGUE;
		}

		if (evoConsume.complete || evoConsume.isProcessing)
		{
			_baseStatus.commands[1] = COMMAND_NONE;
		}
		else
		{
			_baseStatus.commands[1] = COMMAND_EVOLUTION_ZERG_CONSUME;
		}

		if (evoMetasy.complete || evoMetasy.isProcessing)
		{
			_baseStatus.commands[2] = COMMAND_NONE;
		}
		else
		{
			_baseStatus.commands[2] = COMMAND_EVOLUTION_ZERG_METASYNAPTIC_NODE;
		}

		_baseStatus.commands[8] = COMMAND_NONE;
	}
}


void zbDefilerMound::procCommands(void)
{
	switch (_battleStatus.curCommand)
	{
		case COMMAND_EVOLUTION_ZERG_PLAGUE:
		{
			tagEvolution evolution = _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_PLAGUE];

			if (_player->useResource(evolution.cost.mineral, evolution.cost.gas))
			{
				//성공
				_processing.type = PROCESSING_EVOLVING;
				_processing.command = _battleStatus.curCommand;
				_processing.img = IMAGEMANAGER->findImage(L"command-evolution_zerg_evolve_plague");
				_processing.curTime = 0.0f;
				_processing.maxTime = evolution.cost.duration;
				_processing.complete = false;

				evolution.isProcessing = true;
			}

			_battleStatus.curCommand = COMMAND_NONE;
		}
		break;

		case COMMAND_EVOLUTION_ZERG_CONSUME:
		{
			tagEvolution evolution = _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_CONSUME];

			if (_player->useResource(evolution.cost.mineral, evolution.cost.gas))
			{
				//성공
				_processing.type = PROCESSING_EVOLVING;
				_processing.command = _battleStatus.curCommand;
				_processing.img = IMAGEMANAGER->findImage(L"command-evolution_zerg_evolve_consume");
				_processing.curTime = 0.0f;
				_processing.maxTime = evolution.cost.duration;
				_processing.complete = false;

				evolution.isProcessing = true;
			}

			_battleStatus.curCommand = COMMAND_NONE;
		}
		break;

		case COMMAND_EVOLUTION_ZERG_METASYNAPTIC_NODE:
		{
			tagEvolution evolution = _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_METASYNAPTIC_NODE];

			if (_player->useResource(evolution.cost.mineral, evolution.cost.gas))
			{
				//성공
				_processing.type = PROCESSING_EVOLVING;
				_processing.command = _battleStatus.curCommand;
				_processing.img = IMAGEMANAGER->findImage(L"command-evolution_zerg_metasynaptic_node");
				_processing.curTime = 0.0f;
				_processing.maxTime = evolution.cost.duration;
				_processing.complete = false;

				evolution.isProcessing = true;
			}

			_battleStatus.curCommand = COMMAND_NONE;
		}
		break;

		case COMMAND_ESC:
		{
			if (_processing.command == COMMAND_EVOLUTION_ZERG_PLAGUE)
			{
				tagEvolution evoPlague = _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_PLAGUE];

				_player->addResource((UINT)(evoPlague.cost.mineral * CANCLE_RESOURCE), (UINT)(evoPlague.cost.gas * CANCLE_RESOURCE));
				evoPlague.isProcessing = false;
				evoPlague.complete = false;
			}
			else if (_processing.command == COMMAND_EVOLUTION_ZERG_CONSUME)
			{
				tagEvolution evoConsume = _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_CONSUME];

				_player->addResource((UINT)(evoConsume.cost.mineral * CANCLE_RESOURCE), (UINT)(evoConsume.cost.gas * CANCLE_RESOURCE));
				evoConsume.isProcessing = false;
				evoConsume.complete = false;
			}
			else if (_processing.command == COMMAND_EVOLUTION_ZERG_METASYNAPTIC_NODE)
			{
				tagEvolution evoMetasy = _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_METASYNAPTIC_NODE];

				_player->addResource((UINT)(evoMetasy.cost.mineral * CANCLE_RESOURCE), (UINT)(evoMetasy.cost.gas * CANCLE_RESOURCE));
				evoMetasy.isProcessing = false;
				evoMetasy.complete = false;
			}
		
			ZeroMemory(&_processing, sizeof(tagProcessing));

			_battleStatus.curCommand = COMMAND_NONE;
		}
		break;

	}
}

