#include "stdafx.h"
#include "Unit.h"

POINT Unit::_zuBodySize[UNITNUM_ZERG_MAX];

Unit::Unit(bool initUnitInfo)
{
	//유닛 몸체 사이즈
	ZeroMemory(&_zuBodySize, sizeof(POINT) * UNITNUM_ZERG_MAX);

	_zuBodySize[UNITNUM_ZERG_LARVA];
	_zuBodySize[UNITNUM_ZERG_ZERGEGG];
	_zuBodySize[UNITNUM_ZERG_DRONE]			= { 46, 46 };
	_zuBodySize[UNITNUM_ZERG_ZERGLING]		= { 32, 32 };
	_zuBodySize[UNITNUM_ZERG_HYDRALISK]		= { 42, 46 };
	_zuBodySize[UNITNUM_ZERG_LURKER]		= { 64, 64 };
	_zuBodySize[UNITNUM_ZERG_LURKEREGG];
	_zuBodySize[UNITNUM_ZERG_ULTRALISK]		= { 76, 64 };
	_zuBodySize[UNITNUM_ZERG_BROODLING]		= { 38, 38 };
	_zuBodySize[UNITNUM_ZERG_DEFILER]		= { 54, 50 };
	_zuBodySize[UNITNUM_ZERG_INFESTEDTERRAN] = { 34, 40 };
	_zuBodySize[UNITNUM_ZERG_OVERLORD]		= { 100, 100 };
	_zuBodySize[UNITNUM_ZERG_MUTALISK]		= { 88, 88 };
	_zuBodySize[UNITNUM_ZERG_SCOURGE]		= { 48, 48 };
	_zuBodySize[UNITNUM_ZERG_QUEEN]			= { 96, 96 };
	_zuBodySize[UNITNUM_ZERG_COCOON];
	_zuBodySize[UNITNUM_ZERG_GUADIAN]		= { 88, 88 };
	_zuBodySize[UNITNUM_ZERG_DEVOURER]		= { 88, 88 };

}

Unit::Unit()
{
	_unitNumZ = UNITNUM_ZERG_NONE;
	_unitNumT = UNITNUM_TERRAN_NONE;
	_unitNumP = UNITNUM_PROTOSS_NONE;

	//BaseStatus
	ZeroMemory(&_baseStatus, sizeof(tagBaseStatus));

	//BattleStatus
	ZeroMemory(&_battleStatus, sizeof(tagBattleStatus));
}


Unit::~Unit()
{
}

HRESULT Unit::init(void)
{


	return S_OK;
}

void Unit::release(void)
{
}

void Unit::update(void)
{
}

void Unit::render(void)
{
	if (PtInRect(&MAINCAMERA->getRectCamera(), _battleStatus.pt.toPoint()))
	{
		_baseStatus.imgBody->frameRenderCT(getMemDC(), _battleStatus.pt.x, _battleStatus.pt.y, _battleStatus.bodyFrame.x, _battleStatus.bodyFrame.y);
	}
}

void Unit::updateBattleStatus(void)
{
	//지상유닛
	if (_baseStatus.isAir == FALSE)
	{
		//지상공격
		if (_baseStatus.GWable)
		{
			if (_baseStatus.GWAttackType == ATTACKTYPE_ZERG_MELEE)
			{
				_battleStatus.curGWdamage = _baseStatus.GWdamage + _baseStatus.GWdamagePlus * _zergUpgrade->getUpgrade()[UPGRADE_ZERG_MELEEATTACKS].level;
			}
			else if (_baseStatus.GWAttackType == ATTACKTYPE_ZERG_MISSILE)
			{
				_battleStatus.curGWdamage = _baseStatus.GWdamage + _baseStatus.GWdamagePlus * _zergUpgrade->getUpgrade()[UPGRADE_ZERG_MISSILEATTACKS].level;
			}
		}
		//공중공격
		if (_baseStatus.AWable)
		{
			if (_baseStatus.AWAttackType == ATTACKTYPE_ZERG_MELEE)
			{
				_battleStatus.curAWdamage = _baseStatus.AWdamage + _baseStatus.AWdamagePlus * _zergUpgrade->getUpgrade()[UPGRADE_ZERG_MELEEATTACKS].level;
			}
			else if (_baseStatus.AWAttackType == ATTACKTYPE_ZERG_MISSILE)
			{
				_battleStatus.curAWdamage = _baseStatus.AWdamage + _baseStatus.AWdamagePlus * _zergUpgrade->getUpgrade()[UPGRADE_ZERG_MISSILEATTACKS].level;
			}
		}

		//현재 방어력
		_battleStatus.curArmor = _baseStatus.armor + _baseStatus.armorPlus * _zergUpgrade->getUpgrade()[UPGRADE_ZERG_CARAPACE].level;
	}
	//공중유닛
	else
	{
		//지상공격
		if (_baseStatus.GWable)
		{
			if (_baseStatus.GWAttackType == ATTACKTYPE_ZERG_FLYING)
			{
				_battleStatus.curGWdamage = _baseStatus.GWdamage + _baseStatus.GWdamagePlus * _zergUpgrade->getUpgrade()[UPGRADE_ZERG_FLYERATTACKS].level;
			}
		}
		//공중공격
		if (_baseStatus.AWable)
		{
			if (_baseStatus.AWAttackType == ATTACKTYPE_ZERG_FLYING)
			{
				_battleStatus.curAWdamage = _baseStatus.AWdamage + _baseStatus.AWdamagePlus * _zergUpgrade->getUpgrade()[UPGRADE_ZERG_FLYERATTACKS].level;
			}
		}

		//현재 방어력
		_battleStatus.curArmor = _baseStatus.armor + _baseStatus.armorPlus * _zergUpgrade->getUpgrade()[UPGRADE_ZERG_FLYERCARAPACE].level;
	}

}
