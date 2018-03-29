#include "stdafx.h"
#include "zbUltraliskCavern.h"

#include "zergDefine.h"
#include "player.h"


zbUltraliskCavern::zbUltraliskCavern(PLAYER playerNum)
{
	_valid = true;

	//플레이어 정보
	_playerNum = playerNum;

	//종족
	_race = RACES_ZERG;

	//유닛인지 건물인지
	_isBuilding = true;

	//유닛 고유 번호
	_buildingNumZ = BUILDINGNUM_ZERG_ULTRALISKCAVERN;

}


zbUltraliskCavern::~zbUltraliskCavern()
{

}

HRESULT zbUltraliskCavern::init(POINT ptTile)
{
	initBaseStatus();
	initBattleStatus(ptTile);

	return S_OK;
}

void zbUltraliskCavern::initBaseStatus(void)
{
	//Properties
	_stprintf(_baseStatus.name, L"Zerg Ultralisk Cavern");

	TCHAR strKey[100];
	_stprintf(strKey, L"ZB-ultraliskcavern-Body%d", _playerNum);
	_baseStatus.imgBody = IMAGEMANAGER->findImage(strKey);
	_baseStatus.imgFace = IMAGEMANAGER->findImage(L"ZB-Face");
	_baseStatus.imgStat1 = IMAGEMANAGER->findImage(L"ZB-ultraliskcavern-Stat1");
	_baseStatus.imgStat2 = NULL;

	_baseStatus.maxHP = 600.0f;

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
void zbUltraliskCavern::initBattleStatus(POINT ptTile)
{
	//BattleStatus
	_battleStatus.curCommand = COMMAND_NONE;
	_battleStatus.clicked = false;
	_battleStatus.curHP = _baseStatus.maxHP;			//현재 HP
	_battleStatus.maxHP = _baseStatus.maxHP;			//최대 HP

	POINT buildTileSize = BUILDSIZE_ULTRALISKCAVERN;

	_battleStatus.ptTile = ptTile;
	_battleStatus.rcBody = RectMake(ptTile.x * TILESIZE, ptTile.y * TILESIZE, buildTileSize.x * TILESIZE, buildTileSize.y * TILESIZE);
	_battleStatus.pt.set((_battleStatus.rcBody.left + _battleStatus.rcBody.right) * 0.5f, (_battleStatus.rcBody.top + _battleStatus.rcBody.bottom) * 0.5f);
	_battleStatus.rcTile = RectMake(ptTile.x, ptTile.y, buildTileSize.x, buildTileSize.y);
	_battleStatus.rcEllipse = _battleStatus.rcBody;
}

void zbUltraliskCavern::release(void)
{

}

void zbUltraliskCavern::update(void) 
{
	Building::update();

}

void zbUltraliskCavern::render(int imgOffsetX, int imgOffsetY)
{
	POINT imgOffset = BUILDIMAGEOFFSET_ULTRALISKCAVERN;
	Building::render(imgOffset.x * TILESIZE, imgOffset.y * TILESIZE);

}


void zbUltraliskCavern::updateBattleStatus(void)
{

}
void zbUltraliskCavern::updatePosition(void)
{

}

void zbUltraliskCavern::updateImageFrame(void)
{
	float tick = TIMEMANAGER->getElapsedTime();

	_battleStatus.bodyFrameTime += tick;
	if (_battleStatus.bodyFrameTime >= UNIT_BODY_FPS_TIME)
	{
		_battleStatus.bodyFrameTime -= UNIT_BODY_FPS_TIME;

		_battleStatus.bodyFrame.x++;
		if (_battleStatus.bodyFrame.x > _baseStatus.imgBody->getMaxFrameX())
		{
			_battleStatus.bodyFrame.x = 0;
		}
	}

}

void zbUltraliskCavern::updateProcessing(void)
{
	Building::updateProcessing();

}

void zbUltraliskCavern::updateCommandSet(void)
{
	if (_processing.type == PROCESSING_EVOLVING)
	{
		_baseStatus.commands[0] = COMMAND_NONE;
		_baseStatus.commands[1] = COMMAND_NONE;
		_baseStatus.commands[8] = COMMAND_ESC;
	}
	else
	{
		tagEvolution evoAnabolic  = _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_ANABOLIC_SYNTHESIS];
		tagEvolution evoChitinous = _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_CHITINOUS_PLATING];

		if (evoAnabolic.complete || evoAnabolic.isProcessing)
		{
			_baseStatus.commands[0] = COMMAND_NONE;
		}
		else
		{
			_baseStatus.commands[0] = COMMAND_EVOLUTION_ZERG_ANABOLIC_SYNTHESIS;
		}

		if (evoChitinous.complete || evoChitinous.isProcessing)
		{
			_baseStatus.commands[1] = COMMAND_NONE;
		}
		else
		{
			_baseStatus.commands[1] = COMMAND_EVOLUTION_ZERG_CHITINOUS_PLATING;
		}

		_baseStatus.commands[8] = COMMAND_NONE;
	}
}


void zbUltraliskCavern::procCommands(void)
{
	switch (_battleStatus.curCommand)
	{
		case COMMAND_EVOLUTION_ZERG_ANABOLIC_SYNTHESIS:
		{
			tagEvolution evolution = _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_ANABOLIC_SYNTHESIS];

			if (_player->useResource(evolution.cost.mineral, evolution.cost.gas))
			{
				//성공
				_processing.type = PROCESSING_EVOLVING;
				_processing.command = _battleStatus.curCommand;
				_processing.img = IMAGEMANAGER->findImage(L"command-evolution_zerg_anabolic_synthesis");
				_processing.curTime = 0.0f;
				_processing.maxTime = evolution.cost.duration;
				_processing.complete = false;

				evolution.isProcessing = true;
			}

			_battleStatus.curCommand = COMMAND_NONE;
		}
		break;

		case COMMAND_EVOLUTION_ZERG_CHITINOUS_PLATING:
		{
			tagEvolution evolution = _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_CHITINOUS_PLATING];

			if (_player->useResource(evolution.cost.mineral, evolution.cost.gas))
			{
				//성공
				_processing.type = PROCESSING_EVOLVING;
				_processing.command = _battleStatus.curCommand;
				_processing.img = IMAGEMANAGER->findImage(L"command-evolution_zerg_chitinous_plating");
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
			if (_processing.command == COMMAND_EVOLUTION_ZERG_ANABOLIC_SYNTHESIS)
			{
				tagEvolution evolution = _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_ANABOLIC_SYNTHESIS];

				_player->addResource((UINT)(evolution.cost.mineral * CANCLE_RESOURCE), (UINT)(evolution.cost.gas * CANCLE_RESOURCE));
				evolution.isProcessing = false;
				evolution.complete = false;
			}
			else if (_processing.command == COMMAND_EVOLUTION_ZERG_CHITINOUS_PLATING)
			{
				tagEvolution evolution = _player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_CHITINOUS_PLATING];

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
