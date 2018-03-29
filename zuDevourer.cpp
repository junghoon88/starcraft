#include "stdafx.h"
#include "zuDevourer.h"
#include "zergDefine.h"
#include "player.h"


zuDevourer::zuDevourer(PLAYER playerNum)
{
	_valid = true;

	//플레이어 정보
	_playerNum = playerNum;

	//종족
	_race = RACES_ZERG;

	//유닛인지 건물인지
	_isBuilding = false;

	//유닛 고유 번호
	_unitNumZ = UNITNUM_ZERG_DEVOURER;
}


zuDevourer::~zuDevourer()
{
}

HRESULT zuDevourer::init(POINT pt)
{
	initBaseStatus();
	initBattleStatus(pt);



	updatePosition();

	updateBattleStatus();

	return S_OK;
}


void zuDevourer::initBaseStatus(void)
{
	_stprintf(_baseStatus.name, L"Zerg Devourer");

	TCHAR strKey[100];
	_stprintf(strKey, L"ZU-devourer-Body%d", _playerNum);
	_baseStatus.imgBody = IMAGEMANAGER->findImage(strKey);
	_baseStatus.imgFace = IMAGEMANAGER->findImage(L"ZU-devourer-Face");
	_baseStatus.imgStat1 = IMAGEMANAGER->findImage(L"ZU-devourer-Stat1");
	_baseStatus.imgStat2 = IMAGEMANAGER->findImage(L"ZU-devourer-Stat2");

	_baseStatus.unitControl = 2.0f;

	_baseStatus.maxHP = 250.0f;

	_baseStatus.useSH = FALSE;
	_baseStatus.maxSH = 0.0f;

	_baseStatus.useMP = FALSE;
	_baseStatus.maxMP = 0.0f;

	_baseStatus.sight = 10.0f;
	_baseStatus.detector = FALSE;

	_baseStatus.isAir = TRUE;
	_baseStatus.moveSpeed = 5.0f;

	_baseStatus.unitSize = UNITSIZE_LARGE;
	_baseStatus.transportslots = 0;
	_baseStatus.armor = 2;
	_baseStatus.armorPlus = 1;


	_baseStatus.sameGWAW = FALSE;

	_baseStatus.GWable = FALSE;

	_baseStatus.AWable = TRUE;
	_baseStatus.AWAttackType = ATTACKTYPE_ZERG_FLYING;
	_stprintf(_baseStatus.AWname, L"Corrosive Acid");
	_baseStatus.AWdamage = 25;
	_baseStatus.AWdamagePlus = 2;
	_baseStatus.AWmaxHit = 1;
	_baseStatus.AWdamageType = DAMAGETYPE_EXPLOSIVE;
	_baseStatus.AWcooldown = 100.0f;
	_baseStatus.AWattackRange = 6.0f;

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
void zuDevourer::initBattleStatus(POINT pt)
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


void zuDevourer::release(void)
{
}

void zuDevourer::update(void)
{
	Unit::update();
}

void zuDevourer::render(void)
{
	Unit::render();
}

void zuDevourer::updatePosition(void)
{
	POINT pt = _battleStatus.pt.toPoint();
	_battleStatus.ptTile = { pt.x / TILESIZE, pt.y / TILESIZE };			//현재위치한 타일

	POINT unitsize = UNITSIZE_ZERG_DEVOURER;

	_battleStatus.rcBody = RectMakeCenter(pt.x, pt.y, unitsize.x, unitsize.y);			//유닛 몸체
	_battleStatus.rcEllipse = _battleStatus.rcBody;		//클릭했을때 보여주는 타원
	_battleStatus.rcEllipse.top += unitsize.y / 2;
}

void zuDevourer::updateBattleStatus(void)
{
	Unit::updateBattleStatus();




}

void zuDevourer::updateImageFrame(void)
{
	Unit::setImageFrameForAngle();

	float tick = TIMEMANAGER->getElapsedTime();

	bool fireableAir = false;

	float attackTimeAir = _baseStatus.AWcooldown * UNIT_ATTACK_FPS_TIME;

	_battleStatus.bulletDelayAir += tick;
	if (_battleStatus.bulletDelayAir >= attackTimeAir)
	{
		fireableAir = true;
		_battleStatus.bulletDelayAir = attackTimeAir;
	}


	if (_battleStatus.unitState != UNITSTATE_ATTACK)
	{
		if (_battleStatus.bodyFrame.y > 5)
		{
			_battleStatus.bodyFrame.y = 0;
		}

		_battleStatus.bodyFrameTime += tick;
		if (_battleStatus.bodyFrameTime >= UNIT_BODY_FPS_TIME)
		{
			_battleStatus.bodyFrameTime -= UNIT_BODY_FPS_TIME;

			_battleStatus.bodyFrame.y++;
			if (_battleStatus.bodyFrame.y > 5)
			{
				_battleStatus.bodyFrame.y = 0;
			}
		}
	}
	else
	{


		if (_battleStatus.unitState == UNITSTATE_ATTACK && _battleStatus.targetObject != NULL)
		{
			if (_battleStatus.targetObject->getBaseStatus().isAir)
			{
				if (fireableAir)
				{
					_battleStatus.bodyFrameTime += tick;
					if (_battleStatus.bodyFrameTime >= UNIT_BODY_FPS_TIME)
					{
						_battleStatus.bodyFrameTime -= UNIT_BODY_FPS_TIME;

						_battleStatus.bodyFrame.y++;
						if (_battleStatus.bodyFrame.y > 9)
						{
							_battleStatus.bodyFrame.y = 0;

							bullets* bullet = new bullets(BULLETNUM_DEVOURER);
							bullet->init(this, _battleStatus.targetObject);
							_player->addBullet(bullet);
							_battleStatus.bulletDelayAir = 0.0f;
						}
					}
				}
				else
				{
					if (_battleStatus.bodyFrame.y > 6)
					{
						_battleStatus.bodyFrame.y = 0;
					}
					_battleStatus.bodyFrameTime = 0.0f;
					_battleStatus.bodyFrameTime += tick;
					if (_battleStatus.bodyFrameTime >= UNIT_BODY_FPS_TIME)
					{
						_battleStatus.bodyFrameTime -= UNIT_BODY_FPS_TIME;

						_battleStatus.bodyFrame.y++;
						if (_battleStatus.bodyFrame.y > 6)
						{
							_battleStatus.bodyFrame.y = 0;
						}
					}
				}
			}
		}
	}
}

void zuDevourer::procCommands(void)
{
	Unit::procCommands();

}
