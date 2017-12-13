#pragma once
#include "gameNode.h"

#include "zergUpgrade.h"

//���漱��
class Unit;

struct tagBuildingBaseStatus
{
	RACES				race;			//����

	PLAYER				playerNum;		//�÷��̾� ����

	TCHAR				name[50];		//�̸�
	image*				imgBody;		//�̹���-��ü
	image*				imgFace;		//�̹���-��(�����ϴ�)
	image*				imgStat;		//�̹���-���Ȼ���(1����Ŭ��������)

	FLOAT				curHP;			//HP
	FLOAT				maxHP;			//HP

	BOOL				useSH;			//�ǵ忩��
	FLOAT				curSH;			//�ǵ�
	FLOAT				maxSH;			//�ǵ�

	BOOL				useMP;			//����������
	FLOAT				maxMP;			//������

	FLOAT				sight;			//�þ�

	BOOL				isAir;			//���߿� �ִ���(�׶��ǹ�)
	FLOAT				moveSpeed;		//�̵��ӵ�

	UINT				armor;			//����

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

struct tagBuildingBattleStatus
{
	BOOL				isDead;

	DWORD				curCommand;

	BOOL				clicked;

	FLOAT				curHP;			//���� HP
	FLOAT				maxHP;			//�ִ� HP
	FLOAT				curSH;			//���� �ǵ�
	FLOAT				maxSH;			//�ִ� �ǵ�
	FLOAT				curMP;			//���� ������
	FLOAT				maxMP;			//�ִ� ������

	UINT				curGWdamage;	//���� ������ݷ�
	UINT				curAWdamage;	//���� ���߰��ݷ�
	UINT				curArmor;		//���� ����


	MYPOINT				pt;				//������ġ
	POINT				ptTile;			//������ġ�� Ÿ��
	RECT				rcBody;			//�ǹ� ��ü
	RECT				rcTile;			//�ǹ��� �����ϴ� Ÿ��

	RECT				rcEllipse;		//Ŭ�������� �����ִ� Ÿ��
	FLOAT				angle;			//�ٶ󺸴� ����
	DIRECTION			direction;		//�����϶� �̵�����

	POINT				bodyFrame;
	POINT				stat1Frame;
	POINT				stat2Frame;
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


	//�⺻�Ӽ��� �ǽð��Ӽ����� ������!
	tagBuildingBaseStatus		_baseStatus;
	tagBuildingBattleStatus		_battleStatus;

	zergUpgrade*		_zergUpgrade;



public:
	Building();
	~Building();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

public:

};
typedef vector<Building*>				vBuildings;
typedef vector<Building*>::iterator		vBuildingsIter;

