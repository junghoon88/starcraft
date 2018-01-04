#include "stdafx.h"
#include "zuZergling.h"
#include "zergDefine.h"
#include "player.h"


zuZergling::zuZergling(PLAYER playerNum)
{
	_valid = true;

	//�÷��̾� ����
	_playerNum = playerNum;

	//����
	_race = RACES_ZERG;

	//�������� �ǹ�����
	_isBuilding = false;

	//���� ���� ��ȣ
	_unitNumZ = UNITNUM_ZERG_ZERGLING;
}


zuZergling::~zuZergling()
{
}

HRESULT zuZergling::init(POINT pt)
{
	initBaseStatus();
	initBattleStatus(pt);



	updatePosition();

	updateBattleStatus();


	return S_OK;
}


void zuZergling::initBaseStatus(void)
{
	_stprintf(_baseStatus.name, L"Zerg Zergling");

	TCHAR strKey[100];
	_stprintf(strKey, L"ZU-zergling-Body%d", _playerNum);
	_baseStatus.imgBody = IMAGEMANAGER->findImage(strKey);				
	_baseStatus.imgFace = IMAGEMANAGER->findImage(L"ZU-zergling-Face");
	_baseStatus.imgStat1 = IMAGEMANAGER->findImage(L"ZU-zergling-Stat1");	
	_baseStatus.imgStat2 = IMAGEMANAGER->findImage(L"ZU-zergling-Stat2");	

	_baseStatus.unitControl = 0.5f;

	_baseStatus.maxHP = 35.0f;					

	_baseStatus.useSH = FALSE;					
	_baseStatus.maxSH = 0.0f;					

	_baseStatus.useMP = FALSE;					
	_baseStatus.maxMP = 0.0f;					

	_baseStatus.sight = 5.0f;					
	_baseStatus.detector = FALSE;				

	_baseStatus.isAir = FALSE;					
	_baseStatus.moveSpeed = (_player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_METABOLICK_BOOST].complete == false) ? 5.57f : 8.36f;

	_baseStatus.unitSize = UNITSIZE_SMALL;		
	_baseStatus.transportslots = 1;				
	_baseStatus.armor = 0;						
	_baseStatus.armorPlus = 1;					

												
	_baseStatus.sameGWAW = FALSE;				

	_baseStatus.GWable = TRUE;							
	_baseStatus.GWAttackType = ATTACKTYPE_ZERG_MELEE;	
	_stprintf(_baseStatus.GWname, L"Claws");			
	_baseStatus.GWdamage = 5;							
	_baseStatus.GWdamagePlus = 1;						
	_baseStatus.GWmaxHit = 1;							
	_baseStatus.GWdamageType = DAMAGETYPE_NORMAL;		
	_baseStatus.GWcooldown = (_player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_ADRENAL_GLANDS].complete == false) ? 8.0f : 6.0f; //���۽� 6					
	_baseStatus.GWattackRange = 1.0f;					

	_baseStatus.AWable = FALSE;							

	_baseStatus.commands[0] = COMMAND_MOVE;
	_baseStatus.commands[1] = COMMAND_STOP;
	_baseStatus.commands[2] = COMMAND_ATTACK;
	_baseStatus.commands[3] = COMMAND_PATROL;
	_baseStatus.commands[4] = COMMAND_HOLD;
	_baseStatus.commands[5] = COMMAND_NONE;
	_baseStatus.commands[6] = COMMAND_NONE;
	_baseStatus.commands[7] = COMMAND_NONE;
	_baseStatus.commands[8] = COMMAND_BURROW;
}
void zuZergling::initBattleStatus(POINT pt)
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


void zuZergling::release(void)
{
}

void zuZergling::update(void)
{
	Unit::update();
}

void zuZergling::render(void)
{
	Unit::render();
}

void zuZergling::updatePosition(void)
{
	POINT pt = _battleStatus.pt.toPoint();
	_battleStatus.ptTile = { pt.x / TILESIZE, pt.y / TILESIZE };			//������ġ�� Ÿ��

	POINT unitsize = UNITSIZE_ZERG_ZERGLING;

	_battleStatus.rcBody = RectMakeCenter(pt.x, pt.y, unitsize.x, unitsize.y);			//���� ��ü
	_battleStatus.rcEllipse = _battleStatus.rcBody;		//Ŭ�������� �����ִ� Ÿ��
	_battleStatus.rcEllipse.top += unitsize.y / 2;
}

void zuZergling::updateBattleStatus(void)
{
	Unit::updateBattleStatus();

	_baseStatus.moveSpeed = (_player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_METABOLICK_BOOST].complete == false) ? 5.57f : 8.36f;
	_battleStatus.moveSpeed = (_player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_METABOLICK_BOOST].complete == false) ? 5.57f : 8.36f;
	_baseStatus.GWcooldown = (_player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_ADRENAL_GLANDS].complete == false) ? 8.0f : 6.0f; //���۽� 6					

}

void zuZergling::updateImageFrame(void)
{
	Unit::setImageFrameForAngle();
}

void zuZergling::procCommands(void)
{
	Unit::procCommands();

}
