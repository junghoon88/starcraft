#include "stdafx.h"
#include "zuDrone.h"
#include "tileNode.h"


zuDrone::zuDrone()
{
	//유닛 고유 번호
	_unitNumZ = UNITNUM_ZERG_DRONE;

	//Properties
	_baseStatus.race = RACES_ZERG;				//종족

	_stprintf(_baseStatus.name, L"Zerg Drone");	//이름
	_baseStatus.imgBody = NULL;					//이미지-몸체
	_baseStatus.aniFace = NULL;					//이미지-얼굴(우측하단)
	_baseStatus.imgStat1 = NULL;				//이미지-스탯상태(1마리클릭했을때)
	_baseStatus.imgStat2 = NULL;				//이미지-스탯상태(복수클릭했을때)

	_baseStatus.maxHP = 40.0f;					//HP

	_baseStatus.isShield = FALSE;				//실드여부
	_baseStatus.maxSH = 0.0f;					//실드

	_baseStatus.isEnergy = FALSE;				//에너지여부
	_baseStatus.maxEN = 0.0f;					//에너지

	_baseStatus.sight = 7.0f;					//시야

	_baseStatus.isAir = FALSE;					//공중유닛인지
	_baseStatus.moveSpeed = 5.0f;				//이동속도

	_baseStatus.unitSize = UNITSIZE_SMALL;		//유닛사이즈
	_baseStatus.transportslots = 1;				//수송 슬롯칸 수
	_baseStatus.armor = 0;						//방어력
	_baseStatus.armorPlus = 1;					//추가 방어력



	//combat
	_baseStatus.sameGWAW = FALSE;						//지상공격, 공중공격이 같은지

	_baseStatus.GWable = TRUE;							//지상공격 가능여부
	_baseStatus.GWAttackType = ATTACKTYPE_ZERG_WORKER;	//공격타입(업그레이드에 사용)
	_stprintf(_baseStatus.GWname, L"가시뼈");			//공격이름
	_baseStatus.GWdamage = 5;							//공격데미지
	_baseStatus.GWdamagePlus = 0;						//공격보너스데미지
	_baseStatus.GWmaxHit = 1;							//공격최대횟수(프레임당) 
	_baseStatus.GWdamageType = DAMAGETYPE_NORMAL;		//공격타입
	_baseStatus.GWcooldown = 22.0f;						//공격쿨타임
	_baseStatus.GWattackRange = 1.0f;					//공격범위

	_baseStatus.AWable = FALSE;							//공중공격 가능여부
	//_baseStatus.AWAttackType;							//공격타입(업그레이드에 사용)
	//_baseStatus.AWname[100];							//공격이름
	//_baseStatus.AWdamage;								//공격데미지
	//_baseStatus.AWdamagePlus;							//공격보너스데미지
	//_baseStatus.AWmaxHit;								//공격최대횟수(프레임당) 
	//_baseStatus.AWdamageType;							//공격타입
	//_baseStatus.AWcooldown;							//공격쿨타임
	//_baseStatus.AWattackRange;						//공격범위
}


zuDrone::~zuDrone()
{
}

HRESULT zuDrone::init(PLAYER playerNum, POINT pt)
{
	//BaseStatus
	_baseStatus.playerNum = playerNum;

	TCHAR strKey[100];
	_stprintf(strKey, L"ZU-droneBody%d", playerNum);
	_baseStatus.imgBody = IMAGEMANAGER->findImage(strKey);				//이미지-몸체
	_baseStatus.aniFace = NULL;											//이미지-얼굴(우측하단)
	_baseStatus.imgStat1 = IMAGEMANAGER->findImage(L"ZU-droneStat1");	//이미지-스탯상태(1마리클릭했을때)
	_baseStatus.imgStat2 = IMAGEMANAGER->findImage(L"ZU-droneStat2");	//이미지-스탯상태(복수클릭했을때)


	//BattleStatus
	_battleStatus.curHP = _baseStatus.maxHP;			//현재 HP
	_battleStatus.maxHP = _baseStatus.maxHP;			//최대 HP
	_battleStatus.curSH = _baseStatus.maxSH;			//현재 실드
	_battleStatus.maxSH = _baseStatus.maxSH;			//최대 실드
	_battleStatus.curEN = 0.0f;							//현재 에너지
	_battleStatus.maxEN = _baseStatus.maxEN;			//최대 에너지

	_battleStatus.pt.set((float)pt.x, (float)pt.y);							//현재위치
	_battleStatus.ptTile = { pt.x / MAPTOOL_TILESIZE, pt.y / MAPTOOL_TILESIZE };			//현재위치한 타일
	_battleStatus.rcBody = RectMakeCenter(pt.x, pt.y, getZuBodySize(_unitNumZ).x, getZuBodySize(_unitNumZ).y);			//유닛 몸체
	_battleStatus.rcEllipse;		//클릭했을때 보여주는 타원
	_battleStatus.angle;			//바라보는 각도
	_battleStatus.direction;		//움직일때 이동방향

	updateBattleStatus();

	return S_OK;
}

void zuDrone::release(void)
{

}

void zuDrone::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_battleStatus.bodyFrame.x++;
		if (_battleStatus.bodyFrame.x > _baseStatus.imgBody->getMaxFrameX())
		{
			_battleStatus.bodyFrame.x = 0;
		}
	}
}

void zuDrone::render(void)
{
	Unit::render();

}

void zuDrone::updateBattleStatus(void)
{
	Unit::updateBattleStatus();


}