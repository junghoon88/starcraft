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
	//A*�� ���� ������϶� ����ó���Ѵ�.
	//if (unitMove->getBattleStatus().useAstar && unitMove->getBattleStatus().calcAstar)
	//	return false;

	RECT rcInter;
	RECT rcMove = unitMove->getBattleStatus().rcBody;
	RECT rcHold = unitHold->getBattleStatus().rcBody;

	if (!IntersectRect(&rcInter, &rcMove, &rcHold)) return false;

	int interW = rcInter.right - rcInter.left;
	int interH = rcInter.bottom - rcInter.top;

#if 1
	//���η� �ε����� ��
	if (interW > interH)
	{
		//rcMove�� rcHold ���� ���� ���� ��
		if (rcInter.top == rcHold.top)
		{
			unitMove->collisionMoveOffset(0, -interH);
		}
		//rcMove�� rcHold ���� �Ʒ��� ���� ��
		else if (rcInter.bottom == rcHold.bottom)
		{
			unitMove->collisionMoveOffset(0, interH);
		}
	}
	//���η� �ε����� ��
	else
	{
		//rcMove�� rcHold ���� ���ʿ� ���� ��
		if (rcInter.left == rcHold.left)
		{
			unitMove->collisionMoveOffset(-interW, 0);
		}
		//rcMove�� rcHold ���� �����ʿ� ���� ��
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

	//���η� �ε����� ��
	if (interW > interH)
	{
		//rcMove�� rcHold ���� ���� ���� ��
		if (rcInter.top == rcHold.top)
		{
			unit->collisionMoveOffset(0, -interH);
		}
		//rcMove�� rcHold ���� �Ʒ��� ���� ��
		else if (rcInter.bottom == rcHold.bottom)
		{
			unit->collisionMoveOffset(0, interH);
		}
	}
	//���η� �ε����� ��
	else
	{
		//rcMove�� rcHold ���� ���ʿ� ���� ��
		if (rcInter.left == rcHold.left)
		{
			unit->collisionMoveOffset(-interW, 0);
		}
		//rcMove�� rcHold ���� �����ʿ� ���� ��
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

	//���η� �ε����� ��
	if (interW > interH)
	{
		//rcMove�� rcHold ���� ���� ���� ��
		if (rcInter.top == rcHold.top)
		{
			unit->collisionMoveOffset(0, -interH);
		}
		//rcMove�� rcHold ���� �Ʒ��� ���� ��
		else if (rcInter.bottom == rcHold.bottom)
		{
			unit->collisionMoveOffset(0, interH);
		}
	}
	//���η� �ε����� ��
	else
	{
		//rcMove�� rcHold ���� ���ʿ� ���� ��
		if (rcInter.left == rcHold.left)
		{
			unit->collisionMoveOffset(-interW, 0);
		}
		//rcMove�� rcHold ���� �����ʿ� ���� ��
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

	//���η� �ε����� ��
	if (interW > interH)
	{
		//rcMove�� rcHold ���� ���� ���� ��
		if (rcInter.top == rcHold.top)
		{
			unit->collisionMoveOffset(0, -interH);
		}
		//rcMove�� rcHold ���� �Ʒ��� ���� ��
		else if (rcInter.bottom == rcHold.bottom)
		{
			unit->collisionMoveOffset(0, interH);
		}
	}
	//���η� �ε����� ��
	else
	{
		//rcMove�� rcHold ���� ���ʿ� ���� ��
		if (rcInter.left == rcHold.left)
		{
			unit->collisionMoveOffset(-interW, 0);
		}
		//rcMove�� rcHold ���� �����ʿ� ���� ��
		else if (rcInter.right == rcHold.right)
		{
			unit->collisionMoveOffset(interW, 0);
		}
	}

	unit->setIsCollision(true);

	return true;
}
