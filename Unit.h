#pragma once
#include "gameObject.h"
#include "zergUpgrade.h"

#include "aStar.h"

//���漱��
class Building;
class Unit;


struct tagUnitBaseStatus
{
	//Properties
	RACES				race;			//����

	PLAYER				playerNum;		//�÷��̾� ����

	TCHAR				name[50];		//�̸�
	image*				imgBody;		//�̹���-��ü
	image*				imgFace;		//�̹���-��(�����ϴ�)
	image*				imgStat1;		//�̹���-���Ȼ���(1����Ŭ��������)
	image*				imgStat2;		//�̹���-���Ȼ���(����Ŭ��������)

	FLOAT				maxHP;			//HP
	
	BOOL				useSH;			//�ǵ忩��
	FLOAT				maxSH;			//�ǵ�

	BOOL				useMP;			//����������
	FLOAT				maxMP;			//������

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

	COMMAND				commands[COMMAND_MAX];		//������ ����ϴ� Ŀ�ǵ� ��Ʈ
	
};

//BattleStatus
struct tagUnitBattleStatus
{
	BOOL				isDead;
	BOOL				isBusy;			//AStarThread ���� ������϶� �׾ Delete �Ǵ°� ����
	UNITSTATE			unitState;

	COMMAND				curCommand;
	BOOL				useAstar;
	BOOL				calcAstar;
	POINT				ptTarget;
	Unit*				unitTarget;
	Building*			BuildingTarget;


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
	RECT				rcBody;			//���� ��ü
	RECT				rcEllipse;		//Ŭ�������� �����ִ� Ÿ��
	FLOAT				angleDeg;			//�ٶ󺸴� ����
	DIRECTION			direction;		//�����϶� �̵�����

	FLOAT				moveSpeed;		//�̵��ӵ�


	BOOL				isBurrow;

	POINT				bodyFrame;
	POINT				stat1Frame;
	POINT				stat2Frame;

};

class Unit : public gameObject
{
	//��������ó�� Unit �������� ��Ƴ��� ���Ҷ� �ڽ�Ŭ�������� �޾ƿ����� �Ѵ�.
private:
	//static POINT		_zuBodySize[UNITNUM_ZERG_MAX];



public:
	//Unit(bool initUnitInfo);
	Unit();
	~Unit();

	virtual HRESULT init(POINT pt);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//���׷��̵尡 �Ϸ�Ǿ��� �� BattleStatus �� ������Ʈ�Ѵ�.
	virtual void updateBattleStatus(void);
	virtual void updatePosition(void);
	virtual void updateImageFrame(void);


	//Ŀ�ǵ带 ó���Ѵ�.
	virtual void procCommands(void);


	void moveGround(void);
	void moveAir(void);

	void moveToPoint(POINT ptEd);
	void moveComplete(void);

	void checkCloseList(void);

	void setImageFrameForAngle(void);



public:




	//inline POINT getZuBodySize(UNITNUM_ZERG num) { return _zuBodySize[num]; }





};
typedef vector<Unit*>					vUnits;
typedef vector<Unit*>::iterator			vUnitsIter;


