#include "stdafx.h"
#include "zuZergEgg.h"

#include "player.h"

#include "zuDrone.h"
#include "zuZergling.h"
#include "zuOverlord.h"
#include "zuHydralisk.h"
#include "zuMutalisk.h"
#include "zuScourge.h"
#include "zuQueen.h"
#include "zuUltralisk.h"
#include "zuDefiler.h"

#include <assert.h>

zuZergEgg::zuZergEgg(PLAYER playerNum, UNITNUM_ZERG nextUnitNum)
{
	_valid = true;

	//�÷��̾� ����
	_playerNum = playerNum;

	//����
	_race = RACES_ZERG;

	//�������� �ǹ�����
	_isBuilding = false;

	//���� ���� ��ȣ
	_unitNumZ = UNITNUM_ZERG_ZERGEGG;

	_nextUnitNum = nextUnitNum;


	_buildTime = _buildTimeMax = 0.0f;

	_complete = false;

	_zergProductionInfo = new zergProductionInfo;

	_nextUnit = NULL;

	_progressBar = NULL;
}


zuZergEgg::~zuZergEgg()
{
}

HRESULT zuZergEgg::init(POINT pt)
{
	initNextUnit(pt);
	initBaseStatus();
	initBattleStatus(pt);



	updatePosition();

	updateBattleStatus();


	_buildTimeMax = _zergProductionInfo->getZUProductionInfo(_nextUnitNum).buildTime;



	_progressBar = new progressBar;
	_progressBar->init(L"Mutating");
	_progressBar->setPointLT(263, 427);



	return S_OK;
}

void zuZergEgg::initNextUnit(POINT pt)
{
	switch (_nextUnitNum)
	{
	case UNITNUM_ZERG_DRONE:
		_nextUnit = new zuDrone(_playerNum);
		break;
	case UNITNUM_ZERG_ZERGLING:
		_nextUnit = new zuZergling(_playerNum);
		break;
	case UNITNUM_ZERG_OVERLORD:
		_nextUnit = new zuOverlord(_playerNum);
		break;
	case UNITNUM_ZERG_HYDRALISK:
		_nextUnit = new zuHydralisk(_playerNum);
		break;
	case UNITNUM_ZERG_MUTALISK:
		_nextUnit = new zuMutalisk(_playerNum);
		break;
	case UNITNUM_ZERG_SCOURGE:
		_nextUnit = new zuScourge(_playerNum);
		break;
	case UNITNUM_ZERG_QUEEN:
		_nextUnit = new zuQueen(_playerNum);
		break;
	case UNITNUM_ZERG_ULTRALISK:
		_nextUnit = new zuUltralisk(_playerNum);
		break;
	case UNITNUM_ZERG_DEFILER:
		_nextUnit = new zuDefiler(_playerNum);
		break;
	}

	if (_nextUnit == NULL)
	{
		assert(L"egg->nextUnit ����");
		return;
	}

	_nextUnit->setLinkAdressZergUpgrade(_zergUpgrade);
	_nextUnit->setLinkAdressAstar(_aStar);
	_nextUnit->setLinkAdressPlayer(_player);
	_nextUnit->init(pt);

}


void zuZergEgg::initBaseStatus(void)
{
	_stprintf(_baseStatus.name, L"Zerg Egg");	
												
	TCHAR strKey[100];
	_stprintf(strKey, L"ZU-zergegg-Body%d", _playerNum);
	_baseStatus.imgBody = IMAGEMANAGER->findImage(strKey);				
	_baseStatus.imgFace = NULL;											
	_baseStatus.imgStat1 = IMAGEMANAGER->findImage(L"ZU-zergegg-Stat1");	
	_baseStatus.imgStat2 = IMAGEMANAGER->findImage(L"ZU-zergegg-Stat2");	
	
	_baseStatus.unitControl = _nextUnit->getBaseStatus().unitControl;

	_baseStatus.maxHP = 200.0f;					

	_baseStatus.useSH = FALSE;					
	_baseStatus.maxSH = 0.0f;					

	_baseStatus.useMP = FALSE;					
	_baseStatus.maxMP = 0.0f;					

	_baseStatus.sight = 5.0f;					
	_baseStatus.detector = FALSE;				

	_baseStatus.isAir = FALSE;					
	_baseStatus.moveSpeed = 0.0f;				

	_baseStatus.unitSize = UNITSIZE_SMALL;		
	_baseStatus.transportslots = 0;				
	_baseStatus.armor = 10;						
	_baseStatus.armorPlus = 1;					

												
	_baseStatus.sameGWAW = FALSE;				
	_baseStatus.GWable = FALSE;					
	_baseStatus.AWable = FALSE;					

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
	_battleStatus.curHP = _baseStatus.maxHP;			//���� HP
	_battleStatus.maxHP = _baseStatus.maxHP;			//�ִ� HP

	_battleStatus.pt.set((float)pt.x, (float)pt.y);							//������ġ
	_battleStatus.moveSpeed = _baseStatus.moveSpeed;
}


void zuZergEgg::release(void)
{
	SAFE_RELEASEDELETE(_nextUnit);
	SAFE_RELEASEDELETE(_progressBar);
	SAFE_DELETE(_zergProductionInfo);
}

void zuZergEgg::update(void)
{
	Unit::update();

	updateProgressBar();


}

void zuZergEgg::render(void)
{
	Unit::render();

	_progressBar->ZRender(ZORDER_INTERFACE2);

}

void zuZergEgg::updateBattleStatus(void)
{
	POINT pt = _battleStatus.pt.toPoint();
	_battleStatus.ptTile = { pt.x / TILESIZE, pt.y / TILESIZE };			//������ġ�� Ÿ��

	POINT unitsize = UNITSIZE_ZERG_ZERGEGG;

	_battleStatus.rcBody = RectMakeCenter(pt.x, pt.y, unitsize.x, unitsize.y);			//���� ��ü
	_battleStatus.rcEllipse = _battleStatus.rcBody;		//Ŭ�������� �����ִ� Ÿ��
	_battleStatus.rcEllipse.top += unitsize.y / 4;
	_battleStatus.rcEllipse.bottom -= unitsize.y / 4;
}
void zuZergEgg::updatePosition(void)
{
	Unit::updateBattleStatus();

}
void zuZergEgg::updateImageFrame(void)
{
	//�߰� �ݺ�
	_battleStatus.bodyFrameTime += TIMEMANAGER->getElapsedTime();
	if (_battleStatus.bodyFrameTime >= UNIT_BODY_FPS_TIME)
	{
		_battleStatus.bodyFrameTime -= UNIT_BODY_FPS_TIME;

		if (!_complete)
		{
			//ó��
			if (_battleStatus.bodyFrame.x < 4)
			{
				_battleStatus.bodyFrame.x++;
			}
			else
			{
				_battleStatus.bodyFrame.x = (_battleStatus.bodyFrame.x == 6) ? 4 : _battleStatus.bodyFrame.x + 1;
			}
		}
		else
		{
			//������
			if (_battleStatus.bodyFrame.x < 9)
			{
				_battleStatus.bodyFrame.x++;
			}
			else
			{
				_player->addUnit(_nextUnit);

				_nextObject = _nextUnit;
				_valid = false;
			}
		}
	}
}

void zuZergEgg::updateProgressBar(void)
{
	float tick = TIMEMANAGER->getElapsedTime() * BUILDSPEEDMULTIPLY;

	if (_complete == false)
	{
		_buildTime += tick;

		if (_buildTime >= _buildTimeMax)
		{
			_buildTime = _buildTimeMax;

			_complete = true;
			_battleStatus.bodyFrame.x = 7;
		}
	}

	_progressBar->setGauge(_buildTime, _buildTimeMax);

}

void zuZergEgg::procCommands(void)
{
	if (_battleStatus.curCommand == COMMAND_ESC)
	{

	}
	else
	{
		_battleStatus.curCommand = COMMAND_NONE;
	}
}
