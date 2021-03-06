#include "stdafx.h"
#include "gameObject.h"


gameObject::gameObject()
{
	//유효한 오브젝트인지
	_valid = false;

	_nextObject = NULL;

	//플레이어 정보
	_playerNum = PLAYER_NONE;

	//종족
	_race = RACES_ZERG;

	//유닛인지 건물인지
	_isBuilding = false;

	//유닛 고유 번호
	_unitNumZ = UNITNUM_ZERG_NONE;
	_unitNumT = UNITNUM_TERRAN_NONE;
	_unitNumP = UNITNUM_PROTOSS_NONE;
	//건물 고유 번호
	_buildingNumZ = BUILDINGNUM_ZERG_NONE;
	_buildingNumT = BUILDINGNUM_TERRAN_NONE;
	_buildingNumP = BUILDINGNUM_PROTOSS_NONE;

	//자원인지
	_isNrMineral = false;
	_isNrGas = false;


	//BaseStatus
	ZeroMemory(&_baseStatus, sizeof(tagBaseStatus));

	//BattleStatus
	ZeroMemory(&_battleStatus, sizeof(tagBattleStatus));

	//현재 진행중인 작업
	ZeroMemory(&_processing, sizeof(tagProcessing));


	_zergUpgrade = NULL;

	_aStar = NULL;
	_vCloseList.clear();	//A* 에서 계산되서 받은 타일들

	_amountMineral = 0;
	_amountGas = 0;

	_isBurrowing = FALSE;
	_isUnburrowing = FALSE;

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


void gameObject::hitDamage(gameObject* attackker)
{
	float damage = 0.0f;
	DAMAGETYPE dmgType = DAMAGETYPE_NORMAL;

	if (_baseStatus.isAir)
	{
		//내가 공중유닛일 때
		damage = attackker->getBattleStatus().curAWdamage;
		dmgType = attackker->getBaseStatus().AWdamageType;
	}
	else
	{
		//내가 지상유닛일 때
		damage = attackker->getBattleStatus().curGWdamage;
		dmgType = attackker->getBaseStatus().GWdamageType;
	}

	//방어력 계산
	damage = damage - _battleStatus.curArmor;

	//데미지가 0 이하가 되면 0~1 사이 랜덤 실수로 변경
	if (damage <= 0.0f)
	{
		damage = RND->getFloat(1.0f);
	}


	//데미지 유형, 내 유닛 사이즈에 따라 데미지를 변경해준다. 
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

	//HP 계산
	_battleStatus.curHP -= damage;
	if (_battleStatus.curHP < 1.0f)
	{
		_battleStatus.isDead = true;
		attackker->addKill();
	}
}

//bullet 공격일 경우, 공격유닛이 그 사이에 죽을수도 있기 때문에
void gameObject::hitDamage(gameObject* attackker, float dmg, DAMAGETYPE type)
{
	float damage = dmg;
	DAMAGETYPE dmgType = type;

	//방어력 계산
	damage = damage - _battleStatus.curArmor;

	//데미지가 0 이하가 되면 0~1 사이 랜덤 실수로 변경
	if (damage <= 0.0f)
	{
		damage = RND->getFloat(1.0f);
	}


	//데미지 유형, 내 유닛 사이즈에 따라 데미지를 변경해준다. 
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

	//HP 계산
	_battleStatus.curHP -= damage;
	if (_battleStatus.curHP < 1.0f)
	{
		_battleStatus.isDead = true;

		if (attackker != NULL && attackker->getValid() == TRUE)
		{
			attackker->addKill();
		}
	}
}

//외부에서 접근할때 gameObject가 delete 되었는지 확인용
gameObject* gameObject::isValidObject(gameObject* obj)
{
	if (obj->getIsBuilding())
	{
		if (obj->getBuildingNumZerg() <= BUILDINGNUM_ZERG_NONE || obj->getBuildingNumZerg() >= BUILDINGNUM_ZERG_MAX)
		{
			obj = NULL;
		}
	}
	else
	{
		if (obj->getUnitnumZerg() <= UNITNUM_ZERG_NONE || obj->getUnitnumZerg() >= UNITNUM_ZERG_MAX)
		{
			obj = NULL;
		}
	}

	return obj;
}
