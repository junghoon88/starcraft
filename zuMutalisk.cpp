#include "stdafx.h"
#include "zuMutalisk.h"
#include "zergDefine.h"
#include "player.h"

#include "zuCocoon.h"
#include "bullets.h"


zuMutalisk::zuMutalisk(PLAYER playerNum)
{
	_valid = true;

	//플레이어 정보
	_playerNum = playerNum;

	//종족
	_race = RACES_ZERG;

	//유닛인지 건물인지
	_isBuilding = false;

	//유닛 고유 번호
	_unitNumZ = UNITNUM_ZERG_MUTALISK;
}


zuMutalisk::~zuMutalisk()
{
}

HRESULT zuMutalisk::init(POINT pt)
{
	initBaseStatus();
	initBattleStatus(pt);



	updatePosition();

	updateBattleStatus();


	return S_OK;
}


void zuMutalisk::initBaseStatus(void)
{
	_stprintf(_baseStatus.name, L"Zerg Mutalisk");

	TCHAR strKey[100];
	_stprintf(strKey, L"ZU-mutalisk-Body%d", _playerNum);
	_baseStatus.imgBody = IMAGEMANAGER->findImage(strKey);
	_baseStatus.imgFace = IMAGEMANAGER->findImage(L"ZU-mutalisk-Face");
	_baseStatus.imgStat1 = IMAGEMANAGER->findImage(L"ZU-mutalisk-Stat1");
	_baseStatus.imgStat2 = IMAGEMANAGER->findImage(L"ZU-mutalisk-Stat2");

	_baseStatus.unitControl = 2.0f;

	_baseStatus.maxHP = 120.0f;

	_baseStatus.useSH = FALSE;
	_baseStatus.maxSH = 0.0f;

	_baseStatus.useMP = FALSE;
	_baseStatus.maxMP = 0.0f;

	_baseStatus.sight = 7.0f;
	_baseStatus.detector = FALSE;

	_baseStatus.isAir = TRUE;
	_baseStatus.moveSpeed = 6.67;

	_baseStatus.unitSize = UNITSIZE_SMALL;
	_baseStatus.transportslots = 0;
	_baseStatus.armor = 0;
	_baseStatus.armorPlus = 1;


	_baseStatus.sameGWAW = TRUE;

	_baseStatus.GWable = TRUE;
	_baseStatus.GWAttackType = ATTACKTYPE_ZERG_FLYING;
	_stprintf(_baseStatus.GWname, L"Grave Wurm");
	_baseStatus.GWdamage = 9; //바운스되면 1/3씩 줄어듬
	_baseStatus.GWdamagePlus = 1;
	_baseStatus.GWmaxHit = 1;
	_baseStatus.GWdamageType = DAMAGETYPE_NORMAL;
	_baseStatus.GWcooldown = 30.0;
	_baseStatus.GWattackRange = 3.0f;

	_baseStatus.AWable = TRUE;
	_baseStatus.AWAttackType = ATTACKTYPE_ZERG_FLYING;
	_stprintf(_baseStatus.AWname, L"Grave Wurm");
	_baseStatus.AWdamage = 9; //바운스되면 1/3씩 줄어듬
	_baseStatus.AWdamagePlus = 1;
	_baseStatus.AWmaxHit = 1;
	_baseStatus.AWdamageType = DAMAGETYPE_NORMAL;
	_baseStatus.AWcooldown = 30.0;
	_baseStatus.AWattackRange = 3.0f;

	_baseStatus.commands[0] = COMMAND_MOVE;
	_baseStatus.commands[1] = COMMAND_STOP;
	_baseStatus.commands[2] = COMMAND_ATTACK;
	_baseStatus.commands[3] = COMMAND_PATROL;
	_baseStatus.commands[4] = COMMAND_HOLD;
	_baseStatus.commands[5] = COMMAND_NONE;
	_baseStatus.commands[6] = COMMAND_UNIT_GUADIAN;
	_baseStatus.commands[7] = COMMAND_UNIT_DEVOURER;
	_baseStatus.commands[8] = COMMAND_NONE;
}
void zuMutalisk::initBattleStatus(POINT pt)
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


void zuMutalisk::release(void)
{
}

void zuMutalisk::update(void)
{
	Unit::update();
}

void zuMutalisk::render(void)
{
	Unit::render();
}

void zuMutalisk::updatePosition(void)
{
	POINT pt = _battleStatus.pt.toPoint();
	_battleStatus.ptTile = { pt.x / TILESIZE, pt.y / TILESIZE };			//현재위치한 타일

	POINT unitsize = UNITSIZE_ZERG_MUTALISK;

	_battleStatus.rcBody = RectMakeCenter(pt.x, pt.y, unitsize.x, unitsize.y);			//유닛 몸체
	_battleStatus.rcEllipse = _battleStatus.rcBody;		//클릭했을때 보여주는 타원
	_battleStatus.rcEllipse.top += unitsize.y / 2;
}

void zuMutalisk::updateBattleStatus(void)
{
	Unit::updateBattleStatus();


}

void zuMutalisk::updateImageFrame(void)
{
	Unit::setImageFrameForAngle();

	float tick = TIMEMANAGER->getElapsedTime();

	_battleStatus.bodyFrameTime += tick;
	if (_battleStatus.bodyFrameTime >= UNIT_BODY_FPS_TIME)
	{
		_battleStatus.bodyFrameTime -= UNIT_BODY_FPS_TIME;

		_battleStatus.bodyFrame.y++;
		if (_battleStatus.bodyFrame.y > _baseStatus.imgBody->getMaxFrameY())
		{
			_battleStatus.bodyFrame.y = 0;
		}
	}

	bool fireableGround = false;
	bool fireableAir = false;

	float attackTimeGround = _baseStatus.GWcooldown * UNIT_ATTACK_FPS_TIME;
	float attackTimeAir    = _baseStatus.AWcooldown * UNIT_ATTACK_FPS_TIME;

	_battleStatus.bulletDelayGround += tick;
	if (_battleStatus.bulletDelayGround >= attackTimeGround)
	{
		fireableGround = true;
		_battleStatus.bulletDelayGround = attackTimeGround;
	}

	_battleStatus.bulletDelayAir += tick;
	if (_battleStatus.bulletDelayAir >= attackTimeAir)
	{
		fireableAir = true;
		_battleStatus.bulletDelayAir = attackTimeAir;
	}


	if (_battleStatus.unitState == UNITSTATE_ATTACK && _battleStatus.targetObject != NULL)
	{
		if (_battleStatus.targetObject->getBaseStatus().isAir)
		{
			if (fireableAir)
			{
				bullets* bullet = new bullets(BULLETNUM_MUTALISK);
				bullet->init(this, _battleStatus.targetObject);
				_player->addBullet(bullet);
				_battleStatus.bulletDelayAir = 0.0f;
			}
		}
		else
		{
			if (fireableGround)
			{
				bullets* bullet = new bullets(BULLETNUM_MUTALISK);
				bullet->init(this, _battleStatus.targetObject);
				_player->addBullet(bullet);
				_battleStatus.bulletDelayGround = 0.0f;
			}
		}
	}
}

void zuMutalisk::procCommands(void)
{
	Unit::procCommands();

	if (_battleStatus.curCommand == COMMAND_UNIT_GUADIAN)
	{
		tagProduction buildCost = _player->getZergProductionInfo()->getZUProductionInfo(UNITNUM_ZERG_GUADIAN);

		//내가 차지하고 있는 인구수를 빼준다.
		buildCost.control = buildCost.control - _baseStatus.unitControl;

		if (_player->useResource(buildCost.costMinerals, buildCost.costGas, buildCost.control))
		{
			//성공
			zuCocoon* cocoon = new zuCocoon(_playerNum, UNITNUM_ZERG_GUADIAN);
			cocoon->setLinkAdressZergUpgrade(_zergUpgrade);
			cocoon->setLinkAdressAstar(_aStar);
			cocoon->setLinkAdressPlayer(_player);
			cocoon->init(_battleStatus.pt.toPoint());

			_nextObject = cocoon;
			_valid = false;

			_player->addUnit(cocoon);
		}

		_battleStatus.curCommand = COMMAND_NONE;


	}
	else if (_battleStatus.curCommand == COMMAND_UNIT_DEVOURER)
	{
		tagProduction buildCost = _player->getZergProductionInfo()->getZUProductionInfo(UNITNUM_ZERG_DEVOURER);

		//내가 차지하고 있는 인구수를 빼준다.
		buildCost.control = buildCost.control - _baseStatus.unitControl;

		if (_player->useResource(buildCost.costMinerals, buildCost.costGas, buildCost.control))
		{
			//성공
			zuCocoon* cocoon = new zuCocoon(_playerNum, UNITNUM_ZERG_DEVOURER);
			cocoon->setLinkAdressZergUpgrade(_zergUpgrade);
			cocoon->setLinkAdressAstar(_aStar);
			cocoon->setLinkAdressPlayer(_player);
			cocoon->init(_battleStatus.pt.toPoint());

			_nextObject = cocoon;
			_valid = false;

			_player->addUnit(cocoon);
		}

		_battleStatus.curCommand = COMMAND_NONE;
	}

}
