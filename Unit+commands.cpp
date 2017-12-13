#include "stdafx.h"
#include "Unit.h"
#include "Building.h"

void Unit::procCommands(void)
{
	switch (_battleStatus.curCommand)
	{
	case COMMAND_NONE:
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
		break;
	case COMMAND_PATROL:
		break;
	case COMMAND_HOLD:
		break;
	case COMMAND_GATHER:
		break;
	case COMMAND_RETURNCARGO:
		break;
	case COMMAND_BUILD1:
		break;
	case COMMAND_BUILD2:
		break;
	case COMMAND_BURROW:
		break;
	case COMMAND_UNBURROW:
		break;
	case COMMAND_LURKER:
		break;
	case COMMAND_INFEST:
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



void Unit::moveGround(void)
{
	if (_battleStatus.unitTarget != NULL)
	{

	}
	else if (_battleStatus.BuildingTarget != NULL)
	{

	}
	else
	{
		POINT ptStartTile, ptEndTile;
		ptStartTile.x = _battleStatus.pt.toPoint().x / GAMEMAP_TILESIZE;
		ptStartTile.y = _battleStatus.pt.toPoint().y / GAMEMAP_TILESIZE;
		ptEndTile.x = _battleStatus.ptTarget.x / GAMEMAP_TILESIZE;
		ptEndTile.y = _battleStatus.ptTarget.y / GAMEMAP_TILESIZE;

		//���� Ÿ�Ͽ� ������
		if (_battleStatus.ptTile.x == ptEndTile.x && _battleStatus.ptTile.y == ptEndTile.y)
		{
			moveToPoint(_battleStatus.ptTarget);
		}
		//�ٸ� Ÿ�Ͽ� ������
		else
		{
			if (_battleStatus.useAstar)
			{
				_vCloseList.clear();
				_aStar->clearTiles();
				_aStar->setTiles(ptStartTile, ptEndTile);
				_aStar->pathFinder(_aStar->getStartTile());
				_vCloseList = _aStar->getCloseList();
				_battleStatus.useAstar = false;
			}

			if (_vCloseList.size() == 0)
			{
				moveToPoint(_battleStatus.ptTarget);
			}
			else
			{
				tile* nextTile = _vCloseList[0];
				POINT ptNext;
				ptNext.x = (nextTile->getIdX() + 0.5f) * GAMEMAP_TILESIZE;
				ptNext.y = (nextTile->getIdY() + 0.5f) * GAMEMAP_TILESIZE;

				//���� �̵�
				moveToPoint(ptNext);
			}
		}
	}
}

void Unit::moveAir(void)
{

}

void Unit::moveToPoint(POINT ptEd)
{
	float speed = _battleStatus.moveSpeed;

	MYPOINT ptSt = _battleStatus.pt;

	float distance = getDistance(ptSt.x, ptSt.y, ptEd.x, ptEd.y);

	//������ �Ÿ��� ���ּӵ��� �� �Ÿ����� ������(����� ��)
	if (distance < speed)
	{
		speed = distance;
	}

	if (speed < 0.01f)
	{
		//�����ߴٰ� �Ǵ�
		moveComplete();
		return;
	}

	float angle = getAngle(ptSt.x, ptSt.y, ptEd.x, ptEd.y);
	_battleStatus.angleDeg = Rad2Deg(angle);

	float speedX = speed * cosf(angle);
	float speedY = speed * (-sinf(angle));

	//x, y�̵�
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
		_battleStatus.curCommand = COMMAND_STOP;
		break;
	case COMMAND_STOP:
		break;
	case COMMAND_ATTACK:
		break;
	case COMMAND_PATROL:
		break;
	case COMMAND_HOLD:
		break;
	case COMMAND_GATHER:
		break;
	case COMMAND_RETURNCARGO:
		break;
	case COMMAND_BUILD1:
		break;
	case COMMAND_BUILD2:
		break;
	case COMMAND_BURROW:
		break;
	case COMMAND_UNBURROW:
		break;
	case COMMAND_LURKER:
		break;
	case COMMAND_INFEST:
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

	//0.5 �ݿø� ������ 0~max ���� �����Ƿ� max = 0 �� �ǵ��� �ѹ� ���ش�.
	if (iAngleDeg >= maxFrameNum)
		iAngleDeg -= maxFrameNum;

	//������� ��������Ʈ�� ���ؾ���
	iAngleDeg = maxFrameNum - (iAngleDeg - maxFrameNum / 4);
	if (iAngleDeg < 0)				iAngleDeg += maxFrameNum;
	if (iAngleDeg >= maxFrameNum)	iAngleDeg -= maxFrameNum;

	_battleStatus.bodyFrame.x = iAngleDeg;
}

