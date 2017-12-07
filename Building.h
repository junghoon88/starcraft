#pragma once
#include "gameNode.h"

struct tagProperties
{
	RACES				race;			//����

	TCHAR				name[50];		//�̸�
	image*				imgBody;		//�̹���-��ü
	animation*			aniFace;		//�̹���-��(�����ϴ�)
	image*				imgStat;		//�̹���-���Ȼ���(1����Ŭ��������)

	FLOAT				curHP;			//HP
	FLOAT				maxHP;			//HP

	BOOL				isShield;		//�ǵ忩��
	FLOAT				curSH;			//�ǵ�
	FLOAT				maxSH;			//�ǵ�

	FLOAT				sight;			//�þ�

	BOOL				isAir;			//���߿� �ִ���(�׶��ǹ�)
	FLOAT				moveSpeed;		//�̵��ӵ�

	UNITSIZE			unitSize;		//���ֻ�����
	UINT				transportslots;	//���� ����ĭ ��
	UINT				armor;			//����

};

struct tagProduction
{
	UINT				costMinerals;	//�Ҹ� �̳׶�
	UINT				costGas;		//�Ҹ� ����
	FLOAT				buildTime;		//����ð�
	TCHAR				hotKey;			//����Ű
};

struct tagCombat
{
	BOOL				sameGWAW;		//�������, ���߰����� ������

										//Ground Weapon
	BOOL				GWable;			//������� ���ɿ���
	TCHAR				GWname[100];	//�����̸�
	UINT				GWdamage;		//���ݵ�����
	UINT				GWdamagePlus;	//���ݺ��ʽ�������
	UINT				GWmaxHit;		//�����ִ�Ƚ��(�����Ӵ�) 
	DAMAGETYPE			GWdamageType;	//����Ÿ��
	FLOAT				GWcooldown;		//������Ÿ��
	FLOAT				GWattackRange;	//���ݹ���

										//Air Weapon
	BOOL				AWable;			//���߰��� ���ɿ���
	TCHAR				AWname[100];	//�����̸�
	UINT				AWdamage;		//���ݵ�����
	UINT				AWdamagePlus;	//���ݺ��ʽ�������
	UINT				AWmaxHit;		//�����ִ�Ƚ��(�����Ӵ�) 
	DAMAGETYPE			AWdamageType;	//����Ÿ��
	FLOAT				AWcooldown;		//������Ÿ��
	FLOAT				AWattackRange;	//���ݹ���
};

struct tagPosition
{
	MYPOINT				pt;				//������ġ
	POINT				ptTile;			//������ġ�� Ÿ��
	RECT				rcBody;			//�ǹ� ��ü
	RECT				rcTile;			//�ǹ��� �����ϴ� Ÿ��

	RECT				rcEllipse;		//Ŭ�������� �����ִ� Ÿ��
	DIRECTION			direction;		//�����϶� �̵�����
	FLOAT				angle;			//�ٶ󺸴� ����

};

class Building : public gameNode
{
protected:
	//���� ���� ��ȣ�� �Է¹޴´�. 
	//�� �� �ϳ��� ���� �־���ϸ�
	//�� �� -1 ���� -1�̸� ����
	UNITNUM_ZERG		_unitNumZ;
	UNITNUM_TERRAN		_unitNumT;
	UNITNUM_PROTOSS		_unitNumP;


	//Properties
	tagProperties		_properties;

	//Production
	tagProduction		_production;

	//combat
	tagCombat			_combat;


public:
	Building();
	~Building();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

public:

};

