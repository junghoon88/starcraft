#pragma once
#include "gameNode.h"

struct tagProperties
{
	RACES				race;			//종족

	TCHAR				name[50];		//이름
	image*				imgBody;		//이미지-몸체
	animation*			aniFace;		//이미지-얼굴(우측하단)
	image*				imgStat;		//이미지-스탯상태(1마리클릭했을때)

	FLOAT				curHP;			//HP
	FLOAT				maxHP;			//HP

	BOOL				isShield;		//실드여부
	FLOAT				curSH;			//실드
	FLOAT				maxSH;			//실드

	FLOAT				sight;			//시야

	BOOL				isAir;			//공중에 있는지(테란건물)
	FLOAT				moveSpeed;		//이동속도

	UNITSIZE			unitSize;		//유닛사이즈
	UINT				transportslots;	//수송 슬롯칸 수
	UINT				armor;			//방어력

};

struct tagProduction
{
	UINT				costMinerals;	//소모 미네랄
	UINT				costGas;		//소모 가스
	FLOAT				buildTime;		//빌드시간
	TCHAR				hotKey;			//단축키
};

struct tagCombat
{
	BOOL				sameGWAW;		//지상공격, 공중공격이 같은지

										//Ground Weapon
	BOOL				GWable;			//지상공격 가능여부
	TCHAR				GWname[100];	//공격이름
	UINT				GWdamage;		//공격데미지
	UINT				GWdamagePlus;	//공격보너스데미지
	UINT				GWmaxHit;		//공격최대횟수(프레임당) 
	DAMAGETYPE			GWdamageType;	//공격타입
	FLOAT				GWcooldown;		//공격쿨타임
	FLOAT				GWattackRange;	//공격범위

										//Air Weapon
	BOOL				AWable;			//공중공격 가능여부
	TCHAR				AWname[100];	//공격이름
	UINT				AWdamage;		//공격데미지
	UINT				AWdamagePlus;	//공격보너스데미지
	UINT				AWmaxHit;		//공격최대횟수(프레임당) 
	DAMAGETYPE			AWdamageType;	//공격타입
	FLOAT				AWcooldown;		//공격쿨타임
	FLOAT				AWattackRange;	//공격범위
};

struct tagPosition
{
	MYPOINT				pt;				//현재위치
	POINT				ptTile;			//현재위치한 타일
	RECT				rcBody;			//건물 몸체
	RECT				rcTile;			//건물이 차지하는 타일

	RECT				rcEllipse;		//클릭했을때 보여주는 타원
	DIRECTION			direction;		//움직일때 이동방향
	FLOAT				angle;			//바라보는 각도

};

class Building : public gameNode
{
protected:
	//유닛 고유 번호를 입력받는다. 
	//셋 중 하나는 값이 있어야하며
	//셋 다 -1 값이 -1이면 에러
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

