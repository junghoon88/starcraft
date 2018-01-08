#include "stdafx.h"
#include "Unit.h"
#include "Building.h"

#include "tileNode.h"

void Unit::procCommands(void)
{
	switch (_battleStatus.curCommand)
	{
	case COMMAND_NONE:
		_battleStatus.curCommand = _battleStatus.oldCommand;
		break;
	case COMMAND_MOVE:
		if (_baseStatus.isAir)
		{
			moveAir();
		}
		else
		{
			moveGround();
		}
		break;
	case COMMAND_STOP:
		break;
	case COMMAND_ATTACK:
		attackProc();
		break;
	case COMMAND_PATROL:
		break;
	case COMMAND_HOLD:
		break;


	case COMMAND_GATHER:
		if (_unitNumZ != UNITNUM_ZERG_DRONE)
		{
			_battleStatus.oldCommand = _battleStatus.curCommand;
			_battleStatus.curCommand = COMMAND_MOVE;
		}
		break;
	case COMMAND_RETURNCARGO:
		if (_unitNumZ != UNITNUM_ZERG_DRONE)
		{
			_battleStatus.curCommand = _battleStatus.oldCommand;
		}
		break;


	case COMMAND_BURROW:
		if (_baseStatus.commands[8] != COMMAND_BURROW || _battleStatus.isBurrow == TRUE)
		{
			_battleStatus.curCommand = _battleStatus.oldCommand;
		}
		break;
	case COMMAND_UNBURROW:
		if (_baseStatus.commands[8] != COMMAND_UNBURROW || _battleStatus.isBurrow == FALSE)
		{
			_battleStatus.curCommand = _battleStatus.oldCommand;
		}
		break;

	case COMMAND_INFEST:
	case COMMAND_PARASITE:
	case COMMAND_BROODRING:
	case COMMAND_ENSNARE:
		if (_unitNumZ != UNITNUM_ZERG_QUEEN)
		{
			_battleStatus.curCommand = _battleStatus.oldCommand;
		}
		break;
		break;
	case COMMAND_CONSUME:
	case COMMAND_DARKSWARM:
	case COMMAND_PLAGUE:
		if (_unitNumZ != UNITNUM_ZERG_DEFILER)
		{
			_battleStatus.curCommand = _battleStatus.oldCommand;
		}
		break;

		//UNIT2
	//case COMMAND_UNIT_LURKER:
	//case COMMAND_UNIT_GUADIAN:
	//case COMMAND_UNIT_DEVOURER:
	//case COMMAND_UNIT_INFESTEDTERRAN:

	default:
		break;
	}

	if (_battleStatus.unitState == UNITSTATE_ATTACK && _battleStatus.curCommand != COMMAND_ATTACK)
	{
		_battleStatus.unitState = UNITSTATE_MOVE;
	}
}



void Unit::moveGround(void)
{
	//충돌했으면 AStar 를 다시 계산한다.
	if (_battleStatus.isCollision)
	{
		_battleStatus.useAstar = true;
		_battleStatus.calcAstar = true;

		_battleStatus.isCollision = false;
		return;
	}


	if (_battleStatus.targetObject!= NULL)
	{
		if (_battleStatus.useAstar)
		{
			//AstarProc 에서 처리해줄때까지 기다린다.
			if (_battleStatus.calcAstar == false)
			{
				//moveToPoint(_battleStatus.ptTarget);
				return;
			}

			_battleStatus.useAstar = false;
		}

		if (_vCloseList.size() <= 1)
		{
			//다시 계산을 요청한다.
//			_battleStatus.calcAstar = false;

			MYPOINT startPt = _battleStatus.pt;
			MYPOINT endPt = _battleStatus.targetObject->getBattleStatus().pt;
			POINT ptTarget = endPt.toPoint();

			float width1 = _battleStatus.rcBody.right - _battleStatus.rcBody.left;
			float height1 = _battleStatus.rcBody.bottom - _battleStatus.rcBody.top;
			float width2 = _battleStatus.targetObject->getBattleStatus().rcBody.right - _battleStatus.targetObject->getBattleStatus().rcBody.left;
			float height2 = _battleStatus.targetObject->getBattleStatus().rcBody.bottom - _battleStatus.targetObject->getBattleStatus().rcBody.top;

			int gapX = (width1 + width2) / 2;
			int gapY = (height1 + height2) / 2;

			float angleDeg = getAngleDeg(startPt.x, startPt.y, endPt.x, endPt.y);
			if ((angleDeg >= 0 && angleDeg <= 45) || (angleDeg >= 315 && angleDeg < 360))
			{
				//오른쪽방향
				ptTarget.x = endPt.x - gapX;
				ptTarget.y = startPt.y;
			}
			else if (angleDeg > 45 && angleDeg < 135)
			{
				//위쪽방향
				ptTarget.x = startPt.x;
				ptTarget.y = endPt.y + gapY;
			}
			else if (angleDeg >= 135 && angleDeg <= 225)
			{
				//왼쪽방향
				ptTarget.x = endPt.x + gapX;
				ptTarget.y = startPt.y;
			}
			else if (angleDeg > 225 && angleDeg < 315)
			{
				//아래방향
				ptTarget.x = startPt.x;
				ptTarget.y = endPt.y - gapY;
			}

			_battleStatus.ptTarget = ptTarget;

			moveToPoint(_battleStatus.ptTarget);
		}
		else
		{
			tile* nextTile = _vCloseList[_vCloseList.size() - 1];
			POINT ptNext;
			ptNext.x = (nextTile->getIdX() + 0.5f) * TILESIZE;
			ptNext.y = (nextTile->getIdY() + 0.5f) * TILESIZE;

			//실제 이동
			moveToPoint(ptNext);
		}
	}
	else
	{
		POINT ptStartTile, ptEndTile;
		ptStartTile.x = _battleStatus.pt.toPoint().x / TILESIZE;
		ptStartTile.y = _battleStatus.pt.toPoint().y / TILESIZE;
		ptEndTile.x = _battleStatus.ptTarget.x / TILESIZE;
		ptEndTile.y = _battleStatus.ptTarget.y / TILESIZE;

		//같은 타일에 있을때
		if (_battleStatus.ptTile.x == ptEndTile.x && _battleStatus.ptTile.y == ptEndTile.y)
		{
			moveToPoint(_battleStatus.ptTarget);
		}
		//다른 타일에 있을때
		else
		{
			if (_battleStatus.useAstar)
			{
				//AstarProc 에서 처리해줄때까지 기다린다.
				if (_battleStatus.calcAstar == false)
				{
					//moveToPoint(_battleStatus.ptTarget);
					return;
				}

				_battleStatus.useAstar = false;
			}

			if (_vCloseList.size() == 0)
			{
				moveToPoint(_battleStatus.ptTarget);

				//if (_battleStatus.ptTile.x == ptEndTile.x && _battleStatus.ptTile.y == ptEndTile.y)
				//{
				//	moveToPoint(_battleStatus.ptTarget);
				//}
				//else
				//{
				//	moveComplete();
				//}
			}
			else
			{
				tile* nextTile = _vCloseList[_vCloseList.size() - 1];
				POINT ptNext;
				ptNext.x = (nextTile->getIdX() + 0.5f) * TILESIZE;
				ptNext.y = (nextTile->getIdY() + 0.5f) * TILESIZE;

				//실제 이동
				moveToPoint(ptNext);
			}
		}
	}
}

void Unit::moveAir(void)
{
	if (_battleStatus.targetObject != NULL)
	{
		moveToPoint(_battleStatus.targetObject->getBattleStatus().pt.toPoint());
	}
	else
	{
		moveToPoint(_battleStatus.ptTarget);
	}
}

void Unit::moveToPoint(POINT ptEd)
{
	float speed = _battleStatus.moveSpeed;

	MYPOINT ptSt = _battleStatus.pt;

	float distance = getDistance(ptSt.x, ptSt.y, ptEd.x, ptEd.y);

	//가야할 거리가 유닛속도로 갈 거리보다 적을때(가까울 때)
	if (distance < speed)
	{
		speed = distance;
	}

	if (speed < 0.01f)
	{
		//도착했다고 판단
		moveComplete();
		return;
	}

	float angle = getAngle(ptSt.x, ptSt.y, ptEd.x, ptEd.y);
	_battleStatus.angleDeg = Rad2Deg(angle);

	float speedX = speed * cosf(angle);
	float speedY = speed * (-sinf(angle));

	//x, y이동
	ptSt.x += speedX;
	ptSt.y += speedY;

	_battleStatus.pt = ptSt;
}

void Unit::moveComplete(void)
{
	_vCloseList.clear();

	switch (_battleStatus.curCommand)
	{
	case COMMAND_NONE:
		break;
	case COMMAND_MOVE:
		_battleStatus.oldCommand = _battleStatus.curCommand;
		_battleStatus.curCommand = COMMAND_STOP;
		break;
	case COMMAND_STOP:
		break;
	case COMMAND_ATTACK:
		_battleStatus.oldCommand = _battleStatus.curCommand;
		_battleStatus.curCommand = COMMAND_STOP;
		break;
	case COMMAND_PATROL:
		break;
	case COMMAND_HOLD:
		break;
	case COMMAND_GATHER:
		break;
	case COMMAND_RETURNCARGO:
		break;
	case COMMAND_BURROW:
		break;
	case COMMAND_UNBURROW:
		break;
	case COMMAND_INFEST:
		break;
	case COMMAND_PARASITE:
		break;
	case COMMAND_BROODRING:
		break;
	case COMMAND_ENSNARE:
		break;
	case COMMAND_CONSUME:
		break;
	case COMMAND_DARKSWARM:
		break;
	case COMMAND_PLAGUE:
		break;
	default:
		break;
	}


}

void Unit::checkCloseList(void)
{
	if (_vCloseList.size() == 0)
		return;

	vTileIter iter = _vCloseList.begin();
	while (iter != _vCloseList.end())
	{
		if ((*iter)->getIdX() == _battleStatus.ptTile.x
			&& (*iter)->getIdY() == _battleStatus.ptTile.y)
		{
			iter = _vCloseList.erase(iter);
		}
		else ++iter;
	}
}

void Unit::setImageFrameForAngle(void)
{
	int maxFrameNum = _baseStatus.imgBody->getMaxFrameX() + 1;

	float angleDeg = _battleStatus.angleDeg;


	while (angleDeg < 0)
	{
		angleDeg += 360.0f;
	}

	float dAngleDeg = 360.0f / maxFrameNum;

	int iAngleDeg = (int)(angleDeg / dAngleDeg + 0.5);

	//0.5 반올림 때문에 0~max 까지 나오므로 max = 0 이 되도록 한번 빼준다.
	if (iAngleDeg >= maxFrameNum)
		iAngleDeg -= maxFrameNum;

	//여기부터 스프라이트랑 비교해야함
	iAngleDeg = maxFrameNum - (iAngleDeg - maxFrameNum / 4);
	if (iAngleDeg < 0)				iAngleDeg += maxFrameNum;
	if (iAngleDeg >= maxFrameNum)	iAngleDeg -= maxFrameNum;

	_battleStatus.bodyFrame.x = iAngleDeg;
}


void Unit::attackProc(void)
{
	if (_battleStatus.targetObject != NULL && _battleStatus.targetObject->getValid() == FALSE)
	{
		_battleStatus.targetObject = findEnemy();
	}

	if (_baseStatus.AWable == FALSE && _baseStatus.GWable == FALSE)
	{
		//공격 못하는 유닛은 move로 변경
		_battleStatus.curCommand = COMMAND_MOVE;
		return;
	}







	if (_battleStatus.targetObject == NULL)
	{
		_battleStatus.unitState = UNITSTATE_MOVE;

		//어택땅
		_battleStatus.targetObject = findEnemy();

		if (_baseStatus.isAir)
		{
			moveAir();
		}
		else
		{
			moveGround();
		}
	}
	else
	{
		if (_battleStatus.targetObject->getBaseStatus().isAir == TRUE
			&& _baseStatus.AWable == FALSE)
		{
			//타겟이 공중유닛인데 공중공격 못하는 유닛은 move로 변경
			_battleStatus.curCommand = COMMAND_MOVE;
			return;
		}

		if (_battleStatus.targetObject->getBaseStatus().isAir == FALSE
			&& _baseStatus.GWable == FALSE)
		{
			//타겟이 지상유닛인데 지상공격 못하는 유닛은 move로 변경
			_battleStatus.curCommand = COMMAND_MOVE;
			return;
		}

		//
		if (isInAttackRange(_battleStatus.targetObject))
		{
			_battleStatus.unitState = UNITSTATE_ATTACK;
		}
		else
		{
			_battleStatus.unitState = UNITSTATE_MOVE;

			if (_baseStatus.isAir)
			{
				moveAir();
			}
			else
			{
				moveGround();
			}
		}
	}
}

BOOL Unit::isInAttackRange(gameObject* target)
{
	float dist = getDistance(_battleStatus.pt.x, _battleStatus.pt.y,
		target->getBattleStatus().pt.x, target->getBattleStatus().pt.y);

	if (_baseStatus.isAir)
	{
		if (dist < _baseStatus.AWattackRange)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		if (dist < _baseStatus.GWattackRange * TILESIZE)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
}

gameObject* Unit::findEnemy(void)
{
	RECT rcView = RectMakeCenter(_battleStatus.pt.x, _battleStatus.pt.y, _baseStatus.sight, _baseStatus.sight);

	//....적을 받아야함..

	return NULL;
}
