#include "stdafx.h"
#include "Unit.h"
#include "Building.h"

#if 0
POINT Unit::_zuBodySize[UNITNUM_ZERG_MAX];

Unit::Unit(bool initUnitInfo)
	: _zergUpgrade(NULL), _aStar(NULL)
{
	//유닛 몸체 사이즈
	ZeroMemory(&_zuBodySize, sizeof(POINT) * UNITNUM_ZERG_MAX);

}
#endif

Unit::Unit()
{
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
	procCommands();
	updatePosition();
	checkCloseList();
	updateImageFrame();
}

void Unit::render(void)
{
	if (_battleStatus.clicked)
	{
		RECT temp = _battleStatus.rcEllipse;
		temp.left   -= MAINCAMERA->getCameraX();
		temp.right  -= MAINCAMERA->getCameraX();
		temp.top    -= MAINCAMERA->getCameraY();
		temp.bottom -= MAINCAMERA->getCameraY();

		RENDERMANAGER->insertEllipse(ZORDER_GAMEOBJECT, temp, PENVERSION_UNITCLICK);
	}
	RENDERMANAGER->insertImgFrameCC(ZORDER_GAMEOBJECT, _baseStatus.imgBody, _battleStatus.pt.x - MAINCAMERA->getCameraX(), _battleStatus.pt.y - MAINCAMERA->getCameraY(), _battleStatus.bodyFrame.x, _battleStatus.bodyFrame.y);

	//debug
	RENDERMANAGER->insertLineRectangle(ZORDER_INTERFACE2, _battleStatus.rcBody, PENVERSION_BLUE1);
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

void Unit::updatePosition(void)
{
}
void Unit::updateImageFrame(void)
{
	setImageFrameForAngle();
}
