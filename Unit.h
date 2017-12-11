#pragma once
#include "gameNode.h"
#include "zergUpgrade.h"

struct tagBaseStatus
{
	//Properties
	RACES				race;			//����

	PLAYER				playerNum;

	TCHAR				name[50];		//�̸�
	image*				imgBody;		//�̹���-��ü
	animation*			aniFace;		//�̹���-��(�����ϴ�)
	image*				imgStat1;		//�̹���-���Ȼ���(1����Ŭ��������)
	image*				imgStat2;		//�̹���-���Ȼ���(����Ŭ��������)

	FLOAT				maxHP;			//HP
	
	BOOL				isShield;		//�ǵ忩��
	FLOAT				maxSH;			//�ǵ�

	BOOL				isEnergy;		//����������
	FLOAT				maxEN;			//������

	FLOAT				sight;			//�þ�

	BOOL				isAir;			//������������
	FLOAT				moveSpeed;		//�̵��ӵ�

	UNITSIZE			unitSize;		//���ֻ�����
	UINT				transportslots;	//���� ����ĭ ��
	UINT				armor;			//����
	UINT				armorPlus;		//�߰� ����

	//combat
	BOOL				sameGWAW;		//�������, ���߰����� ������

	//Ground Weapon
	BOOL				GWable;			//������� ���ɿ���
	ATTACKTYPE			GWAttackType;	//����Ÿ��(���׷��̵忡 ���)
	TCHAR				GWname[100];	//�����̸�
	UINT				GWdamage;		//���ݷ�
	UINT				GWdamagePlus;	//�߰� ���ݷ�
	UINT				GWmaxHit;		//�����ִ�Ƚ��(�����Ӵ�) 
	DAMAGETYPE			GWdamageType;	//����Ÿ��
	FLOAT				GWcooldown;		//������Ÿ��
	FLOAT				GWattackRange;	//���ݹ���

	//Air Weapon
	BOOL				AWable;			//���߰��� ���ɿ���
	ATTACKTYPE			AWAttackType;	//����Ÿ��(���׷��̵忡 ���)
	TCHAR				AWname[100];	//���ݷ�
	UINT				AWdamage;		//�߰� ���ݷ�
	UINT				AWdamagePlus;	//���ݺ��ʽ�������
	UINT				AWmaxHit;		//�����ִ�Ƚ��(�����Ӵ�) 
	DAMAGETYPE			AWdamageType;	//����Ÿ��
	FLOAT				AWcooldown;		//������Ÿ��
	FLOAT				AWattackRange;	//���ݹ���

};

//BattleStatus
struct tagBattleStatus
{
	FLOAT				curHP;			//���� HP
	FLOAT				maxHP;			//�ִ� HP
	FLOAT				curSH;			//���� �ǵ�
	FLOAT				maxSH;			//�ִ� �ǵ�
	FLOAT				curEN;			//���� ������
	FLOAT				maxEN;			//�ִ� ������

	UINT				curGWdamage;	//���� ������ݷ�
	UINT				curAWdamage;	//���� ���߰��ݷ�
	UINT				curArmor;		//���� ����


	MYPOINT				pt;				//������ġ
	POINT				ptTile;			//������ġ�� Ÿ��
	RECT				rcBody;			//���� ��ü
	RECT				rcEllipse;		//Ŭ�������� �����ִ� Ÿ��
	FLOAT				angle;			//�ٶ󺸴� ����
	DIRECTION			direction;		//�����϶� �̵�����

	POINT				bodyFrame;
	POINT				stat1Frame;
	POINT				stat2Frame;
};

//PlayerInfo
struct tagPlayerControl
{
	BOOL				clicked;
};

class Unit : public gameNode
{
	//��������ó�� Unit �������� ��Ƴ��� ���Ҷ� �ڽ�Ŭ�������� �޾ƿ����� �Ѵ�.
private:
	static POINT		_zuBodySize[UNITNUM_ZERG_MAX];


protected:
	//���� ���� ��ȣ�� �Է¹޴´�. 
	//�� �� �ϳ��� ���� �־���ϸ�
	//�� �� -1 ���� -1�̸� ����
	UNITNUM_ZERG		_unitNumZ;
	UNITNUM_TERRAN		_unitNumT;
	UNITNUM_PROTOSS		_unitNumP;

	//�⺻�Ӽ��� �ǽð��Ӽ����� ������!
	tagBaseStatus		_baseStatus;
	tagBattleStatus		_battleStatus;
	
	zergUpgrade*		_zergUpgrade;


public:
	Unit(bool initUnitInfo);
	Unit();
	~Unit();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//���׷��̵尡 �Ϸ�Ǿ��� �� BattleStatus �� ������Ʈ�Ѵ�.
	virtual void updateBattleStatus(void);


public:
	inline void setLinkAdressZergUpgrade(zergUpgrade* zergUpgrade) { _zergUpgrade = zergUpgrade; }
	inline POINT getZuBodySize(UNITNUM_ZERG num) { return _zuBodySize[num]; }

	inline tagBaseStatus getBaseStatus(void) { return _baseStatus; }
	inline tagBattleStatus getBattleStatus(void) { return _battleStatus; }


};

