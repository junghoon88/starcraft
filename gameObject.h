#pragma once
#include "gameNode.h"

#include "zergUpgrade.h"

#include "aStar.h"




//���漱��
class Unit;
class Building;
class gameObject;
class player;

enum UNITSTATE
{
	UNITSTATE_STOP,
	UNITSTATE_MOVE,
	UNITSTATE_ATTACK,
	//UNITSTATE_ATTACK
};

enum WORKSTATE
{
	WORKSTATE_IDLE,
	WORKSTATE_MOVETO_MINERAL,
	WORKSTATE_WAITING_MINERAL,
	WORKSTATE_GATHERING_MINERAL,
	WORKSTATE_RETURN_MINERAL,
	WORKSTATE_MOVETO_GAS,
	WORKSTATE_WAITING_GAS,
	WORKSTATE_GATHERING_GAS,
	WORKSTATE_RETURN_GAS
};



//BaseStatus
struct tagBaseStatus
{
	//Properties
	TCHAR				name[50];		//�̸�
	image*				imgBody;		//�̹���-��ü
	image*				imgFace;		//�̹���-��(�����ϴ�)
	image*				imgStat1;		//�̹���-���Ȼ���(1����Ŭ��������)
	image*				imgStat2;		//�̹���-���Ȼ���(����Ŭ��������)

	FLOAT				unitControl;	//������ �����ϴ� �α���
	FLOAT				publicControl;	//�������ִ� �α���

	FLOAT				maxHP;			//HP

	BOOL				useSH;			//�ǵ忩��
	FLOAT				maxSH;			//�ǵ�

	BOOL				useMP;			//����������
	FLOAT				maxMP;			//������

	FLOAT				sight;			//�þ�
	BOOL				detector;		//������(�����ε�, �������ݷδ�)

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
struct tagBattleStatus
{
	BOOL				isDead;			//
	BOOL				isBusy;			//AStarThread ���� ������϶� �׾ Delete �Ǵ°� ����
	UNITSTATE			unitState;		//

	COMMAND				curCommand;		//
	BOOL				useAstar;		//
	BOOL				calcAstar;		//
	POINT				ptTarget;		//�̵��Ҷ� ������ ��ġ
	POINT				ptTileTarget;	//�ǹ� ������ �߰��� �޴� ��ġ
	gameObject*			targetObject;	//


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
	RECT				rcTile;			//�ǹ��� �����ϴ� Ÿ��
	RECT				rcEllipse;		//Ŭ�������� �����ִ� Ÿ��
	FLOAT				angleDeg;		//�ٶ󺸴� ����
	DIRECTION			direction;		//�����϶� �̵�����

	FLOAT				moveSpeed;		//�̵��ӵ�


	BOOL				isBurrow;

	POINT				bodyFrame;
	FLOAT				bodyFrameTime;
	POINT				stat1Frame;
	POINT				stat2Frame;

};

class gameObject : public gameNode
{
protected:
	//��ȿ�� ������Ʈ����
	//gameObject�� �������� MemoryPooling �� �Ұ��̱� ������
	//Unit�̳� Building���� init �� �Ǿ����� Ȯ�ο�
	BOOL					_valid;

	gameObject*				_nextObject;	//�����̳� �ǹ��� �ٸ� ������Ʈ�� ������ ���, ���� ������Ʈ�� �������ش�.

	//�÷��̾� ����
	player*					_player;
	PLAYER					_playerNum;

	//����
	RACES					_race;			

	//�������� �ǹ�����
	BOOL					_isBuilding;

	//���� ���� ��ȣ
	UNITNUM_ZERG			_unitNumZ;
	UNITNUM_TERRAN			_unitNumT;
	UNITNUM_PROTOSS			_unitNumP;
	//�ǹ� ���� ��ȣ
	BUILDINGNUM_ZERG		_buildingNumZ;
	BUILDINGNUM_TERRAN		_buildingNumT;
	BUILDINGNUM_PROTOSS		_buildingNumP;


	//�⺻�Ӽ��� �ǽð��Ӽ����� ������!
	tagBaseStatus			_baseStatus;
	tagBattleStatus			_battleStatus;
	
	zergUpgrade*			_zergUpgrade;

	aStar*					_aStar;
	vTile					_vCloseList;	//A* ���� ���Ǽ� ���� Ÿ�ϵ�

public:
	gameObject();
	~gameObject();

	virtual HRESULT init(void);	//�ʱ�ȭ
	virtual void release(void);	//�޸� ����
	virtual void update(void);	//�������(Ÿ�̸�)
	virtual void render(void);	//�׷��ִ� �Լ�
	virtual void getChar(WPARAM wParam);

	//���׷��̵尡 �Ϸ�Ǿ��� �� BattleStatus �� ������Ʈ�Ѵ�.
	virtual void updateBattleStatus(void);
	virtual void updatePosition(void);
	virtual void updateImageFrame(void);

	void receiveCommand(COMMAND cmd);
	void receiveCommand(COMMAND cmd, POINT pt);
	void receiveCommand(COMMAND cmd, POINT pt, POINT ptTile);
	void receiveCommand(COMMAND cmd, gameObject* object);



public:
	inline BOOL getValid(void) { return _valid; }
	inline gameObject* getNextObject(void) { return _nextObject; }
	inline player* getPlayer(void) { return _player; }
	inline PLAYER getPlayerNum(void) { return _playerNum; }
	inline RACES getRaces(void) { return _race; }
	inline BOOL getIsBuilding(void) { return _isBuilding; }

	inline void setLinkAdressZergUpgrade(zergUpgrade* zergUpgrade) { _zergUpgrade = zergUpgrade; }
	inline void setLinkAdressAstar(aStar* astar) { _aStar = astar; }
	inline void setLinkAdressPlayer(player* player) { _player = player; }

	inline UNITNUM_ZERG		getUnitnumZerg(void)	{ return _unitNumZ; }
	inline UNITNUM_TERRAN	getUnitnumTerran(void)	{ return _unitNumT; }
	inline UNITNUM_PROTOSS	getUnitnumProtoss(void) { return _unitNumP; }

	inline BUILDINGNUM_ZERG		getBuildingNumZerg(void)	{ return _buildingNumZ; }
	inline BUILDINGNUM_TERRAN	getBuildingNumTerran(void)	{ return _buildingNumT; }
	inline BUILDINGNUM_PROTOSS	getBuildingNumProtoss(void) { return _buildingNumP; }

	inline tagBaseStatus getBaseStatus(void) { return _baseStatus; }
	inline tagBattleStatus getBattleStatus(void) { return _battleStatus; }
	inline void setBattleStatus(tagBattleStatus status) { _battleStatus = status; }

	//A* ����
	inline BOOL getIsBusy(void) { return _battleStatus.isBusy; }
	inline void setIsBusy(BOOL busy) { _battleStatus.isBusy = busy; }
	inline void setCalcAstar(BOOL calc) { _battleStatus.calcAstar = calc; }
	inline void setVCloseList(vTile list) { _vCloseList = list; }

	//baseStatus �� �Ϻθ� ������

	//battleStatus �� �Ϻθ� ������
	inline void setClicked(BOOL clicked) { _battleStatus.clicked = clicked; }

};
