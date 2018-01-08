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

	//�ڿ�����
	_isNrMineral = false;
	_isNrGas = false;


	//BaseStatus
	ZeroMemory(&_baseStatus, sizeof(tagBaseStatus));

	//BattleStatus
	ZeroMemory(&_battleStatus, sizeof(tagBattleStatus));

	//���� �������� �۾�
	ZeroMemory(&_processing, sizeof(tagProcessing));


	_zergUpgrade = NULL;

	_aStar = NULL;
	_vCloseList.clear();	//A* ���� ���Ǽ� ���� Ÿ�ϵ�

	_amountMineral = 0;
	_amountGas = 0;
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
	_battleStatus.oldCommand = _battleStatus.curCommand;
	_battleStatus.curCommand = cmd;
	_battleStatus.useAstar = false;
	_battleStatus.calcAstar = false;
	//_battleStatus.ptTarget = { -1, -1 };
	//_battleStatus.targetObject = NULL;

	_vCloseList.clear();
}
void gameObject::receiveCommand(COMMAND cmd, POINT pt)
{
	_battleStatus.oldCommand = _battleStatus.curCommand;
	_battleStatus.curCommand = cmd;
	_battleStatus.useAstar = true;
	_battleStatus.calcAstar = false;
	_battleStatus.ptTarget = pt;
	_battleStatus.targetObject = NULL;

	_vCloseList.clear();
}
void gameObject::receiveCommand(COMMAND cmd, POINT pt, POINT ptTile)
{
	_battleStatus.oldCommand = _battleStatus.curCommand;
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
	_battleStatus.oldCommand = _battleStatus.curCommand;
	_battleStatus.curCommand = cmd;
	_battleStatus.useAstar = true;
	_battleStatus.calcAstar = false;
	_battleStatus.ptTarget = object->getBattleStatus().pt.toPoint();
	_battleStatus.targetObject = object;

	_vCloseList.clear();
}

UINT gameObject::gatherMineral(void)
{
	if (_amountMineral > 8)
	{
		_amountMineral -= 8;
		return 8;
	}
	else
	{
		UINT remain = _amountMineral;
		_amountMineral = 0;

		return remain;
	}
}
UINT gameObject::gatherGas(void)
{
	if (_amountGas > 8)
	{
		_amountGas -= 8;
		return 8;
	}
	else if(_amountGas > 0)
	{
		UINT remain = _amountGas;
		_amountGas = 0;

		return remain;
	}
	else
	{
		return 2;
	}
}


void gameObject::hitDamage(gameObject* object)
{
	float damage = 0.0f;
	DAMAGETYPE dmgType = DAMAGETYPE_NORMAL;

	if (_baseStatus.isAir)
	{
		//���� ���������� ��
		damage = object->getBattleStatus().curAWdamage;
		dmgType = object->getBaseStatus().AWdamageType;
	}
	else
	{
		//���� ���������� ��
		damage = object->getBattleStatus().curGWdamage;
		dmgType = object->getBaseStatus().GWdamageType;
	}



	//������ ����, �� ���� ����� ���� �������� �������ش�. 
	switch (dmgType)
	{
	case DAMAGETYPE_NORMAL:
		damage = damage;
		break;
	case DAMAGETYPE_CONCUSSIVE:
	{
		switch (_baseStatus.unitSize)
		{
		case UNITSIZE_SMALL:
			damage = damage;
			break;
		case UNITSIZE_MEDIUM:
			damage = damage * 0.5f;
			break;
		case UNITSIZE_LARGE:
			damage = damage * 0.25f;
			break;
		}
	}
	break;
	case DAMAGETYPE_EXPLOSIVE:
	{
		switch (_baseStatus.unitSize)
		{
		case UNITSIZE_SMALL:
			damage = damage * 0.5f;
			break;
		case UNITSIZE_MEDIUM:
			damage = damage * 0.75f;
			break;
		case UNITSIZE_LARGE:
			damage = damage;
			break;
		}
	}
	break;
	}

	//HP ���
	_battleStatus.curHP -= damage;
	if (_battleStatus.curHP < 1.0f)
	{
		_battleStatus.isDead = true;
	}
}
