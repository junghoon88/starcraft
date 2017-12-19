#include "stdafx.h"
#include "Unit.h"
#include "Building.h"

POINT Unit::_zuBodySize[UNITNUM_ZERG_MAX];

Unit::Unit(bool initUnitInfo)
	: _zergUpgrade(NULL), _aStar(NULL)
{
	//유닛 몸체 사이즈
	ZeroMemory(&_zuBodySize, sizeof(POINT) * UNITNUM_ZERG_MAX);

	_zuBodySize[UNITNUM_ZERG_LARVA];
	_zuBodySize[UNITNUM_ZERG_ZERGEGG];
	_zuBodySize[UNITNUM_ZERG_DRONE]			= { 36, 32 };
	_zuBodySize[UNITNUM_ZERG_ZERGLING]		= { 16, 16 };
	_zuBodySize[UNITNUM_ZERG_HYDRALISK]		= { 21, 23 };
	_zuBodySize[UNITNUM_ZERG_LURKER]		= { 32, 32 };
	_zuBodySize[UNITNUM_ZERG_LURKEREGG];
	_zuBodySize[UNITNUM_ZERG_ULTRALISK]		= { 38, 32 };
	_zuBodySize[UNITNUM_ZERG_BROODLING]		= { 19, 19 };
	_zuBodySize[UNITNUM_ZERG_DEFILER]		= { 27, 25 };
	_zuBodySize[UNITNUM_ZERG_INFESTEDTERRAN] = { 17, 20 };
	_zuBodySize[UNITNUM_ZERG_OVERLORD]		= { 50, 50 };
	_zuBodySize[UNITNUM_ZERG_MUTALISK]		= { 44, 44 };
	_zuBodySize[UNITNUM_ZERG_SCOURGE]		= { 24, 24 };
	_zuBodySize[UNITNUM_ZERG_QUEEN]			= { 48, 48 };
	_zuBodySize[UNITNUM_ZERG_COCOON];
	_zuBodySize[UNITNUM_ZERG_GUADIAN]		= { 44, 44 };
	_zuBodySize[UNITNUM_ZERG_DEVOURER]		= { 44, 44 };

}

Unit::Unit()
	: _zergUpgrade(NULL), _aStar(NULL)
{
	_unitNumZ = UNITNUM_ZERG_NONE;
	_unitNumT = UNITNUM_TERRAN_NONE;
	_unitNumP = UNITNUM_PROTOSS_NONE;

	//BaseStatus
	ZeroMemory(&_baseStatus, sizeof(tagUnitBaseStatus));

	//BattleStatus
	ZeroMemory(&_battleStatus, sizeof(tagUnitBattleStatus));
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
	//if (PtInRect(&MAINCAMERA->getRectCamera(), _battleStatus.pt.toPoint()))
	//{
	//}
	if (_battleStatus.clicked)
	{
		int width  = _battleStatus.rcEllipse.right - _battleStatus.rcEllipse.left;
		int height = _battleStatus.rcEllipse.bottom - _battleStatus.rcEllipse.top;



#if 0

		HPEN oldPen = (HPEN)SelectObject(getMemDC(), _gPen[PENVERSION_UNITCLICK]);
		Ellipse(getMemDC(), _battleStatus.rcEllipse.left - MAINCAMERA->getCameraX(), _battleStatus.rcEllipse.top - MAINCAMERA->getCameraY(),
							_battleStatus.rcEllipse.right - MAINCAMERA->getCameraX(), _battleStatus.rcEllipse.bottom - MAINCAMERA->getCameraY());
		SelectObject(getMemDC(), oldPen);
		DeleteObject(oldPen);

#else
		image* _backBuffer2 = IMAGEMANAGER->addImage(L"backBuffer2", WINSIZEX, WINSIZEY);
		HDC hDCtemp = _backBuffer2->getMemDC();
		PatBlt(hDCtemp, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

		HPEN oldPen = (HPEN)SelectObject(hDCtemp, _gPen[PENVERSION_UNITCLICK]);
		Ellipse(hDCtemp, 0, 0, width, height);
		SelectObject(hDCtemp, oldPen);

		GdiTransparentBlt(getMemDC(),		//복사될 DC영역
						_battleStatus.rcEllipse.left - MAINCAMERA->getCameraX(),	//복사될 DC영역에 뿌려줄 좌표
						_battleStatus.rcEllipse.top - MAINCAMERA->getCameraY(),
						width, height,												//복사될 가로 세로 크기

						hDCtemp,			//복사할 DC
						0, 0,				//복사할 좌표
						width, height,		//복사할 가로 세로 크기
						RGB(255, 255, 255));			//제외할 칼라
#endif

	}
	_baseStatus.imgBody->frameRenderCT(getMemDC(), _battleStatus.pt.x - MAINCAMERA->getCameraX(), _battleStatus.pt.y - MAINCAMERA->getCameraY(), _battleStatus.bodyFrame.x, _battleStatus.bodyFrame.y);
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

void Unit::receiveCommand(COMMAND cmd)
{
	_battleStatus.curCommand = cmd;
	_battleStatus.useAstar = false;
	_battleStatus.calcAstar = false;
	//_battleStatus.ptTarget = { -1, -1 };
	//_battleStatus.unitTarget = NULL;
	//_battleStatus.BuildingTarget = NULL;

	_vCloseList.clear();
}
void Unit::receiveCommand(COMMAND cmd, POINT pt)
{
	_battleStatus.curCommand = cmd;
	_battleStatus.useAstar = true;
	_battleStatus.calcAstar = false;
	_battleStatus.ptTarget = pt;
	_battleStatus.unitTarget = NULL;
	_battleStatus.BuildingTarget = NULL;

	_vCloseList.clear();
	//_aStar->clearTiles();
}
void Unit::receiveCommand(COMMAND cmd, Unit* unit)
{
	_battleStatus.curCommand = cmd;
	_battleStatus.useAstar = true;
	_battleStatus.calcAstar = false;
	_battleStatus.ptTarget = { 0, 0 };
	_battleStatus.unitTarget = unit;
	_battleStatus.BuildingTarget = NULL;

	_vCloseList.clear();
	//_aStar->clearTiles();
}
void Unit::receiveCommand(COMMAND cmd, Building* building)
{
	_battleStatus.curCommand = cmd;
	_battleStatus.useAstar = true;
	_battleStatus.calcAstar = false;
	_battleStatus.ptTarget = { 0, 0 };
	_battleStatus.unitTarget = NULL;
	_battleStatus.BuildingTarget = building;

	_vCloseList.clear();
	//_aStar->clearTiles();
}
