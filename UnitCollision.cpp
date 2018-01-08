#include "stdafx.h"
#include "UnitCollision.h"

#include "Unit.h"
#include "Building.h"
#include "nrMineral.h"
#include "nrGas.h"


UnitCollision::UnitCollision()
{
}


UnitCollision::~UnitCollision()
{
}

bool UnitCollision::isCollision(Unit* unitMove, Unit* unitHold)
{
	//A*를 새로 계산중일땐 예외처리한다.
	//if (unitMove->getBattleStatus().useAstar && unitMove->getBattleStatus().calcAstar)
	//	return false;

	RECT rcInter;
	RECT rcMove = unitMove->getBattleStatus().rcBody;
	RECT rcHold = unitHold->getBattleStatus().rcBody;

	if (!IntersectRect(&rcInter, &rcMove, &rcHold)) return false;

	int interW = rcInter.right - rcInter.left;
	int interH = rcInter.bottom - rcInter.top;

#if 1
	//세로로 부딪혔을 때
	if (interW > interH)
	{
		//rcMove가 rcHold 보다 위에 있을 때
		if (rcInter.top == rcHold.top)
		{
			unitMove->collisionMoveOffset(0, -interH);
		}
		//rcMove가 rcHold 보다 아래에 있을 때
		else if (rcInter.bottom == rcHold.bottom)
		{
			unitMove->collisionMoveOffset(0, interH);
		}
	}
	//가로로 부딪혔을 때
	else
	{
		//rcMove가 rcHold 보다 왼쪽에 있을 때
		if (rcInter.left == rcHold.left)
		{
			unitMove->collisionMoveOffset(-interW, 0);
		}
		//rcMove가 rcHold 보다 오른쪽에 있을 때
		else if (rcInter.right == rcHold.right)
		{
			unitMove->collisionMoveOffset(interW, 0);
		}
	}
#else
	if (rcInter.top == rcHold.top)


#endif


	unitMove->setIsCollision(true);

	return true;
}

bool UnitCollision::isCollision(Unit* unit, Building* building)
{
	//if (unit->getBattleStatus().useAstar && unit->getBattleStatus().calcAstar)
	//	return false;

	RECT rcInter;
	RECT rcMove = unit->getBattleStatus().rcBody;
	RECT rcHold = building->getBattleStatus().rcBody;

	if (!IntersectRect(&rcInter, &rcMove, &rcHold)) return false;

	int interW = rcInter.right - rcInter.left;
	int interH = rcInter.bottom - rcInter.top;

	//세로로 부딪혔을 때
	if (interW > interH)
	{
		//rcMove가 rcHold 보다 위에 있을 때
		if (rcInter.top == rcHold.top)
		{
			unit->collisionMoveOffset(0, -interH);
		}
		//rcMove가 rcHold 보다 아래에 있을 때
		else if (rcInter.bottom == rcHold.bottom)
		{
			unit->collisionMoveOffset(0, interH);
		}
	}
	//가로로 부딪혔을 때
	else
	{
		//rcMove가 rcHold 보다 왼쪽에 있을 때
		if (rcInter.left == rcHold.left)
		{
			unit->collisionMoveOffset(-interW, 0);
		}
		//rcMove가 rcHold 보다 오른쪽에 있을 때
		else if (rcInter.right == rcHold.right)
		{
			unit->collisionMoveOffset(interW, 0);
		}
	}

	unit->setIsCollision(true);

	return true;
}
bool UnitCollision::isCollision(Unit* unit, nrMineral* mineral)
{
	//if (unit->getBattleStatus().useAstar && unit->getBattleStatus().calcAstar)
	//	return false;

	RECT rcInter;
	RECT rcMove = unit->getBattleStatus().rcBody;
	RECT rcHold = mineral->getRectBody();

	if (!IntersectRect(&rcInter, &rcMove, &rcHold)) return false;

	int interW = rcInter.right - rcInter.left;
	int interH = rcInter.bottom - rcInter.top;

	//세로로 부딪혔을 때
	if (interW > interH)
	{
		//rcMove가 rcHold 보다 위에 있을 때
		if (rcInter.top == rcHold.top)
		{
			unit->collisionMoveOffset(0, -interH);
		}
		//rcMove가 rcHold 보다 아래에 있을 때
		else if (rcInter.bottom == rcHold.bottom)
		{
			unit->collisionMoveOffset(0, interH);
		}
	}
	//가로로 부딪혔을 때
	else
	{
		//rcMove가 rcHold 보다 왼쪽에 있을 때
		if (rcInter.left == rcHold.left)
		{
			unit->collisionMoveOffset(-interW, 0);
		}
		//rcMove가 rcHold 보다 오른쪽에 있을 때
		else if (rcInter.right == rcHold.right)
		{
			unit->collisionMoveOffset(interW, 0);
		}
	}

	unit->setIsCollision(true);

	return true;
}
bool UnitCollision::isCollision(Unit* unit, nrGas* gas)
{
	RECT rcInter;
	RECT rcMove = unit->getBattleStatus().rcBody;
	RECT rcHold = gas->getRectBody();

	if (!IntersectRect(&rcInter, &rcMove, &rcHold)) return false;

	int interW = rcInter.right - rcInter.left;
	int interH = rcInter.bottom - rcInter.top;

	//세로로 부딪혔을 때
	if (interW > interH)
	{
		//rcMove가 rcHold 보다 위에 있을 때
		if (rcInter.top == rcHold.top)
		{
			unit->collisionMoveOffset(0, -interH);
		}
		//rcMove가 rcHold 보다 아래에 있을 때
		else if (rcInter.bottom == rcHold.bottom)
		{
			unit->collisionMoveOffset(0, interH);
		}
	}
	//가로로 부딪혔을 때
	else
	{
		//rcMove가 rcHold 보다 왼쪽에 있을 때
		if (rcInter.left == rcHold.left)
		{
			unit->collisionMoveOffset(-interW, 0);
		}
		//rcMove가 rcHold 보다 오른쪽에 있을 때
		else if (rcInter.right == rcHold.right)
		{
			unit->collisionMoveOffset(interW, 0);
		}
	}

	unit->setIsCollision(true);

	return true;
}
