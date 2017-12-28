#include "stdafx.h"
#include "zuLarva.h"
#include "zergDefine.h"

#include "zuZergEgg.h"

zuLarva::zuLarva(PLAYER playerNum)
{
	_valid = true;

	//플레이어 정보
	_playerNum = playerNum;

	//종족
	_race = RACES_ZERG;

	//유닛인지 건물인지
	_isBuilding = false;

	//유닛 고유 번호
	_unitNumZ = UNITNUM_ZERG_LARVA;

	_zergProductionInfo = new zergProductionInfo;
}


zuLarva::~zuLarva()
{
}

HRESULT zuLarva::init(POINT pt)
{
	initBaseStatus();
	initBattleStatus(pt);

	updatePosition();

	updateBattleStatus();

	return S_OK;
}

void zuLarva::release(void)
{

}

void zuLarva::initBaseStatus(void)
{
	//Properties
	_stprintf(_baseStatus.name, L"Zerg Larva");	
												
	TCHAR strKey[100];
	_stprintf(strKey, L"ZU-larvaBody%d", _playerNum);
	_baseStatus.imgBody = IMAGEMANAGER->findImage(strKey);				
	_baseStatus.imgFace = NULL;											
	_baseStatus.imgStat1 = IMAGEMANAGER->findImage(L"ZU-larvaStat1");	
	_baseStatus.imgStat2 = IMAGEMANAGER->findImage(L"ZU-larvaStat2");

	_baseStatus.maxHP = 25.0f;					

	_baseStatus.useSH = FALSE;					
	_baseStatus.maxSH = 0.0f;					

	_baseStatus.useMP = FALSE;					
	_baseStatus.maxMP = 0.0f;					

	_baseStatus.sight = 2.0f;					
	_baseStatus.detector = FALSE;				

	_baseStatus.isAir = FALSE;					
	_baseStatus.moveSpeed = 5.0f;				

	_baseStatus.unitSize = UNITSIZE_SMALL;		
	_baseStatus.transportslots = 0;				
	_baseStatus.armor = 10;						
	_baseStatus.armorPlus = 1;					

												
	_baseStatus.sameGWAW = FALSE;				

	_baseStatus.GWable = TRUE;					

	_baseStatus.AWable = FALSE;					

	_baseStatus.commands[0] = COMMAND_UNIT_DRONE;
	_baseStatus.commands[1] = COMMAND_UNIT_ZERGLING;
	_baseStatus.commands[2] = COMMAND_UNIT_OVERLORD;
	_baseStatus.commands[3] = COMMAND_UNIT_HYDRALISK;
	_baseStatus.commands[4] = COMMAND_UNIT_MUTALISK;
	_baseStatus.commands[5] = COMMAND_UNIT_SCOURGE;
	_baseStatus.commands[6] = COMMAND_UNIT_QUEEN;
	_baseStatus.commands[7] = COMMAND_UNIT_ULTRALISK;
	_baseStatus.commands[8] = COMMAND_UNIT_DEFILER;
}
void zuLarva::initBattleStatus(POINT pt)
{
	//BattleStatus
	_battleStatus.unitState = UNITSTATE_STOP;
	_battleStatus.curCommand = COMMAND_STOP;
	_battleStatus.clicked = false;
	_battleStatus.curHP = _baseStatus.maxHP;			
	_battleStatus.maxHP = _baseStatus.maxHP;			

	_battleStatus.pt.set((float)pt.x, (float)pt.y);		
	_battleStatus.moveSpeed = _baseStatus.moveSpeed;
	_battleStatus.angleDeg = 315.0f;					
	_battleStatus.direction;							
}


void zuLarva::update(void)
{
	Unit::update();

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_battleStatus.angleDeg += 45.0f;

		if (_battleStatus.angleDeg >= 360.0f)
			_battleStatus.angleDeg -= 360.0f;
	}

}

void zuLarva::render(void)
{
	Unit::render();
}

void zuLarva::updatePosition(void)
{
	POINT pt = _battleStatus.pt.toPoint();
	_battleStatus.ptTile = { pt.x / TILESIZE, pt.y / TILESIZE };			//현재위치한 타일

	POINT unitsize = UNITSIZE_ZERG_LARVA;

	_battleStatus.rcBody = RectMakeCenter(pt.x, pt.y, unitsize.x, unitsize.y);			//유닛 몸체
	_battleStatus.rcEllipse = _battleStatus.rcBody;		//클릭했을때 보여주는 타원
	_battleStatus.rcEllipse.top    += unitsize.y / 4;
	_battleStatus.rcEllipse.bottom -= unitsize.y / 4;
}

void zuLarva::updateBattleStatus(void)
{
	Unit::updateBattleStatus();


}

void zuLarva::updateImageFrame(void)
{
	Unit::updateImageFrame();
}


void zuLarva::procCommands(void)
{
	switch (_battleStatus.curCommand)
	{
		case COMMAND_UNIT_DRONE:
			printf("");
			_battleStatus.curCommand = COMMAND_NONE;
			break;
		case COMMAND_UNIT_ZERGLING:
		case COMMAND_UNIT_OVERLORD:
		case COMMAND_UNIT_HYDRALISK:
		case COMMAND_UNIT_MUTALISK:
		case COMMAND_UNIT_SCOURGE:
		case COMMAND_UNIT_QUEEN:
		case COMMAND_UNIT_ULTRALISK:
		case COMMAND_UNIT_DEFILER:
			break;
	}

}