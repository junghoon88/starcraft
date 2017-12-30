#pragma once
#include "gameObject.h"
#include "zergUpgrade.h"

#include "aStar.h"

//전방선언
class Building;
class Unit;


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

	COMMAND				commands[COMMAND_MAX];		//유닛이 사용하는 커맨드 셋트
	
};

//BattleStatus
struct tagUnitBattleStatus
{
	BOOL				isDead;
	BOOL				isBusy;			//AStarThread 에서 계산중일때 죽어서 Delete 되는것 방지
	UNITSTATE			unitState;

	COMMAND				curCommand;
	BOOL				useAstar;
	BOOL				calcAstar;
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

class Unit : public gameObject
{
	//전역변수처럼 Unit 정보들을 담아놓고 원할때 자식클래스에서 받아오도록 한다.
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

	//업그레이드가 완료되었을 때 BattleStatus 를 업데이트한다.
	virtual void updateBattleStatus(void);
	virtual void updatePosition(void);
	virtual void updateImageFrame(void);


	//커맨드를 처리한다.
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


