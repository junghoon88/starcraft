#include "stdafx.h"
#include "gameObject.h"


gameObject::gameObject()
{
	//��ȿ�� ������Ʈ����
	_valid = false;

	_nextObject = NULL;

	//�÷��̾� ����
	_playerNum = PLAYER_NONE;

	//����
	_race = RACES_ZERG;

	//�������� �ǹ�����
	_isBuilding = false;

	//���� ���� ��ȣ
	_unitNumZ = UNITNUM_ZERG_NONE;
	_unitNumT = UNITNUM_TERRAN_NONE;
	_unitNumP = UNITNUM_PROTOSS_NONE;
	//�ǹ� ���� ��ȣ
	_buildingNumZ = BUILDINGNUM_ZERG_NONE;
	_buildingNumT = BUILDINGNUM_TERRAN_NONE;
	_buildingNumP = BUILDINGNUM_PROTOSS_NONE;


	//BaseStatus
	ZeroMemory(&_baseStatus, sizeof(tagBaseStatus));

	//BattleStatus
	ZeroMemory(&_battleStatus, sizeof(tagBattleStatus));

	//���ָ��� ������ �ִ� ���� �Ӽ����� ����
	ZeroMemory(&_unionSpecialStatus, sizeof(unionSpecialStatus));;

	_zergUpgrade = NULL;

	_aStar = NULL;
	_vCloseList.clear();	//A* ���� ���Ǽ� ���� Ÿ�ϵ�
}


gameObject::~gameObject()
{
}

HRESULT gameObject::init(void) { return S_OK; }
void gameObject::release(void) {}
void gameObject::update(void) {}
void gameObject::render(void) {}
void gameObject::getChar(WPARAM wParam) {}
void gameObject::updateBattleStatus(void) {}
void gameObject::updatePosition(void) {}
void gameObject::updateImageFrame(void) {}


void gameObject::receiveCommand(COMMAND cmd)
{
	_battleStatus.curCommand = cmd;
	_battleStatus.useAstar = false;
	_battleStatus.calcAstar = false;
	//_battleStatus.ptTarget = { -1, -1 };
	//_battleStatus.targetObject = NULL;

	_vCloseList.clear();
}
void gameObject::receiveCommand(COMMAND cmd, POINT pt)
{
	_battleStatus.curCommand = cmd;
	_battleStatus.useAstar = true;
	_battleStatus.calcAstar = false;
	_battleStatus.ptTarget = pt;
	_battleStatus.targetObject = NULL;

	_vCloseList.clear();
	//_aStar->clearTiles();
}
void gameObject::receiveCommand(COMMAND cmd, POINT pt, POINT ptTile)
{
	_battleStatus.curCommand = cmd;
	_battleStatus.useAstar = true;
	_battleStatus.calcAstar = false;
	_battleStatus.ptTarget = pt;
	_battleStatus.ptTileTarget = ptTile;
	_battleStatus.targetObject = NULL;

	_vCloseList.clear();
}
void gameObject::receiveCommand(COMMAND cmd, gameObject* object)
{
	_battleStatus.curCommand = cmd;
	_battleStatus.useAstar = true;
	_battleStatus.calcAstar = false;
	_battleStatus.ptTarget = { 0, 0 };
	_battleStatus.targetObject = object;

	_vCloseList.clear();
	//_aStar->clearTiles();
}
