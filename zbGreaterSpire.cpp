#include "stdafx.h"
#include "zbGreaterSpire.h"

#include "zergDefine.h"
#include "player.h"

zbGreaterSpire::zbGreaterSpire(PLAYER playerNum)
{
	_valid = true;

	//플레이어 정보
	_playerNum = playerNum;

	//종족
	_race = RACES_ZERG;

	//유닛인지 건물인지
	_isBuilding = true;

	//유닛 고유 번호
	_buildingNumZ = BUILDINGNUM_ZERG_GREATERSPIRE;

}


zbGreaterSpire::~zbGreaterSpire()
{
}

HRESULT zbGreaterSpire::init(POINT ptTile)
{
	initBaseStatus();
	initBattleStatus(ptTile);

	return S_OK;
}

void zbGreaterSpire::initBaseStatus(void)
{
	//Properties
	_stprintf(_baseStatus.name, L"Zerg Greater Spire");

	TCHAR strKey[100];
	_stprintf(strKey, L"ZB-greaterspire-Body%d", _playerNum);
	_baseStatus.imgBody = IMAGEMANAGER->findImage(strKey);
	_baseStatus.imgFace = IMAGEMANAGER->findImage(L"ZB-Face");
	_baseStatus.imgStat1 = IMAGEMANAGER->findImage(L"ZB-greaterspire-Stat1");
	_baseStatus.imgStat2 = NULL;

	_baseStatus.maxHP = 1000.0f;

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
void zbGreaterSpire::initBattleStatus(POINT ptTile)
{
	//BattleStatus
	_battleStatus.curCommand = COMMAND_NONE;
	_battleStatus.clicked = false;
	_battleStatus.curHP = _baseStatus.maxHP;			//현재 HP
	_battleStatus.maxHP = _baseStatus.maxHP;			//최대 HP

	POINT buildTileSize = BUILDSIZE_GREATERSPIRE;

	_battleStatus.ptTile = ptTile;
	_battleStatus.rcBody = RectMake(ptTile.x * TILESIZE, ptTile.y * TILESIZE, buildTileSize.x * TILESIZE, buildTileSize.y * TILESIZE);
	_battleStatus.pt.set((_battleStatus.rcBody.left + _battleStatus.rcBody.right) * 0.5f, (_battleStatus.rcBody.top + _battleStatus.rcBody.bottom) * 0.5f);
	_battleStatus.rcTile = RectMake(ptTile.x, ptTile.y, buildTileSize.x, buildTileSize.y);
	_battleStatus.rcEllipse = _battleStatus.rcBody;
}

void zbGreaterSpire::release(void)
{

}

void zbGreaterSpire::update(void)
{
	Building::update();

}

void zbGreaterSpire::render(int imgOffsetX, int imgOffsetY)
{
	POINT imgOffset = BUILDIMAGEOFFSET_GREATERSPIRE;
	Building::render(imgOffset.x * TILESIZE, imgOffset.y * TILESIZE);

}

void zbGreaterSpire::updateBattleStatus(void)
{

}
void zbGreaterSpire::updatePosition(void)
{

}

void zbGreaterSpire::updateImageFrame(void)
{

}

void zbGreaterSpire::updateProcessing(void)
{
	Building::updateProcessing();

}

void zbGreaterSpire::updateCommandSet(void)
{
	if (_processing.type == PROCESSING_EVOLVING)
	{
		_baseStatus.commands[0] = COMMAND_NONE;
		_baseStatus.commands[1] = COMMAND_NONE;
		_baseStatus.commands[8] = COMMAND_ESC;
	}
	else
	{
		tagUpgrade upgFlyatk = _player->getZergUpgrade()->getUpgrade()[UPGRADE_ZERG_FLYERATTACKS];
		tagUpgrade upgFlydep = _player->getZergUpgrade()->getUpgrade()[UPGRADE_ZERG_FLYERCARAPACE];

		if (upgFlyatk.complete || upgFlyatk.isProcessing)
		{
			_baseStatus.commands[0] = COMMAND_NONE;
		}
		else
		{
			_baseStatus.commands[0] = COMMAND_UPGRADE_ZERG_FLYERATTACKS;
		}

		if (upgFlydep.complete || upgFlydep.isProcessing)
		{
			_baseStatus.commands[1] = COMMAND_NONE;
		}
		else
		{
			_baseStatus.commands[1] = COMMAND_UPGRADE_ZERG_FLYERCARAPACE;
		}

		_baseStatus.commands[8] = COMMAND_NONE;
	}
}


void zbGreaterSpire::procCommands(void)
{
	switch (_battleStatus.curCommand)
	{
		case COMMAND_UPGRADE_ZERG_FLYERATTACKS:
		{
			tagUpgrade upgFlyatk = _player->getZergUpgrade()->getUpgrade()[UPGRADE_ZERG_FLYERATTACKS];

			if (_player->useResource(upgFlyatk.vCost[upgFlyatk.level].mineral, upgFlyatk.vCost[upgFlyatk.level].gas))
			{
				//성공
				_processing.type = PROCESSING_EVOLVING;
				_processing.command = _battleStatus.curCommand;
				_processing.img = IMAGEMANAGER->findImage(L"command-upgrade_zerg_flyerattacks");
				_processing.curTime = 0.0f;
				_processing.maxTime = upgFlyatk.vCost[upgFlyatk.level].duration;
				_processing.complete = false;

				upgFlyatk.isProcessing = true;
			}
			else
			{
				//실패
			}
			_battleStatus.curCommand = COMMAND_NONE;
		}
		break;

		case COMMAND_UPGRADE_ZERG_FLYERCARAPACE:
		{
			tagUpgrade upgFlydep = _player->getZergUpgrade()->getUpgrade()[UPGRADE_ZERG_FLYERATTACKS];

			if (_player->useResource(upgFlydep.vCost[upgFlydep.level].mineral, upgFlydep.vCost[upgFlydep.level].gas))
			{
				//성공
				_processing.type = PROCESSING_EVOLVING;
				_processing.command = _battleStatus.curCommand;
				_processing.img = IMAGEMANAGER->findImage(L"command-upgrade_zerg_flyercarapace");
				_processing.curTime = 0.0f;
				_processing.maxTime = upgFlydep.vCost[upgFlydep.level].duration;
				_processing.complete = false;

				upgFlydep.isProcessing = true;
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
			if (_processing.command == COMMAND_UPGRADE_ZERG_FLYERATTACKS)
			{
				tagUpgrade upgFlyatk = _player->getZergUpgrade()->getUpgrade()[UPGRADE_ZERG_FLYERATTACKS];

				_player->addResource((UINT)(upgFlyatk.vCost[upgFlyatk.level].mineral * CANCLE_RESOURCE), (UINT)(upgFlyatk.vCost[upgFlyatk.level].gas * CANCLE_RESOURCE));
				upgFlyatk.isProcessing = false;
				upgFlyatk.complete = false;
			}
			else if (_processing.command == COMMAND_UPGRADE_ZERG_FLYERCARAPACE)
			{
				tagUpgrade upgFlydep = _player->getZergUpgrade()->getUpgrade()[UPGRADE_ZERG_FLYERCARAPACE];

				_player->addResource((UINT)(upgFlydep.vCost[upgFlydep.level].mineral * CANCLE_RESOURCE), (UINT)(upgFlydep.vCost[upgFlydep.level].gas * CANCLE_RESOURCE));
				upgFlydep.isProcessing = false;
				upgFlydep.complete = false;
			}


			ZeroMemory(&_processing, sizeof(tagProcessing));

			_battleStatus.curCommand = COMMAND_NONE;

		}
		break;

	}
}
