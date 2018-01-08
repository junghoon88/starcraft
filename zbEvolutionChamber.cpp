#include "stdafx.h"
#include "zbEvolutionChamber.h"

#include "zergDefine.h"
#include "player.h"


zbEvolutionChamber::zbEvolutionChamber(PLAYER playerNum)
{
	_valid = true;

	//플레이어 정보
	_playerNum = playerNum;

	//종족
	_race = RACES_ZERG;

	//유닛인지 건물인지
	_isBuilding = true;

	//유닛 고유 번호
	_buildingNumZ = BUILDINGNUM_ZERG_EVOLUTIONCHAMBER;

}


zbEvolutionChamber::~zbEvolutionChamber()
{
}

HRESULT zbEvolutionChamber::init(POINT ptTile)
{
	initBaseStatus();
	initBattleStatus(ptTile);

	return S_OK;
}

void zbEvolutionChamber::initBaseStatus(void)
{
	//Properties
	_stprintf(_baseStatus.name, L"Zerg Evolution Chamber");

	TCHAR strKey[100];
	_stprintf(strKey, L"ZB-evolutionchamber-Body%d", _playerNum);
	_baseStatus.imgBody = IMAGEMANAGER->findImage(strKey);
	_baseStatus.imgFace = IMAGEMANAGER->findImage(L"ZB-Face");
	_baseStatus.imgStat1 = IMAGEMANAGER->findImage(L"ZB-evolutionchamber-Stat1");
	_baseStatus.imgStat2 = NULL;

	_baseStatus.maxHP = 750.0f;

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
void zbEvolutionChamber::initBattleStatus(POINT ptTile)
{
	//BattleStatus
	_battleStatus.curCommand = COMMAND_NONE;
	_battleStatus.clicked = false;
	_battleStatus.curHP = _baseStatus.maxHP;			//현재 HP
	_battleStatus.maxHP = _baseStatus.maxHP;			//최대 HP

	POINT buildTileSize = BUILDSIZE_EVOLUTIONCHAMBER;

	_battleStatus.ptTile = ptTile;
	_battleStatus.rcBody = RectMake(ptTile.x * TILESIZE, ptTile.y * TILESIZE, buildTileSize.x * TILESIZE, buildTileSize.y * TILESIZE);
	_battleStatus.pt.set((_battleStatus.rcBody.left + _battleStatus.rcBody.right) * 0.5f, (_battleStatus.rcBody.top + _battleStatus.rcBody.bottom) * 0.5f);
	_battleStatus.rcTile = RectMake(ptTile.x, ptTile.y, buildTileSize.x, buildTileSize.y);
	_battleStatus.rcEllipse = _battleStatus.rcBody;
}

void zbEvolutionChamber::release(void)
{

}

void zbEvolutionChamber::update(void)
{
	Building::update();

}

void zbEvolutionChamber::render(int imgOffsetX, int imgOffsetY)
{
	POINT imgOffset = BUILDIMAGEOFFSET_EVOLUTIONCHAMBER;
	Building::render(imgOffset.x * TILESIZE, imgOffset.y * TILESIZE);

}


void zbEvolutionChamber::updateBattleStatus(void)
{

}
void zbEvolutionChamber::updatePosition(void)
{

}

void zbEvolutionChamber::updateImageFrame(void)
{

}

void zbEvolutionChamber::updateProcessing(void)
{
	Building::updateProcessing();

}

void zbEvolutionChamber::updateCommandSet(void)
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
		tagUpgrade upgMelee    = _player->getZergUpgrade()->getUpgrade()[UPGRADE_ZERG_MELEEATTACKS];
		tagUpgrade upgMissile  = _player->getZergUpgrade()->getUpgrade()[UPGRADE_ZERG_MISSILEATTACKS];
		tagUpgrade upgCarapace = _player->getZergUpgrade()->getUpgrade()[UPGRADE_ZERG_CARAPACE];

		if (upgMelee.complete || upgMelee.isProcessing)
		{
			_baseStatus.commands[0] = COMMAND_NONE;
		}
		else
		{
			_baseStatus.commands[0] = COMMAND_UPGRADE_ZERG_MELEEATTACKS;
		}

		if (upgMissile.complete || upgMissile.isProcessing)
		{
			_baseStatus.commands[1] = COMMAND_NONE;
		}
		else
		{
			_baseStatus.commands[1] = COMMAND_UPGRADE_ZERG_MISSILEATTACKS;
		}

		if (upgCarapace.complete || upgCarapace.isProcessing)
		{
			_baseStatus.commands[2] = COMMAND_NONE;
		}
		else
		{
			_baseStatus.commands[2] = COMMAND_UPGRADE_ZERG_CARAPACE;
		}

		_baseStatus.commands[8] = COMMAND_NONE;
	}
}


void zbEvolutionChamber::procCommands(void)
{
	switch (_battleStatus.curCommand)
	{
		case COMMAND_UPGRADE_ZERG_MELEEATTACKS:
		{
			tagUpgrade upgMelee = _player->getZergUpgrade()->getUpgrade()[UPGRADE_ZERG_MELEEATTACKS];

			if (_player->useResource(upgMelee.vCost[upgMelee.level].mineral, upgMelee.vCost[upgMelee.level].gas))
			{
				//성공
				_processing.type = PROCESSING_EVOLVING;
				_processing.command = _battleStatus.curCommand;
				_processing.img = IMAGEMANAGER->findImage(L"command-upgrade_zerg_meleeattacks");
				_processing.curTime = 0.0f;
				_processing.maxTime = upgMelee.vCost[upgMelee.level].duration;
				_processing.complete = false;

				upgMelee.isProcessing = true;
			}

			_battleStatus.curCommand = COMMAND_NONE;
		}
		break;

		case COMMAND_UPGRADE_ZERG_MISSILEATTACKS:
		{
			tagUpgrade upgMissile = _player->getZergUpgrade()->getUpgrade()[UPGRADE_ZERG_MISSILEATTACKS];

			if (_player->useResource(upgMissile.vCost[upgMissile.level].mineral, upgMissile.vCost[upgMissile.level].gas))
			{
				//성공
				_processing.type = PROCESSING_EVOLVING;
				_processing.command = _battleStatus.curCommand;
				_processing.img = IMAGEMANAGER->findImage(L"command-upgrade_zerg_missileattacks");
				_processing.curTime = 0.0f;
				_processing.maxTime = upgMissile.vCost[upgMissile.level].duration;
				_processing.complete = false;

				upgMissile.isProcessing = true;
			}

			_battleStatus.curCommand = COMMAND_NONE;
		}
		break;

		case COMMAND_UPGRADE_ZERG_CARAPACE:
		{
			tagUpgrade upgCarapace = _player->getZergUpgrade()->getUpgrade()[UPGRADE_ZERG_CARAPACE];

			if (_player->useResource(upgCarapace.vCost[upgCarapace.level].mineral, upgCarapace.vCost[upgCarapace.level].gas))
			{
				//성공
				_processing.type = PROCESSING_EVOLVING;
				_processing.command = _battleStatus.curCommand;
				_processing.img = IMAGEMANAGER->findImage(L"command-upgrade_zerg_carapace");
				_processing.curTime = 0.0f;
				_processing.maxTime = upgCarapace.vCost[upgCarapace.level].duration;
				_processing.complete = false;

				upgCarapace.isProcessing = true;
			}

			_battleStatus.curCommand = COMMAND_NONE;
		}
		break;

		case COMMAND_ESC:
		{
			if (_processing.command == COMMAND_UPGRADE_ZERG_MELEEATTACKS)
			{
				tagUpgrade upgMelee = _player->getZergUpgrade()->getUpgrade()[UPGRADE_ZERG_MELEEATTACKS];

				_player->addResource((UINT)(upgMelee.vCost[upgMelee.level].mineral * CANCLE_RESOURCE), (UINT)(upgMelee.vCost[upgMelee.level].gas * CANCLE_RESOURCE));
				upgMelee.isProcessing = false;
				upgMelee.complete = false;
			}
			else if (_processing.command == COMMAND_UPGRADE_ZERG_MISSILEATTACKS)
			{
				tagUpgrade upgMissile = _player->getZergUpgrade()->getUpgrade()[UPGRADE_ZERG_MISSILEATTACKS];

				_player->addResource((UINT)(upgMissile.vCost[upgMissile.level].mineral * CANCLE_RESOURCE), (UINT)(upgMissile.vCost[upgMissile.level].gas * CANCLE_RESOURCE));
				upgMissile.isProcessing = false;
				upgMissile.complete = false;
			}
			else if (_processing.command == COMMAND_UPGRADE_ZERG_CARAPACE)
			{
				tagUpgrade upgCarapace = _player->getZergUpgrade()->getUpgrade()[UPGRADE_ZERG_CARAPACE];

				_player->addResource((UINT)(upgCarapace.vCost[upgCarapace.level].mineral * CANCLE_RESOURCE), (UINT)(upgCarapace.vCost[upgCarapace.level].gas * CANCLE_RESOURCE));
				upgCarapace.isProcessing = false;
				upgCarapace.complete = false;
			}


			ZeroMemory(&_processing, sizeof(tagProcessing));

			_battleStatus.curCommand = COMMAND_NONE;
		}
		break;

	}
}
