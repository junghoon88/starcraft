#include "stdafx.h"
#include "zuUltralisk.h"
#include "zergDefine.h"
#include "player.h"


zuUltralisk::zuUltralisk(PLAYER playerNum)
{
	_valid = true;

	//플레이어 정보
	_playerNum = playerNum;

	//종족
	_race = RACES_ZERG;

	//유닛인지 건물인지
	_isBuilding = false;

	//유닛 고유 번호
	_unitNumZ = UNITNUM_ZERG_ULTRALISK;

}


zuUltralisk::~zuUltralisk()
{
}

HRESULT zuUltralisk::init(POINT pt)
{
	initBaseStatus();
	initBattleStatus(pt);



	updatePosition();

	updateBattleStatus();


	return S_OK;
}


void zuUltralisk::initBaseStatus(void)
{
	_stprintf(_baseStatus.name, L"Zerg Ultralisk");

	TCHAR strKey[100];
	_stprintf(strKey, L"ZU-ultralisk-Body%d", _playerNum);
	_baseStatus.imgBody = IMAGEMANAGER->findImage(strKey);
	_baseStatus.imgFace = IMAGEMANAGER->findImage(L"ZU-ultralisk-Face");;
	_baseStatus.imgStat1 = IMAGEMANAGER->findImage(L"ZU-ultralisk-Stat1");
	_baseStatus.imgStat2 = IMAGEMANAGER->findImage(L"ZU-ultralisk-Stat2");

	_baseStatus.unitControl = 4.0f;

	_baseStatus.maxHP = 400.0f;

	_baseStatus.useSH = FALSE;
	_baseStatus.maxSH = 0.0f;

	_baseStatus.useMP = FALSE;
	_baseStatus.maxMP = 0.0f;

	_baseStatus.sight = 7.0f;
	_baseStatus.detector = FALSE;

	_baseStatus.isAir = FALSE;
	_baseStatus.moveSpeed = (_player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_ANABOLIC_SYNTHESIS].complete == false) ? 5.4f : 8.1f;

	_baseStatus.unitSize = UNITSIZE_LARGE;
	_baseStatus.transportslots = 4;
	_baseStatus.armor = 1;
	_baseStatus.armorPlus = 1;


	_baseStatus.sameGWAW = FALSE;

	_baseStatus.GWable = TRUE;
	_baseStatus.GWAttackType = ATTACKTYPE_ZERG_MELEE;
	_stprintf(_baseStatus.GWname, L"Kaiser Baldes");
	_baseStatus.GWdamage = 20;
	_baseStatus.GWdamagePlus = 3;
	_baseStatus.GWmaxHit = 1;
	_baseStatus.GWdamageType = DAMAGETYPE_NORMAL;
	_baseStatus.GWcooldown = 15.0;
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
	_baseStatus.commands[8] = COMMAND_NONE;
}
void zuUltralisk::initBattleStatus(POINT pt)
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

void zuUltralisk::release(void)
{

}

void zuUltralisk::update(void)
{
	Unit::update();

}

void zuUltralisk::render(void)
{
	Unit::render();

}

void zuUltralisk::updatePosition(void)
{
	POINT pt = _battleStatus.pt.toPoint();
	_battleStatus.ptTile = { pt.x / TILESIZE, pt.y / TILESIZE };			//현재위치한 타일

	POINT unitsize = UNITSIZE_ZERG_ULTRALISK;

	_battleStatus.rcBody = RectMakeCenter(pt.x, pt.y, unitsize.x, unitsize.y);			//유닛 몸체
	_battleStatus.rcEllipse = _battleStatus.rcBody;		//클릭했을때 보여주는 타원
	_battleStatus.rcEllipse.top += unitsize.y / 2;
}

void zuUltralisk::updateBattleStatus(void)
{
	Unit::updateBattleStatus();

	_baseStatus.moveSpeed = (_player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_ANABOLIC_SYNTHESIS].complete == false) ? 5.4f : 8.1f;
	_battleStatus.moveSpeed = (_player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_ANABOLIC_SYNTHESIS].complete == false) ? 5.4f : 8.1f;

	_battleStatus.curArmor = _baseStatus.armor + _baseStatus.armorPlus * _zergUpgrade->getUpgrade()[UPGRADE_ZERG_CARAPACE].level
												+ 2 * (int)(_player->getZergUpgrade()->getEvolution()[EVOLUTION_ZERG_CHITINOUS_PLATING].complete);
}

void zuUltralisk::updateImageFrame(void)
{
	Unit::setImageFrameForAngle();

	float tick = TIMEMANAGER->getElapsedTime();

	if (_battleStatus.unitState == UNITSTATE_STOP)
	{
		//0
		_battleStatus.bodyFrame.y = 0;
		_battleStatus.bodyFrameTime = 0.0f;
	}
	else if (_battleStatus.unitState == UNITSTATE_MOVE)
	{
		//1, 2, 3, 4, 5
		if (_battleStatus.bodyFrame.y >= 1 && _battleStatus.bodyFrame.y <= 5)
		{
			_battleStatus.bodyFrameTime += tick;
			if (_battleStatus.bodyFrameTime >= UNIT_BODY_FPS_TIME)
			{
				_battleStatus.bodyFrameTime -= UNIT_BODY_FPS_TIME;

				_battleStatus.bodyFrame.y++;
				if (_battleStatus.bodyFrame.y > 5)
				{
					_battleStatus.bodyFrame.y = 1;
				}
			}
		}
		else
		{
			_battleStatus.bodyFrame.y = 1;
			_battleStatus.bodyFrameTime = 0.0f;
		}
	}
	else if (_battleStatus.unitState == UNITSTATE_ATTACK)
	{
		if (_battleStatus.targetObject == NULL)
		{
			_battleStatus.bodyFrame.y = 0;
			_battleStatus.bodyFrameTime = 0.0f;
			return;
		}

		float attackTime = (_battleStatus.targetObject->getBaseStatus().isAir) ? _baseStatus.AWcooldown : _baseStatus.GWcooldown;
		attackTime = attackTime * UNIT_ATTACK_FPS_TIME / 6; //공격이 6프레임

		//9, 10, 11, 12, 13, 14
		if (_battleStatus.bodyFrame.y >= 9 && _battleStatus.bodyFrame.y <= 14)
		{
			_battleStatus.bodyFrameTime += tick;
			if (_battleStatus.bodyFrameTime >= attackTime)
			{
				_battleStatus.bodyFrameTime -= attackTime;

				_battleStatus.bodyFrame.y++;
				if (_battleStatus.bodyFrame.y > 14)
				{
					_battleStatus.bodyFrame.y = 9;
					_battleStatus.targetObject->hitDamage(this);
				}
			}
		}
		else
		{
			_battleStatus.bodyFrame.y = 9;
			_battleStatus.bodyFrameTime = 0.0f;
		}
	}
}

void zuUltralisk::procCommands(void)
{
	Unit::procCommands();

}
