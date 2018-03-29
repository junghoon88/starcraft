#include "stdafx.h"
#include "Unit.h"
#include "Building.h"

#include "player.h"
#include "gameMap.h"

Unit::Unit()
{
	_colnum = 0;
	_colsequence = 0;
}


Unit::~Unit()
{
}

HRESULT Unit::init(POINT pt)
{


	return S_OK;
}

void Unit::release(void)
{
}

void Unit::update(void)
{
	checkDead();

	procCommands();
	updatePosition();
	stopUnitRegisterMap();

	collision();

	checkCloseList();

	updateImageFrame();
	updateCommandSet();
}

void Unit::render(void)
{
	//클릭했을 때 녹색 원
	if (_battleStatus.clicked)
	{
		RECT temp = _battleStatus.rcEllipse;
		temp.left   -= MAINCAMERA->getCameraX();
		temp.right  -= MAINCAMERA->getCameraX();
		temp.top    -= MAINCAMERA->getCameraY();
		temp.bottom -= MAINCAMERA->getCameraY();

		if (_baseStatus.isAir)
		{
			RENDERMANAGER->insertEllipse(ZORDER_GAMEOBJECTAIR, temp, PENVERSION_UNITCLICK);
		}
		else
		{
			RENDERMANAGER->insertEllipse(ZORDER_GAMEOBJECT, temp, PENVERSION_UNITCLICK);
		}
	}

	//몸체
	if (_baseStatus.isAir)
	{
		RENDERMANAGER->insertImgFrameCC(ZORDER_GAMEOBJECTAIR, _baseStatus.imgBody, _battleStatus.pt.x - MAINCAMERA->getCameraX(), _battleStatus.pt.y - MAINCAMERA->getCameraY(), _battleStatus.bodyFrame.x, _battleStatus.bodyFrame.y);
	}
	else
	{
		RENDERMANAGER->insertImgFrameCC(ZORDER_GAMEOBJECT, _baseStatus.imgBody, _battleStatus.pt.x - MAINCAMERA->getCameraX(), _battleStatus.pt.y - MAINCAMERA->getCameraY(), _battleStatus.bodyFrame.x, _battleStatus.bodyFrame.y);
	}

	//debug
#if 0
	{
		RECT temp = _battleStatus.rcBody;
		temp.left -= MAINCAMERA->getCameraX();
		temp.right -= MAINCAMERA->getCameraX();
		temp.top -= MAINCAMERA->getCameraY();
		temp.bottom -= MAINCAMERA->getCameraY();
		RENDERMANAGER->insertLineRectangle(ZORDER_GAMEDEBUG1, temp, PENVERSION_BLUE1);
	}
#endif
}

void Unit::updateBattleStatus(void)
{
	//지상유닛
	if (_baseStatus.isAir == FALSE)
	{
		//지상공격
		if (_baseStatus.GWable)
		{
			if (_baseStatus.GWAttackType == ATTACKTYPE_ZERG_FIXED)
			{
				_battleStatus.curGWdamage = _baseStatus.GWdamage;
			}
			else if (_baseStatus.GWAttackType == ATTACKTYPE_ZERG_MELEE)
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
			if (_baseStatus.AWAttackType == ATTACKTYPE_ZERG_FIXED)
			{
				_battleStatus.curAWdamage = _baseStatus.AWdamage;
			}
			else if (_baseStatus.AWAttackType == ATTACKTYPE_ZERG_MELEE)
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
			if (_baseStatus.GWAttackType == ATTACKTYPE_ZERG_FIXED)
			{
				_battleStatus.curGWdamage = _baseStatus.GWdamage;
			}
			else if (_baseStatus.GWAttackType == ATTACKTYPE_ZERG_FLYING)
			{
				_battleStatus.curGWdamage = _baseStatus.GWdamage + _baseStatus.GWdamagePlus * _zergUpgrade->getUpgrade()[UPGRADE_ZERG_FLYERATTACKS].level;
			}
		}
		//공중공격
		if (_baseStatus.AWable)
		{
			if (_baseStatus.AWAttackType == ATTACKTYPE_ZERG_FIXED)
			{
				_battleStatus.curAWdamage = _baseStatus.AWdamage;
			}
			else if (_baseStatus.AWAttackType == ATTACKTYPE_ZERG_FLYING)
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

void Unit::updateCommandSet(void)
{

}

void Unit::checkDead(void)
{
	if (_battleStatus.isDead)
	{
		_nextObject = NULL;
		_valid = false;
	}
}


bool Unit::isInTargetPoint(void)
{
	if (fabs(_battleStatus.pt.x - _battleStatus.ptTarget.x) <= 0.1f
		&& fabs(_battleStatus.pt.y - _battleStatus.ptTarget.y) <= 0.1f)
	{
		return true;
	}
	return false;
}


void Unit::collisionMoveOffset(int x, int y)
{
	float total = sqrt(x*x + y*y);


	if (total > _battleStatus.moveSpeed)
	{
		total = _battleStatus.moveSpeed;
	}
	x = _battleStatus.moveSpeed * (float)x / total;
	y = _battleStatus.moveSpeed * (float)y / total;


	_battleStatus.pt.move(x, y);
	OffsetRect(&_battleStatus.rcBody, x, y);
	OffsetRect(&_battleStatus.rcEllipse, x, y);

	POINT pt = _battleStatus.pt.toPoint();
	_battleStatus.ptTile = { pt.x / TILESIZE, pt.y / TILESIZE };			//현재위치한 타일
}

void Unit::stopUnitRegisterMap(void)
{
	if (_baseStatus.isAir == TRUE)
		return;

	float dist = getDistance(_battleStatus.pt.x, _battleStatus.pt.y, _battleStatus.ptold.x, _battleStatus.ptold.y);

	//정지했는지?
	if (dist < 0.1f)
	{
		if (_battleStatus.isMoving)
		{
			_battleStatus.ptTileOccupy = _battleStatus.ptTile;

			if (_battleStatus.ptTileOccupy.x >= 0 && _battleStatus.ptTileOccupy.x < TILEX
				&& _battleStatus.ptTileOccupy.y >= 0 && _battleStatus.ptTileOccupy.y < TILEY)
			{
				_player->getGamemap()->getTiles()[_battleStatus.ptTileOccupy.x][_battleStatus.ptTileOccupy.y].attribute |= ATTR_UNITSTOP;
			}

			_battleStatus.isMoving = false;

			if (_battleStatus.unitState != UNITSTATE_ATTACK)
			{
				_battleStatus.unitState = UNITSTATE_STOP;
			}
		}
	}
	else
	{
		if (!_battleStatus.isMoving)
		{
			_player->getGamemap()->getTiles()[_battleStatus.ptTileOccupy.x][_battleStatus.ptTileOccupy.y].attribute &= ~ATTR_UNITSTOP;
			_battleStatus.isMoving = true;

			if (_battleStatus.unitState != UNITSTATE_ATTACK)
			{
				_battleStatus.unitState = UNITSTATE_MOVE;
			}
		}
	}


	_battleStatus.ptold = _battleStatus.pt;
}


void Unit::collision(void)
{
	if (_unitNumZ == UNITNUM_ZERG_LARVA || _unitNumZ == UNITNUM_ZERG_ZERGEGG || _unitNumZ == UNITNUM_ZERG_LURKEREGG)
		return;

	if (_baseStatus.isAir)
		return;

	if (_battleStatus.isBurrow)
		return;

	if (_unitNumZ == UNITNUM_ZERG_DRONE)
	{
		if(_battleStatus.curCommand == COMMAND_GATHER 
			|| _battleStatus.curCommand == COMMAND_RETURNCARGO)
		return;
	}



	//A*를 새로 계산중일땐 예외처리한다.
	if (_battleStatus.useAstar && _battleStatus.calcAstar)
		return;


	UINT unitmax = _player->getUnits().size();
	UINT buildmax = _player->getBuildings().size();
	UINT mineralmax = _player->getGamemap()->getVMineral().size();
	UINT gasmax = _player->getGamemap()->getVGas().size();

	//UINT colmax = unitmax + buildmax + mineralmax + gasmax;
	UINT colstart = _colnum;
	UINT colmax = 10; //최대 10개까지 충돌처리

	if (_colsequence == 0)
	{
		//최대개수까지 증가
		_colnum += colmax;

		if (_colnum > unitmax)
		{
			collisionUnit(colstart, unitmax);

			//다음 시퀀스로 초기화
			_colnum = 0;
			_colsequence = 1;
		}
		else
		{
			collisionUnit(colstart, _colnum);
		}
	}
	else if (_colsequence == 1)
	{
		//최대개수까지 증가
		_colnum += colmax;

		if (_colnum > buildmax)
		{
			collisionBuilding(colstart, buildmax);

			//다음 시퀀스로 초기화
			_colnum = 0;
			_colsequence = 2;
		}
		else
		{
			collisionBuilding(colstart, _colnum);
		}
	}
	else if (_colsequence == 2)
	{
		//최대개수까지 증가
		_colnum += colmax;

		if (_colnum > mineralmax)
		{
			collisionMineral(colstart, mineralmax);

			//다음 시퀀스로 초기화
			_colnum = 0;
			_colsequence = 3;
		}
		else
		{
			collisionMineral(colstart, _colnum);
		}
	}
	else if (_colsequence == 3)
	{
		//최대개수까지 증가
		_colnum += colmax;

		if (_colnum > gasmax)
		{
			collisionGas(colstart, gasmax);

			//다음 시퀀스로 초기화
			_colnum = 0;
			_colsequence = 0;
		}
		else
		{
			collisionGas(colstart, _colnum);
		}
	}





}

void Unit::collisionUnit(UINT st, UINT ed)
{
	for (int i = st; i < ed; i++)
	{
		if (this == _player->getUnits()[i]) continue;

		Unit* unitHold = _player->getUnits()[i];

		if (unitHold->getUnitnumZerg() == UNITNUM_ZERG_LARVA)
			continue;
		if (unitHold->getBaseStatus().isAir)
			continue;
		if (unitHold->getBattleStatus().isBurrow)
			continue;

		if (unitHold->getUnitnumZerg() == UNITNUM_ZERG_DRONE)
		{
			if (unitHold->getBattleStatus().curCommand == COMMAND_GATHER
				|| unitHold->getBattleStatus().curCommand == COMMAND_RETURNCARGO)
				continue;
		}

		_player->getUnitCollision()->isCollision(this, unitHold);
	}
}
void Unit::collisionBuilding(UINT st, UINT ed)
{
	for (int i = st; i < ed; i++)
	{
		_player->getUnitCollision()->isCollision(this, _player->getBuildings()[i]);
	}
}
void Unit::collisionMineral(UINT st, UINT ed)
{
	for (int i = st; i < ed; i++)
	{
		_player->getUnitCollision()->isCollision(this, _player->getGamemap()->getVMineral()[i]);
	}
}
void Unit::collisionGas(UINT st, UINT ed)
{
	if (_unitNumZ == UNITNUM_ZERG_DRONE && _battleStatus.curCommand == COMMAND_BUILD_EXTRACTOR)
		return;

	for (int i = st; i < ed; i++)
	{
		_player->getUnitCollision()->isCollision(this, _player->getGamemap()->getVGas()[i]);
	}
}
