#pragma once
#include "gameNode.h"
#include "zergUpgrade.h"

struct tagBaseStatus
{
	//Properties
	RACES				race;			//종족

	PLAYER				playerNum;

	TCHAR				name[50];		//이름
	image*				imgBody;		//이미지-몸체
	animation*			aniFace;		//이미지-얼굴(우측하단)
	image*				imgStat1;		//이미지-스탯상태(1마리클릭했을때)
	image*				imgStat2;		//이미지-스탯상태(복수클릭했을때)

	FLOAT				maxHP;			//HP
	
	BOOL				isShield;		//실드여부
	FLOAT				maxSH;			//실드

	BOOL				isEnergy;		//에너지여부
	FLOAT				maxEN;			//에너지

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

};

//BattleStatus
struct tagBattleStatus
{
	FLOAT				curHP;			//현재 HP
	FLOAT				maxHP;			//최대 HP
	FLOAT				curSH;			//현재 실드
	FLOAT				maxSH;			//최대 실드
	FLOAT				curEN;			//현재 에너지
	FLOAT				maxEN;			//최대 에너지

	UINT				curGWdamage;	//현재 지상공격력
	UINT				curAWdamage;	//현재 공중공격력
	UINT				curArmor;		//현재 방어력


	MYPOINT				pt;				//현재위치
	POINT				ptTile;			//현재위치한 타일
	RECT				rcBody;			//유닛 몸체
	RECT				rcEllipse;		//클릭했을때 보여주는 타원
	FLOAT				angle;			//바라보는 각도
	DIRECTION			direction;		//움직일때 이동방향

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

	//업그레이드가 완료되었을 때 BattleStatus 를 업데이트한다.
	virtual void updateBattleStatus(void);


public:
	inline void setLinkAdressZergUpgrade(zergUpgrade* zergUpgrade) { _zergUpgrade = zergUpgrade; }
	inline POINT getZuBodySize(UNITNUM_ZERG num) { return _zuBodySize[num]; }

	inline tagBaseStatus getBaseStatus(void) { return _baseStatus; }
	inline tagBattleStatus getBattleStatus(void) { return _battleStatus; }


};

