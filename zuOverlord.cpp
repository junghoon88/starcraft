#include "stdafx.h"
#include "zuOverlord.h"
#include "zergDefine.h"
#include "player.h"


zuOverlord::zuOverlord(PLAYER playerNum)
{
	_valid = true;

	//�÷��̾� ����
	_playerNum = playerNum;

	//����
	_race = RACES_ZERG;

	//�������� �ǹ�����
	_isBuilding = false;

	//���� ���� ��ȣ
	_unitNumZ = UNITNUM_ZERG_OVERLORD;
}


zuOverlord::~zuOverlord()
{
}

HRESULT zuOverlord::init(POINT pt)
{
	initBaseStatus();
	initBattleStatus(pt);



	updatePosition();

	updateBattleStatus();


	return S_OK;
}

void zuOverlord::initBaseStatus(void)
{
	_stprintf(_baseStatus.name, L"Zerg Overlord");

	TCHAR strKey[100];
	_stprintf(strKey, L"ZU-overlord-Body%d", _playerNum);
	_baseStatus.imgBody = IMAGEMANAGER->findImage(strKey);
	_baseStatus.imgFace = IMAGEMANAGER->findImage(L"ZU-overlord-Face");
	_baseStatus.imgStat1 = IMAGEMANAGER->findImage(L"ZU-overlord-Stat1");
	_baseStatus.imgStat2 = IMAGEMANAGER->findImage(L"ZU-overlord-Stat2");

	_baseStatus.unitControl = 0.0f;
	_baseStatus.publicControl = 8.0f;

	_baseStatus.maxHP = 200.0f;

	_baseStatus.useSH = FALSE;
	_baseStatus.maxSH = 0.0f;

	_baseStatus.useMP = FALSE;
	_baseStatus.maxMP = 0.0f;

	_baseStatus.sight = 9.0f; //���۽� 11
	_baseStatus.detector = TRUE;

	_baseStatus.isAir = TRUE;
	_baseStatus.moveSpeed = 0.83; //���۽� 3.33

	_baseStatus.unitSize = UNITSIZE_LARGE;
	_baseStatus.transportslots = 0;
	_baseStatus.armor = 0;
	_baseStatus.armorPlus = 1;


	_baseStatus.sameGWAW = FALSE;

	_baseStatus.GWable = FALSE;

	_baseStatus.AWable = FALSE;

	_baseStatus.commands[0] = COMMAND_MOVE;
	_baseStatus.commands[1] = COMMAND_STOP;
	_baseStatus.commands[2] = COMMAND_NONE;
	_baseStatus.commands[3] = COMMAND_PATROL;
	_baseStatus.commands[4] = COMMAND_HOLD;
	_baseStatus.commands[5] = COMMAND_NONE;
	_baseStatus.commands[6] = COMMAND_NONE;
	_baseStatus.commands[7] = COMMAND_NONE;
	_baseStatus.commands[8] = COMMAND_NONE;
}
void zuOverlord::initBattleStatus(POINT pt)
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


void zuOverlord::release(void)
{
}

void zuOverlord::update(void)
{
	Unit::update();
}

void zuOverlord::render(void)
{
	Unit::render();
}

void zuOverlord::updatePosition(void)
{
	POINT pt = _battleStatus.pt.toPoint();
	_battleStatus.ptTile = { pt.x / TILESIZE, pt.y / TILESIZE };			//������ġ�� Ÿ��

	POINT unitsize = UNITSIZE_ZERG_OVERLORD;

	_battleStatus.rcBody = RectMakeCenter(pt.x, pt.y, unitsize.x, unitsize.y);			//���� ��ü
	_battleStatus.rcEllipse = _battleStatus.rcBody;		//Ŭ�������� �����ִ� Ÿ��
	_battleStatus.rcEllipse.top += unitsize.y / 2;
}

void zuOverlord::updateBattleStatus(void)
{
	Unit::updateBattleStatus();


}

void zuOverlord::updateImageFrame(void)
{
	Unit::setImageFrameForAngle();
}

void zuOverlord::procCommands(void)
{
	Unit::procCommands();

}
