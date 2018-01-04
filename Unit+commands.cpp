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

		//��п��� ó����--------
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
		//--------��п��� ó����

		//UNIT
		//��ٿ��� ó����--------
	//case COMMAND_UNIT_DRONE:
	//case COMMAND_UNIT_ZERGLING:
	//case COMMAND_UNIT_OVERLORD:
	//case COMMAND_UNIT_HYDRALISK:
	//case COMMAND_UNIT_MUTALISK:
	//case COMMAND_UNIT_SCOURGE:
	//case COMMAND_UNIT_QUEEN:
	//case COMMAND_UNIT_ULTRALISK:
	//case COMMAND_UNIT_DEFILER:
	//--------��ٿ��� ó����

		//UNIT2
	case COMMAND_UNIT_LURKER:
	case COMMAND_UNIT_GUADIAN:
	case COMMAND_UNIT_DEVOURER:
	case COMMAND_UNIT_INFESTEDTERRAN:

		//UPGRADE
	case COMMAND_UPGRADE_ZERG_MELEEATTACKS:		//���� �������� ���� ����
	case COMMAND_UPGRADE_ZERG_MISSILEATTACKS:	//���� �������� ���Ÿ� ����
	case COMMAND_UPGRADE_ZERG_CARAPACE:			//���� �������� ����
	case COMMAND_UPGRADE_ZERG_FLYERATTACKS:		//���� �������� ����
	case COMMAND_UPGRADE_ZERG_FLYERCARAPACE:		//���� �������� ����

												//EVOLUTION
	case COMMAND_EVOLUTION_ZERG_BURROW:			//���� ������ ����
	case COMMAND_EVOLUTION_ZERG_METABOLICK_BOOST:		//���۸� �̼Ӿ�
	case COMMAND_EVOLUTION_ZERG_ADRENAL_GLANDS:			//���۸� �Ƶ巹����
	case COMMAND_EVOLUTION_ZERG_VECTRAL_SACS:			//�����ε� ���۾�
	case COMMAND_EVOLUTION_ZERG_ANTENNAE:				//�����ε� �þ߾�
	case COMMAND_EVOLUTION_ZERG_PNEUMATIZED_CARAPACE:	//�����ε� �̼Ӿ�
	case COMMAND_EVOLUTION_ZERG_MUSCULAR_AUGMENTS:		//����� �̼Ӿ�
	case COMMAND_EVOLUTION_ZERG_GROOVED_SPINES:			//����� �����Ÿ���
	case COMMAND_EVOLUTION_ZERG_LURKER_ASPECT:	//��Ŀ ����
	case COMMAND_EVOLUTION_ZERG_SPAWN_BROODLING:	//�� ���帵 ����
	case COMMAND_EVOLUTION_ZERG_ENSNARE:			//�� �ν��׾� ����
	case COMMAND_EVOLUTION_ZERG_GAMETE_MEIOSIS:			//�� ������
	case COMMAND_EVOLUTION_ZERG_ANABOLIC_SYNTHESIS:		//��Ʈ�� �̼Ӿ�
	case COMMAND_EVOLUTION_ZERG_CHITINOUS_PLATING:		//��Ʈ�� ���(+2)
	case COMMAND_EVOLUTION_ZERG_PLAGUE:			//�����Ϸ� �÷��̱�
	case COMMAND_EVOLUTION_ZERG_CONSUME:			//�����Ϸ� ����
	case COMMAND_EVOLUTION_ZERG_METASYNAPTIC_NODE:		//�����Ϸ� ������

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
				//AstarProc ���� ó�����ٶ����� ��ٸ���.
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

				//���� �̵�
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

	//0.5 �ݿø� ������ 0~max ���� �����Ƿ� max = 0 �� �ǵ��� �ѹ� ���ش�.
	if (iAngleDeg >= maxFrameNum)
		iAngleDeg -= maxFrameNum;

	//������� ��������Ʈ�� ���ؾ���
	iAngleDeg = maxFrameNum - (iAngleDeg - maxFrameNum / 4);
	if (iAngleDeg < 0)				iAngleDeg += maxFrameNum;
	if (iAngleDeg >= maxFrameNum)	iAngleDeg -= maxFrameNum;

	_battleStatus.bodyFrame.x = iAngleDeg;
}

