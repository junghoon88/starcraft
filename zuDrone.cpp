#include "stdafx.h"
#include "zuDrone.h"
#include "tileNode.h"


zuDrone::zuDrone()
{
	//���� ���� ��ȣ
	_unitNumZ = UNITNUM_ZERG_DRONE;

	//Properties
	_baseStatus.race = RACES_ZERG;				//����

	_stprintf(_baseStatus.name, L"Zerg Drone");	//�̸�
	_baseStatus.imgBody = NULL;					//�̹���-��ü
	_baseStatus.aniFace = NULL;					//�̹���-��(�����ϴ�)
	_baseStatus.imgStat1 = NULL;				//�̹���-���Ȼ���(1����Ŭ��������)
	_baseStatus.imgStat2 = NULL;				//�̹���-���Ȼ���(����Ŭ��������)

	_baseStatus.maxHP = 40.0f;					//HP

	_baseStatus.isShield = FALSE;				//�ǵ忩��
	_baseStatus.maxSH = 0.0f;					//�ǵ�

	_baseStatus.isEnergy = FALSE;				//����������
	_baseStatus.maxEN = 0.0f;					//������

	_baseStatus.sight = 7.0f;					//�þ�

	_baseStatus.isAir = FALSE;					//������������
	_baseStatus.moveSpeed = 5.0f;				//�̵��ӵ�

	_baseStatus.unitSize = UNITSIZE_SMALL;		//���ֻ�����
	_baseStatus.transportslots = 1;				//���� ����ĭ ��
	_baseStatus.armor = 0;						//����
	_baseStatus.armorPlus = 1;					//�߰� ����



	//combat
	_baseStatus.sameGWAW = FALSE;						//�������, ���߰����� ������

	_baseStatus.GWable = TRUE;							//������� ���ɿ���
	_baseStatus.GWAttackType = ATTACKTYPE_ZERG_WORKER;	//����Ÿ��(���׷��̵忡 ���)
	_stprintf(_baseStatus.GWname, L"���û�");			//�����̸�
	_baseStatus.GWdamage = 5;							//���ݵ�����
	_baseStatus.GWdamagePlus = 0;						//���ݺ��ʽ�������
	_baseStatus.GWmaxHit = 1;							//�����ִ�Ƚ��(�����Ӵ�) 
	_baseStatus.GWdamageType = DAMAGETYPE_NORMAL;		//����Ÿ��
	_baseStatus.GWcooldown = 22.0f;						//������Ÿ��
	_baseStatus.GWattackRange = 1.0f;					//���ݹ���

	_baseStatus.AWable = FALSE;							//���߰��� ���ɿ���
	//_baseStatus.AWAttackType;							//����Ÿ��(���׷��̵忡 ���)
	//_baseStatus.AWname[100];							//�����̸�
	//_baseStatus.AWdamage;								//���ݵ�����
	//_baseStatus.AWdamagePlus;							//���ݺ��ʽ�������
	//_baseStatus.AWmaxHit;								//�����ִ�Ƚ��(�����Ӵ�) 
	//_baseStatus.AWdamageType;							//����Ÿ��
	//_baseStatus.AWcooldown;							//������Ÿ��
	//_baseStatus.AWattackRange;						//���ݹ���
}


zuDrone::~zuDrone()
{
}

HRESULT zuDrone::init(PLAYER playerNum, POINT pt)
{
	//BaseStatus
	_baseStatus.playerNum = playerNum;

	TCHAR strKey[100];
	_stprintf(strKey, L"ZU-droneBody%d", playerNum);
	_baseStatus.imgBody = IMAGEMANAGER->findImage(strKey);				//�̹���-��ü
	_baseStatus.aniFace = NULL;											//�̹���-��(�����ϴ�)
	_baseStatus.imgStat1 = IMAGEMANAGER->findImage(L"ZU-droneStat1");	//�̹���-���Ȼ���(1����Ŭ��������)
	_baseStatus.imgStat2 = IMAGEMANAGER->findImage(L"ZU-droneStat2");	//�̹���-���Ȼ���(����Ŭ��������)


	//BattleStatus
	_battleStatus.curHP = _baseStatus.maxHP;			//���� HP
	_battleStatus.maxHP = _baseStatus.maxHP;			//�ִ� HP
	_battleStatus.curSH = _baseStatus.maxSH;			//���� �ǵ�
	_battleStatus.maxSH = _baseStatus.maxSH;			//�ִ� �ǵ�
	_battleStatus.curEN = 0.0f;							//���� ������
	_battleStatus.maxEN = _baseStatus.maxEN;			//�ִ� ������

	_battleStatus.pt.set((float)pt.x, (float)pt.y);							//������ġ
	_battleStatus.ptTile = { pt.x / MAPTOOL_TILESIZE, pt.y / MAPTOOL_TILESIZE };			//������ġ�� Ÿ��
	_battleStatus.rcBody = RectMakeCenter(pt.x, pt.y, getZuBodySize(_unitNumZ).x, getZuBodySize(_unitNumZ).y);			//���� ��ü
	_battleStatus.rcEllipse;		//Ŭ�������� �����ִ� Ÿ��
	_battleStatus.angle;			//�ٶ󺸴� ����
	_battleStatus.direction;		//�����϶� �̵�����

	updateBattleStatus();

	return S_OK;
}

void zuDrone::release(void)
{

}

void zuDrone::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_battleStatus.bodyFrame.x++;
		if (_battleStatus.bodyFrame.x > _baseStatus.imgBody->getMaxFrameX())
		{
			_battleStatus.bodyFrame.x = 0;
		}
	}
}

void zuDrone::render(void)
{
	Unit::render();

}

void zuDrone::updateBattleStatus(void)
{
	Unit::updateBattleStatus();


}