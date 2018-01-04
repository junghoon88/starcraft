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

		//드론에서 처리함--------
		//BUILD1
	//case COMMAND_BUILD_HATCHERY:
	//case COMMAND_BUILD_LAIR:
	//case COMMAND_BUILD_HIVE:
	//case COMMAND_BUILD_CREEPCOLONY:
	//case COMMAND_BUILD_SUNKENCOLONY:
	//case COMMAND_BUILD_SPORECOLONY:
	//case COMMAND_BUILD_EXTRACTOR:
	//case COMMAND_BUILD_SPAWNINGPOOL:
	//case COMMAND_BUILD_EVOLUTIONCHAMBER:
	//case COMMAND_BUILD_HYDRALISKDEN:
		//BUILD2
	//case COMMAND_BUILD_SPIRE:
	//case COMMAND_BUILD_GREATERSPIRE:
	//case COMMAND_BUILD_QUEENSNEST:
	//case COMMAND_BUILD_NYDUSCANAL:
	//case COMMAND_BUILD_ULTRALISKCAVERN:
	//case COMMAND_BUILD_DEFILERMOUND:
	//	break;
		//--------드론에서 처리함

		//UNIT
		//라바에서 처리함--------
	//case COMMAND_UNIT_DRONE:
	//case COMMAND_UNIT_ZERGLING:
	//case COMMAND_UNIT_OVERLORD:
	//case COMMAND_UNIT_HYDRALISK:
	//case COMMAND_UNIT_MUTALISK:
	//case COMMAND_UNIT_SCOURGE:
	//case COMMAND_UNIT_QUEEN:
	//case COMMAND_UNIT_ULTRALISK:
	//case COMMAND_UNIT_DEFILER:
	//--------라바에서 처리함

		//UNIT2
	case COMMAND_UNIT_LURKER:
	case COMMAND_UNIT_GUADIAN:
	case COMMAND_UNIT_DEVOURER:
	case COMMAND_UNIT_INFESTEDTERRAN:

		//UPGRADE
	case COMMAND_UPGRADE_ZERG_MELEEATTACKS:		//저그 지상유닛 근접 공격
	case COMMAND_UPGRADE_ZERG_MISSILEATTACKS:	//저그 지상유닛 원거리 공격
	case COMMAND_UPGRADE_ZERG_CARAPACE:			//저그 지상유닛 방어력
	case COMMAND_UPGRADE_ZERG_FLYERATTACKS:		//저그 공중유닛 공격
	case COMMAND_UPGRADE_ZERG_FLYERCARAPACE:		//저그 공중유닛 방어력

												//EVOLUTION
	case COMMAND_EVOLUTION_ZERG_BURROW:			//저그 버러우 업글
	case COMMAND_EVOLUTION_ZERG_METABOLICK_BOOST:		//저글링 이속업
	case COMMAND_EVOLUTION_ZERG_ADRENAL_GLANDS:			//저글링 아드레날린
	case COMMAND_EVOLUTION_ZERG_VECTRAL_SACS:			//오버로드 수송업
	case COMMAND_EVOLUTION_ZERG_ANTENNAE:				//오버로드 시야업
	case COMMAND_EVOLUTION_ZERG_PNEUMATIZED_CARAPACE:	//오버로드 이속업
	case COMMAND_EVOLUTION_ZERG_MUSCULAR_AUGMENTS:		//히드라 이속업
	case COMMAND_EVOLUTION_ZERG_GROOVED_SPINES:			//히드라 사정거리업
	case COMMAND_EVOLUTION_ZERG_LURKER_ASPECT:	//럴커 업글
	case COMMAND_EVOLUTION_ZERG_SPAWN_BROODLING:	//퀸 브루드링 업글
	case COMMAND_EVOLUTION_ZERG_ENSNARE:			//퀸 인스테어 업글
	case COMMAND_EVOLUTION_ZERG_GAMETE_MEIOSIS:			//퀸 마나업
	case COMMAND_EVOLUTION_ZERG_ANABOLIC_SYNTHESIS:		//울트라 이속업
	case COMMAND_EVOLUTION_ZERG_CHITINOUS_PLATING:		//울트라 방업(+2)
	case COMMAND_EVOLUTION_ZERG_PLAGUE:			//디파일러 플레이그
	case COMMAND_EVOLUTION_ZERG_CONSUME:			//디파일러 컨슘
	case COMMAND_EVOLUTION_ZERG_METASYNAPTIC_NODE:		//디파일러 마나업

	default:
		break;
	}
}



void Unit::moveGround(void)
{
	if (_battleStatus.targetObject!= NULL)
	{

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
					moveToPoint(_battleStatus.ptTarget);
					return;
				}

				//_aStar->setTiles(ptStartTile, ptEndTile);
				//_aStar->pathFinder(_aStar->getStartTile());
				//_vCloseList = _aStar->getCloseList();
				//_battleStatus.useAstar = false;
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

