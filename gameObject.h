#pragma once
#include "gameNode.h"

#include "zergUpgrade.h"
#include "aStar.h"

//전방선언
class Unit;
class Building;
class gameObject;
class player;

enum UNITSTATE
{
	UNITSTATE_STOP,
	UNITSTATE_MOVE,
	UNITSTATE_ATTACK,
	UNITSTATE_SPELL
};

enum PROCESSING
{
	PROCESSING_NONE,
	PROCESSING_MUTATING,
	PROCESSING_MORPHING,
	PROCESSING_EVOLVING,

	PROCESSING_MAX
};


//BaseStatus
struct tagBaseStatus
{
	//Properties
	TCHAR				name[50];		//이름
	image*				imgBody;		//이미지-몸체
	image*				imgFace;		//이미지-얼굴(우측하단)
	image*				imgStat1;		//이미지-스탯상태(1마리클릭했을때)
	image*				imgStat2;		//이미지-스탯상태(복수클릭했을때)

	FLOAT				unitControl;	//유닛이 차지하는 인구수
	FLOAT				publicControl;	//공급해주는 인구수

	FLOAT				maxHP;			//HP

	BOOL				useSH;			//실드여부
	FLOAT				maxSH;			//실드

	BOOL				useMP;			//에너지여부
	FLOAT				maxMP;			//에너지

	FLOAT				sight;			//시야
	BOOL				detector;		//디텍터(오버로드, 스포어콜로니)

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
struct tagBattleStatus
{
	BOOL				isDead;			//
	INT					isBusy;			//AStarThread 에서 계산중일때 죽어서 Delete 되는것 방지
	UNITSTATE			unitState;		//

	COMMAND				curCommand;		//
	COMMAND				oldCommand;		//
	BOOL				useAstar;		//
	BOOL				calcAstar;		//
	POINT				ptTarget;		//이동할때 가려는 위치
	POINT				ptTileTarget;	//건물 지을때 추가로 받는 위치
	gameObject*			targetObject;	//


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
	RECT				rcTile;			//건물이 차지하는 타일
	RECT				rcEllipse;		//클릭했을때 보여주는 타원
	FLOAT				angleDeg;		//바라보는 각도
	DIRECTION			direction;		//움직일때 이동방향

	FLOAT				moveSpeed;		//이동속도

	BOOL				isCollision;	//충돌했는지?

	BOOL				isMoving;
	MYPOINT				ptold;			//이전위치
	POINT				ptTileOccupy;	//정지상태일때 자리를 차지하고 있는 타일(맵에 등록함)


	BOOL				isBurrow;

	POINT				bodyFrame;
	FLOAT				bodyFrameTime;
	POINT				stat1Frame;
	POINT				stat2Frame;

};

struct tagProcessing
{
	PROCESSING		type;
	COMMAND			command;
	image*			img;
	FLOAT			curTime;
	FLOAT			maxTime;
	BOOL			complete;
};

class gameObject : public gameNode
{
protected:
	//유효한 오브젝트인지
	//gameObject를 기준으로 MemoryPooling 을 할것이기 때문에
	//Unit이나 Building으로 init 이 되었는지 확인용
	BOOL					_valid;

	gameObject*				_nextObject;	//유닛이나 건물이 다른 오브젝트로 변형될 경우, 다음 오브젝트를 선택해준다.

	//플레이어 정보
	player*					_player;
	PLAYER					_playerNum;

	//종족
	RACES					_race;

	//유닛인지 건물인지
	BOOL					_isBuilding;

	//유닛 고유 번호
	UNITNUM_ZERG			_unitNumZ;
	UNITNUM_TERRAN			_unitNumT;
	UNITNUM_PROTOSS			_unitNumP;
	//건물 고유 번호
	BUILDINGNUM_ZERG		_buildingNumZ;
	BUILDINGNUM_TERRAN		_buildingNumT;
	BUILDINGNUM_PROTOSS		_buildingNumP;

	BOOL					_isNrMineral;
	BOOL					_isNrGas;



	//기본속성과 실시간속성으로 나누자!
	tagBaseStatus			_baseStatus;
	tagBattleStatus			_battleStatus;

	//현재 진행중인 작업
	tagProcessing			_processing;

	zergUpgrade*			_zergUpgrade;

	aStar*					_aStar;
	vTile					_vCloseList;	//A* 에서 계산되서 받은 타일들

	//resource
	UINT					_amountMineral;
	UINT					_amountGas;

public:
	gameObject();
	~gameObject();

	virtual HRESULT init(void);	//초기화
	virtual void release(void);	//메모리 해제
	virtual void update(void);	//연산관련(타이머)
	virtual void render(void);	//그려주는 함수
	virtual void getChar(WPARAM wParam);

	//업그레이드가 완료되었을 때 BattleStatus 를 업데이트한다.
	virtual void updateBattleStatus(void);
	virtual void updatePosition(void);
	virtual void updateImageFrame(void);

	void receiveCommand(COMMAND cmd);
	void receiveCommand(COMMAND cmd, POINT pt);
	void receiveCommand(COMMAND cmd, POINT pt, POINT ptTile);
	void receiveCommand(COMMAND cmd, gameObject* object);

	UINT gatherMineral(void);
	UINT gatherGas(void);

	void hitDamage(gameObject* object);

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

	inline UNITNUM_ZERG		getUnitnumZerg(void) { return _unitNumZ; }
	inline UNITNUM_TERRAN	getUnitnumTerran(void) { return _unitNumT; }
	inline UNITNUM_PROTOSS	getUnitnumProtoss(void) { return _unitNumP; }

	inline BUILDINGNUM_ZERG		getBuildingNumZerg(void) { return _buildingNumZ; }
	inline BUILDINGNUM_TERRAN	getBuildingNumTerran(void) { return _buildingNumT; }
	inline BUILDINGNUM_PROTOSS	getBuildingNumProtoss(void) { return _buildingNumP; }

	inline BOOL getIsNrMineral(void) { return _isNrMineral; }
	inline BOOL getIsNrGas(void) { return _isNrGas; }


	inline tagBaseStatus getBaseStatus(void) { return _baseStatus; }
	inline tagBattleStatus getBattleStatus(void) { return _battleStatus; }
	inline void setBattleStatus(tagBattleStatus status) { _battleStatus = status; }
	inline tagProcessing getProcessing(void) { return _processing; }

	inline UINT getAmountMineral(void) { return _amountMineral; }
	inline UINT getAmountGas(void) { return _amountGas; }
	inline void setAmountGas(UINT gas) { _amountGas = gas; }


	//A* 관련
	inline INT getIsBusy(void) { return _battleStatus.isBusy; }
	inline void addIsBusy(INT busy) { _battleStatus.isBusy |= busy; }
	inline void deleteIsBusy(INT busy) { _battleStatus.isBusy &= ~busy; }

	inline void setCalcAstar(BOOL calc) { _battleStatus.calcAstar = calc; }
	inline void setVCloseList(vTile list) { _vCloseList = list; }

	//baseStatus 중 일부만 받을때

	//battleStatus 중 일부만 받을때
	inline void setClicked(BOOL clicked) { _battleStatus.clicked = clicked; }
	inline BOOL getClicked(void) { return _battleStatus.clicked; }
	inline void setCurHP(float curHP) { _battleStatus.curHP = curHP; }
	inline void setIsCollision(bool collision) { _battleStatus.isCollision = collision; }
};

