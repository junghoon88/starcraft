#include "stdafx.h"
#include "zuZergEgg.h"



zuZergEgg::zuZergEgg(PLAYER playerNum, UNITNUM_ZERG nextUnitNum)
{
	_valid = true;

	//플레이어 정보
	_playerNum = playerNum;

	//종족
	_race = RACES_ZERG;

	//유닛인지 건물인지
	_isBuilding = false;

	//유닛 고유 번호
	_unitNumZ = UNITNUM_ZERG_ZERGEGG;

	_nextUnitNum = nextUnitNum;

	_complete = false;

	_zergProductionInfo = new zergProductionInfo;
}


zuZergEgg::~zuZergEgg()
{
}

HRESULT zuZergEgg::init(POINT pt)
{
	initBaseStatus();
	initBattleStatus(pt);



	updatePosition();

	updateBattleStatus();


	return S_OK;
}


void zuZergEgg::initBaseStatus(void)
{
	//Properties
	_stprintf(_baseStatus.name, L"Zerg Egg");	//이름
												//BaseStatus
	TCHAR strKey[100];
	_stprintf(strKey, L"ZU-zergeggBody%d", _playerNum);
	_baseStatus.imgBody = IMAGEMANAGER->findImage(strKey);				//이미지-몸체
	_baseStatus.imgFace = NULL;											//이미지-얼굴(우측하단)
	_baseStatus.imgStat1 = NULL;//IMAGEMANAGER->findImage(L"ZU-droneStat1");	//이미지-스탯상태(1마리클릭했을때)
	_baseStatus.imgStat2 = NULL;//IMAGEMANAGER->findImage(L"ZU-droneStat2");	//이미지-스탯상태(복수클릭했을때)

	_baseStatus.maxHP = 200.0f;					//HP

	_baseStatus.useSH = FALSE;					//실드여부
	_baseStatus.maxSH = 0.0f;					//실드

	_baseStatus.useMP = FALSE;					//에너지여부
	_baseStatus.maxMP = 0.0f;					//에너지

	_baseStatus.sight = 5.0f;					//시야
	_baseStatus.detector = FALSE;				//디텍터(오버로드, 스포어콜로니)

	_baseStatus.isAir = FALSE;					//공중유닛인지
	_baseStatus.moveSpeed = 0.0f;				//이동속도

	_baseStatus.unitSize = UNITSIZE_SMALL;		//유닛사이즈
	_baseStatus.transportslots = 0;				//수송 슬롯칸 수
	_baseStatus.armor = 10;						//방어력
	_baseStatus.armorPlus = 1;					//추가 방어력

												//combat
	_baseStatus.sameGWAW = FALSE;						//지상공격, 공중공격이 같은지
	_baseStatus.GWable = FALSE;							//지상공격 가능여부
	_baseStatus.AWable = FALSE;							//공중공격 가능여부

	_baseStatus.commands[0] = COMMAND_NONE;
	_baseStatus.commands[1] = COMMAND_NONE;
	_baseStatus.commands[2] = COMMAND_NONE;
	_baseStatus.commands[3] = COMMAND_NONE;
	_baseStatus.commands[4] = COMMAND_NONE;
	_baseStatus.commands[5] = COMMAND_NONE;
	_baseStatus.commands[6] = COMMAND_NONE;
	_baseStatus.commands[7] = COMMAND_NONE;
	_baseStatus.commands[8] = COMMAND_ESC;
}
void zuZergEgg::initBattleStatus(POINT pt)
{
	//BattleStatus
	_battleStatus.unitState = UNITSTATE_STOP;
	_battleStatus.curCommand = COMMAND_STOP;
	_battleStatus.clicked = false;
	_battleStatus.curHP = _baseStatus.maxHP;			//현재 HP
	_battleStatus.maxHP = _baseStatus.maxHP;			//최대 HP

	_battleStatus.pt.set((float)pt.x, (float)pt.y);							//현재위치
	_battleStatus.moveSpeed = _baseStatus.moveSpeed;
}


void zuZergEgg::release(void)
{
	SAFE_DELETE(_zergProductionInfo);
}

void zuZergEgg::update(void)
{
	if (_battleStatus.bodyFrame.x < 4)
	{
		_battleStatus.bodyFrame.x++;
	}
	else
	{
		if (_complete == false)
		{
			_battleStatus.bodyFrameTime += TIMEMANAGER->getElapsedTime();
			if (_battleStatus.bodyFrameTime >= UNIT_BODY_FPS_TIME)
			{
				_battleStatus.bodyFrameTime -= UNIT_BODY_FPS_TIME;
				_battleStatus.bodyFrame.x = (_battleStatus.bodyFrame.x == 6) ? 4 : _battleStatus.bodyFrame.x + 1;
			}
		}
		else
		{

		}
	}

}

void zuZergEgg::render(void)
{

}

void zuZergEgg::updateBattleStatus(void)
{

}
void zuZergEgg::updatePosition(void)
{

}
void zuZergEgg::updateImageFrame(void)
{

}

void zuZergEgg::procCommands(void)
{

}
