#pragma once
#include "gameNode.h"
#include "zergUpgrade.h"

#include "aStar.h"

//���漱��
class Building;
class Unit;

enum UNITSTATE
{
	UNITSTATE_STOP,
	UNITSTATE_MOVE,
	UNITSTATE_ATTACK,
	//UNITSTATE_ATTACK
};

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

	DWORD				commands[COMMAND_MAX];		//������ ����ϴ� Ŀ�ǵ� ��Ʈ
	
};

//BattleStatus
struct tagUnitBattleStatus
{
	BOOL				isDead;
	UNITSTATE			unitState;

	COMMAND				curCommand;
	BOOL				useAstar;
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
	tagUnitBaseStatus	_baseStatus;
	tagUnitBattleStatus	_battleStatus;
	
	zergUpgrade*		_zergUpgrade;

	aStar*				_aStar;
	vTile				_vCloseList;	//A* ���� ���Ǽ� ���� Ÿ�ϵ�


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
	virtual void updatePosition(void);
	virtual void updateImageFrame(void);


	//Ŀ�ǵ带 ó���Ѵ�.
	void procCommands(void);

	void receiveCommand(COMMAND cmd, POINT pt);
	void receiveCommand(COMMAND cmd, Unit* unit);
	void receiveCommand(COMMAND cmd, Building* building);

	void moveGround(void);
	void moveAir(void);

	void moveToPoint(POINT ptEd);
	void moveComplete(void);

	void checkCloseList(void);

	void setImageFrameForAngle(void);



public:
	inline void setLinkAdressZergUpgrade(zergUpgrade* zergUpgrade) { _zergUpgrade = zergUpgrade; }
	inline void setLinkAdressAstar(aStar* astar) { _aStar = astar; }


	inline UNITNUM_ZERG		getUnitnumZerg(void) { return _unitNumZ; }
	inline UNITNUM_TERRAN	getUnitnumTerran(void) { return _unitNumT; }
	inline UNITNUM_PROTOSS	getUnitnumProtoss(void) { return _unitNumP; }


	inline POINT getZuBodySize(UNITNUM_ZERG num) { return _zuBodySize[num]; }

	inline tagUnitBaseStatus getBaseStatus(void) { return _baseStatus; }
	inline tagUnitBattleStatus getBattleStatus(void) { return _battleStatus; }


	inline void setClicked(BOOL clicked) { _battleStatus.clicked = clicked; }

};
typedef vector<Unit*>					vUnits;
typedef vector<Unit*>::iterator			vUnitsIter;


