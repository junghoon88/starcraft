#include "stdafx.h"
#include "zuZergEgg.h"



zuZergEgg::zuZergEgg(PLAYER playerNum, UNITNUM_ZERG nextUnitNum)
{
	_valid = true;

	//�÷��̾� ����
	_playerNum = playerNum;

	//����
	_race = RACES_ZERG;

	//�������� �ǹ�����
	_isBuilding = false;

	//���� ���� ��ȣ
	_unitNumZ = UNITNUM_ZERG_ZERGEGG;

	_nextUnitNum = nextUnitNum;

	_complete = false;

	_zergProductionInfo = new zergProductionInfo;
}


zuZergEgg::~zuZergEgg()
{
}

HRESULT zuZergEgg::init(POINT pt)
{
	initBaseStatus();
	initBattleStatus(pt);



	updatePosition();

	updateBattleStatus();


	return S_OK;
}


void zuZergEgg::initBaseStatus(void)
{
	//Properties
	_stprintf(_baseStatus.name, L"Zerg Egg");	//�̸�
												//BaseStatus
	TCHAR strKey[100];
	_stprintf(strKey, L"ZU-zergeggBody%d", _playerNum);
	_baseStatus.imgBody = IMAGEMANAGER->findImage(strKey);				//�̹���-��ü
	_baseStatus.imgFace = NULL;											//�̹���-��(�����ϴ�)
	_baseStatus.imgStat1 = NULL;//IMAGEMANAGER->findImage(L"ZU-droneStat1");	//�̹���-���Ȼ���(1����Ŭ��������)
	_baseStatus.imgStat2 = NULL;//IMAGEMANAGER->findImage(L"ZU-droneStat2");	//�̹���-���Ȼ���(����Ŭ��������)

	_baseStatus.maxHP = 200.0f;					//HP

	_baseStatus.useSH = FALSE;					//�ǵ忩��
	_baseStatus.maxSH = 0.0f;					//�ǵ�

	_baseStatus.useMP = FALSE;					//����������
	_baseStatus.maxMP = 0.0f;					//������

	_baseStatus.sight = 5.0f;					//�þ�
	_baseStatus.detector = FALSE;				//������(�����ε�, �������ݷδ�)

	_baseStatus.isAir = FALSE;					//������������
	_baseStatus.moveSpeed = 0.0f;				//�̵��ӵ�

	_baseStatus.unitSize = UNITSIZE_SMALL;		//���ֻ�����
	_baseStatus.transportslots = 0;				//���� ����ĭ ��
	_baseStatus.armor = 10;						//����
	_baseStatus.armorPlus = 1;					//�߰� ����

												//combat
	_baseStatus.sameGWAW = FALSE;						//�������, ���߰����� ������
	_baseStatus.GWable = FALSE;							//������� ���ɿ���
	_baseStatus.AWable = FALSE;							//���߰��� ���ɿ���

	_baseStatus.commands[0] = COMMAND_NONE;
	_baseStatus.commands[1] = COMMAND_NONE;
	_baseStatus.commands[2] = COMMAND_NONE;
	_baseStatus.commands[3] = COMMAND_NONE;
	_baseStatus.commands[4] = COMMAND_NONE;
	_baseStatus.commands[5] = COMMAND_NONE;
	_baseStatus.commands[6] = COMMAND_NONE;
	_baseStatus.commands[7] = COMMAND_NONE;
	_baseStatus.commands[8] = COMMAND_ESC;
}
void zuZergEgg::initBattleStatus(POINT pt)
{
	//BattleStatus
	_battleStatus.unitState = UNITSTATE_STOP;
	_battleStatus.curCommand = COMMAND_STOP;
	_battleStatus.clicked = false;
	_battleStatus.curHP = _baseStatus.maxHP;			//���� HP
	_battleStatus.maxHP = _baseStatus.maxHP;			//�ִ� HP

	_battleStatus.pt.set((float)pt.x, (float)pt.y);							//������ġ
	_battleStatus.moveSpeed = _baseStatus.moveSpeed;
}


void zuZergEgg::release(void)
{
	SAFE_DELETE(_zergProductionInfo);
}

void zuZergEgg::update(void)
{
	if (_battleStatus.bodyFrame.x < 4)
	{
		_battleStatus.bodyFrame.x++;
	}
	else
	{
		if (_complete == false)
		{
			_battleStatus.bodyFrameTime += TIMEMANAGER->getElapsedTime();
			if (_battleStatus.bodyFrameTime >= UNIT_BODY_FPS_TIME)
			{
				_battleStatus.bodyFrameTime -= UNIT_BODY_FPS_TIME;
				_battleStatus.bodyFrame.x = (_battleStatus.bodyFrame.x == 6) ? 4 : _battleStatus.bodyFrame.x + 1;
			}
		}
		else
		{

		}
	}

}

void zuZergEgg::render(void)
{

}

void zuZergEgg::updateBattleStatus(void)
{

}
void zuZergEgg::updatePosition(void)
{

}
void zuZergEgg::updateImageFrame(void)
{

}

void zuZergEgg::procCommands(void)
{

}
