#pragma once
#include "gameNode.h"
#include "zergUpgrade.h"

#include "aStar.h"

//전방선언
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
	RACES				race;			//종족

	PLAYER				playerNum;		//플레이어 정보

	TCHAR				name[50];		//이름
	image*				imgBody;		//이미지-몸체
	image*				imgFace;		//이미지-얼굴(우측하단)
	image*				imgStat1;		//이미지-스탯상태(1마리클릭했을때)
	image*				imgStat2;		//이미지-스탯상태(복수클릭했을때)

	FLOAT				maxHP;			//HP
	
	BOOL				useSH;			//실드여부
	FLOAT				maxSH;			//실드

	BOOL				useMP;			//에너지여부
	FLOAT				maxMP;			//에너지

	FLOAT				sight;			//시야

	BOOL				isAir;			//공중유닛인지
	FLOAT				moveSpeed;		//이동속도

	UNITSIZE			unitSize;		//유닛사이즈
	UINT				transportslots;	//수송 슬롯칸 수
	UINT				armor;			//방어력
	UINT				armorPlus;		//추가 방어력

	//combat
	BOOL				sameGWAW;		//지상공격, 공중공격이 같은지

	//Ground Weapon
	BOOL				GWable;			//지상공격 가능여부
	ATTACKTYPE			GWAttackType;	//공격타입(업그레이드에 사용)
	TCHAR				GWname[100];	//공격이름
	UINT				GWdamage;		//공격력
	UINT				GWdamagePlus;	//추가 공격력
	UINT				GWmaxHit;		//공격최대횟수(프레임당) 
	DAMAGETYPE			GWdamageType;	//공격타입
	FLOAT				GWcooldown;		//공격쿨타임
	FLOAT				GWattackRange;	//공격범위

	//Air Weapon
	BOOL				AWable;			//공중공격 가능여부
	ATTACKTYPE			AWAttackType;	//공격타입(업그레이드에 사용)
	TCHAR				AWname[100];	//공격력
	UINT				AWdamage;		//추가 공격력
	UINT				AWdamagePlus;	//공격보너스데미지
	UINT				AWmaxHit;		//공격최대횟수(프레임당) 
	DAMAGETYPE			AWdamageType;	//공격타입
	FLOAT				AWcooldown;		//공격쿨타임
	FLOAT				AWattackRange;	//공격범위

	DWORD				commands[COMMAND_MAX];		//유닛이 사용하는 커맨드 셋트
	
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

	FLOAT				curHP;			//현재 HP
	FLOAT				maxHP;			//최대 HP
	FLOAT				curSH;			//현재 실드
	FLOAT				maxSH;			//최대 실드
	FLOAT				curMP;			//현재 에너지
	FLOAT				maxMP;			//최대 에너지

	UINT				curGWdamage;	//현재 지상공격력
	UINT				curAWdamage;	//현재 공중공격력
	UINT				curArmor;		//현재 방어력


	MYPOINT				pt;				//현재위치
	POINT				ptTile;			//현재위치한 타일
	RECT				rcBody;			//유닛 몸체
	RECT				rcEllipse;		//클릭했을때 보여주는 타원
	FLOAT				angleDeg;			//바라보는 각도
	DIRECTION			direction;		//움직일때 이동방향

	FLOAT				moveSpeed;		//이동속도


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
	//전역변수처럼 Unit 정보들을 담아놓고 원할때 자식클래스에서 받아오도록 한다.
private:
	static POINT		_zuBodySize[UNITNUM_ZERG_MAX];


protected:
	//유닛 고유 번호를 입력받는다. 
	//셋 중 하나는 값이 있어야하며
	//셋 다 -1 값이 -1이면 에러
	UNITNUM_ZERG		_unitNumZ;
	UNITNUM_TERRAN		_unitNumT;
	UNITNUM_PROTOSS		_unitNumP;

	//기본속성과 실시간속성으로 나누자!
	tagUnitBaseStatus	_baseStatus;
	tagUnitBattleStatus	_battleStatus;
	
	zergUpgrade*		_zergUpgrade;

	aStar*				_aStar;
	vTile				_vCloseList;	//A* 에서 계산되서 받은 타일들


public:
	Unit(bool initUnitInfo);
	Unit();
	~Unit();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//업그레이드가 완료되었을 때 BattleStatus 를 업데이트한다.
	virtual void updateBattleStatus(void);
	virtual void updatePosition(void);
	virtual void updateImageFrame(void);


	//커맨드를 처리한다.
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


