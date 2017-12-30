#include "stdafx.h"
#include "zbUltraliskCavern.h"

#include "zergDefine.h"
#include "player.h"


zbUltraliskCavern::zbUltraliskCavern(PLAYER playerNum)
{
	_valid = true;

	//�÷��̾� ����
	_playerNum = playerNum;

	//����
	_race = RACES_ZERG;

	//�������� �ǹ�����
	_isBuilding = true;

	//���� ���� ��ȣ
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
	_stprintf(_baseStatus.name, L"Zerg UltraliskCavern");

	TCHAR strKey[100];
	_stprintf(strKey, L"ZB-ultraliskCavernBody%d", _playerNum);
	_baseStatus.imgBody = IMAGEMANAGER->findImage(strKey);
	_baseStatus.imgFace = NULL;
	_baseStatus.imgStat1 = IMAGEMANAGER->findImage(L"ZB-ultraliskCavernStat1");
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

	_baseStatus.commands[0] = COMMAND_EVOLUTION_ZERG_ANABOLIC_SYNTHESIS;
	_baseStatus.commands[1] = COMMAND_EVOLUTION_ZERG_CHITINOUS_PLATING;
	_baseStatus.commands[2] = COMMAND_NONE;
	_baseStatus.commands[3] = COMMAND_NONE;
	_baseStatus.commands[4] = COMMAND_NONE;
	_baseStatus.commands[5] = COMMAND_NONE;
	_baseStatus.commands[6] = COMMAND_NONE;
	_baseStatus.commands[7] = COMMAND_NONE;
	_baseStatus.commands[8] = COMMAND_NONE;

}
void zbUltraliskCavern::initBattleStatus(POINT ptTile)
{
	//BattleStatus
	_battleStatus.curCommand = COMMAND_NONE;
	_battleStatus.clicked = false;
	_battleStatus.curHP = _baseStatus.maxHP;			//���� HP
	_battleStatus.maxHP = _baseStatus.maxHP;			//�ִ� HP

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
	Building::render();

}

