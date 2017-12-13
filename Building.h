#pragma once
#include "gameNode.h"

#include "zergUpgrade.h"

//전방선언
class Unit;

struct tagBuildingBaseStatus
{
	RACES				race;			//종족

	PLAYER				playerNum;		//플레이어 정보

	TCHAR				name[50];		//이름
	image*				imgBody;		//이미지-몸체
	image*				imgFace;		//이미지-얼굴(우측하단)
	image*				imgStat;		//이미지-스탯상태(1마리클릭했을때)

	FLOAT				curHP;			//HP
	FLOAT				maxHP;			//HP

	BOOL				useSH;			//실드여부
	FLOAT				curSH;			//실드
	FLOAT				maxSH;			//실드

	BOOL				useMP;			//에너지여부
	FLOAT				maxMP;			//에너지

	FLOAT				sight;			//시야

	BOOL				isAir;			//공중에 있는지(테란건물)
	FLOAT				moveSpeed;		//이동속도

	UINT				armor;			//방어력

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

struct tagBuildingBattleStatus
{
	BOOL				isDead;

	DWORD				curCommand;

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
	RECT				rcBody;			//건물 몸체
	RECT				rcTile;			//건물이 차지하는 타일

	RECT				rcEllipse;		//클릭했을때 보여주는 타원
	FLOAT				angle;			//바라보는 각도
	DIRECTION			direction;		//움직일때 이동방향

	POINT				bodyFrame;
	POINT				stat1Frame;
	POINT				stat2Frame;
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


	//기본속성과 실시간속성으로 나누자!
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

